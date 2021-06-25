<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Register definitions specअगरic to the A2 core
 *
 *  Copyright (C) 2008 Ben. Herrenschmidt (benh@kernel.crashing.org), IBM Corp.
 */

#अगर_अघोषित __ASM_POWERPC_REG_A2_H__
#घोषणा __ASM_POWERPC_REG_A2_H__

#समावेश <यंत्र/यंत्र-स्थिर.h>

#घोषणा SPRN_TENSR	0x1b5
#घोषणा SPRN_TENS	0x1b6	/* Thपढ़ो ENable Set */
#घोषणा SPRN_TENC	0x1b7	/* Thपढ़ो ENable Clear */

#घोषणा SPRN_A2_CCR0	0x3f0	/* Core Configuration Register 0 */
#घोषणा SPRN_A2_CCR1	0x3f1	/* Core Configuration Register 1 */
#घोषणा SPRN_A2_CCR2	0x3f2	/* Core Configuration Register 2 */
#घोषणा SPRN_MMUCR0	0x3fc	/* MMU Control Register 0 */
#घोषणा SPRN_MMUCR1	0x3fd	/* MMU Control Register 1 */
#घोषणा SPRN_MMUCR2	0x3fe	/* MMU Control Register 2 */
#घोषणा SPRN_MMUCR3	0x3ff	/* MMU Control Register 3 */

#घोषणा SPRN_IAR	0x372

#घोषणा SPRN_IUCR0	0x3f3
#घोषणा IUCR0_ICBI_ACK	0x1000

#घोषणा SPRN_XUCR0	0x3f6	/* Execution Unit Config Register 0 */

#घोषणा A2_IERAT_SIZE	16
#घोषणा A2_DERAT_SIZE	32

/* A2 MMUCR0 bits */
#घोषणा MMUCR0_ECL	0x80000000	/* Extended Class क्रम TLB fills */
#घोषणा MMUCR0_TID_NZ	0x40000000	/* TID is non-zero */
#घोषणा MMUCR0_TS	0x10000000	/* Translation space क्रम TLB fills */
#घोषणा MMUCR0_TGS	0x20000000	/* Guest space क्रम TLB fills */
#घोषणा MMUCR0_TLBSEL	0x0c000000	/* TLB or ERAT target क्रम TLB fills */
#घोषणा MMUCR0_TLBSEL_U	0x00000000	/*  TLBSEL = UTLB */
#घोषणा MMUCR0_TLBSEL_I	0x08000000	/*  TLBSEL = I-ERAT */
#घोषणा MMUCR0_TLBSEL_D	0x0c000000	/*  TLBSEL = D-ERAT */
#घोषणा MMUCR0_LOCKSRSH	0x02000000	/* Use TLB lock on tlbsx. */
#घोषणा MMUCR0_TID_MASK	0x000000ff	/* TID field */

/* A2 MMUCR1 bits */
#घोषणा MMUCR1_IRRE		0x80000000	/* I-ERAT round robin enable */
#घोषणा MMUCR1_DRRE		0x40000000	/* D-ERAT round robin enable */
#घोषणा MMUCR1_REE		0x20000000	/* Reference Exception Enable*/
#घोषणा MMUCR1_CEE		0x10000000	/* Change exception enable */
#घोषणा MMUCR1_CSINV_ALL	0x00000000	/* Inval ERAT on all CS evts */
#घोषणा MMUCR1_CSINV_NISYNC	0x04000000	/* Inval ERAT on all ex isync*/
#घोषणा MMUCR1_CSINV_NEVER	0x0c000000	/* Don't inval ERAT on CS */
#घोषणा MMUCR1_ICTID		0x00080000	/* IERAT class field as TID */
#घोषणा MMUCR1_ITTID		0x00040000	/* IERAT thdid field as TID */
#घोषणा MMUCR1_DCTID		0x00020000	/* DERAT class field as TID */
#घोषणा MMUCR1_DTTID		0x00010000	/* DERAT thdid field as TID */
#घोषणा MMUCR1_DCCD		0x00008000	/* DERAT class ignore */
#घोषणा MMUCR1_TLBWE_BINV	0x00004000	/* back invalidate on tlbwe */

/* A2 MMUCR2 bits */
#घोषणा MMUCR2_PSSEL_SHIFT	4

/* A2 MMUCR3 bits */
#घोषणा MMUCR3_THID		0x0000000f	/* Thपढ़ो ID */

/* *** ERAT TLB bits definitions */
#घोषणा TLB0_EPN_MASK		ASM_CONST(0xfffffffffffff000)
#घोषणा TLB0_CLASS_MASK		ASM_CONST(0x0000000000000c00)
#घोषणा TLB0_CLASS_00		ASM_CONST(0x0000000000000000)
#घोषणा TLB0_CLASS_01		ASM_CONST(0x0000000000000400)
#घोषणा TLB0_CLASS_10		ASM_CONST(0x0000000000000800)
#घोषणा TLB0_CLASS_11		ASM_CONST(0x0000000000000c00)
#घोषणा TLB0_V			ASM_CONST(0x0000000000000200)
#घोषणा TLB0_X			ASM_CONST(0x0000000000000100)
#घोषणा TLB0_SIZE_MASK		ASM_CONST(0x00000000000000f0)
#घोषणा TLB0_SIZE_4K		ASM_CONST(0x0000000000000010)
#घोषणा TLB0_SIZE_64K		ASM_CONST(0x0000000000000030)
#घोषणा TLB0_SIZE_1M		ASM_CONST(0x0000000000000050)
#घोषणा TLB0_SIZE_16M		ASM_CONST(0x0000000000000070)
#घोषणा TLB0_SIZE_1G		ASM_CONST(0x00000000000000a0)
#घोषणा TLB0_THDID_MASK		ASM_CONST(0x000000000000000f)
#घोषणा TLB0_THDID_0		ASM_CONST(0x0000000000000001)
#घोषणा TLB0_THDID_1		ASM_CONST(0x0000000000000002)
#घोषणा TLB0_THDID_2		ASM_CONST(0x0000000000000004)
#घोषणा TLB0_THDID_3		ASM_CONST(0x0000000000000008)
#घोषणा TLB0_THDID_ALL		ASM_CONST(0x000000000000000f)

