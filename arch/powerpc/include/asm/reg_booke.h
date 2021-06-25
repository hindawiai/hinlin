<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Contains रेजिस्टर definitions common to the Book E PowerPC
 * specअगरication.  Notice that जबतक the IBM-40x series of CPUs
 * are not true Book E PowerPCs, they borrowed a number of features
 * beक्रमe Book E was finalized, and are included here as well.  Unक्रमtunately,
 * they someबार used dअगरferent locations than true Book E CPUs did.
 *
 * Copyright 2009-2010 Freescale Semiconductor, Inc.
 */
#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASM_POWERPC_REG_BOOKE_H__
#घोषणा __ASM_POWERPC_REG_BOOKE_H__

#समावेश <यंत्र/ppc-opcode.h>

/* Machine State Register (MSR) Fields */
#घोषणा MSR_GS_LG	28	/* Guest state */
#घोषणा MSR_UCLE_LG	26	/* User-mode cache lock enable */
#घोषणा MSR_SPE_LG	25	/* Enable SPE */
#घोषणा MSR_DWE_LG	10	/* Debug Wait Enable */
#घोषणा MSR_UBLE_LG	10	/* BTB lock enable (e500) */
#घोषणा MSR_IS_LG	MSR_IR_LG /* Inकाष्ठाion Space */
#घोषणा MSR_DS_LG	MSR_DR_LG /* Data Space */
#घोषणा MSR_PMM_LG	2	/* Perक्रमmance monitor mark bit */
#घोषणा MSR_CM_LG	31	/* Computation Mode (0=32-bit, 1=64-bit) */

#घोषणा MSR_GS		__MASK(MSR_GS_LG)
#घोषणा MSR_UCLE	__MASK(MSR_UCLE_LG)
#घोषणा MSR_SPE		__MASK(MSR_SPE_LG)
#घोषणा MSR_DWE		__MASK(MSR_DWE_LG)
#घोषणा MSR_UBLE	__MASK(MSR_UBLE_LG)
#घोषणा MSR_IS		__MASK(MSR_IS_LG)
#घोषणा MSR_DS		__MASK(MSR_DS_LG)
#घोषणा MSR_PMM		__MASK(MSR_PMM_LG)
#घोषणा MSR_CM		__MASK(MSR_CM_LG)

#अगर defined(CONFIG_PPC_BOOK3E_64)
#घोषणा MSR_64BIT	MSR_CM

#घोषणा MSR_		(MSR_ME | MSR_RI | MSR_CE)
#घोषणा MSR_KERNEL	(MSR_ | MSR_64BIT)
#घोषणा MSR_USER32	(MSR_ | MSR_PR | MSR_EE)
#घोषणा MSR_USER64	(MSR_USER32 | MSR_64BIT)
#या_अगर defined (CONFIG_40x)
#घोषणा MSR_KERNEL	(MSR_ME|MSR_RI|MSR_IR|MSR_DR|MSR_CE)
#घोषणा MSR_USER	(MSR_KERNEL|MSR_PR|MSR_EE)
#अन्यथा
#घोषणा MSR_KERNEL	(MSR_ME|MSR_RI|MSR_CE)
#घोषणा MSR_USER	(MSR_KERNEL|MSR_PR|MSR_EE)
#पूर्ण_अगर

