<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* iptables module क्रम the IPv4 and TCP ECN bits, Version 1.5
 *
 * (C) 2002 by Harald Welte <laक्रमge@netfilter.org>
*/
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <net/ip.h>
#समावेश <linux/tcp.h>
#समावेश <net/checksum.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv4/ipt_ECN.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("Xtables: Explicit Congestion Notification (ECN) flag modification");

/* set ECT codepoपूर्णांक from IP header.
 * 	वापस false अगर there was an error. */
अटल अंतरभूत bool
set_ect_ip(काष्ठा sk_buff *skb, स्थिर काष्ठा ipt_ECN_info *einfo)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);

	अगर ((iph->tos & IPT_ECN_IP_MASK) != (einfo->ip_ect & IPT_ECN_IP_MASK)) अणु
		__u8 oldtos;
		अगर (skb_ensure_writable(skb, माप(काष्ठा iphdr)))
			वापस false;
		iph = ip_hdr(skb);
		oldtos = iph->tos;
		iph->tos &= ~IPT_ECN_IP_MASK;
		iph->tos |= (einfo->ip_ect & IPT_ECN_IP_MASK);
		csum_replace2(&iph->check, htons(oldtos), htons(iph->tos));
	पूर्ण
	वापस true;
पूर्ण

/* Return false अगर there was an error. */
अटल अंतरभूत bool
set_ect_tcp(काष्ठा sk_buff *skb, स्थिर काष्ठा ipt_ECN_info *einfo)
अणु
	काष्ठा tcphdr _tcph, *tcph;
	__be16 oldval;

	/* Not enough header? */
	tcph = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb), माप(_tcph), &_tcph);
	अगर (!tcph)
		वापस false;

	अगर ((!(einfo->operation & IPT_ECN_OP_SET_ECE) ||
	     tcph->ece == einfo->proto.tcp.ece) &&
	    (!(einfo->operation & IPT_ECN_OP_SET_CWR) ||
	     tcph->cwr == einfo->proto.tcp.cwr))
		वापस true;

	अगर (skb_ensure_writable(skb, ip_hdrlen(skb) + माप(*tcph)))
		वापस false;
	tcph = (व्योम *)ip_hdr(skb) + ip_hdrlen(skb);

	oldval = ((__be16 *)tcph)[6];
	अगर (einfo->operation & IPT_ECN_OP_SET_ECE)
		tcph->ece = einfo->proto.tcp.ece;
	अगर (einfo->operation & IPT_ECN_OP_SET_CWR)
		tcph->cwr = einfo->proto.tcp.cwr;

	inet_proto_csum_replace2(&tcph->check, skb,
				 oldval, ((__be16 *)tcph)[6], false);
	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक
ecn_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ipt_ECN_info *einfo = par->targinfo;

	अगर (einfo->operation & IPT_ECN_OP_SET_IP)
		अगर (!set_ect_ip(skb, einfo))
			वापस NF_DROP;

	अगर (einfo->operation & (IPT_ECN_OP_SET_ECE | IPT_ECN_OP_SET_CWR) &&
	    ip_hdr(skb)->protocol == IPPROTO_TCP)
		अगर (!set_ect_tcp(skb, einfo))
			वापस NF_DROP;

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक ecn_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ipt_ECN_info *einfo = par->targinfo;
	स्थिर काष्ठा ipt_entry *e = par->entryinfo;

	अगर (einfo->operation & IPT_ECN_OP_MASK)
		वापस -EINVAL;

	अगर (einfo->ip_ect & ~IPT_ECN_IP_MASK)
		वापस -EINVAL;

	अगर ((einfo->operation & (IPT_ECN_OP_SET_ECE|IPT_ECN_OP_SET_CWR)) &&
	    (e->ip.proto != IPPROTO_TCP || (e->ip.invflags & XT_INV_PROTO))) अणु
		pr_info_ratelimited("cannot use operation on non-tcp rule\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_target ecn_tg_reg __पढ़ो_mostly = अणु
	.name		= "ECN",
	.family		= NFPROTO_IPV4,
	.target		= ecn_tg,
	.tarमाला_लोize	= माप(काष्ठा ipt_ECN_info),
	.table		= "mangle",
	.checkentry	= ecn_tg_check,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ecn_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&ecn_tg_reg);
पूर्ण

अटल व्योम __निकास ecn_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_target(&ecn_tg_reg);
पूर्ण

module_init(ecn_tg_init);
module_निकास(ecn_tg_निकास);
