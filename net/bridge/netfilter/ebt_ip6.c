<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_ip6
 *
 *	Authors:
 *	Manohar Castelino <manohar.r.castelino@पूर्णांकel.com>
 *	Kuo-Lang Tseng <kuo-lang.tseng@पूर्णांकel.com>
 *	Jan Engelhardt <jengelh@meकरोzas.de>
 *
 * Summary:
 * This is just a modअगरication of the IPv4 code written by
 * Bart De Schuymer <bdschuym@panकरोra.be>
 * with the changes required to support IPv6
 *
 *  Jan, 2008
 */
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <net/dsfield.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_ip6.h>

जोड़ pkthdr अणु
	काष्ठा अणु
		__be16 src;
		__be16 dst;
	पूर्ण tcpudphdr;
	काष्ठा अणु
		u8 type;
		u8 code;
	पूर्ण icmphdr;
पूर्ण;

अटल bool
ebt_ip6_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_ip6_info *info = par->matchinfo;
	स्थिर काष्ठा ipv6hdr *ih6;
	काष्ठा ipv6hdr _ip6h;
	स्थिर जोड़ pkthdr *pptr;
	जोड़ pkthdr _pkthdr;

	ih6 = skb_header_poपूर्णांकer(skb, 0, माप(_ip6h), &_ip6h);
	अगर (ih6 == शून्य)
		वापस false;
	अगर ((info->biपंचांगask & EBT_IP6_TCLASS) &&
	    NF_INVF(info, EBT_IP6_TCLASS,
		    info->tclass != ipv6_get_dsfield(ih6)))
		वापस false;
	अगर (((info->biपंचांगask & EBT_IP6_SOURCE) &&
	     NF_INVF(info, EBT_IP6_SOURCE,
		     ipv6_masked_addr_cmp(&ih6->saddr, &info->smsk,
					  &info->saddr))) ||
	    ((info->biपंचांगask & EBT_IP6_DEST) &&
	     NF_INVF(info, EBT_IP6_DEST,
		     ipv6_masked_addr_cmp(&ih6->daddr, &info->dmsk,
					  &info->daddr))))
		वापस false;
	अगर (info->biपंचांगask & EBT_IP6_PROTO) अणु
		uपूर्णांक8_t nexthdr = ih6->nexthdr;
		__be16 frag_off;
		पूर्णांक offset_ph;

		offset_ph = ipv6_skip_exthdr(skb, माप(_ip6h), &nexthdr, &frag_off);
		अगर (offset_ph == -1)
			वापस false;
		अगर (NF_INVF(info, EBT_IP6_PROTO, info->protocol != nexthdr))
			वापस false;
		अगर (!(info->biपंचांगask & (EBT_IP6_DPORT |
				       EBT_IP6_SPORT | EBT_IP6_ICMP6)))
			वापस true;

		/* min icmpv6 headersize is 4, so माप(_pkthdr) is ok. */
		pptr = skb_header_poपूर्णांकer(skb, offset_ph, माप(_pkthdr),
					  &_pkthdr);
		अगर (pptr == शून्य)
			वापस false;
		अगर (info->biपंचांगask & EBT_IP6_DPORT) अणु
			u16 dst = ntohs(pptr->tcpudphdr.dst);
			अगर (NF_INVF(info, EBT_IP6_DPORT,
				    dst < info->dport[0] ||
				    dst > info->dport[1]))
				वापस false;
		पूर्ण
		अगर (info->biपंचांगask & EBT_IP6_SPORT) अणु
			u16 src = ntohs(pptr->tcpudphdr.src);
			अगर (NF_INVF(info, EBT_IP6_SPORT,
				    src < info->sport[0] ||
				    src > info->sport[1]))
				वापस false;
		पूर्ण
		अगर ((info->biपंचांगask & EBT_IP6_ICMP6) &&
		    NF_INVF(info, EBT_IP6_ICMP6,
			    pptr->icmphdr.type < info->icmpv6_type[0] ||
			    pptr->icmphdr.type > info->icmpv6_type[1] ||
			    pptr->icmphdr.code < info->icmpv6_code[0] ||
			    pptr->icmphdr.code > info->icmpv6_code[1]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक ebt_ip6_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ebt_entry *e = par->entryinfo;
	काष्ठा ebt_ip6_info *info = par->matchinfo;

	अगर (e->ethproto != htons(ETH_P_IPV6) || e->invflags & EBT_IPROTO)
		वापस -EINVAL;
	अगर (info->biपंचांगask & ~EBT_IP6_MASK || info->invflags & ~EBT_IP6_MASK)
		वापस -EINVAL;
	अगर (info->biपंचांगask & (EBT_IP6_DPORT | EBT_IP6_SPORT)) अणु
		अगर (info->invflags & EBT_IP6_PROTO)
			वापस -EINVAL;
		अगर (info->protocol != IPPROTO_TCP &&
		    info->protocol != IPPROTO_UDP &&
		    info->protocol != IPPROTO_UDPLITE &&
		    info->protocol != IPPROTO_SCTP &&
		    info->protocol != IPPROTO_DCCP)
			वापस -EINVAL;
	पूर्ण
	अगर (info->biपंचांगask & EBT_IP6_DPORT && info->dport[0] > info->dport[1])
		वापस -EINVAL;
	अगर (info->biपंचांगask & EBT_IP6_SPORT && info->sport[0] > info->sport[1])
		वापस -EINVAL;
	अगर (info->biपंचांगask & EBT_IP6_ICMP6) अणु
		अगर ((info->invflags & EBT_IP6_PROTO) ||
		     info->protocol != IPPROTO_ICMPV6)
			वापस -EINVAL;
		अगर (info->icmpv6_type[0] > info->icmpv6_type[1] ||
		    info->icmpv6_code[0] > info->icmpv6_code[1])
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_match ebt_ip6_mt_reg __पढ़ो_mostly = अणु
	.name		= "ip6",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_ip6_mt,
	.checkentry	= ebt_ip6_mt_check,
	.matchsize	= माप(काष्ठा ebt_ip6_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_ip6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ebt_ip6_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_ip6_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_ip6_mt_reg);
पूर्ण

module_init(ebt_ip6_init);
module_निकास(ebt_ip6_fini);
MODULE_DESCRIPTION("Ebtables: IPv6 protocol packet match");
MODULE_AUTHOR("Kuo-Lang Tseng <kuo-lang.tseng@intel.com>");
MODULE_LICENSE("GPL");
