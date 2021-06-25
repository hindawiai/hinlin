<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/fs/nfs/nfs4_fs.h
 *
 * Copyright (C) 2005 Trond Myklebust
 *
 * NFSv4-specअगरic fileप्रणाली definitions and declarations
 */

#अगर_अघोषित __LINUX_FS_NFS_NFS4_FS_H
#घोषणा __LINUX_FS_NFS_NFS4_FS_H

#अगर defined(CONFIG_NFS_V4_2)
#घोषणा NFS4_MAX_MINOR_VERSION 2
#या_अगर defined(CONFIG_NFS_V4_1)
#घोषणा NFS4_MAX_MINOR_VERSION 1
#अन्यथा
#घोषणा NFS4_MAX_MINOR_VERSION 0
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NFS_V4)

#घोषणा NFS4_MAX_LOOP_ON_RECOVER (10)

#समावेश <linux/seqlock.h>

काष्ठा idmap;

क्रमागत nfs4_client_state अणु
	NFS4CLNT_MANAGER_RUNNING  = 0,
	NFS4CLNT_CHECK_LEASE,
	NFS4CLNT_LEASE_EXPIRED,
	NFS4CLNT_RECLAIM_REBOOT,
	NFS4CLNT_RECLAIM_NOGRACE,
	NFS4CLNT_DELEGRETURN,
	NFS4CLNT_SESSION_RESET,
	NFS4CLNT_LEASE_CONFIRM,
	NFS4CLNT_SERVER_SCOPE_MISMATCH,
	NFS4CLNT_PURGE_STATE,
	NFS4CLNT_BIND_CONN_TO_SESSION,
	NFS4CLNT_MOVED,
	NFS4CLNT_LEASE_MOVED,
	NFS4CLNT_DELEGATION_EXPIRED,
	NFS4CLNT_RUN_MANAGER,
	NFS4CLNT_RECALL_RUNNING,
	NFS4CLNT_RECALL_ANY_LAYOUT_READ,
	NFS4CLNT_RECALL_ANY_LAYOUT_RW,
पूर्ण;

#घोषणा NFS4_RENEW_TIMEOUT		0x01
#घोषणा NFS4_RENEW_DELEGATION_CB	0x02

काष्ठा nfs_seqid_counter;
काष्ठा nfs4_minor_version_ops अणु
	u32	minor_version;
	अचिन्हित init_caps;

	पूर्णांक	(*init_client)(काष्ठा nfs_client *);
	व्योम	(*shutकरोwn_client)(काष्ठा nfs_client *);
	bool	(*match_stateid)(स्थिर nfs4_stateid *,
			स्थिर nfs4_stateid *);
	पूर्णांक	(*find_root_sec)(काष्ठा nfs_server *, काष्ठा nfs_fh *,
			काष्ठा nfs_fsinfo *);
	व्योम	(*मुक्त_lock_state)(काष्ठा nfs_server *,
			काष्ठा nfs4_lock_state *);
	पूर्णांक	(*test_and_मुक्त_expired)(काष्ठा nfs_server *,
			nfs4_stateid *, स्थिर काष्ठा cred *);
	काष्ठा nfs_seqid *
		(*alloc_seqid)(काष्ठा nfs_seqid_counter *, gfp_t);
	व्योम	(*session_trunk)(काष्ठा rpc_clnt *clnt,
			काष्ठा rpc_xprt *xprt, व्योम *data);
	स्थिर काष्ठा rpc_call_ops *call_sync_ops;
	स्थिर काष्ठा nfs4_state_recovery_ops *reboot_recovery_ops;
	स्थिर काष्ठा nfs4_state_recovery_ops *nograce_recovery_ops;
	स्थिर काष्ठा nfs4_state_मुख्यtenance_ops *state_renewal_ops;
	स्थिर काष्ठा nfs4_mig_recovery_ops *mig_recovery_ops;
पूर्ण;

#घोषणा NFS_SEQID_CONFIRMED 1
काष्ठा nfs_seqid_counter अणु
	kसमय_प्रकार create_समय;
	पूर्णांक owner_id;
	पूर्णांक flags;
	u32 counter;
	spinlock_t lock;		/* Protects the list */
	काष्ठा list_head list;		/* Defines sequence of RPC calls */
	काष्ठा rpc_रुको_queue	रुको;	/* RPC call delay queue */
पूर्ण;

काष्ठा nfs_seqid अणु
	काष्ठा nfs_seqid_counter *sequence;
	काष्ठा list_head list;
	काष्ठा rpc_task *task;
पूर्ण;

अटल अंतरभूत व्योम nfs_confirm_seqid(काष्ठा nfs_seqid_counter *seqid, पूर्णांक status)
अणु
	अगर (seqid_mutating_err(-status))
		seqid->flags |= NFS_SEQID_CONFIRMED;
