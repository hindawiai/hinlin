<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Kernel module to match Segment Routing Header (SRH) parameters. */

/* Author:
 * Ahmed Abdelsalam <amsalam20@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/types.h>
#समावेश <net/ipv6.h>
#समावेश <net/seg6.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv6/ip6t_srh.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

/* Test a काष्ठा->mt_invflags and a boolean क्रम inequality */
#घोषणा NF_SRH_INVF(ptr, flag, boolean)	\
	((boolean) ^ !!((ptr)->mt_invflags & (flag)))

अटल bool srh_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ip6t_srh *srhinfo = par->matchinfo;
	काष्ठा ipv6_sr_hdr *srh;
	काष्ठा ipv6_sr_hdr _srh;
	पूर्णांक hdrlen, srhoff = 0;

	अगर (ipv6_find_hdr(skb, &srhoff, IPPROTO_ROUTING, शून्य, शून्य) < 0)
		वापस false;
	srh = skb_header_poपूर्णांकer(skb, srhoff, माप(_srh), &_srh);
	अगर (!srh)
		वापस false;

	hdrlen = ipv6_optlen(srh);
	अगर (skb->len - srhoff < hdrlen)
		वापस false;

	अगर (srh->type != IPV6_SRCRT_TYPE_4)
		वापस false;

	अगर (srh->segments_left > srh->first_segment)
		वापस false;

	/* Next Header matching */
	अगर (srhinfo->mt_flags & IP6T_SRH_NEXTHDR)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_NEXTHDR,
				!(srh->nexthdr == srhinfo->next_hdr)))
			वापस false;

	/* Header Extension Length matching */
	अगर (srhinfo->mt_flags & IP6T_SRH_LEN_EQ)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LEN_EQ,
				!(srh->hdrlen == srhinfo->hdr_len)))
			वापस false;

	अगर (srhinfo->mt_flags & IP6T_SRH_LEN_GT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LEN_GT,
				!(srh->hdrlen > srhinfo->hdr_len)))
			वापस false;

	अगर (srhinfo->mt_flags & IP6T_SRH_LEN_LT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LEN_LT,
				!(srh->hdrlen < srhinfo->hdr_len)))
			वापस false;

	/* Segments Left matching */
	अगर (srhinfo->mt_flags & IP6T_SRH_SEGS_EQ)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_SEGS_EQ,
				!(srh->segments_left == srhinfo->segs_left)))
			वापस false;

	अगर (srhinfo->mt_flags & IP6T_SRH_SEGS_GT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_SEGS_GT,
				!(srh->segments_left > srhinfo->segs_left)))
			वापस false;

	अगर (srhinfo->mt_flags & IP6T_SRH_SEGS_LT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_SEGS_LT,
				!(srh->segments_left < srhinfo->segs_left)))
			वापस false;

	/**
	 * Last Entry matching
	 * Last_Entry field was पूर्णांकroduced in revision 6 of the SRH draft.
	 * It was called First_Segment in the previous revision
	 */
	अगर (srhinfo->mt_flags & IP6T_SRH_LAST_EQ)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LAST_EQ,
				!(srh->first_segment == srhinfo->last_entry)))
			वापस false;

	अगर (srhinfo->mt_flags & IP6T_SRH_LAST_GT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LAST_GT,
				!(srh->first_segment > srhinfo->last_entry)))
			वापस false;

	अगर (srhinfo->mt_flags & IP6T_SRH_LAST_LT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LAST_LT,
				!(srh->first_segment < srhinfo->last_entry)))
			वापस false;

	/**
	 * Tag matchig
	 * Tag field was पूर्णांकroduced in revision 6 of the SRH draft.
	 */
	अगर (srhinfo->mt_flags & IP6T_SRH_TAG)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_TAG,
				!(srh->tag == srhinfo->tag)))
			वापस false;
	वापस true;
पूर्ण

