<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) 2011 Pablo Neira Ayuso <pablo@netfilter.org>
 * (C) 2011 Intra2net AG <https://www.पूर्णांकra2net.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/nfnetlink_acct.h>
#समावेश <linux/netfilter/xt_nfacct.h>

MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_DESCRIPTION("Xtables: match for the extended accounting infrastructure");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_nfacct");
MODULE_ALIAS("ip6t_nfacct");

अटल bool nfacct_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	पूर्णांक overquota;
	स्थिर काष्ठा xt_nfacct_match_info *info = par->targinfo;

	nfnl_acct_update(skb, info->nfacct);

	overquota = nfnl_acct_overquota(xt_net(par), info->nfacct);

	वापस overquota != NFACCT_UNDERQUOTA;
पूर्ण

अटल पूर्णांक
nfacct_mt_checkentry(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_nfacct_match_info *info = par->matchinfo;
	काष्ठा nf_acct *nfacct;

	nfacct = nfnl_acct_find_get(par->net, info->name);
	अगर (nfacct == शून्य) अणु
		pr_info_ratelimited("accounting object `%s' does not exists\n",
				    info->name);
		वापस -ENOENT;
	पूर्ण
	info->nfacct = nfacct;
	वापस 0;
पूर्ण

अटल व्योम
nfacct_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_nfacct_match_info *info = par->matchinfo;

	nfnl_acct_put(info->nfacct);
पूर्ण

अटल काष्ठा xt_match nfacct_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "nfacct",
		.revision   = 0,
		.family     = NFPROTO_UNSPEC,
		.checkentry = nfacct_mt_checkentry,
		.match      = nfacct_mt,
		.destroy    = nfacct_mt_destroy,
		.matchsize  = माप(काष्ठा xt_nfacct_match_info),
		.usersize   = दुरत्व(काष्ठा xt_nfacct_match_info, nfacct),
		.me         = THIS_MODULE,
	पूर्ण,
	अणु
		.name       = "nfacct",
		.revision   = 1,
		.family     = NFPROTO_UNSPEC,
		.checkentry = nfacct_mt_checkentry,
		.match      = nfacct_mt,
		.destroy    = nfacct_mt_destroy,
		.matchsize  = माप(काष्ठा xt_nfacct_match_info_v1),
		.usersize   = दुरत्व(काष्ठा xt_nfacct_match_info_v1, nfacct),
		.me         = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init nfacct_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(nfacct_mt_reg, ARRAY_SIZE(nfacct_mt_reg));
पूर्ण

अटल व्योम __निकास nfacct_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(nfacct_mt_reg, ARRAY_SIZE(nfacct_mt_reg));
पूर्ण

module_init(nfacct_mt_init);
module_निकास(nfacct_mt_निकास);
