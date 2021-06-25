<शैली गुरु>
/*
 * Xtensa processor core configuration inक्रमmation.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1999-2007 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_CORE_CONFIGURATION_H
#घोषणा _XTENSA_CORE_CONFIGURATION_H


/****************************************************************************
	    Parameters Useful क्रम Any Code, USER or PRIVILEGED
 ****************************************************************************/

/*
 *  Note:  Macros of the क्रमm XCHAL_HAVE_*** have a value of 1 अगर the option is
 *  configured, and a value of 0 otherwise.  These macros are always defined.
 */


/*----------------------------------------------------------------------
				ISA
  ----------------------------------------------------------------------*/

#घोषणा XCHAL_HAVE_BE			0	/* big-endian byte ordering */
#घोषणा XCHAL_HAVE_WINDOWED		1	/* winकरोwed रेजिस्टरs option */
#घोषणा XCHAL_NUM_AREGS			32	/* num of physical addr regs */
#घोषणा XCHAL_NUM_AREGS_LOG2		5	/* log2(XCHAL_NUM_AREGS) */
#घोषणा XCHAL_MAX_INSTRUCTION_SIZE	3	/* max instr bytes (3..8) */
#घोषणा XCHAL_HAVE_DEBUG		1	/* debug option */
#घोषणा XCHAL_HAVE_DENSITY		1	/* 16-bit inकाष्ठाions */
#घोषणा XCHAL_HAVE_LOOPS		1	/* zero-overhead loops */
#घोषणा XCHAL_HAVE_NSA			1	/* NSA/NSAU inकाष्ठाions */
#घोषणा XCHAL_HAVE_MINMAX		1	/* MIN/MAX inकाष्ठाions */
#घोषणा XCHAL_HAVE_SEXT			1	/* SEXT inकाष्ठाion */
#घोषणा XCHAL_HAVE_CLAMPS		1	/* CLAMPS inकाष्ठाion */
#घोषणा XCHAL_HAVE_MUL16		1	/* MUL16S/MUL16U inकाष्ठाions */
#घोषणा XCHAL_HAVE_MUL32		1	/* MULL inकाष्ठाion */
#घोषणा XCHAL_HAVE_MUL32_HIGH		0	/* MULUH/MULSH inकाष्ठाions */
#घोषणा XCHAL_HAVE_DIV32		1	/* QUOS/QUOU/REMS/REMU inकाष्ठाions */
#घोषणा XCHAL_HAVE_L32R			1	/* L32R inकाष्ठाion */
#घोषणा XCHAL_HAVE_ABSOLUTE_LITERALS	1	/* non-PC-rel (extended) L32R */
#घोषणा XCHAL_HAVE_CONST16		0	/* CONST16 inकाष्ठाion */
#घोषणा XCHAL_HAVE_ADDX			1	/* ADDX#/SUBX# inकाष्ठाions */
#घोषणा XCHAL_HAVE_WIDE_BRANCHES	0	/* B*.W18 or B*.W15 instr's */
#घोषणा XCHAL_HAVE_PREDICTED_BRANCHES	0	/* B[EQ/EQZ/NE/NEZ]T instr's */
#घोषणा XCHAL_HAVE_CALL4AND12		1	/* (obsolete option) */
#घोषणा XCHAL_HAVE_ABS			1	/* ABS inकाष्ठाion */
/*#घोषणा XCHAL_HAVE_POPC		0*/	/* POPC inकाष्ठाion */
/*#घोषणा XCHAL_HAVE_CRC		0*/	/* CRC inकाष्ठाion */
#घोषणा XCHAL_HAVE_RELEASE_SYNC		1	/* L32AI/S32RI inकाष्ठाions */
#घोषणा XCHAL_HAVE_S32C1I		1	/* S32C1I inकाष्ठाion */
#घोषणा XCHAL_HAVE_SPECULATION		0	/* speculation */
#घोषणा XCHAL_HAVE_FULL_RESET		1	/* all regs/state reset */
#घोषणा XCHAL_NUM_CONTEXTS		1	/* */
#घोषणा XCHAL_NUM_MISC_REGS		2	/* num of scratch regs (0..4) */
#घोषणा XCHAL_HAVE_TAP_MASTER		0	/* JTAG TAP control instr's */
#घोषणा XCHAL_HAVE_PRID			1	/* processor ID रेजिस्टर */
#घोषणा XCHAL_HAVE_THREADPTR		1	/* THREADPTR रेजिस्टर */
#घोषणा XCHAL_HAVE_BOOLEANS		0	/* boolean रेजिस्टरs */
#घोषणा XCHAL_HAVE_CP			1	/* CPENABLE reg (coprocessor) */
#घोषणा XCHAL_CP_MAXCFG			8	/* max allowed cp id plus one */
#घोषणा XCHAL_HAVE_MAC16		1	/* MAC16 package */
#घोषणा XCHAL_HAVE_VECTORFPU2005	0	/* vector भग्नing-poपूर्णांक pkg */
#घोषणा XCHAL_HAVE_FP			0	/* भग्नing poपूर्णांक pkg */
#घोषणा XCHAL_HAVE_VECTRA1		0	/* Vectra I  pkg */
#घोषणा XCHAL_HAVE_VECTRALX		0	/* Vectra LX pkg */
#घोषणा XCHAL_HAVE_HIFI2		0	/* HiFi2 Audio Engine pkg */


