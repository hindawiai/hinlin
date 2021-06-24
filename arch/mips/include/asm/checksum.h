<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 96, 97, 98, 99, 2001 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Copyright (C) 2001 Thiemo Seufer.
 * Copyright (C) 2002 Maciej W. Rozycki
 * Copyright (C) 2014 Imagination Technologies Ltd.
 */
#अगर_अघोषित _ASM_CHECKSUM_H
#घोषणा _ASM_CHECKSUM_H

#अगर_घोषित CONFIG_GENERIC_CSUM
#समावेश <यंत्र-generic/checksum.h>
#अन्यथा

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
__wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum);

__wsum __csum_partial_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len);
__wsum __csum_partial_copy_to_user(स्थिर व्योम *src, व्योम __user *dst, पूर्णांक len);

#घोषणा _HAVE_ARCH_COPY_AND_CSUM_FROM_USER
अटल अंतरभूत
__wsum csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len)
अणु
	might_fault();
	अगर (!access_ok(src, len))
		वापस 0;
	वापस __csum_partial_copy_from_user(src, dst, len);
पूर्ण

/*
 * Copy and checksum to user
 */
#घोषणा HAVE_CSUM_COPY_USER
अटल अंतरभूत
__wsum csum_and_copy_to_user(स्थिर व्योम *src, व्योम __user *dst, पूर्णांक len)
अणु
	might_fault();
	अगर (!access_ok(dst, len))
		वापस 0;
	वापस __csum_partial_copy_to_user(src, dst, len);
पूर्ण

/*
 * the same as csum_partial, but copies from user space (but on MIPS
 * we have just one address space, so this is identical to the above)
 */
#घोषणा _HAVE_ARCH_CSUM_AND_COPY
__wsum __csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len);
अटल अंतरभूत __wsum csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len)
अणु
	वापस __csum_partial_copy_nocheck(src, dst, len);
पूर्ण

/*
 *	Fold a partial checksum without adding pseuकरो headers
 */
अटल अंतरभूत __sum16 csum_fold(__wsum csum)
अणु
	u32 sum = (__क्रमce u32)csum;

	sum += (sum << 16);
	csum = (__क्रमce __wsum)(sum < (__क्रमce u32)csum);
	sum >>= 16;
	sum += (__क्रमce u32)csum;

	वापस (__क्रमce __sum16)~sum;
पूर्ण
#घोषणा csum_fold csum_fold

/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 *
 *	By Jorge Cwik <jorge@laser.satlink.net>, adapted क्रम linux by
 *	Arnt Gulbअक्रमsen.
 */
अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	स्थिर अचिन्हित पूर्णांक *word = iph;
	स्थिर अचिन्हित पूर्णांक *stop = word + ihl;
	अचिन्हित पूर्णांक csum;
	पूर्णांक carry;

	csum = word[0];
	csum += word[1];
	carry = (csum < word[1]);
	csum += carry;

	csum += word[2];
	carry = (csum < word[2]);
	csum += carry;

	csum += word[3];
	carry = (csum < word[3]);
	csum += carry;

	word += 4;
	करो अणु
		csum += *word;
		carry = (csum < *word);
		csum += carry;
		word++;
	पूर्ण जबतक (word != stop);

	वापस csum_fold(csum);
पूर्ण
#घोषणा ip_fast_csum ip_fast_csum

अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
	अचिन्हित दीर्घ पंचांगp = (__क्रमce अचिन्हित दीर्घ)sum;

	__यंत्र__(
	"	.set	push		# csum_tcpudp_nofold\n"
	"	.set	noat		\n"
#अगर_घोषित CONFIG_32BIT
	"	addu	%0, %2		\n"
	"	sltu	$1, %0, %2	\n"
	"	addu	%0, $1		\n"

	"	addu	%0, %3		\n"
	"	sltu	$1, %0, %3	\n"
	"	addu	%0, $1		\n"

	"	addu	%0, %4		\n"
	"	sltu	$1, %0, %4	\n"
	"	addu	%0, $1		\n"
#पूर्ण_अगर
#अगर_घोषित CONFIG_64BIT
	"	daddu	%0, %2		\n"
	"	daddu	%0, %3		\n"
	"	daddu	%0, %4		\n"
	"	dsll32	$1, %0, 0	\n"
	"	daddu	%0, $1		\n"
	"	sltu	$1, %0, $1	\n"
	"	dsra32	%0, %0, 0	\n"
	"	addu	%0, $1		\n"
#पूर्ण_अगर
	"	.set	pop"
	: "=r" (पंचांगp)
	: "0" ((__क्रमce अचिन्हित दीर्घ)daddr),
	  "r" ((__क्रमce अचिन्हित दीर्घ)saddr),
#अगर_घोषित __MIPSEL__
	  "r" ((proto + len) << 8),
#अन्यथा
	  "r" (proto + len),
#पूर्ण_अगर
	  "r" ((__क्रमce अचिन्हित दीर्घ)sum));

	वापस (__क्रमce __wsum)पंचांगp;
पूर्ण
#घोषणा csum_tcpudp_nofold csum_tcpudp_nofold

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */
अटल अंतरभूत __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस csum_fold(csum_partial(buff, len, 0));
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM
अटल __अंतरभूत__ __sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
					  स्थिर काष्ठा in6_addr *daddr,
					  __u32 len, __u8 proto,
					  __wsum sum)
अणु
	__wsum पंचांगp;

	__यंत्र__(
	"	.set	push		# csum_ipv6_magic\n"
	"	.set	noreorder	\n"
	"	.set	noat		\n"
	"	addu	%0, %5		# proto (long in network byte order)\n"
	"	sltu	$1, %0, %5	\n"
	"	addu	%0, $1		\n"

	"	addu	%0, %6		# csum\n"
	"	sltu	$1, %0, %6	\n"
	"	lw	%1, 0(%2)	# four words source address\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	sltu	$1, %0, %1	\n"

	"	lw	%1, 4(%2)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	sltu	$1, %0, %1	\n"

	"	lw	%1, 8(%2)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	sltu	$1, %0, %1	\n"

	"	lw	%1, 12(%2)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	sltu	$1, %0, %1	\n"

	"	lw	%1, 0(%3)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	sltu	$1, %0, %1	\n"

	"	lw	%1, 4(%3)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	sltu	$1, %0, %1	\n"

	"	lw	%1, 8(%3)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	sltu	$1, %0, %1	\n"

	"	lw	%1, 12(%3)	\n"
	"	addu	%0, $1		\n"
	"	addu	%0, %1		\n"
	"	sltu	$1, %0, %1	\n"

	"	addu	%0, $1		# Add final carry\n"
	"	.set	pop"
	: "=&r" (sum), "=&r" (पंचांगp)
	: "r" (saddr), "r" (daddr),
	  "0" (htonl(len)), "r" (htonl(proto)), "r" (sum));

	वापस csum_fold(sum);
पूर्ण

#समावेश <यंत्र-generic/checksum.h>
#पूर्ण_अगर /* CONFIG_GENERIC_CSUM */

#पूर्ण_अगर /* _ASM_CHECKSUM_H */
