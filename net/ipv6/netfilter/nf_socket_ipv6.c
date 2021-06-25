<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2008 BalaBit IT Ltd.
 * Author: Krisztian Kovacs
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/icmp.h>
#समावेश <net/sock.h>
#समावेश <net/inet_sock.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/netfilter/nf_socket.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर

अटल पूर्णांक
extract_icmp6_fields(स्थिर काष्ठा sk_buff *skb,
		     अचिन्हित पूर्णांक outside_hdrlen,
		     पूर्णांक *protocol,
		     स्थिर काष्ठा in6_addr **raddr,
		     स्थिर काष्ठा in6_addr **laddr,
		     __be16 *rport,
		     __be16 *lport,
		     काष्ठा ipv6hdr *ipv6_var)
अणु
	स्थिर काष्ठा ipv6hdr *inside_iph;
	काष्ठा icmp6hdr *icmph, _icmph;
	__be16 *ports, _ports[2];
	u8 inside_nexthdr;
	__be16 inside_fragoff;
	पूर्णांक inside_hdrlen;

	icmph = skb_header_poपूर्णांकer(skb, outside_hdrlen,
				   माप(_icmph), &_icmph);
	अगर (icmph == शून्य)
		वापस 1;

	अगर (icmph->icmp6_type & ICMPV6_INFOMSG_MASK)
		वापस 1;

	inside_iph = skb_header_poपूर्णांकer(skb, outside_hdrlen + माप(_icmph),
					माप(*ipv6_var), ipv6_var);
	अगर (inside_iph == शून्य)
		वापस 1;
	inside_nexthdr = inside_iph->nexthdr;

	inside_hdrlen = ipv6_skip_exthdr(skb, outside_hdrlen + माप(_icmph) +
					      माप(*ipv6_var),
					 &inside_nexthdr, &inside_fragoff);
	अगर (inside_hdrlen < 0)
		वापस 1; /* hjm: Packet has no/incomplete transport layer headers. */

	अगर (inside_nexthdr != IPPROTO_TCP &&
	    inside_nexthdr != IPPROTO_UDP)
		वापस 1;

	ports = skb_header_poपूर्णांकer(skb, inside_hdrlen,
				   माप(_ports), &_ports);
	अगर (ports == शून्य)
		वापस 1;

	/* the inside IP packet is the one quoted from our side, thus
	 * its saddr is the local address */
	*protocol = inside_nexthdr;
	*laddr = &inside_iph->saddr;
	*lport = ports[0];
	*raddr = &inside_iph->daddr;
	*rport = ports[1];

	वापस 0;
पूर्ण

अटल काष्ठा sock *
nf_socket_get_sock_v6(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक करोff,
		      स्थिर u8 protocol,
		      स्थिर काष्ठा in6_addr *saddr, स्थिर काष्ठा in6_addr *daddr,
		      स्थिर __be16 sport, स्थिर __be16 dport,
		      स्थिर काष्ठा net_device *in)
अणु
	चयन (protocol) अणु
	हाल IPPROTO_TCP:
		वापस inet6_lookup(net, &tcp_hashinfo, skb, करोff,
				    saddr, sport, daddr, dport,
				    in->अगरindex);
	हाल IPPROTO_UDP:
		वापस udp6_lib_lookup(net, saddr, sport, daddr, dport,
				       in->अगरindex);
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा sock *nf_sk_lookup_slow_v6(काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
				  स्थिर काष्ठा net_device *indev)
अणु
	__be16 dport, sport;
	स्थिर काष्ठा in6_addr *daddr = शून्य, *saddr = शून्य;
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा sk_buff *data_skb = शून्य;
	पूर्णांक करोff = 0;
	पूर्णांक thoff = 0, tproto;

	tproto = ipv6_find_hdr(skb, &thoff, -1, शून्य, शून्य);
	अगर (tproto < 0) अणु
		pr_debug("unable to find transport header in IPv6 packet, dropping\n");
		वापस शून्य;
	पूर्ण

	अगर (tproto == IPPROTO_UDP || tproto == IPPROTO_TCP) अणु
		काष्ठा tcphdr _hdr;
		काष्ठा udphdr *hp;

		hp = skb_header_poपूर्णांकer(skb, thoff, tproto == IPPROTO_UDP ?
					माप(*hp) : माप(_hdr), &_hdr);
		अगर (hp == शून्य)
			वापस शून्य;

		saddr = &iph->saddr;
		sport = hp->source;
		daddr = &iph->daddr;
		dport = hp->dest;
		data_skb = (काष्ठा sk_buff *)skb;
		करोff = tproto == IPPROTO_TCP ?
			thoff + __tcp_hdrlen((काष्ठा tcphdr *)hp) :
			thoff + माप(*hp);

	पूर्ण अन्यथा अगर (tproto == IPPROTO_ICMPV6) अणु
		काष्ठा ipv6hdr ipv6_var;

		अगर (extract_icmp6_fields(skb, thoff, &tproto, &saddr, &daddr,
					 &sport, &dport, &ipv6_var))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	वापस nf_socket_get_sock_v6(net, data_skb, करोff, tproto, saddr, daddr,
				     sport, dport, indev);
पूर्ण
EXPORT_SYMBOL_GPL(nf_sk_lookup_slow_v6);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Krisztian Kovacs, Balazs Scheidler");
MODULE_DESCRIPTION("Netfilter IPv6 socket lookup infrastructure");
