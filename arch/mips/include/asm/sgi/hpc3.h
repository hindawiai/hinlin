<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * hpc3.h: Definitions क्रम SGI HPC3 controller
 *
 * Copyright (C) 1996 David S. Miller
 * Copyright (C) 1998 Ralf Baechle
 */

#अगर_अघोषित _SGI_HPC3_H
#घोषणा _SGI_HPC3_H

#समावेश <linux/types.h>
#समावेश <यंत्र/page.h>

/* An HPC DMA descriptor. */
काष्ठा hpc_dma_desc अणु
	u32 pbuf;	/* physical address of data buffer */
	u32 cntinfo;	/* counter and info bits */
#घोषणा HPCDMA_EOX	0x80000000 /* last desc in chain क्रम tx */
#घोषणा HPCDMA_EOR	0x80000000 /* last desc in chain क्रम rx */
#घोषणा HPCDMA_EOXP	0x40000000 /* end of packet क्रम tx */
#घोषणा HPCDMA_EORP	0x40000000 /* end of packet क्रम rx */
#घोषणा HPCDMA_XIE	0x20000000 /* irq generated when at end of this desc */
#घोषणा HPCDMA_XIU	0x01000000 /* Tx buffer in use by CPU. */
#घोषणा HPCDMA_EIPC	0x00ff0000 /* SEEQ ethernet special xternal bytecount */
#घोषणा HPCDMA_ETXD	0x00008000 /* set to one by HPC when packet tx'd */
#घोषणा HPCDMA_OWN	0x00004000 /* Denotes ring buffer ownership on rx */
#घोषणा HPCDMA_BCNT	0x00003fff /* size in bytes of this dma buffer */

	u32 pnext;	/* paddr of next hpc_dma_desc अगर any */
पूर्ण;

/* The set of regs क्रम each HPC3 PBUS DMA channel. */
काष्ठा hpc3_pbus_dmacregs अणु
	अस्थिर u32 pbdma_bptr;	/* pbus dma channel buffer ptr */
	अस्थिर u32 pbdma_dptr;	/* pbus dma channel desc ptr */
	u32 _unused0[0x1000/4 - 2];	/* padding */
	अस्थिर u32 pbdma_ctrl;	/* pbus dma channel control रेजिस्टर has
					 * completely dअगरferent meaning क्रम पढ़ो
					 * compared with ग_लिखो */
	/* पढ़ो */
#घोषणा HPC3_PDMACTRL_INT	0x00000001 /* पूर्णांकerrupt (cleared after पढ़ो) */
#घोषणा HPC3_PDMACTRL_ISACT	0x00000002 /* channel active */
	/* ग_लिखो */
#घोषणा HPC3_PDMACTRL_SEL	0x00000002 /* little endian transfer */
#घोषणा HPC3_PDMACTRL_RCV	0x00000004 /* direction is receive */
#घोषणा HPC3_PDMACTRL_FLSH	0x00000008 /* enable flush क्रम receive DMA */
#घोषणा HPC3_PDMACTRL_ACT	0x00000010 /* start dma transfer */
#घोषणा HPC3_PDMACTRL_LD	0x00000020 /* load enable क्रम ACT */
#घोषणा HPC3_PDMACTRL_RT	0x00000040 /* Use realसमय GIO bus servicing */
#घोषणा HPC3_PDMACTRL_HW	0x0000ff00 /* DMA High-water mark */
#घोषणा HPC3_PDMACTRL_FB	0x003f0000 /* Ptr to beginning of fअगरo */
#घोषणा HPC3_PDMACTRL_FE	0x3f000000 /* Ptr to end of fअगरo */

	u32 _unused1[0x1000/4 - 1];	/* padding */
पूर्ण;

