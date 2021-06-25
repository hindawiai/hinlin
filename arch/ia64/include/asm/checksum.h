<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_CHECKSUM_H
#घोषणा _ASM_IA64_CHECKSUM_H

/*
 * Modअगरied 1998, 1999
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 */

/*
 * This is a version of ip_compute_csum() optimized क्रम IP headers,
 * which always checksum on 4 octet boundaries.
 */
बाह्य __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl);

/*
 * Computes the checksum of the TCP/UDP pseuकरो-header वापसs a 16-bit
 * checksum, alपढ़ोy complemented
 */
बाह्य __sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr,
				 __u32 len, __u8 proto, __wsum sum);

बाह्य __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
				 __u32 len, __u8 proto, __wsum sum);

/*
 * Computes the checksum of a memory block at buff, length len,
 * and adds in "sum" (32-bit)
 *
 * वापसs a 32-bit number suitable क्रम feeding पूर्णांकo itself
 * or csum_tcpudp_magic
 *
 * this function must be called with even lengths, except
 * क्रम the last fragment, which may be odd
 *
 * it's best to have buff aligned on a 32-bit boundary
 */
बाह्य __wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum);

/*
 * This routine is used क्रम miscellaneous IP-like checksums, मुख्यly in
 * icmp.c
 */
बाह्य __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len);

/*
 * Fold a partial checksum without adding pseuकरो headers.
 */
अटल अंतरभूत __sum16 csum_fold(__wsum csum)
अणु
	u32 sum = (__क्रमce u32)csum;
	sum = (sum & 0xffff) + (sum >> 16);
	sum = (sum & 0xffff) + (sum >> 16);
	वापस (__क्रमce __sum16)~sum;
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM	1
काष्ठा in6_addr;
बाह्य __sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
			       स्थिर काष्ठा in6_addr *daddr,
			       __u32 len, __u8 proto, __wsum csum);

#पूर्ण_अगर /* _ASM_IA64_CHECKSUM_H */
