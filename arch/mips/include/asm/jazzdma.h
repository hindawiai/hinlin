<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Helpfile क्रम jazzdma.c -- Mips Jazz R4030 DMA controller support
 */
#अगर_अघोषित _ASM_JAZZDMA_H
#घोषणा _ASM_JAZZDMA_H

/*
 * Prototypes and macros
 */
बाह्य अचिन्हित दीर्घ vdma_alloc(अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ size);
बाह्य पूर्णांक vdma_मुक्त(अचिन्हित दीर्घ laddr);
बाह्य अचिन्हित दीर्घ vdma_phys2log(अचिन्हित दीर्घ paddr);
बाह्य अचिन्हित दीर्घ vdma_log2phys(अचिन्हित दीर्घ laddr);
बाह्य व्योम vdma_stats(व्योम);		/* क्रम debugging only */

बाह्य व्योम vdma_enable(पूर्णांक channel);
बाह्य व्योम vdma_disable(पूर्णांक channel);
बाह्य व्योम vdma_set_mode(पूर्णांक channel, पूर्णांक mode);
बाह्य व्योम vdma_set_addr(पूर्णांक channel, दीर्घ addr);
बाह्य व्योम vdma_set_count(पूर्णांक channel, पूर्णांक count);
बाह्य पूर्णांक vdma_get_residue(पूर्णांक channel);
बाह्य पूर्णांक vdma_get_enable(पूर्णांक channel);

/*
 * some definitions used by the driver functions
 */
#घोषणा VDMA_PAGESIZE		4096
#घोषणा VDMA_PGTBL_ENTRIES	4096
#घोषणा VDMA_PGTBL_SIZE		(माप(VDMA_PGTBL_ENTRY) * VDMA_PGTBL_ENTRIES)
#घोषणा VDMA_PAGE_EMPTY		0xff000000

/*
 * Macros to get page no. and offset of a given address
 * Note that VDMA_PAGE() works क्रम physical addresses only
 */
#घोषणा VDMA_PAGE(a)		((अचिन्हित पूर्णांक)(a) >> 12)
#घोषणा VDMA_OFFSET(a)		((अचिन्हित पूर्णांक)(a) & (VDMA_PAGESIZE-1))

/*
 * VDMA pagetable entry description
 */
प्रकार अस्थिर काष्ठा VDMA_PGTBL_ENTRY अणु
	अचिन्हित पूर्णांक frame;		/* physical frame no. */
	अचिन्हित पूर्णांक owner;		/* owner of this entry (0=मुक्त) */
पूर्ण VDMA_PGTBL_ENTRY;


/*
 * DMA channel control रेजिस्टरs
 * in the R4030 MCT_ADR chip
 */
#घोषणा JAZZ_R4030_CHNL_MODE	0xE0000100	/* 8 DMA Channel Mode Registers, */
						/* 0xE0000100,120,140... */
#घोषणा JAZZ_R4030_CHNL_ENABLE	0xE0000108	/* 8 DMA Channel Enable Regs, */
						/* 0xE0000108,128,148... */
#घोषणा JAZZ_R4030_CHNL_COUNT	0xE0000110	/* 8 DMA Channel Byte Cnt Regs, */
						/* 0xE0000110,130,150... */
#घोषणा JAZZ_R4030_CHNL_ADDR	0xE0000118	/* 8 DMA Channel Address Regs, */
						/* 0xE0000118,138,158... */

/* channel enable रेजिस्टर bits */

#घोषणा R4030_CHNL_ENABLE	 (1<<0)
#घोषणा R4030_CHNL_WRITE	 (1<<1)
#घोषणा R4030_TC_INTR		 (1<<8)
#घोषणा R4030_MEM_INTR		 (1<<9)
#घोषणा R4030_ADDR_INTR		 (1<<10)

/*
 * Channel mode रेजिस्टर bits
 */
#घोषणा R4030_MODE_ATIME_40	 (0) /* device access समय on remote bus */
#घोषणा R4030_MODE_ATIME_80	 (1)
#घोषणा R4030_MODE_ATIME_120	 (2)
#घोषणा R4030_MODE_ATIME_160	 (3)
#घोषणा R4030_MODE_ATIME_200	 (4)
#घोषणा R4030_MODE_ATIME_240	 (5)
#घोषणा R4030_MODE_ATIME_280	 (6)
#घोषणा R4030_MODE_ATIME_320	 (7)
#घोषणा R4030_MODE_WIDTH_8	 (1<<3) /* device data bus width */
#घोषणा R4030_MODE_WIDTH_16	 (2<<3)
#घोषणा R4030_MODE_WIDTH_32	 (3<<3)
#घोषणा R4030_MODE_INTR_EN	 (1<<5)
#घोषणा R4030_MODE_BURST	 (1<<6) /* Rev. 2 only */
#घोषणा R4030_MODE_FAST_ACK	 (1<<7) /* Rev. 2 only */

#पूर्ण_अगर /* _ASM_JAZZDMA_H */