/* Special Purpose Registers (SPRNs)*/
#घोषणा SPRN_DECAR	0x036	/* Decrementer Auto Reload Register */
#घोषणा SPRN_IVPR	0x03F	/* Interrupt Vector Prefix Register */
#घोषणा SPRN_USPRG0	0x100	/* User Special Purpose Register General 0 */
#घोषणा SPRN_SPRG3R	0x103	/* Special Purpose Register General 3 Read */
#घोषणा SPRN_SPRG4R	0x104	/* Special Purpose Register General 4 Read */
#घोषणा SPRN_SPRG5R	0x105	/* Special Purpose Register General 5 Read */
#घोषणा SPRN_SPRG6R	0x106	/* Special Purpose Register General 6 Read */
#घोषणा SPRN_SPRG7R	0x107	/* Special Purpose Register General 7 Read */
#घोषणा SPRN_SPRG4W	0x114	/* Special Purpose Register General 4 Write */
#घोषणा SPRN_SPRG5W	0x115	/* Special Purpose Register General 5 Write */
#घोषणा SPRN_SPRG6W	0x116	/* Special Purpose Register General 6 Write */
#घोषणा SPRN_SPRG7W	0x117	/* Special Purpose Register General 7 Write */
#घोषणा SPRN_EPCR	0x133	/* Embedded Processor Control Register */
#घोषणा SPRN_DBCR2	0x136	/* Debug Control Register 2 */
#घोषणा SPRN_DBCR4	0x233	/* Debug Control Register 4 */
#घोषणा SPRN_MSRP	0x137	/* MSR Protect Register */
#घोषणा SPRN_IAC3	0x13A	/* Inकाष्ठाion Address Compare 3 */
#घोषणा SPRN_IAC4	0x13B	/* Inकाष्ठाion Address Compare 4 */
#घोषणा SPRN_DVC1	0x13E	/* Data Value Compare Register 1 */
#घोषणा SPRN_DVC2	0x13F	/* Data Value Compare Register 2 */
#घोषणा SPRN_LPID	0x152	/* Logical Partition ID */
#घोषणा SPRN_MAS8	0x155	/* MMU Assist Register 8 */
#घोषणा SPRN_TLB0PS	0x158	/* TLB 0 Page Size Register */
#घोषणा SPRN_TLB1PS	0x159	/* TLB 1 Page Size Register */
#घोषणा SPRN_MAS5_MAS6	0x15c	/* MMU Assist Register 5 || 6 */
#घोषणा SPRN_MAS8_MAS1	0x15d	/* MMU Assist Register 8 || 1 */
#घोषणा SPRN_EPTCFG	0x15e	/* Embedded Page Table Config */
#घोषणा SPRN_GSPRG0	0x170	/* Guest SPRG0 */
#घोषणा SPRN_GSPRG1	0x171	/* Guest SPRG1 */
#घोषणा SPRN_GSPRG2	0x172	/* Guest SPRG2 */
#घोषणा SPRN_GSPRG3	0x173	/* Guest SPRG3 */
#घोषणा SPRN_MAS7_MAS3	0x174	/* MMU Assist Register 7 || 3 */
#घोषणा SPRN_MAS0_MAS1	0x175	/* MMU Assist Register 0 || 1 */
#घोषणा SPRN_GSRR0	0x17A	/* Guest SRR0 */
#घोषणा SPRN_GSRR1	0x17B	/* Guest SRR1 */
#घोषणा SPRN_GEPR	0x17C	/* Guest EPR */
#घोषणा SPRN_GDEAR	0x17D	/* Guest DEAR */
#घोषणा SPRN_GPIR	0x17E	/* Guest PIR */
#घोषणा SPRN_GESR	0x17F	/* Guest Exception Syndrome Register */
#घोषणा SPRN_IVOR0	0x190	/* Interrupt Vector Offset Register 0 */
#घोषणा SPRN_IVOR1	0x191	/* Interrupt Vector Offset Register 1 */
#घोषणा SPRN_IVOR2	0x192	/* Interrupt Vector Offset Register 2 */
#घोषणा SPRN_IVOR3	0x193	/* Interrupt Vector Offset Register 3 */
#घोषणा SPRN_IVOR4	0x194	/* Interrupt Vector Offset Register 4 */
#घोषणा SPRN_IVOR5	0x195	/* Interrupt Vector Offset Register 5 */
#घोषणा SPRN_IVOR6	0x196	/* Interrupt Vector Offset Register 6 */
#घोषणा SPRN_IVOR7	0x197	/* Interrupt Vector Offset Register 7 */
#घोषणा SPRN_IVOR8	0x198	/* Interrupt Vector Offset Register 8 */
#घोषणा SPRN_IVOR9	0x199	/* Interrupt Vector Offset Register 9 */
#घोषणा SPRN_IVOR10	0x19A	/* Interrupt Vector Offset Register 10 */
#घोषणा SPRN_IVOR11	0x19B	/* Interrupt Vector Offset Register 11 */
#घोषणा SPRN_IVOR12	0x19C	/* Interrupt Vector Offset Register 12 */
#घोषणा SPRN_IVOR13	0x19D	/* Interrupt Vector Offset Register 13 */
#घोषणा SPRN_IVOR14	0x19E	/* Interrupt Vector Offset Register 14 */
#घोषणा SPRN_IVOR15	0x19F	/* Interrupt Vector Offset Register 15 */
#घोषणा SPRN_IVOR38	0x1B0	/* Interrupt Vector Offset Register 38 */
#घोषणा SPRN_IVOR39	0x1B1	/* Interrupt Vector Offset Register 39 */
#घोषणा SPRN_IVOR40	0x1B2	/* Interrupt Vector Offset Register 40 */
#घोषणा SPRN_IVOR41	0x1B3	/* Interrupt Vector Offset Register 41 */
#घोषणा SPRN_IVOR42	0x1B4	/* Interrupt Vector Offset Register 42 */
#घोषणा SPRN_GIVOR2	0x1B8	/* Guest IVOR2 */
#घोषणा SPRN_GIVOR3	0x1B9	/* Guest IVOR3 */
#घोषणा SPRN_GIVOR4	0x1BA	/* Guest IVOR4 */
#घोषणा SPRN_GIVOR8	0x1BB	/* Guest IVOR8 */
#घोषणा SPRN_GIVOR13	0x1BC	/* Guest IVOR13 */
#घोषणा SPRN_GIVOR14	0x1BD	/* Guest IVOR14 */
#घोषणा SPRN_GIVPR	0x1BF	/* Guest IVPR */
#घोषणा SPRN_SPEFSCR	0x200	/* SPE & Embedded FP Status & Control */
#घोषणा SPRN_BBEAR	0x201	/* Branch Buffer Entry Address Register */
#घोषणा SPRN_BBTAR	0x202	/* Branch Buffer Target Address Register */
#घोषणा SPRN_L1CFG0	0x203	/* L1 Cache Configure Register 0 */
#घोषणा SPRN_L1CFG1	0x204	/* L1 Cache Configure Register 1 */
#घोषणा SPRN_ATB	0x20E	/* Alternate Time Base */
#घोषणा SPRN_ATBL	0x20E	/* Alternate Time Base Lower */
#घोषणा SPRN_ATBU	0x20F	/* Alternate Time Base Upper */
#घोषणा SPRN_IVOR32	0x210	/* Interrupt Vector Offset Register 32 */
#घोषणा SPRN_IVOR33	0x211	/* Interrupt Vector Offset Register 33 */
#घोषणा SPRN_IVOR34	0x212	/* Interrupt Vector Offset Register 34 */
#घोषणा SPRN_IVOR35	0x213	/* Interrupt Vector Offset Register 35 */
#घोषणा SPRN_IVOR36	0x214	/* Interrupt Vector Offset Register 36 */
#घोषणा SPRN_IVOR37	0x215	/* Interrupt Vector Offset Register 37 */
#घोषणा SPRN_MCARU	0x239	/* Machine Check Address Register Upper */
#घोषणा SPRN_MCSRR0	0x23A	/* Machine Check Save and Restore Register 0 */
#घोषणा SPRN_MCSRR1	0x23B	/* Machine Check Save and Restore Register 1 */
#घोषणा SPRN_MCSR	0x23C	/* Machine Check Status Register */
#घोषणा SPRN_MCAR	0x23D	/* Machine Check Address Register */
#घोषणा SPRN_DSRR0	0x23E	/* Debug Save and Restore Register 0 */
#घोषणा SPRN_DSRR1	0x23F	/* Debug Save and Restore Register 1 */
#घोषणा SPRN_SPRG8	0x25C	/* Special Purpose Register General 8 */
#घोषणा SPRN_SPRG9	0x25D	/* Special Purpose Register General 9 */
#घोषणा SPRN_L1CSR2	0x25E	/* L1 Cache Control and Status Register 2 */
#घोषणा SPRN_MAS0	0x270	/* MMU Assist Register 0 */
#घोषणा SPRN_MAS1	0x271	/* MMU Assist Register 1 */
#घोषणा SPRN_MAS2	0x272	/* MMU Assist Register 2 */
#घोषणा SPRN_MAS3	0x273	/* MMU Assist Register 3 */
#घोषणा SPRN_MAS4	0x274	/* MMU Assist Register 4 */
#घोषणा SPRN_MAS5	0x153	/* MMU Assist Register 5 */
#घोषणा SPRN_MAS6	0x276	/* MMU Assist Register 6 */
#घोषणा SPRN_PID1	0x279	/* Process ID Register 1 */
#घोषणा SPRN_PID2	0x27A	/* Process ID Register 2 */
#घोषणा SPRN_TLB0CFG	0x2B0	/* TLB 0 Config Register */
#घोषणा SPRN_TLB1CFG	0x2B1	/* TLB 1 Config Register */
#घोषणा SPRN_TLB2CFG	0x2B2	/* TLB 2 Config Register */
#घोषणा SPRN_TLB3CFG	0x2B3	/* TLB 3 Config Register */
#घोषणा SPRN_EPR	0x2BE	/* External Proxy Register */
#घोषणा SPRN_CCR1	0x378	/* Core Configuration Register 1 */
#घोषणा SPRN_ZPR	0x3B0	/* Zone Protection Register (40x) */
#घोषणा SPRN_MAS7	0x3B0	/* MMU Assist Register 7 */
#घोषणा SPRN_MMUCR	0x3B2	/* MMU Control Register */
#घोषणा SPRN_CCR0	0x3B3	/* Core Configuration Register 0 */
#घोषणा SPRN_EPLC	0x3B3	/* External Process ID Load Context */
#घोषणा SPRN_EPSC	0x3B4	/* External Process ID Store Context */
#घोषणा SPRN_SGR	0x3B9	/* Storage Guarded Register */
#घोषणा SPRN_DCWR	0x3BA	/* Data Cache Write-thru Register */
#घोषणा SPRN_SLER	0x3BB	/* Little-endian real mode */
#घोषणा SPRN_SU0R	0x3BC	/* "User 0" real mode (40x) */
#घोषणा SPRN_DCMP	0x3D1	/* Data TLB Compare Register */
#घोषणा SPRN_ICDBDR	0x3D3	/* Inकाष्ठाion Cache Debug Data Register */
#घोषणा SPRN_EVPR	0x3D6	/* Exception Vector Prefix Register */
#घोषणा SPRN_L1CSR0	0x3F2	/* L1 Cache Control and Status Register 0 */
#घोषणा SPRN_L1CSR1	0x3F3	/* L1 Cache Control and Status Register 1 */
#घोषणा SPRN_MMUCSR0	0x3F4	/* MMU Control and Status Register 0 */
#घोषणा SPRN_MMUCFG	0x3F7	/* MMU Configuration Register */
#घोषणा SPRN_BUCSR	0x3F5	/* Branch Unit Control and Status */
#घोषणा SPRN_L2CSR0	0x3F9	/* L2 Data Cache Control and Status Register 0 */
#घोषणा SPRN_L2CSR1	0x3FA	/* L2 Data Cache Control and Status Register 1 */
#घोषणा SPRN_DCCR	0x3FA	/* Data Cache Cacheability Register */
#घोषणा SPRN_ICCR	0x3FB	/* Inकाष्ठाion Cache Cacheability Register */
#घोषणा SPRN_PWRMGTCR0	0x3FB	/* Power management control रेजिस्टर 0 */
#घोषणा SPRN_SVR	0x3FF	/* System Version Register */

