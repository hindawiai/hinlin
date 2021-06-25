<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/ipv6.h>
#समावेश <net/dsfield.h>
#समावेश <net/xfrm.h>

#अगर_अघोषित XFRM_INOUT_H
#घोषणा XFRM_INOUT_H 1

अटल अंतरभूत व्योम xfrm4_extract_header(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

	XFRM_MODE_SKB_CB(skb)->ihl = माप(*iph);
	XFRM_MODE_SKB_CB(skb)->id = iph->id;
	XFRM_MODE_SKB_CB(skb)->frag_off = iph->frag_off;
	XFRM_MODE_SKB_CB(skb)->tos = iph->tos;
	XFRM_MODE_SKB_CB(skb)->ttl = iph->ttl;
	XFRM_MODE_SKB_CB(skb)->optlen = iph->ihl * 4 - माप(*iph);
	स_रखो(XFRM_MODE_SKB_CB(skb)->flow_lbl, 0,
	       माप(XFRM_MODE_SKB_CB(skb)->flow_lbl));
पूर्ण

अटल अंतरभूत व्योम xfrm6_extract_header(काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);

	XFRM_MODE_SKB_CB(skb)->ihl = माप(*iph);
	XFRM_MODE_SKB_CB(skb)->id = 0;
	XFRM_MODE_SKB_CB(skb)->frag_off = htons(IP_DF);
	XFRM_MODE_SKB_CB(skb)->tos = ipv6_get_dsfield(iph);
	XFRM_MODE_SKB_CB(skb)->ttl = iph->hop_limit;
	XFRM_MODE_SKB_CB(skb)->optlen = 0;
	स_नकल(XFRM_MODE_SKB_CB(skb)->flow_lbl, iph->flow_lbl,
	       माप(XFRM_MODE_SKB_CB(skb)->flow_lbl));
#अन्यथा
	WARN_ON_ONCE(1);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम xfrm6_beet_make_header(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);

	iph->version = 6;

	स_नकल(iph->flow_lbl, XFRM_MODE_SKB_CB(skb)->flow_lbl,
	       माप(iph->flow_lbl));
	iph->nexthdr = XFRM_MODE_SKB_CB(skb)->protocol;

	ipv6_change_dsfield(iph, 0, XFRM_MODE_SKB_CB(skb)->tos);
	iph->hop_limit = XFRM_MODE_SKB_CB(skb)->ttl;
पूर्ण

अटल अंतरभूत व्योम xfrm4_beet_make_header(काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);

	iph->ihl = 5;
	iph->version = 4;

	iph->protocol = XFRM_MODE_SKB_CB(skb)->protocol;
	iph->tos = XFRM_MODE_SKB_CB(skb)->tos;

	iph->id = XFRM_MODE_SKB_CB(skb)->id;
	iph->frag_off = XFRM_MODE_SKB_CB(skb)->frag_off;
	iph->ttl = XFRM_MODE_SKB_CB(skb)->ttl;
पूर्ण

#पूर्ण_अगर
