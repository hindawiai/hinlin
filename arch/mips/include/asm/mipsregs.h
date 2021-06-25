<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 1995, 1996, 1997, 2000, 2001 by Ralf Baechle
 * Copyright (C) 2000 Silicon Graphics, Inc.
 * Modअगरied क्रम further R[236]000 support by Paul M. Antoine, 1996.
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000, 07 MIPS Technologies, Inc.
 * Copyright (C) 2003, 2004  Maciej W. Rozycki
 */
#अगर_अघोषित _ASM_MIPSREGS_H
#घोषणा _ASM_MIPSREGS_H

#समावेश <linux/linkage.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/hazards.h>
#समावेश <यंत्र/isa-rev.h>
#समावेश <यंत्र/war.h>

/*
 * The following macros are especially useful क्रम __यंत्र__
 * अंतरभूत assembler.
 */
#अगर_अघोषित __STR
#घोषणा __STR(x) #x
#पूर्ण_अगर
#अगर_अघोषित STR
#घोषणा STR(x) __STR(x)
#पूर्ण_अगर

/*
 *  Configure language
 */
#अगर_घोषित __ASSEMBLY__
#घोषणा _ULCAST_
#घोषणा _U64CAST_
#अन्यथा
#घोषणा _ULCAST_ (अचिन्हित दीर्घ)
#घोषणा _U64CAST_ (u64)
#पूर्ण_अगर

/*
 * Coprocessor 0 रेजिस्टर names
 */
#घोषणा CP0_INDEX $0
#घोषणा CP0_RANDOM $1
#घोषणा CP0_ENTRYLO0 $2
#घोषणा CP0_ENTRYLO1 $3
#घोषणा CP0_CONF $3
#घोषणा CP0_GLOBALNUMBER $3, 1
#घोषणा CP0_CONTEXT $4
#घोषणा CP0_PAGEMASK $5
#घोषणा CP0_PAGEGRAIN $5, 1
#घोषणा CP0_SEGCTL0 $5, 2
#घोषणा CP0_SEGCTL1 $5, 3
#घोषणा CP0_SEGCTL2 $5, 4
#घोषणा CP0_WIRED $6
#घोषणा CP0_INFO $7
#घोषणा CP0_HWRENA $7
#घोषणा CP0_BADVADDR $8
#घोषणा CP0_BADINSTR $8, 1
#घोषणा CP0_COUNT $9
#घोषणा CP0_ENTRYHI $10
#घोषणा CP0_GUESTCTL1 $10, 4
#घोषणा CP0_GUESTCTL2 $10, 5
#घोषणा CP0_GUESTCTL3 $10, 6
#घोषणा CP0_COMPARE $11
#घोषणा CP0_GUESTCTL0EXT $11, 4
#घोषणा CP0_STATUS $12
#घोषणा CP0_GUESTCTL0 $12, 6
#घोषणा CP0_GTOFFSET $12, 7
#घोषणा CP0_CAUSE $13
#घोषणा CP0_EPC $14
#घोषणा CP0_PRID $15
#घोषणा CP0_EBASE $15, 1
#घोषणा CP0_CMGCRBASE $15, 3
#घोषणा CP0_CONFIG $16
#घोषणा CP0_CONFIG3 $16, 3
#घोषणा CP0_CONFIG5 $16, 5
#घोषणा CP0_CONFIG6 $16, 6
#घोषणा CP0_LLADDR $17
#घोषणा CP0_WATCHLO $18
#घोषणा CP0_WATCHHI $19
#घोषणा CP0_XCONTEXT $20
#घोषणा CP0_FRAMEMASK $21
#घोषणा CP0_DIAGNOSTIC $22
#घोषणा CP0_DIAGNOSTIC1 $22, 1
#घोषणा CP0_DEBUG $23
#घोषणा CP0_DEPC $24
#घोषणा CP0_PERFORMANCE $25
#घोषणा CP0_ECC $26
#घोषणा CP0_CACHEERR $27
#घोषणा CP0_TAGLO $28
#घोषणा CP0_TAGHI $29
#घोषणा CP0_ERROREPC $30
#घोषणा CP0_DESAVE $31

/*
 * R4640/R4650 cp0 रेजिस्टर names.  These रेजिस्टरs are listed
 * here only क्रम completeness; without MMU these CPUs are not useable
 * by Linux.  A future ELKS port might take make Linux run on them
 * though ...
 */
#घोषणा CP0_IBASE $0
#घोषणा CP0_IBOUND $1
#घोषणा CP0_DBASE $2
#घोषणा CP0_DBOUND $3
#घोषणा CP0_CALG $17
#घोषणा CP0_IWATCH $18
#घोषणा CP0_DWATCH $19

/*
 * Coprocessor 0 Set 1 रेजिस्टर names
 */
#घोषणा CP0_S1_DERRADDR0  $26
#घोषणा CP0_S1_DERRADDR1  $27
#घोषणा CP0_S1_INTCONTROL $20

/*
 * Coprocessor 0 Set 2 रेजिस्टर names
 */
#घोषणा CP0_S2_SRSCTL	  $12	/* MIPSR2 */

/*
 * Coprocessor 0 Set 3 रेजिस्टर names
 */
#घोषणा CP0_S3_SRSMAP	  $12	/* MIPSR2 */

/*
 *  TX39 Series
 */
#घोषणा CP0_TX39_CACHE	$7


/* Generic EntryLo bit definitions */
#घोषणा ENTRYLO_G		(_ULCAST_(1) << 0)
#घोषणा ENTRYLO_V		(_ULCAST_(1) << 1)
#घोषणा ENTRYLO_D		(_ULCAST_(1) << 2)
#घोषणा ENTRYLO_C_SHIFT		3
#घोषणा ENTRYLO_C		(_ULCAST_(7) << ENTRYLO_C_SHIFT)

/* R3000 EntryLo bit definitions */
#घोषणा R3K_ENTRYLO_G		(_ULCAST_(1) << 8)
#घोषणा R3K_ENTRYLO_V		(_ULCAST_(1) << 9)
#घोषणा R3K_ENTRYLO_D		(_ULCAST_(1) << 10)
#घोषणा R3K_ENTRYLO_N		(_ULCAST_(1) << 11)

/* MIPS32/64 EntryLo bit definitions */
#घोषणा MIPS_ENTRYLO_PFN_SHIFT	6
#घोषणा MIPS_ENTRYLO_XI		(_ULCAST_(1) << (BITS_PER_LONG - 2))
#घोषणा MIPS_ENTRYLO_RI		(_ULCAST_(1) << (BITS_PER_LONG - 1))

/*
 * MIPSr6+ GlobalNumber रेजिस्टर definitions
 */
#घोषणा MIPS_GLOBALNUMBER_VP_SHF	0
#घोषणा MIPS_GLOBALNUMBER_VP		(_ULCAST_(0xff) << MIPS_GLOBALNUMBER_VP_SHF)
#घोषणा MIPS_GLOBALNUMBER_CORE_SHF	8
#घोषणा MIPS_GLOBALNUMBER_CORE		(_ULCAST_(0xff) << MIPS_GLOBALNUMBER_CORE_SHF)
#घोषणा MIPS_GLOBALNUMBER_CLUSTER_SHF	16
#घोषणा MIPS_GLOBALNUMBER_CLUSTER	(_ULCAST_(0xf) << MIPS_GLOBALNUMBER_CLUSTER_SHF)

/*
 * Values क्रम PageMask रेजिस्टर
 */
#अगर_घोषित CONFIG_CPU_VR41XX

/* Why करोesn't stupidity hurt ... */

#घोषणा PM_1K		0x00000000
#घोषणा PM_4K		0x00001800
#घोषणा PM_16K		0x00007800
#घोषणा PM_64K		0x0001f800
#घोषणा PM_256K		0x0007f800

#अन्यथा

#घोषणा PM_4K		0x00000000
#घोषणा PM_8K		0x00002000
#घोषणा PM_16K		0x00006000
#घोषणा PM_32K		0x0000e000
#घोषणा PM_64K		0x0001e000
#घोषणा PM_128K		0x0003e000
#घोषणा PM_256K		0x0007e000
#घोषणा PM_512K		0x000fe000
#घोषणा PM_1M		0x001fe000
#घोषणा PM_2M		0x003fe000
#घोषणा PM_4M		0x007fe000
#घोषणा PM_8M		0x00ffe000
#घोषणा PM_16M		0x01ffe000
#घोषणा PM_32M		0x03ffe000
#घोषणा PM_64M		0x07ffe000
#घोषणा PM_256M		0x1fffe000
#घोषणा PM_1G		0x7fffe000

#पूर्ण_अगर

/*
 * Default page size क्रम a given kernel configuration
 */
#अगर_घोषित CONFIG_PAGE_SIZE_4KB
#घोषणा PM_DEFAULT_MASK PM_4K
#या_अगर defined(CONFIG_PAGE_SIZE_8KB)
#घोषणा PM_DEFAULT_MASK PM_8K
#या_अगर defined(CONFIG_PAGE_SIZE_16KB)
#घोषणा PM_DEFAULT_MASK PM_16K
#या_अगर defined(CONFIG_PAGE_SIZE_32KB)
#घोषणा PM_DEFAULT_MASK PM_32K
#या_अगर defined(CONFIG_PAGE_SIZE_64KB)
#घोषणा PM_DEFAULT_MASK PM_64K
#अन्यथा
#त्रुटि Bad page size configuration!
#पूर्ण_अगर

/*
 * Default huge tlb size क्रम a given kernel configuration
 */
#अगर_घोषित CONFIG_PAGE_SIZE_4KB
#घोषणा PM_HUGE_MASK	PM_1M
#या_अगर defined(CONFIG_PAGE_SIZE_8KB)
#घोषणा PM_HUGE_MASK	PM_4M
#या_अगर defined(CONFIG_PAGE_SIZE_16KB)
#घोषणा PM_HUGE_MASK	PM_16M
#या_अगर defined(CONFIG_PAGE_SIZE_32KB)
#घोषणा PM_HUGE_MASK	PM_64M
#या_अगर defined(CONFIG_PAGE_SIZE_64KB)
#घोषणा PM_HUGE_MASK	PM_256M
#या_अगर defined(CONFIG_MIPS_HUGE_TLB_SUPPORT)
#त्रुटि Bad page size configuration क्रम hugetlbfs!
#पूर्ण_अगर

/*
 * Wired रेजिस्टर bits
 */
#घोषणा MIPSR6_WIRED_LIMIT_SHIFT 16
#घोषणा MIPSR6_WIRED_LIMIT	(_ULCAST_(0xffff) << MIPSR6_WIRED_LIMIT_SHIFT)
#घोषणा MIPSR6_WIRED_WIRED_SHIFT 0
#घोषणा MIPSR6_WIRED_WIRED	(_ULCAST_(0xffff) << MIPSR6_WIRED_WIRED_SHIFT)

/*
 * Values used क्रम computation of new tlb entries
 */
#घोषणा PL_4K		12
#घोषणा PL_16K		14
#घोषणा PL_64K		16
#घोषणा PL_256K		18
#घोषणा PL_1M		20
#घोषणा PL_4M		22
#घोषणा PL_16M		24
#घोषणा PL_64M		26
#घोषणा PL_256M		28

/*
 * PageGrain bits
 */
#घोषणा PG_RIE		(_ULCAST_(1) <<	 31)
#घोषणा PG_XIE		(_ULCAST_(1) <<	 30)
#घोषणा PG_ELPA		(_ULCAST_(1) <<	 29)
#घोषणा PG_ESP		(_ULCAST_(1) <<	 28)
#घोषणा PG_IEC		(_ULCAST_(1) <<  27)

/* MIPS32/64 EntryHI bit definitions */
#घोषणा MIPS_ENTRYHI_EHINV	(_ULCAST_(1) << 10)
#घोषणा MIPS_ENTRYHI_ASIDX	(_ULCAST_(0x3) << 8)
#घोषणा MIPS_ENTRYHI_ASID	(_ULCAST_(0xff) << 0)

/*
 * R4x00 पूर्णांकerrupt enable / cause bits
 */
#घोषणा IE_SW0		(_ULCAST_(1) <<	 8)
#घोषणा IE_SW1		(_ULCAST_(1) <<	 9)
#घोषणा IE_IRQ0		(_ULCAST_(1) << 10)
#घोषणा IE_IRQ1		(_ULCAST_(1) << 11)
#घोषणा IE_IRQ2		(_ULCAST_(1) << 12)
#घोषणा IE_IRQ3		(_ULCAST_(1) << 13)
#घोषणा IE_IRQ4		(_ULCAST_(1) << 14)
#घोषणा IE_IRQ5		(_ULCAST_(1) << 15)

/*
 * R4x00 पूर्णांकerrupt cause bits
 */
#घोषणा C_SW0		(_ULCAST_(1) <<	 8)
#घोषणा C_SW1		(_ULCAST_(1) <<	 9)
#घोषणा C_IRQ0		(_ULCAST_(1) << 10)
#घोषणा C_IRQ1		(_ULCAST_(1) << 11)
#घोषणा C_IRQ2		(_ULCAST_(1) << 12)
#घोषणा C_IRQ3		(_ULCAST_(1) << 13)
#घोषणा C_IRQ4		(_ULCAST_(1) << 14)
#घोषणा C_IRQ5		(_ULCAST_(1) << 15)

/*
 * Bitfields in the R4xx0 cp0 status रेजिस्टर
 */
#घोषणा ST0_IE			0x00000001
#घोषणा ST0_EXL			0x00000002
#घोषणा ST0_ERL			0x00000004
#घोषणा ST0_KSU			0x00000018
#  define KSU_USER		0x00000010
#  define KSU_SUPERVISOR	0x00000008
#  define KSU_KERNEL		0x00000000
#घोषणा ST0_UX			0x00000020
#घोषणा ST0_SX			0x00000040
#घोषणा ST0_KX			0x00000080
#घोषणा ST0_DE			0x00010000
#घोषणा ST0_CE			0x00020000

/*
 * Setting c0_status.co enables Hit_Writeback and Hit_Writeback_Invalidate
 * cacheops in userspace.  This bit exists only on RM7000 and RM9000
 * processors.
 */
#घोषणा ST0_CO			0x08000000

/*
 * Bitfields in the R[23]000 cp0 status रेजिस्टर.
 */
#घोषणा ST0_IEC			0x00000001
#घोषणा ST0_KUC			0x00000002
#घोषणा ST0_IEP			0x00000004
#घोषणा ST0_KUP			0x00000008
#घोषणा ST0_IEO			0x00000010
#घोषणा ST0_KUO			0x00000020
/* bits 6 & 7 are reserved on R[23]000 */
#घोषणा ST0_ISC			0x00010000
#घोषणा ST0_SWC			0x00020000
#घोषणा ST0_CM			0x00080000

/*
 * Bits specअगरic to the R4640/R4650
 */
#घोषणा ST0_UM			(_ULCAST_(1) <<	 4)
#घोषणा ST0_IL			(_ULCAST_(1) << 23)
#घोषणा ST0_DL			(_ULCAST_(1) << 24)

/*
 * Enable the MIPS MDMX and DSP ASEs
 */
#घोषणा ST0_MX			0x01000000

/*
 * Status रेजिस्टर bits available in all MIPS CPUs.
 */
#घोषणा ST0_IM			0x0000ff00
#घोषणा	 STATUSB_IP0		8
#घोषणा	 STATUSF_IP0		(_ULCAST_(1) <<	 8)
#घोषणा	 STATUSB_IP1		9
#घोषणा	 STATUSF_IP1		(_ULCAST_(1) <<	 9)
#घोषणा	 STATUSB_IP2		10
#घोषणा	 STATUSF_IP2		(_ULCAST_(1) << 10)
#घोषणा	 STATUSB_IP3		11
#घोषणा	 STATUSF_IP3		(_ULCAST_(1) << 11)
#घोषणा	 STATUSB_IP4		12
#घोषणा	 STATUSF_IP4		(_ULCAST_(1) << 12)
#घोषणा	 STATUSB_IP5		13
#घोषणा	 STATUSF_IP5		(_ULCAST_(1) << 13)
#घोषणा	 STATUSB_IP6		14
#घोषणा	 STATUSF_IP6		(_ULCAST_(1) << 14)
#घोषणा	 STATUSB_IP7		15
#घोषणा	 STATUSF_IP7		(_ULCAST_(1) << 15)
#घोषणा	 STATUSB_IP8		0
#घोषणा	 STATUSF_IP8		(_ULCAST_(1) <<	 0)
#घोषणा	 STATUSB_IP9		1
#घोषणा	 STATUSF_IP9		(_ULCAST_(1) <<	 1)
#घोषणा	 STATUSB_IP10		2
#घोषणा	 STATUSF_IP10		(_ULCAST_(1) <<	 2)
#घोषणा	 STATUSB_IP11		3
#घोषणा	 STATUSF_IP11		(_ULCAST_(1) <<	 3)
#घोषणा	 STATUSB_IP12		4
#घोषणा	 STATUSF_IP12		(_ULCAST_(1) <<	 4)
#घोषणा	 STATUSB_IP13		5
#घोषणा	 STATUSF_IP13		(_ULCAST_(1) <<	 5)
#घोषणा	 STATUSB_IP14		6
#घोषणा	 STATUSF_IP14		(_ULCAST_(1) <<	 6)
#घोषणा	 STATUSB_IP15		7
#घोषणा	 STATUSF_IP15		(_ULCAST_(1) <<	 7)
#घोषणा ST0_CH			0x00040000
#घोषणा ST0_NMI			0x00080000
#घोषणा ST0_SR			0x00100000
#घोषणा ST0_TS			0x00200000
#घोषणा ST0_BEV			0x00400000
#घोषणा ST0_RE			0x02000000
#घोषणा ST0_FR			0x04000000
#घोषणा ST0_CU			0xf0000000
#घोषणा ST0_CU0			0x10000000
#घोषणा ST0_CU1			0x20000000
#घोषणा ST0_CU2			0x40000000
#घोषणा ST0_CU3			0x80000000
#घोषणा ST0_XX			0x80000000	/* MIPS IV naming */

/* in-kernel enabled CUs */
#अगर_घोषित CONFIG_CPU_LOONGSON64
#घोषणा ST0_KERNEL_CUMASK      (ST0_CU0 | ST0_CU2)
#अन्यथा
#घोषणा ST0_KERNEL_CUMASK      ST0_CU0
#पूर्ण_अगर

/*
 * Bitfields and bit numbers in the coprocessor 0 IntCtl रेजिस्टर. (MIPSR2)
 */
#घोषणा INTCTLB_IPFDC		23
#घोषणा INTCTLF_IPFDC		(_ULCAST_(7) << INTCTLB_IPFDC)
#घोषणा INTCTLB_IPPCI		26
#घोषणा INTCTLF_IPPCI		(_ULCAST_(7) << INTCTLB_IPPCI)
#घोषणा INTCTLB_IPTI		29
#घोषणा INTCTLF_IPTI		(_ULCAST_(7) << INTCTLB_IPTI)

/*
 * Bitfields and bit numbers in the coprocessor 0 cause रेजिस्टर.
 *
 * Refer to your MIPS R4xx0 manual, chapter 5 क्रम explanation.
 */
#घोषणा CAUSEB_EXCCODE		2
#घोषणा CAUSEF_EXCCODE		(_ULCAST_(31)  <<  2)
#घोषणा CAUSEB_IP		8
#घोषणा CAUSEF_IP		(_ULCAST_(255) <<  8)
#घोषणा	 CAUSEB_IP0		8
#घोषणा	 CAUSEF_IP0		(_ULCAST_(1)   <<  8)
#घोषणा	 CAUSEB_IP1		9
#घोषणा	 CAUSEF_IP1		(_ULCAST_(1)   <<  9)
#घोषणा	 CAUSEB_IP2		10
#घोषणा	 CAUSEF_IP2		(_ULCAST_(1)   << 10)
#घोषणा	 CAUSEB_IP3		11
#घोषणा	 CAUSEF_IP3		(_ULCAST_(1)   << 11)
#घोषणा	 CAUSEB_IP4		12
#घोषणा	 CAUSEF_IP4		(_ULCAST_(1)   << 12)
#घोषणा	 CAUSEB_IP5		13
#घोषणा	 CAUSEF_IP5		(_ULCAST_(1)   << 13)
#घोषणा	 CAUSEB_IP6		14
#घोषणा	 CAUSEF_IP6		(_ULCAST_(1)   << 14)
#घोषणा	 CAUSEB_IP7		15
#घोषणा	 CAUSEF_IP7		(_ULCAST_(1)   << 15)
#घोषणा CAUSEB_FDCI		21
#घोषणा CAUSEF_FDCI		(_ULCAST_(1)   << 21)
#घोषणा CAUSEB_WP		22
#घोषणा CAUSEF_WP		(_ULCAST_(1)   << 22)
#घोषणा CAUSEB_IV		23
#घोषणा CAUSEF_IV		(_ULCAST_(1)   << 23)
#घोषणा CAUSEB_PCI		26
#घोषणा CAUSEF_PCI		(_ULCAST_(1)   << 26)
#घोषणा CAUSEB_DC		27
#घोषणा CAUSEF_DC		(_ULCAST_(1)   << 27)
#घोषणा CAUSEB_CE		28
#घोषणा CAUSEF_CE		(_ULCAST_(3)   << 28)
#घोषणा CAUSEB_TI		30
#घोषणा CAUSEF_TI		(_ULCAST_(1)   << 30)
#घोषणा CAUSEB_BD		31
#घोषणा CAUSEF_BD		(_ULCAST_(1)   << 31)

