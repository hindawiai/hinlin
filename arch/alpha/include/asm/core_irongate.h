<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_IRONGATE__H__
#घोषणा __ALPHA_IRONGATE__H__

#समावेश <linux/types.h>
#समावेश <यंत्र/compiler.h>

/*
 * IRONGATE is the पूर्णांकernal name क्रम the AMD-751 K7 core logic chipset
 * which provides memory controller and PCI access क्रम NAUTILUS-based
 * EV6 (21264) प्रणालीs.
 *
 * This file is based on:
 *
 * IronGate management library, (c) 1999 Alpha Processor, Inc.
 * Copyright (C) 1999 Alpha Processor, Inc.,
 *	(David Daniel, Stig Telfer, Soohoon Lee)
 */

/*
 * The 21264 supports, and पूर्णांकernally recognizes, a 44-bit physical
 * address space that is भागided equally between memory address space
 * and I/O address space. Memory address space resides in the lower
 * half of the physical address space (PA[43]=0) and I/O address space
 * resides in the upper half of the physical address space (PA[43]=1).
 */

/*
 * Irongate CSR map.  Some of the CSRs are 8 or 16 bits, but all access
 * through the routines given is 32-bit.
 *
 * The first 0x40 bytes are standard as per the PCI spec.
 */

प्रकार अस्थिर __u32	igcsr32;

प्रकार काष्ठा अणु
	igcsr32 dev_venकरोr;		/* 0x00 - device ID, venकरोr ID */
	igcsr32 stat_cmd;		/* 0x04 - status, command */
	igcsr32 class;			/* 0x08 - class code, rev ID */
	igcsr32 latency;		/* 0x0C - header type, PCI latency */
	igcsr32 bar0;			/* 0x10 - BAR0 - AGP */
	igcsr32 bar1;			/* 0x14 - BAR1 - GART */
	igcsr32 bar2;			/* 0x18 - Power Management reg block */

	igcsr32 rsrvd0[6];		/* 0x1C-0x33 reserved */

	igcsr32 capptr;			/* 0x34 - Capabilities poपूर्णांकer */

	igcsr32 rsrvd1[2];		/* 0x38-0x3F reserved */

	igcsr32 bacsr10;		/* 0x40 - base address chip selects */
	igcsr32 bacsr32;		/* 0x44 - base address chip selects */
	igcsr32 bacsr54_eccms761;	/* 0x48 - 751: base addr. chip selects
						  761: ECC, mode/status */

	igcsr32 rsrvd2[1];		/* 0x4C-0x4F reserved */

	igcsr32 drammap;		/* 0x50 - address mapping control */
	igcsr32 dramपंचांग;			/* 0x54 - timing, driver strength */
	igcsr32 dramms;			/* 0x58 - DRAM mode/status */

	igcsr32 rsrvd3[1];		/* 0x5C-0x5F reserved */

	igcsr32 biu0;			/* 0x60 - bus पूर्णांकerface unit */
	igcsr32 biusip;			/* 0x64 - Serial initialisation pkt */

	igcsr32 rsrvd4[2];		/* 0x68-0x6F reserved */

	igcsr32 mro;			/* 0x70 - memory request optimiser */

	igcsr32 rsrvd5[3];		/* 0x74-0x7F reserved */

	igcsr32 whami;			/* 0x80 - who am I */
	igcsr32 pciarb;			/* 0x84 - PCI arbitration control */
	igcsr32 pcicfg;			/* 0x88 - PCI config status */

	igcsr32 rsrvd6[4];		/* 0x8C-0x9B reserved */

	igcsr32 pci_mem;		/* 0x9C - PCI top of memory,
						  761 only */

	/* AGP (bus 1) control रेजिस्टरs */
	igcsr32 agpcap;			/* 0xA0 - AGP Capability Identअगरier */
	igcsr32 agpstat;		/* 0xA4 - AGP status रेजिस्टर */
	igcsr32 agpcmd;			/* 0xA8 - AGP control रेजिस्टर */
	igcsr32 agpva;			/* 0xAC - AGP Virtual Address Space */
	igcsr32 agpmode;		/* 0xB0 - AGP/GART mode control */
पूर्ण Irongate0;


प्रकार काष्ठा अणु

	igcsr32 dev_venकरोr;		/* 0x00 - Device and Venकरोr IDs */
	igcsr32 stat_cmd;		/* 0x04 - Status and Command regs */
	igcsr32 class;			/* 0x08 - subclass, baseclass etc */
	igcsr32 htype;			/* 0x0C - header type (at 0x0E) */
	igcsr32 rsrvd0[2];		/* 0x10-0x17 reserved */
	igcsr32 busnos;			/* 0x18 - Primary, secondary bus nos */
	igcsr32 io_baselim_regs;	/* 0x1C - IO base, IO lim, AGP status */
	igcsr32	mem_baselim;		/* 0x20 - memory base, memory lim */
	igcsr32 pfmem_baselim;		/* 0x24 - prefetchable base, lim */
	igcsr32 rsrvd1[2];		/* 0x28-0x2F reserved */
	igcsr32 io_baselim;		/* 0x30 - IO base, IO limit */
	igcsr32 rsrvd2[2];		/* 0x34-0x3B - reserved */
	igcsr32 पूर्णांकerrupt;		/* 0x3C - पूर्णांकerrupt, PCI bridge ctrl */

