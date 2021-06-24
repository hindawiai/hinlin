<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2009 Freescale Semiconductor, Inc.
 *
 * provides masks and opcode images क्रम use by code generation, emulation
 * and क्रम inकाष्ठाions that older assemblers might not know about
 */
#अगर_अघोषित _ASM_POWERPC_PPC_OPCODE_H
#घोषणा _ASM_POWERPC_PPC_OPCODE_H

#समावेश <यंत्र/यंत्र-स्थिर.h>

#घोषणा	__REG_R0	0
#घोषणा	__REG_R1	1
#घोषणा	__REG_R2	2
#घोषणा	__REG_R3	3
#घोषणा	__REG_R4	4
#घोषणा	__REG_R5	5
#घोषणा	__REG_R6	6
#घोषणा	__REG_R7	7
#घोषणा	__REG_R8	8
#घोषणा	__REG_R9	9
#घोषणा	__REG_R10	10
#घोषणा	__REG_R11	11
#घोषणा	__REG_R12	12
#घोषणा	__REG_R13	13
#घोषणा	__REG_R14	14
#घोषणा	__REG_R15	15
#घोषणा	__REG_R16	16
#घोषणा	__REG_R17	17
#घोषणा	__REG_R18	18
#घोषणा	__REG_R19	19
#घोषणा	__REG_R20	20
#घोषणा	__REG_R21	21
#घोषणा	__REG_R22	22
#घोषणा	__REG_R23	23
#घोषणा	__REG_R24	24
#घोषणा	__REG_R25	25
#घोषणा	__REG_R26	26
#घोषणा	__REG_R27	27
#घोषणा	__REG_R28	28
#घोषणा	__REG_R29	29
#घोषणा	__REG_R30	30
#घोषणा	__REG_R31	31

#घोषणा	__REGA0_0	0
#घोषणा	__REGA0_R1	1
#घोषणा	__REGA0_R2	2
#घोषणा	__REGA0_R3	3
#घोषणा	__REGA0_R4	4
#घोषणा	__REGA0_R5	5
#घोषणा	__REGA0_R6	6
#घोषणा	__REGA0_R7	7
#घोषणा	__REGA0_R8	8
#घोषणा	__REGA0_R9	9
#घोषणा	__REGA0_R10	10
#घोषणा	__REGA0_R11	11
#घोषणा	__REGA0_R12	12
#घोषणा	__REGA0_R13	13
#घोषणा	__REGA0_R14	14
#घोषणा	__REGA0_R15	15
#घोषणा	__REGA0_R16	16
#घोषणा	__REGA0_R17	17
#घोषणा	__REGA0_R18	18
#घोषणा	__REGA0_R19	19
#घोषणा	__REGA0_R20	20
#घोषणा	__REGA0_R21	21
#घोषणा	__REGA0_R22	22
#घोषणा	__REGA0_R23	23
#घोषणा	__REGA0_R24	24
#घोषणा	__REGA0_R25	25
#घोषणा	__REGA0_R26	26
#घोषणा	__REGA0_R27	27
#घोषणा	__REGA0_R28	28
#घोषणा	__REGA0_R29	29
#घोषणा	__REGA0_R30	30
#घोषणा	__REGA0_R31	31

#घोषणा IMM_L(i)               ((uपूर्णांकptr_t)(i) & 0xffff)
#घोषणा IMM_DS(i)              ((uपूर्णांकptr_t)(i) & 0xfffc)
#घोषणा IMM_DQ(i)              ((uपूर्णांकptr_t)(i) & 0xfff0)
#घोषणा IMM_D0(i)              (((uपूर्णांकptr_t)(i) >> 16) & 0x3ffff)
#घोषणा IMM_D1(i)              IMM_L(i)

/*
 * 16-bit immediate helper macros: HA() is क्रम use with sign-extending instrs
 * (e.g. LD, ADDI).  If the bottom 16 bits is "-ve", add another bit पूर्णांकo the
 * top half to negate the effect (i.e. 0xffff + 1 = 0x(1)0000).
 */
#घोषणा IMM_H(i)                ((uपूर्णांकptr_t)(i)>>16)
#घोषणा IMM_HA(i)               (((uपूर्णांकptr_t)(i)>>16) +                       \
					(((uपूर्णांकptr_t)(i) & 0x8000) >> 15))


/* opcode and xopcode क्रम inकाष्ठाions */
#घोषणा OP_TRAP 3
#घोषणा OP_TRAP_64 2

#घोषणा OP_31_XOP_TRAP      4
#घोषणा OP_31_XOP_LDX       21
#घोषणा OP_31_XOP_LWZX      23
#घोषणा OP_31_XOP_LDUX      53
#घोषणा OP_31_XOP_DCBST     54
#घोषणा OP_31_XOP_LWZUX     55
#घोषणा OP_31_XOP_TRAP_64   68
#घोषणा OP_31_XOP_DCBF      86
#घोषणा OP_31_XOP_LBZX      87
#घोषणा OP_31_XOP_STDX      149
#घोषणा OP_31_XOP_STWX      151
#घोषणा OP_31_XOP_STDUX     181
#घोषणा OP_31_XOP_STWUX     183
#घोषणा OP_31_XOP_STBX      215
#घोषणा OP_31_XOP_LBZUX     119
#घोषणा OP_31_XOP_STBUX     247
#घोषणा OP_31_XOP_LHZX      279
#घोषणा OP_31_XOP_LHZUX     311
#घोषणा OP_31_XOP_MSGSNDP   142
#घोषणा OP_31_XOP_MSGCLRP   174
#घोषणा OP_31_XOP_TLBIE     306
#घोषणा OP_31_XOP_MFSPR     339
#घोषणा OP_31_XOP_LWAX      341
#घोषणा OP_31_XOP_LHAX      343
#घोषणा OP_31_XOP_LWAUX     373
#घोषणा OP_31_XOP_LHAUX     375
#घोषणा OP_31_XOP_STHX      407
#घोषणा OP_31_XOP_STHUX     439
#घोषणा OP_31_XOP_MTSPR     467
#घोषणा OP_31_XOP_DCBI      470
#घोषणा OP_31_XOP_LDBRX     532
#घोषणा OP_31_XOP_LWBRX     534
#घोषणा OP_31_XOP_TLBSYNC   566
#घोषणा OP_31_XOP_STDBRX    660
#घोषणा OP_31_XOP_STWBRX    662
#घोषणा OP_31_XOP_STFSX	    663
#घोषणा OP_31_XOP_STFSUX    695
#घोषणा OP_31_XOP_STFDX     727
#घोषणा OP_31_XOP_STFDUX    759
#घोषणा OP_31_XOP_LHBRX     790
#घोषणा OP_31_XOP_LFIWAX    855
#घोषणा OP_31_XOP_LFIWZX    887
#घोषणा OP_31_XOP_STHBRX    918
#घोषणा OP_31_XOP_STFIWX    983

