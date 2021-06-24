<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Derived from IRIX <sys/SN/SN0/addrs.h>, revision 1.126.
 *
 * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.
 * Copyright (C) 1999 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SN_SN0_ADDRS_H
#घोषणा _ASM_SN_SN0_ADDRS_H


/*
 * SN0 (on a T5) Address map
 *
 * This file contains a set of definitions and macros which are used
 * to reference पूर्णांकo the major address spaces (CAC, HSPEC, IO, MSPEC,
 * and UNCAC) used by the SN0 architecture.  It also contains addresses
 * क्रम "major" अटलally locatable PROM/Kernel data काष्ठाures, such as
 * the partition table, the configuration data काष्ठाure, etc.
 * We make an implicit assumption that the processor using this file
 * follows the R10K's provisions क्रम specअगरying uncached attributes;
 * should this change, the base रेजिस्टरs may very well become processor-
 * dependent.
 *
 * For more inक्रमmation on the address spaces, see the "Local Resources"
 * chapter of the Hub specअगरication.
 *
 * NOTE: This header file is included both by C and by assembler source
 *	 files.	 Please bracket any language-dependent definitions
 *	 appropriately.
 */

/*
 * Some of the macros here need to be casted to appropriate types when used
 * from C.  They definitely must not be casted from assembly language so we
 * use some new ANSI preprocessor stuff to paste these on where needed.
 */

/*
 * The following couple of definitions will eventually need to be variables,
 * since the amount of address space asचिन्हित to each node depends on
 * whether the प्रणाली is running in N-mode (more nodes with less memory)
 * or M-mode (fewer nodes with more memory).  We expect that it will
 * be a जबतक beक्रमe we need to make this decision dynamically, though,
 * so क्रम now we just use defines bracketed by an अगरdef.
 */

#अगर_घोषित CONFIG_SGI_SN_N_MODE

#घोषणा NODE_SIZE_BITS		31
#घोषणा BWIN_SIZE_BITS		28

#घोषणा NASID_BITS		9
#घोषणा NASID_BITMASK		(0x1ffLL)
#घोषणा NASID_SHFT		31
#घोषणा NASID_META_BITS		5
#घोषणा NASID_LOCAL_BITS	4

#घोषणा BDसूची_UPPER_MASK	(UINT64_CAST 0x7ffff << 10)
#घोषणा BDECC_UPPER_MASK	(UINT64_CAST 0x3ffffff << 3)

#अन्यथा /* !defined(CONFIG_SGI_SN_N_MODE), assume that M-mode is desired */

#घोषणा NODE_SIZE_BITS		32
#घोषणा BWIN_SIZE_BITS		29

#घोषणा NASID_BITMASK		(0xffLL)
#घोषणा NASID_BITS		8
#घोषणा NASID_SHFT		32
#घोषणा NASID_META_BITS		4
#घोषणा NASID_LOCAL_BITS	4

#घोषणा BDसूची_UPPER_MASK	(UINT64_CAST 0xfffff << 10)
#घोषणा BDECC_UPPER_MASK	(UINT64_CAST 0x7ffffff << 3)

#पूर्ण_अगर /* !defined(CONFIG_SGI_SN_N_MODE) */

#घोषणा NODE_ADDRSPACE_SIZE	(UINT64_CAST 1 << NODE_SIZE_BITS)

#घोषणा NASID_MASK		(UINT64_CAST NASID_BITMASK << NASID_SHFT)
#घोषणा NASID_GET(_pa)		(पूर्णांक) ((UINT64_CAST (_pa) >>		\
					NASID_SHFT) & NASID_BITMASK)

#अगर !defined(__ASSEMBLY__)

#घोषणा NODE_SWIN_BASE(nasid, widget)					\
	((widget == 0) ? NODE_BWIN_BASE((nasid), SWIN0_BIGWIN)		\
	: RAW_NODE_SWIN_BASE(nasid, widget))
#अन्यथा /* __ASSEMBLY__ */
#घोषणा NODE_SWIN_BASE(nasid, widget) \
     (NODE_IO_BASE(nasid) + (UINT64_CAST(widget) << SWIN_SIZE_BITS))
#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * The following definitions pertain to the IO special address
 * space.  They define the location of the big and little winकरोws
 * of any given node.
 */

#घोषणा BWIN_INDEX_BITS		3
#घोषणा BWIN_SIZE		(UINT64_CAST 1 << BWIN_SIZE_BITS)
#घोषणा BWIN_SIZEMASK		(BWIN_SIZE - 1)
#घोषणा BWIN_WIDGET_MASK	0x7
#घोषणा NODE_BWIN_BASE0(nasid)	(NODE_IO_BASE(nasid) + BWIN_SIZE)
#घोषणा NODE_BWIN_BASE(nasid, bigwin)	(NODE_BWIN_BASE0(nasid) +	\
			(UINT64_CAST(bigwin) << BWIN_SIZE_BITS))

