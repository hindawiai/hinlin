<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ERRQUEUE_H
#घोषणा _LINUX_ERRQUEUE_H 1


#समावेश <net/ip.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/ipv6.h>
#पूर्ण_अगर
#समावेश <uapi/linux/errqueue.h>

#घोषणा SKB_EXT_ERR(skb) ((काष्ठा sock_exterr_skb *) ((skb)->cb))

काष्ठा sock_exterr_skb अणु
	जोड़ अणु
		काष्ठा inet_skb_parm	h4;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा inet6_skb_parm	h6;
#पूर्ण_अगर
	पूर्ण header;
	काष्ठा sock_extended_err	ee;
	u16				addr_offset;
	__be16				port;
	u8				opt_stats:1,
					unused:7;
पूर्ण;

#पूर्ण_अगर
