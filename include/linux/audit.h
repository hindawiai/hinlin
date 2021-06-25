<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* audit.h -- Auditing support
 *
 * Copyright 2003-2004 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * Written by Rickard E. (Rik) Faith <faith@redhat.com>
 */
#अगर_अघोषित _LINUX_AUDIT_H_
#घोषणा _LINUX_AUDIT_H_

#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <uapi/linux/audit.h>
#समावेश <uapi/linux/netfilter/nf_tables.h>

#घोषणा AUDIT_INO_UNSET ((अचिन्हित दीर्घ)-1)
#घोषणा AUDIT_DEV_UNSET ((dev_t)-1)

काष्ठा audit_sig_info अणु
	uid_t		uid;
	pid_t		pid;
	अक्षर		ctx[];
पूर्ण;

काष्ठा audit_buffer;
काष्ठा audit_context;
काष्ठा inode;
काष्ठा netlink_skb_parms;
काष्ठा path;
काष्ठा linux_binprm;
काष्ठा mq_attr;
काष्ठा mqstat;
काष्ठा audit_watch;
काष्ठा audit_tree;
काष्ठा sk_buff;

काष्ठा audit_krule अणु
	u32			pflags;
	u32			flags;
	u32			listnr;
	u32			action;
	u32			mask[AUDIT_BITMASK_SIZE];
	u32			buflen; /* क्रम data alloc on list rules */
	u32			field_count;
	अक्षर			*filterkey; /* ties events to rules */
	काष्ठा audit_field	*fields;
	काष्ठा audit_field	*arch_f; /* quick access to arch field */
	काष्ठा audit_field	*inode_f; /* quick access to an inode field */
	काष्ठा audit_watch	*watch;	/* associated watch */
	काष्ठा audit_tree	*tree;	/* associated watched tree */
	काष्ठा audit_fsnotअगरy_mark	*exe;
	काष्ठा list_head	rlist;	/* entry in audit_अणुwatch,treeपूर्ण.rules list */
	काष्ठा list_head	list;	/* क्रम AUDIT_LIST* purposes only */
	u64			prio;
पूर्ण;

/* Flag to indicate legacy AUDIT_LOGINUID unset usage */
#घोषणा AUDIT_LOGINUID_LEGACY		0x1

काष्ठा audit_field अणु
	u32				type;
	जोड़ अणु
		u32			val;
		kuid_t			uid;
		kgid_t			gid;
		काष्ठा अणु
			अक्षर		*lsm_str;
			व्योम		*lsm_rule;
		पूर्ण;
	पूर्ण;
	u32				op;
पूर्ण;

क्रमागत audit_ntp_type अणु
	AUDIT_NTP_OFFSET,
	AUDIT_NTP_FREQ,
	AUDIT_NTP_STATUS,
	AUDIT_NTP_TAI,
	AUDIT_NTP_TICK,
	AUDIT_NTP_ADJUST,

	AUDIT_NTP_NVALS /* count */
पूर्ण;

#अगर_घोषित CONFIG_AUDITSYSCALL
काष्ठा audit_ntp_val अणु
	दीर्घ दीर्घ oldval, newval;
पूर्ण;

काष्ठा audit_ntp_data अणु
	काष्ठा audit_ntp_val vals[AUDIT_NTP_NVALS];
पूर्ण;
#अन्यथा
काष्ठा audit_ntp_data अणुपूर्ण;
#पूर्ण_अगर