/*
 * SPRs which have conflicting definitions on true Book E versus classic,
 * or IBM 40x.
 */
#अगर_घोषित CONFIG_BOOKE
#घोषणा SPRN_CSRR0	0x03A	/* Critical Save and Restore Register 0 */
#घोषणा SPRN_CSRR1	0x03B	/* Critical Save and Restore Register 1 */
#घोषणा SPRN_DEAR	0x03D	/* Data Error Address Register */
#घोषणा SPRN_ESR	0x03E	/* Exception Syndrome Register */
#घोषणा SPRN_PIR	0x11E	/* Processor Identअगरication Register */
#घोषणा SPRN_DBSR	0x130	/* Debug Status Register */
#घोषणा SPRN_DBCR0	0x134	/* Debug Control Register 0 */
#घोषणा SPRN_DBCR1	0x135	/* Debug Control Register 1 */
#घोषणा SPRN_IAC1	0x138	/* Inकाष्ठाion Address Compare 1 */
#घोषणा SPRN_IAC2	0x139	/* Inकाष्ठाion Address Compare 2 */
#घोषणा SPRN_DAC1	0x13C	/* Data Address Compare 1 */
#घोषणा SPRN_DAC2	0x13D	/* Data Address Compare 2 */
#घोषणा SPRN_TSR	0x150	/* Timer Status Register */
#घोषणा SPRN_TCR	0x154	/* Timer Control Register */
#पूर्ण_अगर /* Book E */
#अगर_घोषित CONFIG_40x
#घोषणा SPRN_DBCR1	0x3BD	/* Debug Control Register 1 */		
#घोषणा SPRN_ESR	0x3D4	/* Exception Syndrome Register */
#घोषणा SPRN_DEAR	0x3D5	/* Data Error Address Register */
#घोषणा SPRN_TSR	0x3D8	/* Timer Status Register */
#घोषणा SPRN_TCR	0x3DA	/* Timer Control Register */
#घोषणा SPRN_SRR2	0x3DE	/* Save/Restore Register 2 */
#घोषणा SPRN_SRR3	0x3DF	/* Save/Restore Register 3 */
#घोषणा SPRN_DBSR	0x3F0	/* Debug Status Register */		
#घोषणा SPRN_DBCR0	0x3F2	/* Debug Control Register 0 */
#घोषणा SPRN_DAC1	0x3F6	/* Data Address Compare 1 */
#घोषणा SPRN_DAC2	0x3F7	/* Data Address Compare 2 */
#घोषणा SPRN_CSRR0	SPRN_SRR2 /* Critical Save and Restore Register 0 */
#घोषणा SPRN_CSRR1	SPRN_SRR3 /* Critical Save and Restore Register 1 */
#पूर्ण_अगर
#घोषणा SPRN_HACOP	0x15F	/* Hypervisor Available Coprocessor Register */

/* Bit definitions क्रम CCR1. */
#घोषणा	CCR1_DPC	0x00000100 /* Disable L1 I-Cache/D-Cache parity checking */
#घोषणा	CCR1_TCS	0x00000080 /* Timer Clock Select */

/* Bit definitions क्रम PWRMGTCR0. */
#घोषणा PWRMGTCR0_PW20_WAIT		(1 << 14) /* PW20 state enable bit */
#घोषणा PWRMGTCR0_PW20_ENT_SHIFT	8
#घोषणा PWRMGTCR0_PW20_ENT		0x3F00
#घोषणा PWRMGTCR0_AV_IDLE_PD_EN		(1 << 22) /* Altivec idle enable */
#घोषणा PWRMGTCR0_AV_IDLE_CNT_SHIFT	16
#घोषणा PWRMGTCR0_AV_IDLE_CNT		0x3F0000

/* Bit definitions क्रम the MCSR. */
#घोषणा MCSR_MCS	0x80000000 /* Machine Check Summary */
#घोषणा MCSR_IB		0x40000000 /* Inकाष्ठाion PLB Error */
#घोषणा MCSR_DRB	0x20000000 /* Data Read PLB Error */
#घोषणा MCSR_DWB	0x10000000 /* Data Write PLB Error */
#घोषणा MCSR_TLBP	0x08000000 /* TLB Parity Error */
#घोषणा MCSR_ICP	0x04000000 /* I-Cache Parity Error */
#घोषणा MCSR_DCSP	0x02000000 /* D-Cache Search Parity Error */
#घोषणा MCSR_DCFP	0x01000000 /* D-Cache Flush Parity Error */
#घोषणा MCSR_IMPE	0x00800000 /* Imprecise Machine Check Exception */

#घोषणा PPC47x_MCSR_GPR	0x01000000 /* GPR parity error */
#घोषणा PPC47x_MCSR_FPR	0x00800000 /* FPR parity error */
#घोषणा PPC47x_MCSR_IPR	0x00400000 /* Imprecise Machine Check Exception */

#अगर_घोषित CONFIG_E500
/* All e500 */
#घोषणा MCSR_MCP 	0x80000000UL /* Machine Check Input Pin */
#घोषणा MCSR_ICPERR 	0x40000000UL /* I-Cache Parity Error */