/* VSX Scalar Load Inकाष्ठाions */
#घोषणा OP_31_XOP_LXSDX         588
#घोषणा OP_31_XOP_LXSSPX        524
#घोषणा OP_31_XOP_LXSIWAX       76
#घोषणा OP_31_XOP_LXSIWZX       12

/* VSX Scalar Store Inकाष्ठाions */
#घोषणा OP_31_XOP_STXSDX        716
#घोषणा OP_31_XOP_STXSSPX       652
#घोषणा OP_31_XOP_STXSIWX       140

/* VSX Vector Load Inकाष्ठाions */
#घोषणा OP_31_XOP_LXVD2X        844
#घोषणा OP_31_XOP_LXVW4X        780

/* VSX Vector Load and Splat Inकाष्ठाion */
#घोषणा OP_31_XOP_LXVDSX        332

/* VSX Vector Store Inकाष्ठाions */
#घोषणा OP_31_XOP_STXVD2X       972
#घोषणा OP_31_XOP_STXVW4X       908

#घोषणा OP_31_XOP_LFSX          535
#घोषणा OP_31_XOP_LFSUX         567
#घोषणा OP_31_XOP_LFDX          599
#घोषणा OP_31_XOP_LFDUX		631

/* VMX Vector Load Inकाष्ठाions */
#घोषणा OP_31_XOP_LVX           103

/* VMX Vector Store Inकाष्ठाions */
#घोषणा OP_31_XOP_STVX          231

/* Prefixed Inकाष्ठाions */
#घोषणा OP_PREFIX		1

#घोषणा OP_31   31
#घोषणा OP_LWZ  32
#घोषणा OP_STFS 52
#घोषणा OP_STFSU 53
#घोषणा OP_STFD 54
#घोषणा OP_STFDU 55
#घोषणा OP_LD   58
#घोषणा OP_LWZU 33
#घोषणा OP_LBZ  34
#घोषणा OP_LBZU 35
#घोषणा OP_STW  36
#घोषणा OP_STWU 37
#घोषणा OP_STD  62
#घोषणा OP_STB  38
#घोषणा OP_STBU 39
#घोषणा OP_LHZ  40
#घोषणा OP_LHZU 41
#घोषणा OP_LHA  42
#घोषणा OP_LHAU 43
#घोषणा OP_STH  44
#घोषणा OP_STHU 45
#घोषणा OP_LMW  46
#घोषणा OP_STMW 47
#घोषणा OP_LFS  48
#घोषणा OP_LFSU 49
#घोषणा OP_LFD  50
#घोषणा OP_LFDU 51
#घोषणा OP_STFS 52
#घोषणा OP_STFSU 53
#घोषणा OP_STFD  54
#घोषणा OP_STFDU 55
#घोषणा OP_LQ    56

/* sorted alphabetically */
#घोषणा PPC_INST_BCCTR_FLUSH		0x4c400420
#घोषणा PPC_INST_COPY			0x7c20060c
#घोषणा PPC_INST_DCBA			0x7c0005ec
#घोषणा PPC_INST_DCBA_MASK		0xfc0007fe
#घोषणा PPC_INST_ISEL			0x7c00001e
#घोषणा PPC_INST_ISEL_MASK		0xfc00003e
#घोषणा PPC_INST_LSWI			0x7c0004aa
#घोषणा PPC_INST_LSWX			0x7c00042a
#घोषणा PPC_INST_LWSYNC			0x7c2004ac
#घोषणा PPC_INST_SYNC			0x7c0004ac
#घोषणा PPC_INST_SYNC_MASK		0xfc0007fe
#घोषणा PPC_INST_ISYNC			0x4c00012c
#घोषणा PPC_INST_MCRXR			0x7c000400
#घोषणा PPC_INST_MCRXR_MASK		0xfc0007fe
#घोषणा PPC_INST_MFSPR_PVR		0x7c1f42a6
#घोषणा PPC_INST_MFSPR_PVR_MASK		0xfc1ffffe
#घोषणा PPC_INST_MTMSRD			0x7c000164
#घोषणा PPC_INST_NOP			0x60000000
#घोषणा PPC_INST_POPCNTB		0x7c0000f4
#घोषणा PPC_INST_POPCNTB_MASK		0xfc0007fe
#घोषणा PPC_INST_RFEBB			0x4c000124
#घोषणा PPC_INST_RFID			0x4c000024
#घोषणा PPC_INST_MFSPR_DSCR		0x7c1102a6
#घोषणा PPC_INST_MFSPR_DSCR_MASK	0xfc1ffffe
#घोषणा PPC_INST_MTSPR_DSCR		0x7c1103a6
#घोषणा PPC_INST_MTSPR_DSCR_MASK	0xfc1ffffe
#घोषणा PPC_INST_MFSPR_DSCR_USER	0x7c0302a6
#घोषणा PPC_INST_MFSPR_DSCR_USER_MASK	0xfc1ffffe
#घोषणा PPC_INST_MTSPR_DSCR_USER	0x7c0303a6
#घोषणा PPC_INST_MTSPR_DSCR_USER_MASK	0xfc1ffffe
#घोषणा PPC_INST_SC			0x44000002
#घोषणा PPC_INST_STRING			0x7c00042a
#घोषणा PPC_INST_STRING_MASK		0xfc0007fe
#घोषणा PPC_INST_STRING_GEN_MASK	0xfc00067e
#घोषणा PPC_INST_STSWI			0x7c0005aa
#घोषणा PPC_INST_STSWX			0x7c00052a
#घोषणा PPC_INST_TRECHKPT		0x7c0007dd
#घोषणा PPC_INST_TRECLAIM		0x7c00075d
#घोषणा PPC_INST_TSR			0x7c0005dd
#घोषणा PPC_INST_LD			0xe8000000
#घोषणा PPC_INST_STD			0xf8000000
#घोषणा PPC_INST_MFLR			0x7c0802a6
#घोषणा PPC_INST_MTCTR			0x7c0903a6
#घोषणा PPC_INST_ADDI			0x38000000
#घोषणा PPC_INST_ADDIS			0x3c000000
#घोषणा PPC_INST_ADD			0x7c000214
#घोषणा PPC_INST_BLR			0x4e800020
#घोषणा PPC_INST_BCTR			0x4e800420
#घोषणा PPC_INST_BCTRL			0x4e800421
#घोषणा PPC_INST_DIVD			0x7c0003d2
#घोषणा PPC_INST_RLDICR			0x78000004
#घोषणा PPC_INST_ORI			0x60000000
#घोषणा PPC_INST_ORIS			0x64000000
#घोषणा PPC_INST_BRANCH			0x48000000
#घोषणा PPC_INST_BL			0x48000001
#घोषणा PPC_INST_BRANCH_COND		0x40800000