/* The HPC3 SCSI रेजिस्टरs, this करोes not include बाह्यal ones. */
काष्ठा hpc3_scsiregs अणु
	अस्थिर u32 cbptr;	/* current dma buffer ptr, diagnostic use only */
	अस्थिर u32 ndptr;	/* next dma descriptor ptr */
	u32 _unused0[0x1000/4 - 2];	/* padding */
	अस्थिर u32 bcd;	/* byte count info */
#घोषणा HPC3_SBCD_BCNTMSK 0x00003fff /* bytes to transfer from/to memory */
#घोषणा HPC3_SBCD_XIE	  0x00004000 /* Send IRQ when करोne with cur buf */
#घोषणा HPC3_SBCD_EOX	  0x00008000 /* Indicates this is last buf in chain */

	अस्थिर u32 ctrl;    /* control रेजिस्टर */
#घोषणा HPC3_SCTRL_IRQ	  0x01 /* IRQ निश्चितed, either dma करोne or parity */
#घोषणा HPC3_SCTRL_ENDIAN 0x02 /* DMA endian mode, 0=big 1=little */
#घोषणा HPC3_SCTRL_सूची	  0x04 /* DMA direction, 1=dev2mem 0=mem2dev */
#घोषणा HPC3_SCTRL_FLUSH  0x08 /* Tells HPC3 to flush scsi fअगरos */
#घोषणा HPC3_SCTRL_ACTIVE 0x10 /* SCSI DMA channel is active */
#घोषणा HPC3_SCTRL_AMASK  0x20 /* DMA active inhibits PIO */
#घोषणा HPC3_SCTRL_CRESET 0x40 /* Resets dma channel and बाह्यal controller */
#घोषणा HPC3_SCTRL_PERR	  0x80 /* Bad parity on HPC3 अगरace to scsi controller */

	अस्थिर u32 gfptr;	/* current GIO fअगरo ptr */
	अस्थिर u32 dfptr;	/* current device fअगरo ptr */
	अस्थिर u32 dconfig;	/* DMA configuration रेजिस्टर */
#घोषणा HPC3_SDCFG_HCLK 0x00001 /* Enable DMA half घड़ी mode */
#घोषणा HPC3_SDCFG_D1	0x00006 /* Cycles to spend in D1 state */
#घोषणा HPC3_SDCFG_D2	0x00038 /* Cycles to spend in D2 state */
#घोषणा HPC3_SDCFG_D3	0x001c0 /* Cycles to spend in D3 state */
#घोषणा HPC3_SDCFG_HWAT 0x00e00 /* DMA high water mark */
#घोषणा HPC3_SDCFG_HW	0x01000 /* Enable 16-bit halfword DMA accesses to scsi */
#घोषणा HPC3_SDCFG_SWAP 0x02000 /* Byte swap all DMA accesses */
#घोषणा HPC3_SDCFG_EPAR 0x04000 /* Enable parity checking क्रम DMA */
#घोषणा HPC3_SDCFG_POLL 0x08000 /* hd_dreq polarity control */
#घोषणा HPC3_SDCFG_ERLY 0x30000 /* hd_dreq behavior control bits */

	अस्थिर u32 pconfig;	/* PIO configuration रेजिस्टर */
#घोषणा HPC3_SPCFG_P3	0x0003 /* Cycles to spend in P3 state */
#घोषणा HPC3_SPCFG_P2W	0x001c /* Cycles to spend in P2 state क्रम ग_लिखोs */
#घोषणा HPC3_SPCFG_P2R	0x01e0 /* Cycles to spend in P2 state क्रम पढ़ोs */
#घोषणा HPC3_SPCFG_P1	0x0e00 /* Cycles to spend in P1 state */
#घोषणा HPC3_SPCFG_HW	0x1000 /* Enable 16-bit halfword PIO accesses to scsi */
#घोषणा HPC3_SPCFG_SWAP 0x2000 /* Byte swap all PIO accesses */
#घोषणा HPC3_SPCFG_EPAR 0x4000 /* Enable parity checking क्रम PIO */
#घोषणा HPC3_SPCFG_FUJI 0x8000 /* Fujitsu scsi controller mode क्रम faster dma/pio */

	u32 _unused1[0x1000/4 - 6];	/* padding */
