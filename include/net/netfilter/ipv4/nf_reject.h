<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IPV4_NF_REJECT_H
#घोषणा _IPV4_NF_REJECT_H

#समावेश <linux/skbuff.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/netfilter/nf_reject.h>

व्योम nf_send_unreach(काष्ठा sk_buff *skb_in, पूर्णांक code, पूर्णांक hook);
व्योम nf_send_reset(काष्ठा net *net, काष्ठा sock *, काष्ठा sk_buff *oldskb,
		   पूर्णांक hook);
स्थिर काष्ठा tcphdr *nf_reject_ip_tcphdr_get(काष्ठा sk_buff *oldskb,
					     काष्ठा tcphdr *_oth, पूर्णांक hook);
काष्ठा iphdr *nf_reject_iphdr_put(काष्ठा sk_buff *nskb,
				  स्थिर काष्ठा sk_buff *oldskb,
				  __u8 protocol, पूर्णांक ttl);
व्योम nf_reject_ip_tcphdr_put(काष्ठा sk_buff *nskb, स्थिर काष्ठा sk_buff *oldskb,
			     स्थिर काष्ठा tcphdr *oth);

काष्ठा sk_buff *nf_reject_skb_v4_unreach(काष्ठा net *net,
                                         काष्ठा sk_buff *oldskb,
                                         स्थिर काष्ठा net_device *dev,
                                         पूर्णांक hook, u8 code);
काष्ठा sk_buff *nf_reject_skb_v4_tcp_reset(काष्ठा net *net,
					   काष्ठा sk_buff *oldskb,
					   स्थिर काष्ठा net_device *dev,
					   पूर्णांक hook);


#पूर्ण_अगर /* _IPV4_NF_REJECT_H */
