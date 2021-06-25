<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match connection tracking inक्रमmation. */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2005 Netfilter Core Team <coreteam@netfilter.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_state.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rusty Russell <rusty@rustcorp.com.au>");
MODULE_DESCRIPTION("ip[6]_tables connection tracking state match module");
MODULE_ALIAS("ipt_state");
MODULE_ALIAS("ip6t_state");

अटल bool
state_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_state_info *sinfo = par->matchinfo;
	क्रमागत ip_conntrack_info ctinfo;
	अचिन्हित पूर्णांक statebit;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);

	अगर (ct)
		statebit = XT_STATE_BIT(ctinfo);
	अन्यथा अगर (ctinfo == IP_CT_UNTRACKED)
		statebit = XT_STATE_UNTRACKED;
	अन्यथा
		statebit = XT_STATE_INVALID;

	वापस (sinfo->statemask & statebit);
पूर्ण

अटल पूर्णांक state_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	पूर्णांक ret;

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
	वापस ret;
पूर्ण

अटल व्योम state_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल काष्ठा xt_match state_mt_reg __पढ़ो_mostly = अणु
	.name       = "state",
	.family     = NFPROTO_UNSPEC,
	.checkentry = state_mt_check,
	.match      = state_mt,
	.destroy    = state_mt_destroy,
	.matchsize  = माप(काष्ठा xt_state_info),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init state_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&state_mt_reg);
पूर्ण

अटल व्योम __निकास state_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&state_mt_reg);
पूर्ण

module_init(state_mt_init);
module_निकास(state_mt_निकास);