/*
 * Cause.ExcCode trap codes.
 */
#घोषणा EXCCODE_INT		0	/* Interrupt pending */
#घोषणा EXCCODE_MOD		1	/* TLB modअगरied fault */
#घोषणा EXCCODE_TLBL		2	/* TLB miss on load or अगरetch */
#घोषणा EXCCODE_TLBS		3	/* TLB miss on a store */
#घोषणा EXCCODE_ADEL		4	/* Address error on a load or अगरetch */
#घोषणा EXCCODE_ADES		5	/* Address error on a store */
#घोषणा EXCCODE_IBE		6	/* Bus error on an अगरetch */
#घोषणा EXCCODE_DBE		7	/* Bus error on a load or store */
#घोषणा EXCCODE_SYS		8	/* System call */
#घोषणा EXCCODE_BP		9	/* Breakpoपूर्णांक */
#घोषणा EXCCODE_RI		10	/* Reserved inकाष्ठाion exception */
#घोषणा EXCCODE_CPU		11	/* Coprocessor unusable */
#घोषणा EXCCODE_OV		12	/* Arithmetic overflow */
#घोषणा EXCCODE_TR		13	/* Trap inकाष्ठाion */
#घोषणा EXCCODE_MSAFPE		14	/* MSA भग्नing poपूर्णांक exception */
#घोषणा EXCCODE_FPE		15	/* Floating poपूर्णांक exception */
#घोषणा EXCCODE_TLBRI		19	/* TLB Read-Inhibit exception */
#घोषणा EXCCODE_TLBXI		20	/* TLB Execution-Inhibit exception */
#घोषणा EXCCODE_MSADIS		21	/* MSA disabled exception */
#घोषणा EXCCODE_MDMX		22	/* MDMX unusable exception */
#घोषणा EXCCODE_WATCH		23	/* Watch address reference */
#घोषणा EXCCODE_MCHECK		24	/* Machine check */
#घोषणा EXCCODE_THREAD		25	/* Thपढ़ो exceptions (MT) */
#घोषणा EXCCODE_DSPDIS		26	/* DSP disabled exception */
#घोषणा EXCCODE_GE		27	/* Virtualized guest exception (VZ) */
#घोषणा EXCCODE_CACHEERR	30	/* Parity/ECC occured on a core */

/* Implementation specअगरic trap codes used by MIPS cores */
#घोषणा MIPS_EXCCODE_TLBPAR	16	/* TLB parity error exception */

/* Implementation specअगरic trap codes used by Loongson cores */
#घोषणा LOONGSON_EXCCODE_GSEXC	16	/* Loongson-specअगरic exception */

/*
 * Bits in the coprocessor 0 config रेजिस्टर.
 */
/* Generic bits.  */
#घोषणा CONF_CM_CACHABLE_NO_WA		0
#घोषणा CONF_CM_CACHABLE_WA		1
#घोषणा CONF_CM_UNCACHED		2
#घोषणा CONF_CM_CACHABLE_NONCOHERENT	3
#घोषणा CONF_CM_CACHABLE_CE		4
#घोषणा CONF_CM_CACHABLE_COW		5
#घोषणा CONF_CM_CACHABLE_CUW		6
#घोषणा CONF_CM_CACHABLE_ACCELERATED	7
#घोषणा CONF_CM_CMASK			7
#घोषणा CONF_BE			(_ULCAST_(1) << 15)

/* Bits common to various processors.  */
#घोषणा CONF_CU			(_ULCAST_(1) <<	 3)
#घोषणा CONF_DB			(_ULCAST_(1) <<	 4)
#घोषणा CONF_IB			(_ULCAST_(1) <<	 5)
#घोषणा CONF_DC			(_ULCAST_(7) <<	 6)
#घोषणा CONF_IC			(_ULCAST_(7) <<	 9)
#घोषणा CONF_EB			(_ULCAST_(1) << 13)
#घोषणा CONF_EM			(_ULCAST_(1) << 14)
#घोषणा CONF_SM			(_ULCAST_(1) << 16)
#घोषणा CONF_SC			(_ULCAST_(1) << 17)
#घोषणा CONF_EW			(_ULCAST_(3) << 18)
#घोषणा CONF_EP			(_ULCAST_(15)<< 24)
#घोषणा CONF_EC			(_ULCAST_(7) << 28)
#घोषणा CONF_CM			(_ULCAST_(1) << 31)

/* Bits specअगरic to the R4xx0.	*/
#घोषणा R4K_CONF_SW		(_ULCAST_(1) << 20)
#घोषणा R4K_CONF_SS		(_ULCAST_(1) << 21)
#घोषणा R4K_CONF_SB		(_ULCAST_(3) << 22)

/* Bits specअगरic to the R5000.	*/
#घोषणा R5K_CONF_SE		(_ULCAST_(1) << 12)
#घोषणा R5K_CONF_SS		(_ULCAST_(3) << 20)

/* Bits specअगरic to the RM7000.	 */
#घोषणा RM7K_CONF_SE		(_ULCAST_(1) <<	 3)
#घोषणा RM7K_CONF_TE		(_ULCAST_(1) << 12)
#घोषणा RM7K_CONF_CLK		(_ULCAST_(1) << 16)
#घोषणा RM7K_CONF_TC		(_ULCAST_(1) << 17)
#घोषणा RM7K_CONF_SI		(_ULCAST_(3) << 20)
#घोषणा RM7K_CONF_SC		(_ULCAST_(1) << 31)

/* Bits specअगरic to the R10000.	 */
#घोषणा R10K_CONF_DN		(_ULCAST_(3) <<	 3)
#घोषणा R10K_CONF_CT		(_ULCAST_(1) <<	 5)
#घोषणा R10K_CONF_PE		(_ULCAST_(1) <<	 6)
#घोषणा R10K_CONF_PM		(_ULCAST_(3) <<	 7)
#घोषणा R10K_CONF_EC		(_ULCAST_(15)<<	 9)
#घोषणा R10K_CONF_SB		(_ULCAST_(1) << 13)
#घोषणा R10K_CONF_SK		(_ULCAST_(1) << 14)
#घोषणा R10K_CONF_SS		(_ULCAST_(7) << 16)
#घोषणा R10K_CONF_SC		(_ULCAST_(7) << 19)
#घोषणा R10K_CONF_DC		(_ULCAST_(7) << 26)
#घोषणा R10K_CONF_IC		(_ULCAST_(7) << 29)

/* Bits specअगरic to the VR41xx.	 */
#घोषणा VR41_CONF_CS		(_ULCAST_(1) << 12)
#घोषणा VR41_CONF_P4K		(_ULCAST_(1) << 13)
#घोषणा VR41_CONF_BP		(_ULCAST_(1) << 16)
#घोषणा VR41_CONF_M16		(_ULCAST_(1) << 20)
#घोषणा VR41_CONF_AD		(_ULCAST_(1) << 23)

/* Bits specअगरic to the R30xx.	*/
#घोषणा R30XX_CONF_FDM		(_ULCAST_(1) << 19)
#घोषणा R30XX_CONF_REV		(_ULCAST_(1) << 22)
#घोषणा R30XX_CONF_AC		(_ULCAST_(1) << 23)
#घोषणा R30XX_CONF_RF		(_ULCAST_(1) << 24)
#घोषणा R30XX_CONF_HALT		(_ULCAST_(1) << 25)
#घोषणा R30XX_CONF_FPINT	(_ULCAST_(7) << 26)
#घोषणा R30XX_CONF_DBR		(_ULCAST_(1) << 29)
#घोषणा R30XX_CONF_SB		(_ULCAST_(1) << 30)
#घोषणा R30XX_CONF_LOCK		(_ULCAST_(1) << 31)

/* Bits specअगरic to the TX49.  */
#घोषणा TX49_CONF_DC		(_ULCAST_(1) << 16)
#घोषणा TX49_CONF_IC		(_ULCAST_(1) << 17)  /* conflict with CONF_SC */
#घोषणा TX49_CONF_HALT		(_ULCAST_(1) << 18)
#घोषणा TX49_CONF_CWFON		(_ULCAST_(1) << 27)

/* Bits specअगरic to the MIPS32/64 PRA.	*/
#घोषणा MIPS_CONF_VI		(_ULCAST_(1) <<  3)
#घोषणा MIPS_CONF_MT		(_ULCAST_(7) <<	 7)
#घोषणा MIPS_CONF_MT_TLB	(_ULCAST_(1) <<  7)
#घोषणा MIPS_CONF_MT_FTLB	(_ULCAST_(4) <<  7)
#घोषणा MIPS_CONF_AR		(_ULCAST_(7) << 10)
#घोषणा MIPS_CONF_AT		(_ULCAST_(3) << 13)
#घोषणा MIPS_CONF_BE		(_ULCAST_(1) << 15)
#घोषणा MIPS_CONF_BM		(_ULCAST_(1) << 16)
#घोषणा MIPS_CONF_MM		(_ULCAST_(3) << 17)
#घोषणा MIPS_CONF_MM_SYSAD	(_ULCAST_(1) << 17)
#घोषणा MIPS_CONF_MM_FULL	(_ULCAST_(2) << 17)
#घोषणा MIPS_CONF_SB		(_ULCAST_(1) << 21)
#घोषणा MIPS_CONF_UDI		(_ULCAST_(1) << 22)
#घोषणा MIPS_CONF_DSP		(_ULCAST_(1) << 23)
#घोषणा MIPS_CONF_ISP		(_ULCAST_(1) << 24)
#घोषणा MIPS_CONF_KU		(_ULCAST_(3) << 25)
#घोषणा MIPS_CONF_K23		(_ULCAST_(3) << 28)
#घोषणा MIPS_CONF_M		(_ULCAST_(1) << 31)

/*
 * Bits in the MIPS32/64 PRA coprocessor 0 config रेजिस्टरs 1 and above.
 */
#घोषणा MIPS_CONF1_FP		(_ULCAST_(1) <<	 0)
#घोषणा MIPS_CONF1_EP		(_ULCAST_(1) <<	 1)
#घोषणा MIPS_CONF1_CA		(_ULCAST_(1) <<	 2)
#घोषणा MIPS_CONF1_WR		(_ULCAST_(1) <<	 3)
#घोषणा MIPS_CONF1_PC		(_ULCAST_(1) <<	 4)
#घोषणा MIPS_CONF1_MD		(_ULCAST_(1) <<	 5)
#घोषणा MIPS_CONF1_C2		(_ULCAST_(1) <<	 6)
#घोषणा MIPS_CONF1_DA_SHF	7
#घोषणा MIPS_CONF1_DA_SZ	3
#घोषणा MIPS_CONF1_DA		(_ULCAST_(7) <<	 7)
#घोषणा MIPS_CONF1_DL_SHF	10
#घोषणा MIPS_CONF1_DL_SZ	3
#घोषणा MIPS_CONF1_DL		(_ULCAST_(7) << 10)
#घोषणा MIPS_CONF1_DS_SHF	13
#घोषणा MIPS_CONF1_DS_SZ	3
#घोषणा MIPS_CONF1_DS		(_ULCAST_(7) << 13)
#घोषणा MIPS_CONF1_IA_SHF	16
#घोषणा MIPS_CONF1_IA_SZ	3
#घोषणा MIPS_CONF1_IA		(_ULCAST_(7) << 16)
#घोषणा MIPS_CONF1_IL_SHF	19
#घोषणा MIPS_CONF1_IL_SZ	3
#घोषणा MIPS_CONF1_IL		(_ULCAST_(7) << 19)
#घोषणा MIPS_CONF1_IS_SHF	22
#घोषणा MIPS_CONF1_IS_SZ	3
#घोषणा MIPS_CONF1_IS		(_ULCAST_(7) << 22)
#घोषणा MIPS_CONF1_TLBS_SHIFT   (25)
#घोषणा MIPS_CONF1_TLBS_SIZE    (6)
#घोषणा MIPS_CONF1_TLBS         (_ULCAST_(63) << MIPS_CONF1_TLBS_SHIFT)

#घोषणा MIPS_CONF2_SA		(_ULCAST_(15)<<	 0)
#घोषणा MIPS_CONF2_SL		(_ULCAST_(15)<<	 4)
#घोषणा MIPS_CONF2_SS		(_ULCAST_(15)<<	 8)
#घोषणा MIPS_CONF2_SU		(_ULCAST_(15)<< 12)
#घोषणा MIPS_CONF2_TA		(_ULCAST_(15)<< 16)
#घोषणा MIPS_CONF2_TL		(_ULCAST_(15)<< 20)
#घोषणा MIPS_CONF2_TS		(_ULCAST_(15)<< 24)
#घोषणा MIPS_CONF2_TU		(_ULCAST_(7) << 28)

#घोषणा MIPS_CONF3_TL		(_ULCAST_(1) <<	 0)
#घोषणा MIPS_CONF3_SM		(_ULCAST_(1) <<	 1)
#घोषणा MIPS_CONF3_MT		(_ULCAST_(1) <<	 2)
#घोषणा MIPS_CONF3_CDMM		(_ULCAST_(1) <<	 3)
#घोषणा MIPS_CONF3_SP		(_ULCAST_(1) <<	 4)
#घोषणा MIPS_CONF3_VINT		(_ULCAST_(1) <<	 5)
#घोषणा MIPS_CONF3_VEIC		(_ULCAST_(1) <<	 6)
#घोषणा MIPS_CONF3_LPA		(_ULCAST_(1) <<	 7)
#घोषणा MIPS_CONF3_ITL		(_ULCAST_(1) <<	 8)
#घोषणा MIPS_CONF3_CTXTC	(_ULCAST_(1) <<	 9)
#घोषणा MIPS_CONF3_DSP		(_ULCAST_(1) << 10)
#घोषणा MIPS_CONF3_DSP2P	(_ULCAST_(1) << 11)
#घोषणा MIPS_CONF3_RXI		(_ULCAST_(1) << 12)
#घोषणा MIPS_CONF3_ULRI		(_ULCAST_(1) << 13)
#घोषणा MIPS_CONF3_ISA		(_ULCAST_(3) << 14)
#घोषणा MIPS_CONF3_ISA_OE	(_ULCAST_(1) << 16)
#घोषणा MIPS_CONF3_MCU		(_ULCAST_(1) << 17)
#घोषणा MIPS_CONF3_MMAR		(_ULCAST_(7) << 18)
#घोषणा MIPS_CONF3_IPLW		(_ULCAST_(3) << 21)
#घोषणा MIPS_CONF3_VZ		(_ULCAST_(1) << 23)
#घोषणा MIPS_CONF3_PW		(_ULCAST_(1) << 24)
#घोषणा MIPS_CONF3_SC		(_ULCAST_(1) << 25)
#घोषणा MIPS_CONF3_BI		(_ULCAST_(1) << 26)
#घोषणा MIPS_CONF3_BP		(_ULCAST_(1) << 27)
#घोषणा MIPS_CONF3_MSA		(_ULCAST_(1) << 28)
#घोषणा MIPS_CONF3_CMGCR	(_ULCAST_(1) << 29)
#घोषणा MIPS_CONF3_BPG		(_ULCAST_(1) << 30)

#घोषणा MIPS_CONF4_MMUSIZEEXT_SHIFT	(0)
#घोषणा MIPS_CONF4_MMUSIZEEXT	(_ULCAST_(255) << 0)
#घोषणा MIPS_CONF4_FTLBSETS_SHIFT	(0)
#घोषणा MIPS_CONF4_FTLBSETS	(_ULCAST_(15) << MIPS_CONF4_FTLBSETS_SHIFT)
#घोषणा MIPS_CONF4_FTLBWAYS_SHIFT	(4)
#घोषणा MIPS_CONF4_FTLBWAYS	(_ULCAST_(15) << MIPS_CONF4_FTLBWAYS_SHIFT)
#घोषणा MIPS_CONF4_FTLBPAGESIZE_SHIFT	(8)
/* bits 10:8 in FTLB-only configurations */
#घोषणा MIPS_CONF4_FTLBPAGESIZE (_ULCAST_(7) << MIPS_CONF4_FTLBPAGESIZE_SHIFT)
/* bits 12:8 in VTLB-FTLB only configurations */
#घोषणा MIPS_CONF4_VFTLBPAGESIZE (_ULCAST_(31) << MIPS_CONF4_FTLBPAGESIZE_SHIFT)
#घोषणा MIPS_CONF4_MMUEXTDEF	(_ULCAST_(3) << 14)
#घोषणा MIPS_CONF4_MMUEXTDEF_MMUSIZEEXT (_ULCAST_(1) << 14)
#घोषणा MIPS_CONF4_MMUEXTDEF_FTLBSIZEEXT	(_ULCAST_(2) << 14)
#घोषणा MIPS_CONF4_MMUEXTDEF_VTLBSIZEEXT	(_ULCAST_(3) << 14)
#घोषणा MIPS_CONF4_KSCREXIST_SHIFT	(16)
#घोषणा MIPS_CONF4_KSCREXIST	(_ULCAST_(255) << MIPS_CONF4_KSCREXIST_SHIFT)
#घोषणा MIPS_CONF4_VTLBSIZEEXT_SHIFT	(24)
#घोषणा MIPS_CONF4_VTLBSIZEEXT	(_ULCAST_(15) << MIPS_CONF4_VTLBSIZEEXT_SHIFT)
#घोषणा MIPS_CONF4_AE		(_ULCAST_(1) << 28)
#घोषणा MIPS_CONF4_IE		(_ULCAST_(3) << 29)
#घोषणा MIPS_CONF4_TLBINV	(_ULCAST_(2) << 29)

#घोषणा MIPS_CONF5_NF		(_ULCAST_(1) << 0)
#घोषणा MIPS_CONF5_UFR		(_ULCAST_(1) << 2)
#घोषणा MIPS_CONF5_MRP		(_ULCAST_(1) << 3)
#घोषणा MIPS_CONF5_LLB		(_ULCAST_(1) << 4)
#घोषणा MIPS_CONF5_MVH		(_ULCAST_(1) << 5)
#घोषणा MIPS_CONF5_VP		(_ULCAST_(1) << 7)
#घोषणा MIPS_CONF5_SBRI		(_ULCAST_(1) << 6)
#घोषणा MIPS_CONF5_FRE		(_ULCAST_(1) << 8)
#घोषणा MIPS_CONF5_UFE		(_ULCAST_(1) << 9)
#घोषणा MIPS_CONF5_CA2		(_ULCAST_(1) << 14)
#घोषणा MIPS_CONF5_MI		(_ULCAST_(1) << 17)
#घोषणा MIPS_CONF5_CRCP		(_ULCAST_(1) << 18)
#घोषणा MIPS_CONF5_MSAEN	(_ULCAST_(1) << 27)
#घोषणा MIPS_CONF5_EVA		(_ULCAST_(1) << 28)
#घोषणा MIPS_CONF5_CV		(_ULCAST_(1) << 29)
#घोषणा MIPS_CONF5_K		(_ULCAST_(1) << 30)

/* Config6 feature bits क्रम proAptiv/P5600 */

/* Jump रेजिस्टर cache prediction disable */
#घोषणा MTI_CONF6_JRCD		(_ULCAST_(1) << 0)
/* MIPSr6 extensions enable */
#घोषणा MTI_CONF6_R6		(_ULCAST_(1) << 2)
/* IFU Perक्रमmance Control */
#घोषणा MTI_CONF6_IFUPERFCTL	(_ULCAST_(3) << 10)
#घोषणा MTI_CONF6_SYND		(_ULCAST_(1) << 13)
/* Sleep state perक्रमmance counter disable */
#घोषणा MTI_CONF6_SPCD		(_ULCAST_(1) << 14)
/* proAptiv FTLB on/off bit */
#घोषणा MTI_CONF6_FTLBEN	(_ULCAST_(1) << 15)
/* Disable load/store bonding */
#घोषणा MTI_CONF6_DLSB		(_ULCAST_(1) << 21)
/* FTLB probability bits */
#घोषणा MTI_CONF6_FTLBP_SHIFT	(16)

/* Config6 feature bits क्रम Loongson-3 */

