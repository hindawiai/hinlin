<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __NDS32_BITFIELD_H__
#घोषणा __NDS32_BITFIELD_H__
/******************************************************************************
 * cr0: CPU_VER (CPU Version Register)
 *****************************************************************************/
#घोषणा CPU_VER_offCFGID	0	/* Minor configuration */
#घोषणा CPU_VER_offREV		16	/* Revision of the CPU version */
#घोषणा CPU_VER_offCPUID	24	/* Major CPU versions */

#घोषणा CPU_VER_mskCFGID	( 0xFFFF  << CPU_VER_offCFGID )
#घोषणा CPU_VER_mskREV		( 0xFF  << CPU_VER_offREV )
#घोषणा CPU_VER_mskCPUID	( 0xFF  << CPU_VER_offCPUID )

/******************************************************************************
 * cr1: ICM_CFG (Inकाष्ठाion Cache/Memory Configuration Register)
 *****************************************************************************/
#घोषणा ICM_CFG_offISET		0	/* I-cache sets (# of cache lines) per way */
#घोषणा ICM_CFG_offIWAY		3	/* I-cache ways */
#घोषणा ICM_CFG_offISZ		6	/* I-cache line size */
#घोषणा ICM_CFG_offILCK		9	/* I-cache locking support */
#घोषणा ICM_CFG_offILMB		10	/* On-chip ILM banks */
#घोषणा ICM_CFG_offBSAV		13	/* ILM base रेजिस्टर alignment version */
/* bit 15:31 reserved */

#घोषणा ICM_CFG_mskISET		( 0x7  << ICM_CFG_offISET )
#घोषणा ICM_CFG_mskIWAY		( 0x7  << ICM_CFG_offIWAY )
#घोषणा ICM_CFG_mskISZ		( 0x7  << ICM_CFG_offISZ )
#घोषणा ICM_CFG_mskILCK		( 0x1  << ICM_CFG_offILCK )
#घोषणा ICM_CFG_mskILMB		( 0x7  << ICM_CFG_offILMB )
#घोषणा ICM_CFG_mskBSAV		( 0x3  << ICM_CFG_offBSAV )

/******************************************************************************
 * cr2: DCM_CFG (Data Cache/Memory Configuration Register)
 *****************************************************************************/
#घोषणा DCM_CFG_offDSET		0	/* D-cache sets (# of cache lines) per way */
#घोषणा DCM_CFG_offDWAY		3	/* D-cache ways */
#घोषणा DCM_CFG_offDSZ		6	/* D-cache line size */
#घोषणा DCM_CFG_offDLCK		9	/* D-cache locking support */
#घोषणा DCM_CFG_offDLMB		10	/* On-chip DLM banks */
#घोषणा DCM_CFG_offBSAV		13	/* DLM base रेजिस्टर alignment version */
/* bit 15:31 reserved */

#घोषणा DCM_CFG_mskDSET		( 0x7  << DCM_CFG_offDSET )
#घोषणा DCM_CFG_mskDWAY		( 0x7  << DCM_CFG_offDWAY )
#घोषणा DCM_CFG_mskDSZ		( 0x7  << DCM_CFG_offDSZ )
#घोषणा DCM_CFG_mskDLCK		( 0x1  << DCM_CFG_offDLCK )
#घोषणा DCM_CFG_mskDLMB		( 0x7  << DCM_CFG_offDLMB )
#घोषणा DCM_CFG_mskBSAV		( 0x3  << DCM_CFG_offBSAV )

/******************************************************************************
 * cr3: MMU_CFG (MMU Configuration Register)
 *****************************************************************************/
#घोषणा MMU_CFG_offMMPS		0	/* Memory management protection scheme */
#घोषणा MMU_CFG_offMMPV		2	/* Memory management protection version number */
#घोषणा MMU_CFG_offFATB		7	/* Fully-associative or non-fully-associative TLB */

#घोषणा MMU_CFG_offTBW		8	/* TLB ways(non-associative) TBS */
#घोषणा MMU_CFG_offTBS		11	/* TLB sets per way(non-associative) TBS */
/* bit 14:14 reserved */

#घोषणा MMU_CFG_offEP8MIN4	15	/* 8KB page supported जबतक minimum page is 4KB */
#घोषणा MMU_CFG_offfEPSZ	16	/* Extra page size supported */
#घोषणा MMU_CFG_offTLBLCK	24	/* TLB locking support */
#घोषणा MMU_CFG_offHPTWK	25	/* Hardware Page Table Walker implemented */
#घोषणा MMU_CFG_offDE		26	/* Default endian */
#घोषणा MMU_CFG_offNTPT		27	/* Partitions क्रम non-translated attributes */
#घोषणा MMU_CFG_offIVTB		28	/* Invisible TLB */
#घोषणा MMU_CFG_offVLPT		29	/* VLPT क्रम fast TLB fill handling implemented */
#घोषणा MMU_CFG_offNTME		30	/* Non-translated VA to PA mapping */
/* bit 31 reserved */

#घोषणा MMU_CFG_mskMMPS		( 0x3  << MMU_CFG_offMMPS )
#घोषणा MMU_CFG_mskMMPV		( 0x1F  << MMU_CFG_offMMPV )
#घोषणा MMU_CFG_mskFATB		( 0x1  << MMU_CFG_offFATB )
#घोषणा MMU_CFG_mskTBW		( 0x7  << MMU_CFG_offTBW )
#घोषणा MMU_CFG_mskTBS		( 0x7  << MMU_CFG_offTBS )
#घोषणा MMU_CFG_mskEP8MIN4	( 0x1  << MMU_CFG_offEP8MIN4 )
#घोषणा MMU_CFG_mskfEPSZ	( 0xFF  << MMU_CFG_offfEPSZ )
#घोषणा MMU_CFG_mskTLBLCK	( 0x1  << MMU_CFG_offTLBLCK )
#घोषणा MMU_CFG_mskHPTWK	( 0x1  << MMU_CFG_offHPTWK )
#घोषणा MMU_CFG_mskDE		( 0x1  << MMU_CFG_offDE )
#घोषणा MMU_CFG_mskNTPT		( 0x1  << MMU_CFG_offNTPT )
#घोषणा MMU_CFG_mskIVTB		( 0x1  << MMU_CFG_offIVTB )
#घोषणा MMU_CFG_mskVLPT		( 0x1  << MMU_CFG_offVLPT )
#घोषणा MMU_CFG_mskNTME		( 0x1  << MMU_CFG_offNTME )

/******************************************************************************
 * cr4: MSC_CFG (Misc Configuration Register)
 *****************************************************************************/
#घोषणा MSC_CFG_offEDM		0
#घोषणा MSC_CFG_offLMDMA	1
#घोषणा MSC_CFG_offPFM		2
#घोषणा MSC_CFG_offHSMP		3
#घोषणा MSC_CFG_offTRACE	4
#घोषणा MSC_CFG_offDIV		5
#घोषणा MSC_CFG_offMAC		6
#घोषणा MSC_CFG_offAUDIO	7
#घोषणा MSC_CFG_offL2C		9
#घोषणा MSC_CFG_offRDREG	10
#घोषणा MSC_CFG_offADR24	11
#घोषणा MSC_CFG_offINTLC	12
#घोषणा MSC_CFG_offBASEV	13
#घोषणा MSC_CFG_offNOD		16
/* bit 13:31 reserved */

#घोषणा MSC_CFG_mskEDM		( 0x1  << MSC_CFG_offEDM )
#घोषणा MSC_CFG_mskLMDMA	( 0x1  << MSC_CFG_offLMDMA )
#घोषणा MSC_CFG_mskPFM		( 0x1  << MSC_CFG_offPFM )
#घोषणा MSC_CFG_mskHSMP		( 0x1  << MSC_CFG_offHSMP )
#घोषणा MSC_CFG_mskTRACE	( 0x1  << MSC_CFG_offTRACE )
#घोषणा MSC_CFG_mskDIV		( 0x1  << MSC_CFG_offDIV )
#घोषणा MSC_CFG_mskMAC		( 0x1  << MSC_CFG_offMAC )
#घोषणा MSC_CFG_mskAUDIO	( 0x3  << MSC_CFG_offAUDIO )
#घोषणा MSC_CFG_mskL2C		( 0x1  << MSC_CFG_offL2C )
#घोषणा MSC_CFG_mskRDREG	( 0x1  << MSC_CFG_offRDREG )
#घोषणा MSC_CFG_mskADR24	( 0x1  << MSC_CFG_offADR24 )
#घोषणा MSC_CFG_mskINTLC	( 0x1  << MSC_CFG_offINTLC )
#घोषणा MSC_CFG_mskBASEV	( 0x7  << MSC_CFG_offBASEV )
#घोषणा MSC_CFG_mskNOD		( 0x1  << MSC_CFG_offNOD )

