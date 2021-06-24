<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _INET_ECN_H_
#घोषणा _INET_ECN_H_

#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <net/inet_sock.h>
#समावेश <net/dsfield.h>
#समावेश <net/checksum.h>

क्रमागत अणु
	INET_ECN_NOT_ECT = 0,
	INET_ECN_ECT_1 = 1,
	INET_ECN_ECT_0 = 2,
	INET_ECN_CE = 3,
	INET_ECN_MASK = 3,
पूर्ण;

बाह्य पूर्णांक sysctl_tunnel_ecn_log;

अटल अंतरभूत पूर्णांक INET_ECN_is_ce(__u8 dsfield)
अणु
	वापस (dsfield & INET_ECN_MASK) == INET_ECN_CE;
पूर्ण

अटल अंतरभूत पूर्णांक INET_ECN_is_not_ect(__u8 dsfield)
अणु
	वापस (dsfield & INET_ECN_MASK) == INET_ECN_NOT_ECT;
पूर्ण

अटल अंतरभूत पूर्णांक INET_ECN_is_capable(__u8 dsfield)
अणु
	वापस dsfield & INET_ECN_ECT_0;
पूर्ण

/*
 * RFC 3168 9.1.1
 *  The full-functionality option क्रम ECN encapsulation is to copy the
 *  ECN codepoपूर्णांक of the inside header to the outside header on
 *  encapsulation अगर the inside header is not-ECT or ECT, and to set the
 *  ECN codepoपूर्णांक of the outside header to ECT(0) अगर the ECN codepoपूर्णांक of
 *  the inside header is CE.
 */
अटल अंतरभूत __u8 INET_ECN_encapsulate(__u8 outer, __u8 inner)
अणु
	outer &= ~INET_ECN_MASK;
	outer |= !INET_ECN_is_ce(inner) ? (inner & INET_ECN_MASK) :
					  INET_ECN_ECT_0;
	वापस outer;
पूर्ण

अटल अंतरभूत व्योम INET_ECN_xmit(काष्ठा sock *sk)
अणु
	inet_sk(sk)->tos |= INET_ECN_ECT_0;
	अगर (inet6_sk(sk) != शून्य)
		inet6_sk(sk)->tclass |= INET_ECN_ECT_0;
पूर्ण

अटल अंतरभूत व्योम INET_ECN_करोntxmit(काष्ठा sock *sk)
अणु
	inet_sk(sk)->tos &= ~INET_ECN_MASK;
	अगर (inet6_sk(sk) != शून्य)
		inet6_sk(sk)->tclass &= ~INET_ECN_MASK;
पूर्ण

#घोषणा IP6_ECN_flow_init(label) करो अणु		\
      (label) &= ~htonl(INET_ECN_MASK << 20);	\
    पूर्ण जबतक (0)

#घोषणा	IP6_ECN_flow_xmit(sk, label) करो अणु				\
	अगर (INET_ECN_is_capable(inet6_sk(sk)->tclass))			\
		(label) |= htonl(INET_ECN_ECT_0 << 20);			\
    पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक IP_ECN_set_ce(काष्ठा iphdr *iph)
अणु
	u32 ecn = (iph->tos + 1) & INET_ECN_MASK;
	__be16 check_add;

	/*
	 * After the last operation we have (in binary):
	 * INET_ECN_NOT_ECT => 01
	 * INET_ECN_ECT_1   => 10
	 * INET_ECN_ECT_0   => 11
	 * INET_ECN_CE      => 00
	 */
	अगर (!(ecn & 2))
		वापस !ecn;

	/*
	 * The following gives us:
	 * INET_ECN_ECT_1 => check += htons(0xFFFD)
	 * INET_ECN_ECT_0 => check += htons(0xFFFE)
	 */
	check_add = (__क्रमce __be16)((__क्रमce u16)htons(0xFFFB) +
				     (__क्रमce u16)htons(ecn));

	iph->check = csum16_add(iph->check, check_add);
	iph->tos |= INET_ECN_CE;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक IP_ECN_set_ect1(काष्ठा iphdr *iph)
अणु
	अगर ((iph->tos & INET_ECN_MASK) != INET_ECN_ECT_0)
		वापस 0;

	iph->check = csum16_add(iph->check, htons(0x1));
	iph->tos ^= INET_ECN_MASK;
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम IP_ECN_clear(काष्ठा iphdr *iph)
अणु
	iph->tos &= ~INET_ECN_MASK;
पूर्ण

अटल अंतरभूत व्योम ipv4_copy_dscp(अचिन्हित पूर्णांक dscp, काष्ठा iphdr *inner)
अणु
	dscp &= ~INET_ECN_MASK;
	ipv4_change_dsfield(inner, INET_ECN_MASK, dscp);
पूर्ण

काष्ठा ipv6hdr;

/* Note:
 * IP_ECN_set_ce() has to tweak IPV4 checksum when setting CE,
 * meaning both changes have no effect on skb->csum अगर/when CHECKSUM_COMPLETE
 * In IPv6 हाल, no checksum compensates the change in IPv6 header,
 * so we have to update skb->csum.
 */