/* Loongson-3 पूर्णांकernal समयr bit */
#घोषणा LOONGSON_CONF6_INTIMER	(_ULCAST_(1) << 6)
/* Loongson-3 बाह्यal समयr bit */
#घोषणा LOONGSON_CONF6_EXTIMER	(_ULCAST_(1) << 7)
/* Loongson-3 SFB on/off bit, STFill in manual */
#घोषणा LOONGSON_CONF6_SFBEN	(_ULCAST_(1) << 8)
/* Loongson-3's LL on exclusive cacheline */
#घोषणा LOONGSON_CONF6_LLEXC	(_ULCAST_(1) << 16)
/* Loongson-3's SC has a अक्रमom delay */
#घोषणा LOONGSON_CONF6_SCRAND	(_ULCAST_(1) << 17)
/* Loongson-3 FTLB on/off bit, VTLBOnly in manual */
#घोषणा LOONGSON_CONF6_FTLBDIS	(_ULCAST_(1) << 22)

#घोषणा MIPS_CONF7_WII		(_ULCAST_(1) << 31)

#घोषणा MIPS_CONF7_RPS		(_ULCAST_(1) << 2)

#घोषणा MIPS_CONF7_IAR		(_ULCAST_(1) << 10)
#घोषणा MIPS_CONF7_AR		(_ULCAST_(1) << 16)

/* Ingenic HPTLB off bits */
#घोषणा XBURST_PAGECTRL_HPTLB_DIS 0xa9000000

/* Ingenic Config7 bits */
#घोषणा MIPS_CONF7_BTB_LOOP_EN	(_ULCAST_(1) << 4)

/* Config7 Bits specअगरic to MIPS Technologies. */

/* Perक्रमmance counters implemented Per TC */
#घोषणा MTI_CONF7_PTC		(_ULCAST_(1) << 19)

/* WatchLo* रेजिस्टर definitions */
#घोषणा MIPS_WATCHLO_IRW	(_ULCAST_(0x7) << 0)

/* WatchHi* रेजिस्टर definitions */
#घोषणा MIPS_WATCHHI_M		(_ULCAST_(1) << 31)
#घोषणा MIPS_WATCHHI_G		(_ULCAST_(1) << 30)
#घोषणा MIPS_WATCHHI_WM		(_ULCAST_(0x3) << 28)
#घोषणा MIPS_WATCHHI_WM_R_RVA	(_ULCAST_(0) << 28)
#घोषणा MIPS_WATCHHI_WM_R_GPA	(_ULCAST_(1) << 28)
#घोषणा MIPS_WATCHHI_WM_G_GVA	(_ULCAST_(2) << 28)
#घोषणा MIPS_WATCHHI_EAS	(_ULCAST_(0x3) << 24)
#घोषणा MIPS_WATCHHI_ASID	(_ULCAST_(0xff) << 16)
#घोषणा MIPS_WATCHHI_MASK	(_ULCAST_(0x1ff) << 3)
#घोषणा MIPS_WATCHHI_I		(_ULCAST_(1) << 2)
#घोषणा MIPS_WATCHHI_R		(_ULCAST_(1) << 1)
#घोषणा MIPS_WATCHHI_W		(_ULCAST_(1) << 0)
#घोषणा MIPS_WATCHHI_IRW	(_ULCAST_(0x7) << 0)

/* PerfCnt control रेजिस्टर definitions */
#घोषणा MIPS_PERFCTRL_EXL	(_ULCAST_(1) << 0)
#घोषणा MIPS_PERFCTRL_K		(_ULCAST_(1) << 1)
#घोषणा MIPS_PERFCTRL_S		(_ULCAST_(1) << 2)
#घोषणा MIPS_PERFCTRL_U		(_ULCAST_(1) << 3)
#घोषणा MIPS_PERFCTRL_IE	(_ULCAST_(1) << 4)
#घोषणा MIPS_PERFCTRL_EVENT_S	5
#घोषणा MIPS_PERFCTRL_EVENT	(_ULCAST_(0x3ff) << MIPS_PERFCTRL_EVENT_S)
#घोषणा MIPS_PERFCTRL_PCTD	(_ULCAST_(1) << 15)
#घोषणा MIPS_PERFCTRL_EC	(_ULCAST_(0x3) << 23)
#घोषणा MIPS_PERFCTRL_EC_R	(_ULCAST_(0) << 23)
#घोषणा MIPS_PERFCTRL_EC_RI	(_ULCAST_(1) << 23)
#घोषणा MIPS_PERFCTRL_EC_G	(_ULCAST_(2) << 23)
#घोषणा MIPS_PERFCTRL_EC_GRI	(_ULCAST_(3) << 23)
#घोषणा MIPS_PERFCTRL_W		(_ULCAST_(1) << 30)
#घोषणा MIPS_PERFCTRL_M		(_ULCAST_(1) << 31)

/* PerfCnt control रेजिस्टर MT extensions used by MIPS cores */
#घोषणा MIPS_PERFCTRL_VPEID_S	16
#घोषणा MIPS_PERFCTRL_VPEID	(_ULCAST_(0xf) << MIPS_PERFCTRL_VPEID_S)
#घोषणा MIPS_PERFCTRL_TCID_S	22
#घोषणा MIPS_PERFCTRL_TCID	(_ULCAST_(0xff) << MIPS_PERFCTRL_TCID_S)
#घोषणा MIPS_PERFCTRL_MT_EN	(_ULCAST_(0x3) << 20)
#घोषणा MIPS_PERFCTRL_MT_EN_ALL	(_ULCAST_(0) << 20)
#घोषणा MIPS_PERFCTRL_MT_EN_VPE	(_ULCAST_(1) << 20)
#घोषणा MIPS_PERFCTRL_MT_EN_TC	(_ULCAST_(2) << 20)

/* PerfCnt control रेजिस्टर MT extensions used by BMIPS5000 */
#घोषणा BRCM_PERFCTRL_TC	(_ULCAST_(1) << 30)

/* PerfCnt control रेजिस्टर MT extensions used by Netlogic XLR */
#घोषणा XLR_PERFCTRL_ALLTHREADS	(_ULCAST_(1) << 13)

/* MAAR bit definitions */
#घोषणा MIPS_MAAR_VH		(_U64CAST_(1) << 63)
#घोषणा MIPS_MAAR_ADDR		GENMASK_ULL(55, 12)
#घोषणा MIPS_MAAR_ADDR_SHIFT	12
#घोषणा MIPS_MAAR_S		(_ULCAST_(1) << 1)
#घोषणा MIPS_MAAR_VL		(_ULCAST_(1) << 0)
#अगर_घोषित CONFIG_XPA
#घोषणा MIPS_MAAR_V		(MIPS_MAAR_VH | MIPS_MAAR_VL)
#अन्यथा
#घोषणा MIPS_MAAR_V		MIPS_MAAR_VL
#पूर्ण_अगर
#घोषणा MIPS_MAARX_VH		(_ULCAST_(1) << 31)
#घोषणा MIPS_MAARX_ADDR		0xF
#घोषणा MIPS_MAARX_ADDR_SHIFT	32

/* MAARI bit definitions */
#घोषणा MIPS_MAARI_INDEX	(_ULCAST_(0x3f) << 0)

/* EBase bit definitions */
#घोषणा MIPS_EBASE_CPUNUM_SHIFT	0
#घोषणा MIPS_EBASE_CPUNUM	(_ULCAST_(0x3ff) << 0)
#घोषणा MIPS_EBASE_WG_SHIFT	11
#घोषणा MIPS_EBASE_WG		(_ULCAST_(1) << 11)
#घोषणा MIPS_EBASE_BASE_SHIFT	12
#घोषणा MIPS_EBASE_BASE		(~_ULCAST_((1 << MIPS_EBASE_BASE_SHIFT) - 1))

/* CMGCRBase bit definitions */
#घोषणा MIPS_CMGCRB_BASE	11
#घोषणा MIPS_CMGCRF_BASE	(~_ULCAST_((1 << MIPS_CMGCRB_BASE) - 1))

/* LLAddr bit definitions */
#घोषणा MIPS_LLADDR_LLB_SHIFT	0
#घोषणा MIPS_LLADDR_LLB		(_ULCAST_(1) << MIPS_LLADDR_LLB_SHIFT)

/*
 * Bits in the MIPS32 Memory Segmentation रेजिस्टरs.
 */
#घोषणा MIPS_SEGCFG_PA_SHIFT	9
#घोषणा MIPS_SEGCFG_PA		(_ULCAST_(127) << MIPS_SEGCFG_PA_SHIFT)
#घोषणा MIPS_SEGCFG_AM_SHIFT	4
#घोषणा MIPS_SEGCFG_AM		(_ULCAST_(7) << MIPS_SEGCFG_AM_SHIFT)
#घोषणा MIPS_SEGCFG_EU_SHIFT	3
#घोषणा MIPS_SEGCFG_EU		(_ULCAST_(1) << MIPS_SEGCFG_EU_SHIFT)
#घोषणा MIPS_SEGCFG_C_SHIFT	0
#घोषणा MIPS_SEGCFG_C		(_ULCAST_(7) << MIPS_SEGCFG_C_SHIFT)

#घोषणा MIPS_SEGCFG_UUSK	_ULCAST_(7)
#घोषणा MIPS_SEGCFG_USK		_ULCAST_(5)
#घोषणा MIPS_SEGCFG_MUSUK	_ULCAST_(4)
#घोषणा MIPS_SEGCFG_MUSK	_ULCAST_(3)
#घोषणा MIPS_SEGCFG_MSK		_ULCAST_(2)
#घोषणा MIPS_SEGCFG_MK		_ULCAST_(1)
#घोषणा MIPS_SEGCFG_UK		_ULCAST_(0)

#घोषणा MIPS_PWFIELD_GDI_SHIFT	24
#घोषणा MIPS_PWFIELD_GDI_MASK	0x3f000000
#घोषणा MIPS_PWFIELD_UDI_SHIFT	18
#घोषणा MIPS_PWFIELD_UDI_MASK	0x00fc0000
#घोषणा MIPS_PWFIELD_MDI_SHIFT	12
#घोषणा MIPS_PWFIELD_MDI_MASK	0x0003f000
#घोषणा MIPS_PWFIELD_PTI_SHIFT	6
#घोषणा MIPS_PWFIELD_PTI_MASK	0x00000fc0
#घोषणा MIPS_PWFIELD_PTEI_SHIFT	0
#घोषणा MIPS_PWFIELD_PTEI_MASK	0x0000003f

#घोषणा MIPS_PWSIZE_PS_SHIFT	30
#घोषणा MIPS_PWSIZE_PS_MASK	0x40000000
#घोषणा MIPS_PWSIZE_GDW_SHIFT	24
#घोषणा MIPS_PWSIZE_GDW_MASK	0x3f000000
#घोषणा MIPS_PWSIZE_UDW_SHIFT	18
#घोषणा MIPS_PWSIZE_UDW_MASK	0x00fc0000
#घोषणा MIPS_PWSIZE_MDW_SHIFT	12
#घोषणा MIPS_PWSIZE_MDW_MASK	0x0003f000
#घोषणा MIPS_PWSIZE_PTW_SHIFT	6
#घोषणा MIPS_PWSIZE_PTW_MASK	0x00000fc0
#घोषणा MIPS_PWSIZE_PTEW_SHIFT	0
#घोषणा MIPS_PWSIZE_PTEW_MASK	0x0000003f

#घोषणा MIPS_PWCTL_PWEN_SHIFT	31
#घोषणा MIPS_PWCTL_PWEN_MASK	0x80000000
#घोषणा MIPS_PWCTL_XK_SHIFT	28
#घोषणा MIPS_PWCTL_XK_MASK	0x10000000
#घोषणा MIPS_PWCTL_XS_SHIFT	27
#घोषणा MIPS_PWCTL_XS_MASK	0x08000000
#घोषणा MIPS_PWCTL_XU_SHIFT	26
#घोषणा MIPS_PWCTL_XU_MASK	0x04000000
#घोषणा MIPS_PWCTL_DPH_SHIFT	7
#घोषणा MIPS_PWCTL_DPH_MASK	0x00000080
#घोषणा MIPS_PWCTL_HUGEPG_SHIFT	6
#घोषणा MIPS_PWCTL_HUGEPG_MASK	0x00000060
#घोषणा MIPS_PWCTL_PSN_SHIFT	0
#घोषणा MIPS_PWCTL_PSN_MASK	0x0000003f

/* GuestCtl0 fields */
#घोषणा MIPS_GCTL0_GM_SHIFT	31
#घोषणा MIPS_GCTL0_GM		(_ULCAST_(1) << MIPS_GCTL0_GM_SHIFT)
#घोषणा MIPS_GCTL0_RI_SHIFT	30
#घोषणा MIPS_GCTL0_RI		(_ULCAST_(1) << MIPS_GCTL0_RI_SHIFT)
#घोषणा MIPS_GCTL0_MC_SHIFT	29
#घोषणा MIPS_GCTL0_MC		(_ULCAST_(1) << MIPS_GCTL0_MC_SHIFT)
#घोषणा MIPS_GCTL0_CP0_SHIFT	28
#घोषणा MIPS_GCTL0_CP0		(_ULCAST_(1) << MIPS_GCTL0_CP0_SHIFT)
#घोषणा MIPS_GCTL0_AT_SHIFT	26
#घोषणा MIPS_GCTL0_AT		(_ULCAST_(0x3) << MIPS_GCTL0_AT_SHIFT)
#घोषणा MIPS_GCTL0_GT_SHIFT	25
#घोषणा MIPS_GCTL0_GT		(_ULCAST_(1) << MIPS_GCTL0_GT_SHIFT)
#घोषणा MIPS_GCTL0_CG_SHIFT	24
#घोषणा MIPS_GCTL0_CG		(_ULCAST_(1) << MIPS_GCTL0_CG_SHIFT)
#घोषणा MIPS_GCTL0_CF_SHIFT	23
#घोषणा MIPS_GCTL0_CF		(_ULCAST_(1) << MIPS_GCTL0_CF_SHIFT)
#घोषणा MIPS_GCTL0_G1_SHIFT	22
#घोषणा MIPS_GCTL0_G1		(_ULCAST_(1) << MIPS_GCTL0_G1_SHIFT)
#घोषणा MIPS_GCTL0_G0E_SHIFT	19
#घोषणा MIPS_GCTL0_G0E		(_ULCAST_(1) << MIPS_GCTL0_G0E_SHIFT)
#घोषणा MIPS_GCTL0_PT_SHIFT	18
#घोषणा MIPS_GCTL0_PT		(_ULCAST_(1) << MIPS_GCTL0_PT_SHIFT)
#घोषणा MIPS_GCTL0_RAD_SHIFT	9
#घोषणा MIPS_GCTL0_RAD		(_ULCAST_(1) << MIPS_GCTL0_RAD_SHIFT)
#घोषणा MIPS_GCTL0_DRG_SHIFT	8
#घोषणा MIPS_GCTL0_DRG		(_ULCAST_(1) << MIPS_GCTL0_DRG_SHIFT)
#घोषणा MIPS_GCTL0_G2_SHIFT	7
#घोषणा MIPS_GCTL0_G2		(_ULCAST_(1) << MIPS_GCTL0_G2_SHIFT)
#घोषणा MIPS_GCTL0_GEXC_SHIFT	2
#घोषणा MIPS_GCTL0_GEXC		(_ULCAST_(0x1f) << MIPS_GCTL0_GEXC_SHIFT)
#घोषणा MIPS_GCTL0_SFC2_SHIFT	1
#घोषणा MIPS_GCTL0_SFC2		(_ULCAST_(1) << MIPS_GCTL0_SFC2_SHIFT)
#घोषणा MIPS_GCTL0_SFC1_SHIFT	0
#घोषणा MIPS_GCTL0_SFC1		(_ULCAST_(1) << MIPS_GCTL0_SFC1_SHIFT)

/* GuestCtl0.AT Guest address translation control */
#घोषणा MIPS_GCTL0_AT_ROOT	1  /* Guest MMU under Root control */
#घोषणा MIPS_GCTL0_AT_GUEST	3  /* Guest MMU under Guest control */

/* GuestCtl0.GExcCode Hypervisor exception cause codes */
#घोषणा MIPS_GCTL0_GEXC_GPSI	0  /* Guest Privileged Sensitive Inकाष्ठाion */
#घोषणा MIPS_GCTL0_GEXC_GSFC	1  /* Guest Software Field Change */
#घोषणा MIPS_GCTL0_GEXC_HC	2  /* Hypercall */
#घोषणा MIPS_GCTL0_GEXC_GRR	3  /* Guest Reserved Inकाष्ठाion Redirect */
#घोषणा MIPS_GCTL0_GEXC_GVA	8  /* Guest Virtual Address available */
#घोषणा MIPS_GCTL0_GEXC_GHFC	9  /* Guest Hardware Field Change */
#घोषणा MIPS_GCTL0_GEXC_GPA	10 /* Guest Physical Address available */

/* GuestCtl0Ext fields */
#घोषणा MIPS_GCTL0EXT_RPW_SHIFT	8
#घोषणा MIPS_GCTL0EXT_RPW	(_ULCAST_(0x3) << MIPS_GCTL0EXT_RPW_SHIFT)
#घोषणा MIPS_GCTL0EXT_NCC_SHIFT	6
#घोषणा MIPS_GCTL0EXT_NCC	(_ULCAST_(0x3) << MIPS_GCTL0EXT_NCC_SHIFT)
#घोषणा MIPS_GCTL0EXT_CGI_SHIFT	4
#घोषणा MIPS_GCTL0EXT_CGI	(_ULCAST_(1) << MIPS_GCTL0EXT_CGI_SHIFT)
#घोषणा MIPS_GCTL0EXT_FCD_SHIFT	3
#घोषणा MIPS_GCTL0EXT_FCD	(_ULCAST_(1) << MIPS_GCTL0EXT_FCD_SHIFT)
#घोषणा MIPS_GCTL0EXT_OG_SHIFT	2
#घोषणा MIPS_GCTL0EXT_OG	(_ULCAST_(1) << MIPS_GCTL0EXT_OG_SHIFT)
#घोषणा MIPS_GCTL0EXT_BG_SHIFT	1
#घोषणा MIPS_GCTL0EXT_BG	(_ULCAST_(1) << MIPS_GCTL0EXT_BG_SHIFT)
#घोषणा MIPS_GCTL0EXT_MG_SHIFT	0
#घोषणा MIPS_GCTL0EXT_MG	(_ULCAST_(1) << MIPS_GCTL0EXT_MG_SHIFT)

/* GuestCtl0Ext.RPW Root page walk configuration */
#घोषणा MIPS_GCTL0EXT_RPW_BOTH	0  /* Root PW क्रम GPA->RPA and RVA->RPA */
#घोषणा MIPS_GCTL0EXT_RPW_GPA	2  /* Root PW क्रम GPA->RPA */
#घोषणा MIPS_GCTL0EXT_RPW_RVA	3  /* Root PW क्रम RVA->RPA */

/* GuestCtl0Ext.NCC Nested cache coherency attributes */
#घोषणा MIPS_GCTL0EXT_NCC_IND	0  /* Guest CCA independent of Root CCA */
#घोषणा MIPS_GCTL0EXT_NCC_MOD	1  /* Guest CCA modअगरied by Root CCA */

/* GuestCtl1 fields */
#घोषणा MIPS_GCTL1_ID_SHIFT	0
#घोषणा MIPS_GCTL1_ID_WIDTH	8
#घोषणा MIPS_GCTL1_ID		(_ULCAST_(0xff) << MIPS_GCTL1_ID_SHIFT)
#घोषणा MIPS_GCTL1_RID_SHIFT	16
#घोषणा MIPS_GCTL1_RID_WIDTH	8
#घोषणा MIPS_GCTL1_RID		(_ULCAST_(0xff) << MIPS_GCTL1_RID_SHIFT)
#घोषणा MIPS_GCTL1_EID_SHIFT	24
#घोषणा MIPS_GCTL1_EID_WIDTH	8
#घोषणा MIPS_GCTL1_EID		(_ULCAST_(0xff) << MIPS_GCTL1_EID_SHIFT)

/* GuestID reserved क्रम root context */
#घोषणा MIPS_GCTL1_ROOT_GUESTID	0

/* CDMMBase रेजिस्टर bit definitions */
#घोषणा MIPS_CDMMBASE_SIZE_SHIFT 0
#घोषणा MIPS_CDMMBASE_SIZE	(_ULCAST_(511) << MIPS_CDMMBASE_SIZE_SHIFT)
#घोषणा MIPS_CDMMBASE_CI	(_ULCAST_(1) << 9)
#घोषणा MIPS_CDMMBASE_EN	(_ULCAST_(1) << 10)
#घोषणा MIPS_CDMMBASE_ADDR_SHIFT 11
#घोषणा MIPS_CDMMBASE_ADDR_START 15

