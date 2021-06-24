<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * SPR Definitions
 *
 * Copyright (C) 2000 Damjan Lampret
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2008, 2010 Embecosm Limited
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 *
 * This file is part of OpenRISC 1000 Architectural Simulator.
 */

#अगर_अघोषित SPR_DEFS__H
#घोषणा SPR_DEFS__H

/* Definition of special-purpose रेजिस्टरs (SPRs). */

#घोषणा MAX_GRPS (32)
#घोषणा MAX_SPRS_PER_GRP_BITS (11)
#घोषणा MAX_SPRS_PER_GRP (1 << MAX_SPRS_PER_GRP_BITS)
#घोषणा MAX_SPRS (0x10000)

/* Base addresses क्रम the groups */
#घोषणा SPRGROUP_SYS	(0 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_DMMU	(1 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_IMMU	(2 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_DC	(3 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_IC	(4 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_MAC	(5 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_D	(6 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_PC	(7 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_PM	(8 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_PIC	(9 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_TT	(10 << MAX_SPRS_PER_GRP_BITS)
#घोषणा SPRGROUP_FP	(11 << MAX_SPRS_PER_GRP_BITS)

/* System control and status group */
#घोषणा SPR_VR		(SPRGROUP_SYS + 0)
#घोषणा SPR_UPR		(SPRGROUP_SYS + 1)
#घोषणा SPR_CPUCFGR	(SPRGROUP_SYS + 2)
#घोषणा SPR_DMMUCFGR	(SPRGROUP_SYS + 3)
#घोषणा SPR_IMMUCFGR	(SPRGROUP_SYS + 4)
#घोषणा SPR_DCCFGR	(SPRGROUP_SYS + 5)
#घोषणा SPR_ICCFGR	(SPRGROUP_SYS + 6)
#घोषणा SPR_DCFGR	(SPRGROUP_SYS + 7)
#घोषणा SPR_PCCFGR	(SPRGROUP_SYS + 8)
#घोषणा SPR_VR2		(SPRGROUP_SYS + 9)
#घोषणा SPR_AVR		(SPRGROUP_SYS + 10)
#घोषणा SPR_EVBAR	(SPRGROUP_SYS + 11)
#घोषणा SPR_AECR	(SPRGROUP_SYS + 12)
#घोषणा SPR_AESR	(SPRGROUP_SYS + 13)
#घोषणा SPR_NPC         (SPRGROUP_SYS + 16)  /* CZ 21/06/01 */
#घोषणा SPR_SR		(SPRGROUP_SYS + 17)  /* CZ 21/06/01 */
#घोषणा SPR_PPC         (SPRGROUP_SYS + 18)  /* CZ 21/06/01 */
#घोषणा SPR_FPCSR       (SPRGROUP_SYS + 20)  /* CZ 21/06/01 */
#घोषणा SPR_EPCR_BASE	(SPRGROUP_SYS + 32)  /* CZ 21/06/01 */
#घोषणा SPR_EPCR_LAST	(SPRGROUP_SYS + 47)  /* CZ 21/06/01 */
#घोषणा SPR_EEAR_BASE	(SPRGROUP_SYS + 48)
#घोषणा SPR_EEAR_LAST	(SPRGROUP_SYS + 63)
#घोषणा SPR_ESR_BASE	(SPRGROUP_SYS + 64)
#घोषणा SPR_ESR_LAST	(SPRGROUP_SYS + 79)
#घोषणा SPR_COREID	(SPRGROUP_SYS + 128)
#घोषणा SPR_NUMCORES	(SPRGROUP_SYS + 129)
#घोषणा SPR_GPR_BASE	(SPRGROUP_SYS + 1024)

/* Data MMU group */
#घोषणा SPR_DMMUCR	(SPRGROUP_DMMU + 0)
#घोषणा SPR_DTLBEIR	(SPRGROUP_DMMU + 2)
#घोषणा SPR_DTLBMR_BASE(WAY)	(SPRGROUP_DMMU + 0x200 + (WAY) * 0x100)
#घोषणा SPR_DTLBMR_LAST(WAY)	(SPRGROUP_DMMU + 0x27f + (WAY) * 0x100)
#घोषणा SPR_DTLBTR_BASE(WAY)	(SPRGROUP_DMMU + 0x280 + (WAY) * 0x100)
#घोषणा SPR_DTLBTR_LAST(WAY)	(SPRGROUP_DMMU + 0x2ff + (WAY) * 0x100)

