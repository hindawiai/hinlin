<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/sunrpc/clnt.h
 *
 *  Declarations क्रम the high-level RPC client पूर्णांकerface
 *
 *  Copyright (C) 1995, 1996, Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _LINUX_SUNRPC_CLNT_H
#घोषणा _LINUX_SUNRPC_CLNT_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/xprt.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/समयr.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <linux/path.h>
#समावेश <net/ipv6.h>
#समावेश <linux/sunrpc/xprपंचांगultipath.h>

काष्ठा rpc_inode;

/*
 * The high-level client handle
 */
काष्ठा rpc_clnt अणु
	atomic_t		cl_count;	/* Number of references */
	अचिन्हित पूर्णांक		cl_clid;	/* client id */
	काष्ठा list_head	cl_clients;	/* Global list of clients */
	काष्ठा list_head	cl_tasks;	/* List of tasks */
	spinlock_t		cl_lock;	/* spinlock */
	काष्ठा rpc_xprt __rcu *	cl_xprt;	/* transport */
	स्थिर काष्ठा rpc_procinfo *cl_procinfo;	/* procedure info */
	u32			cl_prog,	/* RPC program number */
				cl_vers,	/* RPC version number */
				cl_maxproc;	/* max procedure number */

	काष्ठा rpc_auth *	cl_auth;	/* authenticator */
	काष्ठा rpc_stat *	cl_stats;	/* per-program statistics */
	काष्ठा rpc_iostats *	cl_metrics;	/* per-client statistics */

	अचिन्हित पूर्णांक		cl_softrtry : 1,/* soft समयouts */
				cl_softerr  : 1,/* Timeouts वापस errors */
				cl_discrtry : 1,/* disconnect beक्रमe retry */
				cl_noretransसमयo: 1,/* No retransmit समयouts */
				cl_स्वतःbind : 1,/* use getport() */
				cl_chatty   : 1;/* be verbose */

	काष्ठा rpc_rtt *	cl_rtt;		/* RTO estimator data */
	स्थिर काष्ठा rpc_समयout *cl_समयout;	/* Timeout strategy */

	atomic_t		cl_swapper;	/* swapfile count */
	पूर्णांक			cl_nodelen;	/* nodename length */
	अक्षर 			cl_nodename[UNX_MAXNODENAME+1];
	काष्ठा rpc_pipe_dir_head cl_pipedir_objects;
	काष्ठा rpc_clnt *	cl_parent;	/* Poपूर्णांकs to parent of clones */
	काष्ठा rpc_rtt		cl_rtt_शेष;
	काष्ठा rpc_समयout	cl_समयout_शेष;
	स्थिर काष्ठा rpc_program *cl_program;
	स्थिर अक्षर *		cl_principal;	/* use क्रम machine cred */
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
	काष्ठा dentry		*cl_debugfs;	/* debugfs directory */
#पूर्ण_अगर
	/* cl_work is only needed after cl_xpi is no दीर्घer used,
	 * and that are of similar size
	 */
	जोड़ अणु
		काष्ठा rpc_xprt_iter	cl_xpi;
		काष्ठा work_काष्ठा	cl_work;
	पूर्ण;
	स्थिर काष्ठा cred	*cl_cred;
पूर्ण;

/*
 * General RPC program info
 */
#घोषणा RPC_MAXVERSION		4
काष्ठा rpc_program अणु
	स्थिर अक्षर *		name;		/* protocol name */
	u32			number;		/* program number */
	अचिन्हित पूर्णांक		nrvers;		/* number of versions */
	स्थिर काष्ठा rpc_version **	version;	/* version array */
	काष्ठा rpc_stat *	stats;		/* statistics */
	स्थिर अक्षर *		pipe_dir_name;	/* path to rpc_pipefs dir */
पूर्ण;

काष्ठा rpc_version अणु
	u32			number;		/* version number */
	अचिन्हित पूर्णांक		nrprocs;	/* number of procs */
	स्थिर काष्ठा rpc_procinfo *procs;	/* procedure array */
	अचिन्हित पूर्णांक		*counts;	/* call counts */
पूर्ण;

/*
 * Procedure inक्रमmation
 */
