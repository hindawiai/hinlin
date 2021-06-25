<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_mark
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  July, 2002
 *
 */

/* The mark target can be used in any chain,
 * I believe adding a mangle table just क्रम marking is total overसमाप्त.
 * Marking a frame करोesn't really change anything in the frame anyway.
 */

#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_mark_t.h>

अटल अचिन्हित पूर्णांक
ebt_mark_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_mark_t_info *info = par->targinfo;
	पूर्णांक action = info->target & -16;

	अगर (action == MARK_SET_VALUE)
		skb->mark = info->mark;
	अन्यथा अगर (action == MARK_OR_VALUE)
		skb->mark |= info->mark;
	अन्यथा अगर (action == MARK_AND_VALUE)
		skb->mark &= info->mark;
	अन्यथा
		skb->mark ^= info->mark;

	वापस info->target | ~EBT_VERDICT_BITS;
पूर्ण

अटल पूर्णांक ebt_mark_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ebt_mark_t_info *info = par->targinfo;
	पूर्णांक पंचांगp;

	पंचांगp = info->target | ~EBT_VERDICT_BITS;
	अगर (BASE_CHAIN && पंचांगp == EBT_RETURN)
		वापस -EINVAL;
	अगर (ebt_invalid_target(पंचांगp))
		वापस -EINVAL;
	पंचांगp = info->target & ~EBT_VERDICT_BITS;
	अगर (पंचांगp != MARK_SET_VALUE && पंचांगp != MARK_OR_VALUE &&
	    पंचांगp != MARK_AND_VALUE && पंचांगp != MARK_XOR_VALUE)
		वापस -EINVAL;
	वापस 0;
पूर्ण
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
काष्ठा compat_ebt_mark_t_info अणु
	compat_uदीर्घ_t mark;
	compat_uपूर्णांक_t target;
पूर्ण;

अटल व्योम mark_tg_compat_from_user(व्योम *dst, स्थिर व्योम *src)
अणु
	स्थिर काष्ठा compat_ebt_mark_t_info *user = src;
	काष्ठा ebt_mark_t_info *kern = dst;

	kern->mark = user->mark;
	kern->target = user->target;
पूर्ण

अटल पूर्णांक mark_tg_compat_to_user(व्योम __user *dst, स्थिर व्योम *src)
अणु
	काष्ठा compat_ebt_mark_t_info __user *user = dst;
	स्थिर काष्ठा ebt_mark_t_info *kern = src;

	अगर (put_user(kern->mark, &user->mark) ||
	    put_user(kern->target, &user->target))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा xt_target ebt_mark_tg_reg __पढ़ो_mostly = अणु
	.name		= "mark",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.target		= ebt_mark_tg,
	.checkentry	= ebt_mark_tg_check,
	.tarमाला_लोize	= माप(काष्ठा ebt_mark_t_info),
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	.compatsize	= माप(काष्ठा compat_ebt_mark_t_info),
	.compat_from_user = mark_tg_compat_from_user,
	.compat_to_user	= mark_tg_compat_to_user,
#पूर्ण_अगर
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_mark_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&ebt_mark_tg_reg);
पूर्ण

अटल व्योम __निकास ebt_mark_fini(व्योम)
अणु
	xt_unरेजिस्टर_target(&ebt_mark_tg_reg);
पूर्ण

module_init(ebt_mark_init);
module_निकास(ebt_mark_fini);
MODULE_DESCRIPTION("Ebtables: Packet mark modification");
MODULE_LICENSE("GPL");