/******************************************************************************
 * cr5: CORE_CFG (Core Identअगरication Register)
 *****************************************************************************/
#घोषणा CORE_ID_offCOREID	0
/* bit 4:31 reserved */

#घोषणा CORE_ID_mskCOREID	( 0xF  << CORE_ID_offCOREID )

/******************************************************************************
 * cr6: FUCOP_EXIST (FPU and Coprocessor Existence Configuration Register)
 *****************************************************************************/
#घोषणा FUCOP_EXIST_offCP0EX	0
#घोषणा FUCOP_EXIST_offCP1EX	1
#घोषणा FUCOP_EXIST_offCP2EX	2
#घोषणा FUCOP_EXIST_offCP3EX	3
#घोषणा FUCOP_EXIST_offCP0ISFPU	31

#घोषणा FUCOP_EXIST_mskCP0EX	( 0x1  << FUCOP_EXIST_offCP0EX )
#घोषणा FUCOP_EXIST_mskCP1EX	( 0x1  << FUCOP_EXIST_offCP1EX )
#घोषणा FUCOP_EXIST_mskCP2EX	( 0x1  << FUCOP_EXIST_offCP2EX )
#घोषणा FUCOP_EXIST_mskCP3EX	( 0x1  << FUCOP_EXIST_offCP3EX )
#घोषणा FUCOP_EXIST_mskCP0ISFPU	( 0x1  << FUCOP_EXIST_offCP0ISFPU )

/******************************************************************************
 * ir0: PSW (Processor Status Word Register)
 * ir1: IPSW (Interruption PSW Register)
 * ir2: P_IPSW (Previous IPSW Register)
 *****************************************************************************/
#घोषणा PSW_offGIE		0	/* Global Interrupt Enable */
#घोषणा PSW_offINTL		1	/* Interruption Stack Level */
#घोषणा PSW_offPOM		3	/* Processor Operation Mode, User/Superuser */
#घोषणा PSW_offBE		5	/* Endianness क्रम data memory access, 1:MSB, 0:LSB */
#घोषणा PSW_offIT		6	/* Enable inकाष्ठाion address translation */
#घोषणा PSW_offDT		7	/* Enable data address translation */
#घोषणा PSW_offIME		8	/* Inकाष्ठाion Machine Error flag */
#घोषणा PSW_offDME		9	/* Data Machine Error flag */
#घोषणा PSW_offDEX		10	/* Debug Exception */
#घोषणा PSW_offHSS		11	/* Hardware Single Stepping */
#घोषणा PSW_offDRBE		12	/* Device Register Endian Mode */
#घोषणा PSW_offAEN		13	/* Audio ISA special feature */
#घोषणा PSW_offWBNA		14	/* Write Back Non-Allocate */
#घोषणा PSW_offIFCON		15	/* IFC On */
#घोषणा PSW_offCPL		16	/* Current Priority Level */
/* bit 19:31 reserved */

#घोषणा PSW_mskGIE		( 0x1  << PSW_offGIE )
#घोषणा PSW_mskINTL		( 0x3  << PSW_offINTL )
#घोषणा PSW_mskPOM		( 0x3  << PSW_offPOM )
#घोषणा PSW_mskBE		( 0x1  << PSW_offBE )
#घोषणा PSW_mskIT		( 0x1  << PSW_offIT )
#घोषणा PSW_mskDT		( 0x1  << PSW_offDT )
#घोषणा PSW_mskIME		( 0x1  << PSW_offIME )
#घोषणा PSW_mskDME		( 0x1  << PSW_offDME )
#घोषणा PSW_mskDEX		( 0x1  << PSW_offDEX )
#घोषणा PSW_mskHSS		( 0x1  << PSW_offHSS )
#घोषणा PSW_mskDRBE		( 0x1  << PSW_offDRBE )
#घोषणा PSW_mskAEN		( 0x1  << PSW_offAEN )
#घोषणा PSW_mskWBNA		( 0x1  << PSW_offWBNA )
#घोषणा PSW_mskIFCON		( 0x1  << PSW_offIFCON )
#घोषणा PSW_mskCPL		( 0x7  << PSW_offCPL )

#घोषणा PSW_SYSTEM		( 1 << PSW_offPOM )
#घोषणा PSW_INTL_1		( 1 << PSW_offINTL )
#घोषणा PSW_CPL_NO		( 0 << PSW_offCPL )
#घोषणा PSW_CPL_ANY		( 7 << PSW_offCPL )

#घोषणा PSW_clr			(PSW_mskGIE|PSW_mskINTL|PSW_mskPOM|PSW_mskIT|PSW_mskDT|PSW_mskIME|PSW_mskWBNA)
#अगर_घोषित __NDS32_EB__
#अगर_घोषित CONFIG_WBNA
#घोषणा PSW_init		(PSW_mskWBNA|(1<<PSW_offINTL)|(1<<PSW_offPOM)|PSW_mskIT|PSW_mskDT|PSW_mskBE)
#अन्यथा
#घोषणा PSW_init		((1<<PSW_offINTL)|(1<<PSW_offPOM)|PSW_mskIT|PSW_mskDT|PSW_mskBE)
#पूर्ण_अगर
#अन्यथा
#अगर_घोषित CONFIG_WBNA
#घोषणा PSW_init		(PSW_mskWBNA|(1<<PSW_offINTL)|(1<<PSW_offPOM)|PSW_mskIT|PSW_mskDT)
#अन्यथा
#घोषणा PSW_init		((1<<PSW_offINTL)|(1<<PSW_offPOM)|PSW_mskIT|PSW_mskDT)
#पूर्ण_अगर
#पूर्ण_अगर
/******************************************************************************
 * ir3: IVB (Interruption Vector Base Register)
 *****************************************************************************/
/* bit 0:12 reserved */
#घोषणा IVB_offNIVIC		1	/* Number of input क्रम IVIC Controller */
#घोषणा IVB_offIVIC_VER		11	/* IVIC Version */
#घोषणा IVB_offEVIC		13	/* External Vector Interrupt Controller mode */
#घोषणा IVB_offESZ		14	/* Size of each vector entry */
#घोषणा IVB_offIVBASE		16	/* BasePA of पूर्णांकerrupt vector table */

#घोषणा IVB_mskNIVIC		( 0x7  << IVB_offNIVIC )
#घोषणा IVB_mskIVIC_VER		( 0x3  << IVB_offIVIC_VER )
#घोषणा IVB_mskEVIC		( 0x1  << IVB_offEVIC )
#घोषणा IVB_mskESZ		( 0x3  << IVB_offESZ )
#घोषणा IVB_mskIVBASE		( 0xFFFF  << IVB_offIVBASE )

#घोषणा IVB_valESZ4		0
#घोषणा IVB_valESZ16		1
#घोषणा IVB_valESZ64		2
#घोषणा IVB_valESZ256		3
/******************************************************************************
 * ir4: EVA (Exception Virtual Address Register)
 * ir5: P_EVA (Previous EVA Register)
 *****************************************************************************/

	/* This रेजिस्टर contains the VA that causes the exception */

/******************************************************************************
 * ir6: ITYPE (Interruption Type Register)
 * ir7: P_ITYPE (Previous ITYPE Register)
 *****************************************************************************/
#घोषणा ITYPE_offETYPE		0	/* Exception Type */
#घोषणा ITYPE_offINST		4	/* Exception caused by insn fetch or data access */
/* bit 5:15 reserved */
#घोषणा ITYPE_offVECTOR		5	/* Vector */
#घोषणा ITYPE_offSWID		16	/* SWID of debugging exception */
/* bit 31:31 reserved */

#घोषणा ITYPE_mskETYPE		( 0xF  << ITYPE_offETYPE )
#घोषणा ITYPE_mskINST		( 0x1  << ITYPE_offINST )
#घोषणा ITYPE_mskVECTOR		( 0x7F  << ITYPE_offVECTOR )
#घोषणा ITYPE_mskSWID		( 0x7FFF  << ITYPE_offSWID )