/* e500v1/v2 */
#घोषणा MCSR_DCP_PERR 	0x20000000UL /* D-Cache Push Parity Error */
#घोषणा MCSR_DCPERR 	0x10000000UL /* D-Cache Parity Error */
#घोषणा MCSR_BUS_IAERR 	0x00000080UL /* Inकाष्ठाion Address Error */
#घोषणा MCSR_BUS_RAERR 	0x00000040UL /* Read Address Error */
#घोषणा MCSR_BUS_WAERR 	0x00000020UL /* Write Address Error */
#घोषणा MCSR_BUS_IBERR 	0x00000010UL /* Inकाष्ठाion Data Error */
#घोषणा MCSR_BUS_RBERR 	0x00000008UL /* Read Data Bus Error */
#घोषणा MCSR_BUS_WBERR 	0x00000004UL /* Write Data Bus Error */
#घोषणा MCSR_BUS_IPERR 	0x00000002UL /* Inकाष्ठाion parity Error */
#घोषणा MCSR_BUS_RPERR 	0x00000001UL /* Read parity Error */

/* e500mc */
#घोषणा MCSR_DCPERR_MC	0x20000000UL /* D-Cache Parity Error */
#घोषणा MCSR_L2MMU_MHIT	0x08000000UL /* Hit on multiple TLB entries */
#घोषणा MCSR_NMI	0x00100000UL /* Non-Maskable Interrupt */
#घोषणा MCSR_MAV	0x00080000UL /* MCAR address valid */
#घोषणा MCSR_MEA	0x00040000UL /* MCAR is effective address */
#घोषणा MCSR_IF		0x00010000UL /* Inकाष्ठाion Fetch */
#घोषणा MCSR_LD		0x00008000UL /* Load */
#घोषणा MCSR_ST		0x00004000UL /* Store */
#घोषणा MCSR_LDG	0x00002000UL /* Guarded Load */
#घोषणा MCSR_TLBSYNC	0x00000002UL /* Multiple tlbsyncs detected */
#घोषणा MCSR_BSL2_ERR	0x00000001UL /* Backside L2 cache error */

#घोषणा MSRP_UCLEP	0x04000000 /* Protect MSR[UCLE] */
#घोषणा MSRP_DEP	0x00000200 /* Protect MSR[DE] */
#घोषणा MSRP_PMMP	0x00000004 /* Protect MSR[PMM] */
#पूर्ण_अगर

/* Bit definitions क्रम the HID1 */
#अगर_घोषित CONFIG_E500
/* e500v1/v2 */
#घोषणा HID1_PLL_CFG_MASK 0xfc000000	/* PLL_CFG input pins */
#घोषणा HID1_RFXE	0x00020000	/* Read fault exception enable */
#घोषणा HID1_R1DPE	0x00008000	/* R1 data bus parity enable */
#घोषणा HID1_R2DPE	0x00004000	/* R2 data bus parity enable */
#घोषणा HID1_ASTME	0x00002000	/* Address bus streaming mode enable */
#घोषणा HID1_ABE	0x00001000	/* Address broadcast enable */
#घोषणा HID1_MPXTT	0x00000400	/* MPX re-map transfer type */
#घोषणा HID1_ATS	0x00000080	/* Atomic status */
#घोषणा HID1_MID_MASK	0x0000000f	/* MID input pins */
#पूर्ण_अगर

/* Bit definitions क्रम the DBSR. */
/*
 * DBSR bits which have conflicting definitions on true Book E versus IBM 40x.
 */
#अगर_घोषित CONFIG_BOOKE
#घोषणा DBSR_IDE	0x80000000	/* Imprecise Debug Event */
#घोषणा DBSR_MRR	0x30000000	/* Most Recent Reset */
#घोषणा DBSR_IC		0x08000000	/* Inकाष्ठाion Completion */
#घोषणा DBSR_BT		0x04000000	/* Branch Taken */
#घोषणा DBSR_IRPT	0x02000000	/* Exception Debug Event */
#घोषणा DBSR_TIE	0x01000000	/* Trap Inकाष्ठाion Event */
#घोषणा DBSR_IAC1	0x00800000	/* Instr Address Compare 1 Event */
#घोषणा DBSR_IAC2	0x00400000	/* Instr Address Compare 2 Event */
#घोषणा DBSR_IAC3	0x00200000	/* Instr Address Compare 3 Event */
#घोषणा DBSR_IAC4	0x00100000	/* Instr Address Compare 4 Event */
#घोषणा DBSR_DAC1R	0x00080000	/* Data Addr Compare 1 Read Event */
#घोषणा DBSR_DAC1W	0x00040000	/* Data Addr Compare 1 Write Event */
#घोषणा DBSR_DAC2R	0x00020000	/* Data Addr Compare 2 Read Event */
#घोषणा DBSR_DAC2W	0x00010000	/* Data Addr Compare 2 Write Event */
#घोषणा DBSR_RET	0x00008000	/* Return Debug Event */
#घोषणा DBSR_CIRPT	0x00000040	/* Critical Interrupt Taken Event */
#घोषणा DBSR_CRET	0x00000020	/* Critical Return Debug Event */
#घोषणा DBSR_IAC12ATS	0x00000002	/* Instr Address Compare 1/2 Toggle */
#घोषणा DBSR_IAC34ATS	0x00000001	/* Instr Address Compare 3/4 Toggle */
#पूर्ण_अगर
#अगर_घोषित CONFIG_40x
#घोषणा DBSR_IC		0x80000000	/* Inकाष्ठाion Completion */
#घोषणा DBSR_BT		0x40000000	/* Branch taken */
#घोषणा DBSR_IRPT	0x20000000	/* Exception Debug Event */
#घोषणा DBSR_TIE	0x10000000	/* Trap Inकाष्ठाion debug Event */
#घोषणा DBSR_IAC1	0x04000000	/* Inकाष्ठाion Address Compare 1 Event */
#घोषणा DBSR_IAC2	0x02000000	/* Inकाष्ठाion Address Compare 2 Event */
#घोषणा DBSR_IAC3	0x00080000	/* Inकाष्ठाion Address Compare 3 Event */
#घोषणा DBSR_IAC4	0x00040000	/* Inकाष्ठाion Address Compare 4 Event */
#घोषणा DBSR_DAC1R	0x01000000	/* Data Address Compare 1 Read Event */
#घोषणा DBSR_DAC1W	0x00800000	/* Data Address Compare 1 Write Event */
#घोषणा DBSR_DAC2R	0x00400000	/* Data Address Compare 2 Read Event */
#घोषणा DBSR_DAC2W	0x00200000	/* Data Address Compare 2 Write Event */
#पूर्ण_अगर