/* Prefixes */
#घोषणा PPC_INST_LFS			0xc0000000
#घोषणा PPC_INST_STFS			0xd0000000
#घोषणा PPC_INST_LFD			0xc8000000
#घोषणा PPC_INST_STFD			0xd8000000
#घोषणा PPC_PREFIX_MLS			0x06000000
#घोषणा PPC_PREFIX_8LS			0x04000000

/* Prefixed inकाष्ठाions */
#घोषणा PPC_INST_PLD			0xe4000000
#घोषणा PPC_INST_PSTD			0xf4000000

/* macros to insert fields पूर्णांकo opcodes */
#घोषणा ___PPC_RA(a)	(((a) & 0x1f) << 16)
#घोषणा ___PPC_RB(b)	(((b) & 0x1f) << 11)
#घोषणा ___PPC_RC(c)	(((c) & 0x1f) << 6)
#घोषणा ___PPC_RS(s)	(((s) & 0x1f) << 21)
#घोषणा ___PPC_RT(t)	___PPC_RS(t)
#घोषणा ___PPC_R(r)	(((r) & 0x1) << 16)
#घोषणा ___PPC_PRS(prs)	(((prs) & 0x1) << 17)
#घोषणा ___PPC_RIC(ric)	(((ric) & 0x3) << 18)
#घोषणा __PPC_RA(a)	___PPC_RA(__REG_##a)
#घोषणा __PPC_RA0(a)	___PPC_RA(__REGA0_##a)
#घोषणा __PPC_RB(b)	___PPC_RB(__REG_##b)
#घोषणा __PPC_RS(s)	___PPC_RS(__REG_##s)
#घोषणा __PPC_RT(t)	___PPC_RT(__REG_##t)
#घोषणा __PPC_XA(a)	((((a) & 0x1f) << 16) | (((a) & 0x20) >> 3))
#घोषणा __PPC_XB(b)	((((b) & 0x1f) << 11) | (((b) & 0x20) >> 4))
#घोषणा __PPC_XS(s)	((((s) & 0x1f) << 21) | (((s) & 0x20) >> 5))
#घोषणा __PPC_XT(s)	__PPC_XS(s)
#घोषणा __PPC_XSP(s)	((((s) & 0x1e) | (((s) >> 5) & 0x1)) << 21)
#घोषणा __PPC_XTP(s)	__PPC_XSP(s)
#घोषणा __PPC_T_TLB(t)	(((t) & 0x3) << 21)
#घोषणा __PPC_WC(w)	(((w) & 0x3) << 21)
#घोषणा __PPC_WS(w)	(((w) & 0x1f) << 11)
#घोषणा __PPC_SH(s)	__PPC_WS(s)
#घोषणा __PPC_SH64(s)	(__PPC_SH(s) | (((s) & 0x20) >> 4))
#घोषणा __PPC_MB(s)	___PPC_RC(s)
#घोषणा __PPC_ME(s)	(((s) & 0x1f) << 1)
#घोषणा __PPC_MB64(s)	(__PPC_MB(s) | ((s) & 0x20))
#घोषणा __PPC_ME64(s)	__PPC_MB64(s)
#घोषणा __PPC_BI(s)	(((s) & 0x1f) << 16)
#घोषणा __PPC_CT(t)	(((t) & 0x0f) << 21)
#घोषणा __PPC_SPR(r)	((((r) & 0x1f) << 16) | ((((r) >> 5) & 0x1f) << 11))
#घोषणा __PPC_RC21	(0x1 << 10)
#घोषणा __PPC_PRFX_R(r)	(((r) & 0x1) << 20)

/*
 * Both low and high 16 bits are added as SIGNED additions, so अगर low 16 bits
 * has high bit set, high 16 bits must be adjusted. These macros करो that (stolen
 * from binutils).
 */
#घोषणा PPC_LO(v)	((v) & 0xffff)
#घोषणा PPC_HI(v)	(((v) >> 16) & 0xffff)
#घोषणा PPC_HA(v)	PPC_HI((v) + 0x8000)

/*
 * Only use the larx hपूर्णांक bit on 64bit CPUs. e500v1/v2 based CPUs will treat a
 * larx with EH set as an illegal inकाष्ठाion.
 */
#अगर_घोषित CONFIG_PPC64
#घोषणा __PPC_EH(eh)	(((eh) & 0x1) << 0)
#अन्यथा
#घोषणा __PPC_EH(eh)	0
#पूर्ण_अगर

