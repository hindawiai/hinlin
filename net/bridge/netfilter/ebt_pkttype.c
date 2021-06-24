<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_pkttype
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  April, 2003
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_pkttype.h>

अटल bool
ebt_pkttype_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_pkttype_info *info = par->matchinfo;

	वापस (skb->pkt_type == info->pkt_type) ^ info->invert;
पूर्ण

अटल पूर्णांक ebt_pkttype_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ebt_pkttype_info *info = par->matchinfo;

	अगर (info->invert != 0 && info->invert != 1)
		वापस -EINVAL;
	/* Allow any pkt_type value */
	वापस 0;
पूर्ण

अटल काष्ठा xt_match ebt_pkttype_mt_reg __पढ़ो_mostly = अणु
	.name		= "pkttype",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_pkttype_mt,
	.checkentry	= ebt_pkttype_mt_check,
	.matchsize	= माप(काष्ठा ebt_pkttype_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_pkttype_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ebt_pkttype_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_pkttype_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_pkttype_mt_reg);
पूर्ण

module_init(ebt_pkttype_init);
module_निकास(ebt_pkttype_fini);
MODULE_DESCRIPTION("Ebtables: Link layer packet type match");
MODULE_LICENSE("GPL");
