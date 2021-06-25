<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_limit
 *
 *	Authors:
 *	Tom Marshall <tommy@home.tig-grr.com>
 *
 *	Mostly copied from netfilter's ipt_limit.c, see that file क्रम
 *	more explanation
 *
 *  September, 2003
 *
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_limit.h>

अटल DEFINE_SPINLOCK(limit_lock);

#घोषणा MAX_CPJ (0xFFFFFFFF / (HZ*60*60*24))

#घोषणा _POW2_BELOW2(x) ((x)|((x)>>1))
#घोषणा _POW2_BELOW4(x) (_POW2_BELOW2(x)|_POW2_BELOW2((x)>>2))
#घोषणा _POW2_BELOW8(x) (_POW2_BELOW4(x)|_POW2_BELOW4((x)>>4))
#घोषणा _POW2_BELOW16(x) (_POW2_BELOW8(x)|_POW2_BELOW8((x)>>8))
#घोषणा _POW2_BELOW32(x) (_POW2_BELOW16(x)|_POW2_BELOW16((x)>>16))
#घोषणा POW2_BELOW32(x) ((_POW2_BELOW32(x)>>1) + 1)

#घोषणा CREDITS_PER_JIFFY POW2_BELOW32(MAX_CPJ)

अटल bool
ebt_limit_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा ebt_limit_info *info = (व्योम *)par->matchinfo;
	अचिन्हित दीर्घ now = jअगरfies;

	spin_lock_bh(&limit_lock);
	info->credit += (now - xchg(&info->prev, now)) * CREDITS_PER_JIFFY;
	अगर (info->credit > info->credit_cap)
		info->credit = info->credit_cap;

	अगर (info->credit >= info->cost) अणु
		/* We're not limited. */
		info->credit -= info->cost;
		spin_unlock_bh(&limit_lock);
		वापस true;
	पूर्ण

	spin_unlock_bh(&limit_lock);
	वापस false;
पूर्ण

/* Precision saver. */
अटल u_पूर्णांक32_t
user2credits(u_पूर्णांक32_t user)
अणु
	/* If multiplying would overflow... */
	अगर (user > 0xFFFFFFFF / (HZ*CREDITS_PER_JIFFY))
		/* Divide first. */
		वापस (user / EBT_LIMIT_SCALE) * HZ * CREDITS_PER_JIFFY;

	वापस (user * HZ * CREDITS_PER_JIFFY) / EBT_LIMIT_SCALE;
पूर्ण

अटल पूर्णांक ebt_limit_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा ebt_limit_info *info = par->matchinfo;

	/* Check क्रम overflow. */
	अगर (info->burst == 0 ||
	    user2credits(info->avg * info->burst) < user2credits(info->avg)) अणु
		pr_info_ratelimited("overflow, try lower: %u/%u\n",
				    info->avg, info->burst);
		वापस -EINVAL;
	पूर्ण

	/* User avg in seconds * EBT_LIMIT_SCALE: convert to jअगरfies * 128. */
	info->prev = jअगरfies;
	info->credit = user2credits(info->avg * info->burst);
	info->credit_cap = user2credits(info->avg * info->burst);
	info->cost = user2credits(info->avg);
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
/*
 * no conversion function needed --
 * only avg/burst have meaningful values in userspace.
 */
काष्ठा ebt_compat_limit_info अणु
	compat_uपूर्णांक_t avg, burst;
	compat_uदीर्घ_t prev;
	compat_uपूर्णांक_t credit, credit_cap, cost;
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा xt_match ebt_limit_mt_reg __पढ़ो_mostly = अणु
	.name		= "limit",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_limit_mt,
	.checkentry	= ebt_limit_mt_check,
	.matchsize	= माप(काष्ठा ebt_limit_info),
	.usersize	= दुरत्व(काष्ठा ebt_limit_info, prev),
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	.compatsize	= माप(काष्ठा ebt_compat_limit_info),
#पूर्ण_अगर
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_limit_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ebt_limit_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_limit_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_limit_mt_reg);
पूर्ण

module_init(ebt_limit_init);
module_निकास(ebt_limit_fini);
MODULE_DESCRIPTION("Ebtables: Rate-limit match");
MODULE_LICENSE("GPL");
