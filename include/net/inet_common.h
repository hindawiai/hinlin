<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _INET_COMMON_H
#घोषणा _INET_COMMON_H

#समावेश <linux/indirect_call_wrapper.h>

बाह्य स्थिर काष्ठा proto_ops inet_stream_ops;
बाह्य स्थिर काष्ठा proto_ops inet_dgram_ops;

/*
 *	INET4 prototypes used by INET6
 */

काष्ठा msghdr;
काष्ठा sock;
काष्ठा sockaddr;
काष्ठा socket;

पूर्णांक inet_release(काष्ठा socket *sock);
पूर्णांक inet_stream_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			पूर्णांक addr_len, पूर्णांक flags);
पूर्णांक __inet_stream_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			  पूर्णांक addr_len, पूर्णांक flags, पूर्णांक is_sendmsg);
पूर्णांक inet_dgram_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		       पूर्णांक addr_len, पूर्णांक flags);
पूर्णांक inet_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		bool kern);
पूर्णांक inet_send_prepare(काष्ठा sock *sk);
पूर्णांक inet_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size);
sमाप_प्रकार inet_sendpage(काष्ठा socket *sock, काष्ठा page *page, पूर्णांक offset,
		      माप_प्रकार size, पूर्णांक flags);
पूर्णांक inet_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		 पूर्णांक flags);
पूर्णांक inet_shutकरोwn(काष्ठा socket *sock, पूर्णांक how);
पूर्णांक inet_listen(काष्ठा socket *sock, पूर्णांक backlog);
व्योम inet_sock_deकाष्ठा(काष्ठा sock *sk);
पूर्णांक inet_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);
/* Don't allocate port at this moment, defer to connect. */
#घोषणा BIND_FORCE_ADDRESS_NO_PORT	(1 << 0)
/* Grab and release socket lock. */
#घोषणा BIND_WITH_LOCK			(1 << 1)
/* Called from BPF program. */
#घोषणा BIND_FROM_BPF			(1 << 2)
/* Skip CAP_NET_BIND_SERVICE check. */
#घोषणा BIND_NO_CAP_NET_BIND_SERVICE	(1 << 3)
पूर्णांक __inet_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len,
		u32 flags);
पूर्णांक inet_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		 पूर्णांक peer);
पूर्णांक inet_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक inet_ctl_sock_create(काष्ठा sock **sk, अचिन्हित लघु family,
			 अचिन्हित लघु type, अचिन्हित अक्षर protocol,
			 काष्ठा net *net);
पूर्णांक inet_recv_error(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len,
		    पूर्णांक *addr_len);

काष्ठा sk_buff *inet_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb);
पूर्णांक inet_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff);
काष्ठा sk_buff *inet_gso_segment(काष्ठा sk_buff *skb,
				 netdev_features_t features);

अटल अंतरभूत व्योम inet_ctl_sock_destroy(काष्ठा sock *sk)
अणु
	अगर (sk)
		sock_release(sk->sk_socket);
पूर्ण

#घोषणा indirect_call_gro_receive(f2, f1, cb, head, skb)	\
(अणु								\
	unlikely(gro_recursion_inc_test(skb)) ?			\
		NAPI_GRO_CB(skb)->flush |= 1, शून्य :		\
		INसूचीECT_CALL_2(cb, f2, f1, head, skb);		\
पूर्ण)

#पूर्ण_अगर
