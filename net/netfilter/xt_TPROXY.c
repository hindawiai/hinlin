<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Transparent proxy support क्रम Linux/iptables
 *
 * Copyright (c) 2006-2010 BalaBit IT Ltd.
 * Author: Balazs Scheidler, Krisztian Kovacs
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <net/checksum.h>
#समावेश <net/udp.h>
#समावेश <net/tcp.h>
#समावेश <net/inet_sock.h>
#समावेश <net/inet_hashtables.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>

#समावेश <net/netfilter/ipv4/nf_defrag_ipv4.h>

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
#घोषणा XT_TPROXY_HAVE_IPV6 1
#समावेश <net/अगर_inet6.h>
#समावेश <net/addrconf.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>
#पूर्ण_अगर

#समावेश <net/netfilter/nf_tproxy.h>
#समावेश <linux/netfilter/xt_TPROXY.h>

अटल अचिन्हित पूर्णांक
tproxy_tg4(काष्ठा net *net, काष्ठा sk_buff *skb, __be32 laddr, __be16 lport,
	   u_पूर्णांक32_t mark_mask, u_पूर्णांक32_t mark_value)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा udphdr _hdr, *hp;
	काष्ठा sock *sk;

	hp = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb), माप(_hdr), &_hdr);
	अगर (hp == शून्य)
		वापस NF_DROP;

	/* check अगर there's an ongoing connection on the packet
	 * addresses, this happens अगर the redirect alपढ़ोy happened
	 * and the current packet beदीर्घs to an alपढ़ोy established
	 * connection */
	sk = nf_tproxy_get_sock_v4(net, skb, iph->protocol,
				   iph->saddr, iph->daddr,
				   hp->source, hp->dest,
				   skb->dev, NF_TPROXY_LOOKUP_ESTABLISHED);

	laddr = nf_tproxy_laddr4(skb, laddr, iph->daddr);
	अगर (!lport)
		lport = hp->dest;

	/* UDP has no TCP_TIME_WAIT state, so we never enter here */
	अगर (sk && sk->sk_state == TCP_TIME_WAIT)
		/* reखोलोing a TIME_WAIT connection needs special handling */
		sk = nf_tproxy_handle_समय_रुको4(net, skb, laddr, lport, sk);
	अन्यथा अगर (!sk)
		/* no, there's no established connection, check अगर
		 * there's a listener on the redirected addr/port */
		sk = nf_tproxy_get_sock_v4(net, skb, iph->protocol,
					   iph->saddr, laddr,
					   hp->source, lport,
					   skb->dev, NF_TPROXY_LOOKUP_LISTENER);

	/* NOTE: assign_sock consumes our sk reference */
	अगर (sk && nf_tproxy_sk_is_transparent(sk)) अणु
		/* This should be in a separate target, but we करोn't करो multiple
		   tarमाला_लो on the same rule yet */
		skb->mark = (skb->mark & ~mark_mask) ^ mark_value;

		pr_debug("redirecting: proto %hhu %pI4:%hu -> %pI4:%hu, mark: %x\n",
			 iph->protocol, &iph->daddr, ntohs(hp->dest),
			 &laddr, ntohs(lport), skb->mark);

		nf_tproxy_assign_sock(skb, sk);
		वापस NF_ACCEPT;
	पूर्ण

	pr_debug("no socket, dropping: proto %hhu %pI4:%hu -> %pI4:%hu, mark: %x\n",
		 iph->protocol, &iph->saddr, ntohs(hp->source),
		 &iph->daddr, ntohs(hp->dest), skb->mark);
	वापस NF_DROP;
पूर्ण