#घोषणा BWIN_WIDGETADDR(addr)	((addr) & BWIN_SIZEMASK)
#घोषणा BWIN_WINDOWNUM(addr)	(((addr) >> BWIN_SIZE_BITS) & BWIN_WIDGET_MASK)
/*
 * Verअगरy अगर addr beदीर्घs to large winकरोw address of node with "nasid"
 *
 *
 * NOTE: "addr" is expected to be XKPHYS address, and NOT physical
 * address
 *
 *
 */

#घोषणा NODE_BWIN_ADDR(nasid, addr)	\
		(((addr) >= NODE_BWIN_BASE0(nasid)) && \
		 ((addr) < (NODE_BWIN_BASE(nasid, HUB_NUM_BIG_WINDOW) + \
				BWIN_SIZE)))

/*
 * The following define the major position-independent aliases used
 * in SN0.
 *	CALIAS -- Varies in size, poपूर्णांकs to the first n bytes of memory
 *			on the पढ़ोer's node.
 */

#घोषणा CALIAS_BASE		CAC_BASE

#घोषणा SN0_WIDGET_BASE(_nasid, _wid)	(NODE_SWIN_BASE((_nasid), (_wid)))

/* Turn on sable logging क्रम the processors whose bits are set. */
#घोषणा SABLE_LOG_TRIGGER(_map)

#अगर_अघोषित __ASSEMBLY__
#घोषणा KERN_NMI_ADDR(nasid, slice)					\
		    TO_NODE_UNCAC((nasid), IP27_NMI_KREGS_OFFSET +	\
				  (IP27_NMI_KREGS_CPU_SIZE * (slice)))
#पूर्ण_अगर /* !__ASSEMBLY__ */

#अगर_घोषित PROM

#घोषणा MISC_PROM_BASE		PHYS_TO_K0(0x01300000)
#घोषणा MISC_PROM_SIZE		0x200000

#घोषणा DIAG_BASE		PHYS_TO_K0(0x01500000)
#घोषणा DIAG_SIZE		0x300000

#घोषणा ROUTE_BASE		PHYS_TO_K0(0x01800000)
#घोषणा ROUTE_SIZE		0x200000

#घोषणा IP27PROM_FLASH_HDR	PHYS_TO_K0(0x01300000)
#घोषणा IP27PROM_FLASH_DATA	PHYS_TO_K0(0x01301000)
#घोषणा IP27PROM_CORP_MAX	32
#घोषणा IP27PROM_CORP		PHYS_TO_K0(0x01800000)
#घोषणा IP27PROM_CORP_SIZE	0x10000
#घोषणा IP27PROM_CORP_STK	PHYS_TO_K0(0x01810000)
#घोषणा IP27PROM_CORP_STKSIZE	0x2000
#घोषणा IP27PROM_DECOMP_BUF	PHYS_TO_K0(0x01900000)
#घोषणा IP27PROM_DECOMP_SIZE	0xfff00

#घोषणा IP27PROM_BASE		PHYS_TO_K0(0x01a00000)
#घोषणा IP27PROM_BASE_MAPPED	(UNCAC_BASE | 0x1fc00000)
#घोषणा IP27PROM_SIZE_MAX	0x100000

#घोषणा IP27PROM_PCFG		PHYS_TO_K0(0x01b00000)
#घोषणा IP27PROM_PCFG_SIZE	0xd0000
#घोषणा IP27PROM_ERRDMP		PHYS_TO_K1(0x01bd0000)
#घोषणा IP27PROM_ERRDMP_SIZE	0xf000

#घोषणा IP27PROM_INIT_START	PHYS_TO_K1(0x01bd0000)
#घोषणा IP27PROM_CONSOLE	PHYS_TO_K1(0x01bdf000)
#घोषणा IP27PROM_CONSOLE_SIZE	0x200
#घोषणा IP27PROM_NETUART	PHYS_TO_K1(0x01bdf200)
#घोषणा IP27PROM_NETUART_SIZE	0x100
#घोषणा IP27PROM_UNUSED1	PHYS_TO_K1(0x01bdf300)
#घोषणा IP27PROM_UNUSED1_SIZE	0x500
#घोषणा IP27PROM_ELSC_BASE_A	PHYS_TO_K0(0x01bdf800)
#घोषणा IP27PROM_ELSC_BASE_B	PHYS_TO_K0(0x01bdfc00)
#घोषणा IP27PROM_STACK_A	PHYS_TO_K0(0x01be0000)
#घोषणा IP27PROM_STACK_B	PHYS_TO_K0(0x01bf0000)
#घोषणा IP27PROM_STACK_SHFT	16
#घोषणा IP27PROM_STACK_SIZE	(1 << IP27PROM_STACK_SHFT)
#घोषणा IP27PROM_INIT_END	PHYS_TO_K0(0x01c00000)

#घोषणा SLAVESTACK_BASE		PHYS_TO_K0(0x01580000)
#घोषणा SLAVESTACK_SIZE		0x40000

#घोषणा ENETBUFS_BASE		PHYS_TO_K0(0x01f80000)
#घोषणा ENETBUFS_SIZE		0x20000

