<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match TCP MSS values. */

/* Copyright (C) 2000 Marc Boucher <marc@mbsi.ca>
 * Portions (C) 2005 by Harald Welte <laक्रमge@netfilter.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/tcp.h>

#समावेश <linux/netfilter/xt_tcpmss.h>
#समावेश <linux/netfilter/x_tables.h>

#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marc Boucher <marc@mbsi.ca>");
MODULE_DESCRIPTION("Xtables: TCP MSS match");
MODULE_ALIAS("ipt_tcpmss");
MODULE_ALIAS("ip6t_tcpmss");

अटल bool
tcpmss_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_tcpmss_match_info *info = par->matchinfo;
	स्थिर काष्ठा tcphdr *th;
	काष्ठा tcphdr _tcph;
	/* tcp.करोff is only 4 bits, ie. max 15 * 4 bytes */
	स्थिर u_पूर्णांक8_t *op;
	u8 _opt[15 * 4 - माप(_tcph)];
	अचिन्हित पूर्णांक i, optlen;

	/* If we करोn't have the whole header, drop packet. */
	th = skb_header_poपूर्णांकer(skb, par->thoff, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		जाओ dropit;

	/* Malक्रमmed. */
	अगर (th->करोff*4 < माप(*th))
		जाओ dropit;

	optlen = th->करोff*4 - माप(*th);
	अगर (!optlen)
		जाओ out;

	/* Truncated options. */
	op = skb_header_poपूर्णांकer(skb, par->thoff + माप(*th), optlen, _opt);
	अगर (op == शून्य)
		जाओ dropit;

	क्रम (i = 0; i < optlen; ) अणु
		अगर (op[i] == TCPOPT_MSS
		    && (optlen - i) >= TCPOLEN_MSS
		    && op[i+1] == TCPOLEN_MSS) अणु
			u_पूर्णांक16_t mssval;

			mssval = (op[i+2] << 8) | op[i+3];

			वापस (mssval >= info->mss_min &&
				mssval <= info->mss_max) ^ info->invert;
		पूर्ण
		अगर (op[i] < 2)
			i++;
		अन्यथा
			i += op[i+1] ? : 1;
	पूर्ण
out:
	वापस info->invert;

dropit:
	par->hotdrop = true;
	वापस false;
पूर्ण

अटल काष्ठा xt_match tcpmss_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "tcpmss",
		.family		= NFPROTO_IPV4,
		.match		= tcpmss_mt,
		.matchsize	= माप(काष्ठा xt_tcpmss_match_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "tcpmss",
		.family		= NFPROTO_IPV6,
		.match		= tcpmss_mt,
		.matchsize	= माप(काष्ठा xt_tcpmss_match_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tcpmss_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(tcpmss_mt_reg, ARRAY_SIZE(tcpmss_mt_reg));
पूर्ण

अटल व्योम __निकास tcpmss_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(tcpmss_mt_reg, ARRAY_SIZE(tcpmss_mt_reg));
पूर्ण

module_init(tcpmss_mt_init);
module_निकास(tcpmss_mt_निकास);
