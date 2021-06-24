<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/svc.h
 *
 * RPC server declarations.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */


#अगर_अघोषित SUNRPC_SVC_H
#घोषणा SUNRPC_SVC_H

#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/sunrpc/types.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/sunrpc/svcauth.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>

/* statistics क्रम svc_pool काष्ठाures */
काष्ठा svc_pool_stats अणु
	atomic_दीर्घ_t	packets;
	अचिन्हित दीर्घ	sockets_queued;
	atomic_दीर्घ_t	thपढ़ोs_woken;
	atomic_दीर्घ_t	thपढ़ोs_समयकरोut;
पूर्ण;

/*
 *
 * RPC service thपढ़ो pool.
 *
 * Pool of thपढ़ोs and temporary sockets.  Generally there is only
 * a single one of these per RPC service, but on NUMA machines those
 * services that can benefit from it (i.e. nfs but not lockd) will
 * have one pool per NUMA node.  This optimisation reduces cross-
 * node traffic on multi-node NUMA NFS servers.
 */
काष्ठा svc_pool अणु
	अचिन्हित पूर्णांक		sp_id;	    	/* pool id; also node id on NUMA */
	spinlock_t		sp_lock;	/* protects all fields */
	काष्ठा list_head	sp_sockets;	/* pending sockets */
	अचिन्हित पूर्णांक		sp_nrthपढ़ोs;	/* # of thपढ़ोs in pool */
	काष्ठा list_head	sp_all_thपढ़ोs;	/* all server thपढ़ोs */
	काष्ठा svc_pool_stats	sp_stats;	/* statistics on pool operation */
#घोषणा	SP_TASK_PENDING		(0)		/* still work to करो even अगर no
						 * xprt is queued. */
#घोषणा SP_CONGESTED		(1)
	अचिन्हित दीर्घ		sp_flags;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा svc_serv;

काष्ठा svc_serv_ops अणु
	/* Callback to use when last thपढ़ो निकासs. */
	व्योम		(*svo_shutकरोwn)(काष्ठा svc_serv *, काष्ठा net *);

	/* function क्रम service thपढ़ोs to run */
	पूर्णांक		(*svo_function)(व्योम *);

	/* queue up a transport क्रम servicing */
	व्योम		(*svo_enqueue_xprt)(काष्ठा svc_xprt *);

	/* set up thपढ़ो (or whatever) execution context */
	पूर्णांक		(*svo_setup)(काष्ठा svc_serv *, काष्ठा svc_pool *, पूर्णांक);

	/* optional module to count when adding thपढ़ोs (pooled svcs only) */
	काष्ठा module	*svo_module;
पूर्ण;

/*
 * RPC service.
 *
 * An RPC service is a ``daemon,'' possibly multithपढ़ोed, which
 * receives and processes incoming RPC messages.
 * It has one or more transport sockets associated with it, and मुख्यtains
 * a list of idle thपढ़ोs रुकोing क्रम input.
 *
 * We currently करो not support more than one RPC program per daemon.
 */
काष्ठा svc_serv अणु
	काष्ठा svc_program *	sv_program;	/* RPC program */
	काष्ठा svc_stat *	sv_stats;	/* RPC statistics */
	spinlock_t		sv_lock;
	अचिन्हित पूर्णांक		sv_nrthपढ़ोs;	/* # of server thपढ़ोs */
	अचिन्हित पूर्णांक		sv_maxconn;	/* max connections allowed or
						 * '0' causing max to be based
						 * on number of thपढ़ोs. */

	अचिन्हित पूर्णांक		sv_max_payload;	/* datagram payload size */
	अचिन्हित पूर्णांक		sv_max_mesg;	/* max_payload + 1 page क्रम overheads */
	अचिन्हित पूर्णांक		sv_xdrsize;	/* XDR buffer size */
	काष्ठा list_head	sv_permsocks;	/* all permanent sockets */
	काष्ठा list_head	sv_tempsocks;	/* all temporary sockets */
	पूर्णांक			sv_पंचांगpcnt;	/* count of temporary sockets */
	काष्ठा समयr_list	sv_tempसमयr;	/* समयr क्रम aging temporary sockets */

	अक्षर *			sv_name;	/* service name */

	अचिन्हित पूर्णांक		sv_nrpools;	/* number of thपढ़ो pools */
	काष्ठा svc_pool *	sv_pools;	/* array of thपढ़ो pools */
	स्थिर काष्ठा svc_serv_ops *sv_ops;	/* server operations */
