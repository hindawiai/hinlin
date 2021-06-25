<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IPV6_NF_REJECT_H
#घोषणा _IPV6_NF_REJECT_H

#समावेश <linux/icmpv6.h>
#समावेश <net/netfilter/nf_reject.h>

व्योम nf_send_unreach6(काष्ठा net *net, काष्ठा sk_buff *skb_in, अचिन्हित अक्षर code,
		      अचिन्हित पूर्णांक hooknum);
व्योम nf_send_reset6(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *oldskb,
		    पूर्णांक hook);
स्थिर काष्ठा tcphdr *nf_reject_ip6_tcphdr_get(काष्ठा sk_buff *oldskb,
					      काष्ठा tcphdr *otcph,
					      अचिन्हित पूर्णांक *otcplen, पूर्णांक hook);
काष्ठा ipv6hdr *nf_reject_ip6hdr_put(काष्ठा sk_buff *nskb,
				     स्थिर काष्ठा sk_buff *oldskb,
				     __u8 protocol, पूर्णांक hoplimit);
व्योम nf_reject_ip6_tcphdr_put(काष्ठा sk_buff *nskb,
			      स्थिर काष्ठा sk_buff *oldskb,
			      स्थिर काष्ठा tcphdr *oth, अचिन्हित पूर्णांक otcplen);

काष्ठा sk_buff *nf_reject_skb_v6_tcp_reset(काष्ठा net *net,
					   काष्ठा sk_buff *oldskb,
					   स्थिर काष्ठा net_device *dev,
					   पूर्णांक hook);
काष्ठा sk_buff *nf_reject_skb_v6_unreach(काष्ठा net *net,
					 काष्ठा sk_buff *oldskb,
					 स्थिर काष्ठा net_device *dev,
					 पूर्णांक hook, u8 code);

#पूर्ण_अगर /* _IPV6_NF_REJECT_H */
