<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	xt_connmark - Netfilter module to operate on connection marks
 *
 *	Copyright (C) 2002,2004 MARA Systems AB <https://www.maraप्रणालीs.com>
 *	by Henrik Nordstrom <hno@maraप्रणालीs.com>
 *	Copyright तऊ CC Computer Consultants GmbH, 2007 - 2008
 *	Jan Engelhardt <jengelh@meकरोzas.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_connmark.h>

MODULE_AUTHOR("Henrik Nordstrom <hno@marasystems.com>");
MODULE_DESCRIPTION("Xtables: connection mark operations");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_CONNMARK");
MODULE_ALIAS("ip6t_CONNMARK");
MODULE_ALIAS("ipt_connmark");
MODULE_ALIAS("ip6t_connmark");

अटल अचिन्हित पूर्णांक
connmark_tg_shअगरt(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_connmark_tginfo2 *info)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	u_पूर्णांक32_t new_targeपंचांगark;
	काष्ठा nf_conn *ct;
	u_पूर्णांक32_t newmark;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct == शून्य)
		वापस XT_CONTINUE;

	चयन (info->mode) अणु
	हाल XT_CONNMARK_SET:
		newmark = (ct->mark & ~info->cपंचांगask) ^ info->cपंचांगark;
		अगर (info->shअगरt_dir == D_SHIFT_RIGHT)
			newmark >>= info->shअगरt_bits;
		अन्यथा
			newmark <<= info->shअगरt_bits;

		अगर (ct->mark != newmark) अणु
			ct->mark = newmark;
			nf_conntrack_event_cache(IPCT_MARK, ct);
		पूर्ण
		अवरोध;
	हाल XT_CONNMARK_SAVE:
		new_targeपंचांगark = (skb->mark & info->nfmask);
		अगर (info->shअगरt_dir == D_SHIFT_RIGHT)
			new_targeपंचांगark >>= info->shअगरt_bits;
		अन्यथा
			new_targeपंचांगark <<= info->shअगरt_bits;

		newmark = (ct->mark & ~info->cपंचांगask) ^
			  new_targeपंचांगark;
		अगर (ct->mark != newmark) अणु
			ct->mark = newmark;
			nf_conntrack_event_cache(IPCT_MARK, ct);
		पूर्ण
		अवरोध;
	हाल XT_CONNMARK_RESTORE:
		new_targeपंचांगark = (ct->mark & info->cपंचांगask);
		अगर (info->shअगरt_dir == D_SHIFT_RIGHT)
			new_targeपंचांगark >>= info->shअगरt_bits;
		अन्यथा
			new_targeपंचांगark <<= info->shअगरt_bits;

		newmark = (skb->mark & ~info->nfmask) ^
			  new_targeपंचांगark;
		skb->mark = newmark;
		अवरोध;
	पूर्ण
	वापस XT_CONTINUE;
पूर्ण

अटल अचिन्हित पूर्णांक
connmark_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_connmark_tginfo1 *info = par->targinfo;
	स्थिर काष्ठा xt_connmark_tginfo2 info2 = अणु
		.cपंचांगark	= info->cपंचांगark,
		.cपंचांगask	= info->cपंचांगask,
		.nfmask	= info->nfmask,
		.mode	= info->mode,
	पूर्ण;

	वापस connmark_tg_shअगरt(skb, &info2);
पूर्ण

अटल अचिन्हित पूर्णांक
connmark_tg_v2(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_connmark_tginfo2 *info = par->targinfo;

	वापस connmark_tg_shअगरt(skb, info);
पूर्ण

अटल पूर्णांक connmark_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	पूर्णांक ret;

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
	वापस ret;
पूर्ण

अटल व्योम connmark_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल bool
connmark_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_connmark_mtinfo1 *info = par->matchinfo;
	क्रमागत ip_conntrack_info ctinfo;
	स्थिर काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct == शून्य)
		वापस false;

	वापस ((ct->mark & info->mask) == info->mark) ^ info->invert;
पूर्ण

अटल पूर्णांक connmark_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	पूर्णांक ret;

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
	वापस ret;
पूर्ण

अटल व्योम connmark_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल काष्ठा xt_target connmark_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name           = "CONNMARK",
		.revision       = 1,
		.family         = NFPROTO_UNSPEC,
		.checkentry     = connmark_tg_check,
		.target         = connmark_tg,
		.tarमाला_लोize     = माप(काष्ठा xt_connmark_tginfo1),
		.destroy        = connmark_tg_destroy,
		.me             = THIS_MODULE,
	पूर्ण,
	अणु
		.name           = "CONNMARK",
		.revision       = 2,
		.family         = NFPROTO_UNSPEC,
		.checkentry     = connmark_tg_check,
		.target         = connmark_tg_v2,
		.tarमाला_लोize     = माप(काष्ठा xt_connmark_tginfo2),
		.destroy        = connmark_tg_destroy,
		.me             = THIS_MODULE,
	पूर्ण
पूर्ण;

अटल काष्ठा xt_match connmark_mt_reg __पढ़ो_mostly = अणु
	.name           = "connmark",
	.revision       = 1,
	.family         = NFPROTO_UNSPEC,
	.checkentry     = connmark_mt_check,
	.match          = connmark_mt,
	.matchsize      = माप(काष्ठा xt_connmark_mtinfo1),
	.destroy        = connmark_mt_destroy,
	.me             = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init connmark_mt_init(व्योम)
अणु
	पूर्णांक ret;

	ret = xt_रेजिस्टर_tarमाला_लो(connmark_tg_reg,
				  ARRAY_SIZE(connmark_tg_reg));
	अगर (ret < 0)
		वापस ret;
	ret = xt_रेजिस्टर_match(&connmark_mt_reg);
	अगर (ret < 0) अणु
		xt_unरेजिस्टर_tarमाला_लो(connmark_tg_reg,
				      ARRAY_SIZE(connmark_tg_reg));
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास connmark_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&connmark_mt_reg);
	xt_unरेजिस्टर_tarमाला_लो(connmark_tg_reg, ARRAY_SIZE(connmark_tg_reg));
पूर्ण

module_init(connmark_mt_init);
module_निकास(connmark_mt_निकास);
