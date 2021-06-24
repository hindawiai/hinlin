<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * RPC client multipathing definitions
 *
 * Copyright (c) 2015, 2016, Primary Data, Inc. All rights reserved.
 *
 * Trond Myklebust <trond.myklebust@primarydata.com>
 */
#अगर_अघोषित _NET_SUNRPC_XPRTMULTIPATH_H
#घोषणा _NET_SUNRPC_XPRTMULTIPATH_H

काष्ठा rpc_xprt_iter_ops;
काष्ठा rpc_xprt_चयन अणु
	spinlock_t		xps_lock;
	काष्ठा kref		xps_kref;

	अचिन्हित पूर्णांक		xps_nxprts;
	अचिन्हित पूर्णांक		xps_nactive;
	atomic_दीर्घ_t		xps_queuelen;
	काष्ठा list_head	xps_xprt_list;

	काष्ठा net *		xps_net;

	स्थिर काष्ठा rpc_xprt_iter_ops *xps_iter_ops;

	काष्ठा rcu_head		xps_rcu;
पूर्ण;

काष्ठा rpc_xprt_iter अणु
	काष्ठा rpc_xprt_चयन __rcu *xpi_xpचयन;
	काष्ठा rpc_xprt *	xpi_cursor;

	स्थिर काष्ठा rpc_xprt_iter_ops *xpi_ops;
पूर्ण;


काष्ठा rpc_xprt_iter_ops अणु
	व्योम (*xpi_शुरुआत)(काष्ठा rpc_xprt_iter *);
	काष्ठा rpc_xprt *(*xpi_xprt)(काष्ठा rpc_xprt_iter *);
	काष्ठा rpc_xprt *(*xpi_next)(काष्ठा rpc_xprt_iter *);
पूर्ण;

बाह्य काष्ठा rpc_xprt_चयन *xprt_चयन_alloc(काष्ठा rpc_xprt *xprt,
		gfp_t gfp_flags);

बाह्य काष्ठा rpc_xprt_चयन *xprt_चयन_get(काष्ठा rpc_xprt_चयन *xps);
बाह्य व्योम xprt_चयन_put(काष्ठा rpc_xprt_चयन *xps);

बाह्य व्योम rpc_xprt_चयन_set_roundrobin(काष्ठा rpc_xprt_चयन *xps);

बाह्य व्योम rpc_xprt_चयन_add_xprt(काष्ठा rpc_xprt_चयन *xps,
		काष्ठा rpc_xprt *xprt);
बाह्य व्योम rpc_xprt_चयन_हटाओ_xprt(काष्ठा rpc_xprt_चयन *xps,
		काष्ठा rpc_xprt *xprt);

बाह्य व्योम xprt_iter_init(काष्ठा rpc_xprt_iter *xpi,
		काष्ठा rpc_xprt_चयन *xps);

बाह्य व्योम xprt_iter_init_listall(काष्ठा rpc_xprt_iter *xpi,
		काष्ठा rpc_xprt_चयन *xps);

बाह्य व्योम xprt_iter_destroy(काष्ठा rpc_xprt_iter *xpi);

बाह्य काष्ठा rpc_xprt_चयन *xprt_iter_xchg_चयन(
		काष्ठा rpc_xprt_iter *xpi,
		काष्ठा rpc_xprt_चयन *newचयन);

बाह्य काष्ठा rpc_xprt *xprt_iter_xprt(काष्ठा rpc_xprt_iter *xpi);
बाह्य काष्ठा rpc_xprt *xprt_iter_get_xprt(काष्ठा rpc_xprt_iter *xpi);
बाह्य काष्ठा rpc_xprt *xprt_iter_get_next(काष्ठा rpc_xprt_iter *xpi);

बाह्य bool rpc_xprt_चयन_has_addr(काष्ठा rpc_xprt_चयन *xps,
		स्थिर काष्ठा sockaddr *sap);
#पूर्ण_अगर