पूर्ण

/*
 * NFS4 state_owners and lock_owners are simply labels क्रम ordered
 * sequences of RPC calls. Their sole purpose is to provide once-only
 * semantics by allowing the server to identअगरy replayed requests.
 */
काष्ठा nfs4_state_owner अणु
	काष्ठा nfs_server    *so_server;
	काष्ठा list_head     so_lru;
	अचिन्हित दीर्घ        so_expires;
	काष्ठा rb_node	     so_server_node;

	स्थिर काष्ठा cred    *so_cred;	 /* Associated cred */

	spinlock_t	     so_lock;
	atomic_t	     so_count;
	अचिन्हित दीर्घ	     so_flags;
	काष्ठा list_head     so_states;
	काष्ठा nfs_seqid_counter so_seqid;
	seqcount_spinlock_t  so_reclaim_seqcount;
	काष्ठा mutex	     so_delegवापस_mutex;
पूर्ण;

क्रमागत अणु
	NFS_OWNER_RECLAIM_REBOOT,
	NFS_OWNER_RECLAIM_NOGRACE
पूर्ण;

#घोषणा NFS_LOCK_NEW		0
#घोषणा NFS_LOCK_RECLAIM	1
#घोषणा NFS_LOCK_EXPIRED	2

/*
 * काष्ठा nfs4_state मुख्यtains the client-side state क्रम a given
 * (state_owner,inode) tuple (OPEN) or state_owner (LOCK).
 *
 * OPEN:
 * In order to know when to OPEN_DOWNGRADE or CLOSE the state on the server,
 * we need to know how many files are खोलो क्रम पढ़ोing or writing on a
 * given inode. This inक्रमmation too is stored here.
 *
 * LOCK: one nfs4_state (LOCK) to hold the lock stateid nfs4_state(OPEN)
 */

काष्ठा nfs4_lock_state अणु
	काष्ठा list_head	ls_locks;	/* Other lock stateids */
	काष्ठा nfs4_state *	ls_state;	/* Poपूर्णांकer to खोलो state */
#घोषणा NFS_LOCK_INITIALIZED 0
#घोषणा NFS_LOCK_LOST        1
	अचिन्हित दीर्घ		ls_flags;
	काष्ठा nfs_seqid_counter	ls_seqid;
	nfs4_stateid		ls_stateid;
	refcount_t		ls_count;
	fl_owner_t		ls_owner;
पूर्ण;

/* bits क्रम nfs4_state->flags */
क्रमागत अणु
	LK_STATE_IN_USE,
	NFS_DELEGATED_STATE,		/* Current stateid is delegation */
	NFS_OPEN_STATE,			/* OPEN stateid is set */
	NFS_O_RDONLY_STATE,		/* OPEN stateid has पढ़ो-only state */
	NFS_O_WRONLY_STATE,		/* OPEN stateid has ग_लिखो-only state */
	NFS_O_RDWR_STATE,		/* OPEN stateid has पढ़ो/ग_लिखो state */
	NFS_STATE_RECLAIM_REBOOT,	/* OPEN stateid server rebooted */
	NFS_STATE_RECLAIM_NOGRACE,	/* OPEN stateid needs to recover state */
	NFS_STATE_POSIX_LOCKS,		/* Posix locks are supported */
	NFS_STATE_RECOVERY_FAILED,	/* OPEN stateid state recovery failed */
	NFS_STATE_MAY_NOTIFY_LOCK,	/* server may CB_NOTIFY_LOCK */
	NFS_STATE_CHANGE_WAIT,		/* A state changing operation is outstanding */
	NFS_CLNT_DST_SSC_COPY_STATE,    /* dst server खोलो state on client*/
	NFS_CLNT_SRC_SSC_COPY_STATE,    /* src server खोलो state on client*/
	NFS_SRV_SSC_COPY_STATE,		/* ssc state on the dst server */
पूर्ण;

काष्ठा nfs4_state अणु
	काष्ठा list_head खोलो_states;	/* List of states क्रम the same state_owner */
	काष्ठा list_head inode_states;	/* List of states क्रम the same inode */
	काष्ठा list_head lock_states;	/* List of subservient lock stateids */

	काष्ठा nfs4_state_owner *owner;	/* Poपूर्णांकer to the खोलो owner */
	काष्ठा inode *inode;		/* Poपूर्णांकer to the inode */

	अचिन्हित दीर्घ flags;		/* Do we hold any locks? */
	spinlock_t state_lock;		/* Protects the lock_states list */

	seqlock_t seqlock;		/* Protects the stateid/खोलो_stateid */
	nfs4_stateid stateid;		/* Current stateid: may be delegation */
	nfs4_stateid खोलो_stateid;	/* OPEN stateid */

	/* The following 3 fields are रक्षित by owner->so_lock */
	अचिन्हित पूर्णांक n_rकरोnly;		/* Number of पढ़ो-only references */
	अचिन्हित पूर्णांक n_wronly;		/* Number of ग_लिखो-only references */
	अचिन्हित पूर्णांक n_rdwr;		/* Number of पढ़ो/ग_लिखो references */
	भ_शेषe_t state;			/* State on the server (R,W, or RW) */
	refcount_t count;

	रुको_queue_head_t रुकोq;
	काष्ठा rcu_head rcu_head;
