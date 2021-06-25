<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is a module which is used क्रम rejecting packets.
 */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <linux/icmp.h>
#समावेश <net/icmp.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv4/ipt_REJECT.h>
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
#समावेश <linux/netfilter_bridge.h>
#पूर्ण_अगर

#समावेश <net/netfilter/ipv4/nf_reject.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("Xtables: packet \"rejection\" target for IPv4");

अटल अचिन्हित पूर्णांक
reject_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ipt_reject_info *reject = par->targinfo;
	पूर्णांक hook = xt_hooknum(par);

	चयन (reject->with) अणु
	हाल IPT_ICMP_NET_UNREACHABLE:
		nf_send_unreach(skb, ICMP_NET_UNREACH, hook);
		अवरोध;
	हाल IPT_ICMP_HOST_UNREACHABLE:
		nf_send_unreach(skb, ICMP_HOST_UNREACH, hook);
		अवरोध;
	हाल IPT_ICMP_PROT_UNREACHABLE:
		nf_send_unreach(skb, ICMP_PROT_UNREACH, hook);
		अवरोध;
	हाल IPT_ICMP_PORT_UNREACHABLE:
		nf_send_unreach(skb, ICMP_PORT_UNREACH, hook);
		अवरोध;
	हाल IPT_ICMP_NET_PROHIBITED:
		nf_send_unreach(skb, ICMP_NET_ANO, hook);
		अवरोध;
	हाल IPT_ICMP_HOST_PROHIBITED:
		nf_send_unreach(skb, ICMP_HOST_ANO, hook);
		अवरोध;
	हाल IPT_ICMP_ADMIN_PROHIBITED:
		nf_send_unreach(skb, ICMP_PKT_FILTERED, hook);
		अवरोध;
	हाल IPT_TCP_RESET:
		nf_send_reset(xt_net(par), par->state->sk, skb, hook);
		अवरोध;
	हाल IPT_ICMP_ECHOREPLY:
		/* Doesn't happen. */
		अवरोध;
	पूर्ण

	वापस NF_DROP;
पूर्ण

अटल पूर्णांक reject_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ipt_reject_info *rejinfo = par->targinfo;
	स्थिर काष्ठा ipt_entry *e = par->entryinfo;

	अगर (rejinfo->with == IPT_ICMP_ECHOREPLY) अणु
		pr_info_ratelimited("ECHOREPLY no longer supported.\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (rejinfo->with == IPT_TCP_RESET) अणु
		/* Must specअगरy that it's a TCP packet */
		अगर (e->ip.proto != IPPROTO_TCP ||
		    (e->ip.invflags & XT_INV_PROTO)) अणु
			pr_info_ratelimited("TCP_RESET invalid for non-tcp\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_target reject_tg_reg __पढ़ो_mostly = अणु
	.name		= "REJECT",
	.family		= NFPROTO_IPV4,
	.target		= reject_tg,
	.tarमाला_लोize	= माप(काष्ठा ipt_reject_info),
	.table		= "filter",
	.hooks		= (1 << NF_INET_LOCAL_IN) | (1 << NF_INET_FORWARD) |
			  (1 << NF_INET_LOCAL_OUT),
	.checkentry	= reject_tg_check,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init reject_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&reject_tg_reg);
पूर्ण

अटल व्योम __निकास reject_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_target(&reject_tg_reg);
पूर्ण

module_init(reject_tg_init);
module_निकास(reject_tg_निकास);
