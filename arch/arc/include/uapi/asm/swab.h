<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * vineetg: May 2011
 *  -Support single cycle endian-swap insn in ARC700 4.10
 *
 * vineetg: June 2009
 *  -Better htonl implementation (5 instead of 9 ALU inकाष्ठाions)
 *  -Hardware assisted single cycle bswap (Use Case of ARC custom instrn)
 */

#अगर_अघोषित __ASM_ARC_SWAB_H
#घोषणा __ASM_ARC_SWAB_H

#समावेश <linux/types.h>

/* Native single cycle endian swap insn */
#अगर_घोषित CONFIG_ARC_HAS_SWAPE

#घोषणा __arch_swab32(x)		\
(अणु					\
	अचिन्हित पूर्णांक पंचांगp = x;		\
	__यंत्र__(			\
	"	swape	%0, %1	\n"	\
	: "=r" (पंचांगp)			\
	: "r" (पंचांगp));			\
	पंचांगp;				\
पूर्ण)

#अन्यथा

/* Several ways of Endian-Swap Emulation क्रम ARC
 * 0: kernel generic
 * 1: ARC optimised "C"
 * 2: ARC Custom inकाष्ठाion
 */
#घोषणा ARC_BSWAP_TYPE	1

#अगर (ARC_BSWAP_TYPE == 1)		/******* Software only ********/

/* The kernel शेष implementation of htonl is
 *		वापस  x<<24 | x>>24 |
 *		 (x & (__u32)0x0000ff00UL)<<8 | (x & (__u32)0x00ff0000UL)>>8;
 *
 * This generates 9 inकाष्ठाions on ARC (excluding the ld/st)
 *
 * 8051fd8c:	ld     r3,[r7,20]	; Mem op : Get the value to be swapped
 * 8051fd98:	asl    r5,r3,24		; get  3rd Byte
 * 8051fd9c:	lsr    r2,r3,24		; get  0th Byte
 * 8051fda0:	and    r4,r3,0xff00
 * 8051fda8:	asl    r4,r4,8		; get 1st Byte
 * 8051fdac:	and    r3,r3,0x00ff0000
 * 8051fdb4:	or     r2,r2,r5		; combine 0th and 3rd Bytes
 * 8051fdb8:	lsr    r3,r3,8		; 2nd Byte at correct place in Dst Reg
 * 8051fdbc:	or     r2,r2,r4		; combine 0,3 Bytes with 1st Byte
 * 8051fdc0:	or     r2,r2,r3		; combine 0,3,1 Bytes with 2nd Byte
 * 8051fdc4:	st     r2,[r1,20]	; Mem op : save result back to mem
 *
 * Joern suggested a better "C" algorithm which is great since
 * (1) It is portable to any architecure
 * (2) At the same समय it takes advantage of ARC ISA (rotate पूर्णांकrns)
 */

#घोषणा __arch_swab32(x)					\
(अणु	अचिन्हित दीर्घ __in = (x), __पंचांगp;			\
	__पंचांगp = __in << 8 | __in >> 24; /* ror पंचांगp,in,24 */	\
	__in = __in << 24 | __in >> 8; /* ror in,in,8 */	\
	__पंचांगp ^= __in;						\
	__पंचांगp &= 0xff00ff;					\
	__पंचांगp ^ __in;						\
पूर्ण)

#या_अगर (ARC_BSWAP_TYPE == 2)	/* Custom single cycle bswap inकाष्ठाion */

#घोषणा __arch_swab32(x)						\
(अणु									\
	अचिन्हित पूर्णांक पंचांगp = x;						\
	__यंत्र__(							\
	"	.extInstruction	bswap, 7, 0x00, SUFFIX_NONE, SYNTAX_2OP	\n"\
	"	bswap  %0, %1						\n"\
	: "=r" (पंचांगp)							\
	: "r" (पंचांगp));							\
	पंचांगp;								\
पूर्ण)

#पूर्ण_अगर /* ARC_BSWAP_TYPE=zzz */

#पूर्ण_अगर /* CONFIG_ARC_HAS_SWAPE */

#अगर !defined(__STRICT_ANSI__) || defined(__KERNEL__)
#घोषणा __SWAB_64_THRU_32__
#पूर्ण_अगर

#पूर्ण_अगर
