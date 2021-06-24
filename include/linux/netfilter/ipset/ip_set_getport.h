<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IP_SET_GETPORT_H
#घोषणा _IP_SET_GETPORT_H

#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/in.h>

बाह्य bool ip_set_get_ip4_port(स्थिर काष्ठा sk_buff *skb, bool src,
				__be16 *port, u8 *proto);

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
बाह्य bool ip_set_get_ip6_port(स्थिर काष्ठा sk_buff *skb, bool src,
				__be16 *port, u8 *proto);
#अन्यथा
अटल अंतरभूत bool ip_set_get_ip6_port(स्थिर काष्ठा sk_buff *skb, bool src,
				       __be16 *port, u8 *proto)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool ip_set_proto_with_ports(u8 proto)
अणु
	चयन (proto) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_SCTP:
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

#पूर्ण_अगर /*_IP_SET_GETPORT_H*/