अटल अंतरभूत पूर्णांक IP6_ECN_set_ce(काष्ठा sk_buff *skb, काष्ठा ipv6hdr *iph)
अणु
	__be32 from, to;

	अगर (INET_ECN_is_not_ect(ipv6_get_dsfield(iph)))
		वापस 0;

	from = *(__be32 *)iph;
	to = from | htonl(INET_ECN_CE << 20);
	*(__be32 *)iph = to;
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->csum = csum_add(csum_sub(skb->csum, (__क्रमce __wsum)from),
				     (__क्रमce __wsum)to);
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक IP6_ECN_set_ect1(काष्ठा sk_buff *skb, काष्ठा ipv6hdr *iph)
अणु
	__be32 from, to;

	अगर ((ipv6_get_dsfield(iph) & INET_ECN_MASK) != INET_ECN_ECT_0)
		वापस 0;

	from = *(__be32 *)iph;
	to = from ^ htonl(INET_ECN_MASK << 20);
	*(__be32 *)iph = to;
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->csum = csum_add(csum_sub(skb->csum, (__क्रमce __wsum)from),
				     (__क्रमce __wsum)to);
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम ipv6_copy_dscp(अचिन्हित पूर्णांक dscp, काष्ठा ipv6hdr *inner)
अणु
	dscp &= ~INET_ECN_MASK;
	ipv6_change_dsfield(inner, INET_ECN_MASK, dscp);
पूर्ण

अटल अंतरभूत पूर्णांक INET_ECN_set_ce(काष्ठा sk_buff *skb)
अणु
	चयन (skb_protocol(skb, true)) अणु
	हाल cpu_to_be16(ETH_P_IP):
		अगर (skb_network_header(skb) + माप(काष्ठा iphdr) <=
		    skb_tail_poपूर्णांकer(skb))
			वापस IP_ECN_set_ce(ip_hdr(skb));
		अवरोध;

	हाल cpu_to_be16(ETH_P_IPV6):
		अगर (skb_network_header(skb) + माप(काष्ठा ipv6hdr) <=
		    skb_tail_poपूर्णांकer(skb))
			वापस IP6_ECN_set_ce(skb, ipv6_hdr(skb));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक INET_ECN_set_ect1(काष्ठा sk_buff *skb)
अणु
	चयन (skb_protocol(skb, true)) अणु
	हाल cpu_to_be16(ETH_P_IP):
		अगर (skb_network_header(skb) + माप(काष्ठा iphdr) <=
		    skb_tail_poपूर्णांकer(skb))
			वापस IP_ECN_set_ect1(ip_hdr(skb));
		अवरोध;

	हाल cpu_to_be16(ETH_P_IPV6):
		अगर (skb_network_header(skb) + माप(काष्ठा ipv6hdr) <=
		    skb_tail_poपूर्णांकer(skb))
			वापस IP6_ECN_set_ect1(skb, ipv6_hdr(skb));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * RFC 6040 4.2
 *  To decapsulate the inner header at the tunnel egress, a compliant
 *  tunnel egress MUST set the outgoing ECN field to the codepoपूर्णांक at the
 *  पूर्णांकersection of the appropriate arriving inner header (row) and outer
 *  header (column) in Figure 4
 *
 *      +---------+------------------------------------------------+
 *      |Arriving |            Arriving Outer Header               |
 *      |   Inner +---------+------------+------------+------------+
 *      |  Header | Not-ECT | ECT(0)     | ECT(1)     |     CE     |
 *      +---------+---------+------------+------------+------------+
 *      | Not-ECT | Not-ECT |Not-ECT(!!!)|Not-ECT(!!!)| <drop>(!!!)|
 *      |  ECT(0) |  ECT(0) | ECT(0)     | ECT(1)     |     CE     |
 *      |  ECT(1) |  ECT(1) | ECT(1) (!) | ECT(1)     |     CE     |
 *      |    CE   |      CE |     CE     |     CE(!!!)|     CE     |
 *      +---------+---------+------------+------------+------------+
 *
 *             Figure 4: New IP in IP Decapsulation Behaviour
 *
 *  वापसs 0 on success
 *          1 अगर something is broken and should be logged (!!! above)
 *          2 अगर packet should be dropped
 */
अटल अंतरभूत पूर्णांक __INET_ECN_decapsulate(__u8 outer, __u8 inner, bool *set_ce)
अणु
	अगर (INET_ECN_is_not_ect(inner)) अणु
		चयन (outer & INET_ECN_MASK) अणु
		हाल INET_ECN_NOT_ECT:
			वापस 0;
		हाल INET_ECN_ECT_0:
		हाल INET_ECN_ECT_1:
			वापस 1;
		हाल INET_ECN_CE:
			वापस 2;
		पूर्ण
	पूर्ण

	*set_ce = INET_ECN_is_ce(outer);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक INET_ECN_decapsulate(काष्ठा sk_buff *skb,
				       __u8 outer, __u8 inner)
अणु
	bool set_ce = false;
	पूर्णांक rc;

	rc = __INET_ECN_decapsulate(outer, inner, &set_ce);
	अगर (!rc) अणु
		अगर (set_ce)
			INET_ECN_set_ce(skb);
		अन्यथा अगर ((outer & INET_ECN_MASK) == INET_ECN_ECT_1)
			INET_ECN_set_ect1(skb);
	पूर्ण

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक IP_ECN_decapsulate(स्थिर काष्ठा iphdr *oiph,
				     काष्ठा sk_buff *skb)
अणु
	__u8 inner;

	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		inner = ip_hdr(skb)->tos;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		inner = ipv6_get_dsfield(ipv6_hdr(skb));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस INET_ECN_decapsulate(skb, oiph->tos, inner);
पूर्ण

अटल अंतरभूत पूर्णांक IP6_ECN_decapsulate(स्थिर काष्ठा ipv6hdr *oipv6h,
				      काष्ठा sk_buff *skb)
अणु
	__u8 inner;

	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		inner = ip_hdr(skb)->tos;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		inner = ipv6_get_dsfield(ipv6_hdr(skb));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस INET_ECN_decapsulate(skb, ipv6_get_dsfield(oipv6h), inner);
पूर्ण
#पूर्ण_अगर