पूर्ण;


काष्ठा nfs4_exception अणु
	काष्ठा nfs4_state *state;
	काष्ठा inode *inode;
	nfs4_stateid *stateid;
	दीर्घ समयout;
	अचिन्हित अक्षर task_is_privileged : 1;
	अचिन्हित अक्षर delay : 1,
		      recovering : 1,
		      retry : 1;
	bool पूर्णांकerruptible;
पूर्ण;

काष्ठा nfs4_state_recovery_ops अणु
	पूर्णांक owner_flag_bit;
	पूर्णांक state_flag_bit;
	पूर्णांक (*recover_खोलो)(काष्ठा nfs4_state_owner *, काष्ठा nfs4_state *);
	पूर्णांक (*recover_lock)(काष्ठा nfs4_state *, काष्ठा file_lock *);
	पूर्णांक (*establish_clid)(काष्ठा nfs_client *, स्थिर काष्ठा cred *);
	पूर्णांक (*reclaim_complete)(काष्ठा nfs_client *, स्थिर काष्ठा cred *);
	पूर्णांक (*detect_trunking)(काष्ठा nfs_client *, काष्ठा nfs_client **,
		स्थिर काष्ठा cred *);
पूर्ण;

काष्ठा nfs4_खोलोdata अणु
	काष्ठा kref kref;
	काष्ठा nfs_खोलोargs o_arg;
	काष्ठा nfs_खोलोres o_res;
	काष्ठा nfs_खोलो_confirmargs c_arg;
	काष्ठा nfs_खोलो_confirmres c_res;
	काष्ठा nfs4_string owner_name;
	काष्ठा nfs4_string group_name;
	काष्ठा nfs4_label *a_label;
	काष्ठा nfs_fattr f_attr;
	काष्ठा nfs4_label *f_label;
	काष्ठा dentry *dir;
	काष्ठा dentry *dentry;
	काष्ठा nfs4_state_owner *owner;
	काष्ठा nfs4_state *state;
	काष्ठा iattr attrs;
	काष्ठा nfs4_layoutget *lgp;
	अचिन्हित दीर्घ बारtamp;
	bool rpc_करोne;
	bool file_created;
	bool is_recover;
	bool cancelled;
	पूर्णांक rpc_status;
पूर्ण;

काष्ठा nfs4_add_xprt_data अणु
	काष्ठा nfs_client	*clp;
	स्थिर काष्ठा cred	*cred;
पूर्ण;

काष्ठा nfs4_state_मुख्यtenance_ops अणु
	पूर्णांक (*sched_state_renewal)(काष्ठा nfs_client *, स्थिर काष्ठा cred *, अचिन्हित);
	स्थिर काष्ठा cred * (*get_state_renewal_cred)(काष्ठा nfs_client *);
	पूर्णांक (*renew_lease)(काष्ठा nfs_client *, स्थिर काष्ठा cred *);
पूर्ण;

काष्ठा nfs4_mig_recovery_ops अणु
	पूर्णांक (*get_locations)(काष्ठा inode *, काष्ठा nfs4_fs_locations *,
		काष्ठा page *, स्थिर काष्ठा cred *);
	पूर्णांक (*fsid_present)(काष्ठा inode *, स्थिर काष्ठा cred *);
पूर्ण;

बाह्य स्थिर काष्ठा dentry_operations nfs4_dentry_operations;

/* dir.c */
पूर्णांक nfs_atomic_खोलो(काष्ठा inode *, काष्ठा dentry *, काष्ठा file *,
		    अचिन्हित, umode_t);

/* fs_context.c */
बाह्य काष्ठा file_प्रणाली_type nfs4_fs_type;

/* nfs4namespace.c */
काष्ठा rpc_clnt *nfs4_negotiate_security(काष्ठा rpc_clnt *, काष्ठा inode *,
					 स्थिर काष्ठा qstr *);
पूर्णांक nfs4_submount(काष्ठा fs_context *, काष्ठा nfs_server *);
पूर्णांक nfs4_replace_transport(काष्ठा nfs_server *server,
				स्थिर काष्ठा nfs4_fs_locations *locations);