/*----------------------------------------------------------------------
				MISC
  ----------------------------------------------------------------------*/

#घोषणा XCHAL_NUM_WRITEBUFFER_ENTRIES	8	/* size of ग_लिखो buffer */
#घोषणा XCHAL_INST_FETCH_WIDTH		4	/* instr-fetch width in bytes */
#घोषणा XCHAL_DATA_WIDTH		4	/* data width in bytes */
/*  In T1050, applies to selected core load and store inकाष्ठाions (see ISA): */
#घोषणा XCHAL_UNALIGNED_LOAD_EXCEPTION	1	/* unaligned loads cause exc. */
#घोषणा XCHAL_UNALIGNED_STORE_EXCEPTION	1	/* unaligned stores cause exc.*/

#घोषणा XCHAL_SW_VERSION		701001	/* sw version of this header */

#घोषणा XCHAL_CORE_ID			"dc232b"	/* alphanum core name
						   (CoreID) set in the Xtensa
						   Processor Generator */

#घोषणा XCHAL_CORE_DESCRIPTION		"Diamond 232L Standard Core Rev.B (LE)"
#घोषणा XCHAL_BUILD_UNIQUE_ID		0x0000BEEF	/* 22-bit sw build ID */

/*
 *  These definitions describe the hardware targeted by this software.
 */
#घोषणा XCHAL_HW_CONFIGID0		0xC56307FE	/* ConfigID hi 32 bits*/
#घोषणा XCHAL_HW_CONFIGID1		0x0D40BEEF	/* ConfigID lo 32 bits*/
#घोषणा XCHAL_HW_VERSION_NAME		"LX2.1.1"	/* full version name */
#घोषणा XCHAL_HW_VERSION_MAJOR		2210	/* major ver# of targeted hw */
#घोषणा XCHAL_HW_VERSION_MINOR		1	/* minor ver# of targeted hw */
#घोषणा XCHAL_HW_VERSION		221001	/* major*100+minor */
#घोषणा XCHAL_HW_REL_LX2		1
#घोषणा XCHAL_HW_REL_LX2_1		1
#घोषणा XCHAL_HW_REL_LX2_1_1		1
#घोषणा XCHAL_HW_CONFIGID_RELIABLE	1
/*  If software tarमाला_लो a *range* of hardware versions, these are the bounds: */
#घोषणा XCHAL_HW_MIN_VERSION_MAJOR	2210	/* major v of earliest tgt hw */
#घोषणा XCHAL_HW_MIN_VERSION_MINOR	1	/* minor v of earliest tgt hw */
#घोषणा XCHAL_HW_MIN_VERSION		221001	/* earliest targeted hw */
#घोषणा XCHAL_HW_MAX_VERSION_MAJOR	2210	/* major v of latest tgt hw */
#घोषणा XCHAL_HW_MAX_VERSION_MINOR	1	/* minor v of latest tgt hw */
#घोषणा XCHAL_HW_MAX_VERSION		221001	/* latest targeted hw */