/* Additional definitions क्रम ITYPE रेजिस्टर */
#घोषणा ITYPE_offSTYPE          16	/* Arithmetic Sub Type */
#घोषणा ITYPE_offCPID           20	/* Co-Processor ID which generate the exception */

#घोषणा ITYPE_mskSTYPE		( 0xF  << ITYPE_offSTYPE )
#घोषणा ITYPE_mskCPID		( 0x3  << ITYPE_offCPID )

/* Additional definitions of ITYPE रेजिस्टर क्रम FPU */
#घोषणा FPU_DISABLE_EXCEPTION	(0x1  << ITYPE_offSTYPE)
#घोषणा FPU_EXCEPTION		(0x2  << ITYPE_offSTYPE)
#घोषणा FPU_CPID		0	/* FPU Co-Processor ID is 0 */

#घोषणा NDS32_VECTOR_mskNONEXCEPTION	0x78
#घोषणा NDS32_VECTOR_offEXCEPTION	8
#घोषणा NDS32_VECTOR_offINTERRUPT	9

/* Interrupt vector entry */
#घोषणा ENTRY_RESET_NMI			0
#घोषणा ENTRY_TLB_FILL			1
#घोषणा ENTRY_PTE_NOT_PRESENT		2
#घोषणा ENTRY_TLB_MISC			3
#घोषणा ENTRY_TLB_VLPT_MISS		4
#घोषणा ENTRY_MACHINE_ERROR		5
#घोषणा ENTRY_DEBUG_RELATED		6
#घोषणा ENTRY_GENERAL_EXCPETION		7
#घोषणा ENTRY_SYSCALL			8

/* PTE not present exception definition */
#घोषणा ETYPE_NON_LEAF_PTE_NOT_PRESENT	0
#घोषणा ETYPE_LEAF_PTE_NOT_PRESENT	1

/* General exception ETYPE definition */
#घोषणा ETYPE_ALIGNMENT_CHECK		0
#घोषणा ETYPE_RESERVED_INSTRUCTION	1
#घोषणा ETYPE_TRAP			2
#घोषणा ETYPE_ARITHMETIC		3
#घोषणा ETYPE_PRECISE_BUS_ERROR		4
#घोषणा ETYPE_IMPRECISE_BUS_ERROR	5
#घोषणा ETYPE_COPROCESSOR		6
#घोषणा ETYPE_RESERVED_VALUE		7
#घोषणा ETYPE_NONEXISTENT_MEM_ADDRESS	8
#घोषणा ETYPE_MPZIU_CONTROL		9
#घोषणा ETYPE_NEXT_PRECISE_STACK_OFL	10

/* Kerenl reserves software ID */
#घोषणा SWID_RAISE_INTERRUPT_LEVEL	0x1a	/* SWID_RAISE_INTERRUPT_LEVEL is used to
						 * उठाओ पूर्णांकerrupt level क्रम debug exception
						 */

/******************************************************************************
 * ir8: MERR (Machine Error Log Register)
 *****************************************************************************/
/* bit 0:30 reserved */
#घोषणा MERR_offBUSERR		31	/* Bus error caused by a load insn */

#घोषणा MERR_mskBUSERR		( 0x1  << MERR_offBUSERR )

/******************************************************************************
 * ir9: IPC (Interruption Program Counter Register)
 * ir10: P_IPC (Previous IPC Register)
 * ir11: OIPC (Overflow Interruption Program Counter Register)
 *****************************************************************************/

	/* This is the shaकरोw stack रेजिस्टर of the Program Counter */

/******************************************************************************
 * ir12: P_P0 (Previous P0 Register)
 * ir13: P_P1 (Previous P1 Register)
 *****************************************************************************/

	/* These are shaकरोw रेजिस्टरs of $p0 and $p1 */

/******************************************************************************
 * ir14: INT_MASK (Interruption Masking Register)
 *****************************************************************************/
#घोषणा INT_MASK_offH0IM	0	/* Hardware Interrupt 0 Mask bit */
#घोषणा INT_MASK_offH1IM	1	/* Hardware Interrupt 1 Mask bit */
#घोषणा INT_MASK_offH2IM	2	/* Hardware Interrupt 2 Mask bit */
#घोषणा INT_MASK_offH3IM	3	/* Hardware Interrupt 3 Mask bit */
#घोषणा INT_MASK_offH4IM	4	/* Hardware Interrupt 4 Mask bit */
#घोषणा INT_MASK_offH5IM	5	/* Hardware Interrupt 5 Mask bit */
/* bit 6:15 reserved */
#घोषणा INT_MASK_offSIM		16	/* Software Interrupt Mask bit */
/* bit 17:29 reserved */
#घोषणा INT_MASK_offIDIVZE	30	/* Enable detection क्रम Divide-By-Zero */
#घोषणा INT_MASK_offDSSIM	31	/* Default Single Stepping Interruption Mask */

#घोषणा INT_MASK_mskH0IM	( 0x1  << INT_MASK_offH0IM )
#घोषणा INT_MASK_mskH1IM	( 0x1  << INT_MASK_offH1IM )
#घोषणा INT_MASK_mskH2IM	( 0x1  << INT_MASK_offH2IM )
#घोषणा INT_MASK_mskH3IM	( 0x1  << INT_MASK_offH3IM )
#घोषणा INT_MASK_mskH4IM	( 0x1  << INT_MASK_offH4IM )
#घोषणा INT_MASK_mskH5IM	( 0x1  << INT_MASK_offH5IM )
#घोषणा INT_MASK_mskSIM		( 0x1  << INT_MASK_offSIM )
#घोषणा INT_MASK_mskIDIVZE	( 0x1  << INT_MASK_offIDIVZE )
#घोषणा INT_MASK_mskDSSIM	( 0x1  << INT_MASK_offDSSIM )

#घोषणा INT_MASK_INITAIAL_VAL	(INT_MASK_mskDSSIM|INT_MASK_mskIDIVZE)

/******************************************************************************
 * ir15: INT_PEND (Interrupt Pending Register)
 *****************************************************************************/
#घोषणा INT_PEND_offH0I		0	/* Hardware Interrupt 0 pending bit */
#घोषणा INT_PEND_offH1I		1	/* Hardware Interrupt 1 pending bit */
#घोषणा INT_PEND_offH2I		2	/* Hardware Interrupt 2 pending bit */
#घोषणा INT_PEND_offH3I		3	/* Hardware Interrupt 3 pending bit */
#घोषणा INT_PEND_offH4I		4	/* Hardware Interrupt 4 pending bit */
#घोषणा INT_PEND_offH5I		5	/* Hardware Interrupt 5 pending bit */

#घोषणा INT_PEND_offCIPL	0	/* Current Interrupt Priority Level */

/* bit 6:15 reserved */
#घोषणा INT_PEND_offSWI		16	/* Software Interrupt pending bit */
/* bit 17:31 reserved */

#घोषणा INT_PEND_mskH0I		( 0x1  << INT_PEND_offH0I )
#घोषणा INT_PEND_mskH1I		( 0x1  << INT_PEND_offH1I )
#घोषणा INT_PEND_mskH2I		( 0x1  << INT_PEND_offH2I )
#घोषणा INT_PEND_mskH3I		( 0x1  << INT_PEND_offH3I )
#घोषणा INT_PEND_mskH4I		( 0x1  << INT_PEND_offH4I )
#घोषणा INT_PEND_mskH5I		( 0x1  << INT_PEND_offH5I )
#घोषणा INT_PEND_mskCIPL	( 0x1  << INT_PEND_offCIPL )
#घोषणा INT_PEND_mskSWI		( 0x1  << INT_PEND_offSWI )

/******************************************************************************
 * mr0: MMU_CTL (MMU Control Register)
 *****************************************************************************/
