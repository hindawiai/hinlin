<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_TABLES_IPV4_H_
#घोषणा _NF_TABLES_IPV4_H_

#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/ip.h>

अटल अंतरभूत व्योम nft_set_pktinfo_ipv4(काष्ठा nft_pktinfo *pkt,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *ip;

	ip = ip_hdr(pkt->skb);
	pkt->tprot_set = true;
	pkt->tprot = ip->protocol;
	pkt->xt.thoff = ip_hdrlen(pkt->skb);
	pkt->xt.fragoff = ntohs(ip->frag_off) & IP_OFFSET;
पूर्ण

अटल अंतरभूत पूर्णांक __nft_set_pktinfo_ipv4_validate(काष्ठा nft_pktinfo *pkt,
						  काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph, _iph;
	u32 len, thoff;

	iph = skb_header_poपूर्णांकer(skb, skb_network_offset(skb), माप(*iph),
				 &_iph);
	अगर (!iph)
		वापस -1;

	अगर (iph->ihl < 5 || iph->version != 4)
		वापस -1;

	len = ntohs(iph->tot_len);
	thoff = iph->ihl * 4;
	अगर (skb->len < len)
		वापस -1;
	अन्यथा अगर (len < thoff)
		वापस -1;

	pkt->tprot_set = true;
	pkt->tprot = iph->protocol;
	pkt->xt.thoff = thoff;
	pkt->xt.fragoff = ntohs(iph->frag_off) & IP_OFFSET;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nft_set_pktinfo_ipv4_validate(काष्ठा nft_pktinfo *pkt,
						 काष्ठा sk_buff *skb)
अणु
	अगर (__nft_set_pktinfo_ipv4_validate(pkt, skb) < 0)
		nft_set_pktinfo_unspec(pkt, skb);
पूर्ण

अटल अंतरभूत पूर्णांक nft_set_pktinfo_ipv4_ingress(काष्ठा nft_pktinfo *pkt,
					       काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph;
	u32 len, thoff;

	अगर (!pskb_may_pull(skb, माप(*iph)))
		वापस -1;

	iph = ip_hdr(skb);
	अगर (iph->ihl < 5 || iph->version != 4)
		जाओ inhdr_error;

	len = ntohs(iph->tot_len);
	thoff = iph->ihl * 4;
	अगर (skb->len < len) अणु
		__IP_INC_STATS(nft_net(pkt), IPSTATS_MIB_INTRUNCATEDPKTS);
		वापस -1;
	पूर्ण अन्यथा अगर (len < thoff) अणु
		जाओ inhdr_error;
	पूर्ण

	pkt->tprot_set = true;
	pkt->tprot = iph->protocol;
	pkt->xt.thoff = thoff;
	pkt->xt.fragoff = ntohs(iph->frag_off) & IP_OFFSET;

	वापस 0;

inhdr_error:
	__IP_INC_STATS(nft_net(pkt), IPSTATS_MIB_INHDRERRORS);
	वापस -1;
पूर्ण
#पूर्ण_अगर
