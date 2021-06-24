<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ipv6header match - matches IPv6 packets based
   on whether they contain certain headers */

/* Original idea: Brad Chapman
 * Rewritten by: Andras Kis-Szabo <kisza@sch.bme.hu> */

/* (C) 2001-2002 Andras Kis-Szabo <kisza@sch.bme.hu>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/types.h>
#समावेश <net/checksum.h>
#समावेश <net/ipv6.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_ipv6/ip6t_ipv6header.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: IPv6 header types match");
MODULE_AUTHOR("Andras Kis-Szabo <kisza@sch.bme.hu>");

अटल bool
ipv6header_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ip6t_ipv6header_info *info = par->matchinfo;
	अचिन्हित पूर्णांक temp;
	पूर्णांक len;
	u8 nexthdr;
	अचिन्हित पूर्णांक ptr;

	/* Make sure this isn't an evil packet */

	/* type of the 1st exthdr */
	nexthdr = ipv6_hdr(skb)->nexthdr;
	/* poपूर्णांकer to the 1st exthdr */
	ptr = माप(काष्ठा ipv6hdr);
	/* available length */
	len = skb->len - ptr;
	temp = 0;

	जबतक (nf_ip6_ext_hdr(nexthdr)) अणु
		स्थिर काष्ठा ipv6_opt_hdr *hp;
		काष्ठा ipv6_opt_hdr _hdr;
		पूर्णांक hdrlen;

		/* No more exthdr -> evaluate */
		अगर (nexthdr == NEXTHDR_NONE) अणु
			temp |= MASK_NONE;
			अवरोध;
		पूर्ण
		/* Is there enough space क्रम the next ext header? */
		अगर (len < (पूर्णांक)माप(काष्ठा ipv6_opt_hdr))
			वापस false;
		/* ESP -> evaluate */
		अगर (nexthdr == NEXTHDR_ESP) अणु
			temp |= MASK_ESP;
			अवरोध;
		पूर्ण

		hp = skb_header_poपूर्णांकer(skb, ptr, माप(_hdr), &_hdr);
		अगर (!hp) अणु
			par->hotdrop = true;
			वापस false;
		पूर्ण

		/* Calculate the header length */
		अगर (nexthdr == NEXTHDR_FRAGMENT)
			hdrlen = 8;
		अन्यथा अगर (nexthdr == NEXTHDR_AUTH)
			hdrlen = ipv6_authlen(hp);
		अन्यथा
			hdrlen = ipv6_optlen(hp);

		/* set the flag */
		चयन (nexthdr) अणु
		हाल NEXTHDR_HOP:
			temp |= MASK_HOPOPTS;
			अवरोध;
		हाल NEXTHDR_ROUTING:
			temp |= MASK_ROUTING;
			अवरोध;
		हाल NEXTHDR_FRAGMENT:
			temp |= MASK_FRAGMENT;
			अवरोध;
		हाल NEXTHDR_AUTH:
			temp |= MASK_AH;
			अवरोध;
		हाल NEXTHDR_DEST:
			temp |= MASK_DSTOPTS;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण

		nexthdr = hp->nexthdr;
		len -= hdrlen;
		ptr += hdrlen;
		अगर (ptr > skb->len)
			अवरोध;
	पूर्ण

	अगर (nexthdr != NEXTHDR_NONE && nexthdr != NEXTHDR_ESP)
		temp |= MASK_PROTO;

	अगर (info->modeflag)
		वापस !((temp ^ info->matchflags ^ info->invflags)
			 & info->matchflags);
	अन्यथा अणु
		अगर (info->invflags)
			वापस temp != info->matchflags;
		अन्यथा
			वापस temp == info->matchflags;
	पूर्ण
पूर्ण

अटल पूर्णांक ipv6header_mt6_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_ipv6header_info *info = par->matchinfo;

	/* invflags is 0 or 0xff in hard mode */
	अगर ((!info->modeflag) && info->invflags != 0x00 &&
	    info->invflags != 0xFF)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा xt_match ipv6header_mt6_reg __पढ़ो_mostly = अणु
	.name		= "ipv6header",
	.family		= NFPROTO_IPV6,
	.match		= ipv6header_mt6,
	.matchsize	= माप(काष्ठा ip6t_ipv6header_info),
	.checkentry	= ipv6header_mt6_check,
	.destroy	= शून्य,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ipv6header_mt6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ipv6header_mt6_reg);
पूर्ण

अटल व्योम __निकास ipv6header_mt6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&ipv6header_mt6_reg);
पूर्ण

module_init(ipv6header_mt6_init);
module_निकास(ipv6header_mt6_निकास);