#घोषणा MMU_CTL_offD		0	/* Default minimum page size */
#घोषणा MMU_CTL_offNTC0		1	/* Non-Translated Cachebility of partition 0 */
#घोषणा MMU_CTL_offNTC1		3	/* Non-Translated Cachebility of partition 1 */
#घोषणा MMU_CTL_offNTC2		5	/* Non-Translated Cachebility of partition 2 */
#घोषणा MMU_CTL_offNTC3		7	/* Non-Translated Cachebility of partition 3 */
#घोषणा MMU_CTL_offTBALCK	9	/* TLB all-lock resolution scheme */
#घोषणा MMU_CTL_offMPZIU	10	/* Multiple Page Size In Use bit */
#घोषणा MMU_CTL_offNTM0		11	/* Non-Translated VA to PA of partition 0 */
#घोषणा MMU_CTL_offNTM1		13	/* Non-Translated VA to PA of partition 1 */
#घोषणा MMU_CTL_offNTM2		15	/* Non-Translated VA to PA of partition 2 */
#घोषणा MMU_CTL_offNTM3		17	/* Non-Translated VA to PA of partition 3 */
#घोषणा MMU_CTL_offUNA		23	/* Unaligned access */
/* bit 24:31 reserved */

#घोषणा MMU_CTL_mskD		( 0x1  << MMU_CTL_offD )
#घोषणा MMU_CTL_mskNTC0		( 0x3  << MMU_CTL_offNTC0 )
#घोषणा MMU_CTL_mskNTC1		( 0x3  << MMU_CTL_offNTC1 )
#घोषणा MMU_CTL_mskNTC2		( 0x3  << MMU_CTL_offNTC2 )
#घोषणा MMU_CTL_mskNTC3		( 0x3  << MMU_CTL_offNTC3 )
#घोषणा MMU_CTL_mskTBALCK	( 0x1  << MMU_CTL_offTBALCK )
#घोषणा MMU_CTL_mskMPZIU	( 0x1  << MMU_CTL_offMPZIU )
#घोषणा MMU_CTL_mskNTM0		( 0x3  << MMU_CTL_offNTM0 )
#घोषणा MMU_CTL_mskNTM1         ( 0x3  << MMU_CTL_offNTM1 )
#घोषणा MMU_CTL_mskNTM2         ( 0x3  << MMU_CTL_offNTM2 )
#घोषणा MMU_CTL_mskNTM3         ( 0x3  << MMU_CTL_offNTM3 )

#घोषणा MMU_CTL_D4KB		0
#घोषणा MMU_CTL_D8KB		1
#घोषणा MMU_CTL_UNA		( 0x1  << MMU_CTL_offUNA )

#घोषणा MMU_CTL_CACHEABLE_NON   0
#घोषणा MMU_CTL_CACHEABLE_WB	2
#घोषणा MMU_CTL_CACHEABLE_WT	3

/******************************************************************************
 * mr1: L1_PPTB (L1 Physical Page Table Base Register)
 *****************************************************************************/
#घोषणा L1_PPTB_offNV		0	/* Enable Hardware Page Table Walker (HPTWK) */
/* bit 1:11 reserved */
#घोषणा L1_PPTB_offBASE		12	/* First level physical page table base address */

#घोषणा L1_PPTB_mskNV		( 0x1  << L1_PPTB_offNV )
#घोषणा L1_PPTB_mskBASE		( 0xFFFFF  << L1_PPTB_offBASE )

/******************************************************************************
 * mr2: TLB_VPN (TLB Access VPN Register)
 *****************************************************************************/
/* bit 0:11 reserved */
#घोषणा TLB_VPN_offVPN		12	/* Virtual Page Number */

#घोषणा TLB_VPN_mskVPN		( 0xFFFFF  << TLB_VPN_offVPN )

/******************************************************************************
 * mr3: TLB_DATA (TLB Access Data Register)
 *****************************************************************************/
#घोषणा TLB_DATA_offV		0	/* PTE is valid and present */
#घोषणा TLB_DATA_offM		1	/* Page पढ़ो/ग_लिखो access privilege */
#घोषणा TLB_DATA_offD		4	/* Dirty bit */
#घोषणा TLB_DATA_offX		5	/* Executable bit */
#घोषणा TLB_DATA_offA		6	/* Access bit */
#घोषणा TLB_DATA_offG		7	/* Global page (shared across contexts) */
#घोषणा TLB_DATA_offC		8	/* Cacheability atribute */
/* bit 11:11 reserved */
#घोषणा TLB_DATA_offPPN		12	/* Phisical Page Number */

#घोषणा TLB_DATA_mskV		( 0x1  << TLB_DATA_offV )
#घोषणा TLB_DATA_mskM		( 0x7  << TLB_DATA_offM )
#घोषणा TLB_DATA_mskD		( 0x1  << TLB_DATA_offD )
#घोषणा TLB_DATA_mskX		( 0x1  << TLB_DATA_offX )
#घोषणा TLB_DATA_mskA		( 0x1  << TLB_DATA_offA )
#घोषणा TLB_DATA_mskG		( 0x1  << TLB_DATA_offG )
#घोषणा TLB_DATA_mskC		( 0x7  << TLB_DATA_offC )
#घोषणा TLB_DATA_mskPPN		( 0xFFFFF  << TLB_DATA_offPPN )

#अगर_घोषित CONFIG_CPU_DCACHE_WRITETHROUGH
#घोषणा TLB_DATA_kernel_text_attr	(TLB_DATA_mskV|TLB_DATA_mskM|TLB_DATA_mskD|TLB_DATA_mskX|TLB_DATA_mskG|TLB_DATA_mskC)
#अन्यथा
#घोषणा TLB_DATA_kernel_text_attr	(TLB_DATA_mskV|TLB_DATA_mskM|TLB_DATA_mskD|TLB_DATA_mskX|TLB_DATA_mskG|(0x6 << TLB_DATA_offC))
#पूर्ण_अगर

/******************************************************************************
 * mr4: TLB_MISC (TLB Access Misc Register)
 *****************************************************************************/
#घोषणा TLB_MISC_offACC_PSZ	0	/* Page size of a PTE entry */
#घोषणा TLB_MISC_offCID		4	/* Context id */
/* bit 13:31 reserved */

#घोषणा TLB_MISC_mskACC_PSZ    ( 0xF  << TLB_MISC_offACC_PSZ )
#घोषणा TLB_MISC_mskCID        ( 0x1FF  << TLB_MISC_offCID )

/******************************************************************************
 * mr5: VLPT_IDX (Virtual Linear Page Table Index Register)
 *****************************************************************************/
#घोषणा VLPT_IDX_offZERO	0	/* Always 0 */
#घोषणा VLPT_IDX_offEVPN	2	/* Exception Virtual Page Number */
#घोषणा VLPT_IDX_offVLPTB	22	/* Base VA of VLPT */

#घोषणा VLPT_IDX_mskZERO	( 0x3  << VLPT_IDX_offZERO )
#घोषणा VLPT_IDX_mskEVPN	( 0xFFFFF  << VLPT_IDX_offEVPN )
#घोषणा VLPT_IDX_mskVLPTB	( 0x3FF  << VLPT_IDX_offVLPTB )

/******************************************************************************
 * mr6: ILMB (Inकाष्ठाion Local Memory Base Register)
 *****************************************************************************/
#घोषणा ILMB_offIEN		0	/* Enable ILM */
#घोषणा ILMB_offILMSZ		1	/* Size of ILM */
/* bit 5:19 reserved */
#घोषणा ILMB_offIBPA		20	/* Base PA of ILM */

#घोषणा ILMB_mskIEN		( 0x1  << ILMB_offIEN )
#घोषणा ILMB_mskILMSZ		( 0xF  << ILMB_offILMSZ )
#घोषणा ILMB_mskIBPA		( 0xFFF  << ILMB_offIBPA )

/******************************************************************************
 * mr7: DLMB (Data Local Memory Base Register)
 *****************************************************************************/
#घोषणा DLMB_offDEN		0	/* Enable DLM */
#घोषणा DLMB_offDLMSZ		1	/* Size of DLM */
#घोषणा DLMB_offDBM		5	/* Enable Double-Buffer Mode क्रम DLM */
#घोषणा DLMB_offDBB		6	/* Double-buffer bank which can be accessed by the processor */
/* bit 7:19 reserved */
#घोषणा DLMB_offDBPA		20	/* Base PA of DLM */

#घोषणा DLMB_mskDEN		( 0x1  << DLMB_offDEN )
#घोषणा DLMB_mskDLMSZ		( 0xF  << DLMB_offDLMSZ )
#घोषणा DLMB_mskDBM		( 0x1  << DLMB_offDBM )
#घोषणा DLMB_mskDBB		( 0x1  << DLMB_offDBB )
#घोषणा DLMB_mskDBPA		( 0xFFF  << DLMB_offDBPA )

