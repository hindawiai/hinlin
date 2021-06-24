<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SPARC_DMA_H
#घोषणा _ASM_SPARC_DMA_H

/* These are irrelevant क्रम Sparc DMA, but we leave it in so that
 * things can compile.
 */
#घोषणा MAX_DMA_CHANNELS 8
#घोषणा DMA_MODE_READ    1
#घोषणा DMA_MODE_WRITE   2
#घोषणा MAX_DMA_ADDRESS  (~0UL)

/* Useful स्थिरants */
#घोषणा SIZE_16MB      (16*1024*1024)
#घोषणा SIZE_64K       (64*1024)

/* SBUS DMA controller reg offsets */
#घोषणा DMA_CSR		0x00UL		/* rw  DMA control/status रेजिस्टर    0x00   */
#घोषणा DMA_ADDR	0x04UL		/* rw  DMA transfer address रेजिस्टर  0x04   */
#घोषणा DMA_COUNT	0x08UL		/* rw  DMA transfer count रेजिस्टर    0x08   */
#घोषणा DMA_TEST	0x0cUL		/* rw  DMA test/debug रेजिस्टर        0x0c   */

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
#घोषणा DMA_SCSI_SBUS64  0x00008000        /* HME: Enable 64-bit SBUS mode. */
#घोषणा DMA_CSR_DISAB    0x00010000        /* No FIFO drains during csr */
#घोषणा DMA_SCSI_DISAB   0x00020000        /* No FIFO drains during reg */
#घोषणा DMA_DSBL_WR_INV  0x00020000        /* No EC inval. on slave ग_लिखोs */
#घोषणा DMA_ADD_ENABLE   0x00040000        /* Special ESC DVMA optimization */
#घोषणा DMA_E_BURSTS	 0x000c0000	   /* ENET: SBUS r/w burst mask */
#घोषणा DMA_E_BURST32	 0x00040000	   /* ENET: SBUS 32 byte r/w burst */
#घोषणा DMA_E_BURST16	 0x00000000	   /* ENET: SBUS 16 byte r/w burst */
#घोषणा DMA_BRST_SZ      0x000c0000        /* SCSI: SBUS r/w burst size */
#घोषणा DMA_BRST64       0x000c0000        /* SCSI: 64byte bursts (HME on UltraSparc only) */
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
#घोषणा DMA_RESET_FAS366 0x08000000        /* HME: Assert RESET to FAS366 */

/* Values describing the burst-size property from the PROM */
#घोषणा DMA_BURST1       0x01
#घोषणा DMA_BURST2       0x02
#घोषणा DMA_BURST4       0x04
#घोषणा DMA_BURST8       0x08
#घोषणा DMA_BURST16      0x10
#घोषणा DMA_BURST32      0x20
#घोषणा DMA_BURST64      0x40
#घोषणा DMA_BURSTBITS    0x7f

/* From PCI */

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक isa_dma_bridge_buggy;
#अन्यथा
#घोषणा isa_dma_bridge_buggy 	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARC32
काष्ठा device;

अचिन्हित दीर्घ sparc_dma_alloc_resource(काष्ठा device *dev, माप_प्रकार len);
bool sparc_dma_मुक्त_resource(व्योम *cpu_addr, माप_प्रकार size);
#पूर्ण_अगर

#पूर्ण_अगर /* !(_ASM_SPARC_DMA_H) */