#घोषणा IO6PROM_BASE		PHYS_TO_K0(0x01c00000)
#घोषणा IO6PROM_SIZE		0x400000
#घोषणा IO6PROM_BASE_MAPPED	(UNCAC_BASE | 0x11c00000)
#घोषणा IO6DPROM_BASE		PHYS_TO_K0(0x01c00000)
#घोषणा IO6DPROM_SIZE		0x200000

#घोषणा NODEBUGUNIX_ADDR	PHYS_TO_K0(0x00019000)
#घोषणा DEBUGUNIX_ADDR		PHYS_TO_K0(0x00100000)

#घोषणा IP27PROM_INT_LAUNCH	10	/* and 11 */
#घोषणा IP27PROM_INT_NETUART	12	/* through 17 */

#पूर्ण_अगर /* PROM */

/*
 * needed by symmon so it needs to be outside #अगर PROM
 */
#घोषणा IP27PROM_ELSC_SHFT	10
#घोषणा IP27PROM_ELSC_SIZE	(1 << IP27PROM_ELSC_SHFT)

/*
 * This address is used by IO6PROM to build MemoryDescriptors of
 * मुक्त memory. This address is important since unix माला_लो loaded
 * at this address, and this memory has to be FREE अगर unix is to
 * be loaded.
 */

#घोषणा FREEMEM_BASE		PHYS_TO_K0(0x2000000)

#घोषणा IO6PROM_STACK_SHFT	14	/* stack per cpu */
#घोषणा IO6PROM_STACK_SIZE	(1 << IO6PROM_STACK_SHFT)

/*
 * IP27 PROM vectors
 */

#घोषणा IP27PROM_ENTRY		PHYS_TO_COMPATK1(0x1fc00000)
#घोषणा IP27PROM_RESTART	PHYS_TO_COMPATK1(0x1fc00008)
#घोषणा IP27PROM_SLAVELOOP	PHYS_TO_COMPATK1(0x1fc00010)
#घोषणा IP27PROM_PODMODE	PHYS_TO_COMPATK1(0x1fc00018)
#घोषणा IP27PROM_IOC3UARTPOD	PHYS_TO_COMPATK1(0x1fc00020)
#घोषणा IP27PROM_FLASHLEDS	PHYS_TO_COMPATK1(0x1fc00028)
#घोषणा IP27PROM_REPOD		PHYS_TO_COMPATK1(0x1fc00030)
#घोषणा IP27PROM_LAUNCHSLAVE	PHYS_TO_COMPATK1(0x1fc00038)
#घोषणा IP27PROM_WAITSLAVE	PHYS_TO_COMPATK1(0x1fc00040)
#घोषणा IP27PROM_POLLSLAVE	PHYS_TO_COMPATK1(0x1fc00048)

#घोषणा KL_UART_BASE	LOCAL_HUB_ADDR(MD_UREG0_0)	/* base of UART regs */
#घोषणा KL_UART_CMD	LOCAL_HUB_ADDR(MD_UREG0_0)	/* UART command reg */
#घोषणा KL_UART_DATA	LOCAL_HUB_ADDR(MD_UREG0_1)	/* UART data reg */
#घोषणा KL_I2C_REG	MD_UREG0_0			/* I2C reg */

#अगर_अघोषित __ASSEMBLY__

/* Address 0x400 to 0x1000 ualias poपूर्णांकs to cache error eframe + misc
 * CACHE_ERR_SP_PTR could either contain an address to the stack, or
 * the stack could start at CACHE_ERR_SP_PTR
 */
#अगर defined(HUB_ERR_STS_WAR)
#घोषणा CACHE_ERR_EFRAME	0x480
#अन्यथा /* HUB_ERR_STS_WAR */
#घोषणा CACHE_ERR_EFRAME	0x400
#पूर्ण_अगर /* HUB_ERR_STS_WAR */

#घोषणा CACHE_ERR_ECCFRAME	(CACHE_ERR_EFRAME + EF_SIZE)
#घोषणा CACHE_ERR_SP_PTR	(0x1000 - 32)	/* why -32? TBD */
#घोषणा CACHE_ERR_IBASE_PTR	(0x1000 - 40)
#घोषणा CACHE_ERR_SP		(CACHE_ERR_SP_PTR - 16)
#घोषणा CACHE_ERR_AREA_SIZE	(ARCS_SPB_OFFSET - CACHE_ERR_EFRAME)

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#घोषणा _ARCSPROM

#अगर defined(HUB_ERR_STS_WAR)

#घोषणा ERR_STS_WAR_REGISTER	IIO_IIBUSERR
#घोषणा ERR_STS_WAR_ADDR	LOCAL_HUB_ADDR(IIO_IIBUSERR)
#घोषणा ERR_STS_WAR_PHYSADDR	TO_PHYS((__psअचिन्हित_t)ERR_STS_WAR_ADDR)
				/* Used to match addr in error reg. */
#घोषणा OLD_ERR_STS_WAR_OFFSET	((MD_MEM_BANKS * MD_BANK_SIZE) - 0x100)

#पूर्ण_अगर /* HUB_ERR_STS_WAR */

#पूर्ण_अगर /* _ASM_SN_SN0_ADDRS_H */
