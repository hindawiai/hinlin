<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2007 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/gen_stats.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_rateest.h>
#समावेश <net/netfilter/xt_rateest.h>


अटल bool
xt_rateest_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_rateest_match_info *info = par->matchinfo;
	काष्ठा gnet_stats_rate_est64 sample = अणु0पूर्ण;
	u_पूर्णांक32_t bps1, bps2, pps1, pps2;
	bool ret = true;

	gen_estimator_पढ़ो(&info->est1->rate_est, &sample);

	अगर (info->flags & XT_RATEEST_MATCH_DELTA) अणु
		bps1 = info->bps1 >= sample.bps ? info->bps1 - sample.bps : 0;
		pps1 = info->pps1 >= sample.pps ? info->pps1 - sample.pps : 0;
	पूर्ण अन्यथा अणु
		bps1 = sample.bps;
		pps1 = sample.pps;
	पूर्ण

	अगर (info->flags & XT_RATEEST_MATCH_ABS) अणु
		bps2 = info->bps2;
		pps2 = info->pps2;
	पूर्ण अन्यथा अणु
		gen_estimator_पढ़ो(&info->est2->rate_est, &sample);

		अगर (info->flags & XT_RATEEST_MATCH_DELTA) अणु
			bps2 = info->bps2 >= sample.bps ? info->bps2 - sample.bps : 0;
			pps2 = info->pps2 >= sample.pps ? info->pps2 - sample.pps : 0;
		पूर्ण अन्यथा अणु
			bps2 = sample.bps;
			pps2 = sample.pps;
		पूर्ण
	पूर्ण

	चयन (info->mode) अणु
	हाल XT_RATEEST_MATCH_LT:
		अगर (info->flags & XT_RATEEST_MATCH_BPS)
			ret &= bps1 < bps2;
		अगर (info->flags & XT_RATEEST_MATCH_PPS)
			ret &= pps1 < pps2;
		अवरोध;
	हाल XT_RATEEST_MATCH_GT:
		अगर (info->flags & XT_RATEEST_MATCH_BPS)
			ret &= bps1 > bps2;
		अगर (info->flags & XT_RATEEST_MATCH_PPS)
			ret &= pps1 > pps2;
		अवरोध;
	हाल XT_RATEEST_MATCH_EQ:
		अगर (info->flags & XT_RATEEST_MATCH_BPS)
			ret &= bps1 == bps2;
		अगर (info->flags & XT_RATEEST_MATCH_PPS)
			ret &= pps1 == pps2;
		अवरोध;
	पूर्ण

	ret ^= info->flags & XT_RATEEST_MATCH_INVERT ? true : false;
	वापस ret;
पूर्ण

अटल पूर्णांक xt_rateest_mt_checkentry(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_rateest_match_info *info = par->matchinfo;
	काष्ठा xt_rateest *est1, *est2;
	पूर्णांक ret = -EINVAL;

	अगर (hweight32(info->flags & (XT_RATEEST_MATCH_ABS |
				     XT_RATEEST_MATCH_REL)) != 1)
		जाओ err1;

	अगर (!(info->flags & (XT_RATEEST_MATCH_BPS | XT_RATEEST_MATCH_PPS)))
		जाओ err1;

	चयन (info->mode) अणु
	हाल XT_RATEEST_MATCH_EQ:
	हाल XT_RATEEST_MATCH_LT:
	हाल XT_RATEEST_MATCH_GT:
		अवरोध;
	शेष:
		जाओ err1;
	पूर्ण

	ret  = -ENOENT;
	est1 = xt_rateest_lookup(par->net, info->name1);
	अगर (!est1)
		जाओ err1;

	est2 = शून्य;
	अगर (info->flags & XT_RATEEST_MATCH_REL) अणु
		est2 = xt_rateest_lookup(par->net, info->name2);
		अगर (!est2)
			जाओ err2;
	पूर्ण

	info->est1 = est1;
	info->est2 = est2;
	वापस 0;

err2:
	xt_rateest_put(par->net, est1);
err1:
	वापस ret;
पूर्ण

अटल व्योम xt_rateest_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	काष्ठा xt_rateest_match_info *info = par->matchinfo;

	xt_rateest_put(par->net, info->est1);
	अगर (info->est2)
		xt_rateest_put(par->net, info->est2);
पूर्ण

अटल काष्ठा xt_match xt_rateest_mt_reg __पढ़ो_mostly = अणु
	.name       = "rateest",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.match      = xt_rateest_mt,
	.checkentry = xt_rateest_mt_checkentry,
	.destroy    = xt_rateest_mt_destroy,
	.matchsize  = माप(काष्ठा xt_rateest_match_info),
	.usersize   = दुरत्व(काष्ठा xt_rateest_match_info, est1),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init xt_rateest_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&xt_rateest_mt_reg);
पूर्ण

अटल व्योम __निकास xt_rateest_mt_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&xt_rateest_mt_reg);
पूर्ण

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("xtables rate estimator match");
MODULE_ALIAS("ipt_rateest");
MODULE_ALIAS("ip6t_rateest");
module_init(xt_rateest_mt_init);
module_निकास(xt_rateest_mt_fini);