/* Bit definitions related to the ESR. */
#घोषणा ESR_MCI		0x80000000	/* Machine Check - Inकाष्ठाion */
#घोषणा ESR_IMCP	0x80000000	/* Instr. Machine Check - Protection */
#घोषणा ESR_IMCN	0x40000000	/* Instr. Machine Check - Non-config */
#घोषणा ESR_IMCB	0x20000000	/* Instr. Machine Check - Bus error */
#घोषणा ESR_IMCT	0x10000000	/* Instr. Machine Check - Timeout */
#घोषणा ESR_PIL		0x08000000	/* Program Exception - Illegal */
#घोषणा ESR_PPR		0x04000000	/* Program Exception - Privileged */
#घोषणा ESR_PTR		0x02000000	/* Program Exception - Trap */
#घोषणा ESR_FP		0x01000000	/* Floating Poपूर्णांक Operation */
#घोषणा ESR_DST		0x00800000	/* Storage Exception - Data miss */
#घोषणा ESR_DIZ		0x00400000	/* Storage Exception - Zone fault */
#घोषणा ESR_ST		0x00800000	/* Store Operation */
#घोषणा ESR_DLK		0x00200000	/* Data Cache Locking */
#घोषणा ESR_ILK		0x00100000	/* Instr. Cache Locking */
#घोषणा ESR_PUO		0x00040000	/* Unimplemented Operation exception */
#घोषणा ESR_BO		0x00020000	/* Byte Ordering */
#घोषणा ESR_SPV		0x00000080	/* Signal Processing operation */

/* Bit definitions related to the DBCR0. */
#अगर defined(CONFIG_40x)
#घोषणा DBCR0_EDM	0x80000000	/* External Debug Mode */
#घोषणा DBCR0_IDM	0x40000000	/* Internal Debug Mode */
#घोषणा DBCR0_RST	0x30000000	/* all the bits in the RST field */
#घोषणा DBCR0_RST_SYSTEM 0x30000000	/* System Reset */
#घोषणा DBCR0_RST_CHIP	0x20000000	/* Chip Reset */
#घोषणा DBCR0_RST_CORE	0x10000000	/* Core Reset */
#घोषणा DBCR0_RST_NONE	0x00000000	/* No Reset */
#घोषणा DBCR0_IC	0x08000000	/* Inकाष्ठाion Completion */
#घोषणा DBCR0_ICMP	DBCR0_IC
#घोषणा DBCR0_BT	0x04000000	/* Branch Taken */
#घोषणा DBCR0_BRT	DBCR0_BT
#घोषणा DBCR0_EDE	0x02000000	/* Exception Debug Event */
#घोषणा DBCR0_IRPT	DBCR0_EDE
#घोषणा DBCR0_TDE	0x01000000	/* TRAP Debug Event */
#घोषणा DBCR0_IA1	0x00800000	/* Instr Addr compare 1 enable */
#घोषणा DBCR0_IAC1	DBCR0_IA1
#घोषणा DBCR0_IA2	0x00400000	/* Instr Addr compare 2 enable */
#घोषणा DBCR0_IAC2	DBCR0_IA2
#घोषणा DBCR0_IA12	0x00200000	/* Instr Addr 1-2 range enable */
#घोषणा DBCR0_IA12X	0x00100000	/* Instr Addr 1-2 range eXclusive */
#घोषणा DBCR0_IA3	0x00080000	/* Instr Addr compare 3 enable */
#घोषणा DBCR0_IAC3	DBCR0_IA3
#घोषणा DBCR0_IA4	0x00040000	/* Instr Addr compare 4 enable */
#घोषणा DBCR0_IAC4	DBCR0_IA4
#घोषणा DBCR0_IA34	0x00020000	/* Instr Addr 3-4 range Enable */
#घोषणा DBCR0_IA34X	0x00010000	/* Instr Addr 3-4 range eXclusive */
#घोषणा DBCR0_IA12T	0x00008000	/* Instr Addr 1-2 range Toggle */
#घोषणा DBCR0_IA34T	0x00004000	/* Instr Addr 3-4 range Toggle */
#घोषणा DBCR0_FT	0x00000001	/* Freeze Timers on debug event */

#घोषणा dbcr_iac_range(task)	((task)->thपढ़ो.debug.dbcr0)
#घोषणा DBCR_IAC12I	DBCR0_IA12			/* Range Inclusive */
#घोषणा DBCR_IAC12X	(DBCR0_IA12 | DBCR0_IA12X)	/* Range Exclusive */
#घोषणा DBCR_IAC12MODE	(DBCR0_IA12 | DBCR0_IA12X)	/* IAC 1-2 Mode Bits */
#घोषणा DBCR_IAC34I	DBCR0_IA34			/* Range Inclusive */
#घोषणा DBCR_IAC34X	(DBCR0_IA34 | DBCR0_IA34X)	/* Range Exclusive */
#घोषणा DBCR_IAC34MODE	(DBCR0_IA34 | DBCR0_IA34X)	/* IAC 3-4 Mode Bits */

/* Bit definitions related to the DBCR1. */
#घोषणा DBCR1_DAC1R	0x80000000	/* DAC1 Read Debug Event */
#घोषणा DBCR1_DAC2R	0x40000000	/* DAC2 Read Debug Event */
#घोषणा DBCR1_DAC1W	0x20000000	/* DAC1 Write Debug Event */
#घोषणा DBCR1_DAC2W	0x10000000	/* DAC2 Write Debug Event */

#घोषणा dbcr_dac(task)	((task)->thपढ़ो.debug.dbcr1)
#घोषणा DBCR_DAC1R	DBCR1_DAC1R
#घोषणा DBCR_DAC1W	DBCR1_DAC1W
#घोषणा DBCR_DAC2R	DBCR1_DAC2R
#घोषणा DBCR_DAC2W	DBCR1_DAC2W

/*
 * Are there any active Debug Events represented in the
 * Debug Control Registers?
 */
#घोषणा DBCR0_ACTIVE_EVENTS	(DBCR0_ICMP | DBCR0_IAC1 | DBCR0_IAC2 | \
				 DBCR0_IAC3 | DBCR0_IAC4)
#घोषणा DBCR1_ACTIVE_EVENTS	(DBCR1_DAC1R | DBCR1_DAC2R | \
				 DBCR1_DAC1W | DBCR1_DAC2W)
#घोषणा DBCR_ACTIVE_EVENTS(dbcr0, dbcr1)  (((dbcr0) & DBCR0_ACTIVE_EVENTS) || \
					   ((dbcr1) & DBCR1_ACTIVE_EVENTS))