पूर्ण;

/* SEEQ ethernet HPC3 रेजिस्टरs, only one seeq per HPC3. */
काष्ठा hpc3_ethregs अणु
	/* Receiver रेजिस्टरs. */
	अस्थिर u32 rx_cbptr;	 /* current dma buffer ptr, diagnostic use only */
	अस्थिर u32 rx_ndptr;	 /* next dma descriptor ptr */
	u32 _unused0[0x1000/4 - 2];	/* padding */
	अस्थिर u32 rx_bcd;	/* byte count info */
#घोषणा HPC3_ERXBCD_BCNTMSK 0x00003fff /* bytes to be sent to memory */
#घोषणा HPC3_ERXBCD_XIE	    0x20000000 /* HPC3 पूर्णांकerrupts cpu at end of this buf */
#घोषणा HPC3_ERXBCD_EOX	    0x80000000 /* flags this as end of descriptor chain */

	अस्थिर u32 rx_ctrl;	/* control रेजिस्टर */
#घोषणा HPC3_ERXCTRL_STAT50 0x0000003f /* Receive status reg bits of Seeq8003 */
#घोषणा HPC3_ERXCTRL_STAT6  0x00000040 /* Rकरोnly irq status */
#घोषणा HPC3_ERXCTRL_STAT7  0x00000080 /* Rकरोnlt old/new status bit from Seeq */
#घोषणा HPC3_ERXCTRL_ENDIAN 0x00000100 /* Endian क्रम dma channel, little=1 big=0 */
#घोषणा HPC3_ERXCTRL_ACTIVE 0x00000200 /* Tells अगर DMA transfer is in progress */
#घोषणा HPC3_ERXCTRL_AMASK  0x00000400 /* Tells अगर ACTIVE inhibits PIO's to hpc3 */
#घोषणा HPC3_ERXCTRL_RBO    0x00000800 /* Receive buffer overflow अगर set to 1 */

	अस्थिर u32 rx_gfptr;	/* current GIO fअगरo ptr */
	अस्थिर u32 rx_dfptr;	/* current device fअगरo ptr */
	u32 _unused1;		/* padding */
	अस्थिर u32 reset;	/* reset रेजिस्टर */
#घोषणा HPC3_ERST_CRESET 0x1	/* Reset dma channel and बाह्यal controller */
#घोषणा HPC3_ERST_CLRIRQ 0x2	/* Clear channel पूर्णांकerrupt */
#घोषणा HPC3_ERST_LBACK	 0x4	/* Enable diagnostic loopback mode of Seeq8003 */

	अस्थिर u32 dconfig;	 /* DMA configuration रेजिस्टर */
#घोषणा HPC3_EDCFG_D1	 0x0000f /* Cycles to spend in D1 state क्रम PIO */
#घोषणा HPC3_EDCFG_D2	 0x000f0 /* Cycles to spend in D2 state क्रम PIO */
#घोषणा HPC3_EDCFG_D3	 0x00f00 /* Cycles to spend in D3 state क्रम PIO */
#घोषणा HPC3_EDCFG_WCTRL 0x01000 /* Enable ग_लिखोs of desc पूर्णांकo ex ctrl port */
#घोषणा HPC3_EDCFG_FRXDC 0x02000 /* Clear eop stat bits upon rxdc, hw seeq fix */
#घोषणा HPC3_EDCFG_FEOP	 0x04000 /* Bad packet marker समयout enable */
#घोषणा HPC3_EDCFG_FIRQ	 0x08000 /* Another bad packet समयout enable */
#घोषणा HPC3_EDCFG_PTO	 0x30000 /* Programmed समयout value क्रम above two */

	अस्थिर u32 pconfig;	/* PIO configuration रेजिस्टर */