क्रमागत audit_nfcfgop अणु
	AUDIT_XT_OP_REGISTER,
	AUDIT_XT_OP_REPLACE,
	AUDIT_XT_OP_UNREGISTER,
	AUDIT_NFT_OP_TABLE_REGISTER,
	AUDIT_NFT_OP_TABLE_UNREGISTER,
	AUDIT_NFT_OP_CHAIN_REGISTER,
	AUDIT_NFT_OP_CHAIN_UNREGISTER,
	AUDIT_NFT_OP_RULE_REGISTER,
	AUDIT_NFT_OP_RULE_UNREGISTER,
	AUDIT_NFT_OP_SET_REGISTER,
	AUDIT_NFT_OP_SET_UNREGISTER,
	AUDIT_NFT_OP_SETELEM_REGISTER,
	AUDIT_NFT_OP_SETELEM_UNREGISTER,
	AUDIT_NFT_OP_GEN_REGISTER,
	AUDIT_NFT_OP_OBJ_REGISTER,
	AUDIT_NFT_OP_OBJ_UNREGISTER,
	AUDIT_NFT_OP_OBJ_RESET,
	AUDIT_NFT_OP_FLOWTABLE_REGISTER,
	AUDIT_NFT_OP_FLOWTABLE_UNREGISTER,
	AUDIT_NFT_OP_INVALID,
पूर्ण;

बाह्य पूर्णांक is_audit_feature_set(पूर्णांक which);

बाह्य पूर्णांक __init audit_रेजिस्टर_class(पूर्णांक class, अचिन्हित *list);
बाह्य पूर्णांक audit_classअगरy_syscall(पूर्णांक abi, अचिन्हित syscall);
बाह्य पूर्णांक audit_classअगरy_arch(पूर्णांक arch);
/* only क्रम compat प्रणाली calls */
बाह्य अचिन्हित compat_ग_लिखो_class[];
बाह्य अचिन्हित compat_पढ़ो_class[];
बाह्य अचिन्हित compat_dir_class[];
बाह्य अचिन्हित compat_chattr_class[];
बाह्य अचिन्हित compat_संकेत_class[];

बाह्य पूर्णांक audit_classअगरy_compat_syscall(पूर्णांक abi, अचिन्हित syscall);

/* audit_names->type values */
#घोषणा	AUDIT_TYPE_UNKNOWN	0	/* we करोn't know yet */
#घोषणा	AUDIT_TYPE_NORMAL	1	/* a "normal" audit record */
#घोषणा	AUDIT_TYPE_PARENT	2	/* a parent audit record */
#घोषणा	AUDIT_TYPE_CHILD_DELETE 3	/* a child being deleted */
#घोषणा	AUDIT_TYPE_CHILD_CREATE 4	/* a child being created */

/* maximized args number that audit_socketcall can process */
#घोषणा AUDITSC_ARGS		6

/* bit values क्रम ->संकेत->audit_tty */
#घोषणा AUDIT_TTY_ENABLE	BIT(0)
#घोषणा AUDIT_TTY_LOG_PASSWD	BIT(1)

काष्ठा filename;

#घोषणा AUDIT_OFF	0
#घोषणा AUDIT_ON	1
#घोषणा AUDIT_LOCKED	2
#अगर_घोषित CONFIG_AUDIT
/* These are defined in audit.c */
				/* Public API */
बाह्य __म_लिखो(4, 5)
व्योम audit_log(काष्ठा audit_context *ctx, gfp_t gfp_mask, पूर्णांक type,
	       स्थिर अक्षर *fmt, ...);

बाह्य काष्ठा audit_buffer *audit_log_start(काष्ठा audit_context *ctx, gfp_t gfp_mask, पूर्णांक type);
बाह्य __म_लिखो(2, 3)
व्योम audit_log_क्रमmat(काष्ठा audit_buffer *ab, स्थिर अक्षर *fmt, ...);
बाह्य व्योम		    audit_log_end(काष्ठा audit_buffer *ab);
बाह्य bool		    audit_string_contains_control(स्थिर अक्षर *string,
							  माप_प्रकार len);
बाह्य व्योम		    audit_log_n_hex(काष्ठा audit_buffer *ab,
					  स्थिर अचिन्हित अक्षर *buf,
					  माप_प्रकार len);
बाह्य व्योम		    audit_log_n_string(काष्ठा audit_buffer *ab,
					       स्थिर अक्षर *buf,
					       माप_प्रकार n);
बाह्य व्योम		    audit_log_n_untrustedstring(काष्ठा audit_buffer *ab,
							स्थिर अक्षर *string,
							माप_प्रकार n);
