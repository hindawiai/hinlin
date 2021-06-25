<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1995-1997 Olaf Kirch <okir@monad.swb.de>
 * Copyright (C) 2020, Oracle.
 */

#अगर_अघोषित _NET_SUNRPC_SOCKLIB_H_
#घोषणा _NET_SUNRPC_SOCKLIB_H_

पूर्णांक csum_partial_copy_to_xdr(काष्ठा xdr_buf *xdr, काष्ठा sk_buff *skb);
पूर्णांक xprt_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
		      काष्ठा xdr_buf *xdr, अचिन्हित पूर्णांक base,
		      rpc_fraghdr marker, अचिन्हित पूर्णांक *sent_p);

#पूर्ण_अगर /* _NET_SUNRPC_SOCKLIB_H_ */