/******************************************************************************
 * mr8: CACHE_CTL (Cache Control Register)
 *****************************************************************************/
#घोषणा CACHE_CTL_offIC_EN	0	/* Enable I-cache */
#घोषणा CACHE_CTL_offDC_EN	1	/* Enable D-cache */
#घोषणा CACHE_CTL_offICALCK	2	/* I-cache all-lock resolution scheme */
#घोषणा CACHE_CTL_offDCALCK	3	/* D-cache all-lock resolution scheme */
#घोषणा CACHE_CTL_offDCCWF	4	/* Enable D-cache Critical Word Forwarding */
#घोषणा CACHE_CTL_offDCPMW	5	/* Enable D-cache concurrent miss and ग_लिखो-back processing */
/* bit 6:31 reserved */

#घोषणा CACHE_CTL_mskIC_EN	( 0x1  << CACHE_CTL_offIC_EN )
#घोषणा CACHE_CTL_mskDC_EN	( 0x1  << CACHE_CTL_offDC_EN )
#घोषणा CACHE_CTL_mskICALCK	( 0x1  << CACHE_CTL_offICALCK )
#घोषणा CACHE_CTL_mskDCALCK	( 0x1  << CACHE_CTL_offDCALCK )
#घोषणा CACHE_CTL_mskDCCWF	( 0x1  << CACHE_CTL_offDCCWF )
#घोषणा CACHE_CTL_mskDCPMW	( 0x1  << CACHE_CTL_offDCPMW )

/******************************************************************************
 * mr9: HSMP_SADDR (High Speed Memory Port Starting Address)
 *****************************************************************************/
#घोषणा HSMP_SADDR_offEN	0	/* Enable control bit क्रम the High Speed Memory port */
/* bit 1:19 reserved */

#घोषणा HSMP_SADDR_offRANGE	1	/* Denote the address range (only defined in HSMP v2 ) */
#घोषणा HSMP_SADDR_offSADDR	20	/* Starting base PA of the High Speed Memory Port region */

#घोषणा HSMP_SADDR_mskEN	( 0x1  << HSMP_SADDR_offEN )
#घोषणा HSMP_SADDR_mskRANGE	( 0xFFF  << HSMP_SADDR_offRANGE )
#घोषणा HSMP_SADDR_mskSADDR	( 0xFFF  << HSMP_SADDR_offSADDR )

/******************************************************************************
 * mr10: HSMP_EADDR (High Speed Memory Port Ending Address)
 *****************************************************************************/
/* bit 0:19 reserved */
#घोषणा HSMP_EADDR_offEADDR	20

#घोषणा HSMP_EADDR_mskEADDR	( 0xFFF  << HSMP_EADDR_offEADDR )

/******************************************************************************
 * dr0+(n*5): BPCn (n=0-7) (Breakpoपूर्णांक Control Register)
 *****************************************************************************/
#घोषणा BPC_offWP		0	/* Configuration of BPAn */
#घोषणा BPC_offEL		1	/* Enable BPAn */
#घोषणा BPC_offS		2	/* Data address comparison क्रम a store inकाष्ठाion */
#घोषणा BPC_offP		3	/* Compared data address is PA */
#घोषणा BPC_offC		4	/* CID value is compared with the BPCIDn रेजिस्टर */
#घोषणा BPC_offBE0		5	/* Enable byte mask क्रम the comparison with रेजिस्टर */
#घोषणा BPC_offBE1		6	/* Enable byte mask क्रम the comparison with रेजिस्टर */
#घोषणा BPC_offBE2		7	/* Enable byte mask क्रम the comparison with रेजिस्टर */
#घोषणा BPC_offBE3		8	/* Enable byte mask क्रम the comparison with रेजिस्टर */
#घोषणा BPC_offT		9	/* Enable अवरोधpoपूर्णांक Embedded Tracer triggering operation */

#घोषणा BPC_mskWP		( 0x1  << BPC_offWP )
#घोषणा BPC_mskEL		( 0x1  << BPC_offEL )
#घोषणा BPC_mskS		( 0x1  << BPC_offS )
#घोषणा BPC_mskP		( 0x1  << BPC_offP )
#घोषणा BPC_mskC		( 0x1  << BPC_offC )
#घोषणा BPC_mskBE0		( 0x1  << BPC_offBE0 )
#घोषणा BPC_mskBE1		( 0x1  << BPC_offBE1 )
#घोषणा BPC_mskBE2		( 0x1  << BPC_offBE2 )
#घोषणा BPC_mskBE3		( 0x1  << BPC_offBE3 )
#घोषणा BPC_mskT		( 0x1  << BPC_offT )

/******************************************************************************
 * dr1+(n*5): BPAn (n=0-7) (Breakpoपूर्णांक Address Register)
 *****************************************************************************/

	/* These रेजिस्टरs contain अवरोध poपूर्णांक address */

/******************************************************************************
 * dr2+(n*5): BPAMn (n=0-7) (Breakpoपूर्णांक Address Mask Register)
 *****************************************************************************/

	/* These रेजिस्टरd contain the address comparison mask क्रम the BPAn रेजिस्टर */

/******************************************************************************
 * dr3+(n*5): BPVn (n=0-7) Breakpoपूर्णांक Data Value Register
 *****************************************************************************/

	/* The BPVn रेजिस्टर contains the data value that will be compared with the
	 * incoming load/store data value */

/******************************************************************************
 * dr4+(n*5): BPCIDn (n=0-7) (Breakpoपूर्णांक Context ID Register)
 *****************************************************************************/
#घोषणा BPCID_offCID		0	/* CID that will be compared with a process's CID */
/* bit 9:31 reserved */

#घोषणा BPCID_mskCID		( 0x1FF  << BPCID_offCID )

/******************************************************************************
 * dr40: EDM_CFG (EDM Configuration Register)
 *****************************************************************************/
#घोषणा EDM_CFG_offBC		0	/* Number of hardware अवरोधpoपूर्णांक sets implemented */
#घोषणा EDM_CFG_offDIMU		3	/* Debug Inकाष्ठाion Memory Unit exists */
/* bit 4:15 reserved */
#घोषणा EDM_CFG_offVER		16	/* EDM version */

#घोषणा EDM_CFG_mskBC		( 0x7  << EDM_CFG_offBC )
#घोषणा EDM_CFG_mskDIMU		( 0x1  << EDM_CFG_offDIMU )
#घोषणा EDM_CFG_mskVER		( 0xFFFF  << EDM_CFG_offVER )

/******************************************************************************
 * dr41: EDMSW (EDM Status Word)
 *****************************************************************************/
#घोषणा EDMSW_offWV		0	/* Write Valid */
#घोषणा EDMSW_offRV		1	/* Read Valid */
#घोषणा EDMSW_offDE		2	/* Debug exception has occurred क्रम this core */
/* bit 3:31 reserved */

#घोषणा EDMSW_mskWV		( 0x1  << EDMSW_offWV )
#घोषणा EDMSW_mskRV		( 0x1  << EDMSW_offRV )
#घोषणा EDMSW_mskDE		( 0x1  << EDMSW_offDE )

/******************************************************************************
 * dr42: EDM_CTL (EDM Control Register)
 *****************************************************************************/
/* bit 0:30 reserved */
#घोषणा EDM_CTL_offV3_EDM_MODE	6	/* EDM compatibility control bit */
#घोषणा EDM_CTL_offDEH_SEL	31	/* Controls where debug exception is directed to */

#घोषणा EDM_CTL_mskV3_EDM_MODE	( 0x1 << EDM_CTL_offV3_EDM_MODE )
#घोषणा EDM_CTL_mskDEH_SEL	( 0x1 << EDM_CTL_offDEH_SEL )

/******************************************************************************
 * dr43: EDM_DTR (EDM Data Transfer Register)
 *****************************************************************************/

	/* This is used to exchange data between the embedded EDM logic
	 * and the processor core */

/******************************************************************************
 * dr44: BPMTC (Breakpoपूर्णांक Match Trigger Counter Register)
 *****************************************************************************/
#घोषणा BPMTC_offBPMTC		0	/* Breakpoपूर्णांक match trigger counter value */
/* bit 16:31 reserved */

#घोषणा BPMTC_mskBPMTC		( 0xFFFF  << BPMTC_offBPMTC )