/* Base inकाष्ठाion encoding */
#घोषणा PPC_RAW_CP_ABORT		(0x7c00068c)
#घोषणा PPC_RAW_COPY(a, b)		(PPC_INST_COPY | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_DARN(t, l)		(0x7c0005e6 | ___PPC_RT(t) | (((l) & 0x3) << 16))
#घोषणा PPC_RAW_DCBAL(a, b)		(0x7c2005ec | __PPC_RA(a) | __PPC_RB(b))
#घोषणा PPC_RAW_DCBZL(a, b)		(0x7c2007ec | __PPC_RA(a) | __PPC_RB(b))
#घोषणा PPC_RAW_LQARX(t, a, b, eh)	(0x7c000228 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | __PPC_EH(eh))
#घोषणा PPC_RAW_LDARX(t, a, b, eh)	(0x7c0000a8 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | __PPC_EH(eh))
#घोषणा PPC_RAW_LWARX(t, a, b, eh)	(0x7c000028 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | __PPC_EH(eh))
#घोषणा PPC_RAW_PHWSYNC			(0x7c8004ac)
#घोषणा PPC_RAW_PLWSYNC			(0x7ca004ac)
#घोषणा PPC_RAW_STQCX(t, a, b)		(0x7c00016d | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_MADDHD(t, a, b, c)	(0x10000030 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | ___PPC_RC(c))
#घोषणा PPC_RAW_MADDHDU(t, a, b, c)	(0x10000031 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | ___PPC_RC(c))
#घोषणा PPC_RAW_MADDLD(t, a, b, c)	(0x10000033 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | ___PPC_RC(c))
#घोषणा PPC_RAW_MSGSND(b)		(0x7c00019c | ___PPC_RB(b))
#घोषणा PPC_RAW_MSGSYNC			(0x7c0006ec)
#घोषणा PPC_RAW_MSGCLR(b)		(0x7c0001dc | ___PPC_RB(b))
#घोषणा PPC_RAW_MSGSNDP(b)		(0x7c00011c | ___PPC_RB(b))
#घोषणा PPC_RAW_MSGCLRP(b)		(0x7c00015c | ___PPC_RB(b))
#घोषणा PPC_RAW_PASTE(a, b)		(0x7c20070d | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_POPCNTB(a, s)		(PPC_INST_POPCNTB | __PPC_RA(a) | __PPC_RS(s))
#घोषणा PPC_RAW_POPCNTD(a, s)		(0x7c0003f4 | __PPC_RA(a) | __PPC_RS(s))
#घोषणा PPC_RAW_POPCNTW(a, s)		(0x7c0002f4 | __PPC_RA(a) | __PPC_RS(s))
#घोषणा PPC_RAW_RFCI			(0x4c000066)
#घोषणा PPC_RAW_RFDI			(0x4c00004e)
#घोषणा PPC_RAW_RFMCI			(0x4c00004c)
#घोषणा PPC_RAW_TLBILX(t, a, b)		(0x7c000024 | __PPC_T_TLB(t) | 	__PPC_RA0(a) | __PPC_RB(b))
#घोषणा PPC_RAW_WAIT(w)			(0x7c00007c | __PPC_WC(w))
#घोषणा PPC_RAW_TLBIE(lp, a)		(0x7c000264 | ___PPC_RB(a) | ___PPC_RS(lp))
#घोषणा PPC_RAW_TLBIE_5(rb, rs, ric, prs, r) \
	(0x7c000264 | ___PPC_RB(rb) | ___PPC_RS(rs) | ___PPC_RIC(ric) | ___PPC_PRS(prs) | ___PPC_R(r))
#घोषणा PPC_RAW_TLBIEL(rb, rs, ric, prs, r) \
	(0x7c000224 | ___PPC_RB(rb) | ___PPC_RS(rs) | ___PPC_RIC(ric) | ___PPC_PRS(prs) | ___PPC_R(r))
#घोषणा PPC_RAW_TLBSRX_DOT(a, b)	(0x7c0006a5 | __PPC_RA0(a) | __PPC_RB(b))
#घोषणा PPC_RAW_TLBIVAX(a, b)		(0x7c000624 | __PPC_RA0(a) | __PPC_RB(b))
#घोषणा PPC_RAW_ERATWE(s, a, w)		(0x7c0001a6 | __PPC_RS(s) | __PPC_RA(a) | __PPC_WS(w))
#घोषणा PPC_RAW_ERATRE(s, a, w)		(0x7c000166 | __PPC_RS(s) | __PPC_RA(a) | __PPC_WS(w))
#घोषणा PPC_RAW_ERATILX(t, a, b)	(0x7c000066 | __PPC_T_TLB(t) | __PPC_RA0(a) | __PPC_RB(b))
#घोषणा PPC_RAW_ERATIVAX(s, a, b)	(0x7c000666 | __PPC_RS(s) | __PPC_RA0(a) | __PPC_RB(b))
#घोषणा PPC_RAW_ERATSX(t, a, w)		(0x7c000126 | __PPC_RS(t) | __PPC_RA0(a) | __PPC_RB(b))
#घोषणा PPC_RAW_ERATSX_DOT(t, a, w)	(0x7c000127 | __PPC_RS(t) | __PPC_RA0(a) | __PPC_RB(b))
#घोषणा PPC_RAW_SLBFEE_DOT(t, b)	(0x7c0007a7 | __PPC_RT(t) | __PPC_RB(b))
#घोषणा __PPC_RAW_SLBFEE_DOT(t, b)	(0x7c0007a7 | ___PPC_RT(t) | ___PPC_RB(b))
#घोषणा PPC_RAW_ICBT(c, a, b)		(0x7c00002c | __PPC_CT(c) | __PPC_RA0(a) | __PPC_RB(b))
#घोषणा PPC_RAW_LBZCIX(t, a, b)		(0x7c0006aa | __PPC_RT(t) | __PPC_RA(a) | __PPC_RB(b))
#घोषणा PPC_RAW_STBCIX(s, a, b)		(0x7c0007aa | __PPC_RS(s) | __PPC_RA(a) | __PPC_RB(b))
#घोषणा PPC_RAW_DCBFPS(a, b)		(0x7c0000ac | ___PPC_RA(a) | ___PPC_RB(b) | (4 << 21))
#घोषणा PPC_RAW_DCBSTPS(a, b)		(0x7c0000ac | ___PPC_RA(a) | ___PPC_RB(b) | (6 << 21))
/*
 * Define what the VSX XX1 क्रमm inकाष्ठाions will look like, then add
 * the 128 bit load store inकाष्ठाions based on that.
 */
#घोषणा VSX_XX1(s, a, b)		(__PPC_XS(s) | __PPC_RA(a) | __PPC_RB(b))
#घोषणा VSX_XX3(t, a, b)		(__PPC_XT(t) | __PPC_XA(a) | __PPC_XB(b))
#घोषणा PPC_RAW_STXVD2X(s, a, b)	(0x7c000798 | VSX_XX1((s), a, b))
#घोषणा PPC_RAW_LXVD2X(s, a, b)		(0x7c000698 | VSX_XX1((s), a, b))
#घोषणा PPC_RAW_MFVRD(a, t)		(0x7c000066 | VSX_XX1((t) + 32, a, R0))
#घोषणा PPC_RAW_MTVRD(t, a)		(0x7c000166 | VSX_XX1((t) + 32, a, R0))
#घोषणा PPC_RAW_VPMSUMW(t, a, b)	(0x10000488 | VSX_XX3((t), a, b))
#घोषणा PPC_RAW_VPMSUMD(t, a, b)	(0x100004c8 | VSX_XX3((t), a, b))
#घोषणा PPC_RAW_XXLOR(t, a, b)		(0xf0000490 | VSX_XX3((t), a, b))
#घोषणा PPC_RAW_XXSWAPD(t, a)		(0xf0000250 | VSX_XX3((t), a, a))
#घोषणा PPC_RAW_XVCPSGNDP(t, a, b)	((0xf0000780 | VSX_XX3((t), (a), (b))))
#घोषणा PPC_RAW_VPERMXOR(vrt, vra, vrb, vrc) \
	((0x1000002d | ___PPC_RT(vrt) | ___PPC_RA(vra) | ___PPC_RB(vrb) | (((vrc) & 0x1f) << 6)))