/* Inकाष्ठाion MMU group */
#घोषणा SPR_IMMUCR	(SPRGROUP_IMMU + 0)
#घोषणा SPR_ITLBEIR	(SPRGROUP_IMMU + 2)
#घोषणा SPR_ITLBMR_BASE(WAY)	(SPRGROUP_IMMU + 0x200 + (WAY) * 0x100)
#घोषणा SPR_ITLBMR_LAST(WAY)	(SPRGROUP_IMMU + 0x27f + (WAY) * 0x100)
#घोषणा SPR_ITLBTR_BASE(WAY)	(SPRGROUP_IMMU + 0x280 + (WAY) * 0x100)
#घोषणा SPR_ITLBTR_LAST(WAY)	(SPRGROUP_IMMU + 0x2ff + (WAY) * 0x100)

/* Data cache group */
#घोषणा SPR_DCCR	(SPRGROUP_DC + 0)
#घोषणा SPR_DCBPR	(SPRGROUP_DC + 1)
#घोषणा SPR_DCBFR	(SPRGROUP_DC + 2)
#घोषणा SPR_DCBIR	(SPRGROUP_DC + 3)
#घोषणा SPR_DCBWR	(SPRGROUP_DC + 4)
#घोषणा SPR_DCBLR	(SPRGROUP_DC + 5)
#घोषणा SPR_DCR_BASE(WAY)	(SPRGROUP_DC + 0x200 + (WAY) * 0x200)
#घोषणा SPR_DCR_LAST(WAY)	(SPRGROUP_DC + 0x3ff + (WAY) * 0x200)

/* Inकाष्ठाion cache group */
#घोषणा SPR_ICCR	(SPRGROUP_IC + 0)
#घोषणा SPR_ICBPR	(SPRGROUP_IC + 1)
#घोषणा SPR_ICBIR	(SPRGROUP_IC + 2)
#घोषणा SPR_ICBLR	(SPRGROUP_IC + 3)
#घोषणा SPR_ICR_BASE(WAY)	(SPRGROUP_IC + 0x200 + (WAY) * 0x200)
#घोषणा SPR_ICR_LAST(WAY)	(SPRGROUP_IC + 0x3ff + (WAY) * 0x200)

/* MAC group */
#घोषणा SPR_MACLO	(SPRGROUP_MAC + 1)
#घोषणा SPR_MACHI	(SPRGROUP_MAC + 2)

/* Debug group */
#घोषणा SPR_DVR(N)	(SPRGROUP_D + (N))
#घोषणा SPR_DCR(N)	(SPRGROUP_D + 8 + (N))
#घोषणा SPR_DMR1	(SPRGROUP_D + 16)
#घोषणा SPR_DMR2	(SPRGROUP_D + 17)
#घोषणा SPR_DWCR0	(SPRGROUP_D + 18)
#घोषणा SPR_DWCR1	(SPRGROUP_D + 19)
#घोषणा SPR_DSR		(SPRGROUP_D + 20)
#घोषणा SPR_DRR		(SPRGROUP_D + 21)

/* Perक्रमmance counters group */
#घोषणा SPR_PCCR(N)	(SPRGROUP_PC + (N))
#घोषणा SPR_PCMR(N)	(SPRGROUP_PC + 8 + (N))

/* Power management group */
#घोषणा SPR_PMR (SPRGROUP_PM + 0)

/* PIC group */
#घोषणा SPR_PICMR (SPRGROUP_PIC + 0)
#घोषणा SPR_PICPR (SPRGROUP_PIC + 1)
#घोषणा SPR_PICSR (SPRGROUP_PIC + 2)

/* Tick Timer group */
#घोषणा SPR_TTMR (SPRGROUP_TT + 0)
#घोषणा SPR_TTCR (SPRGROUP_TT + 1)

/*
 * Bit definitions क्रम the Version Register
 *
 */
#घोषणा SPR_VR_VER	0xff000000  /* Processor version */
#घोषणा SPR_VR_CFG	0x00ff0000  /* Processor configuration */
#घोषणा SPR_VR_RES	0x0000ffc0  /* Reserved */
#घोषणा SPR_VR_REV	0x0000003f  /* Processor revision */
#घोषणा SPR_VR_UVRP	0x00000040  /* Updated Version Registers Present */

#घोषणा SPR_VR_VER_OFF	24
#घोषणा SPR_VR_CFG_OFF	16
#घोषणा SPR_VR_REV_OFF	0

/*
 * Bit definitions क्रम the Version Register 2
 */
#घोषणा SPR_VR2_CPUID	0xff000000  /* Processor ID */
#घोषणा SPR_VR2_VER	0x00ffffff  /* Processor version */

/*
 * Bit definitions क्रम the Unit Present Register
 *
 */