/* RDHWR रेजिस्टर numbers */
#घोषणा MIPS_HWR_CPUNUM		0	/* CPU number */
#घोषणा MIPS_HWR_SYNCISTEP	1	/* SYNCI step size */
#घोषणा MIPS_HWR_CC		2	/* Cycle counter */
#घोषणा MIPS_HWR_CCRES		3	/* Cycle counter resolution */
#घोषणा MIPS_HWR_ULR		29	/* UserLocal */
#घोषणा MIPS_HWR_IMPL1		30	/* Implementation dependent */
#घोषणा MIPS_HWR_IMPL2		31	/* Implementation dependent */

/* Bits in HWREna रेजिस्टर */
#घोषणा MIPS_HWRENA_CPUNUM	(_ULCAST_(1) << MIPS_HWR_CPUNUM)
#घोषणा MIPS_HWRENA_SYNCISTEP	(_ULCAST_(1) << MIPS_HWR_SYNCISTEP)
#घोषणा MIPS_HWRENA_CC		(_ULCAST_(1) << MIPS_HWR_CC)
#घोषणा MIPS_HWRENA_CCRES	(_ULCAST_(1) << MIPS_HWR_CCRES)
#घोषणा MIPS_HWRENA_ULR		(_ULCAST_(1) << MIPS_HWR_ULR)
#घोषणा MIPS_HWRENA_IMPL1	(_ULCAST_(1) << MIPS_HWR_IMPL1)
#घोषणा MIPS_HWRENA_IMPL2	(_ULCAST_(1) << MIPS_HWR_IMPL2)

/*
 * Bitfields in the TX39 family CP0 Configuration Register 3
 */
#घोषणा TX39_CONF_ICS_SHIFT	19
#घोषणा TX39_CONF_ICS_MASK	0x00380000
#घोषणा TX39_CONF_ICS_1KB	0x00000000
#घोषणा TX39_CONF_ICS_2KB	0x00080000
#घोषणा TX39_CONF_ICS_4KB	0x00100000
#घोषणा TX39_CONF_ICS_8KB	0x00180000
#घोषणा TX39_CONF_ICS_16KB	0x00200000

#घोषणा TX39_CONF_DCS_SHIFT	16
#घोषणा TX39_CONF_DCS_MASK	0x00070000
#घोषणा TX39_CONF_DCS_1KB	0x00000000
#घोषणा TX39_CONF_DCS_2KB	0x00010000
#घोषणा TX39_CONF_DCS_4KB	0x00020000
#घोषणा TX39_CONF_DCS_8KB	0x00030000
#घोषणा TX39_CONF_DCS_16KB	0x00040000

#घोषणा TX39_CONF_CWFON		0x00004000
#घोषणा TX39_CONF_WBON		0x00002000
#घोषणा TX39_CONF_RF_SHIFT	10
#घोषणा TX39_CONF_RF_MASK	0x00000c00
#घोषणा TX39_CONF_DOZE		0x00000200
#घोषणा TX39_CONF_HALT		0x00000100
#घोषणा TX39_CONF_LOCK		0x00000080
#घोषणा TX39_CONF_ICE		0x00000020
#घोषणा TX39_CONF_DCE		0x00000010
#घोषणा TX39_CONF_IRSIZE_SHIFT	2
#घोषणा TX39_CONF_IRSIZE_MASK	0x0000000c
#घोषणा TX39_CONF_DRSIZE_SHIFT	0
#घोषणा TX39_CONF_DRSIZE_MASK	0x00000003

/*
 * Interesting Bits in the R10K CP0 Branch Diagnostic Register
 */
/* Disable Branch Target Address Cache */
#घोषणा R10K_DIAG_D_BTAC	(_ULCAST_(1) << 27)
/* Enable Branch Prediction Global History */
#घोषणा R10K_DIAG_E_GHIST	(_ULCAST_(1) << 26)
/* Disable Branch Return Cache */
#घोषणा R10K_DIAG_D_BRC		(_ULCAST_(1) << 22)

/* Flush BTB */
#घोषणा LOONGSON_DIAG_BTB	(_ULCAST_(1) << 1)
/* Flush ITLB */
#घोषणा LOONGSON_DIAG_ITLB	(_ULCAST_(1) << 2)
/* Flush DTLB */
#घोषणा LOONGSON_DIAG_DTLB	(_ULCAST_(1) << 3)
/* Allow some CACHE inकाष्ठाions (CACHE0, 1, 3, 21 and 23) in user mode */
#घोषणा LOONGSON_DIAG_UCAC	(_ULCAST_(1) << 8)
/* Flush VTLB */
#घोषणा LOONGSON_DIAG_VTLB	(_ULCAST_(1) << 12)
/* Flush FTLB */
#घोषणा LOONGSON_DIAG_FTLB	(_ULCAST_(1) << 13)

/*
 * Diag1 (GSCause in Loongson-speak) fields
 */
/* Loongson-specअगरic exception code (GSExcCode) */
#घोषणा LOONGSON_DIAG1_EXCCODE_SHIFT	2
#घोषणा LOONGSON_DIAG1_EXCCODE		GENMASK(6, 2)

/* CvmCtl रेजिस्टर field definitions */
#घोषणा CVMCTL_IPPCI_SHIFT	7
#घोषणा CVMCTL_IPPCI		(_U64CAST_(0x7) << CVMCTL_IPPCI_SHIFT)
#घोषणा CVMCTL_IPTI_SHIFT	4
#घोषणा CVMCTL_IPTI		(_U64CAST_(0x7) << CVMCTL_IPTI_SHIFT)

/* CvmMemCtl2 रेजिस्टर field definitions */
#घोषणा CVMMEMCTL2_INHIBITTS	(_U64CAST_(1) << 17)

/* CvmVMConfig रेजिस्टर field definitions */
#घोषणा CVMVMCONF_DGHT		(_U64CAST_(1) << 60)
#घोषणा CVMVMCONF_MMUSIZEM1_S	12
#घोषणा CVMVMCONF_MMUSIZEM1	(_U64CAST_(0xff) << CVMVMCONF_MMUSIZEM1_S)
#घोषणा CVMVMCONF_RMMUSIZEM1_S	0
#घोषणा CVMVMCONF_RMMUSIZEM1	(_U64CAST_(0xff) << CVMVMCONF_RMMUSIZEM1_S)

/* Debug रेजिस्टर field definitions */
#घोषणा MIPS_DEBUG_DBP_SHIFT	1
#घोषणा MIPS_DEBUG_DBP		(_ULCAST_(1) << MIPS_DEBUG_DBP_SHIFT)

/*
 * Coprocessor 1 (FPU) रेजिस्टर names
 */
#घोषणा CP1_REVISION	$0
#घोषणा CP1_UFR		$1
#घोषणा CP1_UNFR	$4
#घोषणा CP1_FCCR	$25
#घोषणा CP1_FEXR	$26
#घोषणा CP1_FENR	$28
#घोषणा CP1_STATUS	$31


/*
 * Bits in the MIPS32/64 coprocessor 1 (FPU) revision रेजिस्टर.
 */
#घोषणा MIPS_FPIR_S		(_ULCAST_(1) << 16)
#घोषणा MIPS_FPIR_D		(_ULCAST_(1) << 17)
#घोषणा MIPS_FPIR_PS		(_ULCAST_(1) << 18)
#घोषणा MIPS_FPIR_3D		(_ULCAST_(1) << 19)
#घोषणा MIPS_FPIR_W		(_ULCAST_(1) << 20)
#घोषणा MIPS_FPIR_L		(_ULCAST_(1) << 21)
#घोषणा MIPS_FPIR_F64		(_ULCAST_(1) << 22)
#घोषणा MIPS_FPIR_HAS2008	(_ULCAST_(1) << 23)
#घोषणा MIPS_FPIR_UFRP		(_ULCAST_(1) << 28)
#घोषणा MIPS_FPIR_FREP		(_ULCAST_(1) << 29)

/*
 * Bits in the MIPS32/64 coprocessor 1 (FPU) condition codes रेजिस्टर.
 */
#घोषणा MIPS_FCCR_CONDX_S	0
#घोषणा MIPS_FCCR_CONDX		(_ULCAST_(255) << MIPS_FCCR_CONDX_S)
#घोषणा MIPS_FCCR_COND0_S	0
#घोषणा MIPS_FCCR_COND0		(_ULCAST_(1) << MIPS_FCCR_COND0_S)
#घोषणा MIPS_FCCR_COND1_S	1
#घोषणा MIPS_FCCR_COND1		(_ULCAST_(1) << MIPS_FCCR_COND1_S)
#घोषणा MIPS_FCCR_COND2_S	2
#घोषणा MIPS_FCCR_COND2		(_ULCAST_(1) << MIPS_FCCR_COND2_S)
#घोषणा MIPS_FCCR_COND3_S	3
#घोषणा MIPS_FCCR_COND3		(_ULCAST_(1) << MIPS_FCCR_COND3_S)
#घोषणा MIPS_FCCR_COND4_S	4
#घोषणा MIPS_FCCR_COND4		(_ULCAST_(1) << MIPS_FCCR_COND4_S)
#घोषणा MIPS_FCCR_COND5_S	5
#घोषणा MIPS_FCCR_COND5		(_ULCAST_(1) << MIPS_FCCR_COND5_S)
#घोषणा MIPS_FCCR_COND6_S	6
#घोषणा MIPS_FCCR_COND6		(_ULCAST_(1) << MIPS_FCCR_COND6_S)
#घोषणा MIPS_FCCR_COND7_S	7
#घोषणा MIPS_FCCR_COND7		(_ULCAST_(1) << MIPS_FCCR_COND7_S)

/*
 * Bits in the MIPS32/64 coprocessor 1 (FPU) enables रेजिस्टर.
 */
#घोषणा MIPS_FENR_FS_S		2
#घोषणा MIPS_FENR_FS		(_ULCAST_(1) << MIPS_FENR_FS_S)

/*
 * FPU Status Register Values
 */
#घोषणा FPU_CSR_COND_S	23					/* $fcc0 */
#घोषणा FPU_CSR_COND	(_ULCAST_(1) << FPU_CSR_COND_S)

#घोषणा FPU_CSR_FS_S	24		/* flush denormalised results to 0 */
#घोषणा FPU_CSR_FS	(_ULCAST_(1) << FPU_CSR_FS_S)

#घोषणा FPU_CSR_CONDX_S	25					/* $fcc[7:1] */
#घोषणा FPU_CSR_CONDX	(_ULCAST_(127) << FPU_CSR_CONDX_S)
#घोषणा FPU_CSR_COND1_S	25					/* $fcc1 */
#घोषणा FPU_CSR_COND1	(_ULCAST_(1) << FPU_CSR_COND1_S)
#घोषणा FPU_CSR_COND2_S	26					/* $fcc2 */
#घोषणा FPU_CSR_COND2	(_ULCAST_(1) << FPU_CSR_COND2_S)
#घोषणा FPU_CSR_COND3_S	27					/* $fcc3 */
#घोषणा FPU_CSR_COND3	(_ULCAST_(1) << FPU_CSR_COND3_S)
#घोषणा FPU_CSR_COND4_S	28					/* $fcc4 */
#घोषणा FPU_CSR_COND4	(_ULCAST_(1) << FPU_CSR_COND4_S)
#घोषणा FPU_CSR_COND5_S	29					/* $fcc5 */
#घोषणा FPU_CSR_COND5	(_ULCAST_(1) << FPU_CSR_COND5_S)
#घोषणा FPU_CSR_COND6_S	30					/* $fcc6 */
#घोषणा FPU_CSR_COND6	(_ULCAST_(1) << FPU_CSR_COND6_S)
#घोषणा FPU_CSR_COND7_S	31					/* $fcc7 */
#घोषणा FPU_CSR_COND7	(_ULCAST_(1) << FPU_CSR_COND7_S)

/*
 * Bits 22:20 of the FPU Status Register will be पढ़ो as 0,
 * and should be written as zero.
 * MAC2008 was हटाओd in Release 5 so we still treat it as
 * reserved.
 */
#घोषणा FPU_CSR_RSVD	(_ULCAST_(7) << 20)

#घोषणा FPU_CSR_MAC2008	(_ULCAST_(1) << 20)
#घोषणा FPU_CSR_ABS2008	(_ULCAST_(1) << 19)
#घोषणा FPU_CSR_न_अंक2008	(_ULCAST_(1) << 18)

/*
 * X the exception cause indicator
 * E the exception enable
 * S the sticky/flag bit
*/
#घोषणा FPU_CSR_ALL_X	0x0003f000
#घोषणा FPU_CSR_UNI_X	0x00020000
#घोषणा FPU_CSR_INV_X	0x00010000
#घोषणा FPU_CSR_DIV_X	0x00008000
#घोषणा FPU_CSR_OVF_X	0x00004000
#घोषणा FPU_CSR_UDF_X	0x00002000
#घोषणा FPU_CSR_INE_X	0x00001000

#घोषणा FPU_CSR_ALL_E	0x00000f80
#घोषणा FPU_CSR_INV_E	0x00000800
#घोषणा FPU_CSR_DIV_E	0x00000400
#घोषणा FPU_CSR_OVF_E	0x00000200
#घोषणा FPU_CSR_UDF_E	0x00000100
#घोषणा FPU_CSR_INE_E	0x00000080

#घोषणा FPU_CSR_ALL_S	0x0000007c
#घोषणा FPU_CSR_INV_S	0x00000040
#घोषणा FPU_CSR_DIV_S	0x00000020
#घोषणा FPU_CSR_OVF_S	0x00000010
#घोषणा FPU_CSR_UDF_S	0x00000008
#घोषणा FPU_CSR_INE_S	0x00000004

/* Bits 0 and 1 of FPU Status Register specअगरy the rounding mode */
#घोषणा FPU_CSR_RM	0x00000003
#घोषणा FPU_CSR_RN	0x0	/* nearest */
#घोषणा FPU_CSR_RZ	0x1	/* towards zero */
#घोषणा FPU_CSR_RU	0x2	/* towards +Infinity */
#घोषणा FPU_CSR_RD	0x3	/* towards -Infinity */


#अगर_अघोषित __ASSEMBLY__

/*
 * Macros क्रम handling the ISA mode bit क्रम MIPS16 and microMIPS.
 */
#अगर defined(CONFIG_SYS_SUPPORTS_MIPS16) || \
    defined(CONFIG_SYS_SUPPORTS_MICROMIPS)
#घोषणा get_isa16_mode(x)		((x) & 0x1)
#घोषणा msk_isa16_mode(x)		((x) & ~0x1)
#घोषणा set_isa16_mode(x)		करो अणु (x) |= 0x1; पूर्ण जबतक(0)
#अन्यथा
#घोषणा get_isa16_mode(x)		0
#घोषणा msk_isa16_mode(x)		(x)
#घोषणा set_isa16_mode(x)		करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/*
 * microMIPS inकाष्ठाions can be 16-bit or 32-bit in length. This
 * वापसs a 1 अगर the inकाष्ठाion is 16-bit and a 0 अगर 32-bit.
 */
अटल अंतरभूत पूर्णांक mm_insn_16bit(u16 insn)
अणु
	u16 opcode = (insn >> 10) & 0x7;

	वापस (opcode >= 1 && opcode <= 3) ? 1 : 0;
पूर्ण

/*
 * Helper macros क्रम generating raw inकाष्ठाion encodings in अंतरभूत यंत्र.
 */
#अगर_घोषित CONFIG_CPU_MICROMIPS
#घोषणा _ASM_INSN16_IF_MM(_enc)			\
	".insn\n\t"				\
	".hword (" #_enc ")\n\t"
#घोषणा _ASM_INSN32_IF_MM(_enc)			\
	".insn\n\t"				\
	".hword ((" #_enc ") >> 16)\n\t"	\
	".hword ((" #_enc ") & 0xffff)\n\t"
#अन्यथा
#घोषणा _ASM_INSN_IF_MIPS(_enc)			\
	".insn\n\t"				\
	".word (" #_enc ")\n\t"
#पूर्ण_अगर

#अगर_अघोषित _ASM_INSN16_IF_MM
#घोषणा _ASM_INSN16_IF_MM(_enc)
#पूर्ण_अगर
#अगर_अघोषित _ASM_INSN32_IF_MM
#घोषणा _ASM_INSN32_IF_MM(_enc)
#पूर्ण_अगर
#अगर_अघोषित _ASM_INSN_IF_MIPS
#घोषणा _ASM_INSN_IF_MIPS(_enc)
#पूर्ण_अगर

/*
 * parse_r var, r - Helper assembler macro क्रम parsing रेजिस्टर names.
 *
 * This converts the रेजिस्टर name in $n क्रमm provided in \ल to the
 * corresponding रेजिस्टर number, which is asचिन्हित to the variable \खar. It is
 * needed to allow explicit encoding of inकाष्ठाions in अंतरभूत assembly where
 * रेजिस्टरs are chosen by the compiler in $n क्रमm, allowing us to aव्योम using
 * fixed रेजिस्टर numbers.
 *
 * It also allows newer inकाष्ठाions (not implemented by the assembler) to be
 * transparently implemented using assembler macros, instead of needing separate
 * हालs depending on toolchain support.
 *
 * Simple usage example:
 * __यंत्र__ __अस्थिर__("parse_r __rt, %0\n\t"
 *			".insn\n\t"
 *			"# di    %0\n\t"
 *			".word   (0x41606000 | (__rt << 16))"
 *			: "=r" (status);
 */

/* Match an inभागidual रेजिस्टर number and assign to \खar */
#घोषणा _IFC_REG(n)				\
	".ifc	\\r, $" #n "\n\t"		\
	"\\var	= " #n "\n\t"			\
	".endif\n\t"

__यंत्र__(".macro	parse_r var r\n\t"
	"\\var	= -1\n\t"
	_IFC_REG(0)  _IFC_REG(1)  _IFC_REG(2)  _IFC_REG(3)
	_IFC_REG(4)  _IFC_REG(5)  _IFC_REG(6)  _IFC_REG(7)
	_IFC_REG(8)  _IFC_REG(9)  _IFC_REG(10) _IFC_REG(11)
	_IFC_REG(12) _IFC_REG(13) _IFC_REG(14) _IFC_REG(15)
	_IFC_REG(16) _IFC_REG(17) _IFC_REG(18) _IFC_REG(19)
	_IFC_REG(20) _IFC_REG(21) _IFC_REG(22) _IFC_REG(23)
	_IFC_REG(24) _IFC_REG(25) _IFC_REG(26) _IFC_REG(27)
	_IFC_REG(28) _IFC_REG(29) _IFC_REG(30) _IFC_REG(31)
	".iflt	\\var\n\t"
	".error	\"Unable to parse register name \\r\"\n\t"
	".endif\n\t"
	".endm");

#अघोषित _IFC_REG

/*
 * C macros क्रम generating assembler macros क्रम common inकाष्ठाion क्रमmats.
 *
 * The names of the opeअक्रमs can be chosen by the caller, and the encoding of
 * रेजिस्टर opeअक्रम \<Rn> is asचिन्हित to __<Rn> where it can be accessed from
 * the ENC encodings.
 */

/* Inकाष्ठाions with no opeअक्रमs */
#घोषणा _ASM_MACRO_0(OP, ENC)						\
	__यंत्र__(".macro	" #OP "\n\t"					\
		ENC							\
		".endm")

/* Inकाष्ठाions with 1 रेजिस्टर opeअक्रम & 1 immediate opeअक्रम */
#घोषणा _ASM_MACRO_1R1I(OP, R1, I2, ENC)				\
	__यंत्र__(".macro	" #OP " " #R1 ", " #I2 "\n\t"			\
		"parse_r __" #R1 ", \\" #R1 "\न\ट"			\
		ENC							\
		".endm")

/* Inकाष्ठाions with 2 रेजिस्टर opeअक्रमs */
#घोषणा _ASM_MACRO_2R(OP, R1, R2, ENC)					\
	__यंत्र__(".macro	" #OP " " #R1 ", " #R2 "\n\t"			\
		"parse_r __" #R1 ", \\" #R1 "\न\ट"			\
		"parse_r __" #R2 ", \\" #R2 "\न\ट"			\
		ENC							\
		".endm")

/* Inकाष्ठाions with 3 रेजिस्टर opeअक्रमs */
#घोषणा _ASM_MACRO_3R(OP, R1, R2, R3, ENC)				\
	__यंत्र__(".macro	" #OP " " #R1 ", " #R2 ", " #R3 "\n\t"		\
		"parse_r __" #R1 ", \\" #R1 "\न\ट"			\
		"parse_r __" #R2 ", \\" #R2 "\न\ट"			\
		"parse_r __" #R3 ", \\" #R3 "\न\ट"			\
		ENC							\
		".endm")

