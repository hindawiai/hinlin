<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* audit -- definition of audit_context काष्ठाure and supporting types 
 *
 * Copyright 2003-2004 Red Hat, Inc.
 * Copyright 2005 Hewlett-Packard Development Company, L.P.
 * Copyright 2005 IBM Corporation
 */

#समावेश <linux/fs.h>
#समावेश <linux/audit.h>
#समावेश <linux/skbuff.h>
#समावेश <uapi/linux/mqueue.h>
#समावेश <linux/tty.h>

/* AUDIT_NAMES is the number of slots we reserve in the audit_context
 * क्रम saving names from getname().  If we get more names we will allocate
 * a name dynamically and also add those to the list anchored by names_list. */
#घोषणा AUDIT_NAMES	5

/* At task start समय, the audit_state is set in the audit_context using
   a per-task filter.  At syscall entry, the audit_state is augmented by
   the syscall filter. */
क्रमागत audit_state अणु
	AUDIT_DISABLED,		/* Do not create per-task audit_context.
				 * No syscall-specअगरic audit records can
				 * be generated. */
	AUDIT_BUILD_CONTEXT,	/* Create the per-task audit_context,
				 * and fill it in at syscall
				 * entry समय.  This makes a full
				 * syscall record available अगर some
				 * other part of the kernel decides it
				 * should be recorded. */
	AUDIT_RECORD_CONTEXT	/* Create the per-task audit_context,
				 * always fill it in at syscall entry
				 * समय, and always ग_लिखो out the audit
				 * record at syscall निकास समय.  */
पूर्ण;

/* Rule lists */
काष्ठा audit_watch;
काष्ठा audit_fsnotअगरy_mark;
काष्ठा audit_tree;
काष्ठा audit_chunk;

काष्ठा audit_entry अणु
	काष्ठा list_head	list;
	काष्ठा rcu_head		rcu;
	काष्ठा audit_krule	rule;
पूर्ण;

काष्ठा audit_cap_data अणु
	kernel_cap_t		permitted;
	kernel_cap_t		inheritable;
	जोड़ अणु
		अचिन्हित पूर्णांक	fE;		/* effective bit of file cap */
		kernel_cap_t	effective;	/* effective set of process */
	पूर्ण;
	kernel_cap_t		ambient;
	kuid_t			rootid;
पूर्ण;

/* When fs/namei.c:getname() is called, we store the poपूर्णांकer in name and bump
 * the refcnt in the associated filename काष्ठा.
 *
 * Further, in fs/namei.c:path_lookup() we store the inode and device.
 */
काष्ठा audit_names अणु
	काष्ठा list_head	list;		/* audit_context->names_list */

	काष्ठा filename		*name;
	पूर्णांक			name_len;	/* number of अक्षरs to log */
	bool			hidden;		/* करोn't log this record */

	अचिन्हित दीर्घ		ino;
	dev_t			dev;
	umode_t			mode;
	kuid_t			uid;
	kgid_t			gid;
	dev_t			rdev;
	u32			osid;
	काष्ठा audit_cap_data	fcap;
	अचिन्हित पूर्णांक		fcap_ver;
	अचिन्हित अक्षर		type;		/* record type */
	/*
	 * This was an allocated audit_names and not from the array of
	 * names allocated in the task audit context.  Thus this name
	 * should be मुक्तd on syscall निकास.
	 */
	bool			should_मुक्त;
पूर्ण;

काष्ठा audit_proctitle अणु
	पूर्णांक	len;	/* length of the cmdline field. */
	अक्षर	*value;	/* the cmdline field */
पूर्ण;