#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
	काष्ठा list_head	sv_cb_list;	/* queue क्रम callback requests
						 * that arrive over the same
						 * connection */
	spinlock_t		sv_cb_lock;	/* protects the svc_cb_list */
	रुको_queue_head_t	sv_cb_रुकोq;	/* sleep here अगर there are no
						 * entries in the svc_cb_list */
	bool			sv_bc_enabled;	/* service uses backchannel */
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */
पूर्ण;

/*
 * We use sv_nrthपढ़ोs as a reference count.  svc_destroy() drops
 * this refcount, so we need to bump it up around operations that
 * change the number of thपढ़ोs.  Horrible, but there it is.
 * Should be called with the "service mutex" held.
 */
अटल अंतरभूत व्योम svc_get(काष्ठा svc_serv *serv)
अणु
	serv->sv_nrthपढ़ोs++;
पूर्ण

/*
 * Maximum payload size supported by a kernel RPC server.
 * This is use to determine the max number of pages nfsd is
 * willing to वापस in a single READ operation.
 *
 * These happen to all be घातers of 2, which is not strictly
 * necessary but helps enक्रमce the real limitation, which is
 * that they should be multiples of PAGE_SIZE.
 *
 * For UDP transports, a block plus NFS,RPC, and UDP headers
 * has to fit पूर्णांकo the IP datagram limit of 64K.  The largest
 * feasible number क्रम all known page sizes is probably 48K,
 * but we choose 32K here.  This is the same as the historical
 * Linux limit; someone who cares more about NFS/UDP perक्रमmance
 * can test a larger number.
 *
 * For TCP transports we have more मुक्तकरोm.  A size of 1MB is
 * chosen to match the client limit.  Other OSes are known to
 * have larger limits, but those numbers are probably beyond
 * the poपूर्णांक of diminishing वापसs.
 */
#घोषणा RPCSVC_MAXPAYLOAD	(1*1024*1024u)
#घोषणा RPCSVC_MAXPAYLOAD_TCP	RPCSVC_MAXPAYLOAD
#घोषणा RPCSVC_MAXPAYLOAD_UDP	(32*1024u)

बाह्य u32 svc_max_payload(स्थिर काष्ठा svc_rqst *rqstp);

/*
 * RPC Requsts and replies are stored in one or more pages.
 * We मुख्यtain an array of pages क्रम each server thपढ़ो.
 * Requests are copied पूर्णांकo these pages as they arrive.  Reमुख्यing
 * pages are available to ग_लिखो the reply पूर्णांकo.
 *
 * Pages are sent using ->sendpage so each server thपढ़ो needs to
 * allocate more to replace those used in sending.  To help keep track
 * of these pages we have a receive list where all pages initialy live,
 * and a send list where pages are moved to when there are to be part
 * of a reply.
 *
 * We use xdr_buf क्रम holding responses as it fits well with NFS
 * पढ़ो responses (that have a header, and some data pages, and possibly
 * a tail) and means we can share some client side routines.
 *
 * The xdr_buf.head kvec always poपूर्णांकs to the first page in the rq_*pages
 * list.  The xdr_buf.pages poपूर्णांकer poपूर्णांकs to the second page on that
 * list.  xdr_buf.tail poपूर्णांकs to the end of the first page.
 * This assumes that the non-page part of an rpc reply will fit
 * in a page - NFSd ensures this.  lockd also has no trouble.
 *
 * Each request/reply pair can have at most one "payload", plus two pages,
 * one क्रम the request, and one क्रम the reply.
 * We using ->sendfile to वापस पढ़ो data, we might need one extra page
 * अगर the request is not page-aligned.  So add another '1'.
 */