/* Inकाष्ठाions with 2 रेजिस्टर opeअक्रमs and 1 optional select opeअक्रम */
#घोषणा _ASM_MACRO_2R_1S(OP, R1, R2, SEL3, ENC)				\
	__यंत्र__(".macro	" #OP " " #R1 ", " #R2 ", " #SEL3 " = 0\n\t"	\
		"parse_r __" #R1 ", \\" #R1 "\न\ट"			\
		"parse_r __" #R2 ", \\" #R2 "\न\ट"			\
		ENC							\
		".endm")

/*
 * TLB Invalidate Flush
 */
अटल अंतरभूत व्योम tlbinvf(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".set push\n\t"
		".set noreorder\n\t"
		"# tlbinvf\n\t"
		_ASM_INSN_IF_MIPS(0x42000004)
		_ASM_INSN32_IF_MM(0x0000537c)
		".set pop");
पूर्ण


/*
 * Functions to access the R10000 perक्रमmance counters.	 These are basically
 * mfc0 and mtc0 inकाष्ठाions from and to coprocessor रेजिस्टर with a 5-bit
 * perक्रमmance counter number encoded पूर्णांकo bits 1 ... 5 of the inकाष्ठाion.
 * Only perक्रमmance counters 0 to 1 actually exist, so क्रम a non-R10000 aware
 * disassembler these will look like an access to sel 0 or 1.
 */
#घोषणा पढ़ो_r10k_perf_cntr(counter)				\
(अणु								\
	अचिन्हित पूर्णांक __res;					\
	__यंत्र__ __अस्थिर__(					\
	"mfpc\t%0, %1"						\
	: "=r" (__res)						\
	: "i" (counter));					\
								\
	__res;							\
पूर्ण)

#घोषणा ग_लिखो_r10k_perf_cntr(counter,val)			\
करो अणु								\
	__यंत्र__ __अस्थिर__(					\
	"mtpc\t%0, %1"						\
	:							\
	: "r" (val), "i" (counter));				\
पूर्ण जबतक (0)

#घोषणा पढ़ो_r10k_perf_event(counter)				\
(अणु								\
	अचिन्हित पूर्णांक __res;					\
	__यंत्र__ __अस्थिर__(					\
	"mfps\t%0, %1"						\
	: "=r" (__res)						\
	: "i" (counter));					\
								\
	__res;							\
पूर्ण)

#घोषणा ग_लिखो_r10k_perf_cntl(counter,val)			\
करो अणु								\
	__यंत्र__ __अस्थिर__(					\
	"mtps\t%0, %1"						\
	:							\
	: "r" (val), "i" (counter));				\
पूर्ण जबतक (0)


/*
 * Macros to access the प्रणाली control coprocessor
 */

#घोषणा ___पढ़ो_32bit_c0_रेजिस्टर(source, sel, vol)			\
(अणु अचिन्हित पूर्णांक __res;							\
	अगर (sel == 0)							\
		__यंत्र__ vol(						\
			"mfc0\t%0, " #source "\n\t"			\
			: "=r" (__res));				\
	अन्यथा								\
		__यंत्र__ vol(						\
			".set\tpush\n\t"				\
			".set\tmips32\n\t"				\
			"mfc0\t%0, " #source ", " #sel "\n\t"		\
			".set\tpop\n\t"					\
			: "=r" (__res));				\
	__res;								\
पूर्ण)

#घोषणा ___पढ़ो_64bit_c0_रेजिस्टर(source, sel, vol)			\
(अणु अचिन्हित दीर्घ दीर्घ __res;						\
	अगर (माप(अचिन्हित दीर्घ) == 4)					\
		__res = __पढ़ो_64bit_c0_split(source, sel, vol);	\
	अन्यथा अगर (sel == 0)						\
		__यंत्र__ vol(						\
			".set\tpush\n\t"				\
			".set\tmips3\n\t"				\
			"dmfc0\t%0, " #source "\n\t"			\
			".set\tpop"					\
			: "=r" (__res));				\
	अन्यथा								\
		__यंत्र__ vol(						\
			".set\tpush\n\t"				\
			".set\tmips64\n\t"				\
			"dmfc0\t%0, " #source ", " #sel "\n\t"		\
			".set\tpop"					\
			: "=r" (__res));				\
	__res;								\
पूर्ण)

#घोषणा __पढ़ो_32bit_c0_रेजिस्टर(source, sel)				\
	___पढ़ो_32bit_c0_रेजिस्टर(source, sel, __अस्थिर__)

#घोषणा __पढ़ो_स्थिर_32bit_c0_रेजिस्टर(source, sel)			\
	___पढ़ो_32bit_c0_रेजिस्टर(source, sel,)

#घोषणा __पढ़ो_64bit_c0_रेजिस्टर(source, sel)				\
	___पढ़ो_64bit_c0_रेजिस्टर(source, sel, __अस्थिर__)

#घोषणा __पढ़ो_स्थिर_64bit_c0_रेजिस्टर(source, sel)			\
	___पढ़ो_64bit_c0_रेजिस्टर(source, sel,)

#घोषणा __ग_लिखो_32bit_c0_रेजिस्टर(रेजिस्टर, sel, value)			\
करो अणु									\
	अगर (sel == 0)							\
		__यंत्र__ __अस्थिर__(					\
			"mtc0\t%z0, " #रेजिस्टर "\n\t"			\
			: : "Jr" ((अचिन्हित पूर्णांक)(value)));		\
	अन्यथा								\
		__यंत्र__ __अस्थिर__(					\
			".set\tpush\n\t"				\
			".set\tmips32\n\t"				\
			"mtc0\t%z0, " #रेजिस्टर ", " #sel "\n\t"	\
			".set\tpop"					\
			: : "Jr" ((अचिन्हित पूर्णांक)(value)));		\
पूर्ण जबतक (0)

#घोषणा __ग_लिखो_64bit_c0_रेजिस्टर(रेजिस्टर, sel, value)			\
करो अणु									\
	अगर (माप(अचिन्हित दीर्घ) == 4)					\
		__ग_लिखो_64bit_c0_split(रेजिस्टर, sel, value);		\
	अन्यथा अगर (sel == 0)						\
		__यंत्र__ __अस्थिर__(					\
			".set\tpush\n\t"				\
			".set\tmips3\n\t"				\
			"dmtc0\t%z0, " #रेजिस्टर "\n\t"			\
			".set\tpop"					\
			: : "Jr" (value));				\
	अन्यथा								\
		__यंत्र__ __अस्थिर__(					\
			".set\tpush\n\t"				\
			".set\tmips64\n\t"				\
			"dmtc0\t%z0, " #रेजिस्टर ", " #sel "\n\t"	\
			".set\tpop"					\
			: : "Jr" (value));				\
पूर्ण जबतक (0)

#घोषणा __पढ़ो_uदीर्घ_c0_रेजिस्टर(reg, sel)				\
	((माप(अचिन्हित दीर्घ) == 4) ?					\
	(अचिन्हित दीर्घ) __पढ़ो_32bit_c0_रेजिस्टर(reg, sel) :		\
	(अचिन्हित दीर्घ) __पढ़ो_64bit_c0_रेजिस्टर(reg, sel))

#घोषणा __पढ़ो_स्थिर_uदीर्घ_c0_रेजिस्टर(reg, sel)			\
	((माप(अचिन्हित दीर्घ) == 4) ?					\
	(अचिन्हित दीर्घ) __पढ़ो_स्थिर_32bit_c0_रेजिस्टर(reg, sel) :	\
	(अचिन्हित दीर्घ) __पढ़ो_स्थिर_64bit_c0_रेजिस्टर(reg, sel))

#घोषणा __ग_लिखो_uदीर्घ_c0_रेजिस्टर(reg, sel, val)			\
करो अणु									\
	अगर (माप(अचिन्हित दीर्घ) == 4)					\
		__ग_लिखो_32bit_c0_रेजिस्टर(reg, sel, val);		\
	अन्यथा								\
		__ग_लिखो_64bit_c0_रेजिस्टर(reg, sel, val);		\
पूर्ण जबतक (0)

/*
 * On RM7000/RM9000 these are uses to access cop0 set 1 रेजिस्टरs
 */
#घोषणा __पढ़ो_32bit_c0_ctrl_रेजिस्टर(source)				\
(अणु अचिन्हित पूर्णांक __res;							\
	__यंत्र__ __अस्थिर__(						\
		"cfc0\t%0, " #source "\n\t"				\
		: "=r" (__res));					\
	__res;								\
पूर्ण)

#घोषणा __ग_लिखो_32bit_c0_ctrl_रेजिस्टर(रेजिस्टर, value)			\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
		"ctc0\t%z0, " #रेजिस्टर "\n\t"				\
		: : "Jr" ((अचिन्हित पूर्णांक)(value)));			\
पूर्ण जबतक (0)

/*
 * These versions are only needed क्रम प्रणालीs with more than 38 bits of
 * physical address space running the 32-bit kernel.  That's none aपंचांग :-)
 */
#घोषणा __पढ़ो_64bit_c0_split(source, sel, vol)				\
(अणु									\
	अचिन्हित दीर्घ दीर्घ __val;					\
	अचिन्हित दीर्घ __flags;						\
									\
	local_irq_save(__flags);					\
	अगर (sel == 0)							\
		__यंत्र__ vol(						\
			".set\tpush\n\t"				\
			".set\tmips64\n\t"				\
			"dmfc0\t%L0, " #source "\n\t"			\
			"dsra\t%M0, %L0, 32\n\t"			\
			"sll\t%L0, %L0, 0\n\t"				\
			".set\tpop"					\
			: "=r" (__val));				\
	अन्यथा								\
		__यंत्र__ vol(						\
			".set\tpush\n\t"				\
			".set\tmips64\n\t"				\
			"dmfc0\t%L0, " #source ", " #sel "\n\t"		\
			"dsra\t%M0, %L0, 32\n\t"			\
			"sll\t%L0, %L0, 0\n\t"				\
			".set\tpop"					\
			: "=r" (__val));				\
	local_irq_restore(__flags);					\
									\
	__val;								\
पूर्ण)

#घोषणा __ग_लिखो_64bit_c0_split(source, sel, val)			\
करो अणु									\
	अचिन्हित दीर्घ दीर्घ __पंचांगp = (val);				\
	अचिन्हित दीर्घ __flags;						\
									\
	local_irq_save(__flags);					\
	अगर (MIPS_ISA_REV >= 2)						\
		__यंत्र__ __अस्थिर__(					\
			".set\tpush\n\t"				\
			".set\t" MIPS_ISA_LEVEL "\n\t"			\
			"dins\t%L0, %M0, 32, 32\n\t"			\
			"dmtc0\t%L0, " #source ", " #sel "\n\t"		\
			".set\tpop"					\
			: "+r" (__पंचांगp));				\
	अन्यथा अगर (sel == 0)						\
		__यंत्र__ __अस्थिर__(					\
			".set\tpush\n\t"				\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc0\t%L0, " #source "\n\t"			\
			".set\tpop"					\
			: "+r" (__पंचांगp));				\
	अन्यथा								\
		__यंत्र__ __अस्थिर__(					\
			".set\tpush\n\t"				\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc0\t%L0, " #source ", " #sel "\n\t"		\
			".set\tpop"					\
			: "+r" (__पंचांगp));				\
	local_irq_restore(__flags);					\
पूर्ण जबतक (0)

#अगर_अघोषित TOOLCHAIN_SUPPORTS_XPA
_ASM_MACRO_2R_1S(mfhc0, rt, rs, sel,
	_ASM_INSN_IF_MIPS(0x40400000 | __rt << 16 | __rs << 11 | \\sel)
	_ASM_INSN32_IF_MM(0x000000f4 | __rt << 21 | __rs << 16 | \\sel << 11));
_ASM_MACRO_2R_1S(mthc0, rt, rd, sel,
	_ASM_INSN_IF_MIPS(0x40c00000 | __rt << 16 | __rd << 11 | \\sel)
	_ASM_INSN32_IF_MM(0x000002f4 | __rt << 21 | __rd << 16 | \\sel << 11));
#घोषणा _ASM_SET_XPA ""
#अन्यथा	/* !TOOLCHAIN_SUPPORTS_XPA */
#घोषणा _ASM_SET_XPA ".set\txpa\n\t"
#पूर्ण_अगर

#घोषणा __पढ़ोx_32bit_c0_रेजिस्टर(source, sel)				\
(अणु									\
	अचिन्हित पूर्णांक __res;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	mips32r2				\n"	\
	_ASM_SET_XPA							\
	"	mfhc0	%0, " #source ", %1			\n"	\
	"	.set	pop					\n"	\
	: "=r" (__res)							\
	: "i" (sel));							\
	__res;								\
पूर्ण)

#घोषणा __ग_लिखोx_32bit_c0_रेजिस्टर(रेजिस्टर, sel, value)		\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	mips32r2				\n"	\
	_ASM_SET_XPA							\
	"	mthc0	%z0, " #रेजिस्टर ", %1			\n"	\
	"	.set	pop					\n"	\
	:								\
	: "Jr" (value), "i" (sel));					\
पूर्ण जबतक (0)

#घोषणा पढ़ो_c0_index()		__पढ़ो_32bit_c0_रेजिस्टर($0, 0)
#घोषणा ग_लिखो_c0_index(val)	__ग_लिखो_32bit_c0_रेजिस्टर($0, 0, val)

#घोषणा पढ़ो_c0_अक्रमom()	__पढ़ो_32bit_c0_रेजिस्टर($1, 0)
#घोषणा ग_लिखो_c0_अक्रमom(val)	__ग_लिखो_32bit_c0_रेजिस्टर($1, 0, val)

#घोषणा पढ़ो_c0_entrylo0()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($2, 0)
#घोषणा ग_लिखो_c0_entrylo0(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($2, 0, val)

#घोषणा पढ़ोx_c0_entrylo0()	__पढ़ोx_32bit_c0_रेजिस्टर($2, 0)
#घोषणा ग_लिखोx_c0_entrylo0(val)	__ग_लिखोx_32bit_c0_रेजिस्टर($2, 0, val)

#घोषणा पढ़ो_c0_entrylo1()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($3, 0)
#घोषणा ग_लिखो_c0_entrylo1(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($3, 0, val)

#घोषणा पढ़ोx_c0_entrylo1()	__पढ़ोx_32bit_c0_रेजिस्टर($3, 0)
#घोषणा ग_लिखोx_c0_entrylo1(val)	__ग_लिखोx_32bit_c0_रेजिस्टर($3, 0, val)

#घोषणा पढ़ो_c0_conf()		__पढ़ो_32bit_c0_रेजिस्टर($3, 0)
#घोषणा ग_लिखो_c0_conf(val)	__ग_लिखो_32bit_c0_रेजिस्टर($3, 0, val)

#घोषणा पढ़ो_c0_globalnumber()	__पढ़ो_32bit_c0_रेजिस्टर($3, 1)

#घोषणा पढ़ो_c0_context()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($4, 0)
#घोषणा ग_लिखो_c0_context(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($4, 0, val)

#घोषणा पढ़ो_c0_contextconfig()		__पढ़ो_32bit_c0_रेजिस्टर($4, 1)
#घोषणा ग_लिखो_c0_contextconfig(val)	__ग_लिखो_32bit_c0_रेजिस्टर($4, 1, val)

#घोषणा पढ़ो_c0_userlocal()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($4, 2)
#घोषणा ग_लिखो_c0_userlocal(val) __ग_लिखो_uदीर्घ_c0_रेजिस्टर($4, 2, val)

#घोषणा पढ़ो_c0_xcontextconfig()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($4, 3)
#घोषणा ग_लिखो_c0_xcontextconfig(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($4, 3, val)

#घोषणा पढ़ो_c0_memorymapid()		__पढ़ो_32bit_c0_रेजिस्टर($4, 5)
#घोषणा ग_लिखो_c0_memorymapid(val)	__ग_लिखो_32bit_c0_रेजिस्टर($4, 5, val)

#घोषणा पढ़ो_c0_pagemask()	__पढ़ो_32bit_c0_रेजिस्टर($5, 0)
#घोषणा ग_लिखो_c0_pagemask(val)	__ग_लिखो_32bit_c0_रेजिस्टर($5, 0, val)

#घोषणा पढ़ो_c0_pagegrain()	__पढ़ो_32bit_c0_रेजिस्टर($5, 1)
#घोषणा ग_लिखो_c0_pagegrain(val) __ग_लिखो_32bit_c0_रेजिस्टर($5, 1, val)

#घोषणा पढ़ो_c0_wired()		__पढ़ो_32bit_c0_रेजिस्टर($6, 0)
#घोषणा ग_लिखो_c0_wired(val)	__ग_लिखो_32bit_c0_रेजिस्टर($6, 0, val)

#घोषणा पढ़ो_c0_info()		__पढ़ो_32bit_c0_रेजिस्टर($7, 0)

#घोषणा पढ़ो_c0_cache()		__पढ़ो_32bit_c0_रेजिस्टर($7, 0) /* TX39xx */
#घोषणा ग_लिखो_c0_cache(val)	__ग_लिखो_32bit_c0_रेजिस्टर($7, 0, val)

#घोषणा पढ़ो_c0_badvaddr()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($8, 0)
#घोषणा ग_लिखो_c0_badvaddr(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($8, 0, val)

#घोषणा पढ़ो_c0_badinstr()	__पढ़ो_32bit_c0_रेजिस्टर($8, 1)
#घोषणा पढ़ो_c0_badinstrp()	__पढ़ो_32bit_c0_रेजिस्टर($8, 2)

#घोषणा पढ़ो_c0_count()		__पढ़ो_32bit_c0_रेजिस्टर($9, 0)
#घोषणा ग_लिखो_c0_count(val)	__ग_लिखो_32bit_c0_रेजिस्टर($9, 0, val)

#घोषणा पढ़ो_c0_entryhi()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($10, 0)
#घोषणा ग_लिखो_c0_entryhi(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($10, 0, val)

#घोषणा पढ़ो_c0_guestctl1()	__पढ़ो_32bit_c0_रेजिस्टर($10, 4)
#घोषणा ग_लिखो_c0_guestctl1(val)	__ग_लिखो_32bit_c0_रेजिस्टर($10, 4, val)

#घोषणा पढ़ो_c0_guestctl2()	__पढ़ो_32bit_c0_रेजिस्टर($10, 5)
#घोषणा ग_लिखो_c0_guestctl2(val)	__ग_लिखो_32bit_c0_रेजिस्टर($10, 5, val)

#घोषणा पढ़ो_c0_guestctl3()	__पढ़ो_32bit_c0_रेजिस्टर($10, 6)
#घोषणा ग_लिखो_c0_guestctl3(val)	__ग_लिखो_32bit_c0_रेजिस्टर($10, 6, val)

#घोषणा पढ़ो_c0_compare()	__पढ़ो_32bit_c0_रेजिस्टर($11, 0)
#घोषणा ग_लिखो_c0_compare(val)	__ग_लिखो_32bit_c0_रेजिस्टर($11, 0, val)

#घोषणा पढ़ो_c0_guestctl0ext()	__पढ़ो_32bit_c0_रेजिस्टर($11, 4)
#घोषणा ग_लिखो_c0_guestctl0ext(val) __ग_लिखो_32bit_c0_रेजिस्टर($11, 4, val)

#घोषणा पढ़ो_c0_status()	__पढ़ो_32bit_c0_रेजिस्टर($12, 0)

#घोषणा ग_लिखो_c0_status(val)	__ग_लिखो_32bit_c0_रेजिस्टर($12, 0, val)

#घोषणा पढ़ो_c0_guestctl0()	__पढ़ो_32bit_c0_रेजिस्टर($12, 6)
#घोषणा ग_लिखो_c0_guestctl0(val)	__ग_लिखो_32bit_c0_रेजिस्टर($12, 6, val)

#घोषणा पढ़ो_c0_gtoffset()	__पढ़ो_32bit_c0_रेजिस्टर($12, 7)
#घोषणा ग_लिखो_c0_gtoffset(val)	__ग_लिखो_32bit_c0_रेजिस्टर($12, 7, val)

#घोषणा पढ़ो_c0_cause()		__पढ़ो_32bit_c0_रेजिस्टर($13, 0)
#घोषणा ग_लिखो_c0_cause(val)	__ग_लिखो_32bit_c0_रेजिस्टर($13, 0, val)

#घोषणा पढ़ो_c0_epc()		__पढ़ो_uदीर्घ_c0_रेजिस्टर($14, 0)
#घोषणा ग_लिखो_c0_epc(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($14, 0, val)

#घोषणा पढ़ो_c0_prid()		__पढ़ो_स्थिर_32bit_c0_रेजिस्टर($15, 0)

#घोषणा पढ़ो_c0_cmgcrbase()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($15, 3)