/* nfs4proc.c */
बाह्य पूर्णांक nfs4_handle_exception(काष्ठा nfs_server *, पूर्णांक, काष्ठा nfs4_exception *);
बाह्य पूर्णांक nfs4_async_handle_error(काष्ठा rpc_task *task,
				   काष्ठा nfs_server *server,
				   काष्ठा nfs4_state *state, दीर्घ *समयout);
बाह्य पूर्णांक nfs4_call_sync(काष्ठा rpc_clnt *, काष्ठा nfs_server *,
			  काष्ठा rpc_message *, काष्ठा nfs4_sequence_args *,
			  काष्ठा nfs4_sequence_res *, पूर्णांक);
बाह्य व्योम nfs4_init_sequence(काष्ठा nfs4_sequence_args *, काष्ठा nfs4_sequence_res *, पूर्णांक, पूर्णांक);
बाह्य पूर्णांक nfs4_proc_setclientid(काष्ठा nfs_client *, u32, अचिन्हित लघु, स्थिर काष्ठा cred *, काष्ठा nfs4_setclientid_res *);
बाह्य पूर्णांक nfs4_proc_setclientid_confirm(काष्ठा nfs_client *, काष्ठा nfs4_setclientid_res *arg, स्थिर काष्ठा cred *);
बाह्य पूर्णांक nfs4_proc_get_rootfh(काष्ठा nfs_server *, काष्ठा nfs_fh *, काष्ठा nfs_fsinfo *, bool);
बाह्य पूर्णांक nfs4_proc_bind_conn_to_session(काष्ठा nfs_client *, स्थिर काष्ठा cred *cred);
बाह्य पूर्णांक nfs4_proc_exchange_id(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred);
बाह्य पूर्णांक nfs4_destroy_clientid(काष्ठा nfs_client *clp);
बाह्य पूर्णांक nfs4_init_clientid(काष्ठा nfs_client *, स्थिर काष्ठा cred *);
बाह्य पूर्णांक nfs41_init_clientid(काष्ठा nfs_client *, स्थिर काष्ठा cred *);
बाह्य पूर्णांक nfs4_करो_बंद(काष्ठा nfs4_state *state, gfp_t gfp_mask, पूर्णांक रुको);
बाह्य पूर्णांक nfs4_server_capabilities(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle);
बाह्य पूर्णांक nfs4_proc_fs_locations(काष्ठा rpc_clnt *, काष्ठा inode *, स्थिर काष्ठा qstr *,
				  काष्ठा nfs4_fs_locations *, काष्ठा page *);
बाह्य पूर्णांक nfs4_proc_get_locations(काष्ठा inode *, काष्ठा nfs4_fs_locations *,
		काष्ठा page *page, स्थिर काष्ठा cred *);
बाह्य पूर्णांक nfs4_proc_fsid_present(काष्ठा inode *, स्थिर काष्ठा cred *);
बाह्य काष्ठा rpc_clnt *nfs4_proc_lookup_mountpoपूर्णांक(काष्ठा inode *,
						    काष्ठा dentry *,
						    काष्ठा nfs_fh *,
						    काष्ठा nfs_fattr *);
बाह्य पूर्णांक nfs4_proc_secinfo(काष्ठा inode *, स्थिर काष्ठा qstr *, काष्ठा nfs4_secinfo_flavors *);
बाह्य स्थिर काष्ठा xattr_handler *nfs4_xattr_handlers[];
बाह्य पूर्णांक nfs4_set_rw_stateid(nfs4_stateid *stateid,
		स्थिर काष्ठा nfs_खोलो_context *ctx,
		स्थिर काष्ठा nfs_lock_context *l_ctx,
		भ_शेषe_t भ_शेषe);
बाह्य पूर्णांक nfs4_proc_getattr(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
			     काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label,
			     काष्ठा inode *inode);
बाह्य पूर्णांक update_खोलो_stateid(काष्ठा nfs4_state *state,
				स्थिर nfs4_stateid *खोलो_stateid,
				स्थिर nfs4_stateid *deleg_stateid,
				भ_शेषe_t भ_शेषe);

बाह्य पूर्णांक nfs4_proc_get_lease_समय(काष्ठा nfs_client *clp,
		काष्ठा nfs_fsinfo *fsinfo);
बाह्य व्योम nfs4_update_changeattr(काष्ठा inode *dir,
				   काष्ठा nfs4_change_info *cinfo,
				   अचिन्हित दीर्घ बारtamp,
				   अचिन्हित दीर्घ cache_validity);
बाह्य पूर्णांक nfs4_buf_to_pages_noslab(स्थिर व्योम *buf, माप_प्रकार buflen,
				    काष्ठा page **pages);