#घोषणा SPR_UPR_UP	   0x00000001  /* UPR present */
#घोषणा SPR_UPR_DCP	   0x00000002  /* Data cache present */
#घोषणा SPR_UPR_ICP	   0x00000004  /* Inकाष्ठाion cache present */
#घोषणा SPR_UPR_DMP	   0x00000008  /* Data MMU present */
#घोषणा SPR_UPR_IMP	   0x00000010  /* Inकाष्ठाion MMU present */
#घोषणा SPR_UPR_MP	   0x00000020  /* MAC present */
#घोषणा SPR_UPR_DUP	   0x00000040  /* Debug unit present */
#घोषणा SPR_UPR_PCUP	   0x00000080  /* Perक्रमmance counters unit present */
#घोषणा SPR_UPR_PICP	   0x00000100  /* PIC present */
#घोषणा SPR_UPR_PMP	   0x00000200  /* Power management present */
#घोषणा SPR_UPR_TTP	   0x00000400  /* Tick समयr present */
#घोषणा SPR_UPR_RES	   0x00fe0000  /* Reserved */
#घोषणा SPR_UPR_CUP	   0xff000000  /* Context units present */

/*
 * JPB: Bit definitions क्रम the CPU configuration रेजिस्टर
 *
 */
#घोषणा SPR_CPUCFGR_NSGF   0x0000000f  /* Number of shaकरोw GPR files */
#घोषणा SPR_CPUCFGR_CGF	   0x00000010  /* Custom GPR file */
#घोषणा SPR_CPUCFGR_OB32S  0x00000020  /* ORBIS32 supported */
#घोषणा SPR_CPUCFGR_OB64S  0x00000040  /* ORBIS64 supported */
#घोषणा SPR_CPUCFGR_OF32S  0x00000080  /* ORFPX32 supported */
#घोषणा SPR_CPUCFGR_OF64S  0x00000100  /* ORFPX64 supported */
#घोषणा SPR_CPUCFGR_OV64S  0x00000200  /* ORVDX64 supported */
#घोषणा SPR_CPUCFGR_RES	   0xfffffc00  /* Reserved */

/*
 * JPB: Bit definitions क्रम the Debug configuration रेजिस्टर and other
 * स्थिरants.
 *
 */

#घोषणा SPR_DCFGR_NDP      0x00000007  /* Number of matchpoपूर्णांकs mask */
#घोषणा SPR_DCFGR_NDP1     0x00000000  /* One matchpoपूर्णांक supported */
#घोषणा SPR_DCFGR_NDP2     0x00000001  /* Two matchpoपूर्णांकs supported */
#घोषणा SPR_DCFGR_NDP3     0x00000002  /* Three matchpoपूर्णांकs supported */
#घोषणा SPR_DCFGR_NDP4     0x00000003  /* Four matchpoपूर्णांकs supported */
#घोषणा SPR_DCFGR_NDP5     0x00000004  /* Five matchpoपूर्णांकs supported */
#घोषणा SPR_DCFGR_NDP6     0x00000005  /* Six matchpoपूर्णांकs supported */
#घोषणा SPR_DCFGR_NDP7     0x00000006  /* Seven matchpoपूर्णांकs supported */
#घोषणा SPR_DCFGR_NDP8     0x00000007  /* Eight matchpoपूर्णांकs supported */
#घोषणा SPR_DCFGR_WPCI     0x00000008  /* Watchpoपूर्णांक counters implemented */

#घोषणा MATCHPOINTS_TO_NDP(n) (1 == n ? SPR_DCFGR_NDP1 : \
                               2 == n ? SPR_DCFGR_NDP2 : \
                               3 == n ? SPR_DCFGR_NDP3 : \
                               4 == n ? SPR_DCFGR_NDP4 : \
                               5 == n ? SPR_DCFGR_NDP5 : \
                               6 == n ? SPR_DCFGR_NDP6 : \
                               7 == n ? SPR_DCFGR_NDP7 : SPR_DCFGR_NDP8)
#घोषणा MAX_MATCHPOINTS  8
#घोषणा MAX_WATCHPOINTS  (MAX_MATCHPOINTS + 2)

/*
 * Bit definitions क्रम the Supervision Register
 *
 */
#घोषणा SPR_SR_SM          0x00000001  /* Supervisor Mode */
#घोषणा SPR_SR_TEE         0x00000002  /* Tick समयr Exception Enable */
#घोषणा SPR_SR_IEE         0x00000004  /* Interrupt Exception Enable */
#घोषणा SPR_SR_DCE         0x00000008  /* Data Cache Enable */
#घोषणा SPR_SR_ICE         0x00000010  /* Inकाष्ठाion Cache Enable */
#घोषणा SPR_SR_DME         0x00000020  /* Data MMU Enable */
#घोषणा SPR_SR_IME         0x00000040  /* Inकाष्ठाion MMU Enable */
#घोषणा SPR_SR_LEE         0x00000080  /* Little Endian Enable */
#घोषणा SPR_SR_CE          0x00000100  /* CID Enable */
#घोषणा SPR_SR_F           0x00000200  /* Condition Flag */
#घोषणा SPR_SR_CY          0x00000400  /* Carry flag */
#घोषणा SPR_SR_OV          0x00000800  /* Overflow flag */
#घोषणा SPR_SR_OVE         0x00001000  /* Overflow flag Exception */
#घोषणा SPR_SR_DSX         0x00002000  /* Delay Slot Exception */
#घोषणा SPR_SR_EPH         0x00004000  /* Exception Prefix High */
#घोषणा SPR_SR_FO          0x00008000  /* Fixed one */
#घोषणा SPR_SR_SUMRA       0x00010000  /* Supervisor SPR पढ़ो access */
#घोषणा SPR_SR_RES         0x0ffe0000  /* Reserved */
#घोषणा SPR_SR_CID         0xf0000000  /* Context ID */

