<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_log
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *	Harald Welte <laक्रमge@netfilter.org>
 *
 *  April, 2002
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/spinlock.h>
#समावेश <net/netfilter/nf_log.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <linux/in6.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_log.h>
#समावेश <linux/netfilter.h>

अटल DEFINE_SPINLOCK(ebt_log_lock);

अटल पूर्णांक ebt_log_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा ebt_log_info *info = par->targinfo;

	अगर (info->biपंचांगask & ~EBT_LOG_MASK)
		वापस -EINVAL;
	अगर (info->loglevel >= 8)
		वापस -EINVAL;
	info->prefix[EBT_LOG_PREFIX_SIZE - 1] = '\0';
	वापस 0;
पूर्ण

काष्ठा tcpudphdr अणु
	__be16 src;
	__be16 dst;
पूर्ण;

काष्ठा arppayload अणु
	अचिन्हित अक्षर mac_src[ETH_ALEN];
	अचिन्हित अक्षर ip_src[4];
	अचिन्हित अक्षर mac_dst[ETH_ALEN];
	अचिन्हित अक्षर ip_dst[4];
पूर्ण;

अटल व्योम
prपूर्णांक_ports(स्थिर काष्ठा sk_buff *skb, uपूर्णांक8_t protocol, पूर्णांक offset)
अणु
	अगर (protocol == IPPROTO_TCP ||
	    protocol == IPPROTO_UDP ||
	    protocol == IPPROTO_UDPLITE ||
	    protocol == IPPROTO_SCTP ||
	    protocol == IPPROTO_DCCP) अणु
		स्थिर काष्ठा tcpudphdr *pptr;
		काष्ठा tcpudphdr _ports;

		pptr = skb_header_poपूर्णांकer(skb, offset,
					  माप(_ports), &_ports);
		अगर (pptr == शून्य) अणु
			pr_cont(" INCOMPLETE TCP/UDP header");
			वापस;
		पूर्ण
		pr_cont(" SPT=%u DPT=%u", ntohs(pptr->src), ntohs(pptr->dst));
	पूर्ण
पूर्ण

अटल व्योम
ebt_log_packet(काष्ठा net *net, u_पूर्णांक8_t pf, अचिन्हित पूर्णांक hooknum,
	       स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *in,
	       स्थिर काष्ठा net_device *out, स्थिर काष्ठा nf_loginfo *loginfo,
	       स्थिर अक्षर *prefix)
अणु
	अचिन्हित पूर्णांक biपंचांगask;

	/* FIXME: Disabled from containers until syslog ns is supported */
	अगर (!net_eq(net, &init_net) && !sysctl_nf_log_all_netns)
		वापस;

	spin_lock_bh(&ebt_log_lock);
	prपूर्णांकk(KERN_SOH "%c%s IN=%s OUT=%s MAC source = %pM MAC dest = %pM proto = 0x%04x",
	       '0' + loginfo->u.log.level, prefix,
	       in ? in->name : "", out ? out->name : "",
	       eth_hdr(skb)->h_source, eth_hdr(skb)->h_dest,
	       ntohs(eth_hdr(skb)->h_proto));

	अगर (loginfo->type == NF_LOG_TYPE_LOG)
		biपंचांगask = loginfo->u.log.logflags;
	अन्यथा
		biपंचांगask = NF_LOG_DEFAULT_MASK;

	अगर ((biपंचांगask & EBT_LOG_IP) && eth_hdr(skb)->h_proto ==
	   htons(ETH_P_IP)) अणु
		स्थिर काष्ठा iphdr *ih;
		काष्ठा iphdr _iph;

		ih = skb_header_poपूर्णांकer(skb, 0, माप(_iph), &_iph);
		अगर (ih == शून्य) अणु
			pr_cont(" INCOMPLETE IP header");
			जाओ out;
		पूर्ण
		pr_cont(" IP SRC=%pI4 IP DST=%pI4, IP tos=0x%02X, IP proto=%d",
			&ih->saddr, &ih->daddr, ih->tos, ih->protocol);
		prपूर्णांक_ports(skb, ih->protocol, ih->ihl*4);
		जाओ out;
	पूर्ण

