<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/lockd/lockd.h
 *
 * General-purpose lockd include file.
 *
 * Copyright (C) 1996 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित LINUX_LOCKD_LOCKD_H
#घोषणा LINUX_LOCKD_LOCKD_H

#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <net/ipv6.h>
#समावेश <linux/fs.h>
#समावेश <linux/kref.h>
#समावेश <linux/refcount.h>
#समावेश <linux/utsname.h>
#समावेश <linux/lockd/bind.h>
#समावेश <linux/lockd/xdr.h>
#अगर_घोषित CONFIG_LOCKD_V4
#समावेश <linux/lockd/xdr4.h>
#पूर्ण_अगर
#समावेश <linux/lockd/debug.h>
#समावेश <linux/sunrpc/svc.h>

/*
 * Version string
 */
#घोषणा LOCKD_VERSION		"0.5"

/*
 * Default समयout क्रम RPC calls (seconds)
 */
#घोषणा LOCKD_DFLT_TIMEO	10

/*
 * Lockd host handle (used both by the client and server personality).
 */
काष्ठा nlm_host अणु
	काष्ठा hlist_node	h_hash;		/* करोubly linked list */
	काष्ठा sockaddr_storage	h_addr;		/* peer address */
	माप_प्रकार			h_addrlen;
	काष्ठा sockaddr_storage	h_srcaddr;	/* our address (optional) */
	माप_प्रकार			h_srcaddrlen;
	काष्ठा rpc_clnt		*h_rpcclnt;	/* RPC client to talk to peer */
	अक्षर			*h_name;		/* remote hostname */
	u32			h_version;	/* पूर्णांकerface version */
	अचिन्हित लघु		h_proto;	/* transport proto */
	अचिन्हित लघु		h_reclaiming : 1,
				h_server     : 1, /* server side, not client side */
				h_noresvport : 1,
				h_inuse      : 1;
	रुको_queue_head_t	h_graceरुको;	/* रुको जबतक reclaiming */
	काष्ठा rw_semaphore	h_rwsem;	/* Reboot recovery lock */
	u32			h_state;	/* pseuकरो-state counter */
	u32			h_nsmstate;	/* true remote NSM state */
	u32			h_pidcount;	/* Pseuकरोpids */
	refcount_t		h_count;	/* reference count */
	काष्ठा mutex		h_mutex;	/* mutex क्रम pmap binding */
	अचिन्हित दीर्घ		h_nextrebind;	/* next porपंचांगap call */
	अचिन्हित दीर्घ		h_expires;	/* eligible क्रम GC */
	काष्ठा list_head	h_lockowners;	/* Lockowners क्रम the client */
	spinlock_t		h_lock;
	काष्ठा list_head	h_granted;	/* Locks in GRANTED state */
	काष्ठा list_head	h_reclaim;	/* Locks in RECLAIM state */
	काष्ठा nsm_handle	*h_nsmhandle;	/* NSM status handle */
	अक्षर			*h_addrbuf;	/* address eyecatcher */
	काष्ठा net		*net;		/* host net */
	स्थिर काष्ठा cred	*h_cred;
	अक्षर			nodename[UNX_MAXNODENAME + 1];
	स्थिर काष्ठा nlmclnt_operations	*h_nlmclnt_ops;	/* Callback ops क्रम NLM users */
पूर्ण;

/*
 * The largest string sm_addrbuf should hold is a full-size IPv6 address
 * (no "::" anywhere) with a scope ID.  The buffer size is computed to
 * hold eight groups of colon-separated four-hex-digit numbers, a
 * percent sign, a scope id (at most 32 bits, in decimal), and NUL.
 */
#घोषणा NSM_ADDRBUF		((8 * 4 + 7) + (1 + 10) + 1)

काष्ठा nsm_handle अणु
	काष्ठा list_head	sm_link;
	refcount_t		sm_count;
	अक्षर			*sm_mon_name;
	अक्षर			*sm_name;
	काष्ठा sockaddr_storage	sm_addr;
	माप_प्रकार			sm_addrlen;
	अचिन्हित पूर्णांक		sm_monitored : 1,
				sm_sticky : 1;	/* करोn't unmonitor */
	काष्ठा nsm_निजी	sm_priv;
	अक्षर			sm_addrbuf[NSM_ADDRBUF];
पूर्ण;

/*
 * Rigorous type checking on sockaddr type conversions
 */
