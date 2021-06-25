<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_CHECKSUM_H
#घोषणा _ASM_MICROBLAZE_CHECKSUM_H

/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented
 */
#घोषणा csum_tcpudp_nofold	csum_tcpudp_nofold
अटल अंतरभूत __wsum
csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len,
		   __u8 proto, __wsum sum)
अणु
	__यंत्र__("add %0, %0, %1\n\t"
		"addc %0, %0, %2\n\t"
		"addc %0, %0, %3\n\t"
		"addc %0, %0, r0\n\t"
		: "+&d" (sum)
		: "d" (saddr), "d" (daddr),
#अगर_घोषित __MICROBLAZEEL__
	"d" ((len + proto) << 8)
#अन्यथा
	"d" (len + proto)
#पूर्ण_अगर
);
	वापस sum;
पूर्ण

#समावेश <यंत्र-generic/checksum.h>

#पूर्ण_अगर /* _ASM_MICROBLAZE_CHECKSUM_H */
