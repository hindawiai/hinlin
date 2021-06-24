<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match one of a list of TCP/UDP(-Lite)/SCTP/DCCP ports:
   ports are in the same place so we can treat them as equal. */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/udp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>

#समावेश <linux/netfilter/xt_multiport.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("Xtables: multiple port matching for TCP, UDP, UDP-Lite, SCTP and DCCP");
MODULE_ALIAS("ipt_multiport");
MODULE_ALIAS("ip6t_multiport");

/* Returns 1 अगर the port is matched by the test, 0 otherwise. */
अटल अंतरभूत bool
ports_match_v1(स्थिर काष्ठा xt_multiport_v1 *minfo,
	       u_पूर्णांक16_t src, u_पूर्णांक16_t dst)
अणु
	अचिन्हित पूर्णांक i;
	u_पूर्णांक16_t s, e;

	क्रम (i = 0; i < minfo->count; i++) अणु
		s = minfo->ports[i];

		अगर (minfo->pflags[i]) अणु
			/* range port matching */
			e = minfo->ports[++i];
			pr_debug("src or dst matches with %d-%d?\n", s, e);

			चयन (minfo->flags) अणु
			हाल XT_MULTIPORT_SOURCE:
				अगर (src >= s && src <= e)
					वापस true ^ minfo->invert;
				अवरोध;
			हाल XT_MULTIPORT_DESTINATION:
				अगर (dst >= s && dst <= e)
					वापस true ^ minfo->invert;
				अवरोध;
			हाल XT_MULTIPORT_EITHER:
				अगर ((dst >= s && dst <= e) ||
				    (src >= s && src <= e))
					वापस true ^ minfo->invert;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* exact port matching */
			pr_debug("src or dst matches with %d?\n", s);

			चयन (minfo->flags) अणु
			हाल XT_MULTIPORT_SOURCE:
				अगर (src == s)
					वापस true ^ minfo->invert;
				अवरोध;
			हाल XT_MULTIPORT_DESTINATION:
				अगर (dst == s)
					वापस true ^ minfo->invert;
				अवरोध;
			हाल XT_MULTIPORT_EITHER:
				अगर (src == s || dst == s)
					वापस true ^ minfo->invert;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस minfo->invert;
पूर्ण

अटल bool
multiport_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर __be16 *pptr;
	__be16 _ports[2];
	स्थिर काष्ठा xt_multiport_v1 *multiinfo = par->matchinfo;

	अगर (par->fragoff != 0)
		वापस false;

	pptr = skb_header_poपूर्णांकer(skb, par->thoff, माप(_ports), _ports);
	अगर (pptr == शून्य) अणु
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to drop.
		 */
		pr_debug("Dropping evil offset=0 tinygram.\n");
		par->hotdrop = true;
		वापस false;
	पूर्ण

	वापस ports_match_v1(multiinfo, ntohs(pptr[0]), ntohs(pptr[1]));
पूर्ण

अटल अंतरभूत bool
check(u_पूर्णांक16_t proto,
      u_पूर्णांक8_t ip_invflags,
      u_पूर्णांक8_t match_flags,
      u_पूर्णांक8_t count)
अणु
	/* Must specअगरy supported protocol, no unknown flags or bad count */
	वापस (proto == IPPROTO_TCP || proto == IPPROTO_UDP
		|| proto == IPPROTO_UDPLITE
		|| proto == IPPROTO_SCTP || proto == IPPROTO_DCCP)
		&& !(ip_invflags & XT_INV_PROTO)
		&& (match_flags == XT_MULTIPORT_SOURCE
		    || match_flags == XT_MULTIPORT_DESTINATION
		    || match_flags == XT_MULTIPORT_EITHER)
		&& count <= XT_MULTI_PORTS;
पूर्ण

अटल पूर्णांक multiport_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ipt_ip *ip = par->entryinfo;
	स्थिर काष्ठा xt_multiport_v1 *multiinfo = par->matchinfo;

	वापस check(ip->proto, ip->invflags, multiinfo->flags,
		     multiinfo->count) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक multiport_mt6_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_ip6 *ip = par->entryinfo;
	स्थिर काष्ठा xt_multiport_v1 *multiinfo = par->matchinfo;

	वापस check(ip->proto, ip->invflags, multiinfo->flags,
		     multiinfo->count) ? 0 : -EINVAL;
पूर्ण

अटल काष्ठा xt_match multiport_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "multiport",
		.family		= NFPROTO_IPV4,
		.revision	= 1,
		.checkentry	= multiport_mt_check,
		.match		= multiport_mt,
		.matchsize	= माप(काष्ठा xt_multiport_v1),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "multiport",
		.family		= NFPROTO_IPV6,
		.revision	= 1,
		.checkentry	= multiport_mt6_check,
		.match		= multiport_mt,
		.matchsize	= माप(काष्ठा xt_multiport_v1),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init multiport_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(multiport_mt_reg,
	       ARRAY_SIZE(multiport_mt_reg));
पूर्ण

अटल व्योम __निकास multiport_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(multiport_mt_reg, ARRAY_SIZE(multiport_mt_reg));
पूर्ण

module_init(multiport_mt_init);
module_निकास(multiport_mt_निकास);
