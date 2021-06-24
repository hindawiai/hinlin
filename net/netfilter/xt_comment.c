<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implements a dummy match to allow attaching comments to rules
 *
 * 2003-05-13 Brad Fisher (brad@info-link.net)
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_comment.h>

MODULE_AUTHOR("Brad Fisher <brad@info-link.net>");
MODULE_DESCRIPTION("Xtables: No-op match which can be tagged with a comment");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_comment");
MODULE_ALIAS("ip6t_comment");

अटल bool
comment_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	/* We always match */
	वापस true;
पूर्ण

अटल काष्ठा xt_match comment_mt_reg __पढ़ो_mostly = अणु
	.name      = "comment",
	.revision  = 0,
	.family    = NFPROTO_UNSPEC,
	.match     = comment_mt,
	.matchsize = माप(काष्ठा xt_comment_info),
	.me        = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init comment_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&comment_mt_reg);
पूर्ण

अटल व्योम __निकास comment_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&comment_mt_reg);
पूर्ण

module_init(comment_mt_init);
module_निकास(comment_mt_निकास);
