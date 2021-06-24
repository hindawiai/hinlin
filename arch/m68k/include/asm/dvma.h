<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-m68k/dma.h
 *
 * Copyright 1995 (C) David S. Miller (davem@caip.rutgers.edu)
 *
 * Hacked to fit Sun3x needs by Thomas Bogenकरोerfer
 */

#अगर_अघोषित __M68K_DVMA_H
#घोषणा __M68K_DVMA_H


#घोषणा DVMA_PAGE_SHIFT	13
#घोषणा DVMA_PAGE_SIZE	(1UL << DVMA_PAGE_SHIFT)
#घोषणा DVMA_PAGE_MASK	(~(DVMA_PAGE_SIZE-1))
#घोषणा DVMA_PAGE_ALIGN(addr)	ALIGN(addr, DVMA_PAGE_SIZE)

बाह्य व्योम dvma_init(व्योम);
बाह्य पूर्णांक dvma_map_iommu(अचिन्हित दीर्घ kaddr, अचिन्हित दीर्घ baddr,
			  पूर्णांक len);

#घोषणा dvma_दो_स्मृति(x) dvma_दो_स्मृति_align(x, 0)
#घोषणा dvma_map(x, y) dvma_map_align(x, y, 0)
#घोषणा dvma_map_vme(x, y) (dvma_map(x, y) & 0xfffff)
#घोषणा dvma_map_align_vme(x, y, z) (dvma_map_align (x, y, z) & 0xfffff)
बाह्य अचिन्हित दीर्घ dvma_map_align(अचिन्हित दीर्घ kaddr, पूर्णांक len,
			    पूर्णांक align);
बाह्य व्योम *dvma_दो_स्मृति_align(अचिन्हित दीर्घ len, अचिन्हित दीर्घ align);

बाह्य व्योम dvma_unmap(व्योम *baddr);
बाह्य व्योम dvma_मुक्त(व्योम *vaddr);


#अगर_घोषित CONFIG_SUN3
/* sun3 dvma page support */

/* memory and pmegs potentially reserved क्रम dvma */
#घोषणा DVMA_PMEG_START 10
#घोषणा DVMA_PMEG_END 16
#घोषणा DVMA_START 0xf00000
#घोषणा DVMA_END 0xfe0000
#घोषणा DVMA_SIZE (DVMA_END-DVMA_START)
#घोषणा IOMMU_TOTAL_ENTRIES 128
#घोषणा IOMMU_ENTRIES 120

/* empirical kludge -- dvma regions only seem to work right on 0x10000
   byte boundaries */
#घोषणा DVMA_REGION_SIZE 0x10000
#घोषणा DVMA_ALIGN(addr) (((addr)+DVMA_REGION_SIZE-1) & \
                         ~(DVMA_REGION_SIZE-1))

/* virt <-> phys conversions */
#घोषणा dvma_vtop(x) ((अचिन्हित दीर्घ)(x) & 0xffffff)
#घोषणा dvma_ptov(x) ((अचिन्हित दीर्घ)(x) | 0xf000000)
#घोषणा dvma_vtovme(x) ((अचिन्हित दीर्घ)(x) & 0x00fffff)
#घोषणा dvma_vmetov(x) ((अचिन्हित दीर्घ)(x) | 0xff00000)
#घोषणा dvma_vtob(x) dvma_vtop(x)
#घोषणा dvma_btov(x) dvma_ptov(x)

अटल अंतरभूत पूर्णांक dvma_map_cpu(अचिन्हित दीर्घ kaddr, अचिन्हित दीर्घ vaddr,
			       पूर्णांक len)
अणु
	वापस 0;
पूर्ण

#अन्यथा /* Sun3x */

/* sun3x dvma page support */

#घोषणा DVMA_START 0x0
#घोषणा DVMA_END 0xf00000
#घोषणा DVMA_SIZE (DVMA_END-DVMA_START)
#घोषणा IOMMU_TOTAL_ENTRIES	   2048
/* the prom takes the top meg */
#घोषणा IOMMU_ENTRIES              (IOMMU_TOTAL_ENTRIES - 0x80)

#घोषणा dvma_vtob(x) ((अचिन्हित दीर्घ)(x) & 0x00ffffff)
#घोषणा dvma_btov(x) ((अचिन्हित दीर्घ)(x) | 0xff000000)

बाह्य पूर्णांक dvma_map_cpu(अचिन्हित दीर्घ kaddr, अचिन्हित दीर्घ vaddr, पूर्णांक len);



/* everything below this line is specअगरic to dma used क्रम the onboard
   ESP scsi on sun3x */

/* Structure to describe the current status of DMA रेजिस्टरs on the Sparc */
काष्ठा sparc_dma_रेजिस्टरs अणु
  __अस्थिर__ अचिन्हित दीर्घ cond_reg;	/* DMA condition रेजिस्टर */
  __अस्थिर__ अचिन्हित दीर्घ st_addr;	/* Start address of this transfer */
  __अस्थिर__ अचिन्हित दीर्घ  cnt;	/* How many bytes to transfer */
  __अस्थिर__ अचिन्हित दीर्घ dma_test;	/* DMA test रेजिस्टर */