/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/

#घोषणा XCHAL_ICACHE_LINESIZE		32	/* I-cache line size in bytes */
#घोषणा XCHAL_DCACHE_LINESIZE		32	/* D-cache line size in bytes */
#घोषणा XCHAL_ICACHE_LINEWIDTH		5	/* log2(I line size in bytes) */
#घोषणा XCHAL_DCACHE_LINEWIDTH		5	/* log2(D line size in bytes) */

#घोषणा XCHAL_ICACHE_SIZE		16384	/* I-cache size in bytes or 0 */
#घोषणा XCHAL_DCACHE_SIZE		16384	/* D-cache size in bytes or 0 */

#घोषणा XCHAL_DCACHE_IS_WRITEBACK	1	/* ग_लिखोback feature */




/****************************************************************************
    Parameters Useful क्रम PRIVILEGED (Supervisory or Non-Virtualized) Code
 ****************************************************************************/


#अगर_अघोषित XTENSA_HAL_NON_PRIVILEGED_ONLY

/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/

#घोषणा XCHAL_HAVE_PIF			1	/* any outbound PIF present */

/*  If present, cache size in bytes == (ways * 2^(linewidth + setwidth)).  */

/*  Number of cache sets in log2(lines per way):  */
#घोषणा XCHAL_ICACHE_SETWIDTH		7
#घोषणा XCHAL_DCACHE_SETWIDTH		7

/*  Cache set associativity (number of ways):  */
#घोषणा XCHAL_ICACHE_WAYS		4
#घोषणा XCHAL_DCACHE_WAYS		4

/*  Cache features:  */
#घोषणा XCHAL_ICACHE_LINE_LOCKABLE	1
#घोषणा XCHAL_DCACHE_LINE_LOCKABLE	1
#घोषणा XCHAL_ICACHE_ECC_PARITY		0
#घोषणा XCHAL_DCACHE_ECC_PARITY		0

/*  Number of encoded cache attr bits (see <xtensa/hal.h> क्रम decoded bits):  */
#घोषणा XCHAL_CA_BITS			4


/*----------------------------------------------------------------------
			INTERNAL I/D RAM/ROMs and XLMI
  ----------------------------------------------------------------------*/

#घोषणा XCHAL_NUM_INSTROM		0	/* number of core instr. ROMs */
#घोषणा XCHAL_NUM_INSTRAM		0	/* number of core instr. RAMs */
#घोषणा XCHAL_NUM_DATAROM		0	/* number of core data ROMs */
#घोषणा XCHAL_NUM_DATARAM		0	/* number of core data RAMs */
#घोषणा XCHAL_NUM_URAM			0	/* number of core unअगरied RAMs*/
#घोषणा XCHAL_NUM_XLMI			0	/* number of core XLMI ports */


/*----------------------------------------------------------------------
			INTERRUPTS and TIMERS
  ----------------------------------------------------------------------*/

#घोषणा XCHAL_HAVE_INTERRUPTS		1	/* पूर्णांकerrupt option */
#घोषणा XCHAL_HAVE_HIGHPRI_INTERRUPTS	1	/* med/high-pri. पूर्णांकerrupts */
#घोषणा XCHAL_HAVE_NMI			1	/* non-maskable पूर्णांकerrupt */
#घोषणा XCHAL_HAVE_CCOUNT		1	/* CCOUNT reg. (समयr option) */
#घोषणा XCHAL_NUM_TIMERS		3	/* number of CCOMPAREn regs */
#घोषणा XCHAL_NUM_INTERRUPTS		22	/* number of पूर्णांकerrupts */
#घोषणा XCHAL_NUM_INTERRUPTS_LOG2	5	/* उच्चमान(log2(NUM_INTERRUPTS)) */
#घोषणा XCHAL_NUM_EXTINTERRUPTS		17	/* num of बाह्यal पूर्णांकerrupts */
#घोषणा XCHAL_NUM_INTLEVELS		6	/* number of पूर्णांकerrupt levels
						   (not including level zero) */
