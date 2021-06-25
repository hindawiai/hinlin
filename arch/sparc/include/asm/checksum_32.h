<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_CHECKSUM_H
#घोषणा __SPARC_CHECKSUM_H

/*  checksum.h:  IP/UDP/TCP checksum routines on the Sparc.
 *
 *  Copyright(C) 1995 Linus Torvalds
 *  Copyright(C) 1995 Miguel de Icaza
 *  Copyright(C) 1996 David S. Miller
 *  Copyright(C) 1996 Eddie C. Dost
 *  Copyright(C) 1997 Jakub Jelinek
 *
 * derived from:
 *	Alpha checksum c-code
 *      ix86 अंतरभूत assembly
 *      RFC1071 Computing the Internet Checksum
 */

#समावेश <linux/in6.h>
#समावेश <linux/uaccess.h>

/* computes the checksum of a memory block at buff, length len,
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

/* the same as csum_partial, but copies from fs:src जबतक it
 * checksums
 *
 * here even more important to align src and dst on a 32-bit (or even
 * better 64-bit) boundary
 */

अचिन्हित पूर्णांक __csum_partial_copy_sparc_generic (स्थिर अचिन्हित अक्षर *, अचिन्हित अक्षर *);

अटल अंतरभूत __wsum
csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len)
अणु
	रेजिस्टर अचिन्हित पूर्णांक ret यंत्र("o0") = (अचिन्हित पूर्णांक)src;
	रेजिस्टर अक्षर *d यंत्र("o1") = dst;
	रेजिस्टर पूर्णांक l यंत्र("g1") = len;

	__यंत्र__ __अस्थिर__ (
		"call __csum_partial_copy_sparc_generic\n\t"
		" mov -1, %%g7\n"
	: "=&r" (ret), "=&r" (d), "=&r" (l)
	: "0" (ret), "1" (d), "2" (l)
	: "o2", "o3", "o4", "o5", "o7",
	  "g2", "g3", "g4", "g5", "g7",
	  "memory", "cc");
	वापस (__क्रमce __wsum)ret;
पूर्ण

अटल अंतरभूत __wsum
csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len)
अणु
	अगर (unlikely(!access_ok(src, len)))
		वापस 0;
	वापस csum_partial_copy_nocheck((__क्रमce व्योम *)src, dst, len);
पूर्ण

अटल अंतरभूत __wsum
csum_and_copy_to_user(स्थिर व्योम *src, व्योम __user *dst, पूर्णांक len)
अणु
	अगर (!access_ok(dst, len))
		वापस 0;
	वापस csum_partial_copy_nocheck(src, (__क्रमce व्योम *)dst, len);
पूर्ण

/* ihl is always 5 or greater, almost always is 5, and iph is word aligned
 * the majority of the समय.
 */
अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	__sum16 sum;

	/* Note: We must पढ़ो %2 beक्रमe we touch %0 क्रम the first समय,
	 *       because GCC can legitimately use the same रेजिस्टर क्रम
	 *       both opeअक्रमs.
	 */
	__यंत्र__ __अस्थिर__("sub\t%2, 4, %%g4\n\t"
			     "ld\t[%1 + 0x00], %0\n\t"
			     "ld\t[%1 + 0x04], %%g2\n\t"
			     "ld\t[%1 + 0x08], %%g3\n\t"
			     "addcc\t%%g2, %0, %0\n\t"
			     "addxcc\t%%g3, %0, %0\n\t"
			     "ld\t[%1 + 0x0c], %%g2\n\t"
			     "ld\t[%1 + 0x10], %%g3\n\t"
			     "addxcc\t%%g2, %0, %0\n\t"
			     "addx\t%0, %%g0, %0\n"
			     "1:\taddcc\t%%g3, %0, %0\n\t"
			     "add\t%1, 4, %1\n\t"
			     "addxcc\t%0, %%g0, %0\n\t"
			     "subcc\t%%g4, 1, %%g4\n\t"
			     "be,a\t2f\n\t"
			     "sll\t%0, 16, %%g2\n\t"
			     "b\t1b\n\t"
			     "ld\t[%1 + 0x10], %%g3\n"
			     "2:\taddcc\t%0, %%g2, %%g2\n\t"
			     "srl\t%%g2, 16, %0\n\t"
			     "addx\t%0, %%g0, %0\n\t"
			     "xnor\t%%g0, %0, %0"
			     : "=r" (sum), "=&r" (iph)
			     : "r" (ihl), "1" (iph)
			     : "g2", "g3", "g4", "cc", "memory");
	वापस sum;