#घोषणा RPCSVC_MAXPAGES		((RPCSVC_MAXPAYLOAD+PAGE_SIZE-1)/PAGE_SIZE \
				+ 2 + 1)

अटल अंतरभूत u32 svc_getnl(काष्ठा kvec *iov)
अणु
	__be32 val, *vp;
	vp = iov->iov_base;
	val = *vp++;
	iov->iov_base = (व्योम*)vp;
	iov->iov_len -= माप(__be32);
	वापस ntohl(val);
पूर्ण

अटल अंतरभूत व्योम svc_putnl(काष्ठा kvec *iov, u32 val)
अणु
	__be32 *vp = iov->iov_base + iov->iov_len;
	*vp = htonl(val);
	iov->iov_len += माप(__be32);
पूर्ण

अटल अंतरभूत __be32 svc_getu32(काष्ठा kvec *iov)
अणु
	__be32 val, *vp;
	vp = iov->iov_base;
	val = *vp++;
	iov->iov_base = (व्योम*)vp;
	iov->iov_len -= माप(__be32);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम svc_ungetu32(काष्ठा kvec *iov)
अणु
	__be32 *vp = (__be32 *)iov->iov_base;
	iov->iov_base = (व्योम *)(vp - 1);
	iov->iov_len += माप(*vp);
पूर्ण

अटल अंतरभूत व्योम svc_putu32(काष्ठा kvec *iov, __be32 val)
अणु
	__be32 *vp = iov->iov_base + iov->iov_len;
	*vp = val;
	iov->iov_len += माप(__be32);
पूर्ण

/*
 * The context of a single thपढ़ो, including the request currently being
 * processed.
 */
काष्ठा svc_rqst अणु
	काष्ठा list_head	rq_all;		/* all thपढ़ोs list */
	काष्ठा rcu_head		rq_rcu_head;	/* क्रम RCU deferred kमुक्त */
	काष्ठा svc_xprt *	rq_xprt;	/* transport ptr */

	काष्ठा sockaddr_storage	rq_addr;	/* peer address */
	माप_प्रकार			rq_addrlen;
	काष्ठा sockaddr_storage	rq_daddr;	/* dest addr of request
						 *  - reply from here */
	माप_प्रकार			rq_daddrlen;

	काष्ठा svc_serv *	rq_server;	/* RPC service definition */
	काष्ठा svc_pool *	rq_pool;	/* thपढ़ो pool */
	स्थिर काष्ठा svc_procedure *rq_procinfo;/* procedure info */
	काष्ठा auth_ops *	rq_authop;	/* authentication flavour */
	काष्ठा svc_cred		rq_cred;	/* auth info */
	व्योम *			rq_xprt_ctxt;	/* transport specअगरic context ptr */
	काष्ठा svc_deferred_req*rq_deferred;	/* deferred request we are replaying */

	माप_प्रकार			rq_xprt_hlen;	/* xprt header len */
	काष्ठा xdr_buf		rq_arg;
	काष्ठा xdr_stream	rq_arg_stream;
	काष्ठा xdr_stream	rq_res_stream;
	काष्ठा page		*rq_scratch_page;
	काष्ठा xdr_buf		rq_res;
	काष्ठा page		*rq_pages[RPCSVC_MAXPAGES + 1];
	काष्ठा page *		*rq_respages;	/* poपूर्णांकs पूर्णांकo rq_pages */
	काष्ठा page *		*rq_next_page; /* next reply page to use */
	काष्ठा page *		*rq_page_end;  /* one past the last page */

	काष्ठा kvec		rq_vec[RPCSVC_MAXPAGES]; /* generally useful.. */
	काष्ठा bio_vec		rq_bvec[RPCSVC_MAXPAGES];

	__be32			rq_xid;		/* transmission id */
	u32			rq_prog;	/* program number */
	u32			rq_vers;	/* program version */
	u32			rq_proc;	/* procedure number */
	u32			rq_prot;	/* IP protocol */
	पूर्णांक			rq_cachetype;	/* catering to nfsd */
