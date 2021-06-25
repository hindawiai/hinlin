<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

#अगर_अघोषित _NET_IPV6_GRO_H
#घोषणा _NET_IPV6_GRO_H

#समावेश <linux/indirect_call_wrapper.h>

काष्ठा list_head;
काष्ठा sk_buff;

INसूचीECT_CALLABLE_DECLARE(काष्ठा sk_buff *ipv6_gro_receive(काष्ठा list_head *,
							   काष्ठा sk_buff *));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक ipv6_gro_complete(काष्ठा sk_buff *, पूर्णांक));
INसूचीECT_CALLABLE_DECLARE(काष्ठा sk_buff *inet_gro_receive(काष्ठा list_head *,
							   काष्ठा sk_buff *));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक inet_gro_complete(काष्ठा sk_buff *, पूर्णांक));

#घोषणा indirect_call_gro_receive_inet(cb, f2, f1, head, skb)	\
(अणु								\
	unlikely(gro_recursion_inc_test(skb)) ?			\
		NAPI_GRO_CB(skb)->flush |= 1, शून्य :		\
		INसूचीECT_CALL_INET(cb, f2, f1, head, skb);	\
पूर्ण)

#पूर्ण_अगर /* _NET_IPV6_GRO_H */