/* The per-task audit context. */
काष्ठा audit_context अणु
	पूर्णांक		    dummy;	/* must be the first element */
	पूर्णांक		    in_syscall;	/* 1 अगर task is in a syscall */
	क्रमागत audit_state    state, current_state;
	अचिन्हित पूर्णांक	    serial;     /* serial number क्रम record */
	पूर्णांक		    major;      /* syscall number */
	काष्ठा बारpec64   स_समय;      /* समय of syscall entry */
	अचिन्हित दीर्घ	    argv[4];    /* syscall arguments */
	दीर्घ		    वापस_code;/* syscall वापस code */
	u64		    prio;
	पूर्णांक		    वापस_valid; /* वापस code is valid */
	/*
	 * The names_list is the list of all audit_names collected during this
	 * syscall.  The first AUDIT_NAMES entries in the names_list will
	 * actually be from the pपुनः_स्मृतिated_names array क्रम perक्रमmance
	 * reasons.  Except during allocation they should never be referenced
	 * through the pपुनः_स्मृतिated_names array and should only be found/used
	 * by running the names_list.
	 */
	काष्ठा audit_names  pपुनः_स्मृतिated_names[AUDIT_NAMES];
	पूर्णांक		    name_count; /* total records in names_list */
	काष्ठा list_head    names_list;	/* काष्ठा audit_names->list anchor */
	अक्षर		    *filterkey;	/* key क्रम rule that triggered record */
	काष्ठा path	    pwd;
	काष्ठा audit_aux_data *aux;
	काष्ठा audit_aux_data *aux_pids;
	काष्ठा sockaddr_storage *sockaddr;
	माप_प्रकार sockaddr_len;
				/* Save things to prपूर्णांक about task_काष्ठा */
	pid_t		    pid, ppid;
	kuid_t		    uid, euid, suid, fsuid;
	kgid_t		    gid, egid, sgid, fsgid;
	अचिन्हित दीर्घ	    personality;
	पूर्णांक		    arch;

	pid_t		    target_pid;
	kuid_t		    target_auid;
	kuid_t		    target_uid;
	अचिन्हित पूर्णांक	    target_sessionid;
	u32		    target_sid;
	अक्षर		    target_comm[TASK_COMM_LEN];

	काष्ठा audit_tree_refs *trees, *first_trees;
	काष्ठा list_head समाप्तed_trees;
	पूर्णांक tree_count;

	पूर्णांक type;
	जोड़ अणु
		काष्ठा अणु
			पूर्णांक nargs;
			दीर्घ args[6];
		पूर्ण socketcall;
		काष्ठा अणु
			kuid_t			uid;
			kgid_t			gid;
			umode_t			mode;
			u32			osid;
			पूर्णांक			has_perm;
			uid_t			perm_uid;
			gid_t			perm_gid;
			umode_t			perm_mode;
			अचिन्हित दीर्घ		qbytes;
		पूर्ण ipc;
		काष्ठा अणु
			mqd_t			mqdes;
			काष्ठा mq_attr		mqstat;
		पूर्ण mq_माला_लोetattr;
		काष्ठा अणु
			mqd_t			mqdes;
			पूर्णांक			sigev_signo;
		पूर्ण mq_notअगरy;
		काष्ठा अणु
			mqd_t			mqdes;
			माप_प्रकार			msg_len;
			अचिन्हित पूर्णांक		msg_prio;
			काष्ठा बारpec64	असल_समयout;
		पूर्ण mq_sendrecv;
		काष्ठा अणु
			पूर्णांक			oflag;
			umode_t			mode;
			काष्ठा mq_attr		attr;
		पूर्ण mq_खोलो;
		काष्ठा अणु
			pid_t			pid;
			काष्ठा audit_cap_data	cap;
		पूर्ण capset;
		काष्ठा अणु
			पूर्णांक			fd;
			पूर्णांक			flags;
		पूर्ण mmap;
		काष्ठा अणु
			पूर्णांक			argc;
		पूर्ण execve;
		काष्ठा अणु
			अक्षर			*name;
		पूर्ण module;
	पूर्ण;
	पूर्णांक fds[2];
	काष्ठा audit_proctitle proctitle;
पूर्ण;

बाह्य bool audit_ever_enabled;

बाह्य व्योम audit_log_session_info(काष्ठा audit_buffer *ab);

बाह्य पूर्णांक auditd_test_task(काष्ठा task_काष्ठा *task);

#घोषणा AUDIT_INODE_BUCKETS	32
बाह्य काष्ठा list_head audit_inode_hash[AUDIT_INODE_BUCKETS];

अटल अंतरभूत पूर्णांक audit_hash_ino(u32 ino)
अणु
	वापस (ino & (AUDIT_INODE_BUCKETS-1));
