<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	xt_mark - Netfilter module to match NFMARK value
 *
 *	(C) 1999-2001 Marc Boucher <marc@mbsi.ca>
 *	Copyright तऊ CC Computer Consultants GmbH, 2007 - 2008
 *	Jan Engelhardt <jengelh@meकरोzas.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/netfilter/xt_mark.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marc Boucher <marc@mbsi.ca>");
MODULE_DESCRIPTION("Xtables: packet mark operations");
MODULE_ALIAS("ipt_mark");
MODULE_ALIAS("ip6t_mark");
MODULE_ALIAS("ipt_MARK");
MODULE_ALIAS("ip6t_MARK");
MODULE_ALIAS("arpt_MARK");

अटल अचिन्हित पूर्णांक
mark_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_mark_tginfo2 *info = par->targinfo;

	skb->mark = (skb->mark & ~info->mask) ^ info->mark;
	वापस XT_CONTINUE;
पूर्ण

अटल bool
mark_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_mark_mtinfo1 *info = par->matchinfo;

	वापस ((skb->mark & info->mask) == info->mark) ^ info->invert;
पूर्ण

अटल काष्ठा xt_target mark_tg_reg __पढ़ो_mostly = अणु
	.name           = "MARK",
	.revision       = 2,
	.family         = NFPROTO_UNSPEC,
	.target         = mark_tg,
	.tarमाला_लोize     = माप(काष्ठा xt_mark_tginfo2),
	.me             = THIS_MODULE,
पूर्ण;

अटल काष्ठा xt_match mark_mt_reg __पढ़ो_mostly = अणु
	.name           = "mark",
	.revision       = 1,
	.family         = NFPROTO_UNSPEC,
	.match          = mark_mt,
	.matchsize      = माप(काष्ठा xt_mark_mtinfo1),
	.me             = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init mark_mt_init(व्योम)
अणु
	पूर्णांक ret;

	ret = xt_रेजिस्टर_target(&mark_tg_reg);
	अगर (ret < 0)
		वापस ret;
	ret = xt_रेजिस्टर_match(&mark_mt_reg);
	अगर (ret < 0) अणु
		xt_unरेजिस्टर_target(&mark_tg_reg);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास mark_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&mark_mt_reg);
	xt_unरेजिस्टर_target(&mark_tg_reg);
पूर्ण

module_init(mark_mt_init);
module_निकास(mark_mt_निकास);