#घोषणा पढ़ो_c0_config()	__पढ़ो_32bit_c0_रेजिस्टर($16, 0)
#घोषणा पढ़ो_c0_config1()	__पढ़ो_32bit_c0_रेजिस्टर($16, 1)
#घोषणा पढ़ो_c0_config2()	__पढ़ो_32bit_c0_रेजिस्टर($16, 2)
#घोषणा पढ़ो_c0_config3()	__पढ़ो_32bit_c0_रेजिस्टर($16, 3)
#घोषणा पढ़ो_c0_config4()	__पढ़ो_32bit_c0_रेजिस्टर($16, 4)
#घोषणा पढ़ो_c0_config5()	__पढ़ो_32bit_c0_रेजिस्टर($16, 5)
#घोषणा पढ़ो_c0_config6()	__पढ़ो_32bit_c0_रेजिस्टर($16, 6)
#घोषणा पढ़ो_c0_config7()	__पढ़ो_32bit_c0_रेजिस्टर($16, 7)
#घोषणा ग_लिखो_c0_config(val)	__ग_लिखो_32bit_c0_रेजिस्टर($16, 0, val)
#घोषणा ग_लिखो_c0_config1(val)	__ग_लिखो_32bit_c0_रेजिस्टर($16, 1, val)
#घोषणा ग_लिखो_c0_config2(val)	__ग_लिखो_32bit_c0_रेजिस्टर($16, 2, val)
#घोषणा ग_लिखो_c0_config3(val)	__ग_लिखो_32bit_c0_रेजिस्टर($16, 3, val)
#घोषणा ग_लिखो_c0_config4(val)	__ग_लिखो_32bit_c0_रेजिस्टर($16, 4, val)
#घोषणा ग_लिखो_c0_config5(val)	__ग_लिखो_32bit_c0_रेजिस्टर($16, 5, val)
#घोषणा ग_लिखो_c0_config6(val)	__ग_लिखो_32bit_c0_रेजिस्टर($16, 6, val)
#घोषणा ग_लिखो_c0_config7(val)	__ग_लिखो_32bit_c0_रेजिस्टर($16, 7, val)

#घोषणा पढ़ो_c0_lladdr()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($17, 0)
#घोषणा ग_लिखो_c0_lladdr(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($17, 0, val)
#घोषणा पढ़ो_c0_maar()		__पढ़ो_uदीर्घ_c0_रेजिस्टर($17, 1)
#घोषणा ग_लिखो_c0_maar(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($17, 1, val)
#घोषणा पढ़ोx_c0_maar()		__पढ़ोx_32bit_c0_रेजिस्टर($17, 1)
#घोषणा ग_लिखोx_c0_maar(val)	__ग_लिखोx_32bit_c0_रेजिस्टर($17, 1, val)
#घोषणा पढ़ो_c0_maari()		__पढ़ो_32bit_c0_रेजिस्टर($17, 2)
#घोषणा ग_लिखो_c0_maari(val)	__ग_लिखो_32bit_c0_रेजिस्टर($17, 2, val)

/*
 * The WatchLo रेजिस्टर.  There may be up to 8 of them.
 */
#घोषणा पढ़ो_c0_watchlo0()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($18, 0)
#घोषणा पढ़ो_c0_watchlo1()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($18, 1)
#घोषणा पढ़ो_c0_watchlo2()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($18, 2)
#घोषणा पढ़ो_c0_watchlo3()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($18, 3)
#घोषणा पढ़ो_c0_watchlo4()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($18, 4)
#घोषणा पढ़ो_c0_watchlo5()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($18, 5)
#घोषणा पढ़ो_c0_watchlo6()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($18, 6)
#घोषणा पढ़ो_c0_watchlo7()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($18, 7)
#घोषणा ग_लिखो_c0_watchlo0(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($18, 0, val)
#घोषणा ग_लिखो_c0_watchlo1(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($18, 1, val)
#घोषणा ग_लिखो_c0_watchlo2(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($18, 2, val)
#घोषणा ग_लिखो_c0_watchlo3(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($18, 3, val)
#घोषणा ग_लिखो_c0_watchlo4(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($18, 4, val)
#घोषणा ग_लिखो_c0_watchlo5(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($18, 5, val)
#घोषणा ग_लिखो_c0_watchlo6(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($18, 6, val)
#घोषणा ग_लिखो_c0_watchlo7(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($18, 7, val)

/*
 * The WatchHi रेजिस्टर.  There may be up to 8 of them.
 */
#घोषणा पढ़ो_c0_watchhi0()	__पढ़ो_32bit_c0_रेजिस्टर($19, 0)
#घोषणा पढ़ो_c0_watchhi1()	__पढ़ो_32bit_c0_रेजिस्टर($19, 1)
#घोषणा पढ़ो_c0_watchhi2()	__पढ़ो_32bit_c0_रेजिस्टर($19, 2)
#घोषणा पढ़ो_c0_watchhi3()	__पढ़ो_32bit_c0_रेजिस्टर($19, 3)
#घोषणा पढ़ो_c0_watchhi4()	__पढ़ो_32bit_c0_रेजिस्टर($19, 4)
#घोषणा पढ़ो_c0_watchhi5()	__पढ़ो_32bit_c0_रेजिस्टर($19, 5)
#घोषणा पढ़ो_c0_watchhi6()	__पढ़ो_32bit_c0_रेजिस्टर($19, 6)
#घोषणा पढ़ो_c0_watchhi7()	__पढ़ो_32bit_c0_रेजिस्टर($19, 7)

#घोषणा ग_लिखो_c0_watchhi0(val)	__ग_लिखो_32bit_c0_रेजिस्टर($19, 0, val)
#घोषणा ग_लिखो_c0_watchhi1(val)	__ग_लिखो_32bit_c0_रेजिस्टर($19, 1, val)
#घोषणा ग_लिखो_c0_watchhi2(val)	__ग_लिखो_32bit_c0_रेजिस्टर($19, 2, val)
#घोषणा ग_लिखो_c0_watchhi3(val)	__ग_लिखो_32bit_c0_रेजिस्टर($19, 3, val)
#घोषणा ग_लिखो_c0_watchhi4(val)	__ग_लिखो_32bit_c0_रेजिस्टर($19, 4, val)
#घोषणा ग_लिखो_c0_watchhi5(val)	__ग_लिखो_32bit_c0_रेजिस्टर($19, 5, val)
#घोषणा ग_लिखो_c0_watchhi6(val)	__ग_लिखो_32bit_c0_रेजिस्टर($19, 6, val)
#घोषणा ग_लिखो_c0_watchhi7(val)	__ग_लिखो_32bit_c0_रेजिस्टर($19, 7, val)

#घोषणा पढ़ो_c0_xcontext()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($20, 0)
#घोषणा ग_लिखो_c0_xcontext(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($20, 0, val)

#घोषणा पढ़ो_c0_पूर्णांकcontrol()	__पढ़ो_32bit_c0_ctrl_रेजिस्टर($20)
#घोषणा ग_लिखो_c0_पूर्णांकcontrol(val) __ग_लिखो_32bit_c0_ctrl_रेजिस्टर($20, val)

#घोषणा पढ़ो_c0_framemask()	__पढ़ो_32bit_c0_रेजिस्टर($21, 0)
#घोषणा ग_लिखो_c0_framemask(val) __ग_लिखो_32bit_c0_रेजिस्टर($21, 0, val)

#घोषणा पढ़ो_c0_diag()		__पढ़ो_32bit_c0_रेजिस्टर($22, 0)
#घोषणा ग_लिखो_c0_diag(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 0, val)

/* R10K CP0 Branch Diagnostic रेजिस्टर is 64bits wide */
#घोषणा पढ़ो_c0_r10k_diag()	__पढ़ो_64bit_c0_रेजिस्टर($22, 0)
#घोषणा ग_लिखो_c0_r10k_diag(val)	__ग_लिखो_64bit_c0_रेजिस्टर($22, 0, val)

#घोषणा पढ़ो_c0_diag1()		__पढ़ो_32bit_c0_रेजिस्टर($22, 1)
#घोषणा ग_लिखो_c0_diag1(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 1, val)

#घोषणा पढ़ो_c0_diag2()		__पढ़ो_32bit_c0_रेजिस्टर($22, 2)
#घोषणा ग_लिखो_c0_diag2(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 2, val)

#घोषणा पढ़ो_c0_diag3()		__पढ़ो_32bit_c0_रेजिस्टर($22, 3)
#घोषणा ग_लिखो_c0_diag3(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 3, val)

#घोषणा पढ़ो_c0_diag4()		__पढ़ो_32bit_c0_रेजिस्टर($22, 4)
#घोषणा ग_लिखो_c0_diag4(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 4, val)

#घोषणा पढ़ो_c0_diag5()		__पढ़ो_32bit_c0_रेजिस्टर($22, 5)
#घोषणा ग_लिखो_c0_diag5(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 5, val)

#घोषणा पढ़ो_c0_debug()		__पढ़ो_32bit_c0_रेजिस्टर($23, 0)
#घोषणा ग_लिखो_c0_debug(val)	__ग_लिखो_32bit_c0_रेजिस्टर($23, 0, val)

#घोषणा पढ़ो_c0_depc()		__पढ़ो_uदीर्घ_c0_रेजिस्टर($24, 0)
#घोषणा ग_लिखो_c0_depc(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($24, 0, val)

/*
 * MIPS32 / MIPS64 perक्रमmance counters
 */
#घोषणा पढ़ो_c0_perfctrl0()	__पढ़ो_32bit_c0_रेजिस्टर($25, 0)
#घोषणा ग_लिखो_c0_perfctrl0(val) __ग_लिखो_32bit_c0_रेजिस्टर($25, 0, val)
#घोषणा पढ़ो_c0_perfcntr0()	__पढ़ो_32bit_c0_रेजिस्टर($25, 1)
#घोषणा ग_लिखो_c0_perfcntr0(val) __ग_लिखो_32bit_c0_रेजिस्टर($25, 1, val)
#घोषणा पढ़ो_c0_perfcntr0_64()	__पढ़ो_64bit_c0_रेजिस्टर($25, 1)
#घोषणा ग_लिखो_c0_perfcntr0_64(val) __ग_लिखो_64bit_c0_रेजिस्टर($25, 1, val)
#घोषणा पढ़ो_c0_perfctrl1()	__पढ़ो_32bit_c0_रेजिस्टर($25, 2)
#घोषणा ग_लिखो_c0_perfctrl1(val) __ग_लिखो_32bit_c0_रेजिस्टर($25, 2, val)
#घोषणा पढ़ो_c0_perfcntr1()	__पढ़ो_32bit_c0_रेजिस्टर($25, 3)
#घोषणा ग_लिखो_c0_perfcntr1(val) __ग_लिखो_32bit_c0_रेजिस्टर($25, 3, val)
#घोषणा पढ़ो_c0_perfcntr1_64()	__पढ़ो_64bit_c0_रेजिस्टर($25, 3)
#घोषणा ग_लिखो_c0_perfcntr1_64(val) __ग_लिखो_64bit_c0_रेजिस्टर($25, 3, val)
#घोषणा पढ़ो_c0_perfctrl2()	__पढ़ो_32bit_c0_रेजिस्टर($25, 4)
#घोषणा ग_लिखो_c0_perfctrl2(val) __ग_लिखो_32bit_c0_रेजिस्टर($25, 4, val)
#घोषणा पढ़ो_c0_perfcntr2()	__पढ़ो_32bit_c0_रेजिस्टर($25, 5)
#घोषणा ग_लिखो_c0_perfcntr2(val) __ग_लिखो_32bit_c0_रेजिस्टर($25, 5, val)
#घोषणा पढ़ो_c0_perfcntr2_64()	__पढ़ो_64bit_c0_रेजिस्टर($25, 5)
#घोषणा ग_लिखो_c0_perfcntr2_64(val) __ग_लिखो_64bit_c0_रेजिस्टर($25, 5, val)
#घोषणा पढ़ो_c0_perfctrl3()	__पढ़ो_32bit_c0_रेजिस्टर($25, 6)
#घोषणा ग_लिखो_c0_perfctrl3(val) __ग_लिखो_32bit_c0_रेजिस्टर($25, 6, val)
#घोषणा पढ़ो_c0_perfcntr3()	__पढ़ो_32bit_c0_रेजिस्टर($25, 7)
#घोषणा ग_लिखो_c0_perfcntr3(val) __ग_लिखो_32bit_c0_रेजिस्टर($25, 7, val)
#घोषणा पढ़ो_c0_perfcntr3_64()	__पढ़ो_64bit_c0_रेजिस्टर($25, 7)
#घोषणा ग_लिखो_c0_perfcntr3_64(val) __ग_लिखो_64bit_c0_रेजिस्टर($25, 7, val)

#घोषणा पढ़ो_c0_ecc()		__पढ़ो_32bit_c0_रेजिस्टर($26, 0)
#घोषणा ग_लिखो_c0_ecc(val)	__ग_लिखो_32bit_c0_रेजिस्टर($26, 0, val)

#घोषणा पढ़ो_c0_derraddr0()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($26, 1)
#घोषणा ग_लिखो_c0_derraddr0(val) __ग_लिखो_uदीर्घ_c0_रेजिस्टर($26, 1, val)

#घोषणा पढ़ो_c0_cacheerr()	__पढ़ो_32bit_c0_रेजिस्टर($27, 0)

#घोषणा पढ़ो_c0_derraddr1()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($27, 1)
#घोषणा ग_लिखो_c0_derraddr1(val) __ग_लिखो_uदीर्घ_c0_रेजिस्टर($27, 1, val)

#घोषणा पढ़ो_c0_taglo()		__पढ़ो_32bit_c0_रेजिस्टर($28, 0)
#घोषणा ग_लिखो_c0_taglo(val)	__ग_लिखो_32bit_c0_रेजिस्टर($28, 0, val)

#घोषणा पढ़ो_c0_dtaglo()	__पढ़ो_32bit_c0_रेजिस्टर($28, 2)
#घोषणा ग_लिखो_c0_dtaglo(val)	__ग_लिखो_32bit_c0_रेजिस्टर($28, 2, val)

#घोषणा पढ़ो_c0_ddatalo()	__पढ़ो_32bit_c0_रेजिस्टर($28, 3)
#घोषणा ग_लिखो_c0_ddatalo(val)	__ग_लिखो_32bit_c0_रेजिस्टर($28, 3, val)

#घोषणा पढ़ो_c0_staglo()	__पढ़ो_32bit_c0_रेजिस्टर($28, 4)
#घोषणा ग_लिखो_c0_staglo(val)	__ग_लिखो_32bit_c0_रेजिस्टर($28, 4, val)

#घोषणा पढ़ो_c0_taghi()		__पढ़ो_32bit_c0_रेजिस्टर($29, 0)
#घोषणा ग_लिखो_c0_taghi(val)	__ग_लिखो_32bit_c0_रेजिस्टर($29, 0, val)

#घोषणा पढ़ो_c0_errorepc()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($30, 0)
#घोषणा ग_लिखो_c0_errorepc(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($30, 0, val)

/* MIPSR2 */
#घोषणा पढ़ो_c0_hwrena()	__पढ़ो_32bit_c0_रेजिस्टर($7, 0)
#घोषणा ग_लिखो_c0_hwrena(val)	__ग_लिखो_32bit_c0_रेजिस्टर($7, 0, val)

#घोषणा पढ़ो_c0_पूर्णांकctl()	__पढ़ो_32bit_c0_रेजिस्टर($12, 1)
#घोषणा ग_लिखो_c0_पूर्णांकctl(val)	__ग_लिखो_32bit_c0_रेजिस्टर($12, 1, val)

#घोषणा पढ़ो_c0_srsctl()	__पढ़ो_32bit_c0_रेजिस्टर($12, 2)
#घोषणा ग_लिखो_c0_srsctl(val)	__ग_लिखो_32bit_c0_रेजिस्टर($12, 2, val)

#घोषणा पढ़ो_c0_srsmap()	__पढ़ो_32bit_c0_रेजिस्टर($12, 3)
#घोषणा ग_लिखो_c0_srsmap(val)	__ग_लिखो_32bit_c0_रेजिस्टर($12, 3, val)

#घोषणा पढ़ो_c0_ebase()		__पढ़ो_32bit_c0_रेजिस्टर($15, 1)
#घोषणा ग_लिखो_c0_ebase(val)	__ग_लिखो_32bit_c0_रेजिस्टर($15, 1, val)

#घोषणा पढ़ो_c0_ebase_64()	__पढ़ो_64bit_c0_रेजिस्टर($15, 1)
#घोषणा ग_लिखो_c0_ebase_64(val)	__ग_लिखो_64bit_c0_रेजिस्टर($15, 1, val)

#घोषणा पढ़ो_c0_cdmmbase()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($15, 2)
#घोषणा ग_लिखो_c0_cdmmbase(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($15, 2, val)

/* MIPSR3 */
#घोषणा पढ़ो_c0_segctl0()	__पढ़ो_32bit_c0_रेजिस्टर($5, 2)
#घोषणा ग_लिखो_c0_segctl0(val)	__ग_लिखो_32bit_c0_रेजिस्टर($5, 2, val)

#घोषणा पढ़ो_c0_segctl1()	__पढ़ो_32bit_c0_रेजिस्टर($5, 3)
#घोषणा ग_लिखो_c0_segctl1(val)	__ग_लिखो_32bit_c0_रेजिस्टर($5, 3, val)

#घोषणा पढ़ो_c0_segctl2()	__पढ़ो_32bit_c0_रेजिस्टर($5, 4)
#घोषणा ग_लिखो_c0_segctl2(val)	__ग_लिखो_32bit_c0_रेजिस्टर($5, 4, val)

/* Hardware Page Table Walker */
#घोषणा पढ़ो_c0_pwbase()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($5, 5)
#घोषणा ग_लिखो_c0_pwbase(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($5, 5, val)

#घोषणा पढ़ो_c0_pwfield()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($5, 6)
#घोषणा ग_लिखो_c0_pwfield(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($5, 6, val)

#घोषणा पढ़ो_c0_pwsize()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($5, 7)
#घोषणा ग_लिखो_c0_pwsize(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($5, 7, val)

#घोषणा पढ़ो_c0_pwctl()		__पढ़ो_32bit_c0_रेजिस्टर($6, 6)
#घोषणा ग_लिखो_c0_pwctl(val)	__ग_लिखो_32bit_c0_रेजिस्टर($6, 6, val)

#घोषणा पढ़ो_c0_pgd()		__पढ़ो_64bit_c0_रेजिस्टर($9, 7)
#घोषणा ग_लिखो_c0_pgd(val)	__ग_लिखो_64bit_c0_रेजिस्टर($9, 7, val)

#घोषणा पढ़ो_c0_kpgd()		__पढ़ो_64bit_c0_रेजिस्टर($31, 7)
#घोषणा ग_लिखो_c0_kpgd(val)	__ग_लिखो_64bit_c0_रेजिस्टर($31, 7, val)

/* Cavium OCTEON (cnMIPS) */
#घोषणा पढ़ो_c0_cvmcount()	__पढ़ो_uदीर्घ_c0_रेजिस्टर($9, 6)
#घोषणा ग_लिखो_c0_cvmcount(val)	__ग_लिखो_uदीर्घ_c0_रेजिस्टर($9, 6, val)

#घोषणा पढ़ो_c0_cvmctl()	__पढ़ो_64bit_c0_रेजिस्टर($9, 7)
#घोषणा ग_लिखो_c0_cvmctl(val)	__ग_लिखो_64bit_c0_रेजिस्टर($9, 7, val)

#घोषणा पढ़ो_c0_cvmmemctl()	__पढ़ो_64bit_c0_रेजिस्टर($11, 7)
#घोषणा ग_लिखो_c0_cvmmemctl(val) __ग_लिखो_64bit_c0_रेजिस्टर($11, 7, val)

#घोषणा पढ़ो_c0_cvmmemctl2()	__पढ़ो_64bit_c0_रेजिस्टर($16, 6)
#घोषणा ग_लिखो_c0_cvmmemctl2(val) __ग_लिखो_64bit_c0_रेजिस्टर($16, 6, val)

#घोषणा पढ़ो_c0_cvmvmconfig()	__पढ़ो_64bit_c0_रेजिस्टर($16, 7)
#घोषणा ग_लिखो_c0_cvmvmconfig(val) __ग_लिखो_64bit_c0_रेजिस्टर($16, 7, val)

/*
 * The cacheerr रेजिस्टरs are not standardized.	 On OCTEON, they are
 * 64 bits wide.
 */
#घोषणा पढ़ो_octeon_c0_icacheerr()	__पढ़ो_64bit_c0_रेजिस्टर($27, 0)
#घोषणा ग_लिखो_octeon_c0_icacheerr(val)	__ग_लिखो_64bit_c0_रेजिस्टर($27, 0, val)

#घोषणा पढ़ो_octeon_c0_dcacheerr()	__पढ़ो_64bit_c0_रेजिस्टर($27, 1)
#घोषणा ग_लिखो_octeon_c0_dcacheerr(val)	__ग_लिखो_64bit_c0_रेजिस्टर($27, 1, val)

