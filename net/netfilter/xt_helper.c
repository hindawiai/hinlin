<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* iptables module to match on related connections */
/*
 * (C) 2001 Martin Josefsson <gandalf@wlug.westbo.se>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_helper.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Josefsson <gandalf@netfilter.org>");
MODULE_DESCRIPTION("Xtables: Related connection matching");
MODULE_ALIAS("ipt_helper");
MODULE_ALIAS("ip6t_helper");


अटल bool
helper_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_helper_info *info = par->matchinfo;
	स्थिर काष्ठा nf_conn *ct;
	स्थिर काष्ठा nf_conn_help *master_help;
	स्थिर काष्ठा nf_conntrack_helper *helper;
	क्रमागत ip_conntrack_info ctinfo;
	bool ret = info->invert;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct || !ct->master)
		वापस ret;

	master_help = nfct_help(ct->master);
	अगर (!master_help)
		वापस ret;

	/* rcu_पढ़ो_lock()ed by nf_hook_thresh */
	helper = rcu_dereference(master_help->helper);
	अगर (!helper)
		वापस ret;

	अगर (info->name[0] == '\0')
		ret = !ret;
	अन्यथा
		ret ^= !म_भेदन(helper->name, info->name,
				म_माप(helper->name));
	वापस ret;
पूर्ण

अटल पूर्णांक helper_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_helper_info *info = par->matchinfo;
	पूर्णांक ret;

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0) अणु
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
		वापस ret;
	पूर्ण
	info->name[माप(info->name) - 1] = '\0';
	वापस 0;
पूर्ण

अटल व्योम helper_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल काष्ठा xt_match helper_mt_reg __पढ़ो_mostly = अणु
	.name       = "helper",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.checkentry = helper_mt_check,
	.match      = helper_mt,
	.destroy    = helper_mt_destroy,
	.matchsize  = माप(काष्ठा xt_helper_info),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init helper_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&helper_mt_reg);
पूर्ण

अटल व्योम __निकास helper_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&helper_mt_reg);
पूर्ण

module_init(helper_mt_init);
module_निकास(helper_mt_निकास);