#घोषणा PPC_RAW_LXVP(xtp, a, i)		(0x18000000 | __PPC_XTP(xtp) | ___PPC_RA(a) | IMM_DQ(i))
#घोषणा PPC_RAW_STXVP(xsp, a, i)	(0x18000001 | __PPC_XSP(xsp) | ___PPC_RA(a) | IMM_DQ(i))
#घोषणा PPC_RAW_LXVPX(xtp, a, b)	(0x7c00029a | __PPC_XTP(xtp) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_STXVPX(xsp, a, b)	(0x7c00039a | __PPC_XSP(xsp) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_PLXVP(xtp, i, a, pr) \
	((PPC_PREFIX_8LS | __PPC_PRFX_R(pr) | IMM_D0(i)) << 32 | (0xe8000000 | __PPC_XTP(xtp) | ___PPC_RA(a) | IMM_D1(i)))
#घोषणा PPC_RAW_PSTXVP(xsp, i, a, pr) \
	((PPC_PREFIX_8LS | __PPC_PRFX_R(pr) | IMM_D0(i)) << 32 | (0xf8000000 | __PPC_XSP(xsp) | ___PPC_RA(a) | IMM_D1(i)))
#घोषणा PPC_RAW_NAP			(0x4c000364)
#घोषणा PPC_RAW_SLEEP			(0x4c0003a4)
#घोषणा PPC_RAW_WINKLE			(0x4c0003e4)
#घोषणा PPC_RAW_STOP			(0x4c0002e4)
#घोषणा PPC_RAW_CLRBHRB			(0x7c00035c)
#घोषणा PPC_RAW_MFBHRBE(r, n)		(0x7c00025c | __PPC_RT(r) | (((n) & 0x3ff) << 11))
#घोषणा PPC_RAW_TRECHKPT		(PPC_INST_TRECHKPT)
#घोषणा PPC_RAW_TRECLAIM(r)		(PPC_INST_TRECLAIM | __PPC_RA(r))
#घोषणा PPC_RAW_TABORT(r)		(0x7c00071d | __PPC_RA(r))
#घोषणा TMRN(x)				((((x) & 0x1f) << 16) | (((x) & 0x3e0) << 6))
#घोषणा PPC_RAW_MTTMR(पंचांगr, r)		(0x7c0003dc | TMRN(पंचांगr) | ___PPC_RS(r))
#घोषणा PPC_RAW_MFTMR(पंचांगr, r)		(0x7c0002dc | TMRN(पंचांगr) | ___PPC_RT(r))
#घोषणा PPC_RAW_ICSWX(s, a, b)		(0x7c00032d | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_ICSWEPX(s, a, b)	(0x7c00076d | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_SLBIA(IH)		(0x7c0003e4 | (((IH) & 0x7) << 21))
#घोषणा PPC_RAW_VCMPEQUD_RC(vrt, vra, vrb) \
	(0x100000c7 | ___PPC_RT(vrt) | ___PPC_RA(vra) | ___PPC_RB(vrb) | __PPC_RC21)
#घोषणा PPC_RAW_VCMPEQUB_RC(vrt, vra, vrb) \
	(0x10000006 | ___PPC_RT(vrt) | ___PPC_RA(vra) | ___PPC_RB(vrb) | __PPC_RC21)
