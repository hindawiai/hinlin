<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_CHECKSUM_H
#घोषणा __UM_CHECKSUM_H

#समावेश <linux/माला.स>
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
बाह्य __wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum);

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
	__यंत्र__(
		"  addl %1,%0\n"
		"  adcl $0xffff,%0"
		: "=r" (sum)
		: "r" ((__क्रमce u32)sum << 16),
		  "0" ((__क्रमce u32)sum & 0xffff0000)
	);
	वापस (__क्रमce __sum16)(~(__क्रमce u32)sum >> 16);
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
	    : "g" (daddr), "g" (saddr), "g" ((len + proto) << 8), "0" (sum));
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

/**
 * ip_fast_csum - Compute the IPv4 header checksum efficiently.
 * iph: ipv4 header
 * ihl: length of header / 4
 */
अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	अचिन्हित पूर्णांक sum;

	यंत्र(	"  movl (%1), %0\n"
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
	/* Since the input रेजिस्टरs which are loaded with iph and ipl
	   are modअगरied, we must also specअगरy them as outमाला_दो, or gcc
	   will assume they contain their original values. */
	: "=r" (sum), "=r" (iph), "=r" (ihl)
	: "1" (iph), "2" (ihl)
	: "memory");
	वापस (__क्रमce __sum16)sum;
पूर्ण

#अगर_घोषित CONFIG_X86_32
# include "checksum_32.h"
#अन्यथा
# include "checksum_64.h"
#पूर्ण_अगर

#पूर्ण_अगर