/******************************************************************************
 * dr45: DIMBR (Debug Inकाष्ठाion Memory Base Register)
 *****************************************************************************/
/* bit 0:11 reserved */
#घोषणा DIMBR_offDIMB		12	/* Base address of the Debug Inकाष्ठाion Memory (DIM) */
#घोषणा DIMBR_mskDIMB		( 0xFFFFF  << DIMBR_offDIMB )

/******************************************************************************
 * dr46: TECR0(Trigger Event Control रेजिस्टर 0)
 * dr47: TECR1 (Trigger Event Control रेजिस्टर 1)
 *****************************************************************************/
#घोषणा TECR_offBP		0	/* Controld which BP is used as a trigger source */
#घोषणा TECR_offNMI		8	/* Use NMI as a trigger source */
#घोषणा TECR_offHWINT		9	/* Corresponding पूर्णांकerrupt is used as a trigger source */
#घोषणा TECR_offEVIC		15	/* Enable HWINT as a trigger source in EVIC mode */
#घोषणा TECR_offSYS		16	/* Enable SYSCALL inकाष्ठाion as a trigger source */
#घोषणा TECR_offDBG		17	/* Enable debug exception as a trigger source */
#घोषणा TECR_offMRE		18	/* Enable MMU related exception as a trigger source */
#घोषणा TECR_offE		19	/* An exception is used as a trigger source */
/* bit 20:30 reserved */
#घोषणा TECR_offL		31	/* Link/Cascade TECR0 trigger event to TECR1 trigger event */

#घोषणा TECR_mskBP		( 0xFF  << TECR_offBP )
#घोषणा TECR_mskNMI		( 0x1  << TECR_offBNMI )
#घोषणा TECR_mskHWINT		( 0x3F  << TECR_offBHWINT )
#घोषणा TECR_mskEVIC		( 0x1  << TECR_offBEVIC )
#घोषणा TECR_mskSYS		( 0x1  << TECR_offBSYS )
#घोषणा TECR_mskDBG		( 0x1  << TECR_offBDBG )
#घोषणा TECR_mskMRE		( 0x1  << TECR_offBMRE )
#घोषणा TECR_mskE		( 0x1  << TECR_offE )
#घोषणा TECR_mskL		( 0x1  << TECR_offL )

/******************************************************************************
 * pfr0-2: PFMC0-2 (Perक्रमmance Counter Register 0-2)
 *****************************************************************************/

	/* These रेजिस्टरs contains perक्रमmance event count */

/******************************************************************************
 * pfr3: PFM_CTL (Perक्रमmance Counter Control Register)
 *****************************************************************************/
#घोषणा PFM_CTL_offEN0		0	/* Enable PFMC0 */
#घोषणा PFM_CTL_offEN1		1	/* Enable PFMC1 */
#घोषणा PFM_CTL_offEN2		2	/* Enable PFMC2 */
#घोषणा PFM_CTL_offIE0		3	/* Enable पूर्णांकerrupt क्रम PFMC0 */
#घोषणा PFM_CTL_offIE1		4	/* Enable पूर्णांकerrupt क्रम PFMC1 */
#घोषणा PFM_CTL_offIE2		5	/* Enable पूर्णांकerrupt क्रम PFMC2 */
#घोषणा PFM_CTL_offOVF0		6	/* Overflow bit of PFMC0 */
#घोषणा PFM_CTL_offOVF1		7	/* Overflow bit of PFMC1 */
#घोषणा PFM_CTL_offOVF2		8	/* Overflow bit of PFMC2 */
#घोषणा PFM_CTL_offKS0		9	/* Enable superuser mode event counting क्रम PFMC0 */
#घोषणा PFM_CTL_offKS1		10	/* Enable superuser mode event counting क्रम PFMC1 */
#घोषणा PFM_CTL_offKS2		11	/* Enable superuser mode event counting क्रम PFMC2 */
#घोषणा PFM_CTL_offKU0		12	/* Enable user mode event counting क्रम PFMC0 */
#घोषणा PFM_CTL_offKU1		13	/* Enable user mode event counting क्रम PFMC1 */
#घोषणा PFM_CTL_offKU2		14	/* Enable user mode event counting क्रम PFMC2 */
#घोषणा PFM_CTL_offSEL0		15	/* The event selection क्रम PFMC0 */
#घोषणा PFM_CTL_offSEL1		16	/* The event selection क्रम PFMC1 */
#घोषणा PFM_CTL_offSEL2		22	/* The event selection क्रम PFMC2 */
/* bit 28:31 reserved */

#घोषणा PFM_CTL_mskEN0		( 0x01  << PFM_CTL_offEN0 )
#घोषणा PFM_CTL_mskEN1		( 0x01  << PFM_CTL_offEN1 )
#घोषणा PFM_CTL_mskEN2		( 0x01  << PFM_CTL_offEN2 )
#घोषणा PFM_CTL_mskIE0		( 0x01  << PFM_CTL_offIE0 )
#घोषणा PFM_CTL_mskIE1		( 0x01  << PFM_CTL_offIE1 )
#घोषणा PFM_CTL_mskIE2		( 0x01  << PFM_CTL_offIE2 )
#घोषणा PFM_CTL_mskOVF0		( 0x01  << PFM_CTL_offOVF0 )
#घोषणा PFM_CTL_mskOVF1		( 0x01  << PFM_CTL_offOVF1 )
#घोषणा PFM_CTL_mskOVF2		( 0x01  << PFM_CTL_offOVF2 )
#घोषणा PFM_CTL_mskKS0		( 0x01  << PFM_CTL_offKS0 )
#घोषणा PFM_CTL_mskKS1		( 0x01  << PFM_CTL_offKS1 )
#घोषणा PFM_CTL_mskKS2		( 0x01  << PFM_CTL_offKS2 )
#घोषणा PFM_CTL_mskKU0		( 0x01  << PFM_CTL_offKU0 )
#घोषणा PFM_CTL_mskKU1		( 0x01  << PFM_CTL_offKU1 )
#घोषणा PFM_CTL_mskKU2		( 0x01  << PFM_CTL_offKU2 )
#घोषणा PFM_CTL_mskSEL0		( 0x01  << PFM_CTL_offSEL0 )
#घोषणा PFM_CTL_mskSEL1		( 0x3F  << PFM_CTL_offSEL1 )
#घोषणा PFM_CTL_mskSEL2		( 0x3F  << PFM_CTL_offSEL2 )

/******************************************************************************
 * SDZ_CTL (Structure Downsizing Control Register)
 *****************************************************************************/
#घोषणा SDZ_CTL_offICDZ		0	/* I-cache करोwnsizing control */
#घोषणा SDZ_CTL_offDCDZ		3	/* D-cache करोwnsizing control */
#घोषणा SDZ_CTL_offMTBDZ	6	/* MTLB करोwnsizing control */
#घोषणा SDZ_CTL_offBTBDZ	9	/* Branch Target Table करोwnsizing control */
/* bit 12:31 reserved */
#घोषणा SDZ_CTL_mskICDZ		( 0x07  << SDZ_CTL_offICDZ )
#घोषणा SDZ_CTL_mskDCDZ		( 0x07  << SDZ_CTL_offDCDZ )
#घोषणा SDZ_CTL_mskMTBDZ	( 0x07  << SDZ_CTL_offMTBDZ )
#घोषणा SDZ_CTL_mskBTBDZ	( 0x07  << SDZ_CTL_offBTBDZ )

/******************************************************************************
 * N13MISC_CTL (N13 Miscellaneous Control Register)
 *****************************************************************************/
#घोषणा N13MISC_CTL_offBTB	0	/* Disable Branch Target Buffer */
#घोषणा N13MISC_CTL_offRTP	1	/* Disable Return Target Predictor */
#घोषणा N13MISC_CTL_offPTEPF	2	/* Disable HPTWK L2 PTE pefetch */
#घोषणा N13MISC_CTL_offSP_SHADOW_EN	4	/* Enable shaकरोw stack poपूर्णांकers */
#घोषणा MISC_CTL_offHWPRE      11      /* Enable HardWare PREFETCH */
/* bit 6, 9:31 reserved */

