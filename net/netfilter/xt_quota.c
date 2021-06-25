<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * netfilter module to enक्रमce network quotas
 *
 * Sam Johnston <samj@samj.net>
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_quota.h>
#समावेश <linux/module.h>

काष्ठा xt_quota_priv अणु
	spinlock_t	lock;
	uपूर्णांक64_t	quota;
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sam Johnston <samj@samj.net>");
MODULE_DESCRIPTION("Xtables: countdown quota match");
MODULE_ALIAS("ipt_quota");
MODULE_ALIAS("ip6t_quota");

अटल bool
quota_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा xt_quota_info *q = (व्योम *)par->matchinfo;
	काष्ठा xt_quota_priv *priv = q->master;
	bool ret = q->flags & XT_QUOTA_INVERT;

	spin_lock_bh(&priv->lock);
	अगर (priv->quota >= skb->len) अणु
		priv->quota -= skb->len;
		ret = !ret;
	पूर्ण अन्यथा अणु
		/* we करो not allow even small packets from now on */
		priv->quota = 0;
	पूर्ण
	spin_unlock_bh(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक quota_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_quota_info *q = par->matchinfo;

	अगर (q->flags & ~XT_QUOTA_MASK)
		वापस -EINVAL;

	q->master = kदो_स्मृति(माप(*q->master), GFP_KERNEL);
	अगर (q->master == शून्य)
		वापस -ENOMEM;

	spin_lock_init(&q->master->lock);
	q->master->quota = q->quota;
	वापस 0;
पूर्ण

अटल व्योम quota_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_quota_info *q = par->matchinfo;

	kमुक्त(q->master);
पूर्ण

अटल काष्ठा xt_match quota_mt_reg __पढ़ो_mostly = अणु
	.name       = "quota",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.match      = quota_mt,
	.checkentry = quota_mt_check,
	.destroy    = quota_mt_destroy,
	.matchsize  = माप(काष्ठा xt_quota_info),
	.usersize   = दुरत्व(काष्ठा xt_quota_info, master),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init quota_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&quota_mt_reg);
पूर्ण

अटल व्योम __निकास quota_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&quota_mt_reg);
पूर्ण

module_init(quota_mt_init);
module_निकास(quota_mt_निकास);
