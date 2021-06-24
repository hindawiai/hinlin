<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2013 Astaro GmbH & Co KG
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_labels.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_DESCRIPTION("Xtables: add/match connection tracking labels");
MODULE_ALIAS("ipt_connlabel");
MODULE_ALIAS("ip6t_connlabel");

अटल bool
connlabel_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_connlabel_mtinfo *info = par->matchinfo;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn_labels *labels;
	काष्ठा nf_conn *ct;
	bool invert = info->options & XT_CONNLABEL_OP_INVERT;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct == शून्य)
		वापस invert;

	labels = nf_ct_labels_find(ct);
	अगर (!labels)
		वापस invert;

	अगर (test_bit(info->bit, labels->bits))
		वापस !invert;

	अगर (info->options & XT_CONNLABEL_OP_SET) अणु
		अगर (!test_and_set_bit(info->bit, labels->bits))
			nf_conntrack_event_cache(IPCT_LABEL, ct);

		वापस !invert;
	पूर्ण

	वापस invert;
पूर्ण

अटल पूर्णांक connlabel_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर पूर्णांक options = XT_CONNLABEL_OP_INVERT |
			    XT_CONNLABEL_OP_SET;
	काष्ठा xt_connlabel_mtinfo *info = par->matchinfo;
	पूर्णांक ret;

	अगर (info->options & ~options) अणु
		pr_info_ratelimited("Unknown options in mask %x\n",
				    info->options);
		वापस -EINVAL;
	पूर्ण

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0) अणु
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
		वापस ret;
	पूर्ण

	ret = nf_connlabels_get(par->net, info->bit);
	अगर (ret < 0)
		nf_ct_netns_put(par->net, par->family);
	वापस ret;
पूर्ण

अटल व्योम connlabel_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	nf_connlabels_put(par->net);
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल काष्ठा xt_match connlabels_mt_reg __पढ़ो_mostly = अणु
	.name           = "connlabel",
	.family         = NFPROTO_UNSPEC,
	.checkentry     = connlabel_mt_check,
	.match          = connlabel_mt,
	.matchsize      = माप(काष्ठा xt_connlabel_mtinfo),
	.destroy        = connlabel_mt_destroy,
	.me             = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init connlabel_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&connlabels_mt_reg);
पूर्ण

अटल व्योम __निकास connlabel_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&connlabels_mt_reg);
पूर्ण

module_init(connlabel_mt_init);
module_निकास(connlabel_mt_निकास);