काष्ठा rpc_procinfo अणु
	u32			p_proc;		/* RPC procedure number */
	kxdreproc_t		p_encode;	/* XDR encode function */
	kxdrdproc_t		p_decode;	/* XDR decode function */
	अचिन्हित पूर्णांक		p_arglen;	/* argument hdr length (u32) */
	अचिन्हित पूर्णांक		p_replen;	/* reply hdr length (u32) */
	अचिन्हित पूर्णांक		p_समयr;	/* Which RTT समयr to use */
	u32			p_statidx;	/* Which procedure to account */
	स्थिर अक्षर *		p_name;		/* name of procedure */
पूर्ण;

काष्ठा rpc_create_args अणु
	काष्ठा net		*net;
	पूर्णांक			protocol;
	काष्ठा sockaddr		*address;
	माप_प्रकार			addrsize;
	काष्ठा sockaddr		*saddress;
	स्थिर काष्ठा rpc_समयout *समयout;
	स्थिर अक्षर		*servername;
	स्थिर अक्षर		*nodename;
	स्थिर काष्ठा rpc_program *program;
	u32			prognumber;	/* overrides program->number */
	u32			version;
	rpc_authflavor_t	authflavor;
	u32			nconnect;
	अचिन्हित दीर्घ		flags;
	अक्षर			*client_name;
	काष्ठा svc_xprt		*bc_xprt;	/* NFSv4.1 backchannel */
	स्थिर काष्ठा cred	*cred;
पूर्ण;

काष्ठा rpc_add_xprt_test अणु
	व्योम (*add_xprt_test)(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt *xprt,
		व्योम *calldata);
	व्योम *data;
पूर्ण;

/* Values क्रम "flags" field */
#घोषणा RPC_CLNT_CREATE_HARDRTRY	(1UL << 0)
#घोषणा RPC_CLNT_CREATE_AUTOBIND	(1UL << 2)
#घोषणा RPC_CLNT_CREATE_NONPRIVPORT	(1UL << 3)
#घोषणा RPC_CLNT_CREATE_NOPING		(1UL << 4)
#घोषणा RPC_CLNT_CREATE_DISCRTRY	(1UL << 5)
#घोषणा RPC_CLNT_CREATE_QUIET		(1UL << 6)
#घोषणा RPC_CLNT_CREATE_INFINITE_SLOTS	(1UL << 7)
#घोषणा RPC_CLNT_CREATE_NO_IDLE_TIMEOUT	(1UL << 8)
#घोषणा RPC_CLNT_CREATE_NO_RETRANS_TIMEOUT	(1UL << 9)
#घोषणा RPC_CLNT_CREATE_SOFTERR		(1UL << 10)
#घोषणा RPC_CLNT_CREATE_REUSEPORT	(1UL << 11)

काष्ठा rpc_clnt *rpc_create(काष्ठा rpc_create_args *args);
काष्ठा rpc_clnt	*rpc_bind_new_program(काष्ठा rpc_clnt *,
				स्थिर काष्ठा rpc_program *, u32);
काष्ठा rpc_clnt *rpc_clone_client(काष्ठा rpc_clnt *);
काष्ठा rpc_clnt *rpc_clone_client_set_auth(काष्ठा rpc_clnt *,
				rpc_authflavor_t);
पूर्णांक		rpc_चयन_client_transport(काष्ठा rpc_clnt *,
				काष्ठा xprt_create *,
				स्थिर काष्ठा rpc_समयout *);

व्योम		rpc_shutकरोwn_client(काष्ठा rpc_clnt *);
व्योम		rpc_release_client(काष्ठा rpc_clnt *);
व्योम		rpc_task_release_transport(काष्ठा rpc_task *);
व्योम		rpc_task_release_client(काष्ठा rpc_task *);
काष्ठा rpc_xprt	*rpc_task_get_xprt(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt *xprt);

पूर्णांक		rpcb_create_local(काष्ठा net *);
व्योम		rpcb_put_local(काष्ठा net *);
पूर्णांक		rpcb_रेजिस्टर(काष्ठा net *, u32, u32, पूर्णांक, अचिन्हित लघु);
पूर्णांक		rpcb_v4_रेजिस्टर(काष्ठा net *net, स्थिर u32 program,
				 स्थिर u32 version,
				 स्थिर काष्ठा sockaddr *address,
				 स्थिर अक्षर *netid);
व्योम		rpcb_getport_async(काष्ठा rpc_task *);

व्योम rpc_prepare_reply_pages(काष्ठा rpc_rqst *req, काष्ठा page **pages,
			     अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
			     अचिन्हित पूर्णांक hdrsize);