#अगर IS_ENABLED(CONFIG_BRIDGE_EBT_IP6)
	अगर ((biपंचांगask & EBT_LOG_IP6) && eth_hdr(skb)->h_proto ==
	   htons(ETH_P_IPV6)) अणु
		स्थिर काष्ठा ipv6hdr *ih;
		काष्ठा ipv6hdr _iph;
		uपूर्णांक8_t nexthdr;
		__be16 frag_off;
		पूर्णांक offset_ph;

		ih = skb_header_poपूर्णांकer(skb, 0, माप(_iph), &_iph);
		अगर (ih == शून्य) अणु
			pr_cont(" INCOMPLETE IPv6 header");
			जाओ out;
		पूर्ण
		pr_cont(" IPv6 SRC=%pI6 IPv6 DST=%pI6, IPv6 priority=0x%01X, Next Header=%d",
			&ih->saddr, &ih->daddr, ih->priority, ih->nexthdr);
		nexthdr = ih->nexthdr;
		offset_ph = ipv6_skip_exthdr(skb, माप(_iph), &nexthdr, &frag_off);
		अगर (offset_ph == -1)
			जाओ out;
		prपूर्णांक_ports(skb, nexthdr, offset_ph);
		जाओ out;
	पूर्ण
#पूर्ण_अगर

	अगर ((biपंचांगask & EBT_LOG_ARP) &&
	    ((eth_hdr(skb)->h_proto == htons(ETH_P_ARP)) ||
	     (eth_hdr(skb)->h_proto == htons(ETH_P_RARP)))) अणु
		स्थिर काष्ठा arphdr *ah;
		काष्ठा arphdr _arph;

		ah = skb_header_poपूर्णांकer(skb, 0, माप(_arph), &_arph);
		अगर (ah == शून्य) अणु
			pr_cont(" INCOMPLETE ARP header");
			जाओ out;
		पूर्ण
		pr_cont(" ARP HTYPE=%d, PTYPE=0x%04x, OPCODE=%d",
			ntohs(ah->ar_hrd), ntohs(ah->ar_pro),
			ntohs(ah->ar_op));

		/* If it's क्रम Ethernet and the lengths are OK,
		 * then log the ARP payload
		 */
		अगर (ah->ar_hrd == htons(1) &&
		    ah->ar_hln == ETH_ALEN &&
		    ah->ar_pln == माप(__be32)) अणु
			स्थिर काष्ठा arppayload *ap;
			काष्ठा arppayload _arpp;

			ap = skb_header_poपूर्णांकer(skb, माप(_arph),
						माप(_arpp), &_arpp);
			अगर (ap == शून्य) अणु
				pr_cont(" INCOMPLETE ARP payload");
				जाओ out;
			पूर्ण
			pr_cont(" ARP MAC SRC=%pM ARP IP SRC=%pI4 ARP MAC DST=%pM ARP IP DST=%pI4",
				ap->mac_src, ap->ip_src,
				ap->mac_dst, ap->ip_dst);
		पूर्ण
	पूर्ण
out:
	pr_cont("\n");
	spin_unlock_bh(&ebt_log_lock);
पूर्ण

अटल अचिन्हित पूर्णांक
ebt_log_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_log_info *info = par->targinfo;
	काष्ठा nf_loginfo li;
	काष्ठा net *net = xt_net(par);

	li.type = NF_LOG_TYPE_LOG;
	li.u.log.level = info->loglevel;
	li.u.log.logflags = info->biपंचांगask;

	/* Remember that we have to use ebt_log_packet() not to अवरोध backward
	 * compatibility. We cannot use the शेष bridge packet logger via
	 * nf_log_packet() with NFT_LOG_TYPE_LOG here. --Pablo
	 */
	अगर (info->biपंचांगask & EBT_LOG_NFLOG)
		nf_log_packet(net, NFPROTO_BRIDGE, xt_hooknum(par), skb,
			      xt_in(par), xt_out(par), &li, "%s",
			      info->prefix);
	अन्यथा
		ebt_log_packet(net, NFPROTO_BRIDGE, xt_hooknum(par), skb,
			       xt_in(par), xt_out(par), &li, info->prefix);
	वापस EBT_CONTINUE;
पूर्ण

अटल काष्ठा xt_target ebt_log_tg_reg __पढ़ो_mostly = अणु
	.name		= "log",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.target		= ebt_log_tg,
	.checkentry	= ebt_log_tg_check,
	.tarमाला_लोize	= माप(काष्ठा ebt_log_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_log_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&ebt_log_tg_reg);
पूर्ण

अटल व्योम __निकास ebt_log_fini(व्योम)
अणु
	xt_unरेजिस्टर_target(&ebt_log_tg_reg);
पूर्ण

module_init(ebt_log_init);
module_निकास(ebt_log_fini);
MODULE_DESCRIPTION("Ebtables: Packet logging to syslog");
MODULE_LICENSE("GPL");
