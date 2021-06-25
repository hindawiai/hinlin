<शैली गुरु>
/*
 * Miscellaneous definitions used to initialise the पूर्णांकerrupt vector table
 * with the machine-specअगरic पूर्णांकerrupt routines.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1997 by Paul M. Antoine.
 * reworked 1998 by Harald Koerfgen.
 * Copyright (C) 2001, 2002, 2003  Maciej W. Rozycki
 */

#अगर_अघोषित __ASM_DEC_INTERRUPTS_H
#घोषणा __ASM_DEC_INTERRUPTS_H

#समावेश <irq.h>
#समावेश <यंत्र/mipsregs.h>


/*
 * The list of possible प्रणाली devices which provide an
 * पूर्णांकerrupt.  Not all devices exist on a given प्रणाली.
 */
#घोषणा DEC_IRQ_CASCADE		0	/* cascade from CSR or I/O ASIC */

/* Ordinary पूर्णांकerrupts */
#घोषणा DEC_IRQ_AB_RECV		1	/* ACCESS.bus receive */
#घोषणा DEC_IRQ_AB_XMIT		2	/* ACCESS.bus transmit */
#घोषणा DEC_IRQ_DZ11		3	/* DZ11 (DC7085) serial */
#घोषणा DEC_IRQ_ASC		4	/* ASC (NCR53C94) SCSI */
#घोषणा DEC_IRQ_FLOPPY		5	/* 82077 FDC */
#घोषणा DEC_IRQ_FPU		6	/* R3k FPU */
#घोषणा DEC_IRQ_HALT		7	/* HALT button or from ACCESS.Bus */
#घोषणा DEC_IRQ_ISDN		8	/* Am79C30A ISDN */
#घोषणा DEC_IRQ_LANCE		9	/* LANCE (Am7990) Ethernet */
#घोषणा DEC_IRQ_BUS		10	/* memory, I/O bus पढ़ो/ग_लिखो errors */
#घोषणा DEC_IRQ_PSU		11	/* घातer supply unit warning */
#घोषणा DEC_IRQ_RTC		12	/* DS1287 RTC */
#घोषणा DEC_IRQ_SCC0		13	/* SCC (Z85C30) serial #0 */
#घोषणा DEC_IRQ_SCC1		14	/* SCC (Z85C30) serial #1 */
#घोषणा DEC_IRQ_SII		15	/* SII (DC7061) SCSI */
#घोषणा DEC_IRQ_TC0		16	/* TURBOchannel slot #0 */
#घोषणा DEC_IRQ_TC1		17	/* TURBOchannel slot #1 */
#घोषणा DEC_IRQ_TC2		18	/* TURBOchannel slot #2 */
#घोषणा DEC_IRQ_TIMER		19	/* ARC periodic समयr */
#घोषणा DEC_IRQ_VIDEO		20	/* framebuffer */