#घोषणा N13MISC_CTL_makBTB	( 0x1  << N13MISC_CTL_offBTB )
#घोषणा N13MISC_CTL_makRTP	( 0x1  << N13MISC_CTL_offRTP )
#घोषणा N13MISC_CTL_makPTEPF	( 0x1  << N13MISC_CTL_offPTEPF )
#घोषणा N13MISC_CTL_makSP_SHADOW_EN	( 0x1  << N13MISC_CTL_offSP_SHADOW_EN )
#घोषणा MISC_CTL_makHWPRE_EN     ( 0x1  << MISC_CTL_offHWPRE )

#अगर_घोषित CONFIG_HW_PRE
#घोषणा MISC_init	(N13MISC_CTL_makBTB|N13MISC_CTL_makRTP|N13MISC_CTL_makSP_SHADOW_EN|MISC_CTL_makHWPRE_EN)
#अन्यथा
#घोषणा MISC_init	(N13MISC_CTL_makBTB|N13MISC_CTL_makRTP|N13MISC_CTL_makSP_SHADOW_EN)
#पूर्ण_अगर

/******************************************************************************
 * PRUSR_ACC_CTL (Privileged Resource User Access Control Registers)
 *****************************************************************************/
#घोषणा PRUSR_ACC_CTL_offDMA_EN	0	/* Allow user mode access of DMA रेजिस्टरs */
#घोषणा PRUSR_ACC_CTL_offPFM_EN	1	/* Allow user mode access of PFM रेजिस्टरs */

#घोषणा PRUSR_ACC_CTL_mskDMA_EN	( 0x1  << PRUSR_ACC_CTL_offDMA_EN )
#घोषणा PRUSR_ACC_CTL_mskPFM_EN	( 0x1  << PRUSR_ACC_CTL_offPFM_EN )

/******************************************************************************
 * dmar0: DMA_CFG (DMA Configuration Register)
 *****************************************************************************/
#घोषणा DMA_CFG_offNCHN		0	/* The number of DMA channels implemented */
#घोषणा DMA_CFG_offUNEA		2	/* Un-aligned External Address transfer feature */
#घोषणा DMA_CFG_off2DET		3	/* 2-D Element Transfer feature */
/* bit 4:15 reserved */
#घोषणा DMA_CFG_offVER		16	/* DMA architecture and implementation version */

#घोषणा DMA_CFG_mskNCHN		( 0x3  << DMA_CFG_offNCHN )
#घोषणा DMA_CFG_mskUNEA		( 0x1  << DMA_CFG_offUNEA )
#घोषणा DMA_CFG_msk2DET		( 0x1  << DMA_CFG_off2DET )
#घोषणा DMA_CFG_mskVER		( 0xFFFF  << DMA_CFG_offVER )

/******************************************************************************
 * dmar1: DMA_GCSW (DMA Global Control and Status Word Register)
 *****************************************************************************/
#घोषणा DMA_GCSW_offC0STAT	0	/* DMA channel 0 state */
#घोषणा DMA_GCSW_offC1STAT	3	/* DMA channel 1 state */
/* bit 6:11 reserved */
#घोषणा DMA_GCSW_offC0INT	12	/* DMA channel 0 generate पूर्णांकerrupt */
#घोषणा DMA_GCSW_offC1INT	13	/* DMA channel 1 generate पूर्णांकerrupt */
/* bit 14:30 reserved */
#घोषणा DMA_GCSW_offEN		31	/* Enable DMA engine */

#घोषणा DMA_GCSW_mskC0STAT	( 0x7  << DMA_GCSW_offC0STAT )
#घोषणा DMA_GCSW_mskC1STAT	( 0x7  << DMA_GCSW_offC1STAT )
#घोषणा DMA_GCSW_mskC0INT	( 0x1  << DMA_GCSW_offC0INT )
#घोषणा DMA_GCSW_mskC1INT	( 0x1  << DMA_GCSW_offC1INT )
#घोषणा DMA_GCSW_mskEN		( 0x1  << DMA_GCSW_offEN )

/******************************************************************************
 * dmar2: DMA_CHNSEL (DMA Channel Selection Register)
 *****************************************************************************/
#घोषणा DMA_CHNSEL_offCHAN	0	/* Selected channel number */
/* bit 2:31 reserved */

#घोषणा DMA_CHNSEL_mskCHAN	( 0x3  << DMA_CHNSEL_offCHAN )

/******************************************************************************
 * dmar3: DMA_ACT (DMA Action Register)
 *****************************************************************************/
#घोषणा DMA_ACT_offACMD		0	/* DMA Action Command */
/* bit 2:31 reserved */
#घोषणा DMA_ACT_mskACMD		( 0x3  << DMA_ACT_offACMD )

/******************************************************************************
 * dmar4: DMA_SETUP (DMA Setup Register)
 *****************************************************************************/
#घोषणा DMA_SETUP_offLM		0	/* Local Memory Selection */
#घोषणा DMA_SETUP_offTसूची	1	/* Transfer Direction */
#घोषणा DMA_SETUP_offTES	2	/* Transfer Element Size */
#घोषणा DMA_SETUP_offESTR	4	/* External memory transfer Stride */
#घोषणा DMA_SETUP_offCIE	16	/* Interrupt Enable on Completion */
#घोषणा DMA_SETUP_offSIE	17	/* Interrupt Enable on explicit Stop */
#घोषणा DMA_SETUP_offEIE	18	/* Interrupt Enable on Error */
#घोषणा DMA_SETUP_offUE		19	/* Enable the Un-aligned External Address */
#घोषणा DMA_SETUP_off2DE	20	/* Enable the 2-D External Transfer */
#घोषणा DMA_SETUP_offCOA	21	/* Transfer Coalescable */
/* bit 22:31 reserved */

#घोषणा DMA_SETUP_mskLM		( 0x1  << DMA_SETUP_offLM )
#घोषणा DMA_SETUP_mskTसूची	( 0x1  << DMA_SETUP_offTसूची )
#घोषणा DMA_SETUP_mskTES	( 0x3  << DMA_SETUP_offTES )
#घोषणा DMA_SETUP_mskESTR	( 0xFFF  << DMA_SETUP_offESTR )
#घोषणा DMA_SETUP_mskCIE	( 0x1  << DMA_SETUP_offCIE )
#घोषणा DMA_SETUP_mskSIE	( 0x1  << DMA_SETUP_offSIE )
#घोषणा DMA_SETUP_mskEIE	( 0x1  << DMA_SETUP_offEIE )
#घोषणा DMA_SETUP_mskUE		( 0x1  << DMA_SETUP_offUE )
#घोषणा DMA_SETUP_msk2DE	( 0x1  << DMA_SETUP_off2DE )
#घोषणा DMA_SETUP_mskCOA	( 0x1  << DMA_SETUP_offCOA )

/******************************************************************************
 * dmar5: DMA_ISADDR (DMA Internal Start Address Register)
 *****************************************************************************/
#घोषणा DMA_ISADDR_offISADDR	0	/* Internal Start Address */
/* bit 20:31 reserved */
#घोषणा DMA_ISADDR_mskISADDR	( 0xFFFFF  << DMA_ISADDR_offISADDR )

/******************************************************************************
 * dmar6: DMA_ESADDR (DMA External Start Address Register)
 *****************************************************************************/
/* This रेजिस्टर holds External Start Address */

/******************************************************************************
 * dmar7: DMA_TCNT (DMA Transfer Element Count Register)
 *****************************************************************************/
#घोषणा DMA_TCNT_offTCNT	0	/* DMA transfer element count */
/* bit 18:31 reserved */
#घोषणा DMA_TCNT_mskTCNT	( 0x3FFFF  << DMA_TCNT_offTCNT )

/******************************************************************************
 * dmar8: DMA_STATUS (DMA Status Register)
 *****************************************************************************/
#घोषणा DMA_STATUS_offSTAT	0	/* DMA channel state */
#घोषणा DMA_STATUS_offSTUNA	3	/* Un-aligned error on External Stride value */
#घोषणा DMA_STATUS_offDERR	4	/* DMA Transfer Disruption Error */
#घोषणा DMA_STATUS_offEUNA	5	/* Un-aligned error on the External address */
#घोषणा DMA_STATUS_offIUNA	6	/* Un-aligned error on the Internal address */
#घोषणा DMA_STATUS_offIOOR	7	/* Out-Of-Range error on the Internal address */
#घोषणा DMA_STATUS_offEBUS	8	/* Bus Error on an External DMA transfer */
#घोषणा DMA_STATUS_offESUP	9	/* DMA setup error */
/* bit 10:31 reserved */

