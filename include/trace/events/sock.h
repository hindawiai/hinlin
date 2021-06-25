<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM sock

#अगर !defined(_TRACE_SOCK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SOCK_H

#समावेश <net/sock.h>
#समावेश <net/ipv6.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>

#घोषणा family_names			\
		EM(AF_INET)				\
		EMe(AF_INET6)

/* The protocol traced by inet_sock_set_state */
#घोषणा inet_protocol_names		\
		EM(IPPROTO_TCP)			\
		EM(IPPROTO_DCCP)		\
		EM(IPPROTO_SCTP)		\
		EMe(IPPROTO_MPTCP)

#घोषणा tcp_state_names			\
		EM(TCP_ESTABLISHED)		\
		EM(TCP_SYN_SENT)		\
		EM(TCP_SYN_RECV)		\
		EM(TCP_FIN_WAIT1)		\
		EM(TCP_FIN_WAIT2)		\
		EM(TCP_TIME_WAIT)		\
		EM(TCP_CLOSE)			\
		EM(TCP_CLOSE_WAIT)		\
		EM(TCP_LAST_ACK)		\
		EM(TCP_LISTEN)			\
		EM(TCP_CLOSING)			\
		EMe(TCP_NEW_SYN_RECV)

#घोषणा skmem_kind_names			\
		EM(SK_MEM_SEND)			\
		EMe(SK_MEM_RECV)

/* क्रमागतs need to be exported to user space */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a)       TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a)      TRACE_DEFINE_ENUM(a);

family_names
inet_protocol_names
tcp_state_names
skmem_kind_names

#अघोषित EM
#अघोषित EMe
#घोषणा EM(a)       अणु a, #a पूर्ण,
#घोषणा EMe(a)      अणु a, #a पूर्ण

#घोषणा show_family_name(val)			\
	__prपूर्णांक_symbolic(val, family_names)

#घोषणा show_inet_protocol_name(val)    \
	__prपूर्णांक_symbolic(val, inet_protocol_names)

#घोषणा show_tcp_state_name(val)        \
	__prपूर्णांक_symbolic(val, tcp_state_names)

#घोषणा show_skmem_kind_names(val)	\
	__prपूर्णांक_symbolic(val, skmem_kind_names)

TRACE_EVENT(sock_rcvqueue_full,

	TP_PROTO(काष्ठा sock *sk, काष्ठा sk_buff *skb),

	TP_ARGS(sk, skb),

	TP_STRUCT__entry(
		__field(पूर्णांक, rmem_alloc)
		__field(अचिन्हित पूर्णांक, truesize)
		__field(पूर्णांक, sk_rcvbuf)
	),

	TP_fast_assign(
		__entry->rmem_alloc = atomic_पढ़ो(&sk->sk_rmem_alloc);
		__entry->truesize   = skb->truesize;
		__entry->sk_rcvbuf  = READ_ONCE(sk->sk_rcvbuf);
	),

	TP_prपूर्णांकk("rmem_alloc=%d truesize=%u sk_rcvbuf=%d",
		__entry->rmem_alloc, __entry->truesize, __entry->sk_rcvbuf)
);