/* BMIPS3300 */
#घोषणा पढ़ो_c0_brcm_config_0()		__पढ़ो_32bit_c0_रेजिस्टर($22, 0)
#घोषणा ग_लिखो_c0_brcm_config_0(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 0, val)

#घोषणा पढ़ो_c0_brcm_bus_pll()		__पढ़ो_32bit_c0_रेजिस्टर($22, 4)
#घोषणा ग_लिखो_c0_brcm_bus_pll(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 4, val)

#घोषणा पढ़ो_c0_brcm_reset()		__पढ़ो_32bit_c0_रेजिस्टर($22, 5)
#घोषणा ग_लिखो_c0_brcm_reset(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 5, val)

/* BMIPS43xx */
#घोषणा पढ़ो_c0_brcm_cmt_पूर्णांकr()		__पढ़ो_32bit_c0_रेजिस्टर($22, 1)
#घोषणा ग_लिखो_c0_brcm_cmt_पूर्णांकr(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 1, val)

#घोषणा पढ़ो_c0_brcm_cmt_ctrl()		__पढ़ो_32bit_c0_रेजिस्टर($22, 2)
#घोषणा ग_लिखो_c0_brcm_cmt_ctrl(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 2, val)

#घोषणा पढ़ो_c0_brcm_cmt_local()	__पढ़ो_32bit_c0_रेजिस्टर($22, 3)
#घोषणा ग_लिखो_c0_brcm_cmt_local(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 3, val)

#घोषणा पढ़ो_c0_brcm_config_1()		__पढ़ो_32bit_c0_रेजिस्टर($22, 5)
#घोषणा ग_लिखो_c0_brcm_config_1(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 5, val)

#घोषणा पढ़ो_c0_brcm_cbr()		__पढ़ो_32bit_c0_रेजिस्टर($22, 6)
#घोषणा ग_लिखो_c0_brcm_cbr(val)		__ग_लिखो_32bit_c0_रेजिस्टर($22, 6, val)

/* BMIPS5000 */
#घोषणा पढ़ो_c0_brcm_config()		__पढ़ो_32bit_c0_रेजिस्टर($22, 0)
#घोषणा ग_लिखो_c0_brcm_config(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 0, val)

#घोषणा पढ़ो_c0_brcm_mode()		__पढ़ो_32bit_c0_रेजिस्टर($22, 1)
#घोषणा ग_लिखो_c0_brcm_mode(val)		__ग_लिखो_32bit_c0_रेजिस्टर($22, 1, val)

#घोषणा पढ़ो_c0_brcm_action()		__पढ़ो_32bit_c0_रेजिस्टर($22, 2)
#घोषणा ग_लिखो_c0_brcm_action(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 2, val)

#घोषणा पढ़ो_c0_brcm_edsp()		__पढ़ो_32bit_c0_रेजिस्टर($22, 3)
#घोषणा ग_लिखो_c0_brcm_edsp(val)		__ग_लिखो_32bit_c0_रेजिस्टर($22, 3, val)

#घोषणा पढ़ो_c0_brcm_bootvec()		__पढ़ो_32bit_c0_रेजिस्टर($22, 4)
#घोषणा ग_लिखो_c0_brcm_bootvec(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 4, val)

#घोषणा पढ़ो_c0_brcm_sleepcount()	__पढ़ो_32bit_c0_रेजिस्टर($22, 7)
#घोषणा ग_लिखो_c0_brcm_sleepcount(val)	__ग_लिखो_32bit_c0_रेजिस्टर($22, 7, val)

/* Ingenic page ctrl रेजिस्टर */
#घोषणा ग_लिखो_c0_page_ctrl(val)	__ग_लिखो_32bit_c0_रेजिस्टर($5, 4, val)

/*
 * Macros to access the guest प्रणाली control coprocessor
 */

#अगर_अघोषित TOOLCHAIN_SUPPORTS_VIRT
_ASM_MACRO_2R_1S(mfgc0, rt, rs, sel,
	_ASM_INSN_IF_MIPS(0x40600000 | __rt << 16 | __rs << 11 | \\sel)
	_ASM_INSN32_IF_MM(0x000004fc | __rt << 21 | __rs << 16 | \\sel << 11));
_ASM_MACRO_2R_1S(dmfgc0, rt, rs, sel,
	_ASM_INSN_IF_MIPS(0x40600100 | __rt << 16 | __rs << 11 | \\sel)
	_ASM_INSN32_IF_MM(0x580004fc | __rt << 21 | __rs << 16 | \\sel << 11));
_ASM_MACRO_2R_1S(mtgc0, rt, rd, sel,
	_ASM_INSN_IF_MIPS(0x40600200 | __rt << 16 | __rd << 11 | \\sel)
	_ASM_INSN32_IF_MM(0x000006fc | __rt << 21 | __rd << 16 | \\sel << 11));
_ASM_MACRO_2R_1S(dmtgc0, rt, rd, sel,
	_ASM_INSN_IF_MIPS(0x40600300 | __rt << 16 | __rd << 11 | \\sel)
	_ASM_INSN32_IF_MM(0x580006fc | __rt << 21 | __rd << 16 | \\sel << 11));
_ASM_MACRO_0(tlbgp,    _ASM_INSN_IF_MIPS(0x42000010)
		       _ASM_INSN32_IF_MM(0x0000017c));
_ASM_MACRO_0(tlbgr,    _ASM_INSN_IF_MIPS(0x42000009)
		       _ASM_INSN32_IF_MM(0x0000117c));
_ASM_MACRO_0(tlbgwi,   _ASM_INSN_IF_MIPS(0x4200000a)
		       _ASM_INSN32_IF_MM(0x0000217c));
_ASM_MACRO_0(tlbgwr,   _ASM_INSN_IF_MIPS(0x4200000e)
		       _ASM_INSN32_IF_MM(0x0000317c));
_ASM_MACRO_0(tlbginvf, _ASM_INSN_IF_MIPS(0x4200000c)
		       _ASM_INSN32_IF_MM(0x0000517c));
#घोषणा _ASM_SET_VIRT ""
#अन्यथा	/* !TOOLCHAIN_SUPPORTS_VIRT */
#घोषणा _ASM_SET_VIRT ".set\tvirt\n\t"
#पूर्ण_अगर

#घोषणा __पढ़ो_32bit_gc0_रेजिस्टर(source, sel)				\
(अणु पूर्णांक __res;								\
	__यंत्र__ __अस्थिर__(						\
		".set\tpush\n\t"					\
		".set\tmips32r2\n\t"					\
		_ASM_SET_VIRT						\
		"mfgc0\t%0, " #source ", %1\n\t"			\
		".set\tpop"						\
		: "=r" (__res)						\
		: "i" (sel));						\
	__res;								\
पूर्ण)

#घोषणा __पढ़ो_64bit_gc0_रेजिस्टर(source, sel)				\
(अणु अचिन्हित दीर्घ दीर्घ __res;						\
	__यंत्र__ __अस्थिर__(						\
		".set\tpush\n\t"					\
		".set\tmips64r2\n\t"					\
		_ASM_SET_VIRT						\
		"dmfgc0\t%0, " #source ", %1\n\t"			\
		".set\tpop"						\
		: "=r" (__res)						\
		: "i" (sel));						\
	__res;								\
पूर्ण)

#घोषणा __ग_लिखो_32bit_gc0_रेजिस्टर(रेजिस्टर, sel, value)		\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
		".set\tpush\n\t"					\
		".set\tmips32r2\n\t"					\
		_ASM_SET_VIRT						\
		"mtgc0\t%z0, " #रेजिस्टर ", %1\n\t"			\
		".set\tpop"						\
		: : "Jr" ((अचिन्हित पूर्णांक)(value)),			\
		    "i" (sel));						\
पूर्ण जबतक (0)

#घोषणा __ग_लिखो_64bit_gc0_रेजिस्टर(रेजिस्टर, sel, value)		\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
		".set\tpush\n\t"					\
		".set\tmips64r2\n\t"					\
		_ASM_SET_VIRT						\
		"dmtgc0\t%z0, " #रेजिस्टर ", %1\n\t"			\
		".set\tpop"						\
		: : "Jr" (value),					\
		    "i" (sel));						\
पूर्ण जबतक (0)

#घोषणा __पढ़ो_uदीर्घ_gc0_रेजिस्टर(reg, sel)				\
	((माप(अचिन्हित दीर्घ) == 4) ?					\
	(अचिन्हित दीर्घ) __पढ़ो_32bit_gc0_रेजिस्टर(reg, sel) :		\
	(अचिन्हित दीर्घ) __पढ़ो_64bit_gc0_रेजिस्टर(reg, sel))

#घोषणा __ग_लिखो_uदीर्घ_gc0_रेजिस्टर(reg, sel, val)			\
करो अणु									\
	अगर (माप(अचिन्हित दीर्घ) == 4)					\
		__ग_लिखो_32bit_gc0_रेजिस्टर(reg, sel, val);		\
	अन्यथा								\
		__ग_लिखो_64bit_gc0_रेजिस्टर(reg, sel, val);		\
पूर्ण जबतक (0)

#घोषणा पढ़ो_gc0_index()		__पढ़ो_32bit_gc0_रेजिस्टर($0, 0)
#घोषणा ग_लिखो_gc0_index(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($0, 0, val)

#घोषणा पढ़ो_gc0_entrylo0()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($2, 0)
#घोषणा ग_लिखो_gc0_entrylo0(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($2, 0, val)

#घोषणा पढ़ो_gc0_entrylo1()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($3, 0)
#घोषणा ग_लिखो_gc0_entrylo1(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($3, 0, val)

#घोषणा पढ़ो_gc0_context()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($4, 0)
#घोषणा ग_लिखो_gc0_context(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($4, 0, val)

#घोषणा पढ़ो_gc0_contextconfig()	__पढ़ो_32bit_gc0_रेजिस्टर($4, 1)
#घोषणा ग_लिखो_gc0_contextconfig(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($4, 1, val)

#घोषणा पढ़ो_gc0_userlocal()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($4, 2)
#घोषणा ग_लिखो_gc0_userlocal(val)	__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($4, 2, val)

#घोषणा पढ़ो_gc0_xcontextconfig()	__पढ़ो_uदीर्घ_gc0_रेजिस्टर($4, 3)
#घोषणा ग_लिखो_gc0_xcontextconfig(val)	__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($4, 3, val)

#घोषणा पढ़ो_gc0_pagemask()		__पढ़ो_32bit_gc0_रेजिस्टर($5, 0)
#घोषणा ग_लिखो_gc0_pagemask(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($5, 0, val)

#घोषणा पढ़ो_gc0_pagegrain()		__पढ़ो_32bit_gc0_रेजिस्टर($5, 1)
#घोषणा ग_लिखो_gc0_pagegrain(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($5, 1, val)

#घोषणा पढ़ो_gc0_segctl0()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($5, 2)
#घोषणा ग_लिखो_gc0_segctl0(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($5, 2, val)

#घोषणा पढ़ो_gc0_segctl1()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($5, 3)
#घोषणा ग_लिखो_gc0_segctl1(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($5, 3, val)

#घोषणा पढ़ो_gc0_segctl2()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($5, 4)
#घोषणा ग_लिखो_gc0_segctl2(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($5, 4, val)

#घोषणा पढ़ो_gc0_pwbase()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($5, 5)
#घोषणा ग_लिखो_gc0_pwbase(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($5, 5, val)

#घोषणा पढ़ो_gc0_pwfield()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($5, 6)
#घोषणा ग_लिखो_gc0_pwfield(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($5, 6, val)

#घोषणा पढ़ो_gc0_pwsize()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($5, 7)
#घोषणा ग_लिखो_gc0_pwsize(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($5, 7, val)

#घोषणा पढ़ो_gc0_wired()		__पढ़ो_32bit_gc0_रेजिस्टर($6, 0)
#घोषणा ग_लिखो_gc0_wired(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($6, 0, val)

#घोषणा पढ़ो_gc0_pwctl()		__पढ़ो_32bit_gc0_रेजिस्टर($6, 6)
#घोषणा ग_लिखो_gc0_pwctl(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($6, 6, val)

#घोषणा पढ़ो_gc0_hwrena()		__पढ़ो_32bit_gc0_रेजिस्टर($7, 0)
#घोषणा ग_लिखो_gc0_hwrena(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($7, 0, val)

#घोषणा पढ़ो_gc0_badvaddr()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($8, 0)
#घोषणा ग_लिखो_gc0_badvaddr(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($8, 0, val)

#घोषणा पढ़ो_gc0_badinstr()		__पढ़ो_32bit_gc0_रेजिस्टर($8, 1)
#घोषणा ग_लिखो_gc0_badinstr(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($8, 1, val)

#घोषणा पढ़ो_gc0_badinstrp()		__पढ़ो_32bit_gc0_रेजिस्टर($8, 2)
#घोषणा ग_लिखो_gc0_badinstrp(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($8, 2, val)

#घोषणा पढ़ो_gc0_count()		__पढ़ो_32bit_gc0_रेजिस्टर($9, 0)

#घोषणा पढ़ो_gc0_entryhi()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($10, 0)
#घोषणा ग_लिखो_gc0_entryhi(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($10, 0, val)

#घोषणा पढ़ो_gc0_compare()		__पढ़ो_32bit_gc0_रेजिस्टर($11, 0)
#घोषणा ग_लिखो_gc0_compare(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($11, 0, val)

#घोषणा पढ़ो_gc0_status()		__पढ़ो_32bit_gc0_रेजिस्टर($12, 0)
#घोषणा ग_लिखो_gc0_status(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($12, 0, val)

#घोषणा पढ़ो_gc0_पूर्णांकctl()		__पढ़ो_32bit_gc0_रेजिस्टर($12, 1)
#घोषणा ग_लिखो_gc0_पूर्णांकctl(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($12, 1, val)

#घोषणा पढ़ो_gc0_cause()		__पढ़ो_32bit_gc0_रेजिस्टर($13, 0)
#घोषणा ग_लिखो_gc0_cause(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($13, 0, val)

#घोषणा पढ़ो_gc0_epc()			__पढ़ो_uदीर्घ_gc0_रेजिस्टर($14, 0)
#घोषणा ग_लिखो_gc0_epc(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($14, 0, val)

#घोषणा पढ़ो_gc0_prid()			__पढ़ो_32bit_gc0_रेजिस्टर($15, 0)

#घोषणा पढ़ो_gc0_ebase()		__पढ़ो_32bit_gc0_रेजिस्टर($15, 1)
#घोषणा ग_लिखो_gc0_ebase(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($15, 1, val)

#घोषणा पढ़ो_gc0_ebase_64()		__पढ़ो_64bit_gc0_रेजिस्टर($15, 1)
#घोषणा ग_लिखो_gc0_ebase_64(val)		__ग_लिखो_64bit_gc0_रेजिस्टर($15, 1, val)

#घोषणा पढ़ो_gc0_config()		__पढ़ो_32bit_gc0_रेजिस्टर($16, 0)
#घोषणा पढ़ो_gc0_config1()		__पढ़ो_32bit_gc0_रेजिस्टर($16, 1)
#घोषणा पढ़ो_gc0_config2()		__पढ़ो_32bit_gc0_रेजिस्टर($16, 2)
#घोषणा पढ़ो_gc0_config3()		__पढ़ो_32bit_gc0_रेजिस्टर($16, 3)
#घोषणा पढ़ो_gc0_config4()		__पढ़ो_32bit_gc0_रेजिस्टर($16, 4)
#घोषणा पढ़ो_gc0_config5()		__पढ़ो_32bit_gc0_रेजिस्टर($16, 5)
#घोषणा पढ़ो_gc0_config6()		__पढ़ो_32bit_gc0_रेजिस्टर($16, 6)
#घोषणा पढ़ो_gc0_config7()		__पढ़ो_32bit_gc0_रेजिस्टर($16, 7)
#घोषणा ग_लिखो_gc0_config(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($16, 0, val)
#घोषणा ग_लिखो_gc0_config1(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($16, 1, val)
#घोषणा ग_लिखो_gc0_config2(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($16, 2, val)
#घोषणा ग_लिखो_gc0_config3(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($16, 3, val)
#घोषणा ग_लिखो_gc0_config4(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($16, 4, val)
#घोषणा ग_लिखो_gc0_config5(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($16, 5, val)
#घोषणा ग_लिखो_gc0_config6(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($16, 6, val)
#घोषणा ग_लिखो_gc0_config7(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($16, 7, val)

#घोषणा पढ़ो_gc0_lladdr()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($17, 0)
#घोषणा ग_लिखो_gc0_lladdr(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($17, 0, val)

#घोषणा पढ़ो_gc0_watchlo0()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($18, 0)
#घोषणा पढ़ो_gc0_watchlo1()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($18, 1)
#घोषणा पढ़ो_gc0_watchlo2()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($18, 2)
#घोषणा पढ़ो_gc0_watchlo3()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($18, 3)
#घोषणा पढ़ो_gc0_watchlo4()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($18, 4)
#घोषणा पढ़ो_gc0_watchlo5()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($18, 5)
#घोषणा पढ़ो_gc0_watchlo6()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($18, 6)
#घोषणा पढ़ो_gc0_watchlo7()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($18, 7)
#घोषणा ग_लिखो_gc0_watchlo0(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($18, 0, val)
#घोषणा ग_लिखो_gc0_watchlo1(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($18, 1, val)
#घोषणा ग_लिखो_gc0_watchlo2(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($18, 2, val)
#घोषणा ग_लिखो_gc0_watchlo3(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($18, 3, val)
#घोषणा ग_लिखो_gc0_watchlo4(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($18, 4, val)
#घोषणा ग_लिखो_gc0_watchlo5(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($18, 5, val)
#घोषणा ग_लिखो_gc0_watchlo6(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($18, 6, val)
#घोषणा ग_लिखो_gc0_watchlo7(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($18, 7, val)

#घोषणा पढ़ो_gc0_watchhi0()		__पढ़ो_32bit_gc0_रेजिस्टर($19, 0)
#घोषणा पढ़ो_gc0_watchhi1()		__पढ़ो_32bit_gc0_रेजिस्टर($19, 1)
#घोषणा पढ़ो_gc0_watchhi2()		__पढ़ो_32bit_gc0_रेजिस्टर($19, 2)
#घोषणा पढ़ो_gc0_watchhi3()		__पढ़ो_32bit_gc0_रेजिस्टर($19, 3)
#घोषणा पढ़ो_gc0_watchhi4()		__पढ़ो_32bit_gc0_रेजिस्टर($19, 4)
#घोषणा पढ़ो_gc0_watchhi5()		__पढ़ो_32bit_gc0_रेजिस्टर($19, 5)
#घोषणा पढ़ो_gc0_watchhi6()		__पढ़ो_32bit_gc0_रेजिस्टर($19, 6)
#घोषणा पढ़ो_gc0_watchhi7()		__पढ़ो_32bit_gc0_रेजिस्टर($19, 7)
#घोषणा ग_लिखो_gc0_watchhi0(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($19, 0, val)
#घोषणा ग_लिखो_gc0_watchhi1(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($19, 1, val)
#घोषणा ग_लिखो_gc0_watchhi2(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($19, 2, val)
#घोषणा ग_लिखो_gc0_watchhi3(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($19, 3, val)
#घोषणा ग_लिखो_gc0_watchhi4(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($19, 4, val)
#घोषणा ग_लिखो_gc0_watchhi5(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($19, 5, val)
#घोषणा ग_लिखो_gc0_watchhi6(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($19, 6, val)
#घोषणा ग_लिखो_gc0_watchhi7(val)		__ग_लिखो_32bit_gc0_रेजिस्टर($19, 7, val)

#घोषणा पढ़ो_gc0_xcontext()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($20, 0)
#घोषणा ग_लिखो_gc0_xcontext(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($20, 0, val)