#या_अगर defined(CONFIG_BOOKE)
#घोषणा DBCR0_EDM	0x80000000	/* External Debug Mode */
#घोषणा DBCR0_IDM	0x40000000	/* Internal Debug Mode */
#घोषणा DBCR0_RST	0x30000000	/* all the bits in the RST field */
/* DBCR0_RST_* is 44x specअगरic and not followed in fsl booke */
#घोषणा DBCR0_RST_SYSTEM 0x30000000	/* System Reset */
#घोषणा DBCR0_RST_CHIP	0x20000000	/* Chip Reset */
#घोषणा DBCR0_RST_CORE	0x10000000	/* Core Reset */
#घोषणा DBCR0_RST_NONE	0x00000000	/* No Reset */
#घोषणा DBCR0_ICMP	0x08000000	/* Inकाष्ठाion Completion */
#घोषणा DBCR0_IC	DBCR0_ICMP
#घोषणा DBCR0_BRT	0x04000000	/* Branch Taken */
#घोषणा DBCR0_BT	DBCR0_BRT
#घोषणा DBCR0_IRPT	0x02000000	/* Exception Debug Event */
#घोषणा DBCR0_TDE	0x01000000	/* TRAP Debug Event */
#घोषणा DBCR0_TIE	DBCR0_TDE
#घोषणा DBCR0_IAC1	0x00800000	/* Instr Addr compare 1 enable */
#घोषणा DBCR0_IAC2	0x00400000	/* Instr Addr compare 2 enable */
#घोषणा DBCR0_IAC3	0x00200000	/* Instr Addr compare 3 enable */
#घोषणा DBCR0_IAC4	0x00100000	/* Instr Addr compare 4 enable */
#घोषणा DBCR0_DAC1R	0x00080000	/* DAC 1 Read enable */
#घोषणा DBCR0_DAC1W	0x00040000	/* DAC 1 Write enable */
#घोषणा DBCR0_DAC2R	0x00020000	/* DAC 2 Read enable */
#घोषणा DBCR0_DAC2W	0x00010000	/* DAC 2 Write enable */
#घोषणा DBCR0_RET	0x00008000	/* Return Debug Event */
#घोषणा DBCR0_CIRPT	0x00000040	/* Critical Interrupt Taken Event */
#घोषणा DBCR0_CRET	0x00000020	/* Critical Return Debug Event */
#घोषणा DBCR0_FT	0x00000001	/* Freeze Timers on debug event */

#घोषणा dbcr_dac(task)	((task)->thपढ़ो.debug.dbcr0)
#घोषणा DBCR_DAC1R	DBCR0_DAC1R
#घोषणा DBCR_DAC1W	DBCR0_DAC1W
#घोषणा DBCR_DAC2R	DBCR0_DAC2R
#घोषणा DBCR_DAC2W	DBCR0_DAC2W

/* Bit definitions related to the DBCR1. */
#घोषणा DBCR1_IAC1US	0xC0000000	/* Instr Addr Cmp 1 Sup/User   */
#घोषणा DBCR1_IAC1ER	0x30000000	/* Instr Addr Cmp 1 Eff/Real */
#घोषणा DBCR1_IAC1ER_01	0x10000000	/* reserved */
#घोषणा DBCR1_IAC1ER_10	0x20000000	/* Instr Addr Cmp 1 Eff/Real MSR[IS]=0 */
#घोषणा DBCR1_IAC1ER_11	0x30000000	/* Instr Addr Cmp 1 Eff/Real MSR[IS]=1 */
#घोषणा DBCR1_IAC2US	0x0C000000	/* Instr Addr Cmp 2 Sup/User   */
#घोषणा DBCR1_IAC2ER	0x03000000	/* Instr Addr Cmp 2 Eff/Real */
#घोषणा DBCR1_IAC2ER_01	0x01000000	/* reserved */
#घोषणा DBCR1_IAC2ER_10	0x02000000	/* Instr Addr Cmp 2 Eff/Real MSR[IS]=0 */
#घोषणा DBCR1_IAC2ER_11	0x03000000	/* Instr Addr Cmp 2 Eff/Real MSR[IS]=1 */
#घोषणा DBCR1_IAC12M	0x00800000	/* Instr Addr 1-2 range enable */
#घोषणा DBCR1_IAC12MX	0x00C00000	/* Instr Addr 1-2 range eXclusive */
#घोषणा DBCR1_IAC12AT	0x00010000	/* Instr Addr 1-2 range Toggle */
#घोषणा DBCR1_IAC3US	0x0000C000	/* Instr Addr Cmp 3 Sup/User   */
#घोषणा DBCR1_IAC3ER	0x00003000	/* Instr Addr Cmp 3 Eff/Real */
#घोषणा DBCR1_IAC3ER_01	0x00001000	/* reserved */
#घोषणा DBCR1_IAC3ER_10	0x00002000	/* Instr Addr Cmp 3 Eff/Real MSR[IS]=0 */
#घोषणा DBCR1_IAC3ER_11	0x00003000	/* Instr Addr Cmp 3 Eff/Real MSR[IS]=1 */
#घोषणा DBCR1_IAC4US	0x00000C00	/* Instr Addr Cmp 4 Sup/User   */
#घोषणा DBCR1_IAC4ER	0x00000300	/* Instr Addr Cmp 4 Eff/Real */
#घोषणा DBCR1_IAC4ER_01	0x00000100	/* Instr Addr Cmp 4 Eff/Real MSR[IS]=0 */
#घोषणा DBCR1_IAC4ER_10	0x00000200	/* Instr Addr Cmp 4 Eff/Real MSR[IS]=0 */
#घोषणा DBCR1_IAC4ER_11	0x00000300	/* Instr Addr Cmp 4 Eff/Real MSR[IS]=1 */
#घोषणा DBCR1_IAC34M	0x00000080	/* Instr Addr 3-4 range enable */
#घोषणा DBCR1_IAC34MX	0x000000C0	/* Instr Addr 3-4 range eXclusive */
#घोषणा DBCR1_IAC34AT	0x00000001	/* Instr Addr 3-4 range Toggle */

#घोषणा dbcr_iac_range(task)	((task)->thपढ़ो.debug.dbcr1)
#घोषणा DBCR_IAC12I	DBCR1_IAC12M	/* Range Inclusive */
#घोषणा DBCR_IAC12X	DBCR1_IAC12MX	/* Range Exclusive */
#घोषणा DBCR_IAC12MODE	DBCR1_IAC12MX	/* IAC 1-2 Mode Bits */
#घोषणा DBCR_IAC34I	DBCR1_IAC34M	/* Range Inclusive */
#घोषणा DBCR_IAC34X	DBCR1_IAC34MX	/* Range Exclusive */
#घोषणा DBCR_IAC34MODE	DBCR1_IAC34MX	/* IAC 3-4 Mode Bits */

/* Bit definitions related to the DBCR2. */
#घोषणा DBCR2_DAC1US	0xC0000000	/* Data Addr Cmp 1 Sup/User   */
#घोषणा DBCR2_DAC1ER	0x30000000	/* Data Addr Cmp 1 Eff/Real */
#घोषणा DBCR2_DAC2US	0x0C000000	/* Data Addr Cmp 2 Sup/User   */
#घोषणा DBCR2_DAC2ER	0x03000000	/* Data Addr Cmp 2 Eff/Real */
#घोषणा DBCR2_DAC12M	0x00800000	/* DAC 1-2 range enable */
#घोषणा DBCR2_DAC12MM	0x00400000	/* DAC 1-2 Mask mode*/
#घोषणा DBCR2_DAC12MX	0x00C00000	/* DAC 1-2 range eXclusive */
#घोषणा DBCR2_DAC12MODE	0x00C00000	/* DAC 1-2 Mode Bits */
#घोषणा DBCR2_DAC12A	0x00200000	/* DAC 1-2 Asynchronous */
#घोषणा DBCR2_DVC1M	0x000C0000	/* Data Value Comp 1 Mode */
#घोषणा DBCR2_DVC1M_SHIFT	18	/* # of bits to shअगरt DBCR2_DVC1M */
#घोषणा DBCR2_DVC2M	0x00030000	/* Data Value Comp 2 Mode */
#घोषणा DBCR2_DVC2M_SHIFT	16	/* # of bits to shअगरt DBCR2_DVC2M */
#घोषणा DBCR2_DVC1BE	0x00000F00	/* Data Value Comp 1 Byte */
#घोषणा DBCR2_DVC1BE_SHIFT	8	/* # of bits to shअगरt DBCR2_DVC1BE */
#घोषणा DBCR2_DVC2BE	0x0000000F	/* Data Value Comp 2 Byte */
#घोषणा DBCR2_DVC2BE_SHIFT	0	/* # of bits to shअगरt DBCR2_DVC2BE */

