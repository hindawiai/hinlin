<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999 Jथऊrथखme de Vivie <devivie@info.enserb.u-bordeaux.fr>
 * (C) 1999 Hervथऊ Eychenne <eychenne@info.enserb.u-bordeaux.fr>
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_limit.h>

काष्ठा xt_limit_priv अणु
	spinlock_t lock;
	अचिन्हित दीर्घ prev;
	uपूर्णांक32_t credit;
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Herve Eychenne <rv@wallfire.org>");
MODULE_DESCRIPTION("Xtables: rate-limit match");
MODULE_ALIAS("ipt_limit");
MODULE_ALIAS("ip6t_limit");

/* The algorithm used is the Simple Token Bucket Filter (TBF)
 * see net/sched/sch_tbf.c in the linux source tree
 */

/* Rusty: This is my (non-mathematically-inclined) understanding of
   this algorithm.  The `average rate' in jअगरfies becomes your initial
   amount of credit `credit' and the most credit you can ever have
   `credit_cap'.  The `peak rate' becomes the cost of passing the
   test, `cost'.

   `prev' tracks the last packet hit: you gain one credit per jअगरfy.
   If you get credit balance more than this, the extra credit is
   discarded.  Every समय the match passes, you lose `cost' credits;
   अगर you करोn't have that many, the test fails.

   See Alexey's क्रमmal explanation in net/sched/sch_tbf.c.

   To get the maximum range, we multiply by this factor (ie. you get N
   credits per jअगरfy).  We want to allow a rate as low as 1 per day
   (slowest userspace tool allows), which means
   CREDITS_PER_JIFFY*HZ*60*60*24 < 2^32. ie. */
#घोषणा MAX_CPJ (0xFFFFFFFF / (HZ*60*60*24))

/* Repeated shअगरt and or gives us all 1s, final shअगरt and add 1 gives
 * us the घातer of 2 below the theoretical max, so GCC simply करोes a
 * shअगरt. */
#घोषणा _POW2_BELOW2(x) ((x)|((x)>>1))
#घोषणा _POW2_BELOW4(x) (_POW2_BELOW2(x)|_POW2_BELOW2((x)>>2))
#घोषणा _POW2_BELOW8(x) (_POW2_BELOW4(x)|_POW2_BELOW4((x)>>4))
#घोषणा _POW2_BELOW16(x) (_POW2_BELOW8(x)|_POW2_BELOW8((x)>>8))
#घोषणा _POW2_BELOW32(x) (_POW2_BELOW16(x)|_POW2_BELOW16((x)>>16))
#घोषणा POW2_BELOW32(x) ((_POW2_BELOW32(x)>>1) + 1)

#घोषणा CREDITS_PER_JIFFY POW2_BELOW32(MAX_CPJ)

अटल bool
limit_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_rateinfo *r = par->matchinfo;
	काष्ठा xt_limit_priv *priv = r->master;
	अचिन्हित दीर्घ now = jअगरfies;

	spin_lock_bh(&priv->lock);
	priv->credit += (now - xchg(&priv->prev, now)) * CREDITS_PER_JIFFY;
	अगर (priv->credit > r->credit_cap)
		priv->credit = r->credit_cap;

	अगर (priv->credit >= r->cost) अणु
		/* We're not limited. */
		priv->credit -= r->cost;
		spin_unlock_bh(&priv->lock);
		वापस true;
	पूर्ण

	spin_unlock_bh(&priv->lock);
	वापस false;
पूर्ण

/* Precision saver. */
अटल u32 user2credits(u32 user)
अणु
	/* If multiplying would overflow... */
	अगर (user > 0xFFFFFFFF / (HZ*CREDITS_PER_JIFFY))
		/* Divide first. */
		वापस (user / XT_LIMIT_SCALE) * HZ * CREDITS_PER_JIFFY;

	वापस (user * HZ * CREDITS_PER_JIFFY) / XT_LIMIT_SCALE;
