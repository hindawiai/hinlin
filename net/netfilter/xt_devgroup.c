<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>

#समावेश <linux/netfilter/xt_devgroup.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: Device group match");
MODULE_ALIAS("ipt_devgroup");
MODULE_ALIAS("ip6t_devgroup");

अटल bool devgroup_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_devgroup_info *info = par->matchinfo;

	अगर (info->flags & XT_DEVGROUP_MATCH_SRC &&
	    (((info->src_group ^ xt_in(par)->group) & info->src_mask ? 1 : 0) ^
	     ((info->flags & XT_DEVGROUP_INVERT_SRC) ? 1 : 0)))
		वापस false;

	अगर (info->flags & XT_DEVGROUP_MATCH_DST &&
	    (((info->dst_group ^ xt_out(par)->group) & info->dst_mask ? 1 : 0) ^
	     ((info->flags & XT_DEVGROUP_INVERT_DST) ? 1 : 0)))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक devgroup_mt_checkentry(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_devgroup_info *info = par->matchinfo;

	अगर (info->flags & ~(XT_DEVGROUP_MATCH_SRC | XT_DEVGROUP_INVERT_SRC |
			    XT_DEVGROUP_MATCH_DST | XT_DEVGROUP_INVERT_DST))
		वापस -EINVAL;

	अगर (info->flags & XT_DEVGROUP_MATCH_SRC &&
	    par->hook_mask & ~((1 << NF_INET_PRE_ROUTING) |
			       (1 << NF_INET_LOCAL_IN) |
			       (1 << NF_INET_FORWARD)))
		वापस -EINVAL;

	अगर (info->flags & XT_DEVGROUP_MATCH_DST &&
	    par->hook_mask & ~((1 << NF_INET_FORWARD) |
			       (1 << NF_INET_LOCAL_OUT) |
			       (1 << NF_INET_POST_ROUTING)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा xt_match devgroup_mt_reg __पढ़ो_mostly = अणु
	.name		= "devgroup",
	.match		= devgroup_mt,
	.checkentry	= devgroup_mt_checkentry,
	.matchsize	= माप(काष्ठा xt_devgroup_info),
	.family		= NFPROTO_UNSPEC,
	.me		= THIS_MODULE
पूर्ण;

अटल पूर्णांक __init devgroup_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&devgroup_mt_reg);
पूर्ण

अटल व्योम __निकास devgroup_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&devgroup_mt_reg);
पूर्ण

module_init(devgroup_mt_init);
module_निकास(devgroup_mt_निकास);