पूर्ण

/* Indicates that audit should log the full pathname. */
#घोषणा AUDIT_NAME_FULL -1

बाह्य पूर्णांक audit_match_class(पूर्णांक class, अचिन्हित syscall);
बाह्य पूर्णांक audit_comparator(स्थिर u32 left, स्थिर u32 op, स्थिर u32 right);
बाह्य पूर्णांक audit_uid_comparator(kuid_t left, u32 op, kuid_t right);
बाह्य पूर्णांक audit_gid_comparator(kgid_t left, u32 op, kgid_t right);
बाह्य पूर्णांक parent_len(स्थिर अक्षर *path);
बाह्य पूर्णांक audit_compare_dname_path(स्थिर काष्ठा qstr *dname, स्थिर अक्षर *path, पूर्णांक plen);
बाह्य काष्ठा sk_buff *audit_make_reply(पूर्णांक seq, पूर्णांक type, पूर्णांक करोne, पूर्णांक multi,
					स्थिर व्योम *payload, पूर्णांक size);
बाह्य व्योम		    audit_panic(स्थिर अक्षर *message);

काष्ठा audit_netlink_list अणु
	__u32 portid;
	काष्ठा net *net;
	काष्ठा sk_buff_head q;
पूर्ण;

पूर्णांक audit_send_list_thपढ़ो(व्योम *_dest);

बाह्य पूर्णांक selinux_audit_rule_update(व्योम);

बाह्य काष्ठा mutex audit_filter_mutex;
बाह्य पूर्णांक audit_del_rule(काष्ठा audit_entry *entry);
बाह्य व्योम audit_मुक्त_rule_rcu(काष्ठा rcu_head *head);
बाह्य काष्ठा list_head audit_filter_list[];

बाह्य काष्ठा audit_entry *audit_dupe_rule(काष्ठा audit_krule *old);

बाह्य व्योम audit_log_d_path_exe(काष्ठा audit_buffer *ab,
				 काष्ठा mm_काष्ठा *mm);

बाह्य काष्ठा tty_काष्ठा *audit_get_tty(व्योम);
बाह्य व्योम audit_put_tty(काष्ठा tty_काष्ठा *tty);

/* audit watch/mark/tree functions */
#अगर_घोषित CONFIG_AUDITSYSCALL
बाह्य अचिन्हित पूर्णांक audit_serial(व्योम);
बाह्य पूर्णांक auditsc_get_stamp(काष्ठा audit_context *ctx,
			      काष्ठा बारpec64 *t, अचिन्हित पूर्णांक *serial);

बाह्य व्योम audit_put_watch(काष्ठा audit_watch *watch);
बाह्य व्योम audit_get_watch(काष्ठा audit_watch *watch);
बाह्य पूर्णांक audit_to_watch(काष्ठा audit_krule *krule, अक्षर *path, पूर्णांक len,
			  u32 op);
बाह्य पूर्णांक audit_add_watch(काष्ठा audit_krule *krule, काष्ठा list_head **list);
बाह्य व्योम audit_हटाओ_watch_rule(काष्ठा audit_krule *krule);
बाह्य अक्षर *audit_watch_path(काष्ठा audit_watch *watch);
बाह्य पूर्णांक audit_watch_compare(काष्ठा audit_watch *watch, अचिन्हित दीर्घ ino,
			       dev_t dev);

बाह्य काष्ठा audit_fsnotअगरy_mark *audit_alloc_mark(काष्ठा audit_krule *krule,
						    अक्षर *pathname, पूर्णांक len);
बाह्य अक्षर *audit_mark_path(काष्ठा audit_fsnotअगरy_mark *mark);
बाह्य व्योम audit_हटाओ_mark(काष्ठा audit_fsnotअगरy_mark *audit_mark);
बाह्य व्योम audit_हटाओ_mark_rule(काष्ठा audit_krule *krule);
बाह्य पूर्णांक audit_mark_compare(काष्ठा audit_fsnotअगरy_mark *mark,
			      अचिन्हित दीर्घ ino, dev_t dev);