#घोषणा PPC_RAW_LD(r, base, i)		(PPC_INST_LD | ___PPC_RT(r) | ___PPC_RA(base) | IMM_DS(i))
#घोषणा PPC_RAW_LWZ(r, base, i)		(0x80000000 | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))
#घोषणा PPC_RAW_LWZX(t, a, b)		(0x7c00002e | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_STD(r, base, i)		(PPC_INST_STD | ___PPC_RS(r) | ___PPC_RA(base) | IMM_DS(i))
#घोषणा PPC_RAW_STDCX(s, a, b)		(0x7c0001ad | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_LFSX(t, a, b)		(0x7c00042e | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_STFSX(s, a, b)		(0x7c00052e | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_LFDX(t, a, b)		(0x7c0004ae | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_STFDX(s, a, b)		(0x7c0005ae | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_LVX(t, a, b)		(0x7c0000ce | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_STVX(s, a, b)		(0x7c0001ce | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_ADDE(t, a, b)		(0x7c000114 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_ADDZE(t, a)		(0x7c000194 | ___PPC_RT(t) | ___PPC_RA(a))
#घोषणा PPC_RAW_ADDME(t, a)		(0x7c0001d4 | ___PPC_RT(t) | ___PPC_RA(a))
#घोषणा PPC_RAW_ADD(t, a, b)		(PPC_INST_ADD | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_ADD_DOT(t, a, b)	(PPC_INST_ADD | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | 0x1)
#घोषणा PPC_RAW_ADDC(t, a, b)		(0x7c000014 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_ADDC_DOT(t, a, b)	(0x7c000014 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | 0x1)
#घोषणा PPC_RAW_NOP()			(PPC_INST_NOP)
#घोषणा PPC_RAW_BLR()			(PPC_INST_BLR)
#घोषणा PPC_RAW_BLRL()			(0x4e800021)
#घोषणा PPC_RAW_MTLR(r)			(0x7c0803a6 | ___PPC_RT(r))
#घोषणा PPC_RAW_MFLR(t)			(PPC_INST_MFLR | ___PPC_RT(t))
#घोषणा PPC_RAW_BCTR()			(PPC_INST_BCTR)
#घोषणा PPC_RAW_MTCTR(r)		(PPC_INST_MTCTR | ___PPC_RT(r))
#घोषणा PPC_RAW_ADDI(d, a, i)		(PPC_INST_ADDI | ___PPC_RT(d) | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_LI(r, i)		PPC_RAW_ADDI(r, 0, i)
#घोषणा PPC_RAW_ADDIS(d, a, i)		(PPC_INST_ADDIS | ___PPC_RT(d) | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_ADDIC(d, a, i)		(0x30000000 | ___PPC_RT(d) | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_ADDIC_DOT(d, a, i)	(0x34000000 | ___PPC_RT(d) | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_LIS(r, i)		PPC_RAW_ADDIS(r, 0, i)
#घोषणा PPC_RAW_STDX(r, base, b)	(0x7c00012a | ___PPC_RS(r) | ___PPC_RA(base) | ___PPC_RB(b))
#घोषणा PPC_RAW_STDU(r, base, i)	(0xf8000001 | ___PPC_RS(r) | ___PPC_RA(base) | ((i) & 0xfffc))
#घोषणा PPC_RAW_STW(r, base, i)		(0x90000000 | ___PPC_RS(r) | ___PPC_RA(base) | IMM_L(i))
#घोषणा PPC_RAW_STWU(r, base, i)	(0x94000000 | ___PPC_RS(r) | ___PPC_RA(base) | IMM_L(i))
#घोषणा PPC_RAW_STH(r, base, i)		(0xb0000000 | ___PPC_RS(r) | ___PPC_RA(base) | IMM_L(i))
#घोषणा PPC_RAW_STB(r, base, i)		(0x98000000 | ___PPC_RS(r) | ___PPC_RA(base) | IMM_L(i))
#घोषणा PPC_RAW_LBZ(r, base, i)		(0x88000000 | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))
#घोषणा PPC_RAW_LDX(r, base, b)		(0x7c00002a | ___PPC_RT(r) | ___PPC_RA(base) | ___PPC_RB(b))
#घोषणा PPC_RAW_LHZ(r, base, i)		(0xa0000000 | ___PPC_RT(r) | ___PPC_RA(base) | IMM_L(i))
#घोषणा PPC_RAW_LHBRX(r, base, b)	(0x7c00062c | ___PPC_RT(r) | ___PPC_RA(base) | ___PPC_RB(b))
#घोषणा PPC_RAW_LDBRX(r, base, b)	(0x7c000428 | ___PPC_RT(r) | ___PPC_RA(base) | ___PPC_RB(b))
#घोषणा PPC_RAW_STWCX(s, a, b)		(0x7c00012d | ___PPC_RS(s) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_CMPWI(a, i)		(0x2c000000 | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_CMPDI(a, i)		(0x2c200000 | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_CMPW(a, b)		(0x7c000000 | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_CMPD(a, b)		(0x7c200000 | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_CMPLWI(a, i)		(0x28000000 | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_CMPLDI(a, i)		(0x28200000 | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_CMPLW(a, b)		(0x7c000040 | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_CMPLD(a, b)		(0x7c200040 | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_SUB(d, a, b)		(0x7c000050 | ___PPC_RT(d) | ___PPC_RB(a) | ___PPC_RA(b))
#घोषणा PPC_RAW_SUBFC(d, a, b)		(0x7c000010 | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_SUBFE(d, a, b)		(0x7c000110 | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_SUBFIC(d, a, i)		(0x20000000 | ___PPC_RT(d) | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_SUBFZE(d, a)		(0x7c000190 | ___PPC_RT(d) | ___PPC_RA(a))
#घोषणा PPC_RAW_MULD(d, a, b)		(0x7c0001d2 | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_MULW(d, a, b)		(0x7c0001d6 | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_MULHWU(d, a, b)		(0x7c000016 | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_MULI(d, a, i)		(0x1c000000 | ___PPC_RT(d) | ___PPC_RA(a) | IMM_L(i))
#घोषणा PPC_RAW_DIVWU(d, a, b)		(0x7c000396 | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_DIVDU(d, a, b)		(0x7c000392 | ___PPC_RT(d) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_DIVDE(t, a, b)		(0x7c000352 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_DIVDE_DOT(t, a, b)	(0x7c000352 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | 0x1)
#घोषणा PPC_RAW_DIVDEU(t, a, b)		(0x7c000312 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_DIVDEU_DOT(t, a, b)	(0x7c000312 | ___PPC_RT(t) | ___PPC_RA(a) | ___PPC_RB(b) | 0x1)
#घोषणा PPC_RAW_AND(d, a, b)		(0x7c000038 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_ANDI(d, a, i)		(0x70000000 | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#घोषणा PPC_RAW_ANDIS(d, a, i)		(0x74000000 | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#घोषणा PPC_RAW_AND_DOT(d, a, b)	(0x7c000039 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_OR(d, a, b)		(0x7c000378 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_MR(d, a)		PPC_RAW_OR(d, a, a)
#घोषणा PPC_RAW_ORI(d, a, i)		(PPC_INST_ORI | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#घोषणा PPC_RAW_ORIS(d, a, i)		(PPC_INST_ORIS | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#घोषणा PPC_RAW_NOR(d, a, b)		(0x7c0000f8 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_XOR(d, a, b)		(0x7c000278 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(b))
#घोषणा PPC_RAW_XORI(d, a, i)		(0x68000000 | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#घोषणा PPC_RAW_XORIS(d, a, i)		(0x6c000000 | ___PPC_RA(d) | ___PPC_RS(a) | IMM_L(i))
#घोषणा PPC_RAW_EXTSW(d, a)		(0x7c0007b4 | ___PPC_RA(d) | ___PPC_RS(a))
#घोषणा PPC_RAW_SLW(d, a, s)		(0x7c000030 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#घोषणा PPC_RAW_SLD(d, a, s)		(0x7c000036 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#घोषणा PPC_RAW_SRW(d, a, s)		(0x7c000430 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#घोषणा PPC_RAW_SRAW(d, a, s)		(0x7c000630 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#घोषणा PPC_RAW_SRAWI(d, a, i)		(0x7c000670 | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH(i))
#घोषणा PPC_RAW_SRD(d, a, s)		(0x7c000436 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#घोषणा PPC_RAW_SRAD(d, a, s)		(0x7c000634 | ___PPC_RA(d) | ___PPC_RS(a) | ___PPC_RB(s))
#घोषणा PPC_RAW_SRADI(d, a, i)		(0x7c000674 | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH64(i))
#घोषणा PPC_RAW_RLWINM(d, a, i, mb, me)	(0x54000000 | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH(i) | __PPC_MB(mb) | __PPC_ME(me))
#घोषणा PPC_RAW_RLWINM_DOT(d, a, i, mb, me) \
					(0x54000001 | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH(i) | __PPC_MB(mb) | __PPC_ME(me))
