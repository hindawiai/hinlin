<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is a module which is used क्रम setting the skb->priority field
 * of an skb क्रम qdisc classअगरication.
 */

/* (C) 2001-2002 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <net/checksum.h>

#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_CLASSIFY.h>
#समावेश <linux/netfilter_arp.h>

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: Qdisc classification");
MODULE_ALIAS("ipt_CLASSIFY");
MODULE_ALIAS("ip6t_CLASSIFY");
MODULE_ALIAS("arpt_CLASSIFY");

अटल अचिन्हित पूर्णांक
classअगरy_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_classअगरy_target_info *clinfo = par->targinfo;

	skb->priority = clinfo->priority;
	वापस XT_CONTINUE;
पूर्ण

अटल काष्ठा xt_target classअगरy_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "CLASSIFY",
		.revision   = 0,
		.family     = NFPROTO_UNSPEC,
		.hooks      = (1 << NF_INET_LOCAL_OUT) | (1 << NF_INET_FORWARD) |
		              (1 << NF_INET_POST_ROUTING),
		.target     = classअगरy_tg,
		.tarमाला_लोize = माप(काष्ठा xt_classअगरy_target_info),
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "CLASSIFY",
		.revision   = 0,
		.family     = NFPROTO_ARP,
		.hooks      = (1 << NF_ARP_OUT) | (1 << NF_ARP_FORWARD),
		.target     = classअगरy_tg,
		.tarमाला_लोize = माप(काष्ठा xt_classअगरy_target_info),
		.me         = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init classअगरy_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(classअगरy_tg_reg, ARRAY_SIZE(classअगरy_tg_reg));
पूर्ण

अटल व्योम __निकास classअगरy_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(classअगरy_tg_reg, ARRAY_SIZE(classअगरy_tg_reg));
पूर्ण

module_init(classअगरy_tg_init);
module_निकास(classअगरy_tg_निकास);
