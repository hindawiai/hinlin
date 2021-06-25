<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_TABLES_IPV6_H_
#घोषणा _NF_TABLES_IPV6_H_

#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <net/ipv6.h>
#समावेश <net/netfilter/nf_tables.h>

अटल अंतरभूत व्योम nft_set_pktinfo_ipv6(काष्ठा nft_pktinfo *pkt,
					काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक flags = IP6_FH_F_AUTH;
	पूर्णांक protohdr, thoff = 0;
	अचिन्हित लघु frag_off;

	protohdr = ipv6_find_hdr(pkt->skb, &thoff, -1, &frag_off, &flags);
	अगर (protohdr < 0) अणु
		nft_set_pktinfo_unspec(pkt, skb);
		वापस;
	पूर्ण

	pkt->tprot_set = true;
	pkt->tprot = protohdr;
	pkt->xt.thoff = thoff;
	pkt->xt.fragoff = frag_off;
पूर्ण

अटल अंतरभूत पूर्णांक __nft_set_pktinfo_ipv6_validate(काष्ठा nft_pktinfo *pkt,
						  काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अचिन्हित पूर्णांक flags = IP6_FH_F_AUTH;
	काष्ठा ipv6hdr *ip6h, _ip6h;
	अचिन्हित पूर्णांक thoff = 0;
	अचिन्हित लघु frag_off;
	पूर्णांक protohdr;
	u32 pkt_len;

	ip6h = skb_header_poपूर्णांकer(skb, skb_network_offset(skb), माप(*ip6h),
				  &_ip6h);
	अगर (!ip6h)
		वापस -1;

	अगर (ip6h->version != 6)
		वापस -1;

	pkt_len = ntohs(ip6h->payload_len);
	अगर (pkt_len + माप(*ip6h) > skb->len)
		वापस -1;

	protohdr = ipv6_find_hdr(pkt->skb, &thoff, -1, &frag_off, &flags);
	अगर (protohdr < 0)
		वापस -1;

	pkt->tprot_set = true;
	pkt->tprot = protohdr;
	pkt->xt.thoff = thoff;
	pkt->xt.fragoff = frag_off;

	वापस 0;
#अन्यथा
	वापस -1;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम nft_set_pktinfo_ipv6_validate(काष्ठा nft_pktinfo *pkt,
						 काष्ठा sk_buff *skb)
अणु
	अगर (__nft_set_pktinfo_ipv6_validate(pkt, skb) < 0)
		nft_set_pktinfo_unspec(pkt, skb);
पूर्ण

अटल अंतरभूत पूर्णांक nft_set_pktinfo_ipv6_ingress(काष्ठा nft_pktinfo *pkt,
					       काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अचिन्हित पूर्णांक flags = IP6_FH_F_AUTH;
	अचिन्हित लघु frag_off;
	अचिन्हित पूर्णांक thoff = 0;
	काष्ठा inet6_dev *idev;
	काष्ठा ipv6hdr *ip6h;
	पूर्णांक protohdr;
	u32 pkt_len;

	अगर (!pskb_may_pull(skb, माप(*ip6h)))
		वापस -1;

	ip6h = ipv6_hdr(skb);
	अगर (ip6h->version != 6)
		जाओ inhdr_error;

	pkt_len = ntohs(ip6h->payload_len);
	अगर (pkt_len + माप(*ip6h) > skb->len) अणु
		idev = __in6_dev_get(nft_in(pkt));
		__IP6_INC_STATS(nft_net(pkt), idev, IPSTATS_MIB_INTRUNCATEDPKTS);
		वापस -1;
	पूर्ण

	protohdr = ipv6_find_hdr(pkt->skb, &thoff, -1, &frag_off, &flags);
	अगर (protohdr < 0)
		जाओ inhdr_error;

	pkt->tprot_set = true;
	pkt->tprot = protohdr;
	pkt->xt.thoff = thoff;
	pkt->xt.fragoff = frag_off;

	वापस 0;

inhdr_error:
	idev = __in6_dev_get(nft_in(pkt));
	__IP6_INC_STATS(nft_net(pkt), idev, IPSTATS_MIB_INHDRERRORS);
	वापस -1;
#अन्यथा
	वापस -1;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर
