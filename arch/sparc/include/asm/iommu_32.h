<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* iommu.h: Definitions क्रम the sun4m IOMMU.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */
#अगर_अघोषित _SPARC_IOMMU_H
#घोषणा _SPARC_IOMMU_H

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/bitext.h>

/* The iommu handles all भव to physical address translations
 * that occur between the SBUS and physical memory.  Access by
 * the cpu to IO रेजिस्टरs and similar go over the mbus so are
 * translated by the on chip SRMMU.  The iommu and the srmmu करो
 * not need to have the same translations at all, in fact most
 * of the समय the translations they handle are a disjunct set.
 * Basically the iommu handles all dvma sbus activity.
 */

/* The IOMMU रेजिस्टरs occupy three pages in IO space. */
काष्ठा iommu_regs अणु
	/* First page */
	अस्थिर अचिन्हित दीर्घ control;    /* IOMMU control */
	अस्थिर अचिन्हित दीर्घ base;       /* Physical base of iopte page table */
	अस्थिर अचिन्हित दीर्घ _unused1[3];
	अस्थिर अचिन्हित दीर्घ tlbflush;   /* ग_लिखो only */
	अस्थिर अचिन्हित दीर्घ pageflush;  /* ग_लिखो only */
	अस्थिर अचिन्हित दीर्घ _unused2[1017];
	/* Second page */
	अस्थिर अचिन्हित दीर्घ afsr;       /* Async-fault status रेजिस्टर */
	अस्थिर अचिन्हित दीर्घ afar;       /* Async-fault physical address */
	अस्थिर अचिन्हित दीर्घ _unused3[2];
	अस्थिर अचिन्हित दीर्घ sbuscfg0;   /* SBUS configuration रेजिस्टरs, per-slot */
	अस्थिर अचिन्हित दीर्घ sbuscfg1;
	अस्थिर अचिन्हित दीर्घ sbuscfg2;
	अस्थिर अचिन्हित दीर्घ sbuscfg3;
	अस्थिर अचिन्हित दीर्घ mfsr;       /* Memory-fault status रेजिस्टर */
	अस्थिर अचिन्हित दीर्घ mfar;       /* Memory-fault physical address */
	अस्थिर अचिन्हित दीर्घ _unused4[1014];
	/* Third page */
	अस्थिर अचिन्हित दीर्घ mid;        /* IOMMU module-id */
पूर्ण;

#घोषणा IOMMU_CTRL_IMPL     0xf0000000 /* Implementation */
#घोषणा IOMMU_CTRL_VERS     0x0f000000 /* Version */
#घोषणा IOMMU_CTRL_RNGE     0x0000001c /* Mapping RANGE */
#घोषणा IOMMU_RNGE_16MB     0x00000000 /* 0xff000000 -> 0xffffffff */
#घोषणा IOMMU_RNGE_32MB     0x00000004 /* 0xfe000000 -> 0xffffffff */
#घोषणा IOMMU_RNGE_64MB     0x00000008 /* 0xfc000000 -> 0xffffffff */
#घोषणा IOMMU_RNGE_128MB    0x0000000c /* 0xf8000000 -> 0xffffffff */
#घोषणा IOMMU_RNGE_256MB    0x00000010 /* 0xf0000000 -> 0xffffffff */
#घोषणा IOMMU_RNGE_512MB    0x00000014 /* 0xe0000000 -> 0xffffffff */
#घोषणा IOMMU_RNGE_1GB      0x00000018 /* 0xc0000000 -> 0xffffffff */
#घोषणा IOMMU_RNGE_2GB      0x0000001c /* 0x80000000 -> 0xffffffff */
#घोषणा IOMMU_CTRL_ENAB     0x00000001 /* IOMMU Enable */