अटल अंतरभूत काष्ठा sockaddr_in *nlm_addr_in(स्थिर काष्ठा nlm_host *host)
अणु
	वापस (काष्ठा sockaddr_in *)&host->h_addr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr *nlm_addr(स्थिर काष्ठा nlm_host *host)
अणु
	वापस (काष्ठा sockaddr *)&host->h_addr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr_in *nlm_srcaddr_in(स्थिर काष्ठा nlm_host *host)
अणु
	वापस (काष्ठा sockaddr_in *)&host->h_srcaddr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr *nlm_srcaddr(स्थिर काष्ठा nlm_host *host)
अणु
	वापस (काष्ठा sockaddr *)&host->h_srcaddr;
पूर्ण

/*
 * Map an fl_owner_t पूर्णांकo a unique 32-bit "pid"
 */
काष्ठा nlm_lockowner अणु
	काष्ठा list_head list;
	refcount_t count;

	काष्ठा nlm_host *host;
	fl_owner_t owner;
	uपूर्णांक32_t pid;
पूर्ण;

काष्ठा nlm_रुको;

/*
 * Memory chunk क्रम NLM client RPC request.
 */
#घोषणा NLMCLNT_OHSIZE		((__NEW_UTS_LEN) + 10u)
काष्ठा nlm_rqst अणु
	refcount_t		a_count;
	अचिन्हित पूर्णांक		a_flags;	/* initial RPC task flags */
	काष्ठा nlm_host *	a_host;		/* host handle */
	काष्ठा nlm_args		a_args;		/* arguments */
	काष्ठा nlm_res		a_res;		/* result */
	काष्ठा nlm_block *	a_block;
	अचिन्हित पूर्णांक		a_retries;	/* Retry count */
	u8			a_owner[NLMCLNT_OHSIZE];
	व्योम *	a_callback_data; /* sent to nlmclnt_operations callbacks */
पूर्ण;

/*
 * This काष्ठा describes a file held खोलो by lockd on behalf of
 * an NFS client.
 */
काष्ठा nlm_file अणु
	काष्ठा hlist_node	f_list;		/* linked list */
	काष्ठा nfs_fh		f_handle;	/* NFS file handle */
	काष्ठा file *		f_file;		/* VFS file poपूर्णांकer */
	काष्ठा nlm_share *	f_shares;	/* DOS shares */
	काष्ठा list_head	f_blocks;	/* blocked locks */
	अचिन्हित पूर्णांक		f_locks;	/* guesstimate # of locks */
	अचिन्हित पूर्णांक		f_count;	/* reference count */
	काष्ठा mutex		f_mutex;	/* aव्योम concurrent access */
पूर्ण;

/*
 * This is a server block (i.e. a lock requested by some client which
 * couldn't be granted because of a conflicting lock).
 */
#घोषणा NLM_NEVER		(~(अचिन्हित दीर्घ) 0)
/* समयout on non-blocking call: */
#घोषणा NLM_TIMEOUT		(7 * HZ)

काष्ठा nlm_block अणु
	काष्ठा kref		b_count;	/* Reference count */
	काष्ठा list_head	b_list;		/* linked list of all blocks */
	काष्ठा list_head	b_flist;	/* linked list (per file) */
	काष्ठा nlm_rqst	*	b_call;		/* RPC args & callback info */
	काष्ठा svc_serv *	b_daemon;	/* NLM service */
	काष्ठा nlm_host *	b_host;		/* host handle क्रम RPC clnt */
	अचिन्हित दीर्घ		b_when;		/* next re-xmit */
	अचिन्हित पूर्णांक		b_id;		/* block id */
	अचिन्हित अक्षर		b_granted;	/* VFS granted lock */
	काष्ठा nlm_file *	b_file;		/* file in question */
	काष्ठा cache_req *	b_cache_req;	/* deferred request handling */
	काष्ठा cache_deferred_req * b_deferred_req;
	अचिन्हित पूर्णांक		b_flags;	/* block flags */
#घोषणा B_QUEUED		1	/* lock queued */
#घोषणा B_GOT_CALLBACK		2	/* got lock or conflicting lock */
#घोषणा B_TIMED_OUT		4	/* fileप्रणाली too slow to respond */
पूर्ण;

/*
 * Global variables
 */
बाह्य स्थिर काष्ठा rpc_program	nlm_program;
बाह्य स्थिर काष्ठा svc_procedure nlmsvc_procedures[];
#अगर_घोषित CONFIG_LOCKD_V4
बाह्य स्थिर काष्ठा svc_procedure nlmsvc_procedures4[];
#पूर्ण_अगर
बाह्य पूर्णांक			nlmsvc_grace_period;
बाह्य अचिन्हित दीर्घ		nlmsvc_समयout;
बाह्य bool			nsm_use_hostnames;
बाह्य u32			nsm_local_state;