बाह्य व्योम		    audit_log_untrustedstring(काष्ठा audit_buffer *ab,
						      स्थिर अक्षर *string);
बाह्य व्योम		    audit_log_d_path(काष्ठा audit_buffer *ab,
					     स्थिर अक्षर *prefix,
					     स्थिर काष्ठा path *path);
बाह्य व्योम		    audit_log_key(काष्ठा audit_buffer *ab,
					  अक्षर *key);
बाह्य व्योम		    audit_log_path_denied(पूर्णांक type,
						  स्थिर अक्षर *operation);
बाह्य व्योम		    audit_log_lost(स्थिर अक्षर *message);

बाह्य पूर्णांक audit_log_task_context(काष्ठा audit_buffer *ab);
बाह्य व्योम audit_log_task_info(काष्ठा audit_buffer *ab);

बाह्य पूर्णांक		    audit_update_lsm_rules(व्योम);

				/* Private API (क्रम audit.c only) */
बाह्य पूर्णांक audit_rule_change(पूर्णांक type, पूर्णांक seq, व्योम *data, माप_प्रकार datasz);
बाह्य पूर्णांक audit_list_rules_send(काष्ठा sk_buff *request_skb, पूर्णांक seq);

बाह्य पूर्णांक audit_set_loginuid(kuid_t loginuid);

अटल अंतरभूत kuid_t audit_get_loginuid(काष्ठा task_काष्ठा *tsk)
अणु
	वापस tsk->loginuid;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक audit_get_sessionid(काष्ठा task_काष्ठा *tsk)
अणु
	वापस tsk->sessionid;
पूर्ण

बाह्य u32 audit_enabled;

बाह्य पूर्णांक audit_संकेत_info(पूर्णांक sig, काष्ठा task_काष्ठा *t);

#अन्यथा /* CONFIG_AUDIT */
अटल अंतरभूत __म_लिखो(4, 5)
व्योम audit_log(काष्ठा audit_context *ctx, gfp_t gfp_mask, पूर्णांक type,
	       स्थिर अक्षर *fmt, ...)
अणु पूर्ण
अटल अंतरभूत काष्ठा audit_buffer *audit_log_start(काष्ठा audit_context *ctx,
						   gfp_t gfp_mask, पूर्णांक type)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत __म_लिखो(2, 3)
