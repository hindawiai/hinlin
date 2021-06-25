<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  Kernel module to match IPComp parameters क्रम IPv4 and IPv6
 *
 *  Copyright (C) 2013 WindRiver
 *
 *  Author:
 *  Fan Du <fan.du@windriver.com>
 *
 *  Based on:
 *  net/netfilter/xt_esp.c
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>

#समावेश <linux/netfilter/xt_ipcomp.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fan Du <fan.du@windriver.com>");
MODULE_DESCRIPTION("Xtables: IPv4/6 IPsec-IPComp SPI match");
MODULE_ALIAS("ipt_ipcomp");
MODULE_ALIAS("ip6t_ipcomp");

/* Returns 1 अगर the spi is matched by the range, 0 otherwise */
अटल अंतरभूत bool
spi_match(u_पूर्णांक32_t min, u_पूर्णांक32_t max, u_पूर्णांक32_t spi, bool invert)
अणु
	bool r;
	pr_debug("spi_match:%c 0x%x <= 0x%x <= 0x%x\n",
		 invert ? '!' : ' ', min, spi, max);
	r = (spi >= min && spi <= max) ^ invert;
	pr_debug(" result %s\n", r ? "PASS" : "FAILED");
	वापस r;
पूर्ण

अटल bool comp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा ip_comp_hdr _comphdr;
	स्थिर काष्ठा ip_comp_hdr *chdr;
	स्थिर काष्ठा xt_ipcomp *compinfo = par->matchinfo;

	/* Must not be a fragment. */
	अगर (par->fragoff != 0)
		वापस false;

	chdr = skb_header_poपूर्णांकer(skb, par->thoff, माप(_comphdr), &_comphdr);
	अगर (chdr == शून्य) अणु
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to drop.
		 */
		pr_debug("Dropping evil IPComp tinygram.\n");
		par->hotdrop = true;
		वापस false;
	पूर्ण

	वापस spi_match(compinfo->spis[0], compinfo->spis[1],
			 ntohs(chdr->cpi),
			 !!(compinfo->invflags & XT_IPCOMP_INV_SPI));
पूर्ण

अटल पूर्णांक comp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_ipcomp *compinfo = par->matchinfo;

	/* Must specअगरy no unknown invflags */
	अगर (compinfo->invflags & ~XT_IPCOMP_INV_MASK) अणु
		pr_info_ratelimited("unknown flags %X\n", compinfo->invflags);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_match comp_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "ipcomp",
		.family		= NFPROTO_IPV4,
		.match		= comp_mt,
		.matchsize	= माप(काष्ठा xt_ipcomp),
		.proto		= IPPROTO_COMP,
		.checkentry	= comp_mt_check,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "ipcomp",
		.family		= NFPROTO_IPV6,
		.match		= comp_mt,
		.matchsize	= माप(काष्ठा xt_ipcomp),
		.proto		= IPPROTO_COMP,
		.checkentry	= comp_mt_check,
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init comp_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(comp_mt_reg, ARRAY_SIZE(comp_mt_reg));
पूर्ण

अटल व्योम __निकास comp_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(comp_mt_reg, ARRAY_SIZE(comp_mt_reg));
पूर्ण

module_init(comp_mt_init);
module_निकास(comp_mt_निकास);
