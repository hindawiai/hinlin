<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match ESP parameters. */

/* (C) 1999-2000 Yon Uriarte <yon@astaro.de>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>

#समावेश <linux/netfilter/xt_esp.h>
#समावेश <linux/netfilter/x_tables.h>

#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yon Uriarte <yon@astaro.de>");
MODULE_DESCRIPTION("Xtables: IPsec-ESP packet match");
MODULE_ALIAS("ipt_esp");
MODULE_ALIAS("ip6t_esp");

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

अटल bool esp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ip_esp_hdr *eh;
	काष्ठा ip_esp_hdr _esp;
	स्थिर काष्ठा xt_esp *espinfo = par->matchinfo;

	/* Must not be a fragment. */
	अगर (par->fragoff != 0)
		वापस false;

	eh = skb_header_poपूर्णांकer(skb, par->thoff, माप(_esp), &_esp);
	अगर (eh == शून्य) अणु
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to drop.
		 */
		pr_debug("Dropping evil ESP tinygram.\n");
		par->hotdrop = true;
		वापस false;
	पूर्ण

	वापस spi_match(espinfo->spis[0], espinfo->spis[1], ntohl(eh->spi),
			 !!(espinfo->invflags & XT_ESP_INV_SPI));
पूर्ण

अटल पूर्णांक esp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_esp *espinfo = par->matchinfo;

	अगर (espinfo->invflags & ~XT_ESP_INV_MASK) अणु
		pr_debug("unknown flags %X\n", espinfo->invflags);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match esp_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "esp",
		.family		= NFPROTO_IPV4,
		.checkentry	= esp_mt_check,
		.match		= esp_mt,
		.matchsize	= माप(काष्ठा xt_esp),
		.proto		= IPPROTO_ESP,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "esp",
		.family		= NFPROTO_IPV6,
		.checkentry	= esp_mt_check,
		.match		= esp_mt,
		.matchsize	= माप(काष्ठा xt_esp),
		.proto		= IPPROTO_ESP,
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init esp_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(esp_mt_reg, ARRAY_SIZE(esp_mt_reg));
पूर्ण

अटल व्योम __निकास esp_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(esp_mt_reg, ARRAY_SIZE(esp_mt_reg));
पूर्ण

module_init(esp_mt_init);
module_निकास(esp_mt_निकास);
