<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PFXLEN_H
#घोषणा _PFXLEN_H

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/netfilter.h>
#समावेश <net/tcp.h>

/* Prefixlen maps, by Jan Engelhardt  */
बाह्य स्थिर जोड़ nf_inet_addr ip_set_neपंचांगask_map[];
बाह्य स्थिर जोड़ nf_inet_addr ip_set_hosपंचांगask_map[];

अटल अंतरभूत __be32
ip_set_neपंचांगask(u8 pfxlen)
अणु
	वापस ip_set_neपंचांगask_map[pfxlen].ip;
पूर्ण

अटल अंतरभूत स्थिर __be32 *
ip_set_neपंचांगask6(u8 pfxlen)
अणु
	वापस &ip_set_neपंचांगask_map[pfxlen].ip6[0];
पूर्ण

अटल अंतरभूत u32
ip_set_hosपंचांगask(u8 pfxlen)
अणु
	वापस (__क्रमce u32) ip_set_hosपंचांगask_map[pfxlen].ip;
पूर्ण

अटल अंतरभूत स्थिर __be32 *
ip_set_hosपंचांगask6(u8 pfxlen)
अणु
	वापस &ip_set_hosपंचांगask_map[pfxlen].ip6[0];
पूर्ण

बाह्य u32 ip_set_range_to_cidr(u32 from, u32 to, u8 *cidr);

#घोषणा ip_set_mask_from_to(from, to, cidr)	\
करो अणु						\
	from &= ip_set_hosपंचांगask(cidr);		\
	to = from | ~ip_set_hosपंचांगask(cidr);	\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम
ip6_neपंचांगask(जोड़ nf_inet_addr *ip, u8 prefix)
अणु
	ip->ip6[0] &= ip_set_neपंचांगask6(prefix)[0];
	ip->ip6[1] &= ip_set_neपंचांगask6(prefix)[1];
	ip->ip6[2] &= ip_set_neपंचांगask6(prefix)[2];
	ip->ip6[3] &= ip_set_neपंचांगask6(prefix)[3];
पूर्ण

#पूर्ण_अगर /*_PFXLEN_H */