#घोषणा DMA_STATUS_mskSTAT	( 0x7  << DMA_STATUS_offSTAT )
#घोषणा DMA_STATUS_mskSTUNA	( 0x1  << DMDMA_STATUS_offSTUNA )
#घोषणा DMA_STATUS_mskDERR	( 0x1  << DMDMA_STATUS_offDERR )
#घोषणा DMA_STATUS_mskEUNA	( 0x1  << DMDMA_STATUS_offEUNA )
#घोषणा DMA_STATUS_mskIUNA	( 0x1  << DMDMA_STATUS_offIUNA )
#घोषणा DMA_STATUS_mskIOOR	( 0x1  << DMDMA_STATUS_offIOOR )
#घोषणा DMA_STATUS_mskEBUS	( 0x1  << DMDMA_STATUS_offEBUS )
#घोषणा DMA_STATUS_mskESUP	( 0x1  << DMDMA_STATUS_offESUP )

/******************************************************************************
 * dmar9: DMA_2DSET (DMA 2D Setup Register)
 *****************************************************************************/
#घोषणा DMA_2DSET_offWECNT	0	/* The Width Element Count क्रम a 2-D region */
#घोषणा DMA_2DSET_offHTSTR	16	/* The Height Stride क्रम a 2-D region */

#घोषणा DMA_2DSET_mskHTSTR	( 0xFFFF  << DMA_2DSET_offHTSTR )
#घोषणा DMA_2DSET_mskWECNT	( 0xFFFF  << DMA_2DSET_offWECNT )

/******************************************************************************
 * dmar10: DMA_2DSCTL (DMA 2D Startup Control Register)
 *****************************************************************************/
#घोषणा DMA_2DSCTL_offSTWECNT	0	/* Startup Width Element Count क्रम a 2-D region */
/* bit 16:31 reserved */

#घोषणा DMA_2DSCTL_mskSTWECNT	( 0xFFFF  << DMA_2DSCTL_offSTWECNT )

/******************************************************************************
 * fpcsr: FPCSR (Floating-Poपूर्णांक Control Status Register)
 *****************************************************************************/
#घोषणा FPCSR_offRM		0
#घोषणा FPCSR_offIVO		2
#घोषणा FPCSR_offDBZ		3
#घोषणा FPCSR_offOVF		4
#घोषणा FPCSR_offUDF		5
#घोषणा FPCSR_offIEX		6
#घोषणा FPCSR_offIVOE		7
#घोषणा FPCSR_offDBZE		8
#घोषणा FPCSR_offOVFE		9
#घोषणा FPCSR_offUDFE		10
#घोषणा FPCSR_offIEXE		11
#घोषणा FPCSR_offDNZ		12
#घोषणा FPCSR_offIVOT		13
#घोषणा FPCSR_offDBZT		14
#घोषणा FPCSR_offOVFT		15
#घोषणा FPCSR_offUDFT		16
#घोषणा FPCSR_offIEXT		17
#घोषणा FPCSR_offDNIT		18
#घोषणा FPCSR_offRIT		19

#घोषणा FPCSR_mskRM             ( 0x3  << FPCSR_offRM )
#घोषणा FPCSR_mskIVO            ( 0x1  << FPCSR_offIVO )
#घोषणा FPCSR_mskDBZ            ( 0x1  << FPCSR_offDBZ )
#घोषणा FPCSR_mskOVF            ( 0x1  << FPCSR_offOVF )
#घोषणा FPCSR_mskUDF            ( 0x1  << FPCSR_offUDF )
#घोषणा FPCSR_mskIEX            ( 0x1  << FPCSR_offIEX )
#घोषणा FPCSR_mskIVOE           ( 0x1  << FPCSR_offIVOE )
#घोषणा FPCSR_mskDBZE           ( 0x1  << FPCSR_offDBZE )
#घोषणा FPCSR_mskOVFE           ( 0x1  << FPCSR_offOVFE )
#घोषणा FPCSR_mskUDFE           ( 0x1  << FPCSR_offUDFE )
#घोषणा FPCSR_mskIEXE           ( 0x1  << FPCSR_offIEXE )
#घोषणा FPCSR_mskDNZ            ( 0x1  << FPCSR_offDNZ )
#घोषणा FPCSR_mskIVOT           ( 0x1  << FPCSR_offIVOT )
#घोषणा FPCSR_mskDBZT           ( 0x1  << FPCSR_offDBZT )
#घोषणा FPCSR_mskOVFT           ( 0x1  << FPCSR_offOVFT )
#घोषणा FPCSR_mskUDFT           ( 0x1  << FPCSR_offUDFT )
#घोषणा FPCSR_mskIEXT           ( 0x1  << FPCSR_offIEXT )
#घोषणा FPCSR_mskDNIT           ( 0x1  << FPCSR_offDNIT )
#घोषणा FPCSR_mskRIT		( 0x1  << FPCSR_offRIT )
#घोषणा FPCSR_mskALL		(FPCSR_mskIVO | FPCSR_mskDBZ | FPCSR_mskOVF | FPCSR_mskUDF | FPCSR_mskIEX)
#घोषणा FPCSR_mskALLE_NO_UDF_IEXE (FPCSR_mskIVOE | FPCSR_mskDBZE | FPCSR_mskOVFE)
#घोषणा FPCSR_mskALLE		(FPCSR_mskIVOE | FPCSR_mskDBZE | FPCSR_mskOVFE | FPCSR_mskUDFE | FPCSR_mskIEXE)
#घोषणा FPCSR_mskALLT           (FPCSR_mskIVOT | FPCSR_mskDBZT | FPCSR_mskOVFT | FPCSR_mskUDFT | FPCSR_mskIEXT |FPCSR_mskDNIT | FPCSR_mskRIT)

/******************************************************************************
 * fpcfg: FPCFG (Floating-Poपूर्णांक Configuration Register)
 *****************************************************************************/
#घोषणा	FPCFG_offSP		0
#घोषणा FPCFG_offDP		1
#घोषणा FPCFG_offFREG		2
#घोषणा FPCFG_offFMA		4
#घोषणा FPCFG_offIMVER		22
#घोषणा FPCFG_offAVER		27

#घोषणा FPCFG_mskSP		( 0x1  << FPCFG_offSP )
#घोषणा FPCFG_mskDP		( 0x1  << FPCFG_offDP )
#घोषणा FPCFG_mskFREG		( 0x3  << FPCFG_offFREG )
#घोषणा FPCFG_mskFMA		( 0x1  << FPCFG_offFMA )
#घोषणा FPCFG_mskIMVER		( 0x1F  << FPCFG_offIMVER )
#घोषणा FPCFG_mskAVER		( 0x1F  << FPCFG_offAVER )

/* 8 Single precision or 4 द्विगुन precision रेजिस्टरs are available */
#घोषणा SP8_DP4_reg		0
/* 16 Single precision or 8 द्विगुन precision रेजिस्टरs are available */
#घोषणा SP16_DP8_reg		1
/* 32 Single precision or 16 द्विगुन precision रेजिस्टरs are available */
#घोषणा SP32_DP16_reg		2
/* 32 Single precision or 32 द्विगुन precision रेजिस्टरs are available */
#घोषणा SP32_DP32_reg		3

/******************************************************************************
 * fucpr: FUCOP_CTL (FPU and Coprocessor Enable Control Register)
 *****************************************************************************/
#घोषणा FUCOP_CTL_offCP0EN	0
#घोषणा FUCOP_CTL_offCP1EN	1
#घोषणा FUCOP_CTL_offCP2EN	2
#घोषणा FUCOP_CTL_offCP3EN	3
#घोषणा FUCOP_CTL_offAUEN	31

#घोषणा FUCOP_CTL_mskCP0EN	( 0x1  << FUCOP_CTL_offCP0EN )
#घोषणा FUCOP_CTL_mskCP1EN	( 0x1  << FUCOP_CTL_offCP1EN )
#घोषणा FUCOP_CTL_mskCP2EN      ( 0x1  << FUCOP_CTL_offCP2EN )
#घोषणा FUCOP_CTL_mskCP3EN      ( 0x1  << FUCOP_CTL_offCP3EN )
#घोषणा FUCOP_CTL_mskAUEN       ( 0x1  << FUCOP_CTL_offAUEN )

#पूर्ण_अगर /* __NDS32_BITFIELD_H__ */
