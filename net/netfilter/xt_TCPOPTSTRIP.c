<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A module क्रम stripping a specअगरic TCP option from TCP packets.
 *
 * Copyright (C) 2007 Sven Schnelle <svens@bitebene.org>
 * Copyright तऊ CC Computer Consultants GmbH, 2007
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <net/ipv6.h>
#समावेश <net/tcp.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_TCPOPTSTRIP.h>

अटल अंतरभूत अचिन्हित पूर्णांक optlen(स्थिर u_पूर्णांक8_t *opt, अचिन्हित पूर्णांक offset)
अणु
	/* Beware zero-length options: make finite progress */
	अगर (opt[offset] <= TCPOPT_NOP || opt[offset+1] == 0)
		वापस 1;
	अन्यथा
		वापस opt[offset+1];
पूर्ण

अटल अचिन्हित पूर्णांक
tcpoptstrip_mangle_packet(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा xt_action_param *par,
			  अचिन्हित पूर्णांक tcphoff)
अणु
	स्थिर काष्ठा xt_tcpoptstrip_target_info *info = par->targinfo;
	काष्ठा tcphdr *tcph, _th;
	अचिन्हित पूर्णांक optl, i, j;
	u_पूर्णांक16_t n, o;
	u_पूर्णांक8_t *opt;
	पूर्णांक tcp_hdrlen;

	/* This is a fragment, no TCP header is available */
	अगर (par->fragoff != 0)
		वापस XT_CONTINUE;

	tcph = skb_header_poपूर्णांकer(skb, tcphoff, माप(_th), &_th);
	अगर (!tcph)
		वापस NF_DROP;

	tcp_hdrlen = tcph->करोff * 4;
	अगर (tcp_hdrlen < माप(काष्ठा tcphdr))
		वापस NF_DROP;

	अगर (skb_ensure_writable(skb, tcphoff + tcp_hdrlen))
		वापस NF_DROP;

	/* must reload tcph, might have been moved */
	tcph = (काष्ठा tcphdr *)(skb_network_header(skb) + tcphoff);
	opt  = (u8 *)tcph;

	/*
	 * Walk through all TCP options - अगर we find some option to हटाओ,
	 * set all octets to %TCPOPT_NOP and adjust checksum.
	 */
	क्रम (i = माप(काष्ठा tcphdr); i < tcp_hdrlen - 1; i += optl) अणु
		optl = optlen(opt, i);

		अगर (i + optl > tcp_hdrlen)
			अवरोध;

		अगर (!tcpoptstrip_test_bit(info->strip_bmap, opt[i]))
			जारी;

		क्रम (j = 0; j < optl; ++j) अणु
			o = opt[i+j];
			n = TCPOPT_NOP;
			अगर ((i + j) % 2 == 0) अणु
				o <<= 8;
				n <<= 8;
			पूर्ण
			inet_proto_csum_replace2(&tcph->check, skb, htons(o),
						 htons(n), false);
		पूर्ण
		स_रखो(opt + i, TCPOPT_NOP, optl);
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल अचिन्हित पूर्णांक
tcpoptstrip_tg4(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	वापस tcpoptstrip_mangle_packet(skb, par, ip_hdrlen(skb));
पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_MANGLE)
अटल अचिन्हित पूर्णांक
tcpoptstrip_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
	पूर्णांक tcphoff;
	u_पूर्णांक8_t nexthdr;
	__be16 frag_off;

	nexthdr = ipv6h->nexthdr;
	tcphoff = ipv6_skip_exthdr(skb, माप(*ipv6h), &nexthdr, &frag_off);
	अगर (tcphoff < 0)
		वापस NF_DROP;

	वापस tcpoptstrip_mangle_packet(skb, par, tcphoff);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा xt_target tcpoptstrip_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name       = "TCPOPTSTRIP",
		.family     = NFPROTO_IPV4,
		.table      = "mangle",
		.proto      = IPPROTO_TCP,
		.target     = tcpoptstrip_tg4,
		.tarमाला_लोize = माप(काष्ठा xt_tcpoptstrip_target_info),
		.me         = THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_MANGLE)
	अणु
		.name       = "TCPOPTSTRIP",
		.family     = NFPROTO_IPV6,
		.table      = "mangle",
		.proto      = IPPROTO_TCP,
		.target     = tcpoptstrip_tg6,
		.tarमाला_लोize = माप(काष्ठा xt_tcpoptstrip_target_info),
		.me         = THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init tcpoptstrip_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(tcpoptstrip_tg_reg,
				   ARRAY_SIZE(tcpoptstrip_tg_reg));
पूर्ण

अटल व्योम __निकास tcpoptstrip_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(tcpoptstrip_tg_reg,
			      ARRAY_SIZE(tcpoptstrip_tg_reg));
पूर्ण

module_init(tcpoptstrip_tg_init);
module_निकास(tcpoptstrip_tg_निकास);
MODULE_AUTHOR("Sven Schnelle <svens@bitebene.org>, Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: TCP option stripping");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_TCPOPTSTRIP");
MODULE_ALIAS("ip6t_TCPOPTSTRIP");
