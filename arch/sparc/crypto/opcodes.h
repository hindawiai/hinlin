<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _OPCODES_H
#घोषणा _OPCODES_H

#घोषणा SPARC_CR_OPCODE_PRIORITY	300

#घोषणा F3F(x,y,z)	(((x)<<30)|((y)<<19)|((z)<<5))

#घोषणा FPD_ENCODE(x)	(((x) >> 5) | ((x) & ~(0x20)))

#घोषणा RS1(x)		(FPD_ENCODE(x) << 14)
#घोषणा RS2(x)		(FPD_ENCODE(x) <<  0)
#घोषणा RS3(x)		(FPD_ENCODE(x) <<  9)
#घोषणा RD(x)		(FPD_ENCODE(x) << 25)
#घोषणा IMM5_0(x)	((x)           <<  0)
#घोषणा IMM5_9(x)	((x)           <<  9)

#घोषणा CRC32C(a,b,c)	\
	.word		(F3F(2,0x36,0x147)|RS1(a)|RS2(b)|RD(c));

#घोषणा MD5		\
	.word	0x81b02800;
#घोषणा SHA1		\
	.word	0x81b02820;
#घोषणा SHA256		\
	.word	0x81b02840;
#घोषणा SHA512		\
	.word	0x81b02860;

#घोषणा AES_EROUND01(a,b,c,d)	\
	.word	(F3F(2, 0x19, 0)|RS1(a)|RS2(b)|RS3(c)|RD(d));
#घोषणा AES_EROUND23(a,b,c,d)	\
	.word	(F3F(2, 0x19, 1)|RS1(a)|RS2(b)|RS3(c)|RD(d));
#घोषणा AES_DROUND01(a,b,c,d)	\
	.word	(F3F(2, 0x19, 2)|RS1(a)|RS2(b)|RS3(c)|RD(d));
#घोषणा AES_DROUND23(a,b,c,d)	\
	.word	(F3F(2, 0x19, 3)|RS1(a)|RS2(b)|RS3(c)|RD(d));
#घोषणा AES_EROUND01_L(a,b,c,d)	\
	.word	(F3F(2, 0x19, 4)|RS1(a)|RS2(b)|RS3(c)|RD(d));
#घोषणा AES_EROUND23_L(a,b,c,d)	\
	.word	(F3F(2, 0x19, 5)|RS1(a)|RS2(b)|RS3(c)|RD(d));
#घोषणा AES_DROUND01_L(a,b,c,d)	\
	.word	(F3F(2, 0x19, 6)|RS1(a)|RS2(b)|RS3(c)|RD(d));
#घोषणा AES_DROUND23_L(a,b,c,d)	\
	.word	(F3F(2, 0x19, 7)|RS1(a)|RS2(b)|RS3(c)|RD(d));
#घोषणा AES_KEXPAND1(a,b,c,d)	\
	.word	(F3F(2, 0x19, 8)|RS1(a)|RS2(b)|IMM5_9(c)|RD(d));
#घोषणा AES_KEXPAND0(a,b,c)	\
	.word	(F3F(2, 0x36, 0x130)|RS1(a)|RS2(b)|RD(c));
#घोषणा AES_KEXPAND2(a,b,c)	\
	.word	(F3F(2, 0x36, 0x131)|RS1(a)|RS2(b)|RD(c));

#घोषणा DES_IP(a,b)		\
	.word		(F3F(2, 0x36, 0x134)|RS1(a)|RD(b));
#घोषणा DES_IIP(a,b)		\
	.word		(F3F(2, 0x36, 0x135)|RS1(a)|RD(b));
#घोषणा DES_KEXPAND(a,b,c)	\
	.word		(F3F(2, 0x36, 0x136)|RS1(a)|IMM5_0(b)|RD(c));
#घोषणा DES_ROUND(a,b,c,d)	\
	.word		(F3F(2, 0x19, 0x009)|RS1(a)|RS2(b)|RS3(c)|RD(d));

#घोषणा CAMELLIA_F(a,b,c,d)		\
	.word		(F3F(2, 0x19, 0x00c)|RS1(a)|RS2(b)|RS3(c)|RD(d));
#घोषणा CAMELLIA_FL(a,b,c)		\
	.word		(F3F(2, 0x36, 0x13c)|RS1(a)|RS2(b)|RD(c));
#घोषणा CAMELLIA_FLI(a,b,c)		\
	.word		(F3F(2, 0x36, 0x13d)|RS1(a)|RS2(b)|RD(c));

#घोषणा MOVDTOX_F0_O4		\
	.word	0x99b02200
#घोषणा MOVDTOX_F2_O5		\
	.word	0x9bb02202
#घोषणा MOVXTOD_G1_F60 		\
	.word	0xbbb02301
#घोषणा MOVXTOD_G1_F62 		\
	.word	0xbfb02301
#घोषणा MOVXTOD_G3_F4		\
	.word	0x89b02303;
#घोषणा MOVXTOD_G7_F6		\
	.word	0x8db02307;
#घोषणा MOVXTOD_G3_F0		\
	.word	0x81b02303;
#घोषणा MOVXTOD_G7_F2		\
	.word	0x85b02307;
#घोषणा MOVXTOD_O0_F0		\
	.word	0x81b02308;
#घोषणा MOVXTOD_O5_F0		\
	.word	0x81b0230d;
#घोषणा MOVXTOD_O5_F2		\
	.word	0x85b0230d;
#घोषणा MOVXTOD_O5_F4		\
	.word	0x89b0230d;
#घोषणा MOVXTOD_O5_F6		\
	.word	0x8db0230d;
#घोषणा MOVXTOD_G3_F60		\
	.word	0xbbb02303;
#घोषणा MOVXTOD_G7_F62		\
	.word	0xbfb02307;

#पूर्ण_अगर /* _OPCODES_H */