#अगर defined(CONFIG_NFS_V4_1)
बाह्य पूर्णांक nfs41_sequence_करोne(काष्ठा rpc_task *, काष्ठा nfs4_sequence_res *);
बाह्य पूर्णांक nfs4_proc_create_session(काष्ठा nfs_client *, स्थिर काष्ठा cred *);
बाह्य पूर्णांक nfs4_proc_destroy_session(काष्ठा nfs4_session *, स्थिर काष्ठा cred *);
बाह्य पूर्णांक nfs4_proc_layoutcommit(काष्ठा nfs4_layoutcommit_data *data,
				  bool sync);
बाह्य पूर्णांक nfs4_detect_session_trunking(काष्ठा nfs_client *clp,
		काष्ठा nfs41_exchange_id_res *res, काष्ठा rpc_xprt *xprt);

अटल अंतरभूत bool
is_ds_only_client(काष्ठा nfs_client *clp)
अणु
	वापस (clp->cl_exchange_flags & EXCHGID4_FLAG_MASK_PNFS) ==
		EXCHGID4_FLAG_USE_PNFS_DS;
पूर्ण

अटल अंतरभूत bool
is_ds_client(काष्ठा nfs_client *clp)
अणु
	वापस clp->cl_exchange_flags & EXCHGID4_FLAG_USE_PNFS_DS;
पूर्ण

अटल अंतरभूत bool
_nfs4_state_protect(काष्ठा nfs_client *clp, अचिन्हित दीर्घ sp4_mode,
		    काष्ठा rpc_clnt **clntp, काष्ठा rpc_message *msg)