#घोषणा XCHAL_EXCM_LEVEL		3	/* level masked by PS.EXCM */
	/* (always 1 in XEA1; levels 2 .. EXCM_LEVEL are "medium priority") */

/*  Masks of पूर्णांकerrupts at each पूर्णांकerrupt level:  */
#घोषणा XCHAL_INTLEVEL1_MASK		0x001F80FF
#घोषणा XCHAL_INTLEVEL2_MASK		0x00000100
#घोषणा XCHAL_INTLEVEL3_MASK		0x00200E00
#घोषणा XCHAL_INTLEVEL4_MASK		0x00001000
#घोषणा XCHAL_INTLEVEL5_MASK		0x00002000
#घोषणा XCHAL_INTLEVEL6_MASK		0x00000000
#घोषणा XCHAL_INTLEVEL7_MASK		0x00004000

/*  Masks of पूर्णांकerrupts at each range 1..n of पूर्णांकerrupt levels:  */
#घोषणा XCHAL_INTLEVEL1_ANDBELOW_MASK	0x001F80FF
#घोषणा XCHAL_INTLEVEL2_ANDBELOW_MASK	0x001F81FF
#घोषणा XCHAL_INTLEVEL3_ANDBELOW_MASK	0x003F8FFF
#घोषणा XCHAL_INTLEVEL4_ANDBELOW_MASK	0x003F9FFF
#घोषणा XCHAL_INTLEVEL5_ANDBELOW_MASK	0x003FBFFF
#घोषणा XCHAL_INTLEVEL6_ANDBELOW_MASK	0x003FBFFF
#घोषणा XCHAL_INTLEVEL7_ANDBELOW_MASK	0x003FFFFF

/*  Level of each पूर्णांकerrupt:  */
#घोषणा XCHAL_INT0_LEVEL		1
#घोषणा XCHAL_INT1_LEVEL		1
#घोषणा XCHAL_INT2_LEVEL		1
#घोषणा XCHAL_INT3_LEVEL		1
#घोषणा XCHAL_INT4_LEVEL		1
#घोषणा XCHAL_INT5_LEVEL		1
#घोषणा XCHAL_INT6_LEVEL		1
#घोषणा XCHAL_INT7_LEVEL		1
#घोषणा XCHAL_INT8_LEVEL		2
#घोषणा XCHAL_INT9_LEVEL		3
#घोषणा XCHAL_INT10_LEVEL		3
#घोषणा XCHAL_INT11_LEVEL		3
#घोषणा XCHAL_INT12_LEVEL		4
#घोषणा XCHAL_INT13_LEVEL		5
#घोषणा XCHAL_INT14_LEVEL		7
#घोषणा XCHAL_INT15_LEVEL		1
#घोषणा XCHAL_INT16_LEVEL		1
#घोषणा XCHAL_INT17_LEVEL		1
#घोषणा XCHAL_INT18_LEVEL		1
#घोषणा XCHAL_INT19_LEVEL		1
#घोषणा XCHAL_INT20_LEVEL		1
#घोषणा XCHAL_INT21_LEVEL		3
#घोषणा XCHAL_DEBUGLEVEL		6	/* debug पूर्णांकerrupt level */
#घोषणा XCHAL_HAVE_DEBUG_EXTERN_INT	1	/* OCD बाह्यal db पूर्णांकerrupt */
#घोषणा XCHAL_NMILEVEL			7	/* NMI "level" (क्रम use with
						   EXCSAVE/EPS/EPC_n, RFI n) */

