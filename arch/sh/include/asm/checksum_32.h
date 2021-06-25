<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CHECKSUM_H
#घोषणा __ASM_SH_CHECKSUM_H

/*
 * Copyright (C) 1999 by Kaz Kojima & Niibe Yutaka
 */

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
 *
 *	If you use these functions directly please करोn't क्रमget the
 *	access_ok().
 */
अटल अंतरभूत
__wsum csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len)
अणु
	वापस csum_partial_copy_generic(src, dst, len);
पूर्ण

#घोषणा _HAVE_ARCH_COPY_AND_CSUM_FROM_USER
अटल अंतरभूत
__wsum csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len)
अणु
	अगर (!access_ok(src, len))
		वापस 0;
	वापस csum_partial_copy_generic((__क्रमce स्थिर व्योम *)src, dst, len);
पूर्ण

/*
 *	Fold a partial checksum
 */

अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	अचिन्हित पूर्णांक __dummy;
	__यंत्र__("swap.w %0, %1\n\t"
		"extu.w	%0, %0\n\t"
		"extu.w	%1, %1\n\t"
		"add	%1, %0\n\t"
		"swap.w	%0, %1\n\t"
		"add	%1, %0\n\t"
		"not	%0, %0\n\t"
		: "=r" (sum), "=&r" (__dummy)
		: "0" (sum)
		: "t");
	वापस (__क्रमce __sum16)sum;
पूर्ण

/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 *
 *      i386 version by Jorge Cwik <jorge@laser.satlink.net>, adapted
 *      क्रम linux by * Arnt Gulbअक्रमsen.
 */
अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	अचिन्हित पूर्णांक sum, __dummy0, __dummy1;

	__यंत्र__ __अस्थिर__(
		"mov.l	@%1+, %0\n\t"
		"mov.l	@%1+, %3\n\t"
		"add	#-2, %2\n\t"
		"clrt\n\t"
		"1:\t"
		"addc	%3, %0\n\t"
		"movt	%4\n\t"
		"mov.l	@%1+, %3\n\t"
		"dt	%2\n\t"
		"bf/s	1b\n\t"
		" cmp/eq #1, %4\n\t"
		"addc	%3, %0\n\t"
		"addc	%2, %0"	    /* Here %2 is 0, add carry-bit */
	/* Since the input रेजिस्टरs which are loaded with iph and ihl
	   are modअगरied, we must also specअगरy them as outमाला_दो, or gcc
	   will assume they contain their original values. */
	: "=r" (sum), "=r" (iph), "=r" (ihl), "=&r" (__dummy0), "=&z" (__dummy1)
	: "1" (iph), "2" (ihl)
	: "t", "memory");

	वापस	csum_fold(sum);
पूर्ण

अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
#अगर_घोषित __LITTLE_ENDIAN__
	अचिन्हित दीर्घ len_proto = (proto + len) << 8;
#अन्यथा
	अचिन्हित दीर्घ len_proto = proto + len;
#पूर्ण_अगर
	__यंत्र__("clrt\n\t"
		"addc	%0, %1\n\t"
		"addc	%2, %1\n\t"
		"addc	%3, %1\n\t"
		"movt	%0\n\t"
		"add	%1, %0"
		: "=r" (sum), "=r" (len_proto)
		: "r" (daddr), "r" (saddr), "1" (len_proto), "0" (sum)
		: "t");

	वापस sum;
पूर्ण

/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented
 */
अटल अंतरभूत __sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
पूर्ण

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */
अटल अंतरभूत __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
    वापस csum_fold(csum_partial(buff, len, 0));
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM
अटल अंतरभूत __sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
				      स्थिर काष्ठा in6_addr *daddr,
				      __u32 len, __u8 proto, __wsum sum)
अणु
	अचिन्हित पूर्णांक __dummy;
	__यंत्र__("clrt\n\t"
		"mov.l	@(0,%2), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.l	@(4,%2), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.l	@(8,%2), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.l	@(12,%2), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.l	@(0,%3), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.l	@(4,%3), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.l	@(8,%3), %1\n\t"
		"addc	%1, %0\n\t"
		"mov.l	@(12,%3), %1\n\t"
		"addc	%1, %0\n\t"
		"addc	%4, %0\n\t"
		"addc	%5, %0\n\t"
		"movt	%1\n\t"
		"add	%1, %0\n"
		: "=r" (sum), "=&r" (__dummy)
		: "r" (saddr), "r" (daddr),
		  "r" (htonl(len)), "r" (htonl(proto)), "0" (sum)
		: "t");

	वापस csum_fold(sum);
पूर्ण

/*
 *	Copy and checksum to user
 */
#घोषणा HAVE_CSUM_COPY_USER
अटल अंतरभूत __wsum csum_and_copy_to_user(स्थिर व्योम *src,
					   व्योम __user *dst,
					   पूर्णांक len)
अणु
	अगर (!access_ok(dst, len))
		वापस 0;
	वापस csum_partial_copy_generic((__क्रमce स्थिर व्योम *)src, dst, len);
पूर्ण
#पूर्ण_अगर /* __ASM_SH_CHECKSUM_H */