व्योम audit_log_क्रमmat(काष्ठा audit_buffer *ab, स्थिर अक्षर *fmt, ...)
अणु पूर्ण
अटल अंतरभूत व्योम audit_log_end(काष्ठा audit_buffer *ab)
अणु पूर्ण
अटल अंतरभूत व्योम audit_log_n_hex(काष्ठा audit_buffer *ab,
				   स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु पूर्ण
अटल अंतरभूत व्योम audit_log_n_string(काष्ठा audit_buffer *ab,
				      स्थिर अक्षर *buf, माप_प्रकार n)
अणु पूर्ण
अटल अंतरभूत व्योम  audit_log_n_untrustedstring(काष्ठा audit_buffer *ab,
						स्थिर अक्षर *string, माप_प्रकार n)
अणु पूर्ण
अटल अंतरभूत व्योम audit_log_untrustedstring(काष्ठा audit_buffer *ab,
					     स्थिर अक्षर *string)
अणु पूर्ण
अटल अंतरभूत व्योम audit_log_d_path(काष्ठा audit_buffer *ab,
				    स्थिर अक्षर *prefix,
				    स्थिर काष्ठा path *path)
अणु पूर्ण
अटल अंतरभूत व्योम audit_log_key(काष्ठा audit_buffer *ab, अक्षर *key)
अणु पूर्ण
अटल अंतरभूत व्योम audit_log_path_denied(पूर्णांक type, स्थिर अक्षर *operation)
अणु पूर्ण
अटल अंतरभूत पूर्णांक audit_log_task_context(काष्ठा audit_buffer *ab)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम audit_log_task_info(काष्ठा audit_buffer *ab)
अणु पूर्ण

अटल अंतरभूत kuid_t audit_get_loginuid(काष्ठा task_काष्ठा *tsk)
अणु
	वापस INVALID_UID;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक audit_get_sessionid(काष्ठा task_काष्ठा *tsk)
अणु
	वापस AUDIT_SID_UNSET;
पूर्ण

#घोषणा audit_enabled AUDIT_OFF

अटल अंतरभूत पूर्णांक audit_संकेत_info(पूर्णांक sig, काष्ठा task_काष्ठा *t)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_AUDIT */

#अगर_घोषित CONFIG_AUDIT_COMPAT_GENERIC
#घोषणा audit_is_compat(arch)  (!((arch) & __AUDIT_ARCH_64BIT))
#अन्यथा
#घोषणा audit_is_compat(arch)  false
#पूर्ण_अगर

#घोषणा AUDIT_INODE_PARENT	1	/* dentry represents the parent */
#घोषणा AUDIT_INODE_HIDDEN	2	/* audit record should be hidden */
#घोषणा AUDIT_INODE_NOEVAL	4	/* audit record incomplete */

#अगर_घोषित CONFIG_AUDITSYSCALL
#समावेश <यंत्र/syscall.h> /* क्रम syscall_get_arch() */

/* These are defined in auditsc.c */
				/* Public API */
बाह्य पूर्णांक  audit_alloc(काष्ठा task_काष्ठा *task);
बाह्य व्योम __audit_मुक्त(काष्ठा task_काष्ठा *task);
बाह्य व्योम __audit_syscall_entry(पूर्णांक major, अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
				  अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3);
बाह्य व्योम __audit_syscall_निकास(पूर्णांक ret_success, दीर्घ ret_value);
बाह्य काष्ठा filename *__audit_reusename(स्थिर __user अक्षर *uptr);
बाह्य व्योम __audit_getname(काष्ठा filename *name);
बाह्य व्योम __audit_inode(काष्ठा filename *name, स्थिर काष्ठा dentry *dentry,
				अचिन्हित पूर्णांक flags);
बाह्य व्योम __audit_file(स्थिर काष्ठा file *);
बाह्य व्योम __audit_inode_child(काष्ठा inode *parent,
				स्थिर काष्ठा dentry *dentry,
				स्थिर अचिन्हित अक्षर type);
बाह्य व्योम audit_seccomp(अचिन्हित दीर्घ syscall, दीर्घ signr, पूर्णांक code);
बाह्य व्योम audit_seccomp_actions_logged(स्थिर अक्षर *names,
					 स्थिर अक्षर *old_names, पूर्णांक res);
बाह्य व्योम __audit_ptrace(काष्ठा task_काष्ठा *t);

अटल अंतरभूत व्योम audit_set_context(काष्ठा task_काष्ठा *task, काष्ठा audit_context *ctx)
अणु
	task->audit_context = ctx;
पूर्ण

अटल अंतरभूत काष्ठा audit_context *audit_context(व्योम)
अणु
	वापस current->audit_context;
पूर्ण

अटल अंतरभूत bool audit_dummy_context(व्योम)
अणु
	व्योम *p = audit_context();
	वापस !p || *(पूर्णांक *)p;
पूर्ण
अटल अंतरभूत व्योम audit_मुक्त(काष्ठा task_काष्ठा *task)
अणु
	अगर (unlikely(task->audit_context))
		__audit_मुक्त(task);
पूर्ण
अटल अंतरभूत व्योम audit_syscall_entry(पूर्णांक major, अचिन्हित दीर्घ a0,
				       अचिन्हित दीर्घ a1, अचिन्हित दीर्घ a2,
				       अचिन्हित दीर्घ a3)
अणु
	अगर (unlikely(audit_context()))
		__audit_syscall_entry(major, a0, a1, a2, a3);
पूर्ण
अटल अंतरभूत व्योम audit_syscall_निकास(व्योम *pt_regs)
अणु
	अगर (unlikely(audit_context())) अणु
		पूर्णांक success = is_syscall_success(pt_regs);
		दीर्घ वापस_code = regs_वापस_value(pt_regs);

		__audit_syscall_निकास(success, वापस_code);
	पूर्ण
पूर्ण
अटल अंतरभूत काष्ठा filename *audit_reusename(स्थिर __user अक्षर *name)
अणु
	अगर (unlikely(!audit_dummy_context()))
		वापस __audit_reusename(name);
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम audit_getname(काष्ठा filename *name)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_getname(name);
पूर्ण
अटल अंतरभूत व्योम audit_inode(काष्ठा filename *name,
				स्थिर काष्ठा dentry *dentry,
				अचिन्हित पूर्णांक aflags) अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_inode(name, dentry, aflags);
पूर्ण
अटल अंतरभूत व्योम audit_file(काष्ठा file *file)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_file(file);
पूर्ण
अटल अंतरभूत व्योम audit_inode_parent_hidden(काष्ठा filename *name,
						स्थिर काष्ठा dentry *dentry)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_inode(name, dentry,
				AUDIT_INODE_PARENT | AUDIT_INODE_HIDDEN);
पूर्ण
अटल अंतरभूत व्योम audit_inode_child(काष्ठा inode *parent,
				     स्थिर काष्ठा dentry *dentry,
				     स्थिर अचिन्हित अक्षर type) अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_inode_child(parent, dentry, type);
पूर्ण
व्योम audit_core_dumps(दीर्घ signr);

अटल अंतरभूत व्योम audit_ptrace(काष्ठा task_काष्ठा *t)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_ptrace(t);
पूर्ण

				/* Private API (क्रम audit.c only) */
बाह्य व्योम __audit_ipc_obj(काष्ठा kern_ipc_perm *ipcp);
बाह्य व्योम __audit_ipc_set_perm(अचिन्हित दीर्घ qbytes, uid_t uid, gid_t gid, umode_t mode);
बाह्य व्योम __audit_bprm(काष्ठा linux_binprm *bprm);
बाह्य पूर्णांक __audit_socketcall(पूर्णांक nargs, अचिन्हित दीर्घ *args);
बाह्य पूर्णांक __audit_sockaddr(पूर्णांक len, व्योम *addr);
बाह्य व्योम __audit_fd_pair(पूर्णांक fd1, पूर्णांक fd2);
बाह्य व्योम __audit_mq_खोलो(पूर्णांक oflag, umode_t mode, काष्ठा mq_attr *attr);
बाह्य व्योम __audit_mq_sendrecv(mqd_t mqdes, माप_प्रकार msg_len, अचिन्हित पूर्णांक msg_prio, स्थिर काष्ठा बारpec64 *असल_समयout);
बाह्य व्योम __audit_mq_notअगरy(mqd_t mqdes, स्थिर काष्ठा sigevent *notअगरication);
बाह्य व्योम __audit_mq_माला_लोetattr(mqd_t mqdes, काष्ठा mq_attr *mqstat);
बाह्य पूर्णांक __audit_log_bprm_fcaps(काष्ठा linux_binprm *bprm,
				  स्थिर काष्ठा cred *new,
				  स्थिर काष्ठा cred *old);
बाह्य व्योम __audit_log_capset(स्थिर काष्ठा cred *new, स्थिर काष्ठा cred *old);
बाह्य व्योम __audit_mmap_fd(पूर्णांक fd, पूर्णांक flags);
बाह्य व्योम __audit_log_kern_module(अक्षर *name);
बाह्य व्योम __audit_fanotअगरy(अचिन्हित पूर्णांक response);
बाह्य व्योम __audit_tk_injoffset(काष्ठा बारpec64 offset);
बाह्य व्योम __audit_ntp_log(स्थिर काष्ठा audit_ntp_data *ad);
बाह्य व्योम __audit_log_nfcfg(स्थिर अक्षर *name, u8 af, अचिन्हित पूर्णांक nentries,
			      क्रमागत audit_nfcfgop op, gfp_t gfp);

अटल अंतरभूत व्योम audit_ipc_obj(काष्ठा kern_ipc_perm *ipcp)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_ipc_obj(ipcp);
पूर्ण
अटल अंतरभूत व्योम audit_fd_pair(पूर्णांक fd1, पूर्णांक fd2)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_fd_pair(fd1, fd2);
पूर्ण
अटल अंतरभूत व्योम audit_ipc_set_perm(अचिन्हित दीर्घ qbytes, uid_t uid, gid_t gid, umode_t mode)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_ipc_set_perm(qbytes, uid, gid, mode);
पूर्ण
अटल अंतरभूत व्योम audit_bprm(काष्ठा linux_binprm *bprm)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_bprm(bprm);
पूर्ण
अटल अंतरभूत पूर्णांक audit_socketcall(पूर्णांक nargs, अचिन्हित दीर्घ *args)
अणु
	अगर (unlikely(!audit_dummy_context()))
		वापस __audit_socketcall(nargs, args);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक audit_socketcall_compat(पूर्णांक nargs, u32 *args)
अणु
	अचिन्हित दीर्घ a[AUDITSC_ARGS];
	पूर्णांक i;

	अगर (audit_dummy_context())
		वापस 0;

	क्रम (i = 0; i < nargs; i++)
		a[i] = (अचिन्हित दीर्घ)args[i];
	वापस __audit_socketcall(nargs, a);
पूर्ण

अटल अंतरभूत पूर्णांक audit_sockaddr(पूर्णांक len, व्योम *addr)
अणु
	अगर (unlikely(!audit_dummy_context()))
		वापस __audit_sockaddr(len, addr);
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम audit_mq_खोलो(पूर्णांक oflag, umode_t mode, काष्ठा mq_attr *attr)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_mq_खोलो(oflag, mode, attr);
पूर्ण
अटल अंतरभूत व्योम audit_mq_sendrecv(mqd_t mqdes, माप_प्रकार msg_len, अचिन्हित पूर्णांक msg_prio, स्थिर काष्ठा बारpec64 *असल_समयout)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_mq_sendrecv(mqdes, msg_len, msg_prio, असल_समयout);
पूर्ण
अटल अंतरभूत व्योम audit_mq_notअगरy(mqd_t mqdes, स्थिर काष्ठा sigevent *notअगरication)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_mq_notअगरy(mqdes, notअगरication);
पूर्ण
अटल अंतरभूत व्योम audit_mq_माला_लोetattr(mqd_t mqdes, काष्ठा mq_attr *mqstat)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_mq_माला_लोetattr(mqdes, mqstat);
पूर्ण

अटल अंतरभूत पूर्णांक audit_log_bprm_fcaps(काष्ठा linux_binprm *bprm,
				       स्थिर काष्ठा cred *new,
				       स्थिर काष्ठा cred *old)
अणु
	अगर (unlikely(!audit_dummy_context()))
		वापस __audit_log_bprm_fcaps(bprm, new, old);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम audit_log_capset(स्थिर काष्ठा cred *new,
				   स्थिर काष्ठा cred *old)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_log_capset(new, old);
पूर्ण

अटल अंतरभूत व्योम audit_mmap_fd(पूर्णांक fd, पूर्णांक flags)
अणु
	अगर (unlikely(!audit_dummy_context()))
		__audit_mmap_fd(fd, flags);
पूर्ण

अटल अंतरभूत व्योम audit_log_kern_module(अक्षर *name)
अणु
	अगर (!audit_dummy_context())
		__audit_log_kern_module(name);
पूर्ण

अटल अंतरभूत व्योम audit_fanotअगरy(अचिन्हित पूर्णांक response)
अणु
	अगर (!audit_dummy_context())
		__audit_fanotअगरy(response);
पूर्ण

अटल अंतरभूत व्योम audit_tk_injoffset(काष्ठा बारpec64 offset)
अणु
	/* ignore no-op events */
	अगर (offset.tv_sec == 0 && offset.tv_nsec == 0)
		वापस;

	अगर (!audit_dummy_context())
		__audit_tk_injoffset(offset);
पूर्ण

अटल अंतरभूत व्योम audit_ntp_init(काष्ठा audit_ntp_data *ad)
अणु
	स_रखो(ad, 0, माप(*ad));
पूर्ण

अटल अंतरभूत व्योम audit_ntp_set_old(काष्ठा audit_ntp_data *ad,
				     क्रमागत audit_ntp_type type, दीर्घ दीर्घ val)
अणु
	ad->vals[type].oldval = val;
पूर्ण

अटल अंतरभूत व्योम audit_ntp_set_new(काष्ठा audit_ntp_data *ad,
				     क्रमागत audit_ntp_type type, दीर्घ दीर्घ val)
अणु
	ad->vals[type].newval = val;
पूर्ण

अटल अंतरभूत व्योम audit_ntp_log(स्थिर काष्ठा audit_ntp_data *ad)
अणु
	अगर (!audit_dummy_context())
		__audit_ntp_log(ad);
पूर्ण

अटल अंतरभूत व्योम audit_log_nfcfg(स्थिर अक्षर *name, u8 af,
				   अचिन्हित पूर्णांक nentries,
				   क्रमागत audit_nfcfgop op, gfp_t gfp)
अणु
	अगर (audit_enabled)
		__audit_log_nfcfg(name, af, nentries, op, gfp);
पूर्ण

बाह्य पूर्णांक audit_n_rules;
बाह्य पूर्णांक audit_संकेतs;
#अन्यथा /* CONFIG_AUDITSYSCALL */
अटल अंतरभूत पूर्णांक audit_alloc(काष्ठा task_काष्ठा *task)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम audit_मुक्त(काष्ठा task_काष्ठा *task)
अणु पूर्ण
अटल अंतरभूत व्योम audit_syscall_entry(पूर्णांक major, अचिन्हित दीर्घ a0,
				       अचिन्हित दीर्घ a1, अचिन्हित दीर्घ a2,
				       अचिन्हित दीर्घ a3)
अणु पूर्ण
अटल अंतरभूत व्योम audit_syscall_निकास(व्योम *pt_regs)
अणु पूर्ण
अटल अंतरभूत bool audit_dummy_context(व्योम)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत व्योम audit_set_context(काष्ठा task_काष्ठा *task, काष्ठा audit_context *ctx)
अणु पूर्ण
अटल अंतरभूत काष्ठा audit_context *audit_context(व्योम)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा filename *audit_reusename(स्थिर __user अक्षर *name)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम audit_getname(काष्ठा filename *name)
अणु पूर्ण
अटल अंतरभूत व्योम audit_inode(काष्ठा filename *name,
				स्थिर काष्ठा dentry *dentry,
				अचिन्हित पूर्णांक aflags)
अणु पूर्ण
अटल अंतरभूत व्योम audit_file(काष्ठा file *file)
अणु
पूर्ण
अटल अंतरभूत व्योम audit_inode_parent_hidden(काष्ठा filename *name,
				स्थिर काष्ठा dentry *dentry)
अणु पूर्ण
अटल अंतरभूत व्योम audit_inode_child(काष्ठा inode *parent,
				     स्थिर काष्ठा dentry *dentry,
				     स्थिर अचिन्हित अक्षर type)
अणु पूर्ण
अटल अंतरभूत व्योम audit_core_dumps(दीर्घ signr)
अणु पूर्ण
अटल अंतरभूत व्योम audit_seccomp(अचिन्हित दीर्घ syscall, दीर्घ signr, पूर्णांक code)
अणु पूर्ण
अटल अंतरभूत व्योम audit_seccomp_actions_logged(स्थिर अक्षर *names,
						स्थिर अक्षर *old_names, पूर्णांक res)
अणु पूर्ण
अटल अंतरभूत व्योम audit_ipc_obj(काष्ठा kern_ipc_perm *ipcp)
अणु पूर्ण
अटल अंतरभूत व्योम audit_ipc_set_perm(अचिन्हित दीर्घ qbytes, uid_t uid,
					gid_t gid, umode_t mode)
अणु पूर्ण
अटल अंतरभूत व्योम audit_bprm(काष्ठा linux_binprm *bprm)
अणु पूर्ण
अटल अंतरभूत पूर्णांक audit_socketcall(पूर्णांक nargs, अचिन्हित दीर्घ *args)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक audit_socketcall_compat(पूर्णांक nargs, u32 *args)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम audit_fd_pair(पूर्णांक fd1, पूर्णांक fd2)
अणु पूर्ण
अटल अंतरभूत पूर्णांक audit_sockaddr(पूर्णांक len, व्योम *addr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम audit_mq_खोलो(पूर्णांक oflag, umode_t mode, काष्ठा mq_attr *attr)
अणु पूर्ण
अटल अंतरभूत व्योम audit_mq_sendrecv(mqd_t mqdes, माप_प्रकार msg_len,
				     अचिन्हित पूर्णांक msg_prio,
				     स्थिर काष्ठा बारpec64 *असल_समयout)
अणु पूर्ण
अटल अंतरभूत व्योम audit_mq_notअगरy(mqd_t mqdes,
				   स्थिर काष्ठा sigevent *notअगरication)
अणु पूर्ण
अटल अंतरभूत व्योम audit_mq_माला_लोetattr(mqd_t mqdes, काष्ठा mq_attr *mqstat)
अणु पूर्ण
अटल अंतरभूत पूर्णांक audit_log_bprm_fcaps(काष्ठा linux_binprm *bprm,
				       स्थिर काष्ठा cred *new,
				       स्थिर काष्ठा cred *old)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम audit_log_capset(स्थिर काष्ठा cred *new,
				    स्थिर काष्ठा cred *old)
अणु पूर्ण
अटल अंतरभूत व्योम audit_mmap_fd(पूर्णांक fd, पूर्णांक flags)
अणु पूर्ण

अटल अंतरभूत व्योम audit_log_kern_module(अक्षर *name)
अणु
पूर्ण

अटल अंतरभूत व्योम audit_fanotअगरy(अचिन्हित पूर्णांक response)
अणु पूर्ण

अटल अंतरभूत व्योम audit_tk_injoffset(काष्ठा बारpec64 offset)
अणु पूर्ण

अटल अंतरभूत व्योम audit_ntp_init(काष्ठा audit_ntp_data *ad)
अणु पूर्ण

अटल अंतरभूत व्योम audit_ntp_set_old(काष्ठा audit_ntp_data *ad,
				     क्रमागत audit_ntp_type type, दीर्घ दीर्घ val)
अणु पूर्ण

अटल अंतरभूत व्योम audit_ntp_set_new(काष्ठा audit_ntp_data *ad,
				     क्रमागत audit_ntp_type type, दीर्घ दीर्घ val)
अणु पूर्ण

अटल अंतरभूत व्योम audit_ntp_log(स्थिर काष्ठा audit_ntp_data *ad)
अणु पूर्ण

अटल अंतरभूत व्योम audit_ptrace(काष्ठा task_काष्ठा *t)
अणु पूर्ण

अटल अंतरभूत व्योम audit_log_nfcfg(स्थिर अक्षर *name, u8 af,
				   अचिन्हित पूर्णांक nentries,
				   क्रमागत audit_nfcfgop op, gfp_t gfp)
अणु पूर्ण

#घोषणा audit_n_rules 0
#घोषणा audit_संकेतs 0
#पूर्ण_अगर /* CONFIG_AUDITSYSCALL */

अटल अंतरभूत bool audit_loginuid_set(काष्ठा task_काष्ठा *tsk)
अणु
	वापस uid_valid(audit_get_loginuid(tsk));
पूर्ण

#पूर्ण_अगर