बाह्य पूर्णांक audit_dupe_exe(काष्ठा audit_krule *new, काष्ठा audit_krule *old);
बाह्य पूर्णांक audit_exe_compare(काष्ठा task_काष्ठा *tsk,
			     काष्ठा audit_fsnotअगरy_mark *mark);

बाह्य काष्ठा audit_chunk *audit_tree_lookup(स्थिर काष्ठा inode *inode);
बाह्य व्योम audit_put_chunk(काष्ठा audit_chunk *chunk);
बाह्य bool audit_tree_match(काष्ठा audit_chunk *chunk,
			     काष्ठा audit_tree *tree);
बाह्य पूर्णांक audit_make_tree(काष्ठा audit_krule *rule, अक्षर *pathname, u32 op);
बाह्य पूर्णांक audit_add_tree_rule(काष्ठा audit_krule *rule);
बाह्य पूर्णांक audit_हटाओ_tree_rule(काष्ठा audit_krule *rule);
बाह्य व्योम audit_trim_trees(व्योम);
बाह्य पूर्णांक audit_tag_tree(अक्षर *old, अक्षर *new);
बाह्य स्थिर अक्षर *audit_tree_path(काष्ठा audit_tree *tree);
बाह्य व्योम audit_put_tree(काष्ठा audit_tree *tree);
बाह्य व्योम audit_समाप्त_trees(काष्ठा audit_context *context);

बाह्य पूर्णांक audit_संकेत_info_syscall(काष्ठा task_काष्ठा *t);
बाह्य व्योम audit_filter_inodes(काष्ठा task_काष्ठा *tsk,
				काष्ठा audit_context *ctx);
बाह्य काष्ठा list_head *audit_समाप्तed_trees(व्योम);
#अन्यथा /* CONFIG_AUDITSYSCALL */
#घोषणा auditsc_get_stamp(c, t, s) 0
#घोषणा audit_put_watch(w) करो अणु पूर्ण जबतक (0)
#घोषणा audit_get_watch(w) करो अणु पूर्ण जबतक (0)
#घोषणा audit_to_watch(k, p, l, o) (-EINVAL)
#घोषणा audit_add_watch(k, l) (-EINVAL)
#घोषणा audit_हटाओ_watch_rule(k) BUG()
#घोषणा audit_watch_path(w) ""
#घोषणा audit_watch_compare(w, i, d) 0

#घोषणा audit_alloc_mark(k, p, l) (ERR_PTR(-EINVAL))
#घोषणा audit_mark_path(m) ""
#घोषणा audit_हटाओ_mark(m) करो अणु पूर्ण जबतक (0)
#घोषणा audit_हटाओ_mark_rule(k) करो अणु पूर्ण जबतक (0)
#घोषणा audit_mark_compare(m, i, d) 0
#घोषणा audit_exe_compare(t, m) (-EINVAL)
#घोषणा audit_dupe_exe(n, o) (-EINVAL)

#घोषणा audit_हटाओ_tree_rule(rule) BUG()
#घोषणा audit_add_tree_rule(rule) -EINVAL
#घोषणा audit_make_tree(rule, str, op) -EINVAL
#घोषणा audit_trim_trees() करो अणु पूर्ण जबतक (0)
#घोषणा audit_put_tree(tree) करो अणु पूर्ण जबतक (0)
#घोषणा audit_tag_tree(old, new) -EINVAL
#घोषणा audit_tree_path(rule) ""	/* never called */
#घोषणा audit_समाप्त_trees(context) BUG()

अटल अंतरभूत पूर्णांक audit_संकेत_info_syscall(काष्ठा task_काष्ठा *t)
अणु
	वापस 0;
पूर्ण

#घोषणा audit_filter_inodes(t, c) AUDIT_DISABLED
#पूर्ण_अगर /* CONFIG_AUDITSYSCALL */

बाह्य अक्षर *audit_unpack_string(व्योम **bufp, माप_प्रकार *reमुख्य, माप_प्रकार len);

बाह्य पूर्णांक audit_filter(पूर्णांक msgtype, अचिन्हित पूर्णांक listtype);

बाह्य व्योम audit_ctl_lock(व्योम);
बाह्य व्योम audit_ctl_unlock(व्योम);