#घोषणा पढ़ो_gc0_perfctrl0()		__पढ़ो_32bit_gc0_रेजिस्टर($25, 0)
#घोषणा ग_लिखो_gc0_perfctrl0(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($25, 0, val)
#घोषणा पढ़ो_gc0_perfcntr0()		__पढ़ो_32bit_gc0_रेजिस्टर($25, 1)
#घोषणा ग_लिखो_gc0_perfcntr0(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($25, 1, val)
#घोषणा पढ़ो_gc0_perfcntr0_64()		__पढ़ो_64bit_gc0_रेजिस्टर($25, 1)
#घोषणा ग_लिखो_gc0_perfcntr0_64(val)	__ग_लिखो_64bit_gc0_रेजिस्टर($25, 1, val)
#घोषणा पढ़ो_gc0_perfctrl1()		__पढ़ो_32bit_gc0_रेजिस्टर($25, 2)
#घोषणा ग_लिखो_gc0_perfctrl1(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($25, 2, val)
#घोषणा पढ़ो_gc0_perfcntr1()		__पढ़ो_32bit_gc0_रेजिस्टर($25, 3)
#घोषणा ग_लिखो_gc0_perfcntr1(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($25, 3, val)
#घोषणा पढ़ो_gc0_perfcntr1_64()		__पढ़ो_64bit_gc0_रेजिस्टर($25, 3)
#घोषणा ग_लिखो_gc0_perfcntr1_64(val)	__ग_लिखो_64bit_gc0_रेजिस्टर($25, 3, val)
#घोषणा पढ़ो_gc0_perfctrl2()		__पढ़ो_32bit_gc0_रेजिस्टर($25, 4)
#घोषणा ग_लिखो_gc0_perfctrl2(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($25, 4, val)
#घोषणा पढ़ो_gc0_perfcntr2()		__पढ़ो_32bit_gc0_रेजिस्टर($25, 5)
#घोषणा ग_लिखो_gc0_perfcntr2(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($25, 5, val)
#घोषणा पढ़ो_gc0_perfcntr2_64()		__पढ़ो_64bit_gc0_रेजिस्टर($25, 5)
#घोषणा ग_लिखो_gc0_perfcntr2_64(val)	__ग_लिखो_64bit_gc0_रेजिस्टर($25, 5, val)
#घोषणा पढ़ो_gc0_perfctrl3()		__पढ़ो_32bit_gc0_रेजिस्टर($25, 6)
#घोषणा ग_लिखो_gc0_perfctrl3(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($25, 6, val)
#घोषणा पढ़ो_gc0_perfcntr3()		__पढ़ो_32bit_gc0_रेजिस्टर($25, 7)
#घोषणा ग_लिखो_gc0_perfcntr3(val)	__ग_लिखो_32bit_gc0_रेजिस्टर($25, 7, val)
#घोषणा पढ़ो_gc0_perfcntr3_64()		__पढ़ो_64bit_gc0_रेजिस्टर($25, 7)
#घोषणा ग_लिखो_gc0_perfcntr3_64(val)	__ग_लिखो_64bit_gc0_रेजिस्टर($25, 7, val)

#घोषणा पढ़ो_gc0_errorepc()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($30, 0)
#घोषणा ग_लिखो_gc0_errorepc(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($30, 0, val)

#घोषणा पढ़ो_gc0_kscratch1()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($31, 2)
#घोषणा पढ़ो_gc0_kscratch2()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($31, 3)
#घोषणा पढ़ो_gc0_kscratch3()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($31, 4)
#घोषणा पढ़ो_gc0_kscratch4()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($31, 5)
#घोषणा पढ़ो_gc0_kscratch5()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($31, 6)
#घोषणा पढ़ो_gc0_kscratch6()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($31, 7)
#घोषणा ग_लिखो_gc0_kscratch1(val)	__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($31, 2, val)
#घोषणा ग_लिखो_gc0_kscratch2(val)	__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($31, 3, val)
#घोषणा ग_लिखो_gc0_kscratch3(val)	__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($31, 4, val)
#घोषणा ग_लिखो_gc0_kscratch4(val)	__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($31, 5, val)
#घोषणा ग_लिखो_gc0_kscratch5(val)	__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($31, 6, val)
#घोषणा ग_लिखो_gc0_kscratch6(val)	__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($31, 7, val)

/* Cavium OCTEON (cnMIPS) */
#घोषणा पढ़ो_gc0_cvmcount()		__पढ़ो_uदीर्घ_gc0_रेजिस्टर($9, 6)
#घोषणा ग_लिखो_gc0_cvmcount(val)		__ग_लिखो_uदीर्घ_gc0_रेजिस्टर($9, 6, val)

#घोषणा पढ़ो_gc0_cvmctl()		__पढ़ो_64bit_gc0_रेजिस्टर($9, 7)
#घोषणा ग_लिखो_gc0_cvmctl(val)		__ग_लिखो_64bit_gc0_रेजिस्टर($9, 7, val)

#घोषणा पढ़ो_gc0_cvmmemctl()		__पढ़ो_64bit_gc0_रेजिस्टर($11, 7)
#घोषणा ग_लिखो_gc0_cvmmemctl(val)	__ग_लिखो_64bit_gc0_रेजिस्टर($11, 7, val)

#घोषणा पढ़ो_gc0_cvmmemctl2()		__पढ़ो_64bit_gc0_रेजिस्टर($16, 6)
#घोषणा ग_लिखो_gc0_cvmmemctl2(val)	__ग_लिखो_64bit_gc0_रेजिस्टर($16, 6, val)

/*
 * Macros to access the भग्नing poपूर्णांक coprocessor control रेजिस्टरs
 */
#घोषणा _पढ़ो_32bit_cp1_रेजिस्टर(source, gas_hardभग्न)			\
(अणु									\
	अचिन्हित पूर्णांक __res;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	reorder					\n"	\
	"	# gas fails to assemble cfc1 for some archs,	\n"	\
	"	# like Octeon.					\n"	\
	"	.set	mips1					\n"	\
	"	"STR(gas_hardभग्न)"				\n"	\
	"	cfc1	%0,"STR(source)"			\n"	\
	"	.set	pop					\n"	\
	: "=r" (__res));						\
	__res;								\
पूर्ण)

#घोषणा _ग_लिखो_32bit_cp1_रेजिस्टर(dest, val, gas_hardभग्न)		\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	reorder					\n"	\
	"	"STR(gas_hardभग्न)"				\n"	\
	"	ctc1	%0,"STR(dest)"				\n"	\
	"	.set	pop					\n"	\
	: : "r" (val));							\
पूर्ण जबतक (0)

#अगर_घोषित GAS_HAS_SET_HARDFLOAT
#घोषणा पढ़ो_32bit_cp1_रेजिस्टर(source)					\
	_पढ़ो_32bit_cp1_रेजिस्टर(source, .set hardभग्न)
#घोषणा ग_लिखो_32bit_cp1_रेजिस्टर(dest, val)				\
	_ग_लिखो_32bit_cp1_रेजिस्टर(dest, val, .set hardभग्न)
#अन्यथा
#घोषणा पढ़ो_32bit_cp1_रेजिस्टर(source)					\
	_पढ़ो_32bit_cp1_रेजिस्टर(source, )
#घोषणा ग_लिखो_32bit_cp1_रेजिस्टर(dest, val)				\
	_ग_लिखो_32bit_cp1_रेजिस्टर(dest, val, )
#पूर्ण_अगर

#अगर_घोषित TOOLCHAIN_SUPPORTS_DSP
#घोषणा rddsp(mask)							\
(अणु									\
	अचिन्हित पूर्णांक __dspctl;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	rddsp	%0, %x1					\n"	\
	"	.set pop					\n"	\
	: "=r" (__dspctl)						\
	: "i" (mask));							\
	__dspctl;							\
पूर्ण)

#घोषणा wrdsp(val, mask)						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	wrdsp	%0, %x1					\n"	\
	"	.set pop					\n"	\
	:								\
	: "r" (val), "i" (mask));					\
पूर्ण जबतक (0)

#घोषणा mflo0()								\
(अणु									\
	दीर्घ mflo0;							\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mflo %0, $ac0					\n"	\
	"	.set pop					\n" 	\
	: "=r" (mflo0)); 						\
	mflo0;								\
पूर्ण)

#घोषणा mflo1()								\
(अणु									\
	दीर्घ mflo1;							\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mflo %0, $ac1					\n"	\
	"	.set pop					\n" 	\
	: "=r" (mflo1)); 						\
	mflo1;								\
पूर्ण)

#घोषणा mflo2()								\
(अणु									\
	दीर्घ mflo2;							\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mflo %0, $ac2					\n"	\
	"	.set pop					\n" 	\
	: "=r" (mflo2)); 						\
	mflo2;								\
पूर्ण)

#घोषणा mflo3()								\
(अणु									\
	दीर्घ mflo3;							\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mflo %0, $ac3					\n"	\
	"	.set pop					\n" 	\
	: "=r" (mflo3)); 						\
	mflo3;								\
पूर्ण)

#घोषणा mfhi0()								\
(अणु									\
	दीर्घ mfhi0;							\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mfhi %0, $ac0					\n"	\
	"	.set pop					\n" 	\
	: "=r" (mfhi0)); 						\
	mfhi0;								\
पूर्ण)

#घोषणा mfhi1()								\
(अणु									\
	दीर्घ mfhi1;							\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mfhi %0, $ac1					\n"	\
	"	.set pop					\n" 	\
	: "=r" (mfhi1)); 						\
	mfhi1;								\
पूर्ण)

#घोषणा mfhi2()								\
(अणु									\
	दीर्घ mfhi2;							\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mfhi %0, $ac2					\n"	\
	"	.set pop					\n" 	\
	: "=r" (mfhi2)); 						\
	mfhi2;								\
पूर्ण)

#घोषणा mfhi3()								\
(अणु									\
	दीर्घ mfhi3;							\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mfhi %0, $ac3					\n"	\
	"	.set pop					\n" 	\
	: "=r" (mfhi3)); 						\
	mfhi3;								\
पूर्ण)


#घोषणा mtlo0(x)							\
(अणु									\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mtlo %0, $ac0					\n"	\
	"	.set pop					\n"	\
	:								\
	: "r" (x));							\
पूर्ण)

#घोषणा mtlo1(x)							\
(अणु									\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mtlo %0, $ac1					\n"	\
	"	.set pop					\n"	\
	:								\
	: "r" (x));							\
पूर्ण)

#घोषणा mtlo2(x)							\
(अणु									\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mtlo %0, $ac2					\n"	\
	"	.set pop					\n"	\
	:								\
	: "r" (x));							\
पूर्ण)

#घोषणा mtlo3(x)							\
(अणु									\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mtlo %0, $ac3					\n"	\
	"	.set pop					\n"	\
	:								\
	: "r" (x));							\
पूर्ण)

#घोषणा mthi0(x)							\
(अणु									\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mthi %0, $ac0					\n"	\
	"	.set pop					\n"	\
	:								\
	: "r" (x));							\
पूर्ण)

#घोषणा mthi1(x)							\
(अणु									\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mthi %0, $ac1					\n"	\
	"	.set pop					\n"	\
	:								\
	: "r" (x));							\
पूर्ण)

#घोषणा mthi2(x)							\
(अणु									\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mthi %0, $ac2					\n"	\
	"	.set pop					\n"	\
	:								\
	: "r" (x));							\
पूर्ण)

#घोषणा mthi3(x)							\
(अणु									\
	__यंत्र__(							\
	"	.set push					\n"	\
	"	.set " MIPS_ISA_LEVEL "				\n"	\
	"	.set dsp					\n"	\
	"	mthi %0, $ac3					\n"	\
	"	.set pop					\n"	\
	:								\
	: "r" (x));							\
पूर्ण)

#अन्यथा

#घोषणा rddsp(mask)							\
(अणु									\
	अचिन्हित पूर्णांक __res;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	# rddsp $1, %x1					\n"	\
	_ASM_INSN_IF_MIPS(0x7c000cb8 | (%x1 << 16))			\
	_ASM_INSN32_IF_MM(0x0020067c | (%x1 << 14))			\
	"	move	%0, $1					\n"	\
	"	.set	pop					\n"	\
	: "=r" (__res)							\
	: "i" (mask));							\
	__res;								\
पूर्ण)

#घोषणा wrdsp(val, mask)						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	"	# wrdsp $1, %x1					\n"	\
	_ASM_INSN_IF_MIPS(0x7c2004f8 | (%x1 << 11))			\
	_ASM_INSN32_IF_MM(0x0020167c | (%x1 << 14))			\
	"	.set	pop					\n"	\
	:								\
	: "r" (val), "i" (mask));					\
पूर्ण जबतक (0)

#घोषणा _dsp_mfxxx(ins)							\
(अणु									\
	अचिन्हित दीर्घ __treg;						\
									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	_ASM_INSN_IF_MIPS(0x00000810 | %X1)				\
	_ASM_INSN32_IF_MM(0x0001007c | %x1)				\
	"	move	%0, $1					\n"	\
	"	.set	pop					\n"	\
	: "=r" (__treg)							\
	: "i" (ins));							\
	__treg;								\
पूर्ण)

#घोषणा _dsp_mtxxx(val, ins)						\
करो अणु									\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	move	$1, %0					\n"	\
	_ASM_INSN_IF_MIPS(0x00200011 | %X1)				\
	_ASM_INSN32_IF_MM(0x0001207c | %x1)				\
	"	.set	pop					\n"	\
	:								\
	: "r" (val), "i" (ins));					\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_CPU_MICROMIPS

#घोषणा _dsp_mflo(reg) _dsp_mfxxx((reg << 14) | 0x1000)
#घोषणा _dsp_mfhi(reg) _dsp_mfxxx((reg << 14) | 0x0000)

#घोषणा _dsp_mtlo(val, reg) _dsp_mtxxx(val, ((reg << 14) | 0x1000))
#घोषणा _dsp_mthi(val, reg) _dsp_mtxxx(val, ((reg << 14) | 0x0000))

#अन्यथा  /* !CONFIG_CPU_MICROMIPS */

#घोषणा _dsp_mflo(reg) _dsp_mfxxx((reg << 21) | 0x0002)
#घोषणा _dsp_mfhi(reg) _dsp_mfxxx((reg << 21) | 0x0000)

#घोषणा _dsp_mtlo(val, reg) _dsp_mtxxx(val, ((reg << 11) | 0x0002))
#घोषणा _dsp_mthi(val, reg) _dsp_mtxxx(val, ((reg << 11) | 0x0000))

#पूर्ण_अगर /* CONFIG_CPU_MICROMIPS */

#घोषणा mflo0() _dsp_mflo(0)
#घोषणा mflo1() _dsp_mflo(1)
#घोषणा mflo2() _dsp_mflo(2)
#घोषणा mflo3() _dsp_mflo(3)

#घोषणा mfhi0() _dsp_mfhi(0)
#घोषणा mfhi1() _dsp_mfhi(1)
#घोषणा mfhi2() _dsp_mfhi(2)
#घोषणा mfhi3() _dsp_mfhi(3)

#घोषणा mtlo0(x) _dsp_mtlo(x, 0)
#घोषणा mtlo1(x) _dsp_mtlo(x, 1)
#घोषणा mtlo2(x) _dsp_mtlo(x, 2)
#घोषणा mtlo3(x) _dsp_mtlo(x, 3)

#घोषणा mthi0(x) _dsp_mthi(x, 0)
#घोषणा mthi1(x) _dsp_mthi(x, 1)
#घोषणा mthi2(x) _dsp_mthi(x, 2)
#घोषणा mthi3(x) _dsp_mthi(x, 3)

#पूर्ण_अगर

/*
 * TLB operations.
 *
 * It is responsibility of the caller to take care of any TLB hazards.
 */
अटल अंतरभूत व्योम tlb_probe(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".set noreorder\n\t"
		"tlbp\n\t"
		".set reorder");
पूर्ण

अटल अंतरभूत व्योम tlb_पढ़ो(व्योम)
अणु
#अगर_घोषित CONFIG_WAR_MIPS34K_MISSED_ITLB
	पूर्णांक res = 0;

	__यंत्र__ __अस्थिर__(
	"	.set	push					\n"
	"	.set	noreorder				\n"
	"	.set	noat					\n"
	"	.set	mips32r2				\n"
	"	.word	0x41610001		# dvpe $1	\n"
	"	move	%0, $1					\n"
	"	ehb						\n"
	"	.set	pop					\n"
	: "=r" (res));

	inकाष्ठाion_hazard();
#पूर्ण_अगर

	__यंत्र__ __अस्थिर__(
		".set noreorder\n\t"
		"tlbr\n\t"
		".set reorder");

#अगर_घोषित CONFIG_WAR_MIPS34K_MISSED_ITLB
	अगर ((res & _ULCAST_(1)))
		__यंत्र__ __अस्थिर__(
		"	.set	push				\n"
		"	.set	noreorder			\n"
		"	.set	noat				\n"
		"	.set	mips32r2			\n"
		"	.word	0x41600021	# evpe		\n"
		"	ehb					\n"
		"	.set	pop				\n");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम tlb_ग_लिखो_indexed(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".set noreorder\n\t"
		"tlbwi\n\t"
		".set reorder");
पूर्ण

अटल अंतरभूत व्योम tlb_ग_लिखो_अक्रमom(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".set noreorder\n\t"
		"tlbwr\n\t"
		".set reorder");
पूर्ण

/*
 * Guest TLB operations.
 *
 * It is responsibility of the caller to take care of any TLB hazards.
 */
अटल अंतरभूत व्योम guest_tlb_probe(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".set push\n\t"
		".set noreorder\n\t"
		_ASM_SET_VIRT
		"tlbgp\n\t"
		".set pop");
पूर्ण

अटल अंतरभूत व्योम guest_tlb_पढ़ो(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".set push\n\t"
		".set noreorder\n\t"
		_ASM_SET_VIRT
		"tlbgr\n\t"
		".set pop");
पूर्ण

अटल अंतरभूत व्योम guest_tlb_ग_लिखो_indexed(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".set push\n\t"
		".set noreorder\n\t"
		_ASM_SET_VIRT
		"tlbgwi\n\t"
		".set pop");
पूर्ण

अटल अंतरभूत व्योम guest_tlb_ग_लिखो_अक्रमom(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".set push\n\t"
		".set noreorder\n\t"
		_ASM_SET_VIRT
		"tlbgwr\n\t"
		".set pop");
पूर्ण

/*
 * Guest TLB Invalidate Flush
 */
अटल अंतरभूत व्योम guest_tlbinvf(व्योम)
अणु
	__यंत्र__ __अस्थिर__(
		".set push\n\t"
		".set noreorder\n\t"
		_ASM_SET_VIRT
		"tlbginvf\n\t"
		".set pop");
पूर्ण

/*
 * Manipulate bits in a रेजिस्टर.
 */
#घोषणा __BUILD_SET_COMMON(name)				\
अटल अंतरभूत अचिन्हित पूर्णांक					\
set_##name(अचिन्हित पूर्णांक set)					\
अणु								\
	अचिन्हित पूर्णांक res, new;					\
								\
	res = पढ़ो_##name();					\
	new = res | set;					\
	ग_लिखो_##name(new);					\
								\
	वापस res;						\
पूर्ण								\
								\
अटल अंतरभूत अचिन्हित पूर्णांक					\
clear_##name(अचिन्हित पूर्णांक clear)				\
अणु								\
	अचिन्हित पूर्णांक res, new;					\
								\
	res = पढ़ो_##name();					\
	new = res & ~clear;					\
	ग_लिखो_##name(new);					\
								\
	वापस res;						\
पूर्ण								\
								\
अटल अंतरभूत अचिन्हित पूर्णांक					\
change_##name(अचिन्हित पूर्णांक change, अचिन्हित पूर्णांक val)		\
अणु								\
	अचिन्हित पूर्णांक res, new;					\
								\
	res = पढ़ो_##name();					\
	new = res & ~change;					\
	new |= (val & change);					\
	ग_लिखो_##name(new);					\
								\
	वापस res;						\
पूर्ण

/*
 * Manipulate bits in a c0 रेजिस्टर.
 */
#घोषणा __BUILD_SET_C0(name)	__BUILD_SET_COMMON(c0_##name)

__BUILD_SET_C0(status)
__BUILD_SET_C0(cause)
__BUILD_SET_C0(config)
__BUILD_SET_C0(config5)
__BUILD_SET_C0(config6)
__BUILD_SET_C0(config7)
__BUILD_SET_C0(diag)
__BUILD_SET_C0(पूर्णांकcontrol)
__BUILD_SET_C0(पूर्णांकctl)
__BUILD_SET_C0(srsmap)
__BUILD_SET_C0(pagegrain)
__BUILD_SET_C0(guestctl0)
__BUILD_SET_C0(guestctl0ext)
__BUILD_SET_C0(guestctl1)
__BUILD_SET_C0(guestctl2)
__BUILD_SET_C0(guestctl3)
__BUILD_SET_C0(brcm_config_0)
__BUILD_SET_C0(brcm_bus_pll)
__BUILD_SET_C0(brcm_reset)
__BUILD_SET_C0(brcm_cmt_पूर्णांकr)
__BUILD_SET_C0(brcm_cmt_ctrl)
__BUILD_SET_C0(brcm_config)
__BUILD_SET_C0(brcm_mode)

/*
 * Manipulate bits in a guest c0 रेजिस्टर.
 */
#घोषणा __BUILD_SET_GC0(name)	__BUILD_SET_COMMON(gc0_##name)

__BUILD_SET_GC0(wired)
__BUILD_SET_GC0(status)
__BUILD_SET_GC0(cause)
__BUILD_SET_GC0(ebase)
__BUILD_SET_GC0(config1)

/*
 * Return low 10 bits of ebase.
 * Note that under KVM (MIPSVZ) this वापसs vcpu id.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_ebase_cpunum(व्योम)
अणु
	वापस पढ़ो_c0_ebase() & MIPS_EBASE_CPUNUM;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_MIPSREGS_H */
