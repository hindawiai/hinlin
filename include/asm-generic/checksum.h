<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_CHECKSUM_H
#घोषणा __ASM_GENERIC_CHECKSUM_H

/*
 * computes the checksum of a memory block at buff, length len,
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

#अगर_अघोषित ip_fast_csum
/*
 * This is a version of ip_compute_csum() optimized क्रम IP headers,
 * which always checksum on 4 octet boundaries.
 */
बाह्य __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl);
#पूर्ण_अगर

#अगर_अघोषित csum_fold
/*
 * Fold a partial checksum
 */
अटल अंतरभूत __sum16 csum_fold(__wsum csum)
अणु
	u32 sum = (__क्रमce u32)csum;
	sum = (sum & 0xffff) + (sum >> 16);
	sum = (sum & 0xffff) + (sum >> 16);
	वापस (__क्रमce __sum16)~sum;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित csum_tcpudp_nofold
/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented
 */
बाह्य __wsum
csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len,
		   __u8 proto, __wsum sum);
#पूर्ण_अगर

#अगर_अघोषित csum_tcpudp_magic
अटल अंतरभूत __sum16
csum_tcpudp_magic(__be32 saddr, __be32 daddr, __u32 len,
		  __u8 proto, __wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
पूर्ण
#पूर्ण_अगर

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */
बाह्य __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len);

#पूर्ण_अगर /* __ASM_GENERIC_CHECKSUM_H */
