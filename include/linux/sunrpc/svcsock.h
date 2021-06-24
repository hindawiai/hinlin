<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/svcsock.h
 *
 * RPC server socket I/O.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित SUNRPC_SVCSOCK_H
#घोषणा SUNRPC_SVCSOCK_H

#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/svc_xprt.h>

/*
 * RPC server socket.
 */
काष्ठा svc_sock अणु
	काष्ठा svc_xprt		sk_xprt;
	काष्ठा socket *		sk_sock;	/* berkeley socket layer */
	काष्ठा sock *		sk_sk;		/* INET layer */

	/* We keep the old state_change and data_पढ़ोy CB's here */
	व्योम			(*sk_ostate)(काष्ठा sock *);
	व्योम			(*sk_odata)(काष्ठा sock *);
	व्योम			(*sk_owspace)(काष्ठा sock *);

	/* निजी TCP part */
	/* On-the-wire fragment header: */
	__be32			sk_marker;
	/* As we receive a record, this includes the length received so
	 * far (including the fragment header): */
	u32			sk_tcplen;
	/* Total length of the data (not including fragment headers)
	 * received so far in the fragments making up this rpc: */
	u32			sk_datalen;
	/* Number of queued send requests */
	atomic_t		sk_sendqlen;

	काष्ठा page *		sk_pages[RPCSVC_MAXPAGES];	/* received data */
पूर्ण;

अटल अंतरभूत u32 svc_sock_reclen(काष्ठा svc_sock *svsk)
अणु
	वापस be32_to_cpu(svsk->sk_marker) & RPC_FRAGMENT_SIZE_MASK;
पूर्ण

अटल अंतरभूत u32 svc_sock_final_rec(काष्ठा svc_sock *svsk)
अणु
	वापस be32_to_cpu(svsk->sk_marker) & RPC_LAST_STREAM_FRAGMENT;
पूर्ण

/*
 * Function prototypes.
 */
व्योम		svc_बंद_net(काष्ठा svc_serv *, काष्ठा net *);
पूर्णांक		svc_recv(काष्ठा svc_rqst *, दीर्घ);
पूर्णांक		svc_send(काष्ठा svc_rqst *);
व्योम		svc_drop(काष्ठा svc_rqst *);
व्योम		svc_sock_update_bufs(काष्ठा svc_serv *serv);
bool		svc_alien_sock(काष्ठा net *net, पूर्णांक fd);
पूर्णांक		svc_addsock(काष्ठा svc_serv *serv, स्थिर पूर्णांक fd,
					अक्षर *name_वापस, स्थिर माप_प्रकार len,
					स्थिर काष्ठा cred *cred);
व्योम		svc_init_xprt_sock(व्योम);
व्योम		svc_cleanup_xprt_sock(व्योम);
काष्ठा svc_xprt *svc_sock_create(काष्ठा svc_serv *serv, पूर्णांक prot);
व्योम		svc_sock_destroy(काष्ठा svc_xprt *);

/*
 * svc_makesock socket अक्षरacteristics
 */
#घोषणा SVC_SOCK_DEFAULTS	(0U)
#घोषणा SVC_SOCK_ANONYMOUS	(1U << 0)	/* करोn't रेजिस्टर with pmap */
#घोषणा SVC_SOCK_TEMPORARY	(1U << 1)	/* flag socket as temporary */

#पूर्ण_अगर /* SUNRPC_SVCSOCK_H */