व्योम		rpc_call_start(काष्ठा rpc_task *);
पूर्णांक		rpc_call_async(काष्ठा rpc_clnt *clnt,
			       स्थिर काष्ठा rpc_message *msg, पूर्णांक flags,
			       स्थिर काष्ठा rpc_call_ops *tk_ops,
			       व्योम *calldata);
पूर्णांक		rpc_call_sync(काष्ठा rpc_clnt *clnt,
			      स्थिर काष्ठा rpc_message *msg, पूर्णांक flags);
काष्ठा rpc_task *rpc_call_null(काष्ठा rpc_clnt *clnt, काष्ठा rpc_cred *cred,
			       पूर्णांक flags);
पूर्णांक		rpc_restart_call_prepare(काष्ठा rpc_task *);
पूर्णांक		rpc_restart_call(काष्ठा rpc_task *);
व्योम		rpc_रखो_बफsize(काष्ठा rpc_clnt *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
काष्ठा net *	rpc_net_ns(काष्ठा rpc_clnt *);
माप_प्रकार		rpc_max_payload(काष्ठा rpc_clnt *);
माप_प्रकार		rpc_max_bc_payload(काष्ठा rpc_clnt *);
अचिन्हित पूर्णांक	rpc_num_bc_slots(काष्ठा rpc_clnt *);
व्योम		rpc_क्रमce_rebind(काष्ठा rpc_clnt *);
माप_प्रकार		rpc_peeraddr(काष्ठा rpc_clnt *, काष्ठा sockaddr *, माप_प्रकार);
स्थिर अक्षर	*rpc_peeraddr2str(काष्ठा rpc_clnt *, क्रमागत rpc_display_क्रमmat_t);
पूर्णांक		rpc_localaddr(काष्ठा rpc_clnt *, काष्ठा sockaddr *, माप_प्रकार);

पूर्णांक 		rpc_clnt_iterate_क्रम_each_xprt(काष्ठा rpc_clnt *clnt,
			पूर्णांक (*fn)(काष्ठा rpc_clnt *, काष्ठा rpc_xprt *, व्योम *),
			व्योम *data);

पूर्णांक 		rpc_clnt_test_and_add_xprt(काष्ठा rpc_clnt *clnt,
			काष्ठा rpc_xprt_चयन *xps,
			काष्ठा rpc_xprt *xprt,
			व्योम *dummy);
पूर्णांक		rpc_clnt_add_xprt(काष्ठा rpc_clnt *, काष्ठा xprt_create *,
			पूर्णांक (*setup)(काष्ठा rpc_clnt *,
				काष्ठा rpc_xprt_चयन *,
				काष्ठा rpc_xprt *,
				व्योम *),
			व्योम *data);
व्योम		rpc_set_connect_समयout(काष्ठा rpc_clnt *clnt,
			अचिन्हित दीर्घ connect_समयout,
			अचिन्हित दीर्घ reconnect_समयout);

पूर्णांक		rpc_clnt_setup_test_and_add_xprt(काष्ठा rpc_clnt *,
			काष्ठा rpc_xprt_चयन *,
			काष्ठा rpc_xprt *,
			व्योम *);

स्थिर अक्षर *rpc_proc_name(स्थिर काष्ठा rpc_task *task);

व्योम rpc_clnt_xprt_चयन_put(काष्ठा rpc_clnt *);
व्योम rpc_clnt_xprt_चयन_add_xprt(काष्ठा rpc_clnt *, काष्ठा rpc_xprt *);
bool rpc_clnt_xprt_चयन_has_addr(काष्ठा rpc_clnt *clnt,
			स्थिर काष्ठा sockaddr *sap);
व्योम rpc_cleanup_clids(व्योम);

अटल अंतरभूत पूर्णांक rpc_reply_expected(काष्ठा rpc_task *task)
अणु
	वापस (task->tk_msg.rpc_proc != शून्य) &&
		(task->tk_msg.rpc_proc->p_decode != शून्य);
पूर्ण

अटल अंतरभूत व्योम rpc_task_बंद_connection(काष्ठा rpc_task *task)
अणु
	अगर (task->tk_xprt)
		xprt_क्रमce_disconnect(task->tk_xprt);
पूर्ण
#पूर्ण_अगर /* _LINUX_SUNRPC_CLNT_H */