अटल bool srh1_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	पूर्णांक hdrlen, psiकरोff, nsiकरोff, lsiकरोff, srhoff = 0;
	स्थिर काष्ठा ip6t_srh1 *srhinfo = par->matchinfo;
	काष्ठा in6_addr *psid, *nsid, *lsid;
	काष्ठा in6_addr _psid, _nsid, _lsid;
	काष्ठा ipv6_sr_hdr *srh;
	काष्ठा ipv6_sr_hdr _srh;

	अगर (ipv6_find_hdr(skb, &srhoff, IPPROTO_ROUTING, शून्य, शून्य) < 0)
		वापस false;
	srh = skb_header_poपूर्णांकer(skb, srhoff, माप(_srh), &_srh);
	अगर (!srh)
		वापस false;

	hdrlen = ipv6_optlen(srh);
	अगर (skb->len - srhoff < hdrlen)
		वापस false;

	अगर (srh->type != IPV6_SRCRT_TYPE_4)
		वापस false;

	अगर (srh->segments_left > srh->first_segment)
		वापस false;

	/* Next Header matching */
	अगर (srhinfo->mt_flags & IP6T_SRH_NEXTHDR)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_NEXTHDR,
				!(srh->nexthdr == srhinfo->next_hdr)))
			वापस false;

	/* Header Extension Length matching */
	अगर (srhinfo->mt_flags & IP6T_SRH_LEN_EQ)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LEN_EQ,
				!(srh->hdrlen == srhinfo->hdr_len)))
			वापस false;
	अगर (srhinfo->mt_flags & IP6T_SRH_LEN_GT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LEN_GT,
				!(srh->hdrlen > srhinfo->hdr_len)))
			वापस false;
	अगर (srhinfo->mt_flags & IP6T_SRH_LEN_LT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LEN_LT,
				!(srh->hdrlen < srhinfo->hdr_len)))
			वापस false;

	/* Segments Left matching */
	अगर (srhinfo->mt_flags & IP6T_SRH_SEGS_EQ)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_SEGS_EQ,
				!(srh->segments_left == srhinfo->segs_left)))
			वापस false;
	अगर (srhinfo->mt_flags & IP6T_SRH_SEGS_GT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_SEGS_GT,
				!(srh->segments_left > srhinfo->segs_left)))
			वापस false;
	अगर (srhinfo->mt_flags & IP6T_SRH_SEGS_LT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_SEGS_LT,
				!(srh->segments_left < srhinfo->segs_left)))
			वापस false;

	/**
	 * Last Entry matching
	 * Last_Entry field was पूर्णांकroduced in revision 6 of the SRH draft.
	 * It was called First_Segment in the previous revision
	 */
	अगर (srhinfo->mt_flags & IP6T_SRH_LAST_EQ)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LAST_EQ,
				!(srh->first_segment == srhinfo->last_entry)))
			वापस false;
	अगर (srhinfo->mt_flags & IP6T_SRH_LAST_GT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LAST_GT,
				!(srh->first_segment > srhinfo->last_entry)))
			वापस false;
	अगर (srhinfo->mt_flags & IP6T_SRH_LAST_LT)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LAST_LT,
				!(srh->first_segment < srhinfo->last_entry)))
			वापस false;

	/**
	 * Tag matchig
	 * Tag field was पूर्णांकroduced in revision 6 of the SRH draft
	 */
	अगर (srhinfo->mt_flags & IP6T_SRH_TAG)
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_TAG,
				!(srh->tag == srhinfo->tag)))
			वापस false;

	/* Previous SID matching */
	अगर (srhinfo->mt_flags & IP6T_SRH_PSID) अणु
		अगर (srh->segments_left == srh->first_segment)
			वापस false;
		psiकरोff = srhoff + माप(काष्ठा ipv6_sr_hdr) +
			  ((srh->segments_left + 1) * माप(काष्ठा in6_addr));
		psid = skb_header_poपूर्णांकer(skb, psiकरोff, माप(_psid), &_psid);
		अगर (!psid)
			वापस false;
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_PSID,
				ipv6_masked_addr_cmp(psid, &srhinfo->psid_msk,
						     &srhinfo->psid_addr)))
			वापस false;
	पूर्ण

	/* Next SID matching */
	अगर (srhinfo->mt_flags & IP6T_SRH_NSID) अणु
		अगर (srh->segments_left == 0)
			वापस false;
		nsiकरोff = srhoff + माप(काष्ठा ipv6_sr_hdr) +
			  ((srh->segments_left - 1) * माप(काष्ठा in6_addr));
		nsid = skb_header_poपूर्णांकer(skb, nsiकरोff, माप(_nsid), &_nsid);
		अगर (!nsid)
			वापस false;
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_NSID,
				ipv6_masked_addr_cmp(nsid, &srhinfo->nsid_msk,
						     &srhinfo->nsid_addr)))
			वापस false;
	पूर्ण

	/* Last SID matching */
	अगर (srhinfo->mt_flags & IP6T_SRH_LSID) अणु
		lsiकरोff = srhoff + माप(काष्ठा ipv6_sr_hdr);
		lsid = skb_header_poपूर्णांकer(skb, lsiकरोff, माप(_lsid), &_lsid);
		अगर (!lsid)
			वापस false;
		अगर (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LSID,
				ipv6_masked_addr_cmp(lsid, &srhinfo->lsid_msk,
						     &srhinfo->lsid_addr)))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक srh_mt6_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_srh *srhinfo = par->matchinfo;

	अगर (srhinfo->mt_flags & ~IP6T_SRH_MASK) अणु
		pr_info_ratelimited("unknown srh match flags  %X\n",
				    srhinfo->mt_flags);
		वापस -EINVAL;
	पूर्ण

	अगर (srhinfo->mt_invflags & ~IP6T_SRH_INV_MASK) अणु
		pr_info_ratelimited("unknown srh invflags %X\n",
				    srhinfo->mt_invflags);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक srh1_mt6_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_srh1 *srhinfo = par->matchinfo;

	अगर (srhinfo->mt_flags & ~IP6T_SRH_MASK) अणु
		pr_info_ratelimited("unknown srh match flags  %X\n",
				    srhinfo->mt_flags);
		वापस -EINVAL;
	पूर्ण

	अगर (srhinfo->mt_invflags & ~IP6T_SRH_INV_MASK) अणु
		pr_info_ratelimited("unknown srh invflags %X\n",
				    srhinfo->mt_invflags);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match srh_mt6_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "srh",
		.revision	= 0,
		.family		= NFPROTO_IPV6,
		.match		= srh_mt6,
		.matchsize	= माप(काष्ठा ip6t_srh),
		.checkentry	= srh_mt6_check,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name           = "srh",
		.revision       = 1,
		.family         = NFPROTO_IPV6,
		.match          = srh1_mt6,
		.matchsize      = माप(काष्ठा ip6t_srh1),
		.checkentry     = srh1_mt6_check,
		.me             = THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init srh_mt6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(srh_mt6_reg, ARRAY_SIZE(srh_mt6_reg));
पूर्ण

अटल व्योम __निकास srh_mt6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(srh_mt6_reg, ARRAY_SIZE(srh_mt6_reg));
पूर्ण

module_init(srh_mt6_init);
module_निकास(srh_mt6_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: IPv6 Segment Routing Header match");
MODULE_AUTHOR("Ahmed Abdelsalam <amsalam20@gmail.com>");