/*
 * Are there any active Debug Events represented in the
 * Debug Control Registers?
 */
#घोषणा DBCR0_ACTIVE_EVENTS  (DBCR0_ICMP | DBCR0_IAC1 | DBCR0_IAC2 | \
			      DBCR0_IAC3 | DBCR0_IAC4 | DBCR0_DAC1R | \
			      DBCR0_DAC1W  | DBCR0_DAC2R | DBCR0_DAC2W)
#घोषणा DBCR1_ACTIVE_EVENTS	0

#घोषणा DBCR_ACTIVE_EVENTS(dbcr0, dbcr1)  (((dbcr0) & DBCR0_ACTIVE_EVENTS) || \
					   ((dbcr1) & DBCR1_ACTIVE_EVENTS))
#पूर्ण_अगर /* #या_अगर defined(CONFIG_BOOKE) */

/* Bit definitions related to the TCR. */
#घोषणा TCR_WP(x)	(((x)&0x3)<<30)	/* WDT Period */
#घोषणा TCR_WP_MASK	TCR_WP(3)
#घोषणा WP_2_17		0		/* 2^17 घड़ीs */
#घोषणा WP_2_21		1		/* 2^21 घड़ीs */
#घोषणा WP_2_25		2		/* 2^25 घड़ीs */
#घोषणा WP_2_29		3		/* 2^29 घड़ीs */
#घोषणा TCR_WRC(x)	(((x)&0x3)<<28)	/* WDT Reset Control */
#घोषणा TCR_WRC_MASK	TCR_WRC(3)
#घोषणा WRC_NONE	0		/* No reset will occur */
#घोषणा WRC_CORE	1		/* Core reset will occur */
#घोषणा WRC_CHIP	2		/* Chip reset will occur */
#घोषणा WRC_SYSTEM	3		/* System reset will occur */
#घोषणा TCR_WIE		0x08000000	/* WDT Interrupt Enable */
#घोषणा TCR_PIE		0x04000000	/* PIT Interrupt Enable */
#घोषणा TCR_DIE		TCR_PIE		/* DEC Interrupt Enable */
#घोषणा TCR_FP(x)	(((x)&0x3)<<24)	/* FIT Period */
#घोषणा TCR_FP_MASK	TCR_FP(3)
#घोषणा FP_2_9		0		/* 2^9 घड़ीs */
#घोषणा FP_2_13		1		/* 2^13 घड़ीs */
#घोषणा FP_2_17		2		/* 2^17 घड़ीs */
#घोषणा FP_2_21		3		/* 2^21 घड़ीs */
#घोषणा TCR_FIE		0x00800000	/* FIT Interrupt Enable */
#घोषणा TCR_ARE		0x00400000	/* Auto Reload Enable */

#अगर_घोषित CONFIG_E500
#घोषणा TCR_GET_WP(tcr)  ((((tcr) & 0xC0000000) >> 30) | \
			      (((tcr) & 0x1E0000) >> 15))
#अन्यथा
#घोषणा TCR_GET_WP(tcr)  (((tcr) & 0xC0000000) >> 30)
#पूर्ण_अगर

/* Bit definitions क्रम the TSR. */
#घोषणा TSR_ENW		0x80000000	/* Enable Next Watchकरोg */
#घोषणा TSR_WIS		0x40000000	/* WDT Interrupt Status */
#घोषणा TSR_WRS(x)	(((x)&0x3)<<28)	/* WDT Reset Status */
#घोषणा WRS_NONE	0		/* No WDT reset occurred */
#घोषणा WRS_CORE	1		/* WDT क्रमced core reset */
#घोषणा WRS_CHIP	2		/* WDT क्रमced chip reset */
#घोषणा WRS_SYSTEM	3		/* WDT क्रमced प्रणाली reset */
#घोषणा TSR_PIS		0x08000000	/* PIT Interrupt Status */
#घोषणा TSR_DIS		TSR_PIS		/* DEC Interrupt Status */
#घोषणा TSR_FIS		0x04000000	/* FIT Interrupt Status */

/* Bit definitions क्रम the DCCR. */
#घोषणा DCCR_NOCACHE	0		/* Noncacheable */
#घोषणा DCCR_CACHE	1		/* Cacheable */

/* Bit definitions क्रम DCWR. */
#घोषणा DCWR_COPY	0		/* Copy-back */
#घोषणा DCWR_WRITE	1		/* Write-through */

/* Bit definitions क्रम ICCR. */
#घोषणा ICCR_NOCACHE	0		/* Noncacheable */
#घोषणा ICCR_CACHE	1		/* Cacheable */

/* Bit definitions क्रम L1CSR0. */
#घोषणा L1CSR0_CPE	0x00010000	/* Data Cache Parity Enable */
#घोषणा L1CSR0_CUL	0x00000400	/* Data Cache Unable to Lock */
#घोषणा L1CSR0_CLFC	0x00000100	/* Cache Lock Bits Flash Clear */
#घोषणा L1CSR0_DCFI	0x00000002	/* Data Cache Flash Invalidate */
#घोषणा L1CSR0_CFI	0x00000002	/* Cache Flash Invalidate */
#घोषणा L1CSR0_DCE	0x00000001	/* Data Cache Enable */

/* Bit definitions क्रम L1CSR1. */
#घोषणा L1CSR1_CPE	0x00010000	/* Inकाष्ठाion Cache Parity Enable */
#घोषणा L1CSR1_ICLFR	0x00000100	/* Instr Cache Lock Bits Flash Reset */
#घोषणा L1CSR1_ICFI	0x00000002	/* Instr Cache Flash Invalidate */
#घोषणा L1CSR1_ICE	0x00000001	/* Instr Cache Enable */

/* Bit definitions क्रम L1CSR2. */
#घोषणा L1CSR2_DCWS	0x40000000	/* Data Cache ग_लिखो shaकरोw */

/* Bit definitions क्रम BUCSR. */
#घोषणा BUCSR_STAC_EN	0x01000000	/* Segment Target Address Cache */
#घोषणा BUCSR_LS_EN	0x00400000	/* Link Stack */
#घोषणा BUCSR_BBFI	0x00000200	/* Branch Buffer flash invalidate */
#घोषणा BUCSR_BPEN	0x00000001	/* Branch prediction enable */
#घोषणा BUCSR_INIT	(BUCSR_STAC_EN | BUCSR_LS_EN | BUCSR_BBFI | BUCSR_BPEN)

