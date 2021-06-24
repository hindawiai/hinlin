<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_mark_m
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  July, 2002
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_mark_m.h>

अटल bool
ebt_mark_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_mark_m_info *info = par->matchinfo;

	अगर (info->biपंचांगask & EBT_MARK_OR)
		वापस !!(skb->mark & info->mask) ^ info->invert;
	वापस ((skb->mark & info->mask) == info->mark) ^ info->invert;
पूर्ण

अटल पूर्णांक ebt_mark_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ebt_mark_m_info *info = par->matchinfo;

	अगर (info->biपंचांगask & ~EBT_MARK_MASK)
		वापस -EINVAL;
	अगर ((info->biपंचांगask & EBT_MARK_OR) && (info->biपंचांगask & EBT_MARK_AND))
		वापस -EINVAL;
	अगर (!info->biपंचांगask)
		वापस -EINVAL;
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
काष्ठा compat_ebt_mark_m_info अणु
	compat_uदीर्घ_t mark, mask;
	uपूर्णांक8_t invert, biपंचांगask;
पूर्ण;

अटल व्योम mark_mt_compat_from_user(व्योम *dst, स्थिर व्योम *src)
अणु
	स्थिर काष्ठा compat_ebt_mark_m_info *user = src;
	काष्ठा ebt_mark_m_info *kern = dst;

	kern->mark = user->mark;
	kern->mask = user->mask;
	kern->invert = user->invert;
	kern->biपंचांगask = user->biपंचांगask;
पूर्ण

अटल पूर्णांक mark_mt_compat_to_user(व्योम __user *dst, स्थिर व्योम *src)
अणु
	काष्ठा compat_ebt_mark_m_info __user *user = dst;
	स्थिर काष्ठा ebt_mark_m_info *kern = src;

	अगर (put_user(kern->mark, &user->mark) ||
	    put_user(kern->mask, &user->mask) ||
	    put_user(kern->invert, &user->invert) ||
	    put_user(kern->biपंचांगask, &user->biपंचांगask))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा xt_match ebt_mark_mt_reg __पढ़ो_mostly = अणु
	.name		= "mark_m",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_mark_mt,
	.checkentry	= ebt_mark_mt_check,
	.matchsize	= माप(काष्ठा ebt_mark_m_info),
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	.compatsize	= माप(काष्ठा compat_ebt_mark_m_info),
	.compat_from_user = mark_mt_compat_from_user,
	.compat_to_user	= mark_mt_compat_to_user,
#पूर्ण_अगर
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_mark_m_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ebt_mark_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_mark_m_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_mark_mt_reg);
पूर्ण

module_init(ebt_mark_m_init);
module_निकास(ebt_mark_m_fini);
MODULE_DESCRIPTION("Ebtables: Packet mark match");
MODULE_LICENSE("GPL");