अटल अचिन्हित पूर्णांक
tproxy_tg4_v0(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_tproxy_target_info *tgi = par->targinfo;

	वापस tproxy_tg4(xt_net(par), skb, tgi->laddr, tgi->lport,
			  tgi->mark_mask, tgi->mark_value);
पूर्ण

अटल अचिन्हित पूर्णांक
tproxy_tg4_v1(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_tproxy_target_info_v1 *tgi = par->targinfo;

	वापस tproxy_tg4(xt_net(par), skb, tgi->laddr.ip, tgi->lport,
			  tgi->mark_mask, tgi->mark_value);
पूर्ण

#अगर_घोषित XT_TPROXY_HAVE_IPV6

अटल अचिन्हित पूर्णांक
tproxy_tg6_v1(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	स्थिर काष्ठा xt_tproxy_target_info_v1 *tgi = par->targinfo;
	काष्ठा udphdr _hdr, *hp;
	काष्ठा sock *sk;
	स्थिर काष्ठा in6_addr *laddr;
	__be16 lport;
	पूर्णांक thoff = 0;
	पूर्णांक tproto;

	tproto = ipv6_find_hdr(skb, &thoff, -1, शून्य, शून्य);
	अगर (tproto < 0) अणु
		pr_debug("unable to find transport header in IPv6 packet, dropping\n");
		वापस NF_DROP;
	पूर्ण

	hp = skb_header_poपूर्णांकer(skb, thoff, माप(_hdr), &_hdr);
	अगर (hp == शून्य) अणु
		pr_debug("unable to grab transport header contents in IPv6 packet, dropping\n");
		वापस NF_DROP;
	पूर्ण

	/* check अगर there's an ongoing connection on the packet
	 * addresses, this happens अगर the redirect alपढ़ोy happened
	 * and the current packet beदीर्घs to an alपढ़ोy established
	 * connection */
	sk = nf_tproxy_get_sock_v6(xt_net(par), skb, thoff, tproto,
				   &iph->saddr, &iph->daddr,
				   hp->source, hp->dest,
				   xt_in(par), NF_TPROXY_LOOKUP_ESTABLISHED);

	laddr = nf_tproxy_laddr6(skb, &tgi->laddr.in6, &iph->daddr);
	lport = tgi->lport ? tgi->lport : hp->dest;

	/* UDP has no TCP_TIME_WAIT state, so we never enter here */
	अगर (sk && sk->sk_state == TCP_TIME_WAIT) अणु
		स्थिर काष्ठा xt_tproxy_target_info_v1 *tgi = par->targinfo;
		/* reखोलोing a TIME_WAIT connection needs special handling */
		sk = nf_tproxy_handle_समय_रुको6(skb, tproto, thoff,
					      xt_net(par),
					      &tgi->laddr.in6,
					      tgi->lport,
					      sk);
	पूर्ण
	अन्यथा अगर (!sk)
		/* no there's no established connection, check अगर
		 * there's a listener on the redirected addr/port */
		sk = nf_tproxy_get_sock_v6(xt_net(par), skb, thoff,
					   tproto, &iph->saddr, laddr,
					   hp->source, lport,
					   xt_in(par), NF_TPROXY_LOOKUP_LISTENER);

	/* NOTE: assign_sock consumes our sk reference */
	अगर (sk && nf_tproxy_sk_is_transparent(sk)) अणु
		/* This should be in a separate target, but we करोn't करो multiple
		   tarमाला_लो on the same rule yet */
		skb->mark = (skb->mark & ~tgi->mark_mask) ^ tgi->mark_value;

		pr_debug("redirecting: proto %hhu %pI6:%hu -> %pI6:%hu, mark: %x\n",
			 tproto, &iph->saddr, ntohs(hp->source),
			 laddr, ntohs(lport), skb->mark);

		nf_tproxy_assign_sock(skb, sk);
		वापस NF_ACCEPT;
	पूर्ण

	pr_debug("no socket, dropping: proto %hhu %pI6:%hu -> %pI6:%hu, mark: %x\n",
		 tproto, &iph->saddr, ntohs(hp->source),
		 &iph->daddr, ntohs(hp->dest), skb->mark);

	वापस NF_DROP;
पूर्ण

अटल पूर्णांक tproxy_tg6_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ip6t_ip6 *i = par->entryinfo;
	पूर्णांक err;

	err = nf_defrag_ipv6_enable(par->net);
	अगर (err)
		वापस err;

	अगर ((i->proto == IPPROTO_TCP || i->proto == IPPROTO_UDP) &&
	    !(i->invflags & IP6T_INV_PROTO))
		वापस 0;

	pr_info_ratelimited("Can be used only with -p tcp or -p udp\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम tproxy_tg6_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_defrag_ipv6_disable(par->net);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tproxy_tg4_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ipt_ip *i = par->entryinfo;
	पूर्णांक err;

	err = nf_defrag_ipv4_enable(par->net);
	अगर (err)
		वापस err;

	अगर ((i->proto == IPPROTO_TCP || i->proto == IPPROTO_UDP)
	    && !(i->invflags & IPT_INV_PROTO))
		वापस 0;

	pr_info_ratelimited("Can be used only with -p tcp or -p udp\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम tproxy_tg4_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_defrag_ipv4_disable(par->net);
पूर्ण

अटल काष्ठा xt_target tproxy_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "TPROXY",
		.family		= NFPROTO_IPV4,
		.table		= "mangle",
		.target		= tproxy_tg4_v0,
		.revision	= 0,
		.tarमाला_लोize	= माप(काष्ठा xt_tproxy_target_info),
		.checkentry	= tproxy_tg4_check,
		.destroy	= tproxy_tg4_destroy,
		.hooks		= 1 << NF_INET_PRE_ROUTING,
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "TPROXY",
		.family		= NFPROTO_IPV4,
		.table		= "mangle",
		.target		= tproxy_tg4_v1,
		.revision	= 1,
		.tarमाला_लोize	= माप(काष्ठा xt_tproxy_target_info_v1),
		.checkentry	= tproxy_tg4_check,
		.destroy	= tproxy_tg4_destroy,
		.hooks		= 1 << NF_INET_PRE_ROUTING,
		.me		= THIS_MODULE,
	पूर्ण,
#अगर_घोषित XT_TPROXY_HAVE_IPV6
	अणु
		.name		= "TPROXY",
		.family		= NFPROTO_IPV6,
		.table		= "mangle",
		.target		= tproxy_tg6_v1,
		.revision	= 1,
		.tarमाला_लोize	= माप(काष्ठा xt_tproxy_target_info_v1),
		.checkentry	= tproxy_tg6_check,
		.destroy	= tproxy_tg6_destroy,
		.hooks		= 1 << NF_INET_PRE_ROUTING,
		.me		= THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर

पूर्ण;

अटल पूर्णांक __init tproxy_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(tproxy_tg_reg, ARRAY_SIZE(tproxy_tg_reg));
पूर्ण

अटल व्योम __निकास tproxy_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(tproxy_tg_reg, ARRAY_SIZE(tproxy_tg_reg));
पूर्ण

module_init(tproxy_tg_init);
module_निकास(tproxy_tg_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Balazs Scheidler, Krisztian Kovacs");
MODULE_DESCRIPTION("Netfilter transparent proxy (TPROXY) target module.");
MODULE_ALIAS("ipt_TPROXY");
MODULE_ALIAS("ip6t_TPROXY");
