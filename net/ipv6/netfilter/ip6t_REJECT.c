<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IP6 tables REJECT target module
 * Linux INET6 implementation
 *
 * Copyright (C)2003 USAGI/WIDE Project
 *
 * Authors:
 *	Yasuyuki Kozakai	<yasuyuki.kozakai@toshiba.co.jp>
 *
 * Copyright (c) 2005-2007 Patrick McHardy <kaber@trash.net>
 *
 * Based on net/ipv4/netfilter/ipt_REJECT.c
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/netdevice.h>
#समावेश <net/icmp.h>
#समावेश <net/flow.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter_ipv6/ip6t_REJECT.h>

#समावेश <net/netfilter/ipv6/nf_reject.h>

MODULE_AUTHOR("Yasuyuki KOZAKAI <yasuyuki.kozakai@toshiba.co.jp>");
MODULE_DESCRIPTION("Xtables: packet \"rejection\" target for IPv6");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक
reject_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ip6t_reject_info *reject = par->targinfo;
	काष्ठा net *net = xt_net(par);

	चयन (reject->with) अणु
	हाल IP6T_ICMP6_NO_ROUTE:
		nf_send_unreach6(net, skb, ICMPV6_NOROUTE, xt_hooknum(par));
		अवरोध;
	हाल IP6T_ICMP6_ADM_PROHIBITED:
		nf_send_unreach6(net, skb, ICMPV6_ADM_PROHIBITED,
				 xt_hooknum(par));
		अवरोध;
	हाल IP6T_ICMP6_NOT_NEIGHBOUR:
		nf_send_unreach6(net, skb, ICMPV6_NOT_NEIGHBOUR,
				 xt_hooknum(par));
		अवरोध;
	हाल IP6T_ICMP6_ADDR_UNREACH:
		nf_send_unreach6(net, skb, ICMPV6_ADDR_UNREACH,
				 xt_hooknum(par));
		अवरोध;
	हाल IP6T_ICMP6_PORT_UNREACH:
		nf_send_unreach6(net, skb, ICMPV6_PORT_UNREACH,
				 xt_hooknum(par));
		अवरोध;
	हाल IP6T_ICMP6_ECHOREPLY:
		/* Do nothing */
		अवरोध;
	हाल IP6T_TCP_RESET:
		nf_send_reset6(net, par->state->sk, skb, xt_hooknum(par));
		अवरोध;
	हाल IP6T_ICMP6_POLICY_FAIL:
		nf_send_unreach6(net, skb, ICMPV6_POLICY_FAIL, xt_hooknum(par));
		अवरोध;
	हाल IP6T_ICMP6_REJECT_ROUTE:
		nf_send_unreach6(net, skb, ICMPV6_REJECT_ROUTE,
				 xt_hooknum(par));
		अवरोध;
	पूर्ण

	वापस NF_DROP;
पूर्ण

अटल पूर्णांक reject_tg6_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ip6t_reject_info *rejinfo = par->targinfo;
	स्थिर काष्ठा ip6t_entry *e = par->entryinfo;

	अगर (rejinfo->with == IP6T_ICMP6_ECHOREPLY) अणु
		pr_info_ratelimited("ECHOREPLY is not supported\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (rejinfo->with == IP6T_TCP_RESET) अणु
		/* Must specअगरy that it's a TCP packet */
		अगर (!(e->ipv6.flags & IP6T_F_PROTO) ||
		    e->ipv6.proto != IPPROTO_TCP ||
		    (e->ipv6.invflags & XT_INV_PROTO)) अणु
			pr_info_ratelimited("TCP_RESET illegal for non-tcp\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_target reject_tg6_reg __पढ़ो_mostly = अणु
	.name		= "REJECT",
	.family		= NFPROTO_IPV6,
	.target		= reject_tg6,
	.tarमाला_लोize	= माप(काष्ठा ip6t_reject_info),
	.table		= "filter",
	.hooks		= (1 << NF_INET_LOCAL_IN) | (1 << NF_INET_FORWARD) |
			  (1 << NF_INET_LOCAL_OUT),
	.checkentry	= reject_tg6_check,
	.me		= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init reject_tg6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&reject_tg6_reg);
पूर्ण

अटल व्योम __निकास reject_tg6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_target(&reject_tg6_reg);
पूर्ण

module_init(reject_tg6_init);
module_निकास(reject_tg6_निकास);