#घोषणा HPC3_EPCFG_P1	 0x000f /* Cycles to spend in P1 state क्रम PIO */
#घोषणा HPC3_EPCFG_P2	 0x00f0 /* Cycles to spend in P2 state क्रम PIO */
#घोषणा HPC3_EPCFG_P3	 0x0f00 /* Cycles to spend in P3 state क्रम PIO */
#घोषणा HPC3_EPCFG_TST	 0x1000 /* Diagnostic ram test feature bit */

	u32 _unused2[0x1000/4 - 8];	/* padding */

	/* Transmitter रेजिस्टरs. */
	अस्थिर u32 tx_cbptr;	/* current dma buffer ptr, diagnostic use only */
	अस्थिर u32 tx_ndptr;	/* next dma descriptor ptr */
	u32 _unused3[0x1000/4 - 2];	/* padding */
	अस्थिर u32 tx_bcd;		/* byte count info */
#घोषणा HPC3_ETXBCD_BCNTMSK 0x00003fff	/* bytes to be पढ़ो from memory */
#घोषणा HPC3_ETXBCD_ESAMP   0x10000000	/* अगर set, too late to add descriptor */
#घोषणा HPC3_ETXBCD_XIE	    0x20000000	/* Interrupt cpu at end of cur desc */
#घोषणा HPC3_ETXBCD_EOP	    0x40000000	/* Last byte of cur buf is end of packet */
#घोषणा HPC3_ETXBCD_EOX	    0x80000000	/* This buf is the end of desc chain */

	अस्थिर u32 tx_ctrl;		/* control रेजिस्टर */
#घोषणा HPC3_ETXCTRL_STAT30 0x0000000f	/* Rकरोnly copy of seeq tx stat reg */
#घोषणा HPC3_ETXCTRL_STAT4  0x00000010	/* Indicate late collision occurred */
#घोषणा HPC3_ETXCTRL_STAT75 0x000000e0	/* Rकरोnly irq status from seeq */
#घोषणा HPC3_ETXCTRL_ENDIAN 0x00000100	/* DMA channel endian mode, 1=little 0=big */
#घोषणा HPC3_ETXCTRL_ACTIVE 0x00000200	/* DMA tx channel is active */
#घोषणा HPC3_ETXCTRL_AMASK  0x00000400	/* Indicates ACTIVE inhibits PIO's */

	अस्थिर u32 tx_gfptr;		/* current GIO fअगरo ptr */
	अस्थिर u32 tx_dfptr;		/* current device fअगरo ptr */
	u32 _unused4[0x1000/4 - 4];	/* padding */
पूर्ण;

काष्ठा hpc3_regs अणु
	/* First regs क्रम the PBUS 8 dma channels. */
	काष्ठा hpc3_pbus_dmacregs pbdma[8];

	/* Now the HPC scsi रेजिस्टरs, we get two scsi reg sets. */
	काष्ठा hpc3_scsiregs scsi_chan0, scsi_chan1;

	/* The SEEQ hpc3 ethernet dma/control रेजिस्टरs. */
	काष्ठा hpc3_ethregs ethregs;

	/* Here are where the hpc3 fअगरo's can be directly accessed
	 * via PIO accesses.  Under normal operation we never stick
	 * our grubby paws in here so it's just padding. */
	u32 _unused0[0x18000/4];

	/* HPC3 irq status regs.  Due to a peculiar bug you need to
	 * look at two dअगरferent रेजिस्टर addresses to get at all of
	 * the status bits.  The first reg can only reliably report
	 * bits 4:0 of the status, and the second reg can only
	 * reliably report bits 9:5 of the hpc3 irq status.  I told
	 * you it was a peculiar bug. ;-)
	 */
	अस्थिर u32 istat0;		/* Irq status, only bits <4:0> reliable. */
#घोषणा HPC3_ISTAT_PBIMASK	0x0ff	/* irq bits क्रम pbus devs 0 --> 7 */
#घोषणा HPC3_ISTAT_SC0MASK	0x100	/* irq bit क्रम scsi channel 0 */
#घोषणा HPC3_ISTAT_SC1MASK	0x200	/* irq bit क्रम scsi channel 1 */

	अस्थिर u32 gio_misc;		/* GIO misc control bits. */
#घोषणा HPC3_GIOMISC_ERTIME	0x1	/* Enable बाह्यal समयr real समय. */
#घोषणा HPC3_GIOMISC_DENDIAN	0x2	/* dma descriptor endian, 1=lit 0=big */

	u32 eeprom;			/* EEPROM data reg. */
#घोषणा HPC3_EEPROM_EPROT	0x01	/* Protect रेजिस्टर enable */
#घोषणा HPC3_EEPROM_CSEL	0x02	/* Chip select */
#घोषणा HPC3_EEPROM_ECLK	0x04	/* EEPROM घड़ी */
#घोषणा HPC3_EEPROM_DATO	0x08	/* Data out */
#घोषणा HPC3_EEPROM_DATI	0x10	/* Data in */

	अस्थिर u32 istat1;		/* Irq status, only bits <9:5> reliable. */
	अस्थिर u32 bestat;		/* Bus error पूर्णांकerrupt status reg. */
#घोषणा HPC3_BESTAT_BLMASK	0x000ff /* Bus lane where bad parity occurred */
#घोषणा HPC3_BESTAT_CTYPE	0x00100 /* Bus cycle type, 0=PIO 1=DMA */
#घोषणा HPC3_BESTAT_PIDSHIFT	9
#घोषणा HPC3_BESTAT_PIDMASK	0x3f700 /* DMA channel parity identअगरier */

	u32 _unused1[0x14000/4 - 5];	/* padding */

	/* Now direct PIO per-HPC3 peripheral access to बाह्यal regs. */
	अस्थिर u32 scsi0_ext[256];	/* SCSI channel 0 बाह्यal regs */
	u32 _unused2[0x7c00/4];
	अस्थिर u32 scsi1_ext[256];	/* SCSI channel 1 बाह्यal regs */
	u32 _unused3[0x7c00/4];
	अस्थिर u32 eth_ext[320];	/* Ethernet बाह्यal रेजिस्टरs */
	u32 _unused4[0x3b00/4];

	/* Per-peripheral device बाह्यal रेजिस्टरs and DMA/PIO control. */
	अस्थिर u32 pbus_extregs[16][256];
	अस्थिर u32 pbus_dmacfg[8][128];
	/* Cycles to spend in D3 क्रम पढ़ोs */
#घोषणा HPC3_DMACFG_D3R_MASK		0x00000001
#घोषणा HPC3_DMACFG_D3R_SHIFT		0
	/* Cycles to spend in D4 क्रम पढ़ोs */
#घोषणा HPC3_DMACFG_D4R_MASK		0x0000001e
#घोषणा HPC3_DMACFG_D4R_SHIFT		1
	/* Cycles to spend in D5 क्रम पढ़ोs */
#घोषणा HPC3_DMACFG_D5R_MASK		0x000001e0
#घोषणा HPC3_DMACFG_D5R_SHIFT		5
	/* Cycles to spend in D3 क्रम ग_लिखोs */
#घोषणा HPC3_DMACFG_D3W_MASK		0x00000200
#घोषणा HPC3_DMACFG_D3W_SHIFT		9
	/* Cycles to spend in D4 क्रम ग_लिखोs */
#घोषणा HPC3_DMACFG_D4W_MASK		0x00003c00
#घोषणा HPC3_DMACFG_D4W_SHIFT		10
	/* Cycles to spend in D5 क्रम ग_लिखोs */
#घोषणा HPC3_DMACFG_D5W_MASK		0x0003c000
#घोषणा HPC3_DMACFG_D5W_SHIFT		14
	/* Enable 16-bit DMA access mode */
