<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  arch/arm/include/यंत्र/checksum.h
 *
 * IP checksum routines
 *
 * Copyright (C) Original authors of ../यंत्र-i386/checksum.h
 * Copyright (C) 1996-1999 Russell King
 */
#अगर_अघोषित __ASM_ARM_CHECKSUM_H
#घोषणा __ASM_ARM_CHECKSUM_H

#समावेश <linux/in6.h>

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
 * checksums, and handles user-space poपूर्णांकer exceptions correctly, when needed.
 *
 * here even more important to align src and dst on a 32-bit (or even
 * better 64-bit) boundary
 */

__wsum
csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len);

__wsum
csum_partial_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len);

#घोषणा _HAVE_ARCH_COPY_AND_CSUM_FROM_USER
#घोषणा _HAVE_ARCH_CSUM_AND_COPY
अटल अंतरभूत
__wsum csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len)
अणु
	अगर (!access_ok(src, len))
		वापस 0;

	वापस csum_partial_copy_from_user(src, dst, len);
पूर्ण

/*
 * 	Fold a partial checksum without adding pseuकरो headers
 */
अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	__यंत्र__(
	"add	%0, %1, %1, ror #16	@ csum_fold"
	: "=r" (sum)
	: "r" (sum)
	: "cc");
	वापस (__क्रमce __sum16)(~(__क्रमce u32)sum >> 16);
पूर्ण

/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 */
अटल अंतरभूत __sum16
ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	अचिन्हित पूर्णांक पंचांगp1;
	__wsum sum;

	__यंत्र__ __अस्थिर__(
	"ldr	%0, [%1], #4		@ ip_fast_csum		\न\
	ldr	%3, [%1], #4					\न\
	sub	%2, %2, #5					\न\
	adds	%0, %0, %3					\न\
	ldr	%3, [%1], #4					\न\
	adcs	%0, %0, %3					\न\
	ldr	%3, [%1], #4					\न\
1:	adcs	%0, %0, %3					\न\
	ldr	%3, [%1], #4					\न\
	tst	%2, #15			@ करो this carefully	\न\
	subne	%2, %2, #1		@ without destroying	\न\
	bne	1b			@ the carry flag	\न\
	adcs	%0, %0, %3					\न\
	adc	%0, %0, #0"
	: "=r" (sum), "=r" (iph), "=r" (ihl), "=r" (पंचांगp1)
	: "1" (iph), "2" (ihl)
	: "cc", "memory");
	वापस csum_fold(sum);
पूर्ण

अटल अंतरभूत __wsum
csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len,
		   __u8 proto, __wsum sum)
अणु
	u32 lenprot = len + proto;
	अगर (__builtin_स्थिरant_p(sum) && sum == 0) अणु
		__यंत्र__(
		"adds	%0, %1, %2	@ csum_tcpudp_nofold0	\n\t"
#अगर_घोषित __ARMEB__
		"adcs	%0, %0, %3				\n\t"
#अन्यथा
		"adcs	%0, %0, %3, ror #8			\n\t"
#पूर्ण_अगर
		"adc	%0, %0, #0"
		: "=&r" (sum)
		: "r" (daddr), "r" (saddr), "r" (lenprot)
		: "cc");
	पूर्ण अन्यथा अणु
		__यंत्र__(
		"adds	%0, %1, %2	@ csum_tcpudp_nofold	\n\t"
		"adcs	%0, %0, %3				\n\t"
#अगर_घोषित __ARMEB__
		"adcs	%0, %0, %4				\n\t"
#अन्यथा
		"adcs	%0, %0, %4, ror #8			\n\t"
#पूर्ण_अगर
		"adc	%0, %0, #0"
		: "=&r"(sum)
		: "r" (sum), "r" (daddr), "r" (saddr), "r" (lenprot)
		: "cc");
	पूर्ण
	वापस sum;
पूर्ण	
/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented
 */
अटल अंतरभूत __sum16
csum_tcpudp_magic(__be32 saddr, __be32 daddr, __u32 len,
		  __u8 proto, __wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
पूर्ण


/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */
अटल अंतरभूत __sum16
ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस csum_fold(csum_partial(buff, len, 0));
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM
बाह्य __wsum
__csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr, स्थिर काष्ठा in6_addr *daddr, __be32 len,
		__be32 proto, __wsum sum);

अटल अंतरभूत __sum16
csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr, स्थिर काष्ठा in6_addr *daddr,
		__u32 len, __u8 proto, __wsum sum)
अणु
	वापस csum_fold(__csum_ipv6_magic(saddr, daddr, htonl(len),
					   htonl(proto), sum));
पूर्ण
#पूर्ण_अगर
