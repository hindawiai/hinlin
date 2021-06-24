<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/sunrpc/xprtsock.h
 *
 *  Declarations क्रम the RPC transport socket provider.
 */

#अगर_अघोषित _LINUX_SUNRPC_XPRTSOCK_H
#घोषणा _LINUX_SUNRPC_XPRTSOCK_H

पूर्णांक		init_socket_xprt(व्योम);
व्योम		cleanup_socket_xprt(व्योम);

#घोषणा RPC_MIN_RESVPORT	(1U)
#घोषणा RPC_MAX_RESVPORT	(65535U)
#घोषणा RPC_DEF_MIN_RESVPORT	(665U)
#घोषणा RPC_DEF_MAX_RESVPORT	(1023U)

काष्ठा sock_xprt अणु
	काष्ठा rpc_xprt		xprt;

	/*
	 * Network layer
	 */
	काष्ठा socket *		sock;
	काष्ठा sock *		inet;
	काष्ठा file *		file;

	/*
	 * State of TCP reply receive
	 */
	काष्ठा अणु
		काष्ठा अणु
			__be32	fraghdr,
				xid,
				calldir;
		पूर्ण __attribute__((packed));

		u32		offset,
				len;

		अचिन्हित दीर्घ	copied;
	पूर्ण recv;

	/*
	 * State of TCP transmit queue
	 */
	काष्ठा अणु
		u32		offset;
	पूर्ण xmit;

	/*
	 * Connection of transports
	 */
	अचिन्हित दीर्घ		sock_state;
	काष्ठा delayed_work	connect_worker;
	काष्ठा work_काष्ठा	error_worker;
	काष्ठा work_काष्ठा	recv_worker;
	काष्ठा mutex		recv_mutex;
	काष्ठा sockaddr_storage	srcaddr;
	अचिन्हित लघु		srcport;
	पूर्णांक			xprt_err;

	/*
	 * UDP socket buffer size parameters
	 */
	माप_प्रकार			rcvsize,
				sndsize;

	काष्ठा rpc_समयout	tcp_समयout;

	/*
	 * Saved socket callback addresses
	 */
	व्योम			(*old_data_पढ़ोy)(काष्ठा sock *);
	व्योम			(*old_state_change)(काष्ठा sock *);
	व्योम			(*old_ग_लिखो_space)(काष्ठा sock *);
	व्योम			(*old_error_report)(काष्ठा sock *);
पूर्ण;

/*
 * TCP RPC flags
 */
#घोषणा XPRT_SOCK_CONNECTING	1U
#घोषणा XPRT_SOCK_DATA_READY	(2)
#घोषणा XPRT_SOCK_UPD_TIMEOUT	(3)
#घोषणा XPRT_SOCK_WAKE_ERROR	(4)
#घोषणा XPRT_SOCK_WAKE_WRITE	(5)
#घोषणा XPRT_SOCK_WAKE_PENDING	(6)
#घोषणा XPRT_SOCK_WAKE_DISCONNECT	(7)

#पूर्ण_अगर /* _LINUX_SUNRPC_XPRTSOCK_H */
