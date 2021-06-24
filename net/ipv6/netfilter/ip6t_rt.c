<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match ROUTING parameters. */

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
#समावेश <linux/netfilter_ipv6/ip6t_rt.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: IPv6 Routing Header match");
MODULE_AUTHOR("Andras Kis-Szabo <kisza@sch.bme.hu>");

/* Returns 1 अगर the id is matched by the range, 0 otherwise */
अटल अंतरभूत bool
segsleft_match(u_पूर्णांक32_t min, u_पूर्णांक32_t max, u_पूर्णांक32_t id, bool invert)
अणु
	bool r;
	pr_debug("segsleft_match:%c 0x%x <= 0x%x <= 0x%x\n",
		 invert ? '!' : ' ', min, id, max);
	r = (id >= min && id <= max) ^ invert;
	pr_debug(" result %s\n", r ? "PASS" : "FAILED");
	वापस r;
पूर्ण

अटल bool rt_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा ipv6_rt_hdr _route;
	स्थिर काष्ठा ipv6_rt_hdr *rh;
	स्थिर काष्ठा ip6t_rt *rtinfo = par->matchinfo;
	अचिन्हित पूर्णांक temp;
	अचिन्हित पूर्णांक ptr = 0;
	अचिन्हित पूर्णांक hdrlen = 0;
	bool ret = false;
	काष्ठा in6_addr _addr;
	स्थिर काष्ठा in6_addr *ap;
	पूर्णांक err;

	err = ipv6_find_hdr(skb, &ptr, NEXTHDR_ROUTING, शून्य, शून्य);
	अगर (err < 0) अणु
		अगर (err != -ENOENT)
			par->hotdrop = true;
		वापस false;
	पूर्ण

	rh = skb_header_poपूर्णांकer(skb, ptr, माप(_route), &_route);
	अगर (rh == शून्य) अणु
		par->hotdrop = true;
		वापस false;
	पूर्ण

	hdrlen = ipv6_optlen(rh);
	अगर (skb->len - ptr < hdrlen) अणु
		/* Pcket smaller than its length field */
		वापस false;
	पूर्ण

	pr_debug("IPv6 RT LEN %u %u ", hdrlen, rh->hdrlen);
	pr_debug("TYPE %04X ", rh->type);
	pr_debug("SGS_LEFT %u %02X\n", rh->segments_left, rh->segments_left);

	pr_debug("IPv6 RT segsleft %02X ",
		 segsleft_match(rtinfo->segsleft[0], rtinfo->segsleft[1],
				rh->segments_left,
				!!(rtinfo->invflags & IP6T_RT_INV_SGS)));
	pr_debug("type %02X %02X %02X ",
		 rtinfo->rt_type, rh->type,
		 (!(rtinfo->flags & IP6T_RT_TYP) ||
		  ((rtinfo->rt_type == rh->type) ^
		   !!(rtinfo->invflags & IP6T_RT_INV_TYP))));
	pr_debug("len %02X %04X %02X ",
		 rtinfo->hdrlen, hdrlen,
		 !(rtinfo->flags & IP6T_RT_LEN) ||
		  ((rtinfo->hdrlen == hdrlen) ^
		   !!(rtinfo->invflags & IP6T_RT_INV_LEN)));
	pr_debug("res %02X %02X %02X ",
		 rtinfo->flags & IP6T_RT_RES,
		 ((स्थिर काष्ठा rt0_hdr *)rh)->reserved,
		 !((rtinfo->flags & IP6T_RT_RES) &&
		   (((स्थिर काष्ठा rt0_hdr *)rh)->reserved)));

	ret = (segsleft_match(rtinfo->segsleft[0], rtinfo->segsleft[1],
			      rh->segments_left,
			      !!(rtinfo->invflags & IP6T_RT_INV_SGS))) &&
	      (!(rtinfo->flags & IP6T_RT_LEN) ||
	       ((rtinfo->hdrlen == hdrlen) ^
		!!(rtinfo->invflags & IP6T_RT_INV_LEN))) &&
	      (!(rtinfo->flags & IP6T_RT_TYP) ||
	       ((rtinfo->rt_type == rh->type) ^
		!!(rtinfo->invflags & IP6T_RT_INV_TYP)));

	अगर (ret && (rtinfo->flags & IP6T_RT_RES)) अणु
		स्थिर u_पूर्णांक32_t *rp;
		u_पूर्णांक32_t _reserved;
		rp = skb_header_poपूर्णांकer(skb,
					ptr + दुरत्व(काष्ठा rt0_hdr,
						       reserved),
					माप(_reserved),
					&_reserved);

		ret = (*rp == 0);
	पूर्ण

	pr_debug("#%d ", rtinfo->addrnr);
	अगर (!(rtinfo->flags & IP6T_RT_FST)) अणु
		वापस ret;
	पूर्ण अन्यथा अगर (rtinfo->flags & IP6T_RT_FST_NSTRICT) अणु
		pr_debug("Not strict ");
		अगर (rtinfo->addrnr > (अचिन्हित पूर्णांक)((hdrlen - 8) / 16)) अणु
			pr_debug("There isn't enough space\n");
			वापस false;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक i = 0;

			pr_debug("#%d ", rtinfo->addrnr);
			क्रम (temp = 0;
			     temp < (अचिन्हित पूर्णांक)((hdrlen - 8) / 16);
			     temp++) अणु
				ap = skb_header_poपूर्णांकer(skb,
							ptr
							+ माप(काष्ठा rt0_hdr)
							+ temp * माप(_addr),
							माप(_addr),
							&_addr);

				अगर (ap == शून्य) अणु
					par->hotdrop = true;
					वापस false;
				पूर्ण

				अगर (ipv6_addr_equal(ap, &rtinfo->addrs[i])) अणु
					pr_debug("i=%d temp=%d;\n", i, temp);
					i++;
				पूर्ण
				अगर (i == rtinfo->addrnr)
					अवरोध;
			पूर्ण
			pr_debug("i=%d #%d\n", i, rtinfo->addrnr);
			अगर (i == rtinfo->addrnr)
				वापस ret;
			अन्यथा
				वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_debug("Strict ");
		अगर (rtinfo->addrnr > (अचिन्हित पूर्णांक)((hdrlen - 8) / 16)) अणु
			pr_debug("There isn't enough space\n");
			वापस false;
		पूर्ण अन्यथा अणु
			pr_debug("#%d ", rtinfo->addrnr);
			क्रम (temp = 0; temp < rtinfo->addrnr; temp++) अणु
				ap = skb_header_poपूर्णांकer(skb,
							ptr
							+ माप(काष्ठा rt0_hdr)
							+ temp * माप(_addr),
							माप(_addr),
							&_addr);
				अगर (ap == शून्य) अणु
					par->hotdrop = true;
					वापस false;
				पूर्ण

				अगर (!ipv6_addr_equal(ap, &rtinfo->addrs[temp]))
					अवरोध;
			पूर्ण
			pr_debug("temp=%d #%d\n", temp, rtinfo->addrnr);
			अगर (temp == rtinfo->addrnr &&
			    temp == (अचिन्हित पूर्णांक)((hdrlen - 8) / 16))
				वापस ret;
			अन्यथा
				वापस false;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक rt_mt6_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_rt *rtinfo = par->matchinfo;

	अगर (rtinfo->invflags & ~IP6T_RT_INV_MASK) अणु
		pr_debug("unknown flags %X\n", rtinfo->invflags);
		वापस -EINVAL;
	पूर्ण
	अगर ((rtinfo->flags & (IP6T_RT_RES | IP6T_RT_FST_MASK)) &&
	    (!(rtinfo->flags & IP6T_RT_TYP) ||
	     (rtinfo->rt_type != 0) ||
	     (rtinfo->invflags & IP6T_RT_INV_TYP))) अणु
		pr_debug("`--rt-type 0' required before `--rt-0-*'");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match rt_mt6_reg __पढ़ो_mostly = अणु
	.name		= "rt",
	.family		= NFPROTO_IPV6,
	.match		= rt_mt6,
	.matchsize	= माप(काष्ठा ip6t_rt),
	.checkentry	= rt_mt6_check,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init rt_mt6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&rt_mt6_reg);
पूर्ण

अटल व्योम __निकास rt_mt6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&rt_mt6_reg);
पूर्ण

module_init(rt_mt6_init);
module_निकास(rt_mt6_निकास);
