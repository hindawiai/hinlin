<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_CHECKSUM_H
#घोषणा __ASM_CSKY_CHECKSUM_H

#समावेश <linux/in6.h>
#समावेश <यंत्र/byteorder.h>

अटल अंतरभूत __sum16 csum_fold(__wsum csum)
अणु
	u32 पंचांगp;

	यंत्र अस्थिर(
	"mov	%1, %0\n"
	"rori	%0, 16\n"
	"addu	%0, %1\n"
	"lsri	%0, 16\n"
	: "=r"(csum), "=r"(पंचांगp)
	: "0"(csum));

	वापस (__क्रमce __sum16) ~csum;
पूर्ण
#घोषणा csum_fold csum_fold

अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
		अचिन्हित लघु len, अचिन्हित लघु proto, __wsum sum)
अणु
	यंत्र अस्थिर(
	"clrc\n"
	"addc    %0, %1\n"
	"addc    %0, %2\n"
	"addc    %0, %3\n"
	"inct    %0\n"
	: "=r"(sum)
	: "r"((__क्रमce u32)saddr), "r"((__क्रमce u32)daddr),
#अगर_घोषित __BIG_ENDIAN
	"r"(proto + len),
#अन्यथा
	"r"((proto + len) << 8),
#पूर्ण_अगर
	"0" ((__क्रमce अचिन्हित दीर्घ)sum)
	: "cc");
	वापस sum;
पूर्ण
#घोषणा csum_tcpudp_nofold csum_tcpudp_nofold

#समावेश <यंत्र-generic/checksum.h>

#पूर्ण_अगर /* __ASM_CSKY_CHECKSUM_H */
