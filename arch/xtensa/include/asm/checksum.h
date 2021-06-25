<शैली गुरु>
/*
 * include/यंत्र-xtensa/checksum.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_CHECKSUM_H
#घोषणा _XTENSA_CHECKSUM_H

#समावेश <linux/in6.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/core.h>

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
यंत्रlinkage __wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum);

/*
 * the same as csum_partial, but copies from src जबतक it
 * checksums, and handles user-space poपूर्णांकer exceptions correctly, when needed.
 *
 * here even more important to align src and dst on a 32-bit (or even
 * better 64-bit) boundary
 */

यंत्रlinkage __wsum csum_partial_copy_generic(स्थिर व्योम *src, व्योम *dst, पूर्णांक len);

#घोषणा _HAVE_ARCH_CSUM_AND_COPY
/*
 *	Note: when you get a शून्य poपूर्णांकer exception here this means someone
 *	passed in an incorrect kernel address to one of these functions.
 */
अटल अंतरभूत
__wsum csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len)
अणु
	वापस csum_partial_copy_generic(src, dst, len);
पूर्ण

#घोषणा _HAVE_ARCH_COPY_AND_CSUM_FROM_USER
अटल अंतरभूत
__wsum csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst,
				   पूर्णांक len)
अणु
	अगर (!access_ok(src, len))
		वापस 0;
	वापस csum_partial_copy_generic((__क्रमce स्थिर व्योम *)src, dst, len);
पूर्ण

/*
 *	Fold a partial checksum
 */

अटल __अंतरभूत__ __sum16 csum_fold(__wsum sum)
अणु
	अचिन्हित पूर्णांक __dummy;
	__यंत्र__("extui	%1, %0, 16, 16\n\t"
		"extui	%0 ,%0, 0, 16\n\t"
		"add	%0, %0, %1\n\t"
		"slli	%1, %0, 16\n\t"
		"add	%0, %0, %1\n\t"
		"extui	%0, %0, 16, 16\n\t"
		"neg	%0, %0\n\t"
		"addi	%0, %0, -1\n\t"
		"extui	%0, %0, 0, 16\n\t"
		: "=r" (sum), "=&r" (__dummy)
		: "0" (sum));
	वापस (__क्रमce __sum16)sum;
पूर्ण

/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 */
अटल __अंतरभूत__ __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	अचिन्हित पूर्णांक sum, पंचांगp, endaddr;

	__यंत्र__ __अस्थिर__(
		"sub		%0, %0, %0\n\t"
#अगर XCHAL_HAVE_LOOPS
		"loopgtz	%2, 2f\n\t"
#अन्यथा
		"beqz		%2, 2f\n\t"
		"slli		%4, %2, 2\n\t"
		"add		%4, %4, %1\n\t"
		"0:\t"
#पूर्ण_अगर
		"l32i		%3, %1, 0\n\t"
		"add		%0, %0, %3\n\t"
		"bgeu		%0, %3, 1f\n\t"
		"addi		%0, %0, 1\n\t"
		"1:\t"
		"addi		%1, %1, 4\n\t"
#अगर !XCHAL_HAVE_LOOPS
		"blt		%1, %4, 0b\n\t"
#पूर्ण_अगर
		"2:\t"
	/* Since the input रेजिस्टरs which are loaded with iph and ihl
	   are modअगरied, we must also specअगरy them as outमाला_दो, or gcc
	   will assume they contain their original values. */
		: "=r" (sum), "=r" (iph), "=r" (ihl), "=&r" (पंचांगp),
		  "=&r" (endaddr)
		: "1" (iph), "2" (ihl)
		: "memory");

	वापस	csum_fold(sum);
पूर्ण

अटल __अंतरभूत__ __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
					    __u32 len, __u8 proto,
					    __wsum sum)
अणु

#अगर_घोषित __XTENSA_EL__
	अचिन्हित दीर्घ len_proto = (len + proto) << 8;
#या_अगर defined(__XTENSA_EB__)
	अचिन्हित दीर्घ len_proto = len + proto;
#अन्यथा
# error processor byte order undefined!
#पूर्ण_अगर
	__यंत्र__("add	%0, %0, %1\n\t"
		"bgeu	%0, %1, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"add	%0, %0, %2\n\t"
		"bgeu	%0, %2, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"add	%0, %0, %3\n\t"
		"bgeu	%0, %3, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		: "=r" (sum), "=r" (len_proto)
		: "r" (daddr), "r" (saddr), "1" (len_proto), "0" (sum));
	वापस sum;
पूर्ण

/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented
 */
अटल __अंतरभूत__ __sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr,
					    __u32 len, __u8 proto,
					    __wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr,daddr,len,proto,sum));
पूर्ण

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */

अटल __अंतरभूत__ __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस csum_fold (csum_partial(buff, len, 0));
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM
अटल __अंतरभूत__ __sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
					  स्थिर काष्ठा in6_addr *daddr,
					  __u32 len, __u8 proto,
					  __wsum sum)
अणु
	अचिन्हित पूर्णांक __dummy;
	__यंत्र__("l32i	%1, %2, 0\n\t"
		"add	%0, %0, %1\n\t"
		"bgeu	%0, %1, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"l32i	%1, %2, 4\n\t"
		"add	%0, %0, %1\n\t"
		"bgeu	%0, %1, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"l32i	%1, %2, 8\n\t"
		"add	%0, %0, %1\n\t"
		"bgeu	%0, %1, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"l32i	%1, %2, 12\n\t"
		"add	%0, %0, %1\n\t"
		"bgeu	%0, %1, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"l32i	%1, %3, 0\n\t"
		"add	%0, %0, %1\n\t"
		"bgeu	%0, %1, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"l32i	%1, %3, 4\n\t"
		"add	%0, %0, %1\n\t"
		"bgeu	%0, %1, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"l32i	%1, %3, 8\n\t"
		"add	%0, %0, %1\n\t"
		"bgeu	%0, %1, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"l32i	%1, %3, 12\n\t"
		"add	%0, %0, %1\n\t"
		"bgeu	%0, %1, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"add	%0, %0, %4\n\t"
		"bgeu	%0, %4, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		"add	%0, %0, %5\n\t"
		"bgeu	%0, %5, 1f\n\t"
		"addi	%0, %0, 1\n\t"
		"1:\t"
		: "=r" (sum), "=&r" (__dummy)
		: "r" (saddr), "r" (daddr),
		  "r" (htonl(len)), "r" (htonl(proto)), "0" (sum)
		: "memory");

	वापस csum_fold(sum);
पूर्ण

/*
 *	Copy and checksum to user
 */
#घोषणा HAVE_CSUM_COPY_USER
अटल __अंतरभूत__ __wsum csum_and_copy_to_user(स्थिर व्योम *src,
					       व्योम __user *dst, पूर्णांक len)
अणु
	अगर (!access_ok(dst, len))
		वापस 0;
	वापस csum_partial_copy_generic(src, (__क्रमce व्योम *)dst, len);
पूर्ण
#पूर्ण_अगर
