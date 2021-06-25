<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is a module which is used क्रम setting the MSS option in TCP packets.
 *
 * Copyright (C) 2000 Marc Boucher <marc@mbsi.ca>
 * Copyright (C) 2007 Patrick McHardy <kaber@trash.net>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/gfp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/ipv6.h>
#समावेश <net/route.h>
#समावेश <net/tcp.h>

#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_tcpudp.h>
#समावेश <linux/netfilter/xt_TCPMSS.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marc Boucher <marc@mbsi.ca>");
MODULE_DESCRIPTION("Xtables: TCP Maximum Segment Size (MSS) adjustment");
MODULE_ALIAS("ipt_TCPMSS");
MODULE_ALIAS("ip6t_TCPMSS");

अटल अंतरभूत अचिन्हित पूर्णांक
optlen(स्थिर u_पूर्णांक8_t *opt, अचिन्हित पूर्णांक offset)
अणु
	/* Beware zero-length options: make finite progress */
	अगर (opt[offset] <= TCPOPT_NOP || opt[offset+1] == 0)
		वापस 1;
	अन्यथा
		वापस opt[offset+1];
पूर्ण

अटल u_पूर्णांक32_t tcpmss_reverse_mtu(काष्ठा net *net,
				    स्थिर काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक family)
अणु
	काष्ठा flowi fl;
	काष्ठा rtable *rt = शून्य;
	u_पूर्णांक32_t mtu     = ~0U;

	अगर (family == PF_INET) अणु
		काष्ठा flowi4 *fl4 = &fl.u.ip4;
		स_रखो(fl4, 0, माप(*fl4));
		fl4->daddr = ip_hdr(skb)->saddr;
	पूर्ण अन्यथा अणु
		काष्ठा flowi6 *fl6 = &fl.u.ip6;

		स_रखो(fl6, 0, माप(*fl6));
		fl6->daddr = ipv6_hdr(skb)->saddr;
	पूर्ण

	nf_route(net, (काष्ठा dst_entry **)&rt, &fl, false, family);
	अगर (rt != शून्य) अणु
		mtu = dst_mtu(&rt->dst);
		dst_release(&rt->dst);
	पूर्ण
	वापस mtu;
पूर्ण

अटल पूर्णांक
tcpmss_mangle_packet(काष्ठा sk_buff *skb,
		     स्थिर काष्ठा xt_action_param *par,
		     अचिन्हित पूर्णांक family,
		     अचिन्हित पूर्णांक tcphoff,
		     अचिन्हित पूर्णांक minlen)
