<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2003-2011 Jozsef Kadlecsik <kadlec@netfilter.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/* Get Layer-4 data from the packets */

#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/icmp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/sctp.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>

#समावेश <linux/netfilter/ipset/ip_set_getport.h>
#समावेश <linux/export.h>

/* We must handle non-linear skbs */
अटल bool
get_port(स्थिर काष्ठा sk_buff *skb, पूर्णांक protocol, अचिन्हित पूर्णांक protooff,
	 bool src, __be16 *port, u8 *proto)
अणु
	चयन (protocol) अणु
	हाल IPPROTO_TCP: अणु
		काष्ठा tcphdr _tcph;
		स्थिर काष्ठा tcphdr *th;

		th = skb_header_poपूर्णांकer(skb, protooff, माप(_tcph), &_tcph);
		अगर (!th)
			/* No choice either */
			वापस false;

		*port = src ? th->source : th->dest;
		अवरोध;
	पूर्ण
	हाल IPPROTO_SCTP: अणु
		काष्ठा sctphdr _sh;
		स्थिर काष्ठा sctphdr *sh;

		sh = skb_header_poपूर्णांकer(skb, protooff, माप(_sh), &_sh);
		अगर (!sh)
			/* No choice either */
			वापस false;

		*port = src ? sh->source : sh->dest;
		अवरोध;
	पूर्ण
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE: अणु
		काष्ठा udphdr _udph;
		स्थिर काष्ठा udphdr *uh;

		uh = skb_header_poपूर्णांकer(skb, protooff, माप(_udph), &_udph);
		अगर (!uh)
			/* No choice either */
			वापस false;

		*port = src ? uh->source : uh->dest;
		अवरोध;
	पूर्ण
	हाल IPPROTO_ICMP: अणु
		काष्ठा icmphdr _ich;
		स्थिर काष्ठा icmphdr *ic;

		ic = skb_header_poपूर्णांकer(skb, protooff, माप(_ich), &_ich);
		अगर (!ic)
			वापस false;

		*port = (__क्रमce __be16)htons((ic->type << 8) | ic->code);
		अवरोध;
	पूर्ण
	हाल IPPROTO_ICMPV6: अणु
		काष्ठा icmp6hdr _ich;
		स्थिर काष्ठा icmp6hdr *ic;

		ic = skb_header_poपूर्णांकer(skb, protooff, माप(_ich), &_ich);
		अगर (!ic)
			वापस false;

		*port = (__क्रमce __be16)
			htons((ic->icmp6_type << 8) | ic->icmp6_code);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
	*proto = protocol;

	वापस true;
पूर्ण

bool
ip_set_get_ip4_port(स्थिर काष्ठा sk_buff *skb, bool src,
		    __be16 *port, u8 *proto)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	अचिन्हित पूर्णांक protooff = skb_network_offset(skb) + ip_hdrlen(skb);
	पूर्णांक protocol = iph->protocol;

	/* See comments at tcp_match in ip_tables.c */
	अगर (protocol <= 0)
		वापस false;

	अगर (ntohs(iph->frag_off) & IP_OFFSET)
		चयन (protocol) अणु
		हाल IPPROTO_TCP:
		हाल IPPROTO_SCTP:
		हाल IPPROTO_UDP:
		हाल IPPROTO_UDPLITE:
		हाल IPPROTO_ICMP:
			/* Port info not available क्रम fragment offset > 0 */
			वापस false;
		शेष:
			/* Other protocols करोesn't have ports,
			 * so we can match fragments.
			 */
			*proto = protocol;
			वापस true;
		पूर्ण

	वापस get_port(skb, protocol, protooff, src, port, proto);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_get_ip4_port);

#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
bool
ip_set_get_ip6_port(स्थिर काष्ठा sk_buff *skb, bool src,
		    __be16 *port, u8 *proto)
अणु
	पूर्णांक protoff;
	u8 nexthdr;
	__be16 frag_off = 0;

	nexthdr = ipv6_hdr(skb)->nexthdr;
	protoff = ipv6_skip_exthdr(skb,
				   skb_network_offset(skb) +
					माप(काष्ठा ipv6hdr), &nexthdr,
				   &frag_off);
	अगर (protoff < 0 || (frag_off & htons(~0x7)) != 0)
		वापस false;

	वापस get_port(skb, nexthdr, protoff, src, port, proto);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_get_ip6_port);
#पूर्ण_अगर