#घोषणा	RQ_SECURE	(0)			/* secure port */
#घोषणा	RQ_LOCAL	(1)			/* local request */
#घोषणा	RQ_USEDEFERRAL	(2)			/* use deferral */
#घोषणा	RQ_DROPME	(3)			/* drop current reply */
#घोषणा	RQ_SPLICE_OK	(4)			/* turned off in gss privacy
						 * to prevent encrypting page
						 * cache pages */
#घोषणा	RQ_VICTIM	(5)			/* about to be shut करोwn */
#घोषणा	RQ_BUSY		(6)			/* request is busy */
#घोषणा	RQ_DATA		(7)			/* request has data */
#घोषणा RQ_AUTHERR	(8)			/* Request status is auth error */
	अचिन्हित दीर्घ		rq_flags;	/* flags field */
	kसमय_प्रकार			rq_qसमय;	/* enqueue समय */

	व्योम *			rq_argp;	/* decoded arguments */
	व्योम *			rq_resp;	/* xdr'd results */
	व्योम *			rq_auth_data;	/* flavor-specअगरic data */
	पूर्णांक			rq_auth_slack;	/* extra space xdr code
						 * should leave in head
						 * क्रम krb5i, krb5p.
						 */
	पूर्णांक			rq_reserved;	/* space on socket outq
						 * reserved क्रम this request
						 */
	kसमय_प्रकार			rq_sसमय;	/* start समय */

	काष्ठा cache_req	rq_chandle;	/* handle passed to caches क्रम 
						 * request delaying 
						 */
	/* Catering to nfsd */
	काष्ठा auth_करोमुख्य *	rq_client;	/* RPC peer info */
	काष्ठा auth_करोमुख्य *	rq_gssclient;	/* "gss/"-style peer info */
	काष्ठा svc_cacherep *	rq_cacherep;	/* cache info */
	काष्ठा task_काष्ठा	*rq_task;	/* service thपढ़ो */
	spinlock_t		rq_lock;	/* per-request lock */
	काष्ठा net		*rq_bc_net;	/* poपूर्णांकer to backchannel's
						 * net namespace
						 */
	व्योम **			rq_lease_अवरोधer; /* The v4 client अवरोधing a lease */
पूर्ण;

#घोषणा SVC_NET(rqst) (rqst->rq_xprt ? rqst->rq_xprt->xpt_net : rqst->rq_bc_net)

/*
 * Rigorous type checking on sockaddr type conversions
 */
अटल अंतरभूत काष्ठा sockaddr_in *svc_addr_in(स्थिर काष्ठा svc_rqst *rqst)
अणु
	वापस (काष्ठा sockaddr_in *) &rqst->rq_addr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr_in6 *svc_addr_in6(स्थिर काष्ठा svc_rqst *rqst)
अणु
	वापस (काष्ठा sockaddr_in6 *) &rqst->rq_addr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr *svc_addr(स्थिर काष्ठा svc_rqst *rqst)
अणु
	वापस (काष्ठा sockaddr *) &rqst->rq_addr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr_in *svc_daddr_in(स्थिर काष्ठा svc_rqst *rqst)
अणु
	वापस (काष्ठा sockaddr_in *) &rqst->rq_daddr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr_in6 *svc_daddr_in6(स्थिर काष्ठा svc_rqst *rqst)
अणु
	वापस (काष्ठा sockaddr_in6 *) &rqst->rq_daddr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr *svc_daddr(स्थिर काष्ठा svc_rqst *rqst)
अणु
	वापस (काष्ठा sockaddr *) &rqst->rq_daddr;
पूर्ण

/*
 * Check buffer bounds after decoding arguments
 */
