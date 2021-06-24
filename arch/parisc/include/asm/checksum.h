<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_CHECKSUM_H
#घोषणा _PARISC_CHECKSUM_H

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
बाह्य __wsum csum_partial(स्थिर व्योम *, पूर्णांक, __wsum);

/*
 *	Optimized क्रम IP headers, which always checksum on 4 octet boundaries.
 *
 *	Written by Ranकरोlph Chung <tausq@debian.org>, and then mucked with by
 *	LaMont Jones <lamont@debian.org>
 */
अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	अचिन्हित पूर्णांक sum;
	अचिन्हित दीर्घ t0, t1, t2;

	__यंत्र__ __अस्थिर__ (
"	ldws,ma		4(%1), %0\n"
"	addib,<=	-4, %2, 2f\n"
"\n"
"	ldws		4(%1), %4\n"
"	ldws		8(%1), %5\n"
"	add		%0, %4, %0\n"
"	ldws,ma		12(%1), %3\n"
"	addc		%0, %5, %0\n"
"	addc		%0, %3, %0\n"
"1:	ldws,ma		4(%1), %3\n"
"	addib,<		0, %2, 1b\n"
"	addc		%0, %3, %0\n"
"\n"
"	extru		%0, 31, 16, %4\n"
"	extru		%0, 15, 16, %5\n"
"	addc		%4, %5, %0\n"
"	extru		%0, 15, 16, %5\n"
"	add		%0, %5, %0\n"
"	subi		-1, %0, %0\n"
"2:\n"
	: "=r" (sum), "=r" (iph), "=r" (ihl), "=r" (t0), "=r" (t1), "=r" (t2)
	: "1" (iph), "2" (ihl)
	: "memory");

	वापस (__क्रमce __sum16)sum;
पूर्ण

/*
 *	Fold a partial checksum
 */
अटल अंतरभूत __sum16 csum_fold(__wsum csum)
अणु
	u32 sum = (__क्रमce u32)csum;
	/* add the swapped two 16-bit halves of sum,
	   a possible carry from adding the two 16-bit halves,
	   will carry from the lower half पूर्णांकo the upper half,
	   giving us the correct sum in the upper half. */
	sum += (sum << 16) + (sum >> 16);
	वापस (__क्रमce __sum16)(~sum >> 16);
पूर्ण
 
अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
	__यंत्र__(
	"	add  %1, %0, %0\n"
	"	addc %2, %0, %0\n"
	"	addc %3, %0, %0\n"
	"	addc %%r0, %0, %0\n"
		: "=r" (sum)
		: "r" (daddr), "r"(saddr), "r"(proto+len), "0"(sum));
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

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */
अटल अंतरभूत __sum16 ip_compute_csum(स्थिर व्योम *buf, पूर्णांक len)
अणु
	 वापस csum_fold (csum_partial(buf, len, 0));
पूर्ण


#घोषणा _HAVE_ARCH_IPV6_CSUM
अटल __अंतरभूत__ __sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
					  स्थिर काष्ठा in6_addr *daddr,
					  __u32 len, __u8 proto,
					  __wsum sum)
अणु
	अचिन्हित दीर्घ t0, t1, t2, t3;

	len += proto;	/* add 16-bit proto + len */

	__यंत्र__ __अस्थिर__ (

#अगर BITS_PER_LONG > 32

	/*
	** We can execute two loads and two adds per cycle on PA 8000.
	** But add insn's get serialized रुकोing क्रम the carry bit.
	** Try to keep 4 रेजिस्टरs with "live" values ahead of the ALU.
	*/

"	ldd,ma		8(%1), %4\n"	/* get 1st saddr word */
"	ldd,ma		8(%2), %5\n"	/* get 1st daddr word */
"	add		%4, %0, %0\n"
"	ldd,ma		8(%1), %6\n"	/* 2nd saddr */
"	ldd,ma		8(%2), %7\n"	/* 2nd daddr */
"	add,dc		%5, %0, %0\n"
"	add,dc		%6, %0, %0\n"
"	add,dc		%7, %0, %0\n"
"	add,dc		%3, %0, %0\n"  /* fold in proto+len | carry bit */
"	extrd,u		%0, 31, 32, %4\n"/* copy upper half करोwn */
"	depdi		0, 31, 32, %0\n"/* clear upper half */
"	add		%4, %0, %0\n"	/* fold पूर्णांकo 32-bits */
"	addc		0, %0, %0\n"	/* add carry */

#अन्यथा

	/*
	** For PA 1.x, the insn order करोesn't matter as much.
	** Insn stream is serialized on the carry bit here too.
	** result from the previous operation (eg r0 + x)
	*/
"	ldw,ma		4(%1), %4\n"	/* get 1st saddr word */
"	ldw,ma		4(%2), %5\n"	/* get 1st daddr word */
"	add		%4, %0, %0\n"
"	ldw,ma		4(%1), %6\n"	/* 2nd saddr */
"	addc		%5, %0, %0\n"
"	ldw,ma		4(%2), %7\n"	/* 2nd daddr */
"	addc		%6, %0, %0\n"
"	ldw,ma		4(%1), %4\n"	/* 3rd saddr */
"	addc		%7, %0, %0\n"
"	ldw,ma		4(%2), %5\n"	/* 3rd daddr */
"	addc		%4, %0, %0\n"
"	ldw,ma		4(%1), %6\n"	/* 4th saddr */
"	addc		%5, %0, %0\n"
"	ldw,ma		4(%2), %7\n"	/* 4th daddr */
"	addc		%6, %0, %0\n"
"	addc		%7, %0, %0\n"
"	addc		%3, %0, %0\n"	/* fold in proto+len, catch carry */

#पूर्ण_अगर
	: "=r" (sum), "=r" (saddr), "=r" (daddr), "=r" (len),
	  "=r" (t0), "=r" (t1), "=r" (t2), "=r" (t3)
	: "0" (sum), "1" (saddr), "2" (daddr), "3" (len)
	: "memory");
	वापस csum_fold(sum);
पूर्ण

#पूर्ण_अगर