/*
 * Bit definitions क्रम the Data MMU Control Register
 *
 */
#घोषणा SPR_DMMUCR_P2S	   0x0000003e  /* Level 2 Page Size */
#घोषणा SPR_DMMUCR_P1S	   0x000007c0  /* Level 1 Page Size */
#घोषणा SPR_DMMUCR_VADDR_WIDTH	0x0000f800  /* Virtual ADDR Width */
#घोषणा SPR_DMMUCR_PADDR_WIDTH	0x000f0000  /* Physical ADDR Width */

/*
 * Bit definitions क्रम the Inकाष्ठाion MMU Control Register
 *
 */
#घोषणा SPR_IMMUCR_P2S	   0x0000003e  /* Level 2 Page Size */
#घोषणा SPR_IMMUCR_P1S	   0x000007c0  /* Level 1 Page Size */
#घोषणा SPR_IMMUCR_VADDR_WIDTH	0x0000f800  /* Virtual ADDR Width */
#घोषणा SPR_IMMUCR_PADDR_WIDTH	0x000f0000  /* Physical ADDR Width */

/*
 * Bit definitions क्रम the Data TLB Match Register
 *
 */
#घोषणा SPR_DTLBMR_V	   0x00000001  /* Valid */
#घोषणा SPR_DTLBMR_PL1	   0x00000002  /* Page Level 1 (अगर 0 then PL2) */
#घोषणा SPR_DTLBMR_CID	   0x0000003c  /* Context ID */
#घोषणा SPR_DTLBMR_LRU	   0x000000c0  /* Least Recently Used */
#घोषणा SPR_DTLBMR_VPN	   0xfffff000  /* Virtual Page Number */

/*
 * Bit definitions क्रम the Data TLB Translate Register
 *
 */
#घोषणा SPR_DTLBTR_CC	   0x00000001  /* Cache Coherency */
#घोषणा SPR_DTLBTR_CI	   0x00000002  /* Cache Inhibit */
#घोषणा SPR_DTLBTR_WBC	   0x00000004  /* Write-Back Cache */
#घोषणा SPR_DTLBTR_WOM	   0x00000008  /* Weakly-Ordered Memory */
#घोषणा SPR_DTLBTR_A	   0x00000010  /* Accessed */
#घोषणा SPR_DTLBTR_D	   0x00000020  /* Dirty */
#घोषणा SPR_DTLBTR_URE	   0x00000040  /* User Read Enable */
#घोषणा SPR_DTLBTR_UWE	   0x00000080  /* User Write Enable */
#घोषणा SPR_DTLBTR_SRE	   0x00000100  /* Supervisor Read Enable */
#घोषणा SPR_DTLBTR_SWE	   0x00000200  /* Supervisor Write Enable */
#घोषणा SPR_DTLBTR_PPN	   0xfffff000  /* Physical Page Number */

/*
 * Bit definitions क्रम the Inकाष्ठाion TLB Match Register
 *
 */
#घोषणा SPR_ITLBMR_V	   0x00000001  /* Valid */
#घोषणा SPR_ITLBMR_PL1	   0x00000002  /* Page Level 1 (अगर 0 then PL2) */
#घोषणा SPR_ITLBMR_CID	   0x0000003c  /* Context ID */
#घोषणा SPR_ITLBMR_LRU	   0x000000c0  /* Least Recently Used */
#घोषणा SPR_ITLBMR_VPN	   0xfffff000  /* Virtual Page Number */

/*
 * Bit definitions क्रम the Inकाष्ठाion TLB Translate Register
 *
 */
#घोषणा SPR_ITLBTR_CC	   0x00000001  /* Cache Coherency */
#घोषणा SPR_ITLBTR_CI	   0x00000002  /* Cache Inhibit */
#घोषणा SPR_ITLBTR_WBC	   0x00000004  /* Write-Back Cache */
#घोषणा SPR_ITLBTR_WOM	   0x00000008  /* Weakly-Ordered Memory */
#घोषणा SPR_ITLBTR_A	   0x00000010  /* Accessed */
#घोषणा SPR_ITLBTR_D	   0x00000020  /* Dirty */
#घोषणा SPR_ITLBTR_SXE	   0x00000040  /* User Read Enable */
#घोषणा SPR_ITLBTR_UXE	   0x00000080  /* User Write Enable */
#घोषणा SPR_ITLBTR_PPN	   0xfffff000  /* Physical Page Number */