/*
 * Lockd client functions
 */
काष्ठा nlm_rqst * nlm_alloc_call(काष्ठा nlm_host *host);
पूर्णांक		  nlm_async_call(काष्ठा nlm_rqst *, u32, स्थिर काष्ठा rpc_call_ops *);
पूर्णांक		  nlm_async_reply(काष्ठा nlm_rqst *, u32, स्थिर काष्ठा rpc_call_ops *);
व्योम		  nlmclnt_release_call(काष्ठा nlm_rqst *);
काष्ठा nlm_रुको * nlmclnt_prepare_block(काष्ठा nlm_host *host, काष्ठा file_lock *fl);
व्योम		  nlmclnt_finish_block(काष्ठा nlm_रुको *block);
पूर्णांक		  nlmclnt_block(काष्ठा nlm_रुको *block, काष्ठा nlm_rqst *req, दीर्घ समयout);
__be32		  nlmclnt_grant(स्थिर काष्ठा sockaddr *addr,
				स्थिर काष्ठा nlm_lock *lock);
व्योम		  nlmclnt_recovery(काष्ठा nlm_host *);
पूर्णांक		  nlmclnt_reclaim(काष्ठा nlm_host *, काष्ठा file_lock *,
				  काष्ठा nlm_rqst *);
व्योम		  nlmclnt_next_cookie(काष्ठा nlm_cookie *);

/*
 * Host cache
 */
काष्ठा nlm_host  *nlmclnt_lookup_host(स्थिर काष्ठा sockaddr *sap,
					स्थिर माप_प्रकार salen,
					स्थिर अचिन्हित लघु protocol,
					स्थिर u32 version,
					स्थिर अक्षर *hostname,
					पूर्णांक noresvport,
					काष्ठा net *net,
					स्थिर काष्ठा cred *cred);
व्योम		  nlmclnt_release_host(काष्ठा nlm_host *);
काष्ठा nlm_host  *nlmsvc_lookup_host(स्थिर काष्ठा svc_rqst *rqstp,
					स्थिर अक्षर *hostname,
					स्थिर माप_प्रकार hostname_len);
व्योम		  nlmsvc_release_host(काष्ठा nlm_host *);
काष्ठा rpc_clnt * nlm_bind_host(काष्ठा nlm_host *);
व्योम		  nlm_rebind_host(काष्ठा nlm_host *);
काष्ठा nlm_host * nlm_get_host(काष्ठा nlm_host *);
व्योम		  nlm_shutकरोwn_hosts(व्योम);
व्योम		  nlm_shutकरोwn_hosts_net(काष्ठा net *net);
व्योम		  nlm_host_rebooted(स्थिर काष्ठा net *net,
					स्थिर काष्ठा nlm_reboot *);

/*
 * Host monitoring
 */
पूर्णांक		  nsm_monitor(स्थिर काष्ठा nlm_host *host);
व्योम		  nsm_unmonitor(स्थिर काष्ठा nlm_host *host);

काष्ठा nsm_handle *nsm_get_handle(स्थिर काष्ठा net *net,
					स्थिर काष्ठा sockaddr *sap,
					स्थिर माप_प्रकार salen,
					स्थिर अक्षर *hostname,
					स्थिर माप_प्रकार hostname_len);
काष्ठा nsm_handle *nsm_reboot_lookup(स्थिर काष्ठा net *net,
					स्थिर काष्ठा nlm_reboot *info);
व्योम		  nsm_release(काष्ठा nsm_handle *nsm);

/*
 * This is used in garbage collection and resource reclaim
 * A वापस value != 0 means destroy the lock/block/share
 */
प्रकार पूर्णांक	  (*nlm_host_match_fn_t)(व्योम *cur, काष्ठा nlm_host *ref);

/*
 * Server-side lock handling
 */
__be32		  nlmsvc_lock(काष्ठा svc_rqst *, काष्ठा nlm_file *,
			      काष्ठा nlm_host *, काष्ठा nlm_lock *, पूर्णांक,
			      काष्ठा nlm_cookie *, पूर्णांक);