/* Bit definitions क्रम L2CSR0. */
#घोषणा L2CSR0_L2E	0x80000000	/* L2 Cache Enable */
#घोषणा L2CSR0_L2PE	0x40000000	/* L2 Cache Parity/ECC Enable */
#घोषणा L2CSR0_L2WP	0x1c000000	/* L2 I/D Way Partioning */
#घोषणा L2CSR0_L2CM	0x03000000	/* L2 Cache Coherency Mode */
#घोषणा L2CSR0_L2FI	0x00200000	/* L2 Cache Flash Invalidate */
#घोषणा L2CSR0_L2IO	0x00100000	/* L2 Cache Inकाष्ठाion Only */
#घोषणा L2CSR0_L2DO	0x00010000	/* L2 Cache Data Only */
#घोषणा L2CSR0_L2REP	0x00003000	/* L2 Line Replacement Algo */
#घोषणा L2CSR0_L2FL	0x00000800	/* L2 Cache Flush */
#घोषणा L2CSR0_L2LFC	0x00000400	/* L2 Cache Lock Flash Clear */
#घोषणा L2CSR0_L2LOA	0x00000080	/* L2 Cache Lock Overflow Allocate */
#घोषणा L2CSR0_L2LO	0x00000020	/* L2 Cache Lock Overflow */

/* Bit definitions क्रम SGR. */
#घोषणा SGR_NORMAL	0		/* Speculative fetching allowed. */
#घोषणा SGR_GUARDED	1		/* Speculative fetching disallowed. */

/* Bit definitions क्रम EPCR */
#घोषणा SPRN_EPCR_EXTGS		0x80000000	/* External Input पूर्णांकerrupt
						 * directed to Guest state */
#घोषणा SPRN_EPCR_DTLBGS	0x40000000	/* Data TLB Error पूर्णांकerrupt
						 * directed to guest state */
#घोषणा SPRN_EPCR_ITLBGS	0x20000000	/* Instr. TLB error पूर्णांकerrupt
						 * directed to guest state */
#घोषणा SPRN_EPCR_DSIGS		0x10000000	/* Data Storage पूर्णांकerrupt
						 * directed to guest state */
#घोषणा SPRN_EPCR_ISIGS		0x08000000	/* Instr. Storage पूर्णांकerrupt
						 * directed to guest state */
#घोषणा SPRN_EPCR_DUVD		0x04000000	/* Disable Hypervisor Debug */
#घोषणा SPRN_EPCR_ICM		0x02000000	/* Interrupt computation mode
						 * (copied to MSR:CM on पूर्णांकr) */
#घोषणा SPRN_EPCR_GICM		0x01000000	/* Guest Interrupt Comp. mode */
#घोषणा SPRN_EPCR_DGTMI		0x00800000	/* Disable TLB Guest Management
						 * inकाष्ठाions */
#घोषणा SPRN_EPCR_DMIUH		0x00400000	/* Disable MAS Interrupt updates
						 * क्रम hypervisor */

/* Bit definitions क्रम EPLC/EPSC */
#घोषणा EPC_EPR		0x80000000 /* 1 = user, 0 = kernel */
#घोषणा EPC_EPR_SHIFT	31
#घोषणा EPC_EAS		0x40000000 /* Address Space */
#घोषणा EPC_EAS_SHIFT	30
#घोषणा EPC_EGS		0x20000000 /* 1 = guest, 0 = hypervisor */
#घोषणा EPC_EGS_SHIFT	29
#घोषणा EPC_ELPID	0x00ff0000
#घोषणा EPC_ELPID_SHIFT	16
#घोषणा EPC_EPID	0x00003fff
#घोषणा EPC_EPID_SHIFT	0

/* Some 476 specअगरic रेजिस्टरs */
#घोषणा SPRN_SSPCR		830
#घोषणा SPRN_USPCR		831
#घोषणा SPRN_ISPCR		829
#घोषणा SPRN_MMUBE0		820
#घोषणा MMUBE0_IBE0_SHIFT	24
#घोषणा MMUBE0_IBE1_SHIFT	16
#घोषणा MMUBE0_IBE2_SHIFT	8
#घोषणा MMUBE0_VBE0		0x00000004
#घोषणा MMUBE0_VBE1		0x00000002
#घोषणा MMUBE0_VBE2		0x00000001
#घोषणा SPRN_MMUBE1		821
#घोषणा MMUBE1_IBE3_SHIFT	24
#घोषणा MMUBE1_IBE4_SHIFT	16
#घोषणा MMUBE1_IBE5_SHIFT	8
#घोषणा MMUBE1_VBE3		0x00000004
#घोषणा MMUBE1_VBE4		0x00000002
#घोषणा MMUBE1_VBE5		0x00000001

#घोषणा TMRN_TMCFG0      16	/* Thपढ़ो Management Configuration Register 0 */
#घोषणा TMRN_TMCFG0_NPRIBITS       0x003f0000 /* Bits of thपढ़ो priority */
#घोषणा TMRN_TMCFG0_NPRIBITS_SHIFT 16
#घोषणा TMRN_TMCFG0_NATHRD         0x00003f00 /* Number of active thपढ़ोs */
#घोषणा TMRN_TMCFG0_NATHRD_SHIFT   8
#घोषणा TMRN_TMCFG0_NTHRD          0x0000003f /* Number of thपढ़ोs */
#घोषणा TMRN_IMSR0	0x120	/* Initial MSR Register 0 (e6500) */
#घोषणा TMRN_IMSR1	0x121	/* Initial MSR Register 1 (e6500) */
#घोषणा TMRN_INIA0	0x140	/* Next Inकाष्ठाion Address Register 0 */
#घोषणा TMRN_INIA1	0x141	/* Next Inकाष्ठाion Address Register 1 */
#घोषणा SPRN_TENSR	0x1b5	/* Thपढ़ो Enable Status Register */
#घोषणा SPRN_TENS	0x1b6	/* Thपढ़ो Enable Set Register */
#घोषणा SPRN_TENC	0x1b7	/* Thपढ़ो Enable Clear Register */

#घोषणा TEN_THREAD(x)	(1 << (x))

#अगर_अघोषित __ASSEMBLY__
#घोषणा mfपंचांगr(rn)	(अणुअचिन्हित दीर्घ rval; \
			यंत्र अस्थिर(MFTMR(rn, %0) : "=r" (rval)); rval;पूर्ण)
#घोषणा mtपंचांगr(rn, v)	यंत्र अस्थिर(MTTMR(rn, %0) : \
				     : "r" ((अचिन्हित दीर्घ)(v)) \
				     : "memory")

बाह्य अचिन्हित दीर्घ global_dbcr0[];

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_POWERPC_REG_BOOKE_H__ */
#पूर्ण_अगर /* __KERNEL__ */
