<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    S390 fast network checksum routines
 *
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Ulrich Hild        (first version)
 *               Martin Schwidefsky (heavily optimized CKSM version)
 *               D.J. Barrow        (third attempt) 
 */

#अगर_अघोषित _S390_CHECKSUM_H
#घोषणा _S390_CHECKSUM_H

#समावेश <linux/uaccess.h>
#समावेश <linux/in6.h>

/*
 * Computes the checksum of a memory block at buff, length len,
 * and adds in "sum" (32-bit).
 *
 * Returns a 32-bit number suitable क्रम feeding पूर्णांकo itself
 * or csum_tcpudp_magic.
 *
 * This function must be called with even lengths, except
 * क्रम the last fragment, which may be odd.
 *
 * It's best to have buff aligned on a 32-bit boundary.
 */
अटल अंतरभूत __wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र("2") = (अचिन्हित दीर्घ) buff;
	रेजिस्टर अचिन्हित दीर्घ reg3 यंत्र("3") = (अचिन्हित दीर्घ) len;

	यंत्र अस्थिर(
		"0:	cksm	%0,%1\n"	/* करो checksum on दीर्घs */
		"	jo	0b\n"
		: "+d" (sum), "+d" (reg2), "+d" (reg3) : : "cc", "memory");
	वापस sum;
पूर्ण

/*
 * Fold a partial checksum without adding pseuकरो headers.
 */
अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	u32 csum = (__क्रमce u32) sum;

	csum += (csum >> 16) | (csum << 16);
	csum >>= 16;
	वापस (__क्रमce __sum16) ~csum;
पूर्ण

/*
 * This is a version of ip_compute_csum() optimized क्रम IP headers,
 * which always checksums on 4 octet boundaries.
 */
अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	__u64 csum = 0;
	__u32 *ptr = (u32 *)iph;

	csum += *ptr++;
	csum += *ptr++;
	csum += *ptr++;
	csum += *ptr++;
	ihl -= 4;
	जबतक (ihl--)
		csum += *ptr++;
	csum += (csum >> 32) | (csum << 32);
	वापस csum_fold((__क्रमce __wsum)(csum >> 32));
पूर्ण

/*
 * Computes the checksum of the TCP/UDP pseuकरो-header.
 * Returns a 32-bit checksum.
 */
अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len,
					__u8 proto, __wsum sum)
अणु
	__u64 csum = (__क्रमce __u64)sum;

	csum += (__क्रमce __u32)saddr;
	csum += (__क्रमce __u32)daddr;
	csum += len;
	csum += proto;
	csum += (csum >> 32) | (csum << 32);
	वापस (__क्रमce __wsum)(csum >> 32);
पूर्ण

/*
 * Computes the checksum of the TCP/UDP pseuकरो-header.
 * Returns a 16-bit checksum, alपढ़ोy complemented.
 */
अटल अंतरभूत __sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr, __u32 len,
					__u8 proto, __wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
पूर्ण

/*
 * Used क्रम miscellaneous IP-like checksums, मुख्यly icmp.
 */
अटल अंतरभूत __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस csum_fold(csum_partial(buff, len, 0));
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM
अटल अंतरभूत __sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
				      स्थिर काष्ठा in6_addr *daddr,
				      __u32 len, __u8 proto, __wsum csum)
अणु
	__u64 sum = (__क्रमce __u64)csum;

	sum += (__क्रमce __u32)saddr->s6_addr32[0];
	sum += (__क्रमce __u32)saddr->s6_addr32[1];
	sum += (__क्रमce __u32)saddr->s6_addr32[2];
	sum += (__क्रमce __u32)saddr->s6_addr32[3];
	sum += (__क्रमce __u32)daddr->s6_addr32[0];
	sum += (__क्रमce __u32)daddr->s6_addr32[1];
	sum += (__क्रमce __u32)daddr->s6_addr32[2];
	sum += (__क्रमce __u32)daddr->s6_addr32[3];
	sum += len;
	sum += proto;
	sum += (sum >> 32) | (sum << 32);
	वापस csum_fold((__क्रमce __wsum)(sum >> 32));
पूर्ण

#पूर्ण_अगर /* _S390_CHECKSUM_H */
