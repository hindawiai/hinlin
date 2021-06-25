<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* IP tables module क्रम matching the routing realm
 *
 * (C) 2003 by Sampsa Ranta <sampsa@netsonic.fi>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <net/route.h>

#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter/xt_realm.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_AUTHOR("Sampsa Ranta <sampsa@netsonic.fi>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: Routing realm match");
MODULE_ALIAS("ipt_realm");

अटल bool
realm_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_realm_info *info = par->matchinfo;
	स्थिर काष्ठा dst_entry *dst = skb_dst(skb);

	वापस (info->id == (dst->tclassid & info->mask)) ^ info->invert;
पूर्ण

अटल काष्ठा xt_match realm_mt_reg __पढ़ो_mostly = अणु
	.name		= "realm",
	.match		= realm_mt,
	.matchsize	= माप(काष्ठा xt_realm_info),
	.hooks		= (1 << NF_INET_POST_ROUTING) | (1 << NF_INET_FORWARD) |
			  (1 << NF_INET_LOCAL_OUT) | (1 << NF_INET_LOCAL_IN),
	.family		= NFPROTO_UNSPEC,
	.me		= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init realm_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&realm_mt_reg);
पूर्ण

अटल व्योम __निकास realm_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&realm_mt_reg);
पूर्ण

module_init(realm_mt_init);
module_निकास(realm_mt_निकास);
