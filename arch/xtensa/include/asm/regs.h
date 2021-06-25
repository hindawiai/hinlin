<शैली गुरु>
/*
 * Copyright (c) 2006 Tensilica, Inc.  All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2.1 of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Further, this software is distributed without any warranty that it is
 * मुक्त of the rightful claim of any third person regarding infringement
 * or the like.  Any license provided herein, whether implied or
 * otherwise, applies only to this software file.  Patent licenses, अगर
 * any, provided herein करो not apply to combinations of this program with
 * other software, or any other product whatsoever.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License aदीर्घ with this program; अगर not, ग_लिखो the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307,
 * USA.
 */

#अगर_अघोषित _XTENSA_REGS_H
#घोषणा _XTENSA_REGS_H

/*  Special रेजिस्टरs.  */

#घोषणा SREG_MR			32
#घोषणा SREG_IBREAKENABLE	96
#घोषणा SREG_IBREAKA		128
#घोषणा SREG_DBREAKA		144
#घोषणा SREG_DBREAKC		160
#घोषणा SREG_EPC		176
#घोषणा SREG_EPS		192
#घोषणा SREG_EXCSAVE		208
#घोषणा SREG_CCOMPARE		240
#घोषणा SREG_MISC		244

/*  EXCCAUSE रेजिस्टर fields  */

#घोषणा EXCCAUSE_EXCCAUSE_SHIFT	0
#घोषणा EXCCAUSE_EXCCAUSE_MASK	0x3F

#घोषणा EXCCAUSE_ILLEGAL_INSTRUCTION		0
#घोषणा EXCCAUSE_SYSTEM_CALL			1
#घोषणा EXCCAUSE_INSTRUCTION_FETCH_ERROR	2
#घोषणा EXCCAUSE_LOAD_STORE_ERROR		3
#घोषणा EXCCAUSE_LEVEL1_INTERRUPT		4
#घोषणा EXCCAUSE_ALLOCA				5
#घोषणा EXCCAUSE_INTEGER_DIVIDE_BY_ZERO		6
#घोषणा EXCCAUSE_SPECULATION			7
#घोषणा EXCCAUSE_PRIVILEGED			8
#घोषणा EXCCAUSE_UNALIGNED			9
#घोषणा EXCCAUSE_INSTR_DATA_ERROR		12
#घोषणा EXCCAUSE_LOAD_STORE_DATA_ERROR		13
#घोषणा EXCCAUSE_INSTR_ADDR_ERROR		14
#घोषणा EXCCAUSE_LOAD_STORE_ADDR_ERROR		15
#घोषणा EXCCAUSE_ITLB_MISS			16
#घोषणा EXCCAUSE_ITLB_MULTIHIT			17
#घोषणा EXCCAUSE_ITLB_PRIVILEGE			18
#घोषणा EXCCAUSE_ITLB_SIZE_RESTRICTION		19
#घोषणा EXCCAUSE_FETCH_CACHE_ATTRIBUTE		20
#घोषणा EXCCAUSE_DTLB_MISS			24
#घोषणा EXCCAUSE_DTLB_MULTIHIT			25
#घोषणा EXCCAUSE_DTLB_PRIVILEGE			26
#घोषणा EXCCAUSE_DTLB_SIZE_RESTRICTION		27
#घोषणा EXCCAUSE_LOAD_CACHE_ATTRIBUTE		28
#घोषणा EXCCAUSE_STORE_CACHE_ATTRIBUTE		29
#घोषणा EXCCAUSE_COPROCESSOR0_DISABLED		32
#घोषणा EXCCAUSE_COPROCESSOR1_DISABLED		33
#घोषणा EXCCAUSE_COPROCESSOR2_DISABLED		34
#घोषणा EXCCAUSE_COPROCESSOR3_DISABLED		35
#घोषणा EXCCAUSE_COPROCESSOR4_DISABLED		36
#घोषणा EXCCAUSE_COPROCESSOR5_DISABLED		37
#घोषणा EXCCAUSE_COPROCESSOR6_DISABLED		38
#घोषणा EXCCAUSE_COPROCESSOR7_DISABLED		39
#घोषणा EXCCAUSE_N				64

/*  PS रेजिस्टर fields.  */

#घोषणा PS_WOE_BIT		18
#घोषणा PS_WOE_MASK		0x00040000
#घोषणा PS_CALLINC_SHIFT	16
#घोषणा PS_CALLINC_MASK		0x00030000
#घोषणा PS_OWB_SHIFT		8
#घोषणा PS_OWB_WIDTH		4
#घोषणा PS_OWB_MASK		0x00000F00
#घोषणा PS_RING_SHIFT		6
#घोषणा PS_RING_MASK		0x000000C0
#घोषणा PS_UM_BIT		5
#घोषणा PS_EXCM_BIT		4
#घोषणा PS_INTLEVEL_SHIFT	0
#घोषणा PS_INTLEVEL_WIDTH	4
#घोषणा PS_INTLEVEL_MASK	0x0000000F

/*  DBREAKCn रेजिस्टर fields.  */

#घोषणा DBREAKC_MASK_BIT		0
#घोषणा DBREAKC_MASK_MASK		0x0000003F
#घोषणा DBREAKC_LOAD_BIT		30
#घोषणा DBREAKC_LOAD_MASK		0x40000000
#घोषणा DBREAKC_STOR_BIT		31
#घोषणा DBREAKC_STOR_MASK		0x80000000

/*  DEBUGCAUSE रेजिस्टर fields.  */

#घोषणा DEBUGCAUSE_DBNUM_MASK		0xf00
#घोषणा DEBUGCAUSE_DBNUM_SHIFT		8	/* First bit of DBNUM field */
#घोषणा DEBUGCAUSE_DEBUGINT_BIT		5	/* External debug पूर्णांकerrupt */
#घोषणा DEBUGCAUSE_BREAKN_BIT		4	/* BREAK.N inकाष्ठाion */
#घोषणा DEBUGCAUSE_BREAK_BIT		3	/* BREAK inकाष्ठाion */
#घोषणा DEBUGCAUSE_DBREAK_BIT		2	/* DBREAK match */
#घोषणा DEBUGCAUSE_IBREAK_BIT		1	/* IBREAK match */
#घोषणा DEBUGCAUSE_ICOUNT_BIT		0	/* ICOUNT would incr. to zero */

#पूर्ण_अगर /* _XTENSA_SPECREG_H */
