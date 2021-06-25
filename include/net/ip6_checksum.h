<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Checksumming functions क्रम IPv6
 *
 * Authors:	Jorge Cwik, <jorge@laser.satlink.net>
 *		Arnt Gulbअक्रमsen, <agulbra@nvg.unit.no>
 *		Borrows very liberally from tcp.c and ip.c, see those
 *		files क्रम more names.
 */

/*
 *	Fixes:
 *
 *	Ralf Baechle			:	generic ipv6 checksum
 *	<ralf@walकरोrf-gmbh.de>
 */

#अगर_अघोषित _CHECKSUM_IPV6_H
#घोषणा _CHECKSUM_IPV6_H

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <net/ip.h>
#समावेश <यंत्र/checksum.h>
#समावेश <linux/in6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ipv6.h>

#अगर_अघोषित _HAVE_ARCH_IPV6_CSUM
__sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
			स्थिर काष्ठा in6_addr *daddr,
			__u32 len, __u8 proto, __wsum csum);
#पूर्ण_अगर

अटल अंतरभूत __wsum ip6_compute_pseuकरो(काष्ठा sk_buff *skb, पूर्णांक proto)
अणु
	वापस ~csum_unfold(csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
					    &ipv6_hdr(skb)->daddr,
					    skb->len, proto, 0));
पूर्ण

अटल अंतरभूत __wsum ip6_gro_compute_pseuकरो(काष्ठा sk_buff *skb, पूर्णांक proto)
अणु
	स्थिर काष्ठा ipv6hdr *iph = skb_gro_network_header(skb);

	वापस ~csum_unfold(csum_ipv6_magic(&iph->saddr, &iph->daddr,
					    skb_gro_len(skb), proto, 0));
पूर्ण

अटल __अंतरभूत__ __sum16 tcp_v6_check(पूर्णांक len,
				   स्थिर काष्ठा in6_addr *saddr,
				   स्थिर काष्ठा in6_addr *daddr,
				   __wsum base)
अणु
	वापस csum_ipv6_magic(saddr, daddr, len, IPPROTO_TCP, base);
पूर्ण

अटल अंतरभूत व्योम __tcp_v6_send_check(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा in6_addr *saddr,
				       स्थिर काष्ठा in6_addr *daddr)
अणु
	काष्ठा tcphdr *th = tcp_hdr(skb);

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		th->check = ~tcp_v6_check(skb->len, saddr, daddr, 0);
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = दुरत्व(काष्ठा tcphdr, check);
	पूर्ण अन्यथा अणु
		th->check = tcp_v6_check(skb->len, saddr, daddr,
					 csum_partial(th, th->करोff << 2,
						      skb->csum));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम tcp_v6_gso_csum_prep(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
	काष्ठा tcphdr *th = tcp_hdr(skb);

	ipv6h->payload_len = 0;
	th->check = ~tcp_v6_check(0, &ipv6h->saddr, &ipv6h->daddr, 0);
पूर्ण

अटल अंतरभूत __sum16 udp_v6_check(पूर्णांक len,
				   स्थिर काष्ठा in6_addr *saddr,
				   स्थिर काष्ठा in6_addr *daddr,
				   __wsum base)
अणु
	वापस csum_ipv6_magic(saddr, daddr, len, IPPROTO_UDP, base);
पूर्ण

व्योम udp6_set_csum(bool nocheck, काष्ठा sk_buff *skb,
		   स्थिर काष्ठा in6_addr *saddr,
		   स्थिर काष्ठा in6_addr *daddr, पूर्णांक len);

पूर्णांक udp6_csum_init(काष्ठा sk_buff *skb, काष्ठा udphdr *uh, पूर्णांक proto);
#पूर्ण_अगर