/* I/O ASIC DMA पूर्णांकerrupts */
#घोषणा DEC_IRQ_ASC_MERR	21	/* ASC memory पढ़ो error */
#घोषणा DEC_IRQ_ASC_ERR		22	/* ASC page overrun */
#घोषणा DEC_IRQ_ASC_DMA		23	/* ASC buffer poपूर्णांकer loaded */
#घोषणा DEC_IRQ_FLOPPY_ERR	24	/* FDC error */
#घोषणा DEC_IRQ_ISDN_ERR	25	/* ISDN memory पढ़ो/overrun error */
#घोषणा DEC_IRQ_ISDN_RXDMA	26	/* ISDN recv buffer poपूर्णांकer loaded */
#घोषणा DEC_IRQ_ISDN_TXDMA	27	/* ISDN xmit buffer poपूर्णांकer loaded */
#घोषणा DEC_IRQ_LANCE_MERR	28	/* LANCE memory पढ़ो error */
#घोषणा DEC_IRQ_SCC0A_RXERR	29	/* SCC0A (prपूर्णांकer) receive overrun */
#घोषणा DEC_IRQ_SCC0A_RXDMA	30	/* SCC0A receive half page */
#घोषणा DEC_IRQ_SCC0A_TXERR	31	/* SCC0A xmit memory पढ़ो/overrun */
#घोषणा DEC_IRQ_SCC0A_TXDMA	32	/* SCC0A transmit page end */
#घोषणा DEC_IRQ_AB_RXERR	33	/* ACCESS.bus receive overrun */
#घोषणा DEC_IRQ_AB_RXDMA	34	/* ACCESS.bus receive half page */
#घोषणा DEC_IRQ_AB_TXERR	35	/* ACCESS.bus xmit memory पढ़ो/ovrn */
#घोषणा DEC_IRQ_AB_TXDMA	36	/* ACCESS.bus transmit page end */
#घोषणा DEC_IRQ_SCC1A_RXERR	37	/* SCC1A (modem) receive overrun */
#घोषणा DEC_IRQ_SCC1A_RXDMA	38	/* SCC1A receive half page */
#घोषणा DEC_IRQ_SCC1A_TXERR	39	/* SCC1A xmit memory पढ़ो/overrun */
#घोषणा DEC_IRQ_SCC1A_TXDMA	40	/* SCC1A transmit page end */

/* TC5 & TC6 are भव slots क्रम KN02's onboard devices */
#घोषणा DEC_IRQ_TC5		DEC_IRQ_ASC	/* भव PMAZ-AA */
#घोषणा DEC_IRQ_TC6		DEC_IRQ_LANCE	/* भव PMAD-AA */

#घोषणा DEC_NR_INTS		41


/* Largest of cpu mask_nr tables. */
#घोषणा DEC_MAX_CPU_INTS	6
/* Largest of asic mask_nr tables. */
#घोषणा DEC_MAX_ASIC_INTS	9


/*
 * CPU पूर्णांकerrupt bits common to all प्रणालीs.
 */
#घोषणा DEC_CPU_INR_FPU		7	/* R3k FPU */
#घोषणा DEC_CPU_INR_SW1		1	/* software #1 */
#घोषणा DEC_CPU_INR_SW0		0	/* software #0 */

#घोषणा DEC_CPU_IRQ_BASE	MIPS_CPU_IRQ_BASE	/* first IRQ asचिन्हित to CPU */

#घोषणा DEC_CPU_IRQ_NR(n)	((n) + DEC_CPU_IRQ_BASE)
#घोषणा DEC_CPU_IRQ_MASK(n)	(1 << ((n) + CAUSEB_IP))
#घोषणा DEC_CPU_IRQ_ALL		(0xff << CAUSEB_IP)


#अगर_अघोषित __ASSEMBLY__

/*
 * Interrupt table काष्ठाures to hide dअगरferences between प्रणालीs.
 */
प्रकार जोड़ अणु पूर्णांक i; व्योम *p; पूर्ण पूर्णांक_ptr;
बाह्य पूर्णांक dec_पूर्णांकerrupt[DEC_NR_INTS];
बाह्य पूर्णांक_ptr cpu_mask_nr_tbl[DEC_MAX_CPU_INTS][2];
बाह्य पूर्णांक_ptr asic_mask_nr_tbl[DEC_MAX_ASIC_INTS][2];
बाह्य पूर्णांक cpu_fpu_mask;


/*
 * Common पूर्णांकerrupt routine prototypes क्रम all DECStations
 */
बाह्य व्योम kn02_io_पूर्णांक(व्योम);
बाह्य व्योम kn02xa_io_पूर्णांक(व्योम);
बाह्य व्योम kn03_io_पूर्णांक(व्योम);
बाह्य व्योम asic_dma_पूर्णांक(व्योम);
बाह्य व्योम asic_all_पूर्णांक(व्योम);
बाह्य व्योम kn02_all_पूर्णांक(व्योम);
बाह्य व्योम cpu_all_पूर्णांक(व्योम);

बाह्य व्योम dec_पूर्णांकr_unimplemented(व्योम);
बाह्य व्योम asic_पूर्णांकr_unimplemented(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