#घोषणा TLB1_RESVATTR		ASM_CONST(0x00f0000000000000)
#घोषणा TLB1_U0			ASM_CONST(0x0008000000000000)
#घोषणा TLB1_U1			ASM_CONST(0x0004000000000000)
#घोषणा TLB1_U2			ASM_CONST(0x0002000000000000)
#घोषणा TLB1_U3			ASM_CONST(0x0001000000000000)
#घोषणा TLB1_R			ASM_CONST(0x0000800000000000)
#घोषणा TLB1_C			ASM_CONST(0x0000400000000000)
#घोषणा TLB1_RPN_MASK		ASM_CONST(0x000003fffffff000)
#घोषणा TLB1_W			ASM_CONST(0x0000000000000800)
#घोषणा TLB1_I			ASM_CONST(0x0000000000000400)
#घोषणा TLB1_M			ASM_CONST(0x0000000000000200)
#घोषणा TLB1_G			ASM_CONST(0x0000000000000100)
#घोषणा TLB1_E			ASM_CONST(0x0000000000000080)
#घोषणा TLB1_VF			ASM_CONST(0x0000000000000040)
#घोषणा TLB1_UX			ASM_CONST(0x0000000000000020)
#घोषणा TLB1_SX			ASM_CONST(0x0000000000000010)
#घोषणा TLB1_UW			ASM_CONST(0x0000000000000008)
#घोषणा TLB1_SW			ASM_CONST(0x0000000000000004)
#घोषणा TLB1_UR			ASM_CONST(0x0000000000000002)
#घोषणा TLB1_SR			ASM_CONST(0x0000000000000001)

/* A2 erativax attributes definitions */
#घोषणा ERATIVAX_RS_IS_ALL		0x000
#घोषणा ERATIVAX_RS_IS_TID		0x040
#घोषणा ERATIVAX_RS_IS_CLASS		0x080
#घोषणा ERATIVAX_RS_IS_FULLMATCH	0x0c0
#घोषणा ERATIVAX_CLASS_00		0x000
#घोषणा ERATIVAX_CLASS_01		0x010
#घोषणा ERATIVAX_CLASS_10		0x020
#घोषणा ERATIVAX_CLASS_11		0x030
#घोषणा ERATIVAX_PSIZE_4K		(TLB_PSIZE_4K >> 1)
#घोषणा ERATIVAX_PSIZE_64K		(TLB_PSIZE_64K >> 1)
#घोषणा ERATIVAX_PSIZE_1M		(TLB_PSIZE_1M >> 1)
#घोषणा ERATIVAX_PSIZE_16M		(TLB_PSIZE_16M >> 1)
#घोषणा ERATIVAX_PSIZE_1G		(TLB_PSIZE_1G >> 1)

/* A2 eratilx attributes definitions */
#घोषणा ERATILX_T_ALL			0
#घोषणा ERATILX_T_TID			1
#घोषणा ERATILX_T_TGS			2
#घोषणा ERATILX_T_FULLMATCH		3
#घोषणा ERATILX_T_CLASS0		4
#घोषणा ERATILX_T_CLASS1		5
#घोषणा ERATILX_T_CLASS2		6
#घोषणा ERATILX_T_CLASS3		7

/* XUCR0 bits */
#घोषणा XUCR0_TRACE_UM_T0		0x40000000	/* Thपढ़ो 0 */
#घोषणा XUCR0_TRACE_UM_T1		0x20000000	/* Thपढ़ो 1 */
#घोषणा XUCR0_TRACE_UM_T2		0x10000000	/* Thपढ़ो 2 */
#घोषणा XUCR0_TRACE_UM_T3		0x08000000	/* Thपढ़ो 3 */

/* A2 CCR0 रेजिस्टर */
#घोषणा A2_CCR0_PME_DISABLED		0x00000000
#घोषणा A2_CCR0_PME_SLEEP		0x40000000
#घोषणा A2_CCR0_PME_RVW			0x80000000
#घोषणा A2_CCR0_PME_DISABLED2		0xc0000000

/* A2 CCR2 रेजिस्टर */
#घोषणा A2_CCR2_ERAT_ONLY_MODE		0x00000001
#घोषणा A2_CCR2_ENABLE_ICSWX		0x00000002
#घोषणा A2_CCR2_ENABLE_PC		0x20000000
#घोषणा A2_CCR2_ENABLE_TRACE		0x40000000

#पूर्ण_अगर /* __ASM_POWERPC_REG_A2_H__ */
