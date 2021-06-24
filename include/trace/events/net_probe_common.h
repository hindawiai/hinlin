<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर !defined(_TRACE_NET_PROBE_COMMON_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NET_PROBE_COMMON_H

#घोषणा TP_STORE_ADDR_PORTS_V4(__entry, inet, sk)			\
	करो अणु								\
		काष्ठा sockaddr_in *v4 = (व्योम *)__entry->saddr;	\
									\
		v4->sin_family = AF_INET;				\
		v4->sin_port = inet->inet_sport;			\
		v4->sin_addr.s_addr = inet->inet_saddr;			\
		v4 = (व्योम *)__entry->daddr;				\
		v4->sin_family = AF_INET;				\
		v4->sin_port = inet->inet_dport;			\
		v4->sin_addr.s_addr = inet->inet_daddr;			\
	पूर्ण जबतक (0)

#अगर IS_ENABLED(CONFIG_IPV6)

#घोषणा TP_STORE_ADDR_PORTS(__entry, inet, sk)				\
	करो अणु								\
		अगर (sk->sk_family == AF_INET6) अणु			\
			काष्ठा sockaddr_in6 *v6 = (व्योम *)__entry->saddr; \
									\
			v6->sin6_family = AF_INET6;			\
			v6->sin6_port = inet->inet_sport;		\
			v6->sin6_addr = inet6_sk(sk)->saddr;		\
			v6 = (व्योम *)__entry->daddr;			\
			v6->sin6_family = AF_INET6;			\
			v6->sin6_port = inet->inet_dport;		\
			v6->sin6_addr = sk->sk_v6_daddr;		\
		पूर्ण अन्यथा							\
			TP_STORE_ADDR_PORTS_V4(__entry, inet, sk);	\
	पूर्ण जबतक (0)

#अन्यथा

#घोषणा TP_STORE_ADDR_PORTS(__entry, inet, sk)		\
	TP_STORE_ADDR_PORTS_V4(__entry, inet, sk);

#पूर्ण_अगर

#पूर्ण_अगर
