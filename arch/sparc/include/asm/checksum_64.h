<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC64_CHECKSUM_H
#घोषणा __SPARC64_CHECKSUM_H

/*  checksum.h:  IP/UDP/TCP checksum routines on the V9.
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
__wsum csum_partial(स्थिर व्योम * buff, पूर्णांक len, __wsum sum);

/* the same as csum_partial, but copies from user space जबतक it
 * checksums
 *
 * here even more important to align src and dst on a 32-bit (or even
 * better 64-bit) boundary
 */
__wsum csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len);
__wsum csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len);
__wsum csum_and_copy_to_user(स्थिर व्योम *src, व्योम __user *dst, पूर्णांक len);

/* ihl is always 5 or greater, almost always is 5, and iph is word aligned
 * the majority of the समय.
 */
__sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl);

/* Fold a partial checksum without adding pseuकरो headers. */
अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	__यंत्र__ __अस्थिर__(
"	addcc		%0, %1, %1\n"
"	srl		%1, 16, %1\n"
"	addc		%1, %%g0, %1\n"
"	xnor		%%g0, %1, %0\n"
	: "=&r" (sum), "=r" (पंचांगp)
	: "0" (sum), "1" ((__क्रमce u32)sum<<16)
	: "cc");
	वापस (__क्रमce __sum16)sum;
पूर्ण

अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
	__यंत्र__ __अस्थिर__(
"	addcc		%1, %0, %0\n"
"	addccc		%2, %0, %0\n"
"	addccc		%3, %0, %0\n"
"	addc		%0, %%g0, %0\n"
	: "=r" (sum), "=r" (saddr)
	: "r" (daddr), "r" (proto + len), "0" (sum), "1" (saddr)
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
"	addcc		%3, %4, %%g7\n"
"	addccc		%5, %%g7, %%g7\n"
"	lduw		[%2 + 0x0c], %%g2\n"
"	lduw		[%2 + 0x08], %%g3\n"
"	addccc		%%g2, %%g7, %%g7\n"
"	lduw		[%2 + 0x04], %%g2\n"
"	addccc		%%g3, %%g7, %%g7\n"
"	lduw		[%2 + 0x00], %%g3\n"
"	addccc		%%g2, %%g7, %%g7\n"
"	lduw		[%1 + 0x0c], %%g2\n"
"	addccc		%%g3, %%g7, %%g7\n"
"	lduw		[%1 + 0x08], %%g3\n"
"	addccc		%%g2, %%g7, %%g7\n"
"	lduw		[%1 + 0x04], %%g2\n"
"	addccc		%%g3, %%g7, %%g7\n"
"	lduw		[%1 + 0x00], %%g3\n"
"	addccc		%%g2, %%g7, %%g7\n"
"	addccc		%%g3, %%g7, %0\n"
"	addc		0, %0, %0\n"
	: "=&r" (sum)
	: "r" (saddr), "r" (daddr), "r"(htonl(len)),
	  "r"(htonl(proto)), "r"(sum)
	: "g2", "g3", "g7", "cc");

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

#पूर्ण_अगर /* !(__SPARC64_CHECKSUM_H) */