#घोषणा PPC_RAW_RLWIMI(d, a, i, mb, me) (0x50000000 | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH(i) | __PPC_MB(mb) | __PPC_ME(me))
#घोषणा PPC_RAW_RLDICL(d, a, i, mb)     (0x78000000 | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH64(i) | __PPC_MB64(mb))
#घोषणा PPC_RAW_RLDICR(d, a, i, me)     (PPC_INST_RLDICR | ___PPC_RA(d) | ___PPC_RS(a) | __PPC_SH64(i) | __PPC_ME64(me))

/* slwi = rlwinm Rx, Ry, n, 0, 31-n */
#घोषणा PPC_RAW_SLWI(d, a, i)		PPC_RAW_RLWINM(d, a, i, 0, 31-(i))
/* srwi = rlwinm Rx, Ry, 32-n, n, 31 */
#घोषणा PPC_RAW_SRWI(d, a, i)		PPC_RAW_RLWINM(d, a, 32-(i), i, 31)
/* sldi = rldicr Rx, Ry, n, 63-n */
#घोषणा PPC_RAW_SLDI(d, a, i)		PPC_RAW_RLDICR(d, a, i, 63-(i))
/* sldi = rldicl Rx, Ry, 64-n, n */
#घोषणा PPC_RAW_SRDI(d, a, i)		PPC_RAW_RLDICL(d, a, 64-(i), i)

#घोषणा PPC_RAW_NEG(d, a)		(0x7c0000d0 | ___PPC_RT(d) | ___PPC_RA(a))

#घोषणा PPC_RAW_MFSPR(d, spr)		(0x7c0002a6 | ___PPC_RT(d) | __PPC_SPR(spr))

/* Deal with inकाष्ठाions that older assemblers aren't aware of */
#घोषणा	PPC_BCCTR_FLUSH		stringअगरy_in_c(.दीर्घ PPC_INST_BCCTR_FLUSH)
#घोषणा	PPC_CP_ABORT		stringअगरy_in_c(.दीर्घ PPC_RAW_CP_ABORT)
#घोषणा	PPC_COPY(a, b)		stringअगरy_in_c(.दीर्घ PPC_RAW_COPY(a, b))
#घोषणा PPC_DARN(t, l)		stringअगरy_in_c(.दीर्घ PPC_RAW_DARN(t, l))
#घोषणा	PPC_DCBAL(a, b)		stringअगरy_in_c(.दीर्घ PPC_RAW_DCBAL(a, b))
#घोषणा	PPC_DCBZL(a, b)		stringअगरy_in_c(.दीर्घ PPC_RAW_DCBZL(a, b))
#घोषणा	PPC_DIVDE(t, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_DIVDE(t, a, b))
#घोषणा	PPC_DIVDEU(t, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_DIVDEU(t, a, b))
#घोषणा PPC_LQARX(t, a, b, eh)	stringअगरy_in_c(.दीर्घ PPC_RAW_LQARX(t, a, b, eh))
#घोषणा PPC_LDARX(t, a, b, eh)	stringअगरy_in_c(.दीर्घ PPC_RAW_LDARX(t, a, b, eh))
#घोषणा PPC_LWARX(t, a, b, eh)	stringअगरy_in_c(.दीर्घ PPC_RAW_LWARX(t, a, b, eh))
#घोषणा PPC_STQCX(t, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_STQCX(t, a, b))
#घोषणा PPC_MADDHD(t, a, b, c)	stringअगरy_in_c(.दीर्घ PPC_RAW_MADDHD(t, a, b, c))
#घोषणा PPC_MADDHDU(t, a, b, c)	stringअगरy_in_c(.दीर्घ PPC_RAW_MADDHDU(t, a, b, c))
#घोषणा PPC_MADDLD(t, a, b, c)	stringअगरy_in_c(.दीर्घ PPC_RAW_MADDLD(t, a, b, c))
#घोषणा PPC_MSGSND(b)		stringअगरy_in_c(.दीर्घ PPC_RAW_MSGSND(b))
#घोषणा PPC_MSGSYNC		stringअगरy_in_c(.दीर्घ PPC_RAW_MSGSYNC)
#घोषणा PPC_MSGCLR(b)		stringअगरy_in_c(.दीर्घ PPC_RAW_MSGCLR(b))
#घोषणा PPC_MSGSNDP(b)		stringअगरy_in_c(.दीर्घ PPC_RAW_MSGSNDP(b))
#घोषणा PPC_MSGCLRP(b)		stringअगरy_in_c(.दीर्घ PPC_RAW_MSGCLRP(b))
#घोषणा PPC_PASTE(a, b)		stringअगरy_in_c(.दीर्घ PPC_RAW_PASTE(a, b))
#घोषणा PPC_POPCNTB(a, s)	stringअगरy_in_c(.दीर्घ PPC_RAW_POPCNTB(a, s))
#घोषणा PPC_POPCNTD(a, s)	stringअगरy_in_c(.दीर्घ PPC_RAW_POPCNTD(a, s))
#घोषणा PPC_POPCNTW(a, s)	stringअगरy_in_c(.दीर्घ PPC_RAW_POPCNTW(a, s))
#घोषणा PPC_RFCI		stringअगरy_in_c(.दीर्घ PPC_RAW_RFCI)
#घोषणा PPC_RFDI		stringअगरy_in_c(.दीर्घ PPC_RAW_RFDI)
#घोषणा PPC_RFMCI		stringअगरy_in_c(.दीर्घ PPC_RAW_RFMCI)
#घोषणा PPC_TLBILX(t, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_TLBILX(t, a, b))
#घोषणा PPC_TLBILX_ALL(a, b)	PPC_TLBILX(0, a, b)
#घोषणा PPC_TLBILX_PID(a, b)	PPC_TLBILX(1, a, b)
#घोषणा PPC_TLBILX_VA(a, b)	PPC_TLBILX(3, a, b)
#घोषणा PPC_WAIT(w)		stringअगरy_in_c(.दीर्घ PPC_RAW_WAIT(w))
#घोषणा PPC_TLBIE(lp, a) 	stringअगरy_in_c(.दीर्घ PPC_RAW_TLBIE(lp, a))
#घोषणा	PPC_TLBIE_5(rb, rs, ric, prs, r) \
				stringअगरy_in_c(.दीर्घ PPC_RAW_TLBIE_5(rb, rs, ric, prs, r))
#घोषणा	PPC_TLBIEL(rb,rs,ric,prs,r) \
				stringअगरy_in_c(.दीर्घ PPC_RAW_TLBIEL(rb, rs, ric, prs, r))
#घोषणा PPC_TLBSRX_DOT(a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_TLBSRX_DOT(a, b))
#घोषणा PPC_TLBIVAX(a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_TLBIVAX(a, b))