पूर्ण

/* Fold a partial checksum without adding pseuकरो headers. */
अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	__यंत्र__ __अस्थिर__("addcc\t%0, %1, %1\n\t"
			     "srl\t%1, 16, %1\n\t"
			     "addx\t%1, %%g0, %1\n\t"
			     "xnor\t%%g0, %1, %0"
			     : "=&r" (sum), "=r" (पंचांगp)
			     : "0" (sum), "1" ((__क्रमce u32)sum<<16)
			     : "cc");
	वापस (__क्रमce __sum16)sum;
पूर्ण

अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
	__यंत्र__ __अस्थिर__("addcc\t%1, %0, %0\n\t"
			     "addxcc\t%2, %0, %0\n\t"
			     "addxcc\t%3, %0, %0\n\t"
			     "addx\t%0, %%g0, %0\n\t"
			     : "=r" (sum), "=r" (saddr)
			     : "r" (daddr), "r" (proto + len), "0" (sum),
			       "1" (saddr)
			     : "cc");
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
	वापस csum_fold(csum_tcpudp_nofold(saddr,daddr,len,proto,sum));
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM

अटल अंतरभूत __sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
				      स्थिर काष्ठा in6_addr *daddr,
				      __u32 len, __u8 proto, __wsum sum)
अणु
	__यंत्र__ __अस्थिर__ (
		"addcc	%3, %4, %%g4\n\t"
		"addxcc	%5, %%g4, %%g4\n\t"
		"ld	[%2 + 0x0c], %%g2\n\t"
		"ld	[%2 + 0x08], %%g3\n\t"
		"addxcc	%%g2, %%g4, %%g4\n\t"
		"ld	[%2 + 0x04], %%g2\n\t"
		"addxcc	%%g3, %%g4, %%g4\n\t"
		"ld	[%2 + 0x00], %%g3\n\t"
		"addxcc	%%g2, %%g4, %%g4\n\t"
		"ld	[%1 + 0x0c], %%g2\n\t"
		"addxcc	%%g3, %%g4, %%g4\n\t"
		"ld	[%1 + 0x08], %%g3\n\t"
		"addxcc	%%g2, %%g4, %%g4\n\t"
		"ld	[%1 + 0x04], %%g2\n\t"
		"addxcc	%%g3, %%g4, %%g4\n\t"
		"ld	[%1 + 0x00], %%g3\n\t"
		"addxcc	%%g2, %%g4, %%g4\n\t"
		"addxcc	%%g3, %%g4, %0\n\t"
		"addx	0, %0, %0\n"
		: "=&r" (sum)
		: "r" (saddr), "r" (daddr),
		  "r"(htonl(len)), "r"(htonl(proto)), "r"(sum)
		: "g2", "g3", "g4", "cc");

	वापस csum_fold(sum);
पूर्ण

/* this routine is used क्रम miscellaneous IP-like checksums, मुख्यly in icmp.c */
अटल अंतरभूत __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस csum_fold(csum_partial(buff, len, 0));
पूर्ण

#घोषणा HAVE_ARCH_CSUM_ADD
अटल अंतरभूत __wsum csum_add(__wsum csum, __wsum addend)
अणु
	__यंत्र__ __अस्थिर__(
		"addcc   %0, %1, %0\n"
		"addx    %0, %%g0, %0"
		: "=r" (csum)
		: "r" (addend), "0" (csum));

	वापस csum;
पूर्ण

#पूर्ण_अगर /* !(__SPARC_CHECKSUM_H) */
