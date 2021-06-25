<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_ip
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  April, 2002
 *
 *  Changes:
 *    added ip-sport and ip-dport
 *    Innominate Security Technologies AG <mhopf@innominate.com>
 *    September, 2002
 */
#समावेश <linux/ip.h>
#समावेश <net/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_ip.h>

जोड़ pkthdr अणु
	काष्ठा अणु
		__be16 src;
		__be16 dst;
	पूर्ण tcpudphdr;
	काष्ठा अणु
		u8 type;
		u8 code;
	पूर्ण icmphdr;
	काष्ठा अणु
		u8 type;
	पूर्ण igmphdr;
पूर्ण;

अटल bool
ebt_ip_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_ip_info *info = par->matchinfo;
	स्थिर काष्ठा iphdr *ih;
	काष्ठा iphdr _iph;
	स्थिर जोड़ pkthdr *pptr;
	जोड़ pkthdr _pkthdr;

	ih = skb_header_poपूर्णांकer(skb, 0, माप(_iph), &_iph);
	अगर (ih == शून्य)
		वापस false;
	अगर ((info->biपंचांगask & EBT_IP_TOS) &&
	    NF_INVF(info, EBT_IP_TOS, info->tos != ih->tos))
		वापस false;
	अगर ((info->biपंचांगask & EBT_IP_SOURCE) &&
	    NF_INVF(info, EBT_IP_SOURCE,
		    (ih->saddr & info->smsk) != info->saddr))
		वापस false;
	अगर ((info->biपंचांगask & EBT_IP_DEST) &&
	    NF_INVF(info, EBT_IP_DEST,
		    (ih->daddr & info->dmsk) != info->daddr))
		वापस false;
	अगर (info->biपंचांगask & EBT_IP_PROTO) अणु
		अगर (NF_INVF(info, EBT_IP_PROTO, info->protocol != ih->protocol))
			वापस false;
		अगर (!(info->biपंचांगask & (EBT_IP_DPORT | EBT_IP_SPORT |
				       EBT_IP_ICMP | EBT_IP_IGMP)))
			वापस true;
		अगर (ntohs(ih->frag_off) & IP_OFFSET)
			वापस false;

		/* min icmp/igmp headersize is 4, so माप(_pkthdr) is ok. */
		pptr = skb_header_poपूर्णांकer(skb, ih->ihl*4,
					  माप(_pkthdr), &_pkthdr);
		अगर (pptr == शून्य)
			वापस false;
		अगर (info->biपंचांगask & EBT_IP_DPORT) अणु
			u32 dst = ntohs(pptr->tcpudphdr.dst);
			अगर (NF_INVF(info, EBT_IP_DPORT,
				    dst < info->dport[0] ||
				    dst > info->dport[1]))
				वापस false;
		पूर्ण
		अगर (info->biपंचांगask & EBT_IP_SPORT) अणु
			u32 src = ntohs(pptr->tcpudphdr.src);
			अगर (NF_INVF(info, EBT_IP_SPORT,
				    src < info->sport[0] ||
				    src > info->sport[1]))
				वापस false;
		पूर्ण
		अगर ((info->biपंचांगask & EBT_IP_ICMP) &&
		    NF_INVF(info, EBT_IP_ICMP,
			    pptr->icmphdr.type < info->icmp_type[0] ||
			    pptr->icmphdr.type > info->icmp_type[1] ||
			    pptr->icmphdr.code < info->icmp_code[0] ||
			    pptr->icmphdr.code > info->icmp_code[1]))
			वापस false;
		अगर ((info->biपंचांगask & EBT_IP_IGMP) &&
		    NF_INVF(info, EBT_IP_IGMP,
			    pptr->igmphdr.type < info->igmp_type[0] ||
			    pptr->igmphdr.type > info->igmp_type[1]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक ebt_ip_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ebt_ip_info *info = par->matchinfo;
	स्थिर काष्ठा ebt_entry *e = par->entryinfo;

	अगर (e->ethproto != htons(ETH_P_IP) ||
	   e->invflags & EBT_IPROTO)
		वापस -EINVAL;
	अगर (info->biपंचांगask & ~EBT_IP_MASK || info->invflags & ~EBT_IP_MASK)
		वापस -EINVAL;
	अगर (info->biपंचांगask & (EBT_IP_DPORT | EBT_IP_SPORT)) अणु
		अगर (info->invflags & EBT_IP_PROTO)
			वापस -EINVAL;
		अगर (info->protocol != IPPROTO_TCP &&
		    info->protocol != IPPROTO_UDP &&
		    info->protocol != IPPROTO_UDPLITE &&
		    info->protocol != IPPROTO_SCTP &&
		    info->protocol != IPPROTO_DCCP)
			 वापस -EINVAL;
	पूर्ण
	अगर (info->biपंचांगask & EBT_IP_DPORT && info->dport[0] > info->dport[1])
		वापस -EINVAL;
	अगर (info->biपंचांगask & EBT_IP_SPORT && info->sport[0] > info->sport[1])
		वापस -EINVAL;
	अगर (info->biपंचांगask & EBT_IP_ICMP) अणु
		अगर ((info->invflags & EBT_IP_PROTO) ||
		    info->protocol != IPPROTO_ICMP)
			वापस -EINVAL;
		अगर (info->icmp_type[0] > info->icmp_type[1] ||
		    info->icmp_code[0] > info->icmp_code[1])
			वापस -EINVAL;
	पूर्ण
	अगर (info->biपंचांगask & EBT_IP_IGMP) अणु
		अगर ((info->invflags & EBT_IP_PROTO) ||
		    info->protocol != IPPROTO_IGMP)
			वापस -EINVAL;
		अगर (info->igmp_type[0] > info->igmp_type[1])
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_match ebt_ip_mt_reg __पढ़ो_mostly = अणु
	.name		= "ip",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_ip_mt,
	.checkentry	= ebt_ip_mt_check,
	.matchsize	= माप(काष्ठा ebt_ip_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_ip_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ebt_ip_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_ip_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_ip_mt_reg);
पूर्ण

module_init(ebt_ip_init);
module_निकास(ebt_ip_fini);
MODULE_DESCRIPTION("Ebtables: IPv4 protocol packet match");
MODULE_LICENSE("GPL");
