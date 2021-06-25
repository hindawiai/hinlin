<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CHECKSUM_64_H
#घोषणा _ASM_X86_CHECKSUM_64_H

/*
 * Checksums क्रम x86-64
 * Copyright 2002 by Andi Kleen, SuSE Lअसल
 * with some code from यंत्र-x86/checksum.h
 */

#समावेश <linux/compiler.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>

/**
 * csum_fold - Fold and invert a 32bit checksum.
 * sum: 32bit unfolded sum
 *
 * Fold a 32bit running checksum to 16bit and invert it. This is usually
 * the last step beक्रमe putting a checksum पूर्णांकo a packet.
 * Make sure not to mix with 64bit checksums.
 */
अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	यंत्र("  addl %1,%0\n"
	    "  adcl $0xffff,%0"
	    : "=r" (sum)
	    : "r" ((__क्रमce u32)sum << 16),
	      "0" ((__क्रमce u32)sum & 0xffff0000));
	वापस (__क्रमce __sum16)(~(__क्रमce u32)sum >> 16);
पूर्ण

/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 *
 *	By Jorge Cwik <jorge@laser.satlink.net>, adapted क्रम linux by
 *	Arnt Gulbअक्रमsen.
 */

/**
 * ip_fast_csum - Compute the IPv4 header checksum efficiently.
 * iph: ipv4 header
 * ihl: length of header / 4
 */
अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	अचिन्हित पूर्णांक sum;

	यंत्र("  movl (%1), %0\n"
	    "  subl $4, %2\n"
	    "  jbe 2f\n"
	    "  addl 4(%1), %0\n"
	    "  adcl 8(%1), %0\n"
	    "  adcl 12(%1), %0\n"
	    "1: adcl 16(%1), %0\n"
	    "  lea 4(%1), %1\n"
	    "  decl %2\n"
	    "  jne	1b\n"
	    "  adcl $0, %0\n"
	    "  movl %0, %2\n"
	    "  shrl $16, %0\n"
	    "  addw %w2, %w0\n"
	    "  adcl $0, %0\n"
	    "  notl %0\n"
	    "2:"
	/* Since the input रेजिस्टरs which are loaded with iph and ihl
	   are modअगरied, we must also specअगरy them as outमाला_दो, or gcc
	   will assume they contain their original values. */
	    : "=r" (sum), "=r" (iph), "=r" (ihl)
	    : "1" (iph), "2" (ihl)
	    : "memory");
	वापस (__क्रमce __sum16)sum;
पूर्ण

/**
 * csum_tcpup_nofold - Compute an IPv4 pseuकरो header checksum.
 * @saddr: source address
 * @daddr: destination address
 * @len: length of packet
 * @proto: ip protocol of packet
 * @sum: initial sum to be added in (32bit unfolded)
 *
 * Returns the pseuकरो header checksum the input data. Result is
 * 32bit unfolded.
 */
अटल अंतरभूत __wsum
csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len,
		   __u8 proto, __wsum sum)
अणु
	यंत्र("  addl %1, %0\n"
	    "  adcl %2, %0\n"
	    "  adcl %3, %0\n"
	    "  adcl $0, %0\n"
	    : "=r" (sum)
	    : "g" (daddr), "g" (saddr),
	      "g" ((len + proto)<<8), "0" (sum));
	वापस sum;
पूर्ण


/**
 * csum_tcpup_magic - Compute an IPv4 pseuकरो header checksum.
 * @saddr: source address
 * @daddr: destination address
 * @len: length of packet
 * @proto: ip protocol of packet
 * @sum: initial sum to be added in (32bit unfolded)
 *
 * Returns the 16bit pseuकरो header checksum the input data alपढ़ोy
 * complemented and पढ़ोy to be filled in.
 */
अटल अंतरभूत __sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
पूर्ण

/**
 * csum_partial - Compute an पूर्णांकernet checksum.
 * @buff: buffer to be checksummed
 * @len: length of buffer.
 * @sum: initial sum to be added in (32bit unfolded)
 *
 * Returns the 32bit unfolded पूर्णांकernet checksum of the buffer.
 * Beक्रमe filling it in it needs to be csum_fold()'ed.
 * buff should be aligned to a 64bit boundary अगर possible.
 */
बाह्य __wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum);

/* Do not call this directly. Use the wrappers below */
बाह्य __visible __wsum csum_partial_copy_generic(स्थिर व्योम *src, व्योम *dst, पूर्णांक len);

बाह्य __wsum csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len);
बाह्य __wsum csum_and_copy_to_user(स्थिर व्योम *src, व्योम __user *dst, पूर्णांक len);
बाह्य __wsum csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len);

/**
 * ip_compute_csum - Compute an 16bit IP checksum.
 * @buff: buffer address.
 * @len: length of buffer.
 *
 * Returns the 16bit folded/inverted checksum of the passed buffer.
 * Ready to fill in.
 */
बाह्य __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len);

/**
 * csum_ipv6_magic - Compute checksum of an IPv6 pseuकरो header.
 * @saddr: source address
 * @daddr: destination address
 * @len: length of packet
 * @proto: protocol of packet
 * @sum: initial sum (32bit unfolded) to be added in
 *
 * Computes an IPv6 pseuकरो header checksum. This sum is added the checksum
 * पूर्णांकo UDP/TCP packets and contains some link layer inक्रमmation.
 * Returns the unfolded 32bit checksum.
 */

काष्ठा in6_addr;

#घोषणा _HAVE_ARCH_IPV6_CSUM 1
बाह्य __sum16
csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr, स्थिर काष्ठा in6_addr *daddr,
		__u32 len, __u8 proto, __wsum sum);

अटल अंतरभूत अचिन्हित add32_with_carry(अचिन्हित a, अचिन्हित b)
अणु
	यंत्र("addl %2,%0\n\t"
	    "adcl $0,%0"
	    : "=r" (a)
	    : "0" (a), "rm" (b));
	वापस a;
पूर्ण

#घोषणा HAVE_ARCH_CSUM_ADD
अटल अंतरभूत __wsum csum_add(__wsum csum, __wsum addend)
अणु
	वापस (__क्रमce __wsum)add32_with_carry((__क्रमce अचिन्हित)csum,
						(__क्रमce अचिन्हित)addend);
पूर्ण

#पूर्ण_अगर /* _ASM_X86_CHECKSUM_64_H */