/*
 * Bit definitions क्रम Data Cache Control रेजिस्टर
 *
 */
#घोषणा SPR_DCCR_EW	   0x000000ff  /* Enable ways */

/*
 * Bit definitions क्रम Insn Cache Control रेजिस्टर
 *
 */
#घोषणा SPR_ICCR_EW	   0x000000ff  /* Enable ways */

/*
 * Bit definitions क्रम Data Cache Configuration Register
 *
 */

#घोषणा SPR_DCCFGR_NCW		0x00000007
#घोषणा SPR_DCCFGR_NCS		0x00000078
#घोषणा SPR_DCCFGR_CBS		0x00000080
#घोषणा SPR_DCCFGR_CWS		0x00000100
#घोषणा SPR_DCCFGR_CCRI		0x00000200
#घोषणा SPR_DCCFGR_CBIRI	0x00000400
#घोषणा SPR_DCCFGR_CBPRI	0x00000800
#घोषणा SPR_DCCFGR_CBLRI	0x00001000
#घोषणा SPR_DCCFGR_CBFRI	0x00002000
#घोषणा SPR_DCCFGR_CBWBRI	0x00004000

#घोषणा SPR_DCCFGR_NCW_OFF      0
#घोषणा SPR_DCCFGR_NCS_OFF      3
#घोषणा SPR_DCCFGR_CBS_OFF	7

/*
 * Bit definitions क्रम Inकाष्ठाion Cache Configuration Register
 *
 */
#घोषणा SPR_ICCFGR_NCW		0x00000007
#घोषणा SPR_ICCFGR_NCS		0x00000078
#घोषणा SPR_ICCFGR_CBS		0x00000080
#घोषणा SPR_ICCFGR_CCRI		0x00000200
#घोषणा SPR_ICCFGR_CBIRI	0x00000400
#घोषणा SPR_ICCFGR_CBPRI	0x00000800
#घोषणा SPR_ICCFGR_CBLRI	0x00001000

#घोषणा SPR_ICCFGR_NCW_OFF      0
#घोषणा SPR_ICCFGR_NCS_OFF      3
#घोषणा SPR_ICCFGR_CBS_OFF	7

/*
 * Bit definitions क्रम Data MMU Configuration Register
 *
 */

#घोषणा SPR_DMMUCFGR_NTW	0x00000003
#घोषणा SPR_DMMUCFGR_NTS	0x0000001C
#घोषणा SPR_DMMUCFGR_NAE	0x000000E0
#घोषणा SPR_DMMUCFGR_CRI	0x00000100
#घोषणा SPR_DMMUCFGR_PRI        0x00000200
#घोषणा SPR_DMMUCFGR_TEIRI	0x00000400
#घोषणा SPR_DMMUCFGR_HTR	0x00000800

#घोषणा SPR_DMMUCFGR_NTW_OFF	0
#घोषणा SPR_DMMUCFGR_NTS_OFF	2

/*
 * Bit definitions क्रम Inकाष्ठाion MMU Configuration Register
 *
 */

#घोषणा SPR_IMMUCFGR_NTW	0x00000003
#घोषणा SPR_IMMUCFGR_NTS	0x0000001C
#घोषणा SPR_IMMUCFGR_NAE	0x000000E0
#घोषणा SPR_IMMUCFGR_CRI	0x00000100
#घोषणा SPR_IMMUCFGR_PRI	0x00000200
#घोषणा SPR_IMMUCFGR_TEIRI	0x00000400
#घोषणा SPR_IMMUCFGR_HTR	0x00000800

#घोषणा SPR_IMMUCFGR_NTW_OFF	0
#घोषणा SPR_IMMUCFGR_NTS_OFF	2

/*
 * Bit definitions क्रम Debug Control रेजिस्टरs
 *
 */
#घोषणा SPR_DCR_DP	0x00000001  /* DVR/DCR present */
#घोषणा SPR_DCR_CC	0x0000000e  /* Compare condition */
#घोषणा SPR_DCR_SC	0x00000010  /* Signed compare */
#घोषणा SPR_DCR_CT	0x000000e0  /* Compare to */

/* Bit results with SPR_DCR_CC mask */
#घोषणा SPR_DCR_CC_MASKED 0x00000000
#घोषणा SPR_DCR_CC_EQUAL  0x00000002
#घोषणा SPR_DCR_CC_LESS   0x00000004
#घोषणा SPR_DCR_CC_LESSE  0x00000006
#घोषणा SPR_DCR_CC_GREAT  0x00000008
#घोषणा SPR_DCR_CC_GREATE 0x0000000a
#घोषणा SPR_DCR_CC_NEQUAL 0x0000000c