अणु
	स्थिर काष्ठा xt_tcpmss_info *info = par->targinfo;
	काष्ठा tcphdr *tcph;
	पूर्णांक len, tcp_hdrlen;
	अचिन्हित पूर्णांक i;
	__be16 oldval;
	u16 newmss;
	u8 *opt;

	/* This is a fragment, no TCP header is available */
	अगर (par->fragoff != 0)
		वापस 0;

	अगर (skb_ensure_writable(skb, skb->len))
		वापस -1;

	len = skb->len - tcphoff;
	अगर (len < (पूर्णांक)माप(काष्ठा tcphdr))
		वापस -1;

	tcph = (काष्ठा tcphdr *)(skb_network_header(skb) + tcphoff);
	tcp_hdrlen = tcph->करोff * 4;

	अगर (len < tcp_hdrlen || tcp_hdrlen < माप(काष्ठा tcphdr))
		वापस -1;

	अगर (info->mss == XT_TCPMSS_CLAMP_PMTU) अणु
		काष्ठा net *net = xt_net(par);
		अचिन्हित पूर्णांक in_mtu = tcpmss_reverse_mtu(net, skb, family);
		अचिन्हित पूर्णांक min_mtu = min(dst_mtu(skb_dst(skb)), in_mtu);

		अगर (min_mtu <= minlen) अणु
			net_err_ratelimited("unknown or invalid path-MTU (%u)\n",
					    min_mtu);
			वापस -1;
		पूर्ण
		newmss = min_mtu - minlen;
	पूर्ण अन्यथा
		newmss = info->mss;

	opt = (u_पूर्णांक8_t *)tcph;
	क्रम (i = माप(काष्ठा tcphdr); i <= tcp_hdrlen - TCPOLEN_MSS; i += optlen(opt, i)) अणु
		अगर (opt[i] == TCPOPT_MSS && opt[i+1] == TCPOLEN_MSS) अणु
			u_पूर्णांक16_t oldmss;

			oldmss = (opt[i+2] << 8) | opt[i+3];

			/* Never increase MSS, even when setting it, as
			 * करोing so results in problems क्रम hosts that rely
			 * on MSS being set correctly.
			 */
			अगर (oldmss <= newmss)
				वापस 0;

			opt[i+2] = (newmss & 0xff00) >> 8;
			opt[i+3] = newmss & 0x00ff;

			inet_proto_csum_replace2(&tcph->check, skb,
						 htons(oldmss), htons(newmss),
						 false);
			वापस 0;
		पूर्ण
	पूर्ण

	/* There is data after the header so the option can't be added
	 * without moving it, and करोing so may make the SYN packet
	 * itself too large. Accept the packet unmodअगरied instead.
	 */
	अगर (len > tcp_hdrlen)
		वापस 0;

	/* tcph->करोff has 4 bits, करो not wrap it to 0 */
	अगर (tcp_hdrlen >= 15 * 4)
		वापस 0;

	/*
	 * MSS Option not found ?! add it..
	 */
	अगर (skb_tailroom(skb) < TCPOLEN_MSS) अणु
		अगर (pskb_expand_head(skb, 0,
				     TCPOLEN_MSS - skb_tailroom(skb),
				     GFP_ATOMIC))
			वापस -1;
		tcph = (काष्ठा tcphdr *)(skb_network_header(skb) + tcphoff);
	पूर्ण

	skb_put(skb, TCPOLEN_MSS);

	/*
	 * IPv4: RFC 1122 states "If an MSS option is not received at
	 * connection setup, TCP MUST assume a शेष send MSS of 536".
	 * IPv6: RFC 2460 states IPv6 has a minimum MTU of 1280 and a minimum
	 * length IPv6 header of 60, ergo the शेष MSS value is 1220
	 * Since no MSS was provided, we must use the शेष values
	 */
	अगर (xt_family(par) == NFPROTO_IPV4)
		newmss = min(newmss, (u16)536);
	अन्यथा
		newmss = min(newmss, (u16)1220);

	opt = (u_पूर्णांक8_t *)tcph + माप(काष्ठा tcphdr);
	स_हटाओ(opt + TCPOLEN_MSS, opt, len - माप(काष्ठा tcphdr));

	inet_proto_csum_replace2(&tcph->check, skb,
				 htons(len), htons(len + TCPOLEN_MSS), true);
	opt[0] = TCPOPT_MSS;
	opt[1] = TCPOLEN_MSS;
	opt[2] = (newmss & 0xff00) >> 8;
	opt[3] = newmss & 0x00ff;

	inet_proto_csum_replace4(&tcph->check, skb, 0, *((__be32 *)opt), false);

	oldval = ((__be16 *)tcph)[6];
	tcph->करोff += TCPOLEN_MSS/4;
	inet_proto_csum_replace2(&tcph->check, skb,
				 oldval, ((__be16 *)tcph)[6], false);
	वापस TCPOLEN_MSS;
पूर्ण

अटल अचिन्हित पूर्णांक
tcpmss_tg4(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);
	__be16 newlen;
	पूर्णांक ret;

	ret = tcpmss_mangle_packet(skb, par,
				   PF_INET,
				   iph->ihl * 4,
				   माप(*iph) + माप(काष्ठा tcphdr));
	अगर (ret < 0)
		वापस NF_DROP;
	अगर (ret > 0) अणु
		iph = ip_hdr(skb);
		newlen = htons(ntohs(iph->tot_len) + ret);
		csum_replace2(&iph->check, iph->tot_len, newlen);
		iph->tot_len = newlen;
	पूर्ण
	वापस XT_CONTINUE;
पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
अटल अचिन्हित पूर्णांक
tcpmss_tg6(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
	u8 nexthdr;
	__be16 frag_off, oldlen, newlen;
	पूर्णांक tcphoff;
	पूर्णांक ret;

	nexthdr = ipv6h->nexthdr;
	tcphoff = ipv6_skip_exthdr(skb, माप(*ipv6h), &nexthdr, &frag_off);
	अगर (tcphoff < 0)
		वापस NF_DROP;
	ret = tcpmss_mangle_packet(skb, par,
				   PF_INET6,
				   tcphoff,
				   माप(*ipv6h) + माप(काष्ठा tcphdr));
	अगर (ret < 0)
		वापस NF_DROP;
	अगर (ret > 0) अणु
		ipv6h = ipv6_hdr(skb);
		oldlen = ipv6h->payload_len;
		newlen = htons(ntohs(oldlen) + ret);
		अगर (skb->ip_summed == CHECKSUM_COMPLETE)
			skb->csum = csum_add(csum_sub(skb->csum, oldlen),
					     newlen);
		ipv6h->payload_len = newlen;
	पूर्ण
	वापस XT_CONTINUE;
पूर्ण
#पूर्ण_अगर

/* Must specअगरy -p tcp --syn */
अटल अंतरभूत bool find_syn_match(स्थिर काष्ठा xt_entry_match *m)
अणु
	स्थिर काष्ठा xt_tcp *tcpinfo = (स्थिर काष्ठा xt_tcp *)m->data;

	अगर (म_भेद(m->u.kernel.match->name, "tcp") == 0 &&
	    tcpinfo->flg_cmp & TCPHDR_SYN &&
	    !(tcpinfo->invflags & XT_TCP_INV_FLAGS))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक tcpmss_tg4_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_tcpmss_info *info = par->targinfo;
	स्थिर काष्ठा ipt_entry *e = par->entryinfo;
	स्थिर काष्ठा xt_entry_match *ematch;

	अगर (info->mss == XT_TCPMSS_CLAMP_PMTU &&
	    (par->hook_mask & ~((1 << NF_INET_FORWARD) |
			   (1 << NF_INET_LOCAL_OUT) |
			   (1 << NF_INET_POST_ROUTING))) != 0) अणु
		pr_info_ratelimited("path-MTU clamping only supported in FORWARD, OUTPUT and POSTROUTING hooks\n");
		वापस -EINVAL;
	पूर्ण
	अगर (par->nft_compat)
		वापस 0;

	xt_ematch_क्रमeach(ematch, e)
		अगर (find_syn_match(ematch))
			वापस 0;
	pr_info_ratelimited("Only works on TCP SYN packets\n");
	वापस -EINVAL;
पूर्ण

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
अटल पूर्णांक tcpmss_tg6_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_tcpmss_info *info = par->targinfo;
	स्थिर काष्ठा ip6t_entry *e = par->entryinfo;
	स्थिर काष्ठा xt_entry_match *ematch;

	अगर (info->mss == XT_TCPMSS_CLAMP_PMTU &&
	    (par->hook_mask & ~((1 << NF_INET_FORWARD) |
			   (1 << NF_INET_LOCAL_OUT) |
			   (1 << NF_INET_POST_ROUTING))) != 0) अणु
		pr_info_ratelimited("path-MTU clamping only supported in FORWARD, OUTPUT and POSTROUTING hooks\n");
		वापस -EINVAL;
	पूर्ण
	अगर (par->nft_compat)
		वापस 0;

	xt_ematch_क्रमeach(ematch, e)
		अगर (find_syn_match(ematch))
			वापस 0;
	pr_info_ratelimited("Only works on TCP SYN packets\n");
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा xt_target tcpmss_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.family		= NFPROTO_IPV4,
		.name		= "TCPMSS",
		.checkentry	= tcpmss_tg4_check,
		.target		= tcpmss_tg4,
		.tarमाला_लोize	= माप(काष्ठा xt_tcpmss_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अणु
		.family		= NFPROTO_IPV6,
		.name		= "TCPMSS",
		.checkentry	= tcpmss_tg6_check,
		.target		= tcpmss_tg6,
		.tarमाला_लोize	= माप(काष्ठा xt_tcpmss_info),
		.proto		= IPPROTO_TCP,
		.me		= THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init tcpmss_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(tcpmss_tg_reg, ARRAY_SIZE(tcpmss_tg_reg));
पूर्ण

अटल व्योम __निकास tcpmss_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(tcpmss_tg_reg, ARRAY_SIZE(tcpmss_tg_reg));
पूर्ण

module_init(tcpmss_tg_init);
module_निकास(tcpmss_tg_निकास);
