<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_RAWV6_H
#घोषणा _NET_RAWV6_H

#समावेश <net/protocol.h>

बाह्य काष्ठा raw_hashinfo raw_v6_hashinfo;
काष्ठा sock *__raw_v6_lookup(काष्ठा net *net, काष्ठा sock *sk,
			     अचिन्हित लघु num, स्थिर काष्ठा in6_addr *loc_addr,
			     स्थिर काष्ठा in6_addr *rmt_addr, पूर्णांक dअगर, पूर्णांक sdअगर);

पूर्णांक raw_पात(काष्ठा sock *sk, पूर्णांक err);

व्योम raw6_icmp_error(काष्ठा sk_buff *, पूर्णांक nexthdr,
		u8 type, u8 code, पूर्णांक inner_offset, __be32);
bool raw6_local_deliver(काष्ठा sk_buff *, पूर्णांक);

पूर्णांक rawv6_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);

#अगर defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
पूर्णांक rawv6_mh_filter_रेजिस्टर(पूर्णांक (*filter)(काष्ठा sock *sock,
					   काष्ठा sk_buff *skb));
पूर्णांक rawv6_mh_filter_unरेजिस्टर(पूर्णांक (*filter)(काष्ठा sock *sock,
					     काष्ठा sk_buff *skb));
#पूर्ण_अगर

#पूर्ण_अगर