/* Bit results with SPR_DCR_CT mask */
#घोषणा SPR_DCR_CT_DISABLED 0x00000000
#घोषणा SPR_DCR_CT_IFEA     0x00000020
#घोषणा SPR_DCR_CT_LEA      0x00000040
#घोषणा SPR_DCR_CT_SEA      0x00000060
#घोषणा SPR_DCR_CT_LD       0x00000080
#घोषणा SPR_DCR_CT_SD       0x000000a0
#घोषणा SPR_DCR_CT_LSEA     0x000000c0
#घोषणा SPR_DCR_CT_LSD	    0x000000e0
/* SPR_DCR_CT_LSD करोesn't seem to be implemented anywhere in or1ksim. 2004-1-30 HP */

/*
 * Bit definitions क्रम Debug Mode 1 रेजिस्टर
 *
 */
#घोषणा SPR_DMR1_CW       0x000fffff  /* Chain रेजिस्टर pair data */
#घोषणा SPR_DMR1_CW0_AND  0x00000001
#घोषणा SPR_DMR1_CW0_OR   0x00000002
#घोषणा SPR_DMR1_CW0      (SPR_DMR1_CW0_AND | SPR_DMR1_CW0_OR)
#घोषणा SPR_DMR1_CW1_AND  0x00000004
#घोषणा SPR_DMR1_CW1_OR   0x00000008
#घोषणा SPR_DMR1_CW1      (SPR_DMR1_CW1_AND | SPR_DMR1_CW1_OR)
#घोषणा SPR_DMR1_CW2_AND  0x00000010
#घोषणा SPR_DMR1_CW2_OR   0x00000020
#घोषणा SPR_DMR1_CW2      (SPR_DMR1_CW2_AND | SPR_DMR1_CW2_OR)
#घोषणा SPR_DMR1_CW3_AND  0x00000040
#घोषणा SPR_DMR1_CW3_OR   0x00000080
#घोषणा SPR_DMR1_CW3      (SPR_DMR1_CW3_AND | SPR_DMR1_CW3_OR)
#घोषणा SPR_DMR1_CW4_AND  0x00000100
#घोषणा SPR_DMR1_CW4_OR   0x00000200
#घोषणा SPR_DMR1_CW4      (SPR_DMR1_CW4_AND | SPR_DMR1_CW4_OR)
#घोषणा SPR_DMR1_CW5_AND  0x00000400
#घोषणा SPR_DMR1_CW5_OR   0x00000800
#घोषणा SPR_DMR1_CW5      (SPR_DMR1_CW5_AND | SPR_DMR1_CW5_OR)
#घोषणा SPR_DMR1_CW6_AND  0x00001000
#घोषणा SPR_DMR1_CW6_OR   0x00002000
#घोषणा SPR_DMR1_CW6      (SPR_DMR1_CW6_AND | SPR_DMR1_CW6_OR)
#घोषणा SPR_DMR1_CW7_AND  0x00004000
#घोषणा SPR_DMR1_CW7_OR   0x00008000
#घोषणा SPR_DMR1_CW7      (SPR_DMR1_CW7_AND | SPR_DMR1_CW7_OR)
#घोषणा SPR_DMR1_CW8_AND  0x00010000
#घोषणा SPR_DMR1_CW8_OR   0x00020000
#घोषणा SPR_DMR1_CW8      (SPR_DMR1_CW8_AND | SPR_DMR1_CW8_OR)
#घोषणा SPR_DMR1_CW9_AND  0x00040000
#घोषणा SPR_DMR1_CW9_OR   0x00080000
#घोषणा SPR_DMR1_CW9      (SPR_DMR1_CW9_AND | SPR_DMR1_CW9_OR)
#घोषणा SPR_DMR1_RES1      0x00300000  /* Reserved */
#घोषणा SPR_DMR1_ST	  0x00400000  /* Single-step trace*/
#घोषणा SPR_DMR1_BT	  0x00800000  /* Branch trace */
#घोषणा SPR_DMR1_RES2	  0xff000000  /* Reserved */

/*
 * Bit definitions क्रम Debug Mode 2 रेजिस्टर. AWTC and WGB corrected by JPB
 *
 */
#घोषणा SPR_DMR2_WCE0	   0x00000001  /* Watchpoपूर्णांक counter 0 enable */
#घोषणा SPR_DMR2_WCE1	   0x00000002  /* Watchpoपूर्णांक counter 0 enable */
#घोषणा SPR_DMR2_AWTC	   0x00000ffc  /* Assign watchpoपूर्णांकs to counters */
#घोषणा SPR_DMR2_AWTC_OFF           2  /* Bit offset to AWTC field */
#घोषणा SPR_DMR2_WGB	   0x003ff000  /* Watchpoपूर्णांकs generating अवरोधpoपूर्णांक */
#घोषणा SPR_DMR2_WGB_OFF           12  /* Bit offset to WGB field */
#घोषणा SPR_DMR2_WBS	   0xffc00000  /* JPB: Watchpoपूर्णांक status */
#घोषणा SPR_DMR2_WBS_OFF           22  /* Bit offset to WBS field */