अणु
	rpc_authflavor_t flavor;

	अगर (sp4_mode == NFS_SP4_MACH_CRED_CLEANUP ||
	    sp4_mode == NFS_SP4_MACH_CRED_PNFS_CLEANUP) अणु
		/* Using machine creds क्रम cleanup operations
		 * is only relevent अगर the client credentials
		 * might expire. So करोn't bother क्रम
		 * RPC_AUTH_UNIX.  If file was only exported to
		 * sec=sys, the PUTFH would fail anyway.
		 */
		अगर ((*clntp)->cl_auth->au_flavor == RPC_AUTH_UNIX)
			वापस false;
	पूर्ण
	अगर (test_bit(sp4_mode, &clp->cl_sp4_flags)) अणु
		msg->rpc_cred = rpc_machine_cred();

		flavor = clp->cl_rpcclient->cl_auth->au_flavor;
		WARN_ON_ONCE(flavor != RPC_AUTH_GSS_KRB5I &&
			     flavor != RPC_AUTH_GSS_KRB5P);
		*clntp = clp->cl_rpcclient;

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Function responsible क्रम determining अगर an rpc_message should use the
 * machine cred under SP4_MACH_CRED and अगर so चयनing the credential and
 * authflavor (using the nfs_client's rpc_clnt which will be krb5i/p).
 * Should be called beक्रमe rpc_call_sync/rpc_call_async.
 */
अटल अंतरभूत व्योम
nfs4_state_protect(काष्ठा nfs_client *clp, अचिन्हित दीर्घ sp4_mode,
		   काष्ठा rpc_clnt **clntp, काष्ठा rpc_message *msg)
अणु
	_nfs4_state_protect(clp, sp4_mode, clntp, msg);
पूर्ण

/*
 * Special wrapper to nfs4_state_protect क्रम ग_लिखो.
 * If WRITE can use machine cred but COMMIT cannot, make sure all ग_लिखोs
 * that use machine cred use NFS_खाता_SYNC.
 */
अटल अंतरभूत व्योम
nfs4_state_protect_ग_लिखो(काष्ठा nfs_client *clp, काष्ठा rpc_clnt **clntp,
			 काष्ठा rpc_message *msg, काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (_nfs4_state_protect(clp, NFS_SP4_MACH_CRED_WRITE, clntp, msg) &&
	    !test_bit(NFS_SP4_MACH_CRED_COMMIT, &clp->cl_sp4_flags))
		hdr->args.stable = NFS_खाता_SYNC;
पूर्ण
#अन्यथा /* CONFIG_NFS_v4_1 */
अटल अंतरभूत bool
is_ds_only_client(काष्ठा nfs_client *clp)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
is_ds_client(काष्ठा nfs_client *clp)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम
nfs4_state_protect(काष्ठा nfs_client *clp, अचिन्हित दीर्घ sp4_flags,
		   काष्ठा rpc_clnt **clntp, काष्ठा rpc_message *msg)
अणु
पूर्ण

अटल अंतरभूत व्योम
nfs4_state_protect_ग_लिखो(काष्ठा nfs_client *clp, काष्ठा rpc_clnt **clntp,
			 काष्ठा rpc_message *msg, काष्ठा nfs_pgio_header *hdr)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

बाह्य स्थिर काष्ठा nfs4_minor_version_ops *nfs_v4_minor_ops[];

बाह्य स्थिर u32 nfs4_fattr_biपंचांगap[3];
बाह्य स्थिर u32 nfs4_statfs_biपंचांगap[3];
बाह्य स्थिर u32 nfs4_pathconf_biपंचांगap[3];
बाह्य स्थिर u32 nfs4_fsinfo_biपंचांगap[3];
बाह्य स्थिर u32 nfs4_fs_locations_biपंचांगap[3];

व्योम nfs40_shutकरोwn_client(काष्ठा nfs_client *);
व्योम nfs41_shutकरोwn_client(काष्ठा nfs_client *);
पूर्णांक nfs40_init_client(काष्ठा nfs_client *);
पूर्णांक nfs41_init_client(काष्ठा nfs_client *);
व्योम nfs4_मुक्त_client(काष्ठा nfs_client *);

काष्ठा nfs_client *nfs4_alloc_client(स्थिर काष्ठा nfs_client_initdata *);

/* nfs4renewd.c */
बाह्य व्योम nfs4_schedule_state_renewal(काष्ठा nfs_client *);
बाह्य व्योम nfs4_renewd_prepare_shutकरोwn(काष्ठा nfs_server *);
बाह्य व्योम nfs4_समाप्त_renewd(काष्ठा nfs_client *);
बाह्य व्योम nfs4_renew_state(काष्ठा work_काष्ठा *);
बाह्य व्योम nfs4_set_lease_period(काष्ठा nfs_client *clp, अचिन्हित दीर्घ lease);


/* nfs4state.c */
बाह्य स्थिर nfs4_stateid current_stateid;

स्थिर काष्ठा cred *nfs4_get_clid_cred(काष्ठा nfs_client *clp);
स्थिर काष्ठा cred *nfs4_get_machine_cred(काष्ठा nfs_client *clp);
स्थिर काष्ठा cred *nfs4_get_renew_cred(काष्ठा nfs_client *clp);
पूर्णांक nfs4_discover_server_trunking(काष्ठा nfs_client *clp,
			काष्ठा nfs_client **);
पूर्णांक nfs40_discover_server_trunking(काष्ठा nfs_client *clp,
			काष्ठा nfs_client **, स्थिर काष्ठा cred *);
#अगर defined(CONFIG_NFS_V4_1)
पूर्णांक nfs41_discover_server_trunking(काष्ठा nfs_client *clp,
			काष्ठा nfs_client **, स्थिर काष्ठा cred *);
बाह्य व्योम nfs4_schedule_session_recovery(काष्ठा nfs4_session *, पूर्णांक);
बाह्य व्योम nfs41_notअगरy_server(काष्ठा nfs_client *);
bool nfs4_check_serverowner_major_id(काष्ठा nfs41_server_owner *o1,
			काष्ठा nfs41_server_owner *o2);
#अन्यथा
अटल अंतरभूत व्योम nfs4_schedule_session_recovery(काष्ठा nfs4_session *session, पूर्णांक err)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

बाह्य काष्ठा nfs4_state_owner *nfs4_get_state_owner(काष्ठा nfs_server *, स्थिर काष्ठा cred *, gfp_t);
बाह्य व्योम nfs4_put_state_owner(काष्ठा nfs4_state_owner *);
बाह्य व्योम nfs4_purge_state_owners(काष्ठा nfs_server *, काष्ठा list_head *);
बाह्य व्योम nfs4_मुक्त_state_owners(काष्ठा list_head *head);
बाह्य काष्ठा nfs4_state * nfs4_get_खोलो_state(काष्ठा inode *, काष्ठा nfs4_state_owner *);
बाह्य व्योम nfs4_put_खोलो_state(काष्ठा nfs4_state *);
बाह्य व्योम nfs4_बंद_state(काष्ठा nfs4_state *, भ_शेषe_t);
बाह्य व्योम nfs4_बंद_sync(काष्ठा nfs4_state *, भ_शेषe_t);
बाह्य व्योम nfs4_state_set_mode_locked(काष्ठा nfs4_state *, भ_शेषe_t);
बाह्य व्योम nfs_inode_find_state_and_recover(काष्ठा inode *inode,
		स्थिर nfs4_stateid *stateid);
बाह्य पूर्णांक nfs4_state_mark_reclaim_nograce(काष्ठा nfs_client *, काष्ठा nfs4_state *);
बाह्य व्योम nfs4_schedule_lease_recovery(काष्ठा nfs_client *);
बाह्य पूर्णांक nfs4_रुको_clnt_recover(काष्ठा nfs_client *clp);
बाह्य पूर्णांक nfs4_client_recover_expired_lease(काष्ठा nfs_client *clp);
बाह्य व्योम nfs4_schedule_state_manager(काष्ठा nfs_client *);
बाह्य व्योम nfs4_schedule_path_करोwn_recovery(काष्ठा nfs_client *clp);
बाह्य पूर्णांक nfs4_schedule_stateid_recovery(स्थिर काष्ठा nfs_server *, काष्ठा nfs4_state *);
बाह्य पूर्णांक nfs4_schedule_migration_recovery(स्थिर काष्ठा nfs_server *);
बाह्य व्योम nfs4_schedule_lease_moved_recovery(काष्ठा nfs_client *);
बाह्य व्योम nfs41_handle_sequence_flag_errors(काष्ठा nfs_client *clp, u32 flags, bool);
बाह्य व्योम nfs41_handle_server_scope(काष्ठा nfs_client *,
				      काष्ठा nfs41_server_scope **);
बाह्य व्योम nfs4_put_lock_state(काष्ठा nfs4_lock_state *lsp);
बाह्य पूर्णांक nfs4_set_lock_state(काष्ठा nfs4_state *state, काष्ठा file_lock *fl);
बाह्य पूर्णांक nfs4_select_rw_stateid(काष्ठा nfs4_state *, भ_शेषe_t,
		स्थिर काष्ठा nfs_lock_context *, nfs4_stateid *,
		स्थिर काष्ठा cred **);
बाह्य bool nfs4_copy_खोलो_stateid(nfs4_stateid *dst,
		काष्ठा nfs4_state *state);

बाह्य काष्ठा nfs_seqid *nfs_alloc_seqid(काष्ठा nfs_seqid_counter *counter, gfp_t gfp_mask);
बाह्य पूर्णांक nfs_रुको_on_sequence(काष्ठा nfs_seqid *seqid, काष्ठा rpc_task *task);
बाह्य व्योम nfs_increment_खोलो_seqid(पूर्णांक status, काष्ठा nfs_seqid *seqid);
बाह्य व्योम nfs_increment_lock_seqid(पूर्णांक status, काष्ठा nfs_seqid *seqid);
बाह्य व्योम nfs_release_seqid(काष्ठा nfs_seqid *seqid);
बाह्य व्योम nfs_मुक्त_seqid(काष्ठा nfs_seqid *seqid);
बाह्य पूर्णांक nfs4_setup_sequence(काष्ठा nfs_client *client,
				काष्ठा nfs4_sequence_args *args,
				काष्ठा nfs4_sequence_res *res,
				काष्ठा rpc_task *task);
बाह्य पूर्णांक nfs4_sequence_करोne(काष्ठा rpc_task *task,
			      काष्ठा nfs4_sequence_res *res);

बाह्य व्योम nfs4_मुक्त_lock_state(काष्ठा nfs_server *server, काष्ठा nfs4_lock_state *lsp);
बाह्य पूर्णांक nfs4_proc_commit(काष्ठा file *dst, __u64 offset, __u32 count, काष्ठा nfs_commitres *res);
बाह्य स्थिर nfs4_stateid zero_stateid;
बाह्य स्थिर nfs4_stateid invalid_stateid;

/* nfs4super.c */
काष्ठा nfs_mount_info;
बाह्य काष्ठा nfs_subversion nfs_v4;
बाह्य bool nfs4_disable_idmapping;
बाह्य अचिन्हित लघु max_session_slots;
बाह्य अचिन्हित लघु max_session_cb_slots;
बाह्य अचिन्हित लघु send_implementation_id;
बाह्य bool recover_lost_locks;

#घोषणा NFS4_CLIENT_ID_UNIQ_LEN		(64)
बाह्य अक्षर nfs4_client_id_uniquअगरier[NFS4_CLIENT_ID_UNIQ_LEN];

बाह्य पूर्णांक nfs4_try_get_tree(काष्ठा fs_context *);
बाह्य पूर्णांक nfs4_get_referral_tree(काष्ठा fs_context *);

/* nfs4sysctl.c */
#अगर_घोषित CONFIG_SYSCTL
पूर्णांक nfs4_रेजिस्टर_sysctl(व्योम);
व्योम nfs4_unरेजिस्टर_sysctl(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक nfs4_रेजिस्टर_sysctl(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nfs4_unरेजिस्टर_sysctl(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

/* nfs4xdr.c */
बाह्य स्थिर काष्ठा rpc_procinfo nfs4_procedures[];

#अगर_घोषित CONFIG_NFS_V4_2
बाह्य स्थिर u32 nfs42_maxsetxattr_overhead;
बाह्य स्थिर u32 nfs42_maxgetxattr_overhead;
बाह्य स्थिर u32 nfs42_maxlistxattrs_overhead;
#पूर्ण_अगर

काष्ठा nfs4_mount_data;

/* callback_xdr.c */
बाह्य स्थिर काष्ठा svc_version nfs4_callback_version1;
बाह्य स्थिर काष्ठा svc_version nfs4_callback_version4;

अटल अंतरभूत व्योम nfs4_stateid_copy(nfs4_stateid *dst, स्थिर nfs4_stateid *src)
अणु
	स_नकल(dst->data, src->data, माप(dst->data));
	dst->type = src->type;
पूर्ण

अटल अंतरभूत bool nfs4_stateid_match(स्थिर nfs4_stateid *dst, स्थिर nfs4_stateid *src)
अणु
	अगर (dst->type != src->type)
		वापस false;
	वापस स_भेद(dst->data, src->data, माप(dst->data)) == 0;
पूर्ण

अटल अंतरभूत bool nfs4_stateid_match_other(स्थिर nfs4_stateid *dst, स्थिर nfs4_stateid *src)
अणु
	वापस स_भेद(dst->other, src->other, NFS4_STATEID_OTHER_SIZE) == 0;
पूर्ण

अटल अंतरभूत bool nfs4_stateid_is_newer(स्थिर nfs4_stateid *s1, स्थिर nfs4_stateid *s2)
अणु
	वापस (s32)(be32_to_cpu(s1->seqid) - be32_to_cpu(s2->seqid)) > 0;
पूर्ण

अटल अंतरभूत bool nfs4_stateid_is_next(स्थिर nfs4_stateid *s1, स्थिर nfs4_stateid *s2)
अणु
	u32 seq1 = be32_to_cpu(s1->seqid);
	u32 seq2 = be32_to_cpu(s2->seqid);

	वापस seq2 == seq1 + 1U || (seq2 == 1U && seq1 == 0xffffffffU);
पूर्ण

अटल अंतरभूत bool nfs4_stateid_match_or_older(स्थिर nfs4_stateid *dst, स्थिर nfs4_stateid *src)
अणु
	वापस nfs4_stateid_match_other(dst, src) &&
		!(src->seqid && nfs4_stateid_is_newer(dst, src));
पूर्ण

अटल अंतरभूत व्योम nfs4_stateid_seqid_inc(nfs4_stateid *s1)
अणु
	u32 seqid = be32_to_cpu(s1->seqid);

	अगर (++seqid == 0)
		++seqid;
	s1->seqid = cpu_to_be32(seqid);
पूर्ण

अटल अंतरभूत bool nfs4_valid_खोलो_stateid(स्थिर काष्ठा nfs4_state *state)
अणु
	वापस test_bit(NFS_STATE_RECOVERY_FAILED, &state->flags) == 0;
पूर्ण

अटल अंतरभूत bool nfs4_state_match_खोलो_stateid_other(स्थिर काष्ठा nfs4_state *state,
		स्थिर nfs4_stateid *stateid)
अणु
	वापस test_bit(NFS_OPEN_STATE, &state->flags) &&
		nfs4_stateid_match_other(&state->खोलो_stateid, stateid);
पूर्ण

/* nfs42xattr.c */
#अगर_घोषित CONFIG_NFS_V4_2
बाह्य पूर्णांक __init nfs4_xattr_cache_init(व्योम);
बाह्य व्योम nfs4_xattr_cache_निकास(व्योम);
बाह्य व्योम nfs4_xattr_cache_add(काष्ठा inode *inode, स्थिर अक्षर *name,
				 स्थिर अक्षर *buf, काष्ठा page **pages,
				 sमाप_प्रकार buflen);
बाह्य व्योम nfs4_xattr_cache_हटाओ(काष्ठा inode *inode, स्थिर अक्षर *name);
बाह्य sमाप_प्रकार nfs4_xattr_cache_get(काष्ठा inode *inode, स्थिर अक्षर *name,
				अक्षर *buf, sमाप_प्रकार buflen);
बाह्य व्योम nfs4_xattr_cache_set_list(काष्ठा inode *inode, स्थिर अक्षर *buf,
				      sमाप_प्रकार buflen);
बाह्य sमाप_प्रकार nfs4_xattr_cache_list(काष्ठा inode *inode, अक्षर *buf,
				     sमाप_प्रकार buflen);
बाह्य व्योम nfs4_xattr_cache_zap(काष्ठा inode *inode);
#अन्यथा
अटल अंतरभूत व्योम nfs4_xattr_cache_zap(काष्ठा inode *inode)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

#अन्यथा /* CONFIG_NFS_V4 */

#घोषणा nfs4_बंद_state(a, b) करो अणु पूर्ण जबतक (0)
#घोषणा nfs4_बंद_sync(a, b) करो अणु पूर्ण जबतक (0)
#घोषणा nfs4_state_protect(a, b, c, d) करो अणु पूर्ण जबतक (0)
#घोषणा nfs4_state_protect_ग_लिखो(a, b, c, d) करो अणु पूर्ण जबतक (0)


#पूर्ण_अगर /* CONFIG_NFS_V4 */
#पूर्ण_अगर /* __LINUX_FS_NFS_NFS4_FS.H */