/*  Type of each पूर्णांकerrupt:  */
#घोषणा XCHAL_INT0_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#घोषणा XCHAL_INT1_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#घोषणा XCHAL_INT2_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#घोषणा XCHAL_INT3_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#घोषणा XCHAL_INT4_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#घोषणा XCHAL_INT5_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#घोषणा XCHAL_INT6_TYPE 	XTHAL_INTTYPE_TIMER
#घोषणा XCHAL_INT7_TYPE 	XTHAL_INTTYPE_SOFTWARE
#घोषणा XCHAL_INT8_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#घोषणा XCHAL_INT9_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#घोषणा XCHAL_INT10_TYPE 	XTHAL_INTTYPE_TIMER
#घोषणा XCHAL_INT11_TYPE 	XTHAL_INTTYPE_SOFTWARE
#घोषणा XCHAL_INT12_TYPE 	XTHAL_INTTYPE_EXTERN_LEVEL
#घोषणा XCHAL_INT13_TYPE 	XTHAL_INTTYPE_TIMER
#घोषणा XCHAL_INT14_TYPE 	XTHAL_INTTYPE_NMI
#घोषणा XCHAL_INT15_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#घोषणा XCHAL_INT16_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#घोषणा XCHAL_INT17_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#घोषणा XCHAL_INT18_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#घोषणा XCHAL_INT19_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#घोषणा XCHAL_INT20_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE
#घोषणा XCHAL_INT21_TYPE 	XTHAL_INTTYPE_EXTERN_EDGE

/*  Masks of पूर्णांकerrupts क्रम each type of पूर्णांकerrupt:  */
#घोषणा XCHAL_INTTYPE_MASK_UNCONFIGURED	0xFFC00000
#घोषणा XCHAL_INTTYPE_MASK_SOFTWARE	0x00000880
#घोषणा XCHAL_INTTYPE_MASK_EXTERN_EDGE	0x003F8000
#घोषणा XCHAL_INTTYPE_MASK_EXTERN_LEVEL	0x0000133F
#घोषणा XCHAL_INTTYPE_MASK_TIMER	0x00002440
#घोषणा XCHAL_INTTYPE_MASK_NMI		0x00004000
#घोषणा XCHAL_INTTYPE_MASK_WRITE_ERROR	0x00000000

/*  Interrupt numbers asचिन्हित to specअगरic पूर्णांकerrupt sources:  */
#घोषणा XCHAL_TIMER0_INTERRUPT		6	/* CCOMPARE0 */
#घोषणा XCHAL_TIMER1_INTERRUPT		10	/* CCOMPARE1 */
#घोषणा XCHAL_TIMER2_INTERRUPT		13	/* CCOMPARE2 */
#घोषणा XCHAL_TIMER3_INTERRUPT		XTHAL_TIMER_UNCONFIGURED
#घोषणा XCHAL_NMI_INTERRUPT		14	/* non-maskable पूर्णांकerrupt */

/*  Interrupt numbers क्रम levels at which only one पूर्णांकerrupt is configured:  */
#घोषणा XCHAL_INTLEVEL2_NUM		8
#घोषणा XCHAL_INTLEVEL4_NUM		12
#घोषणा XCHAL_INTLEVEL5_NUM		13
#घोषणा XCHAL_INTLEVEL7_NUM		14
/*  (There are many पूर्णांकerrupts each at level(s) 1, 3.)  */


/*
 *  External पूर्णांकerrupt vectors/levels.
 *  These macros describe how Xtensa processor पूर्णांकerrupt numbers
 *  (as numbered पूर्णांकernally, eg. in INTERRUPT and INTENABLE रेजिस्टरs)
 *  map to बाह्यal BInterrupt<n> pins, क्रम those पूर्णांकerrupts
 *  configured as बाह्यal (level-triggered, edge-triggered, or NMI).
 *  See the Xtensa processor databook क्रम more details.
 */

/*  Core पूर्णांकerrupt numbers mapped to each EXTERNAL पूर्णांकerrupt number:  */
#घोषणा XCHAL_EXTINT0_NUM		0	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT1_NUM		1	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT2_NUM		2	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT3_NUM		3	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT4_NUM		4	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT5_NUM		5	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT6_NUM		8	/* (पूर्णांकlevel 2) */
#घोषणा XCHAL_EXTINT7_NUM		9	/* (पूर्णांकlevel 3) */
#घोषणा XCHAL_EXTINT8_NUM		12	/* (पूर्णांकlevel 4) */
#घोषणा XCHAL_EXTINT9_NUM		14	/* (पूर्णांकlevel 7) */
#घोषणा XCHAL_EXTINT10_NUM		15	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT11_NUM		16	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT12_NUM		17	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT13_NUM		18	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT14_NUM		19	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT15_NUM		20	/* (पूर्णांकlevel 1) */
#घोषणा XCHAL_EXTINT16_NUM		21	/* (पूर्णांकlevel 3) */


