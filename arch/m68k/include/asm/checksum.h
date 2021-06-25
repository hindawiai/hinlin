<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_CHECKSUM_H
#घोषणा _M68K_CHECKSUM_H

#समावेश <linux/in6.h>

#अगर_घोषित CONFIG_GENERIC_CSUM
#समावेश <यंत्र-generic/checksum.h>
#अन्यथा

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
__wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum);

/*
 * the same as csum_partial, but copies from src जबतक it
 * checksums
 *
 * here even more important to align src and dst on a 32-bit (or even
 * better 64-bit) boundary
 */

#घोषणा _HAVE_ARCH_COPY_AND_CSUM_FROM_USER
#घोषणा _HAVE_ARCH_CSUM_AND_COPY
बाह्य __wsum csum_and_copy_from_user(स्थिर व्योम __user *src,
						व्योम *dst,
						पूर्णांक len);

बाह्य __wsum csum_partial_copy_nocheck(स्थिर व्योम *src,
					      व्योम *dst, पूर्णांक len);

/*
 *	This is a version of ip_fast_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 */
अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	अचिन्हित पूर्णांक sum = 0;
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ ("subqw #1,%2\n"
		 "1:\t"
		 "movel %1@+,%3\n\t"
		 "addxl %3,%0\n\t"
		 "dbra  %2,1b\n\t"
		 "movel %0,%3\n\t"
		 "swap  %3\n\t"
		 "addxw %3,%0\n\t"
		 "clrw  %3\n\t"
		 "addxw %3,%0\n\t"
		 : "=d" (sum), "=&a" (iph), "=&d" (ihl), "=&d" (पंचांगp)
		 : "0" (sum), "1" (iph), "2" (ihl)
		 : "memory");
	वापस (__क्रमce __sum16)~sum;
पूर्ण

अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	अचिन्हित पूर्णांक पंचांगp = (__क्रमce u32)sum;

	__यंत्र__("swap %1\n\t"
		"addw %1, %0\n\t"
		"clrw %1\n\t"
		"addxw %1, %0"
		: "=&d" (sum), "=&d" (पंचांगp)
		: "0" (sum), "1" (पंचांगp));

	वापस (__क्रमce __sum16)~sum;
पूर्ण

अटल अंतरभूत __wsum
csum_tcpudp_nofold(__be32 saddr, __be32 daddr, अचिन्हित लघु len,
		  अचिन्हित लघु proto, __wsum sum)
अणु
	__यंत्र__ ("addl  %2,%0\n\t"
		 "addxl %3,%0\n\t"
		 "addxl %4,%0\n\t"
		 "clrl %1\n\t"
		 "addxl %1,%0"
		 : "=&d" (sum), "=d" (saddr)
		 : "g" (daddr), "1" (saddr), "d" (len + proto),
		   "0" (sum));
	वापस sum;
पूर्ण


/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented
 */
अटल अंतरभूत __sum16
csum_tcpudp_magic(__be32 saddr, __be32 daddr, अचिन्हित लघु len,
		  अचिन्हित लघु proto, __wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr,daddr,len,proto,sum));
पूर्ण

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */

अटल अंतरभूत __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस csum_fold (csum_partial(buff, len, 0));
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM
अटल __अंतरभूत__ __sum16
csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr, स्थिर काष्ठा in6_addr *daddr,
		__u32 len, __u8 proto, __wsum sum)
अणु
	रेजिस्टर अचिन्हित दीर्घ पंचांगp;
	__यंत्र__("addl %2@,%0\n\t"
		"movel %2@(4),%1\n\t"
		"addxl %1,%0\n\t"
		"movel %2@(8),%1\n\t"
		"addxl %1,%0\n\t"
		"movel %2@(12),%1\n\t"
		"addxl %1,%0\n\t"
		"movel %3@,%1\n\t"
		"addxl %1,%0\n\t"
		"movel %3@(4),%1\n\t"
		"addxl %1,%0\n\t"
		"movel %3@(8),%1\n\t"
		"addxl %1,%0\n\t"
		"movel %3@(12),%1\n\t"
		"addxl %1,%0\n\t"
		"addxl %4,%0\n\t"
		"clrl %1\n\t"
		"addxl %1,%0"
		: "=&d" (sum), "=&d" (पंचांगp)
		: "a" (saddr), "a" (daddr), "d" (len + proto),
		  "0" (sum));

	वापस csum_fold(sum);
पूर्ण

#पूर्ण_अगर /* CONFIG_GENERIC_CSUM */
#पूर्ण_अगर /* _M68K_CHECKSUM_H */