पूर्ण Irongate1;

बाह्य igcsr32 *IronECC;

/*
 * Memory spaces:
 */

/* Irongate is consistent with a subset of the Tsunami memory map */
#अगर_घोषित USE_48_BIT_KSEG
#घोषणा IRONGATE_BIAS 0x80000000000UL
#अन्यथा
#घोषणा IRONGATE_BIAS 0x10000000000UL
#पूर्ण_अगर


#घोषणा IRONGATE_MEM		(IDENT_ADDR | IRONGATE_BIAS | 0x000000000UL)
#घोषणा IRONGATE_IACK_SC	(IDENT_ADDR | IRONGATE_BIAS | 0x1F8000000UL)
#घोषणा IRONGATE_IO		(IDENT_ADDR | IRONGATE_BIAS | 0x1FC000000UL)
#घोषणा IRONGATE_CONF		(IDENT_ADDR | IRONGATE_BIAS | 0x1FE000000UL)

/*
 * PCI Configuration space accesses are क्रमmed like so:
 *
 * 0x1FE << 24 |  : 2 2 2 2 1 1 1 1 : 1 1 1 1 1 1 0 0 : 0 0 0 0 0 0 0 0 :
 *                : 3 2 1 0 9 8 7 6 : 5 4 3 2 1 0 9 8 : 7 6 5 4 3 2 1 0 :
 *                  ---bus numer---   -device-- -fun-   ---रेजिस्टर----
 */

#घोषणा IGCSR(dev,fun,reg)	( IRONGATE_CONF | \
				((dev)<<11) | \
				((fun)<<8) | \
				(reg) )

#घोषणा IRONGATE0		((Irongate0 *) IGCSR(0, 0, 0))
#घोषणा IRONGATE1		((Irongate1 *) IGCSR(1, 0, 0))

/*
 * Data काष्ठाure क्रम handling IRONGATE machine checks:
 * This is the standard OSF logout frame
 */

#घोषणा SCB_Q_SYSERR	0x620			/* OSF definitions */
#घोषणा SCB_Q_PROCERR	0x630
#घोषणा SCB_Q_SYSMCHK	0x660
#घोषणा SCB_Q_PROCMCHK	0x670

काष्ठा el_IRONGATE_sysdata_mcheck अणु
	__u32 FrameSize;                 /* Bytes, including this field */
	__u32 FrameFlags;                /* <31> = Retry, <30> = Second Error */
	__u32 CpuOffset;                 /* Offset to CPU-specअगरic पूर्णांकo */
	__u32 SystemOffset;              /* Offset to प्रणाली-specअगरic info */
	__u32 MCHK_Code;
	__u32 MCHK_Frame_Rev;
	__u64 I_STAT;
	__u64 DC_STAT;
	__u64 C_ADDR;
	__u64 DC1_SYNDROME;
	__u64 DC0_SYNDROME;
	__u64 C_STAT;
	__u64 C_STS;
	__u64 RESERVED0;
	__u64 EXC_ADDR;
	__u64 IER_CM;
	__u64 ISUM;
	__u64 MM_STAT;
	__u64 PAL_BASE;
	__u64 I_CTL;
	__u64 PCTX;
पूर्ण;


#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions:
 *
 * IRONGATE (AMD-751) PCI/memory support chip क्रम the EV6 (21264) and
 * K7 can only use linear accesses to get at PCI memory and I/O spaces.
 */

/*
 * Memory functions.  All accesses are करोne through linear space.
 */

__EXTERN_INLINE व्योम __iomem *irongate_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)(addr + IRONGATE_IO);
पूर्ण

बाह्य व्योम __iomem *irongate_ioremap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size);
बाह्य व्योम irongate_iounmap(अस्थिर व्योम __iomem *addr);

__EXTERN_INLINE पूर्णांक irongate_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= IRONGATE_MEM;
पूर्ण

__EXTERN_INLINE पूर्णांक irongate_is_mmio(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)xaddr;
	वापस addr < IRONGATE_IO || addr >= IRONGATE_CONF;
पूर्ण

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX			irongate
#घोषणा irongate_trivial_rw_bw		1
#घोषणा irongate_trivial_rw_lq		1
#घोषणा irongate_trivial_io_bw		1
#घोषणा irongate_trivial_io_lq		1
#घोषणा irongate_trivial_iounmap	0
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_IRONGATE__H__ */
