<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match AH parameters. */

/* (C) 2001-2002 Andras Kis-Szabo <kisza@sch.bme.hu>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/types.h>
#समावेश <net/checksum.h>
#समावेश <net/ipv6.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter_ipv6/ip6t_ah.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: IPv6 IPsec-AH match");
MODULE_AUTHOR("Andras Kis-Szabo <kisza@sch.bme.hu>");

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

अटल bool ah_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा ip_auth_hdr _ah;
	स्थिर काष्ठा ip_auth_hdr *ah;
	स्थिर काष्ठा ip6t_ah *ahinfo = par->matchinfo;
	अचिन्हित पूर्णांक ptr = 0;
	अचिन्हित पूर्णांक hdrlen = 0;
	पूर्णांक err;

	err = ipv6_find_hdr(skb, &ptr, NEXTHDR_AUTH, शून्य, शून्य);
	अगर (err < 0) अणु
		अगर (err != -ENOENT)
			par->hotdrop = true;
		वापस false;
	पूर्ण

	ah = skb_header_poपूर्णांकer(skb, ptr, माप(_ah), &_ah);
	अगर (ah == शून्य) अणु
		par->hotdrop = true;
		वापस false;
	पूर्ण

	hdrlen = ipv6_authlen(ah);

	pr_debug("IPv6 AH LEN %u %u ", hdrlen, ah->hdrlen);
	pr_debug("RES %04X ", ah->reserved);
	pr_debug("SPI %u %08X\n", ntohl(ah->spi), ntohl(ah->spi));

	pr_debug("IPv6 AH spi %02X ",
		 spi_match(ahinfo->spis[0], ahinfo->spis[1],
			   ntohl(ah->spi),
			   !!(ahinfo->invflags & IP6T_AH_INV_SPI)));
	pr_debug("len %02X %04X %02X ",
		 ahinfo->hdrlen, hdrlen,
		 (!ahinfo->hdrlen ||
		  (ahinfo->hdrlen == hdrlen) ^
		  !!(ahinfo->invflags & IP6T_AH_INV_LEN)));
	pr_debug("res %02X %04X %02X\n",
		 ahinfo->hdrres, ah->reserved,
		 !(ahinfo->hdrres && ah->reserved));

	वापस spi_match(ahinfo->spis[0], ahinfo->spis[1],
			  ntohl(ah->spi),
			  !!(ahinfo->invflags & IP6T_AH_INV_SPI)) &&
		(!ahinfo->hdrlen ||
		 (ahinfo->hdrlen == hdrlen) ^
		 !!(ahinfo->invflags & IP6T_AH_INV_LEN)) &&
		!(ahinfo->hdrres && ah->reserved);
पूर्ण

अटल पूर्णांक ah_mt6_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_ah *ahinfo = par->matchinfo;

	अगर (ahinfo->invflags & ~IP6T_AH_INV_MASK) अणु
		pr_debug("unknown flags %X\n", ahinfo->invflags);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_match ah_mt6_reg __पढ़ो_mostly = अणु
	.name		= "ah",
	.family		= NFPROTO_IPV6,
	.match		= ah_mt6,
	.matchsize	= माप(काष्ठा ip6t_ah),
	.checkentry	= ah_mt6_check,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ah_mt6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ah_mt6_reg);
पूर्ण

अटल व्योम __निकास ah_mt6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&ah_mt6_reg);
पूर्ण

module_init(ah_mt6_init);
module_निकास(ah_mt6_निकास);