पूर्ण

अटल पूर्णांक limit_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_rateinfo *r = par->matchinfo;
	काष्ठा xt_limit_priv *priv;

	/* Check क्रम overflow. */
	अगर (r->burst == 0
	    || user2credits(r->avg * r->burst) < user2credits(r->avg)) अणु
		pr_info_ratelimited("Overflow, try lower: %u/%u\n",
				    r->avg, r->burst);
		वापस -दुस्फल;
	पूर्ण

	priv = kदो_स्मृति(माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;

	/* For SMP, we only want to use one set of state. */
	r->master = priv;
	/* User avg in seconds * XT_LIMIT_SCALE: convert to jअगरfies *
	   128. */
	priv->prev = jअगरfies;
	priv->credit = user2credits(r->avg * r->burst); /* Credits full. */
	अगर (r->cost == 0) अणु
		r->credit_cap = priv->credit; /* Credits full. */
		r->cost = user2credits(r->avg);
	पूर्ण
	spin_lock_init(&priv->lock);

	वापस 0;
पूर्ण

अटल व्योम limit_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	स्थिर काष्ठा xt_rateinfo *info = par->matchinfo;

	kमुक्त(info->master);
पूर्ण

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
काष्ठा compat_xt_rateinfo अणु
	u_पूर्णांक32_t avg;
	u_पूर्णांक32_t burst;

	compat_uदीर्घ_t prev;
	u_पूर्णांक32_t credit;
	u_पूर्णांक32_t credit_cap, cost;

	u_पूर्णांक32_t master;
पूर्ण;

/* To keep the full "prev" बारtamp, the upper 32 bits are stored in the
 * master poपूर्णांकer, which करोes not need to be preserved. */
अटल व्योम limit_mt_compat_from_user(व्योम *dst, स्थिर व्योम *src)
अणु
	स्थिर काष्ठा compat_xt_rateinfo *cm = src;
	काष्ठा xt_rateinfo m = अणु
		.avg		= cm->avg,
		.burst		= cm->burst,
		.prev		= cm->prev | (अचिन्हित दीर्घ)cm->master << 32,
		.credit		= cm->credit,
		.credit_cap	= cm->credit_cap,
		.cost		= cm->cost,
	पूर्ण;
	स_नकल(dst, &m, माप(m));
पूर्ण

अटल पूर्णांक limit_mt_compat_to_user(व्योम __user *dst, स्थिर व्योम *src)
अणु
	स्थिर काष्ठा xt_rateinfo *m = src;
	काष्ठा compat_xt_rateinfo cm = अणु
		.avg		= m->avg,
		.burst		= m->burst,
		.prev		= m->prev,
		.credit		= m->credit,
		.credit_cap	= m->credit_cap,
		.cost		= m->cost,
		.master		= m->prev >> 32,
	पूर्ण;
	वापस copy_to_user(dst, &cm, माप(cm)) ? -EFAULT : 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETFILTER_XTABLES_COMPAT */

अटल काष्ठा xt_match limit_mt_reg __पढ़ो_mostly = अणु
	.name             = "limit",
	.revision         = 0,
	.family           = NFPROTO_UNSPEC,
	.match            = limit_mt,
	.checkentry       = limit_mt_check,
	.destroy          = limit_mt_destroy,
	.matchsize        = माप(काष्ठा xt_rateinfo),
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	.compatsize       = माप(काष्ठा compat_xt_rateinfo),
	.compat_from_user = limit_mt_compat_from_user,
	.compat_to_user   = limit_mt_compat_to_user,
#पूर्ण_अगर
	.usersize         = दुरत्व(काष्ठा xt_rateinfo, prev),
	.me               = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init limit_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&limit_mt_reg);
पूर्ण

अटल व्योम __निकास limit_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&limit_mt_reg);
पूर्ण

module_init(limit_mt_init);
module_निकास(limit_mt_निकास);
