<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match AH parameters. */
/* (C) 1999-2000 Yon Uriarte <yon@astaro.de>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>

#समावेश <linux/netfilter_ipv4/ipt_ah.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yon Uriarte <yon@astaro.de>");
MODULE_DESCRIPTION("Xtables: IPv4 IPsec-AH SPI match");

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

अटल bool ah_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा ip_auth_hdr _ahdr;
	स्थिर काष्ठा ip_auth_hdr *ah;
	स्थिर काष्ठा ipt_ah *ahinfo = par->matchinfo;

	/* Must not be a fragment. */
	अगर (par->fragoff != 0)
		वापस false;

	ah = skb_header_poपूर्णांकer(skb, par->thoff, माप(_ahdr), &_ahdr);
	अगर (ah == शून्य) अणु
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to drop.
		 */
		pr_debug("Dropping evil AH tinygram.\n");
		par->hotdrop = true;
		वापस false;
	पूर्ण

	वापस spi_match(ahinfo->spis[0], ahinfo->spis[1],
			 ntohl(ah->spi),
			 !!(ahinfo->invflags & IPT_AH_INV_SPI));
पूर्ण

अटल पूर्णांक ah_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ipt_ah *ahinfo = par->matchinfo;

	/* Must specअगरy no unknown invflags */
	अगर (ahinfo->invflags & ~IPT_AH_INV_MASK) अणु
		pr_debug("unknown flags %X\n", ahinfo->invflags);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_match ah_mt_reg __पढ़ो_mostly = अणु
	.name		= "ah",
	.family		= NFPROTO_IPV4,
	.match		= ah_mt,
	.matchsize	= माप(काष्ठा ipt_ah),
	.proto		= IPPROTO_AH,
	.checkentry	= ah_mt_check,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ah_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ah_mt_reg);
पूर्ण

अटल व्योम __निकास ah_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&ah_mt_reg);
पूर्ण

module_init(ah_mt_init);
module_निकास(ah_mt_निकास);