/*
 * Bit definitions क्रम Debug watchpoपूर्णांक counter रेजिस्टरs
 *
 */
#घोषणा SPR_DWCR_COUNT	    0x0000ffff  /* Count */
#घोषणा SPR_DWCR_MATCH	    0xffff0000  /* Match */
#घोषणा SPR_DWCR_MATCH_OFF          16  /* Match bit offset */

/*
 * Bit definitions क्रम Debug stop रेजिस्टर
 *
 */
#घोषणा SPR_DSR_RSTE	0x00000001  /* Reset exception */
#घोषणा SPR_DSR_BUSEE	0x00000002  /* Bus error exception */
#घोषणा SPR_DSR_DPFE	0x00000004  /* Data Page Fault exception */
#घोषणा SPR_DSR_IPFE	0x00000008  /* Insn Page Fault exception */
#घोषणा SPR_DSR_TTE	0x00000010  /* Tick Timer exception */
#घोषणा SPR_DSR_AE	0x00000020  /* Alignment exception */
#घोषणा SPR_DSR_IIE	0x00000040  /* Illegal Inकाष्ठाion exception */
#घोषणा SPR_DSR_IE	0x00000080  /* Interrupt exception */
#घोषणा SPR_DSR_DME	0x00000100  /* DTLB miss exception */
#घोषणा SPR_DSR_IME	0x00000200  /* ITLB miss exception */
#घोषणा SPR_DSR_RE	0x00000400  /* Range exception */
#घोषणा SPR_DSR_SCE	0x00000800  /* System call exception */
#घोषणा SPR_DSR_FPE     0x00001000  /* Floating Poपूर्णांक Exception */
#घोषणा SPR_DSR_TE	0x00002000  /* Trap exception */

/*
 * Bit definitions क्रम Debug reason रेजिस्टर
 *
 */
#घोषणा SPR_DRR_RSTE	0x00000001  /* Reset exception */
#घोषणा SPR_DRR_BUSEE	0x00000002  /* Bus error exception */
#घोषणा SPR_DRR_DPFE	0x00000004  /* Data Page Fault exception */
#घोषणा SPR_DRR_IPFE	0x00000008  /* Insn Page Fault exception */
#घोषणा SPR_DRR_TTE	0x00000010  /* Tick Timer exception */
#घोषणा SPR_DRR_AE	0x00000020  /* Alignment exception */
#घोषणा SPR_DRR_IIE	0x00000040  /* Illegal Inकाष्ठाion exception */
#घोषणा SPR_DRR_IE	0x00000080  /* Interrupt exception */
#घोषणा SPR_DRR_DME	0x00000100  /* DTLB miss exception */
#घोषणा SPR_DRR_IME	0x00000200  /* ITLB miss exception */
#घोषणा SPR_DRR_RE	0x00000400  /* Range exception */
#घोषणा SPR_DRR_SCE	0x00000800  /* System call exception */
#घोषणा SPR_DRR_FPE     0x00001000  /* Floating Poपूर्णांक Exception */
#घोषणा SPR_DRR_TE	0x00002000  /* Trap exception */

/*
 * Bit definitions क्रम Perक्रमmance counters mode रेजिस्टरs
 *
 */
#घोषणा SPR_PCMR_CP	0x00000001  /* Counter present */
#घोषणा SPR_PCMR_UMRA	0x00000002  /* User mode पढ़ो access */
#घोषणा SPR_PCMR_CISM	0x00000004  /* Count in supervisor mode */
#घोषणा SPR_PCMR_CIUM	0x00000008  /* Count in user mode */
#घोषणा SPR_PCMR_LA	0x00000010  /* Load access event */
#घोषणा SPR_PCMR_SA	0x00000020  /* Store access event */
#घोषणा SPR_PCMR_IF	0x00000040  /* Inकाष्ठाion fetch event*/
#घोषणा SPR_PCMR_DCM	0x00000080  /* Data cache miss event */
#घोषणा SPR_PCMR_ICM	0x00000100  /* Insn cache miss event */
#घोषणा SPR_PCMR_IFS	0x00000200  /* Insn fetch stall event */
#घोषणा SPR_PCMR_LSUS	0x00000400  /* LSU stall event */
#घोषणा SPR_PCMR_BS	0x00000800  /* Branch stall event */
#घोषणा SPR_PCMR_DTLBM	0x00001000  /* DTLB miss event */
#घोषणा SPR_PCMR_ITLBM	0x00002000  /* ITLB miss event */
#घोषणा SPR_PCMR_DDS	0x00004000  /* Data dependency stall event */
#घोषणा SPR_PCMR_WPE	0x03ff8000  /* Watchpoपूर्णांक events */

