<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006 Patrick McHardy <kaber@trash.net>
 *
 * Based on ipt_अक्रमom and ipt_nth by Fabrice MARIE <fabrice@netfilter.org>.
 */

#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>

#समावेश <linux/netfilter/xt_statistic.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/module.h>

काष्ठा xt_statistic_priv अणु
	atomic_t count;
पूर्ण ____cacheline_aligned_in_smp;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Xtables: statistics-based matching (\"Nth\", random)");
MODULE_ALIAS("ipt_statistic");
MODULE_ALIAS("ip6t_statistic");

अटल bool
statistic_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_statistic_info *info = par->matchinfo;
	bool ret = info->flags & XT_STATISTIC_INVERT;
	पूर्णांक nval, oval;

	चयन (info->mode) अणु
	हाल XT_STATISTIC_MODE_RANDOM:
		अगर ((pअक्रमom_u32() & 0x7FFFFFFF) < info->u.अक्रमom.probability)
			ret = !ret;
		अवरोध;
	हाल XT_STATISTIC_MODE_NTH:
		करो अणु
			oval = atomic_पढ़ो(&info->master->count);
			nval = (oval == info->u.nth.every) ? 0 : oval + 1;
		पूर्ण जबतक (atomic_cmpxchg(&info->master->count, oval, nval) != oval);
		अगर (nval == 0)
			ret = !ret;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक statistic_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_statistic_info *info = par->matchinfo;

	अगर (info->mode > XT_STATISTIC_MODE_MAX ||
	    info->flags & ~XT_STATISTIC_MASK)
		वापस -EINVAL;

	info->master = kzalloc(माप(*info->master), GFP_KERNEL);
	अगर (info->master == शून्य)
		वापस -ENOMEM;
	atomic_set(&info->master->count, info->u.nth.count);

	वापस 0;
पूर्ण

अटल व्योम statistic_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_statistic_info *info = par->matchinfo;

	kमुक्त(info->master);
पूर्ण

अटल काष्ठा xt_match xt_statistic_mt_reg __पढ़ो_mostly = अणु
	.name       = "statistic",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.match      = statistic_mt,
	.checkentry = statistic_mt_check,
	.destroy    = statistic_mt_destroy,
	.matchsize  = माप(काष्ठा xt_statistic_info),
	.usersize   = दुरत्व(काष्ठा xt_statistic_info, master),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init statistic_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&xt_statistic_mt_reg);
पूर्ण

अटल व्योम __निकास statistic_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&xt_statistic_mt_reg);
पूर्ण

module_init(statistic_mt_init);
module_निकास(statistic_mt_निकास);