अटल अंतरभूत पूर्णांक
xdr_argsize_check(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	अक्षर *cp = (अक्षर *)p;
	काष्ठा kvec *vec = &rqstp->rq_arg.head[0];
	वापस cp >= (अक्षर*)vec->iov_base
		&& cp <= (अक्षर*)vec->iov_base + vec->iov_len;
पूर्ण

अटल अंतरभूत पूर्णांक
xdr_ressize_check(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा kvec *vec = &rqstp->rq_res.head[0];
	अक्षर *cp = (अक्षर*)p;

	vec->iov_len = cp - (अक्षर*)vec->iov_base;

	वापस vec->iov_len <= PAGE_SIZE;
पूर्ण

अटल अंतरभूत व्योम svc_मुक्त_res_pages(काष्ठा svc_rqst *rqstp)
अणु
	जबतक (rqstp->rq_next_page != rqstp->rq_respages) अणु
		काष्ठा page **pp = --rqstp->rq_next_page;
		अगर (*pp) अणु
			put_page(*pp);
			*pp = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा svc_deferred_req अणु
	u32			prot;	/* protocol (UDP or TCP) */
	काष्ठा svc_xprt		*xprt;
	काष्ठा sockaddr_storage	addr;	/* where reply must go */
	माप_प्रकार			addrlen;
	काष्ठा sockaddr_storage	daddr;	/* where reply must come from */
	माप_प्रकार			daddrlen;
	काष्ठा cache_deferred_req handle;
	माप_प्रकार			xprt_hlen;
	पूर्णांक			argslen;
	__be32			args[];
पूर्ण;

काष्ठा svc_process_info अणु
	जोड़ अणु
		पूर्णांक  (*dispatch)(काष्ठा svc_rqst *, __be32 *);
		काष्ठा अणु
			अचिन्हित पूर्णांक lovers;
			अचिन्हित पूर्णांक hivers;
		पूर्ण mismatch;
	पूर्ण;
पूर्ण;

/*
 * List of RPC programs on the same transport endpoपूर्णांक
 */
काष्ठा svc_program अणु
	काष्ठा svc_program *	pg_next;	/* other programs (same xprt) */
	u32			pg_prog;	/* program number */
	अचिन्हित पूर्णांक		pg_lovers;	/* lowest version */
	अचिन्हित पूर्णांक		pg_hivers;	/* highest version */
	अचिन्हित पूर्णांक		pg_nvers;	/* number of versions */
	स्थिर काष्ठा svc_version **pg_vers;	/* version array */
	अक्षर *			pg_name;	/* service name */
	अक्षर *			pg_class;	/* class name: services sharing authentication */
	काष्ठा svc_stat *	pg_stats;	/* rpc statistics */
	पूर्णांक			(*pg_authenticate)(काष्ठा svc_rqst *);
	__be32			(*pg_init_request)(काष्ठा svc_rqst *,
						   स्थिर काष्ठा svc_program *,
						   काष्ठा svc_process_info *);
	पूर्णांक			(*pg_rpcbind_set)(काष्ठा net *net,
						  स्थिर काष्ठा svc_program *,
						  u32 version, पूर्णांक family,
						  अचिन्हित लघु proto,
						  अचिन्हित लघु port);
पूर्ण;

/*
 * RPC program version
 */
काष्ठा svc_version अणु
	u32			vs_vers;	/* version number */
	u32			vs_nproc;	/* number of procedures */
	स्थिर काष्ठा svc_procedure *vs_proc;	/* per-procedure info */
	अचिन्हित पूर्णांक		*vs_count;	/* call counts */
	u32			vs_xdrsize;	/* xdrsize needed क्रम this version */

	/* Don't रेजिस्टर with rpcbind */
	bool			vs_hidden;

	/* Don't care अगर the rpcbind registration fails */
	bool			vs_rpcb_optnl;

	/* Need xprt with congestion control */
	bool			vs_need_cong_ctrl;

	/* Override dispatch function (e.g. when caching replies).
	 * A वापस value of 0 means drop the request. 
	 * vs_dispatch == शून्य means use शेष dispatcher.
	 */
	पूर्णांक			(*vs_dispatch)(काष्ठा svc_rqst *, __be32 *);
पूर्ण;

/*
 * RPC procedure info
 */
काष्ठा svc_procedure अणु
	/* process the request: */
	__be32			(*pc_func)(काष्ठा svc_rqst *);
	/* XDR decode args: */
	पूर्णांक			(*pc_decode)(काष्ठा svc_rqst *, __be32 *data);
	/* XDR encode result: */
	पूर्णांक			(*pc_encode)(काष्ठा svc_rqst *, __be32 *data);
	/* XDR मुक्त result: */
	व्योम			(*pc_release)(काष्ठा svc_rqst *);
	अचिन्हित पूर्णांक		pc_argsize;	/* argument काष्ठा size */
	अचिन्हित पूर्णांक		pc_ressize;	/* result काष्ठा size */
	अचिन्हित पूर्णांक		pc_cachetype;	/* cache info (NFS) */
	अचिन्हित पूर्णांक		pc_xdrressize;	/* maximum size of XDR reply */
	स्थिर अक्षर *		pc_name;	/* क्रम display */
पूर्ण;

/*
 * Mode क्रम mapping cpus to pools.
 */
क्रमागत अणु
	SVC_POOL_AUTO = -1,	/* choose one of the others */
	SVC_POOL_GLOBAL,	/* no mapping, just a single global pool
				 * (legacy & UP mode) */
	SVC_POOL_PERCPU,	/* one pool per cpu */
	SVC_POOL_PERNODE	/* one pool per numa node */
पूर्ण;

काष्ठा svc_pool_map अणु
	पूर्णांक count;			/* How many svc_servs use us */
	पूर्णांक mode;			/* Note: पूर्णांक not क्रमागत to aव्योम
					 * warnings about "क्रमागतeration value
					 * not handled in चयन" */
	अचिन्हित पूर्णांक npools;
	अचिन्हित पूर्णांक *pool_to;		/* maps pool id to cpu or node */
	अचिन्हित पूर्णांक *to_pool;		/* maps cpu or node to pool id */
पूर्ण;

बाह्य काष्ठा svc_pool_map svc_pool_map;

/*
 * Function prototypes.
 */
पूर्णांक svc_rpcb_setup(काष्ठा svc_serv *serv, काष्ठा net *net);
व्योम svc_rpcb_cleanup(काष्ठा svc_serv *serv, काष्ठा net *net);
पूर्णांक svc_bind(काष्ठा svc_serv *serv, काष्ठा net *net);
काष्ठा svc_serv *svc_create(काष्ठा svc_program *, अचिन्हित पूर्णांक,
			    स्थिर काष्ठा svc_serv_ops *);
काष्ठा svc_rqst *svc_rqst_alloc(काष्ठा svc_serv *serv,
					काष्ठा svc_pool *pool, पूर्णांक node);
काष्ठा svc_rqst *svc_prepare_thपढ़ो(काष्ठा svc_serv *serv,
					काष्ठा svc_pool *pool, पूर्णांक node);
व्योम		   svc_rqst_मुक्त(काष्ठा svc_rqst *);
व्योम		   svc_निकास_thपढ़ो(काष्ठा svc_rqst *);
अचिन्हित पूर्णांक	   svc_pool_map_get(व्योम);
व्योम		   svc_pool_map_put(व्योम);
काष्ठा svc_serv *  svc_create_pooled(काष्ठा svc_program *, अचिन्हित पूर्णांक,
			स्थिर काष्ठा svc_serv_ops *);
पूर्णांक		   svc_set_num_thपढ़ोs(काष्ठा svc_serv *, काष्ठा svc_pool *, पूर्णांक);
पूर्णांक		   svc_set_num_thपढ़ोs_sync(काष्ठा svc_serv *, काष्ठा svc_pool *, पूर्णांक);
पूर्णांक		   svc_pool_stats_खोलो(काष्ठा svc_serv *serv, काष्ठा file *file);
व्योम		   svc_destroy(काष्ठा svc_serv *);
व्योम		   svc_shutकरोwn_net(काष्ठा svc_serv *, काष्ठा net *);
पूर्णांक		   svc_process(काष्ठा svc_rqst *);
पूर्णांक		   bc_svc_process(काष्ठा svc_serv *, काष्ठा rpc_rqst *,
			काष्ठा svc_rqst *);
पूर्णांक		   svc_रेजिस्टर(स्थिर काष्ठा svc_serv *, काष्ठा net *, स्थिर पूर्णांक,
				स्थिर अचिन्हित लघु, स्थिर अचिन्हित लघु);

व्योम		   svc_wake_up(काष्ठा svc_serv *);
व्योम		   svc_reserve(काष्ठा svc_rqst *rqstp, पूर्णांक space);
काष्ठा svc_pool *  svc_pool_क्रम_cpu(काष्ठा svc_serv *serv, पूर्णांक cpu);
अक्षर *		   svc_prपूर्णांक_addr(काष्ठा svc_rqst *, अक्षर *, माप_प्रकार);
पूर्णांक		   svc_encode_result_payload(काष्ठा svc_rqst *rqstp,
					     अचिन्हित पूर्णांक offset,
					     अचिन्हित पूर्णांक length);
अचिन्हित पूर्णांक	   svc_fill_ग_लिखो_vector(काष्ठा svc_rqst *rqstp,
					 काष्ठा page **pages,
					 काष्ठा kvec *first, माप_प्रकार total);
अक्षर		  *svc_fill_symlink_pathname(काष्ठा svc_rqst *rqstp,
					     काष्ठा kvec *first, व्योम *p,
					     माप_प्रकार total);
__be32		   svc_वापस_autherr(काष्ठा svc_rqst *rqstp, __be32 auth_err);
__be32		   svc_generic_init_request(काष्ठा svc_rqst *rqstp,
					    स्थिर काष्ठा svc_program *progp,
					    काष्ठा svc_process_info *procinfo);
पूर्णांक		   svc_generic_rpcbind_set(काष्ठा net *net,
					   स्थिर काष्ठा svc_program *progp,
					   u32 version, पूर्णांक family,
					   अचिन्हित लघु proto,
					   अचिन्हित लघु port);
पूर्णांक		   svc_rpcbind_set_version(काष्ठा net *net,
					   स्थिर काष्ठा svc_program *progp,
					   u32 version, पूर्णांक family,
					   अचिन्हित लघु proto,
					   अचिन्हित लघु port);

#घोषणा	RPC_MAX_ADDRBUFLEN	(63U)

/*
 * When we want to reduce the size of the reserved space in the response
 * buffer, we need to take पूर्णांकo account the size of any checksum data that
 * may be at the end of the packet. This is dअगरficult to determine exactly
 * क्रम all हालs without actually generating the checksum, so we just use a
 * अटल value.
 */
अटल अंतरभूत व्योम svc_reserve_auth(काष्ठा svc_rqst *rqstp, पूर्णांक space)
अणु
	svc_reserve(rqstp, space + rqstp->rq_auth_slack);
पूर्ण

/**
 * svcxdr_init_decode - Prepare an xdr_stream क्रम svc Call decoding
 * @rqstp: controlling server RPC transaction context
 *
 */
अटल अंतरभूत व्योम svcxdr_init_decode(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा kvec *argv = rqstp->rq_arg.head;

	xdr_init_decode(xdr, &rqstp->rq_arg, argv->iov_base, शून्य);
	xdr_set_scratch_page(xdr, rqstp->rq_scratch_page);
पूर्ण

/**
 * svcxdr_init_encode - Prepare an xdr_stream क्रम svc Reply encoding
 * @rqstp: controlling server RPC transaction context
 *
 */
अटल अंतरभूत व्योम svcxdr_init_encode(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा xdr_buf *buf = &rqstp->rq_res;
	काष्ठा kvec *resv = buf->head;

	xdr_reset_scratch_buffer(xdr);

	xdr->buf = buf;
	xdr->iov = resv;
	xdr->p   = resv->iov_base + resv->iov_len;
	xdr->end = resv->iov_base + PAGE_SIZE - rqstp->rq_auth_slack;
	buf->len = resv->iov_len;
	xdr->page_ptr = buf->pages - 1;
	buf->buflen = PAGE_SIZE * (1 + rqstp->rq_page_end - buf->pages);
	buf->buflen -= rqstp->rq_auth_slack;
	xdr->rqst = शून्य;
पूर्ण

#पूर्ण_अगर /* SUNRPC_SVC_H */