/*
 * Bit definitions क्रम the Power management रेजिस्टर
 *
 */
#घोषणा SPR_PMR_SDF	0x0000000f  /* Slow करोwn factor */
#घोषणा SPR_PMR_DME	0x00000010  /* Doze mode enable */
#घोषणा SPR_PMR_SME	0x00000020  /* Sleep mode enable */
#घोषणा SPR_PMR_DCGE	0x00000040  /* Dynamic घड़ी gating enable */
#घोषणा SPR_PMR_SUME	0x00000080  /* Suspend mode enable */

/*
 * Bit definitions क्रम PICMR
 *
 */
#घोषणा SPR_PICMR_IUM	0xfffffffc  /* Interrupt unmask */

/*
 * Bit definitions क्रम PICPR
 *
 */
#घोषणा SPR_PICPR_IPRIO	0xfffffffc  /* Interrupt priority */

/*
 * Bit definitions क्रम PICSR
 *
 */
#घोषणा SPR_PICSR_IS	0xffffffff  /* Interrupt status */

/*
 * Bit definitions क्रम Tick Timer Control Register
 *
 */

#घोषणा SPR_TTCR_CNT	0xffffffff  /* Count, समय period */
#घोषणा SPR_TTMR_TP	0x0fffffff  /* Time period */
#घोषणा SPR_TTMR_IP	0x10000000  /* Interrupt Pending */
#घोषणा SPR_TTMR_IE	0x20000000  /* Interrupt Enable */
#घोषणा SPR_TTMR_DI	0x00000000  /* Disabled */
#घोषणा SPR_TTMR_RT	0x40000000  /* Restart tick */
#घोषणा SPR_TTMR_SR     0x80000000  /* Single run */
#घोषणा SPR_TTMR_CR     0xc0000000  /* Continuous run */
#घोषणा SPR_TTMR_M      0xc0000000  /* Tick mode */

/*
 * Bit definitions क्रम the FP Control Status Register
 *
 */
#घोषणा SPR_FPCSR_FPEE  0x00000001  /* Floating Poपूर्णांक Exception Enable */
#घोषणा SPR_FPCSR_RM    0x00000006  /* Rounding Mode */
#घोषणा SPR_FPCSR_OVF   0x00000008  /* Overflow Flag */
#घोषणा SPR_FPCSR_UNF   0x00000010  /* Underflow Flag */
#घोषणा SPR_FPCSR_SNF   0x00000020  /* Sन_अंक Flag */
#घोषणा SPR_FPCSR_QNF   0x00000040  /* Qन_अंक Flag */
#घोषणा SPR_FPCSR_ZF    0x00000080  /* Zero Flag */
#घोषणा SPR_FPCSR_IXF   0x00000100  /* Inexact Flag */
#घोषणा SPR_FPCSR_IVF   0x00000200  /* Invalid Flag */
#घोषणा SPR_FPCSR_INF   0x00000400  /* Infinity Flag */
#घोषणा SPR_FPCSR_DZF   0x00000800  /* Divide By Zero Flag */
#घोषणा SPR_FPCSR_ALLF (SPR_FPCSR_OVF | SPR_FPCSR_UNF | SPR_FPCSR_SNF | \
			SPR_FPCSR_QNF | SPR_FPCSR_ZF | SPR_FPCSR_IXF |  \
			SPR_FPCSR_IVF | SPR_FPCSR_INF | SPR_FPCSR_DZF)

#घोषणा FPCSR_RM_RN (0<<1)
#घोषणा FPCSR_RM_RZ (1<<1)
#घोषणा FPCSR_RM_RIP (2<<1)
#घोषणा FPCSR_RM_RIN (3<<1)

/*
 * l.nop स्थिरants
 *
 */
#घोषणा NOP_NOP          0x0000      /* Normal nop inकाष्ठाion */
#घोषणा NOP_EXIT         0x0001      /* End of simulation */
#घोषणा NOP_REPORT       0x0002      /* Simple report */
/*#घोषणा NOP_PRINTF       0x0003       Simम_लिखो inकाष्ठाion (obsolete)*/
#घोषणा NOP_PUTC         0x0004      /* JPB: Simअ_दो inकाष्ठाion */
#घोषणा NOP_CNT_RESET    0x0005	     /* Reset statistics counters */
#घोषणा NOP_GET_TICKS    0x0006	     /* JPB: Get # ticks running */
#घोषणा NOP_GET_PS       0x0007      /* JPB: Get picosecs/cycle */
#घोषणा NOP_REPORT_FIRST 0x0400      /* Report with number */
#घोषणा NOP_REPORT_LAST  0x03ff      /* Report with number */

#पूर्ण_अगर	/* SPR_DEFS__H */