/*----------------------------------------------------------------------
			EXCEPTIONS and VECTORS
  ----------------------------------------------------------------------*/

#घोषणा XCHAL_XEA_VERSION		2	/* Xtensa Exception Architecture
						   number: 1 == XEA1 (old)
							   2 == XEA2 (new)
							   0 == XEAX (बाह्य) */
#घोषणा XCHAL_HAVE_XEA1			0	/* Exception Architecture 1 */
#घोषणा XCHAL_HAVE_XEA2			1	/* Exception Architecture 2 */
#घोषणा XCHAL_HAVE_XEAX			0	/* External Exception Arch. */
#घोषणा XCHAL_HAVE_EXCEPTIONS		1	/* exception option */
#घोषणा XCHAL_HAVE_MEM_ECC_PARITY	0	/* local memory ECC/parity */
#घोषणा XCHAL_HAVE_VECTOR_SELECT	1	/* relocatable vectors */
#घोषणा XCHAL_HAVE_VECBASE		1	/* relocatable vectors */
#घोषणा XCHAL_VECBASE_RESET_VADDR	0xD0000000  /* VECBASE reset value */
#घोषणा XCHAL_VECBASE_RESET_PADDR	0x00000000
#घोषणा XCHAL_RESET_VECBASE_OVERLAP	0

#घोषणा XCHAL_RESET_VECTOR0_VADDR	0xFE000000
#घोषणा XCHAL_RESET_VECTOR0_PADDR	0xFE000000
#घोषणा XCHAL_RESET_VECTOR1_VADDR	0xD8000500
#घोषणा XCHAL_RESET_VECTOR1_PADDR	0x00000500
#घोषणा XCHAL_RESET_VECTOR_VADDR	0xFE000000
#घोषणा XCHAL_RESET_VECTOR_PADDR	0xFE000000
#घोषणा XCHAL_USER_VECOFS		0x00000340
#घोषणा XCHAL_USER_VECTOR_VADDR		0xD0000340
#घोषणा XCHAL_USER_VECTOR_PADDR		0x00000340
#घोषणा XCHAL_KERNEL_VECOFS		0x00000300
#घोषणा XCHAL_KERNEL_VECTOR_VADDR	0xD0000300
#घोषणा XCHAL_KERNEL_VECTOR_PADDR	0x00000300
#घोषणा XCHAL_DOUBLEEXC_VECOFS		0x000003C0
#घोषणा XCHAL_DOUBLEEXC_VECTOR_VADDR	0xD00003C0
#घोषणा XCHAL_DOUBLEEXC_VECTOR_PADDR	0x000003C0
#घोषणा XCHAL_WINDOW_OF4_VECOFS		0x00000000
#घोषणा XCHAL_WINDOW_UF4_VECOFS		0x00000040
#घोषणा XCHAL_WINDOW_OF8_VECOFS		0x00000080
#घोषणा XCHAL_WINDOW_UF8_VECOFS		0x000000C0
#घोषणा XCHAL_WINDOW_OF12_VECOFS	0x00000100
#घोषणा XCHAL_WINDOW_UF12_VECOFS	0x00000140
#घोषणा XCHAL_WINDOW_VECTORS_VADDR	0xD0000000
#घोषणा XCHAL_WINDOW_VECTORS_PADDR	0x00000000
#घोषणा XCHAL_INTLEVEL2_VECOFS		0x00000180
#घोषणा XCHAL_INTLEVEL2_VECTOR_VADDR	0xD0000180
#घोषणा XCHAL_INTLEVEL2_VECTOR_PADDR	0x00000180
#घोषणा XCHAL_INTLEVEL3_VECOFS		0x000001C0
#घोषणा XCHAL_INTLEVEL3_VECTOR_VADDR	0xD00001C0
#घोषणा XCHAL_INTLEVEL3_VECTOR_PADDR	0x000001C0
#घोषणा XCHAL_INTLEVEL4_VECOFS		0x00000200
#घोषणा XCHAL_INTLEVEL4_VECTOR_VADDR	0xD0000200
#घोषणा XCHAL_INTLEVEL4_VECTOR_PADDR	0x00000200
#घोषणा XCHAL_INTLEVEL5_VECOFS		0x00000240
#घोषणा XCHAL_INTLEVEL5_VECTOR_VADDR	0xD0000240
#घोषणा XCHAL_INTLEVEL5_VECTOR_PADDR	0x00000240
#घोषणा XCHAL_INTLEVEL6_VECOFS		0x00000280
#घोषणा XCHAL_INTLEVEL6_VECTOR_VADDR	0xD0000280
#घोषणा XCHAL_INTLEVEL6_VECTOR_PADDR	0x00000280
#घोषणा XCHAL_DEBUG_VECOFS		XCHAL_INTLEVEL6_VECOFS
#घोषणा XCHAL_DEBUG_VECTOR_VADDR	XCHAL_INTLEVEL6_VECTOR_VADDR
#घोषणा XCHAL_DEBUG_VECTOR_PADDR	XCHAL_INTLEVEL6_VECTOR_PADDR
#घोषणा XCHAL_NMI_VECOFS		0x000002C0
#घोषणा XCHAL_NMI_VECTOR_VADDR		0xD00002C0
#घोषणा XCHAL_NMI_VECTOR_PADDR		0x000002C0
#घोषणा XCHAL_INTLEVEL7_VECOFS		XCHAL_NMI_VECOFS
#घोषणा XCHAL_INTLEVEL7_VECTOR_VADDR	XCHAL_NMI_VECTOR_VADDR
#घोषणा XCHAL_INTLEVEL7_VECTOR_PADDR	XCHAL_NMI_VECTOR_PADDR