TRACE_EVENT(sock_exceed_buf_limit,

	TP_PROTO(काष्ठा sock *sk, काष्ठा proto *prot, दीर्घ allocated, पूर्णांक kind),

	TP_ARGS(sk, prot, allocated, kind),

	TP_STRUCT__entry(
		__array(अक्षर, name, 32)
		__field(दीर्घ *, sysctl_mem)
		__field(दीर्घ, allocated)
		__field(पूर्णांक, sysctl_rmem)
		__field(पूर्णांक, rmem_alloc)
		__field(पूर्णांक, sysctl_wmem)
		__field(पूर्णांक, wmem_alloc)
		__field(पूर्णांक, wmem_queued)
		__field(पूर्णांक, kind)
	),

	TP_fast_assign(
		म_नकलन(__entry->name, prot->name, 32);
		__entry->sysctl_mem = prot->sysctl_mem;
		__entry->allocated = allocated;
		__entry->sysctl_rmem = sk_get_rmem0(sk, prot);
		__entry->rmem_alloc = atomic_पढ़ो(&sk->sk_rmem_alloc);
		__entry->sysctl_wmem = sk_get_wmem0(sk, prot);
		__entry->wmem_alloc = refcount_पढ़ो(&sk->sk_wmem_alloc);
		__entry->wmem_queued = READ_ONCE(sk->sk_wmem_queued);
		__entry->kind = kind;
	),

	TP_prपूर्णांकk("proto:%s sysctl_mem=%ld,%ld,%ld allocated=%ld sysctl_rmem=%d rmem_alloc=%d sysctl_wmem=%d wmem_alloc=%d wmem_queued=%d kind=%s",
		__entry->name,
		__entry->sysctl_mem[0],
		__entry->sysctl_mem[1],
		__entry->sysctl_mem[2],
		__entry->allocated,
		__entry->sysctl_rmem,
		__entry->rmem_alloc,
		__entry->sysctl_wmem,
		__entry->wmem_alloc,
		__entry->wmem_queued,
		show_skmem_kind_names(__entry->kind)
	)
);

TRACE_EVENT(inet_sock_set_state,

	TP_PROTO(स्थिर काष्ठा sock *sk, स्थिर पूर्णांक oldstate, स्थिर पूर्णांक newstate),

	TP_ARGS(sk, oldstate, newstate),

	TP_STRUCT__entry(
		__field(स्थिर व्योम *, skaddr)
		__field(पूर्णांक, oldstate)
		__field(पूर्णांक, newstate)
		__field(__u16, sport)
		__field(__u16, dport)
		__field(__u16, family)
		__field(__u16, protocol)
		__array(__u8, saddr, 4)
		__array(__u8, daddr, 4)
		__array(__u8, saddr_v6, 16)
		__array(__u8, daddr_v6, 16)
	),

	TP_fast_assign(
		काष्ठा inet_sock *inet = inet_sk(sk);
		काष्ठा in6_addr *pin6;
		__be32 *p32;

		__entry->skaddr = sk;
		__entry->oldstate = oldstate;
		__entry->newstate = newstate;

		__entry->family = sk->sk_family;
		__entry->protocol = sk->sk_protocol;
		__entry->sport = ntohs(inet->inet_sport);
		__entry->dport = ntohs(inet->inet_dport);

		p32 = (__be32 *) __entry->saddr;
		*p32 = inet->inet_saddr;

		p32 = (__be32 *) __entry->daddr;
		*p32 =  inet->inet_daddr;

#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (sk->sk_family == AF_INET6) अणु
			pin6 = (काष्ठा in6_addr *)__entry->saddr_v6;
			*pin6 = sk->sk_v6_rcv_saddr;
			pin6 = (काष्ठा in6_addr *)__entry->daddr_v6;
			*pin6 = sk->sk_v6_daddr;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			pin6 = (काष्ठा in6_addr *)__entry->saddr_v6;
			ipv6_addr_set_v4mapped(inet->inet_saddr, pin6);
			pin6 = (काष्ठा in6_addr *)__entry->daddr_v6;
			ipv6_addr_set_v4mapped(inet->inet_daddr, pin6);
		पूर्ण
	),

	TP_prपूर्णांकk("family=%s protocol=%s sport=%hu dport=%hu saddr=%pI4 daddr=%pI4 saddrv6=%pI6c daddrv6=%pI6c oldstate=%s newstate=%s",
			show_family_name(__entry->family),
			show_inet_protocol_name(__entry->protocol),
			__entry->sport, __entry->dport,
			__entry->saddr, __entry->daddr,
			__entry->saddr_v6, __entry->daddr_v6,
			show_tcp_state_name(__entry->oldstate),
			show_tcp_state_name(__entry->newstate))
);

#पूर्ण_अगर /* _TRACE_SOCK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