#घोषणा HPC3_DMACFG_DS16		0x00040000
	/* Places halfwords on high 16 bits of bus */
#घोषणा HPC3_DMACFG_EVENHI		0x00080000
	/* Make this device real समय */
#घोषणा HPC3_DMACFG_RTIME		0x00200000
	/* 5 bit burst count क्रम DMA device */
#घोषणा HPC3_DMACFG_BURST_MASK		0x07c00000
#घोषणा HPC3_DMACFG_BURST_SHIFT 22
	/* Use live pbus_dreq unsynchronized संकेत */
#घोषणा HPC3_DMACFG_DRQLIVE		0x08000000
	अस्थिर u32 pbus_piocfg[16][64];
	/* Cycles to spend in P2 state क्रम पढ़ोs */
#घोषणा HPC3_PIOCFG_P2R_MASK		0x00001
#घोषणा HPC3_PIOCFG_P2R_SHIFT		0
	/* Cycles to spend in P3 state क्रम पढ़ोs */
#घोषणा HPC3_PIOCFG_P3R_MASK		0x0001e
#घोषणा HPC3_PIOCFG_P3R_SHIFT		1
	/* Cycles to spend in P4 state क्रम पढ़ोs */
#घोषणा HPC3_PIOCFG_P4R_MASK		0x001e0
#घोषणा HPC3_PIOCFG_P4R_SHIFT		5
	/* Cycles to spend in P2 state क्रम ग_लिखोs */
#घोषणा HPC3_PIOCFG_P2W_MASK		0x00200
#घोषणा HPC3_PIOCFG_P2W_SHIFT		9
	/* Cycles to spend in P3 state क्रम ग_लिखोs */
#घोषणा HPC3_PIOCFG_P3W_MASK		0x03c00
#घोषणा HPC3_PIOCFG_P3W_SHIFT		10
	/* Cycles to spend in P4 state क्रम ग_लिखोs */
#घोषणा HPC3_PIOCFG_P4W_MASK		0x3c000
#घोषणा HPC3_PIOCFG_P4W_SHIFT		14
	/* Enable 16-bit PIO accesses */
#घोषणा HPC3_PIOCFG_DS16		0x40000
	/* Place even address bits in bits <15:8> */
#घोषणा HPC3_PIOCFG_EVENHI		0x80000

	/* PBUS PROM control regs. */
	अस्थिर u32 pbus_promwe;	/* PROM ग_लिखो enable रेजिस्टर */
#घोषणा HPC3_PROM_WENAB 0x1	/* Enable ग_लिखोs to the PROM */

	u32 _unused5[0x0800/4 - 1];
	अस्थिर u32 pbus_promswap;	/* Chip select swap reg */
#घोषणा HPC3_PROM_SWAP	0x1	/* invert GIO addr bit to select prom0 or prom1 */

	u32 _unused6[0x0800/4 - 1];
	अस्थिर u32 pbus_gout; /* PROM general purpose output reg */
#घोषणा HPC3_PROM_STAT	0x1	/* General purpose status bit in gout */

	u32 _unused7[0x1000/4 - 1];
	अस्थिर u32 rtcregs[14];	/* Dallas घड़ी रेजिस्टरs */
	u32 _unused8[50];
	अस्थिर u32 bbram[8192-50-14]; /* Battery backed ram */
पूर्ण;

/*
 * It is possible to have two HPC3's within the address space on
 * one machine, though only having one is more likely on an Indy.
 */
बाह्य काष्ठा hpc3_regs *hpc3c0, *hpc3c1;
#घोषणा HPC3_CHIP0_BASE		0x1fb80000	/* physical */
#घोषणा HPC3_CHIP1_BASE		0x1fb00000	/* physical */

बाह्य व्योम sgihpc_init(व्योम);

#पूर्ण_अगर /* _SGI_HPC3_H */