पूर्ण;

/* DVMA chip revisions */
क्रमागत dvma_rev अणु
	dvmarev0,
	dvmaesc1,
	dvmarev1,
	dvmarev2,
	dvmarev3,
	dvmarevplus,
	dvmahme
पूर्ण;

#घोषणा DMA_HASCOUNT(rev)  ((rev)==dvmaesc1)

/* Linux DMA inक्रमmation काष्ठाure, filled during probe. */
काष्ठा Linux_SBus_DMA अणु
	काष्ठा Linux_SBus_DMA *next;
	काष्ठा linux_sbus_device *SBus_dev;
	काष्ठा sparc_dma_रेजिस्टरs *regs;

	/* Status, misc info */
	पूर्णांक node;                /* Prom node क्रम this DMA device */
	पूर्णांक running;             /* Are we करोing DMA now? */
	पूर्णांक allocated;           /* Are we "owned" by anyone yet? */

	/* Transfer inक्रमmation. */
	अचिन्हित दीर्घ addr;      /* Start address of current transfer */
	पूर्णांक nbytes;              /* Size of current transfer */
	पूर्णांक realbytes;           /* For splitting up large transfers, etc. */

	/* DMA revision */
	क्रमागत dvma_rev revision;
पूर्ण;

बाह्य काष्ठा Linux_SBus_DMA *dma_chain;

/* Broken hardware... */
#घोषणा DMA_ISBROKEN(dma)    ((dma)->revision == dvmarev1)
#घोषणा DMA_ISESC1(dma)      ((dma)->revision == dvmaesc1)

/* Fields in the cond_reg रेजिस्टर */
/* First, the version identअगरication bits */
#घोषणा DMA_DEVICE_ID    0xf0000000        /* Device identअगरication bits */
#घोषणा DMA_VERS0        0x00000000        /* Sunray DMA version */
#घोषणा DMA_ESCV1        0x40000000        /* DMA ESC Version 1 */
#घोषणा DMA_VERS1        0x80000000        /* DMA rev 1 */
#घोषणा DMA_VERS2        0xa0000000        /* DMA rev 2 */
#घोषणा DMA_VERHME       0xb0000000        /* DMA hme gate array */
#घोषणा DMA_VERSPLUS     0x90000000        /* DMA rev 1 PLUS */

#घोषणा DMA_HNDL_INTR    0x00000001        /* An IRQ needs to be handled */
#घोषणा DMA_HNDL_ERROR   0x00000002        /* We need to take an error */
#घोषणा DMA_FIFO_ISDRAIN 0x0000000c        /* The DMA FIFO is draining */
#घोषणा DMA_INT_ENAB     0x00000010        /* Turn on पूर्णांकerrupts */
#घोषणा DMA_FIFO_INV     0x00000020        /* Invalidate the FIFO */
#घोषणा DMA_ACC_SZ_ERR   0x00000040        /* The access size was bad */
#घोषणा DMA_FIFO_STDRAIN 0x00000040        /* DMA_VERS1 Drain the FIFO */
#घोषणा DMA_RST_SCSI     0x00000080        /* Reset the SCSI controller */
#घोषणा DMA_RST_ENET     DMA_RST_SCSI      /* Reset the ENET controller */
#घोषणा DMA_ST_WRITE     0x00000100        /* ग_लिखो from device to memory */
#घोषणा DMA_ENABLE       0x00000200        /* Fire up DMA, handle requests */
#घोषणा DMA_PEND_READ    0x00000400        /* DMA_VERS1/0/PLUS Pending Read */
#घोषणा DMA_ESC_BURST    0x00000800        /* 1=16byte 0=32byte */
#घोषणा DMA_READ_AHEAD   0x00001800        /* DMA पढ़ो ahead partial दीर्घword */
#घोषणा DMA_DSBL_RD_DRN  0x00001000        /* No EC drain on slave पढ़ोs */
#घोषणा DMA_BCNT_ENAB    0x00002000        /* If on, use the byte counter */
#घोषणा DMA_TERM_CNTR    0x00004000        /* Terminal counter */
#घोषणा DMA_CSR_DISAB    0x00010000        /* No FIFO drains during csr */
#घोषणा DMA_SCSI_DISAB   0x00020000        /* No FIFO drains during reg */
#घोषणा DMA_DSBL_WR_INV  0x00020000        /* No EC inval. on slave ग_लिखोs */
#घोषणा DMA_ADD_ENABLE   0x00040000        /* Special ESC DVMA optimization */
#घोषणा DMA_E_BURST8	 0x00040000	   /* ENET: SBUS r/w burst size */
#घोषणा DMA_BRST_SZ      0x000c0000        /* SCSI: SBUS r/w burst size */
#घोषणा DMA_BRST64       0x00080000        /* SCSI: 64byte bursts (HME on UltraSparc only) */
#घोषणा DMA_BRST32       0x00040000        /* SCSI: 32byte bursts */
#घोषणा DMA_BRST16       0x00000000        /* SCSI: 16byte bursts */
#घोषणा DMA_BRST0        0x00080000        /* SCSI: no bursts (non-HME gate arrays) */
#घोषणा DMA_ADDR_DISAB   0x00100000        /* No FIFO drains during addr */
#घोषणा DMA_2CLKS        0x00200000        /* Each transfer = 2 घड़ी ticks */
#घोषणा DMA_3CLKS        0x00400000        /* Each transfer = 3 घड़ी ticks */
#घोषणा DMA_EN_ENETAUI   DMA_3CLKS         /* Put lance पूर्णांकo AUI-cable mode */
#घोषणा DMA_CNTR_DISAB   0x00800000        /* No IRQ when DMA_TERM_CNTR set */
#घोषणा DMA_AUTO_NADDR   0x01000000        /* Use "auto nxt addr" feature */
#घोषणा DMA_SCSI_ON      0x02000000        /* Enable SCSI dma */
#घोषणा DMA_PARITY_OFF   0x02000000        /* HME: disable parity checking */
#घोषणा DMA_LOADED_ADDR  0x04000000        /* Address has been loaded */
#घोषणा DMA_LOADED_NADDR 0x08000000        /* Next address has been loaded */

