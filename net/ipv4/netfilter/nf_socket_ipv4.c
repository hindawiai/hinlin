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
#समावेश <net/netfilter/nf_socket.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर

अटल पूर्णांक
extract_icmp4_fields(स्थिर काष्ठा sk_buff *skb, u8 *protocol,
		     __be32 *raddr, __be32 *laddr,
		     __be16 *rport, __be16 *lport)
अणु
	अचिन्हित पूर्णांक outside_hdrlen = ip_hdrlen(skb);
	काष्ठा iphdr *inside_iph, _inside_iph;
	काष्ठा icmphdr *icmph, _icmph;
	__be16 *ports, _ports[2];

	icmph = skb_header_poपूर्णांकer(skb, outside_hdrlen,
				   माप(_icmph), &_icmph);
	अगर (icmph == शून्य)
		वापस 1;

	अगर (!icmp_is_err(icmph->type))
		वापस 1;

	inside_iph = skb_header_poपूर्णांकer(skb, outside_hdrlen +
					माप(काष्ठा icmphdr),
					माप(_inside_iph), &_inside_iph);
	अगर (inside_iph == शून्य)
		वापस 1;

	अगर (inside_iph->protocol != IPPROTO_TCP &&
	    inside_iph->protocol != IPPROTO_UDP)
		वापस 1;

	ports = skb_header_poपूर्णांकer(skb, outside_hdrlen +
				   माप(काष्ठा icmphdr) +
				   (inside_iph->ihl << 2),
				   माप(_ports), &_ports);
	अगर (ports == शून्य)
		वापस 1;

	/* the inside IP packet is the one quoted from our side, thus
	 * its saddr is the local address */
	*protocol = inside_iph->protocol;
	*laddr = inside_iph->saddr;
	*lport = ports[0];
	*raddr = inside_iph->daddr;
	*rport = ports[1];

	वापस 0;
पूर्ण

अटल काष्ठा sock *
nf_socket_get_sock_v4(काष्ठा net *net, काष्ठा sk_buff *skb, स्थिर पूर्णांक करोff,
		      स्थिर u8 protocol,
		      स्थिर __be32 saddr, स्थिर __be32 daddr,
		      स्थिर __be16 sport, स्थिर __be16 dport,
		      स्थिर काष्ठा net_device *in)
अणु
	चयन (protocol) अणु
	हाल IPPROTO_TCP:
		वापस inet_lookup(net, &tcp_hashinfo, skb, करोff,
				   saddr, sport, daddr, dport,
				   in->अगरindex);
	हाल IPPROTO_UDP:
		वापस udp4_lib_lookup(net, saddr, sport, daddr, dport,
				       in->अगरindex);
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा sock *nf_sk_lookup_slow_v4(काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
				  स्थिर काष्ठा net_device *indev)
अणु
	__be32 daddr, saddr;
	__be16 dport, sport;
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा sk_buff *data_skb = शून्य;
	u8 protocol;
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn स्थिर *ct;
#पूर्ण_अगर
	पूर्णांक करोff = 0;

	अगर (iph->protocol == IPPROTO_UDP || iph->protocol == IPPROTO_TCP) अणु
		काष्ठा tcphdr _hdr;
		काष्ठा udphdr *hp;

		hp = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb),
					iph->protocol == IPPROTO_UDP ?
					माप(*hp) : माप(_hdr), &_hdr);
		अगर (hp == शून्य)
			वापस शून्य;

		protocol = iph->protocol;
		saddr = iph->saddr;
		sport = hp->source;
		daddr = iph->daddr;
		dport = hp->dest;
		data_skb = (काष्ठा sk_buff *)skb;
		करोff = iph->protocol == IPPROTO_TCP ?
			ip_hdrlen(skb) + __tcp_hdrlen((काष्ठा tcphdr *)hp) :
			ip_hdrlen(skb) + माप(*hp);

	पूर्ण अन्यथा अगर (iph->protocol == IPPROTO_ICMP) अणु
		अगर (extract_icmp4_fields(skb, &protocol, &saddr, &daddr,
					 &sport, &dport))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	/* Do the lookup with the original socket address in
	 * हाल this is a reply packet of an established
	 * SNAT-ted connection.
	 */
	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct &&
	    ((iph->protocol != IPPROTO_ICMP &&
	      ctinfo == IP_CT_ESTABLISHED_REPLY) ||
	     (iph->protocol == IPPROTO_ICMP &&
	      ctinfo == IP_CT_RELATED_REPLY)) &&
	    (ct->status & IPS_SRC_NAT_DONE)) अणु

		daddr = ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u3.ip;
		dport = (iph->protocol == IPPROTO_TCP) ?
			ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u.tcp.port :
			ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u.udp.port;
	पूर्ण
#पूर्ण_अगर

	वापस nf_socket_get_sock_v4(net, data_skb, करोff, protocol, saddr,
				     daddr, sport, dport, indev);
पूर्ण
EXPORT_SYMBOL_GPL(nf_sk_lookup_slow_v4);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Krisztian Kovacs, Balazs Scheidler");
MODULE_DESCRIPTION("Netfilter IPv4 socket lookup infrastructure");
