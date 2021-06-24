<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Florian Westphal <fw@म_माप.de>
 *
 * based on fib_frontend.c; Author: Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ip.h>
#समावेश <net/ip.h>
#समावेश <net/ip_fib.h>
#समावेश <net/route.h>

#समावेश <linux/netfilter/xt_rpfilter.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_DESCRIPTION("iptables: ipv4 reverse path filter match");

/* करोn't try to find route from mcast/bcast/zeronet */
अटल __be32 rpfilter_get_saddr(__be32 addr)
अणु
	अगर (ipv4_is_multicast(addr) || ipv4_is_lbcast(addr) ||
	    ipv4_is_zeronet(addr))
		वापस 0;
	वापस addr;
पूर्ण

अटल bool rpfilter_lookup_reverse(काष्ठा net *net, काष्ठा flowi4 *fl4,
				स्थिर काष्ठा net_device *dev, u8 flags)
अणु
	काष्ठा fib_result res;
	पूर्णांक ret __maybe_unused;

	अगर (fib_lookup(net, fl4, &res, FIB_LOOKUP_IGNORE_LINKSTATE))
		वापस false;

	अगर (res.type != RTN_UNICAST) अणु
		अगर (res.type != RTN_LOCAL || !(flags & XT_RPFILTER_ACCEPT_LOCAL))
			वापस false;
	पूर्ण
	वापस fib_info_nh_uses_dev(res.fi, dev) || flags & XT_RPFILTER_LOOSE;
पूर्ण

अटल bool
rpfilter_is_loopback(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *in)
अणु
	वापस skb->pkt_type == PACKET_LOOPBACK || in->flags & IFF_LOOPBACK;
पूर्ण

अटल bool rpfilter_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_rpfilter_info *info;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा flowi4 flow;
	bool invert;

	info = par->matchinfo;
	invert = info->flags & XT_RPFILTER_INVERT;

	अगर (rpfilter_is_loopback(skb, xt_in(par)))
		वापस true ^ invert;

	iph = ip_hdr(skb);
	अगर (ipv4_is_zeronet(iph->saddr)) अणु
		अगर (ipv4_is_lbcast(iph->daddr) ||
		    ipv4_is_local_multicast(iph->daddr))
			वापस true ^ invert;
	पूर्ण

	स_रखो(&flow, 0, माप(flow));
	flow.flowi4_iअगर = LOOPBACK_IFINDEX;
	flow.daddr = iph->saddr;
	flow.saddr = rpfilter_get_saddr(iph->daddr);
	flow.flowi4_mark = info->flags & XT_RPFILTER_VALID_MARK ? skb->mark : 0;
	flow.flowi4_tos = iph->tos & IPTOS_RT_MASK;
	flow.flowi4_scope = RT_SCOPE_UNIVERSE;
	flow.flowi4_oअगर = l3mdev_master_अगरindex_rcu(xt_in(par));

	वापस rpfilter_lookup_reverse(xt_net(par), &flow, xt_in(par), info->flags) ^ invert;
पूर्ण

अटल पूर्णांक rpfilter_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_rpfilter_info *info = par->matchinfo;
	अचिन्हित पूर्णांक options = ~XT_RPFILTER_OPTION_MASK;
	अगर (info->flags & options) अणु
		pr_info_ratelimited("unknown options\n");
		वापस -EINVAL;
	पूर्ण

	अगर (म_भेद(par->table, "mangle") != 0 &&
	    म_भेद(par->table, "raw") != 0) अणु
		pr_info_ratelimited("only valid in \'raw\' or \'mangle\' table, not \'%s\'\n",
				    par->table);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match rpfilter_mt_reg __पढ़ो_mostly = अणु
	.name		= "rpfilter",
	.family		= NFPROTO_IPV4,
	.checkentry	= rpfilter_check,
	.match		= rpfilter_mt,
	.matchsize	= माप(काष्ठा xt_rpfilter_info),
	.hooks		= (1 << NF_INET_PRE_ROUTING),
	.me		= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init rpfilter_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&rpfilter_mt_reg);
पूर्ण

अटल व्योम __निकास rpfilter_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&rpfilter_mt_reg);
पूर्ण

module_init(rpfilter_mt_init);
module_निकास(rpfilter_mt_निकास);