/* Values describing the burst-size property from the PROM */
#घोषणा DMA_BURST1       0x01
#घोषणा DMA_BURST2       0x02
#घोषणा DMA_BURST4       0x04
#घोषणा DMA_BURST8       0x08
#घोषणा DMA_BURST16      0x10
#घोषणा DMA_BURST32      0x20
#घोषणा DMA_BURST64      0x40
#घोषणा DMA_BURSTBITS    0x7f

/* Determine highest possible final transfer address given a base */
#घोषणा DMA_MAXEND(addr) (0x01000000UL-(((अचिन्हित दीर्घ)(addr))&0x00ffffffUL))

/* Yes, I hack a lot of elisp in my spare समय... */
#घोषणा DMA_ERROR_P(regs)  ((((regs)->cond_reg) & DMA_HNDL_ERROR))
#घोषणा DMA_IRQ_P(regs)    ((((regs)->cond_reg) & (DMA_HNDL_INTR | DMA_HNDL_ERROR)))
#घोषणा DMA_WRITE_P(regs)  ((((regs)->cond_reg) & DMA_ST_WRITE))
#घोषणा DMA_OFF(regs)      ((((regs)->cond_reg) &= (~DMA_ENABLE)))
#घोषणा DMA_INTSOFF(regs)  ((((regs)->cond_reg) &= (~DMA_INT_ENAB)))
#घोषणा DMA_INTSON(regs)   ((((regs)->cond_reg) |= (DMA_INT_ENAB)))
#घोषणा DMA_PUNTFIFO(regs) ((((regs)->cond_reg) |= DMA_FIFO_INV))
#घोषणा DMA_SETSTART(regs, addr)  ((((regs)->st_addr) = (अक्षर *) addr))
#घोषणा DMA_BEGINDMA_W(regs) \
        ((((regs)->cond_reg |= (DMA_ST_WRITE|DMA_ENABLE|DMA_INT_ENAB))))
#घोषणा DMA_BEGINDMA_R(regs) \
        ((((regs)->cond_reg |= ((DMA_ENABLE|DMA_INT_ENAB)&(~DMA_ST_WRITE)))))

/* For certain DMA chips, we need to disable पूर्णांकs upon irq entry
 * and turn them back on when we are करोne.  So in any ESP पूर्णांकerrupt
 * handler you *must* call DMA_IRQ_ENTRY upon entry and DMA_IRQ_EXIT
 * when leaving the handler.  You have been warned...
 */
#घोषणा DMA_IRQ_ENTRY(dma, dregs) करो अणु \
        अगर(DMA_ISBROKEN(dma)) DMA_INTSOFF(dregs); \
   पूर्ण जबतक (0)

#घोषणा DMA_IRQ_EXIT(dma, dregs) करो अणु \
	अगर(DMA_ISBROKEN(dma)) DMA_INTSON(dregs); \
   पूर्ण जबतक(0)

/* Reset the friggin' thing... */
#घोषणा DMA_RESET(dma) करो अणु \
	काष्ठा sparc_dma_रेजिस्टरs *regs = dma->regs;                      \
	/* Let the current FIFO drain itself */                            \
	sparc_dma_छोड़ो(regs, (DMA_FIFO_ISDRAIN));                         \
	/* Reset the logic */                                              \
	regs->cond_reg |= (DMA_RST_SCSI);     /* निश्चित */                 \
	__delay(400);                         /* let the bits set ;) */    \
	regs->cond_reg &= ~(DMA_RST_SCSI);    /* de-निश्चित */              \
	sparc_dma_enable_पूर्णांकerrupts(regs);    /* Re-enable पूर्णांकerrupts */   \
	/* Enable FAST transfers अगर available */                           \
	अगर(dma->revision>dvmarev1) regs->cond_reg |= DMA_3CLKS;            \
	dma->running = 0;                                                  \
पूर्ण जबतक(0)


#पूर्ण_अगर /* !CONFIG_SUN3 */

#पूर्ण_अगर /* !(__M68K_DVMA_H) */
