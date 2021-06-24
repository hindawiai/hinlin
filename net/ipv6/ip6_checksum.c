<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <net/ip.h>
#समावेश <net/udp.h>
#समावेश <net/udplite.h>
#समावेश <यंत्र/checksum.h>

#अगर_अघोषित _HAVE_ARCH_IPV6_CSUM
__sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
			स्थिर काष्ठा in6_addr *daddr,
			__u32 len, __u8 proto, __wsum csum)
अणु

	पूर्णांक carry;
	__u32 ulen;
	__u32 uproto;
	__u32 sum = (__क्रमce u32)csum;

	sum += (__क्रमce u32)saddr->s6_addr32[0];
	carry = (sum < (__क्रमce u32)saddr->s6_addr32[0]);
	sum += carry;

	sum += (__क्रमce u32)saddr->s6_addr32[1];
	carry = (sum < (__क्रमce u32)saddr->s6_addr32[1]);
	sum += carry;

	sum += (__क्रमce u32)saddr->s6_addr32[2];
	carry = (sum < (__क्रमce u32)saddr->s6_addr32[2]);
	sum += carry;

	sum += (__क्रमce u32)saddr->s6_addr32[3];
	carry = (sum < (__क्रमce u32)saddr->s6_addr32[3]);
	sum += carry;

	sum += (__क्रमce u32)daddr->s6_addr32[0];
	carry = (sum < (__क्रमce u32)daddr->s6_addr32[0]);
	sum += carry;

	sum += (__क्रमce u32)daddr->s6_addr32[1];
	carry = (sum < (__क्रमce u32)daddr->s6_addr32[1]);
	sum += carry;

	sum += (__क्रमce u32)daddr->s6_addr32[2];
	carry = (sum < (__क्रमce u32)daddr->s6_addr32[2]);
	sum += carry;

	sum += (__क्रमce u32)daddr->s6_addr32[3];
	carry = (sum < (__क्रमce u32)daddr->s6_addr32[3]);
	sum += carry;

	ulen = (__क्रमce u32)htonl((__u32) len);
	sum += ulen;
	carry = (sum < ulen);
	sum += carry;

	uproto = (__क्रमce u32)htonl(proto);
	sum += uproto;
	carry = (sum < uproto);
	sum += carry;

	वापस csum_fold((__क्रमce __wsum)sum);
पूर्ण
EXPORT_SYMBOL(csum_ipv6_magic);
#पूर्ण_अगर

पूर्णांक udp6_csum_init(काष्ठा sk_buff *skb, काष्ठा udphdr *uh, पूर्णांक proto)
अणु
	पूर्णांक err;

	UDP_SKB_CB(skb)->partial_cov = 0;
	UDP_SKB_CB(skb)->cscov = skb->len;

	अगर (proto == IPPROTO_UDPLITE) अणु
		err = udplite_checksum_init(skb, uh);
		अगर (err)
			वापस err;

		अगर (UDP_SKB_CB(skb)->partial_cov) अणु
			skb->csum = ip6_compute_pseuकरो(skb, proto);
			वापस 0;
		पूर्ण
	पूर्ण

	/* To support RFC 6936 (allow zero checksum in UDP/IPV6 क्रम tunnels)
	 * we accept a checksum of zero here. When we find the socket
	 * क्रम the UDP packet we'll check अगर that socket allows zero checksum
	 * क्रम IPv6 (set by socket option).
	 *
	 * Note, we are only पूर्णांकerested in != 0 or == 0, thus the
	 * क्रमce to पूर्णांक.
	 */
	err = (__क्रमce पूर्णांक)skb_checksum_init_zero_check(skb, proto, uh->check,
							ip6_compute_pseuकरो);
	अगर (err)
		वापस err;

	अगर (skb->ip_summed == CHECKSUM_COMPLETE && !skb->csum_valid) अणु
		/* If SW calculated the value, we know it's bad */
		अगर (skb->csum_complete_sw)
			वापस 1;

		/* HW says the value is bad. Let's validate that.
		 * skb->csum is no दीर्घer the full packet checksum,
		 * so करोn't treat is as such.
		 */
		skb_checksum_complete_unset(skb);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(udp6_csum_init);

/* Function to set UDP checksum क्रम an IPv6 UDP packet. This is पूर्णांकended
 * क्रम the simple हाल like when setting the checksum क्रम a UDP tunnel.
 */
व्योम udp6_set_csum(bool nocheck, काष्ठा sk_buff *skb,
		   स्थिर काष्ठा in6_addr *saddr,
		   स्थिर काष्ठा in6_addr *daddr, पूर्णांक len)
अणु
	काष्ठा udphdr *uh = udp_hdr(skb);

	अगर (nocheck)
		uh->check = 0;
	अन्यथा अगर (skb_is_gso(skb))
		uh->check = ~udp_v6_check(len, saddr, daddr, 0);
	अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		uh->check = 0;
		uh->check = udp_v6_check(len, saddr, daddr, lco_csum(skb));
		अगर (uh->check == 0)
			uh->check = CSUM_MANGLED_0;
	पूर्ण अन्यथा अणु
		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = दुरत्व(काष्ठा udphdr, check);
		uh->check = ~udp_v6_check(len, saddr, daddr, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(udp6_set_csum);
