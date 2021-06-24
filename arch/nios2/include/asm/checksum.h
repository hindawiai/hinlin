<शैली गुरु>
/*
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS_CHECKSUM_H
#घोषणा _ASM_NIOS_CHECKSUM_H

/* Take these from lib/checksum.c */
बाह्य __wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum);
बाह्य __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl);
बाह्य __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len);

/*
 * Fold a partial checksum
 */
अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	__यंत्र__ __अस्थिर__(
		"add	%0, %1, %0\n"
		"cmpltu	r8, %0, %1\n"
		"srli	%0, %0, 16\n"
		"add	%0, %0, r8\n"
		"nor	%0, %0, %0\n"
		: "=r" (sum)
		: "r" (sum << 16), "0" (sum)
		: "r8");
	वापस (__क्रमce __sum16) sum;
पूर्ण

/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented
 */
#घोषणा csum_tcpudp_nofold csum_tcpudp_nofold
अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
	__यंत्र__ __अस्थिर__(
		"add	%0, %1, %0\n"
		"cmpltu	r8, %0, %1\n"
		"add	%0, %0, r8\n"	/* add carry */
		"add	%0, %2, %0\n"
		"cmpltu	r8, %0, %2\n"
		"add	%0, %0, r8\n"	/* add carry */
		"add	%0, %3, %0\n"
		"cmpltu	r8, %0, %3\n"
		"add	%0, %0, r8\n"	/* add carry */
		: "=r" (sum), "=r" (saddr)
		: "r" (daddr), "r" ((len + proto) << 8),
		  "0" (sum),
		  "1" (saddr)
		: "r8");

	वापस sum;
पूर्ण

अटल अंतरभूत __sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr,
					__u32 len, __u8 proto,
					__wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
पूर्ण

#पूर्ण_अगर /* _ASM_NIOS_CHECKSUM_H */