#घोषणा PPC_ERATWE(s, a, w)	stringअगरy_in_c(.दीर्घ PPC_RAW_ERATWE(s, a, w))
#घोषणा PPC_ERATRE(s, a, w)	stringअगरy_in_c(.दीर्घ PPC_RAW_ERATRE(a, a, w))
#घोषणा PPC_ERATILX(t, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_ERATILX(t, a, b))
#घोषणा PPC_ERATIVAX(s, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_ERATIVAX(s, a, b))
#घोषणा PPC_ERATSX(t, a, w)	stringअगरy_in_c(.दीर्घ PPC_RAW_ERATSX(t, a, w))
#घोषणा PPC_ERATSX_DOT(t, a, w)	stringअगरy_in_c(.दीर्घ PPC_RAW_ERATSX_DOT(t, a, w))
#घोषणा PPC_SLBFEE_DOT(t, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_SLBFEE_DOT(t, b))
#घोषणा __PPC_SLBFEE_DOT(t, b)	stringअगरy_in_c(.दीर्घ __PPC_RAW_SLBFEE_DOT(t, b))
#घोषणा PPC_ICBT(c, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_ICBT(c, a, b))
/* PASemi inकाष्ठाions */
#घोषणा LBZCIX(t, a, b)		stringअगरy_in_c(.दीर्घ PPC_RAW_LBZCIX(t, a, b))
#घोषणा STBCIX(s, a, b)		stringअगरy_in_c(.दीर्घ PPC_RAW_STBCIX(s, a, b))
#घोषणा PPC_DCBFPS(a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_DCBFPS(a, b))
#घोषणा PPC_DCBSTPS(a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_DCBSTPS(a, b))
#घोषणा PPC_PHWSYNC		stringअगरy_in_c(.दीर्घ PPC_RAW_PHWSYNC)
#घोषणा PPC_PLWSYNC		stringअगरy_in_c(.दीर्घ PPC_RAW_PLWSYNC)
#घोषणा STXVD2X(s, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_STXVD2X(s, a, b))
#घोषणा LXVD2X(s, a, b)		stringअगरy_in_c(.दीर्घ PPC_RAW_LXVD2X(s, a, b))
#घोषणा MFVRD(a, t)		stringअगरy_in_c(.दीर्घ PPC_RAW_MFVRD(a, t))
#घोषणा MTVRD(t, a)		stringअगरy_in_c(.दीर्घ PPC_RAW_MTVRD(t, a))
#घोषणा VPMSUMW(t, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_VPMSUMW(t, a, b))
#घोषणा VPMSUMD(t, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_VPMSUMD(t, a, b))
#घोषणा XXLOR(t, a, b)		stringअगरy_in_c(.दीर्घ PPC_RAW_XXLOR(t, a, b))
#घोषणा XXSWAPD(t, a)		stringअगरy_in_c(.दीर्घ PPC_RAW_XXSWAPD(t, a))
#घोषणा XVCPSGNDP(t, a, b)	stringअगरy_in_c(.दीर्घ (PPC_RAW_XVCPSGNDP(t, a, b)))

#घोषणा VPERMXOR(vrt, vra, vrb, vrc)				\
	stringअगरy_in_c(.दीर्घ (PPC_RAW_VPERMXOR(vrt, vra, vrb, vrc)))

#घोषणा PPC_NAP			stringअगरy_in_c(.दीर्घ PPC_RAW_NAP)
#घोषणा PPC_SLEEP		stringअगरy_in_c(.दीर्घ PPC_RAW_SLEEP)
#घोषणा PPC_WINKLE		stringअगरy_in_c(.दीर्घ PPC_RAW_WINKLE)

#घोषणा PPC_STOP		stringअगरy_in_c(.दीर्घ PPC_RAW_STOP)

/* BHRB inकाष्ठाions */
#घोषणा PPC_CLRBHRB		stringअगरy_in_c(.दीर्घ PPC_RAW_CLRBHRB)
#घोषणा PPC_MFBHRBE(r, n)	stringअगरy_in_c(.दीर्घ PPC_RAW_MFBHRBE(r, n))

/* Transactional memory inकाष्ठाions */
#घोषणा TRECHKPT		stringअगरy_in_c(.दीर्घ PPC_RAW_TRECHKPT)
#घोषणा TRECLAIM(r)		stringअगरy_in_c(.दीर्घ PPC_RAW_TRECLAIM(r))
#घोषणा TABORT(r)		stringअगरy_in_c(.दीर्घ PPC_RAW_TABORT(r))

/* book3e thपढ़ो control inकाष्ठाions */
#घोषणा MTTMR(पंचांगr, r)		stringअगरy_in_c(.दीर्घ PPC_RAW_MTTMR(पंचांगr, r))
#घोषणा MFTMR(पंचांगr, r)		stringअगरy_in_c(.दीर्घ PPC_RAW_MFTMR(पंचांगr, r))

/* Coprocessor inकाष्ठाions */
#घोषणा PPC_ICSWX(s, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_ICSWX(s, a, b))
#घोषणा PPC_ICSWEPX(s, a, b)	stringअगरy_in_c(.दीर्घ PPC_RAW_ICSWEPX(s, a, b))

#घोषणा PPC_SLBIA(IH)	stringअगरy_in_c(.दीर्घ PPC_RAW_SLBIA(IH))

/*
 * These may only be used on ISA v3.0 or later (aka. CPU_FTR_ARCH_300, radix
 * implies CPU_FTR_ARCH_300). USER/GUEST invalidates may only be used by radix
 * mode (on HPT these would also invalidate various SLBEs which may not be
 * desired).
 */
#घोषणा PPC_ISA_3_0_INVALIDATE_ERAT	PPC_SLBIA(7)
#घोषणा PPC_RADIX_INVALIDATE_ERAT_USER	PPC_SLBIA(3)
#घोषणा PPC_RADIX_INVALIDATE_ERAT_GUEST	PPC_SLBIA(6)

#घोषणा VCMPEQUD_RC(vrt, vra, vrb)	stringअगरy_in_c(.दीर्घ PPC_RAW_VCMPEQUD_RC(vrt, vra, vrb))

#घोषणा VCMPEQUB_RC(vrt, vra, vrb)	stringअगरy_in_c(.दीर्घ PPC_RAW_VCMPEQUB_RC(vrt, vra, vrb))

#पूर्ण_अगर /* _ASM_POWERPC_PPC_OPCODE_H */
