<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match Hop-by-Hop and Destination parameters. */

/* (C) 2001-2002 Andras Kis-Szabo <kisza@sch.bme.hu>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/types.h>
#समावेश <net/checksum.h>
#समावेश <net/ipv6.h>

#समावेश <यंत्र/byteorder.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter_ipv6/ip6t_opts.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: IPv6 Hop-By-Hop and Destination Header match");
MODULE_AUTHOR("Andras Kis-Szabo <kisza@sch.bme.hu>");
MODULE_ALIAS("ip6t_dst");

/*
 *  (Type & 0xC0) >> 6
 *	0	-> ignorable
 *	1	-> must drop the packet
 *	2	-> send ICMP PARM PROB regardless and drop packet
 *	3	-> Send ICMP अगर not a multicast address and drop packet
 *  (Type & 0x20) >> 5
 *	0	-> invariant
 *	1	-> can change the routing
 *  (Type & 0x1F) Type
 *	0	-> Pad1 (only 1 byte!)
 *	1	-> PadN LENGTH info (total length = length + 2)
 *	C0 | 2	-> JUMBO 4 x x x x ( xxxx > 64k )
 *	5	-> RTALERT 2 x x
 */

अटल काष्ठा xt_match hbh_mt6_reg[] __पढ़ो_mostly;

अटल bool
hbh_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा ipv6_opt_hdr _optsh;
	स्थिर काष्ठा ipv6_opt_hdr *oh;
	स्थिर काष्ठा ip6t_opts *optinfo = par->matchinfo;
	अचिन्हित पूर्णांक temp;
	अचिन्हित पूर्णांक ptr = 0;
	अचिन्हित पूर्णांक hdrlen = 0;
	bool ret = false;
	u8 _opttype;
	u8 _optlen;
	स्थिर u_पूर्णांक8_t *tp = शून्य;
	स्थिर u_पूर्णांक8_t *lp = शून्य;
	अचिन्हित पूर्णांक optlen;
	पूर्णांक err;

	err = ipv6_find_hdr(skb, &ptr,
			    (par->match == &hbh_mt6_reg[0]) ?
			    NEXTHDR_HOP : NEXTHDR_DEST, शून्य, शून्य);
	अगर (err < 0) अणु
		अगर (err != -ENOENT)
			par->hotdrop = true;
		वापस false;
	पूर्ण

	oh = skb_header_poपूर्णांकer(skb, ptr, माप(_optsh), &_optsh);
	अगर (oh == शून्य) अणु
		par->hotdrop = true;
		वापस false;
	पूर्ण

	hdrlen = ipv6_optlen(oh);
	अगर (skb->len - ptr < hdrlen) अणु
		/* Packet smaller than it's length field */
		वापस false;
	पूर्ण

	pr_debug("IPv6 OPTS LEN %u %u ", hdrlen, oh->hdrlen);

	pr_debug("len %02X %04X %02X ",
		 optinfo->hdrlen, hdrlen,
		 (!(optinfo->flags & IP6T_OPTS_LEN) ||
		  ((optinfo->hdrlen == hdrlen) ^
		   !!(optinfo->invflags & IP6T_OPTS_INV_LEN))));

	ret = (!(optinfo->flags & IP6T_OPTS_LEN) ||
	       ((optinfo->hdrlen == hdrlen) ^
		!!(optinfo->invflags & IP6T_OPTS_INV_LEN)));

	ptr += 2;
	hdrlen -= 2;
	अगर (!(optinfo->flags & IP6T_OPTS_OPTS)) अणु
		वापस ret;
	पूर्ण अन्यथा अणु
		pr_debug("Strict ");
		pr_debug("#%d ", optinfo->optsnr);
		क्रम (temp = 0; temp < optinfo->optsnr; temp++) अणु
			/* type field exists ? */
			अगर (hdrlen < 1)
				अवरोध;
			tp = skb_header_poपूर्णांकer(skb, ptr, माप(_opttype),
						&_opttype);
			अगर (tp == शून्य)
				अवरोध;

			/* Type check */
			अगर (*tp != (optinfo->opts[temp] & 0xFF00) >> 8) अणु
				pr_debug("Tbad %02X %02X\n", *tp,
					 (optinfo->opts[temp] & 0xFF00) >> 8);
				वापस false;
			पूर्ण अन्यथा अणु
				pr_debug("Tok ");
			पूर्ण
			/* Length check */
			अगर (*tp) अणु
				u16 spec_len;

				/* length field exists ? */
				अगर (hdrlen < 2)
					अवरोध;
				lp = skb_header_poपूर्णांकer(skb, ptr + 1,
							माप(_optlen),
							&_optlen);
				अगर (lp == शून्य)
					अवरोध;
				spec_len = optinfo->opts[temp] & 0x00FF;

				अगर (spec_len != 0x00FF && spec_len != *lp) अणु
					pr_debug("Lbad %02X %04X\n", *lp,
						 spec_len);
					वापस false;
				पूर्ण
				pr_debug("Lok ");
				optlen = *lp + 2;
			पूर्ण अन्यथा अणु
				pr_debug("Pad1\n");
				optlen = 1;
			पूर्ण

			/* Step to the next */
			pr_debug("len%04X\n", optlen);

			अगर ((ptr > skb->len - optlen || hdrlen < optlen) &&
			    temp < optinfo->optsnr - 1) अणु
				pr_debug("new pointer is too large!\n");
				अवरोध;
			पूर्ण
			ptr += optlen;
			hdrlen -= optlen;
		पूर्ण
		अगर (temp == optinfo->optsnr)
			वापस ret;
		अन्यथा
			वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक hbh_mt6_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_opts *optsinfo = par->matchinfo;

	अगर (optsinfo->invflags & ~IP6T_OPTS_INV_MASK) अणु
		pr_debug("unknown flags %X\n", optsinfo->invflags);
		वापस -EINVAL;
	पूर्ण

	अगर (optsinfo->flags & IP6T_OPTS_NSTRICT) अणु
		pr_debug("Not strict - not implemented");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match hbh_mt6_reg[] __पढ़ो_mostly = अणु
	अणु
		/* Note, hbh_mt6 relies on the order of hbh_mt6_reg */
		.name		= "hbh",
		.family		= NFPROTO_IPV6,
		.match		= hbh_mt6,
		.matchsize	= माप(काष्ठा ip6t_opts),
		.checkentry	= hbh_mt6_check,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "dst",
		.family		= NFPROTO_IPV6,
		.match		= hbh_mt6,
		.matchsize	= माप(काष्ठा ip6t_opts),
		.checkentry	= hbh_mt6_check,
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hbh_mt6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(hbh_mt6_reg, ARRAY_SIZE(hbh_mt6_reg));
पूर्ण

अटल व्योम __निकास hbh_mt6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(hbh_mt6_reg, ARRAY_SIZE(hbh_mt6_reg));
पूर्ण

module_init(hbh_mt6_init);
module_निकास(hbh_mt6_निकास);
