<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Joern Rennecke  <joern.rennecke@embecosm.com>: Jan 2012
 *  -Insn Scheduling improvements to csum core routines.
 *      = csum_fold( ) largely derived from ARM version.
 *      = ip_fast_cum( ) to have module scheduling
 *  -gcc 4.4.x broke networking. Alias analysis needed to be primed.
 *   worked around by adding memory clobber to ip_fast_csum( )
 *
 * vineetg: May 2010
 *  -Rewrote ip_fast_cscum( ) and csum_fold( ) with fast अंतरभूत यंत्र
 */

#अगर_अघोषित _ASM_ARC_CHECKSUM_H
#घोषणा _ASM_ARC_CHECKSUM_H

/*
 *	Fold a partial checksum
 *
 *  The 2 swords comprising the 32bit sum are added, any carry to 16th bit
 *  added back and final sword result inverted.
 */
अटल अंतरभूत __sum16 csum_fold(__wsum s)
अणु
	अचिन्हित r = s << 16 | s >> 16;	/* ror */
	s = ~s;
	s -= r;
	वापस s >> 16;
पूर्ण

/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 */
अटल अंतरभूत __sum16
ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	स्थिर व्योम *ptr = iph;
	अचिन्हित पूर्णांक पंचांगp, पंचांगp2, sum;

	__यंत्र__(
	"	ld.ab  %0, [%3, 4]		\n"
	"	ld.ab  %2, [%3, 4]		\n"
	"	sub    %1, %4, 2		\n"
	"	lsr.f  lp_count, %1, 1		\n"
	"	bcc    0f			\n"
	"	add.f  %0, %0, %2		\n"
	"	ld.ab  %2, [%3, 4]		\n"
	"0:	lp     1f			\n"
	"	ld.ab  %1, [%3, 4]		\n"
	"	adc.f  %0, %0, %2		\n"
	"	ld.ab  %2, [%3, 4]		\n"
	"	adc.f  %0, %0, %1		\n"
	"1:	adc.f  %0, %0, %2		\n"
	"	add.cs %0,%0,1			\n"
	: "=&r"(sum), "=r"(पंचांगp), "=&r"(पंचांगp2), "+&r" (ptr)
	: "r"(ihl)
	: "cc", "lp_count", "memory");

	वापस csum_fold(sum);
पूर्ण

/*
 * TCP pseuकरो Header is 12 bytes:
 * SA [4], DA [4], zeroes [1], Proto[1], TCP Seg(hdr+data) Len [2]
 */
अटल अंतरभूत __wsum
csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len,
		   __u8 proto, __wsum sum)
अणु
	__यंत्र__ __अस्थिर__(
	"	add.f %0, %0, %1	\n"
	"	adc.f %0, %0, %2	\n"
	"	adc.f %0, %0, %3	\n"
	"	adc.f %0, %0, %4	\n"
	"	adc   %0, %0, 0		\n"
	: "+&r"(sum)
	: "r"(saddr), "r"(daddr),
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	  "r"(len),
#अन्यथा
	  "r"(len << 8),
#पूर्ण_अगर
	  "r"(htons(proto))
	: "cc");

	वापस sum;
पूर्ण

#घोषणा csum_fold csum_fold
#घोषणा ip_fast_csum ip_fast_csum
#घोषणा csum_tcpudp_nofold csum_tcpudp_nofold

#समावेश <यंत्र-generic/checksum.h>

#पूर्ण_अगर /* _ASM_ARC_CHECKSUM_H */