#घोषणा IOMMU_AFSR_ERR      0x80000000 /* LE, TO, or BE निश्चितed */
#घोषणा IOMMU_AFSR_LE       0x40000000 /* SBUS reports error after transaction */
#घोषणा IOMMU_AFSR_TO       0x20000000 /* Write access took more than 12.8 us. */
#घोषणा IOMMU_AFSR_BE       0x10000000 /* Write access received error acknowledge */
#घोषणा IOMMU_AFSR_SIZE     0x0e000000 /* Size of transaction causing error */
#घोषणा IOMMU_AFSR_S        0x01000000 /* Sparc was in supervisor mode */
#घोषणा IOMMU_AFSR_RESV     0x00f00000 /* Reserver, क्रमced to 0x8 by hardware */
#घोषणा IOMMU_AFSR_ME       0x00080000 /* Multiple errors occurred */
#घोषणा IOMMU_AFSR_RD       0x00040000 /* A पढ़ो operation was in progress */
#घोषणा IOMMU_AFSR_FAV      0x00020000 /* IOMMU afar has valid contents */

#घोषणा IOMMU_SBCFG_SAB30   0x00010000 /* Phys-address bit 30 when bypass enabled */
#घोषणा IOMMU_SBCFG_BA16    0x00000004 /* Slave supports 16 byte bursts */
#घोषणा IOMMU_SBCFG_BA8     0x00000002 /* Slave supports 8 byte bursts */
#घोषणा IOMMU_SBCFG_BYPASS  0x00000001 /* Bypass IOMMU, treat all addresses
					  produced by this device as pure
					  physical. */

#घोषणा IOMMU_MFSR_ERR      0x80000000 /* One or more of PERR1 or PERR0 */
#घोषणा IOMMU_MFSR_S        0x01000000 /* Sparc was in supervisor mode */
#घोषणा IOMMU_MFSR_CPU      0x00800000 /* CPU transaction caused parity error */
#घोषणा IOMMU_MFSR_ME       0x00080000 /* Multiple parity errors occurred */
#घोषणा IOMMU_MFSR_PERR     0x00006000 /* high bit indicates parity error occurred
					  on the even word of the access, low bit
					  indicated odd word caused the parity error */
#घोषणा IOMMU_MFSR_BM       0x00001000 /* Error occurred जबतक in boot mode */
#घोषणा IOMMU_MFSR_C        0x00000800 /* Address causing error was marked cacheable */
#घोषणा IOMMU_MFSR_RTYP     0x000000f0 /* Memory request transaction type */

#घोषणा IOMMU_MID_SBAE      0x001f0000 /* SBus arbitration enable */
#घोषणा IOMMU_MID_SE        0x00100000 /* Enables SCSI/ETHERNET arbitration */
#घोषणा IOMMU_MID_SB3       0x00080000 /* Enable SBUS device 3 arbitration */
#घोषणा IOMMU_MID_SB2       0x00040000 /* Enable SBUS device 2 arbitration */
#घोषणा IOMMU_MID_SB1       0x00020000 /* Enable SBUS device 1 arbitration */
#घोषणा IOMMU_MID_SB0       0x00010000 /* Enable SBUS device 0 arbitration */
#घोषणा IOMMU_MID_MID       0x0000000f /* Module-id, hardcoded to 0x8 */

/* The क्रमmat of an iopte in the page tables */
#घोषणा IOPTE_PAGE          0x07ffff00 /* Physical page number (PA[30:12]) */
#घोषणा IOPTE_CACHE         0x00000080 /* Cached (in vme IOCACHE or Viking/MXCC) */
#घोषणा IOPTE_WRITE         0x00000004 /* Writeable */
#घोषणा IOPTE_VALID         0x00000002 /* IOPTE is valid */
#घोषणा IOPTE_WAZ           0x00000001 /* Write as zeros */

काष्ठा iommu_काष्ठा अणु
	काष्ठा iommu_regs __iomem *regs;
	iopte_t *page_table;
	/* For convenience */
	अचिन्हित दीर्घ start; /* First managed भव address */
	अचिन्हित दीर्घ end;   /* Last managed भव address */

	काष्ठा bit_map usemap;
पूर्ण;

अटल अंतरभूत व्योम iommu_invalidate(काष्ठा iommu_regs __iomem *regs)
अणु
	sbus_ग_लिखोl(0, &regs->tlbflush);
पूर्ण

अटल अंतरभूत व्योम iommu_invalidate_page(काष्ठा iommu_regs __iomem *regs, अचिन्हित दीर्घ ba)
अणु
	sbus_ग_लिखोl(ba & PAGE_MASK, &regs->pageflush);
पूर्ण

#पूर्ण_अगर /* !(_SPARC_IOMMU_H) */