/*----------------------------------------------------------------------
				DEBUG
  ----------------------------------------------------------------------*/

#घोषणा XCHAL_HAVE_OCD			1	/* OnChipDebug option */
#घोषणा XCHAL_NUM_IBREAK		2	/* number of IBREAKn regs */
#घोषणा XCHAL_NUM_DBREAK		2	/* number of DBREAKn regs */
#घोषणा XCHAL_HAVE_OCD_सूची_ARRAY	1	/* faster OCD option */


/*----------------------------------------------------------------------
				MMU
  ----------------------------------------------------------------------*/

/*  See core-maपंचांगap.h header file क्रम more details.  */

#घोषणा XCHAL_HAVE_TLBS			1	/* inverse of HAVE_CACHEATTR */
#घोषणा XCHAL_HAVE_SPANNING_WAY		0	/* one way maps I+D 4GB vaddr */
#घोषणा XCHAL_HAVE_IDENTITY_MAP		0	/* vaddr == paddr always */
#घोषणा XCHAL_HAVE_CACHEATTR		0	/* CACHEATTR रेजिस्टर present */
#घोषणा XCHAL_HAVE_MIMIC_CACHEATTR	0	/* region protection */
#घोषणा XCHAL_HAVE_XLT_CACHEATTR	0	/* region prot. w/translation */
#घोषणा XCHAL_HAVE_PTP_MMU		1	/* full MMU (with page table
						   [स्वतःrefill] and protection)
						   usable क्रम an MMU-based OS */
/*  If none of the above last 4 are set, it's a custom TLB configuration.  */
#घोषणा XCHAL_ITLB_ARF_ENTRIES_LOG2	2	/* log2(स्वतःrefill way size) */
#घोषणा XCHAL_DTLB_ARF_ENTRIES_LOG2	2	/* log2(स्वतःrefill way size) */

#घोषणा XCHAL_MMU_ASID_BITS		8	/* number of bits in ASIDs */
#घोषणा XCHAL_MMU_RINGS			4	/* number of rings (1..4) */
#घोषणा XCHAL_MMU_RING_BITS		2	/* num of bits in RING field */

#पूर्ण_अगर /* !XTENSA_HAL_NON_PRIVILEGED_ONLY */


#पूर्ण_अगर /* _XTENSA_CORE_CONFIGURATION_H */