__be32		  nlmsvc_unlock(काष्ठा net *net, काष्ठा nlm_file *, काष्ठा nlm_lock *);
__be32		  nlmsvc_testlock(काष्ठा svc_rqst *, काष्ठा nlm_file *,
			काष्ठा nlm_host *, काष्ठा nlm_lock *,
			काष्ठा nlm_lock *, काष्ठा nlm_cookie *);
__be32		  nlmsvc_cancel_blocked(काष्ठा net *net, काष्ठा nlm_file *, काष्ठा nlm_lock *);
अचिन्हित दीर्घ	  nlmsvc_retry_blocked(व्योम);
व्योम		  nlmsvc_traverse_blocks(काष्ठा nlm_host *, काष्ठा nlm_file *,
					nlm_host_match_fn_t match);
व्योम		  nlmsvc_grant_reply(काष्ठा nlm_cookie *, __be32);
व्योम		  nlmsvc_release_call(काष्ठा nlm_rqst *);
व्योम		  nlmsvc_locks_init_निजी(काष्ठा file_lock *, काष्ठा nlm_host *, pid_t);

/*
 * File handling क्रम the server personality
 */
__be32		  nlm_lookup_file(काष्ठा svc_rqst *, काष्ठा nlm_file **,
					काष्ठा nfs_fh *);
व्योम		  nlm_release_file(काष्ठा nlm_file *);
व्योम		  nlmsvc_release_lockowner(काष्ठा nlm_lock *);
व्योम		  nlmsvc_mark_resources(काष्ठा net *);
व्योम		  nlmsvc_मुक्त_host_resources(काष्ठा nlm_host *);
व्योम		  nlmsvc_invalidate_all(व्योम);

/*
 * Cluster failover support
 */
पूर्णांक           nlmsvc_unlock_all_by_sb(काष्ठा super_block *sb);
पूर्णांक           nlmsvc_unlock_all_by_ip(काष्ठा sockaddr *server_addr);

अटल अंतरभूत काष्ठा inode *nlmsvc_file_inode(काष्ठा nlm_file *file)
अणु
	वापस locks_inode(file->f_file);
पूर्ण

अटल अंतरभूत पूर्णांक __nlm_privileged_request4(स्थिर काष्ठा sockaddr *sap)
अणु
	स्थिर काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)sap;

	अगर (ntohs(sin->sin_port) > 1023)
		वापस 0;

	वापस ipv4_is_loopback(sin->sin_addr.s_addr);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत पूर्णांक __nlm_privileged_request6(स्थिर काष्ठा sockaddr *sap)
अणु
	स्थिर काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sap;

	अगर (ntohs(sin6->sin6_port) > 1023)
		वापस 0;

	अगर (ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_MAPPED)
		वापस ipv4_is_loopback(sin6->sin6_addr.s6_addr32[3]);

	वापस ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_LOOPBACK;
पूर्ण
#अन्यथा	/* IS_ENABLED(CONFIG_IPV6) */
अटल अंतरभूत पूर्णांक __nlm_privileged_request6(स्थिर काष्ठा sockaddr *sap)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* IS_ENABLED(CONFIG_IPV6) */

/*
 * Ensure incoming requests are from local privileged callers.
 *
 * Return TRUE अगर sender is local and is connecting via a privileged port;
 * otherwise वापस FALSE.
 */
अटल अंतरभूत पूर्णांक nlm_privileged_requester(स्थिर काष्ठा svc_rqst *rqstp)
अणु
	स्थिर काष्ठा sockaddr *sap = svc_addr(rqstp);

	चयन (sap->sa_family) अणु
	हाल AF_INET:
		वापस __nlm_privileged_request4(sap);
	हाल AF_INET6:
		वापस __nlm_privileged_request6(sap);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Compare two NLM locks.
 * When the second lock is of type F_UNLCK, this acts like a wildcard.
 */
अटल अंतरभूत पूर्णांक nlm_compare_locks(स्थिर काष्ठा file_lock *fl1,
				    स्थिर काष्ठा file_lock *fl2)
अणु
	वापस locks_inode(fl1->fl_file) == locks_inode(fl2->fl_file)
	     && fl1->fl_pid   == fl2->fl_pid
	     && fl1->fl_owner == fl2->fl_owner
	     && fl1->fl_start == fl2->fl_start
	     && fl1->fl_end   == fl2->fl_end
	     &&(fl1->fl_type  == fl2->fl_type || fl2->fl_type == F_UNLCK);
पूर्ण

बाह्य स्थिर काष्ठा lock_manager_operations nlmsvc_lock_operations;

#पूर्ण_अगर /* LINUX_LOCKD_LOCKD_H */
