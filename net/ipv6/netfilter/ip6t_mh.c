<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C)2006 USAGI/WIDE Project
 *
 * Author:
 *	Masahide NAKAMURA @USAGI <masahide.nakamura.cz@hitachi.com>
 *
 * Based on net/netfilter/xt_tcpudp.c
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <net/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ipv6.h>
#समावेश <net/mip6.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv6/ip6t_mh.h>

MODULE_DESCRIPTION("Xtables: IPv6 Mobility Header match");
MODULE_LICENSE("GPL");

/* Returns 1 अगर the type is matched by the range, 0 otherwise */
अटल अंतरभूत bool
type_match(u_पूर्णांक8_t min, u_पूर्णांक8_t max, u_पूर्णांक8_t type, bool invert)
अणु
	वापस (type >= min && type <= max) ^ invert;
पूर्ण

अटल bool mh_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा ip6_mh _mh;
	स्थिर काष्ठा ip6_mh *mh;
	स्थिर काष्ठा ip6t_mh *mhinfo = par->matchinfo;

	/* Must not be a fragment. */
	अगर (par->fragoff != 0)
		वापस false;

	mh = skb_header_poपूर्णांकer(skb, par->thoff, माप(_mh), &_mh);
	अगर (mh == शून्य) अणु
		/* We've been asked to examine this packet, and we
		   can't.  Hence, no choice but to drop. */
		pr_debug("Dropping evil MH tinygram.\n");
		par->hotdrop = true;
		वापस false;
	पूर्ण

	अगर (mh->ip6mh_proto != IPPROTO_NONE) अणु
		pr_debug("Dropping invalid MH Payload Proto: %u\n",
			 mh->ip6mh_proto);
		par->hotdrop = true;
		वापस false;
	पूर्ण

	वापस type_match(mhinfo->types[0], mhinfo->types[1], mh->ip6mh_type,
			  !!(mhinfo->invflags & IP6T_MH_INV_TYPE));
पूर्ण

अटल पूर्णांक mh_mt6_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_mh *mhinfo = par->matchinfo;

	/* Must specअगरy no unknown invflags */
	वापस (mhinfo->invflags & ~IP6T_MH_INV_MASK) ? -EINVAL : 0;
पूर्ण

अटल काष्ठा xt_match mh_mt6_reg __पढ़ो_mostly = अणु
	.name		= "mh",
	.family		= NFPROTO_IPV6,
	.checkentry	= mh_mt6_check,
	.match		= mh_mt6,
	.matchsize	= माप(काष्ठा ip6t_mh),
	.proto		= IPPROTO_MH,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init mh_mt6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&mh_mt6_reg);
पूर्ण

अटल व्योम __निकास mh_mt6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&mh_mt6_reg);
पूर्ण

module_init(mh_mt6_init);
module_निकास(mh_mt6_निकास);
