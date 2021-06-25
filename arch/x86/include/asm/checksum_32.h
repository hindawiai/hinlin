<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CHECKSUM_32_H
#घोषणा _ASM_X86_CHECKSUM_32_H

#समावेश <linux/in6.h>
#समावेश <linux/uaccess.h>

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

/*
 *	Note: when you get a शून्य poपूर्णांकer exception here this means someone
 *	passed in an incorrect kernel address to one of these functions.
 *
 *	If you use these functions directly please करोn't क्रमget the
 *	access_ok().
 */
अटल अंतरभूत __wsum csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len)
अणु
	वापस csum_partial_copy_generic(src, dst, len);
पूर्ण

अटल अंतरभूत __wsum csum_and_copy_from_user(स्थिर व्योम __user *src,
					     व्योम *dst, पूर्णांक len)
अणु
	__wsum ret;

	might_sleep();
	अगर (!user_access_begin(src, len))
		वापस 0;
	ret = csum_partial_copy_generic((__क्रमce व्योम *)src, dst, len);
	user_access_end();

	वापस ret;
पूर्ण

/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 *
 *	By Jorge Cwik <jorge@laser.satlink.net>, adapted क्रम linux by
 *	Arnt Gulbअक्रमsen.
 */
अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	अचिन्हित पूर्णांक sum;

	यंत्र अस्थिर("movl (%1), %0	;\n"
		     "subl $4, %2	;\n"
		     "jbe 2f		;\n"
		     "addl 4(%1), %0	;\n"
		     "adcl 8(%1), %0	;\n"
		     "adcl 12(%1), %0;\n"
		     "1:	adcl 16(%1), %0	;\n"
		     "lea 4(%1), %1	;\n"
		     "decl %2	;\n"
		     "jne 1b		;\n"
		     "adcl $0, %0	;\n"
		     "movl %0, %2	;\n"
		     "shrl $16, %0	;\n"
		     "addw %w2, %w0	;\n"
		     "adcl $0, %0	;\n"
		     "notl %0	;\n"
		     "2:		;\n"
	/* Since the input रेजिस्टरs which are loaded with iph and ihl
	   are modअगरied, we must also specअगरy them as outमाला_दो, or gcc
	   will assume they contain their original values. */
		     : "=r" (sum), "=r" (iph), "=r" (ihl)
		     : "1" (iph), "2" (ihl)
		     : "memory");
	वापस (__क्रमce __sum16)sum;
पूर्ण

/*
 *	Fold a partial checksum
 */

अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	यंत्र("addl %1, %0		;\n"
	    "adcl $0xffff, %0	;\n"
	    : "=r" (sum)
	    : "r" ((__क्रमce u32)sum << 16),
	      "0" ((__क्रमce u32)sum & 0xffff0000));
	वापस (__क्रमce __sum16)(~(__क्रमce u32)sum >> 16);
पूर्ण

अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
	यंत्र("addl %1, %0	;\n"
	    "adcl %2, %0	;\n"
	    "adcl %3, %0	;\n"
	    "adcl $0, %0	;\n"
	    : "=r" (sum)
	    : "g" (daddr), "g"(saddr),
	      "g" ((len + proto) << 8), "0" (sum));
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
	यंत्र("addl 0(%1), %0	;\n"
	    "adcl 4(%1), %0	;\n"
	    "adcl 8(%1), %0	;\n"
	    "adcl 12(%1), %0	;\n"
	    "adcl 0(%2), %0	;\n"
	    "adcl 4(%2), %0	;\n"
	    "adcl 8(%2), %0	;\n"
	    "adcl 12(%2), %0	;\n"
	    "adcl %3, %0	;\n"
	    "adcl %4, %0	;\n"
	    "adcl $0, %0	;\n"
	    : "=&r" (sum)
	    : "r" (saddr), "r" (daddr),
	      "r" (htonl(len)), "r" (htonl(proto)), "0" (sum)
	    : "memory");

	वापस csum_fold(sum);
पूर्ण

/*
 *	Copy and checksum to user
 */
अटल अंतरभूत __wsum csum_and_copy_to_user(स्थिर व्योम *src,
					   व्योम __user *dst,
					   पूर्णांक len)
अणु
	__wsum ret;

	might_sleep();
	अगर (!user_access_begin(dst, len))
		वापस 0;

	ret = csum_partial_copy_generic(src, (__क्रमce व्योम *)dst, len);
	user_access_end();
	वापस ret;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_CHECKSUM_32_H */
