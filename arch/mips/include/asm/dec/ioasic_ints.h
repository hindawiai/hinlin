<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Definitions क्रम the पूर्णांकerrupt related bits in the I/O ASIC
 * पूर्णांकerrupt status रेजिस्टर (and the पूर्णांकerrupt mask रेजिस्टर, of course)
 *
 * Created with Inक्रमmation from:
 *
 * "DEC 3000 300/400/500/600/700/800/900 AXP Models System Programmer's Manual"
 *
 * and the Mach Sources
 *
 * Copyright (C) 199x  the Anonymous
 * Copyright (C) 2002  Maciej W. Rozycki
 */

#अगर_अघोषित __ASM_DEC_IOASIC_INTS_H
#घोषणा __ASM_DEC_IOASIC_INTS_H

/*
 * The upper 16 bits are a part of the I/O ASIC's पूर्णांकernal DMA engine
 * and thus are common to all I/O ASIC machines.  The exception is
 * the Maxine, which makes use of the FLOPPY and ISDN bits (otherwise
 * unused) and has a dअगरferent SCC wiring.
 */
					/* all प्रणालीs */
#घोषणा IO_INR_SCC0A_TXDMA	31	/* SCC0A transmit page end */
#घोषणा IO_INR_SCC0A_TXERR	30	/* SCC0A transmit memory पढ़ो error */
#घोषणा IO_INR_SCC0A_RXDMA	29	/* SCC0A receive half page */
#घोषणा IO_INR_SCC0A_RXERR	28	/* SCC0A receive overrun */
#घोषणा IO_INR_ASC_DMA		19	/* ASC buffer poपूर्णांकer loaded */
#घोषणा IO_INR_ASC_ERR		18	/* ASC page overrun */
#घोषणा IO_INR_ASC_MERR		17	/* ASC memory पढ़ो error */
#घोषणा IO_INR_LANCE_MERR	16	/* LANCE memory पढ़ो error */

					/* except Maxine */
#घोषणा IO_INR_SCC1A_TXDMA	27	/* SCC1A transmit page end */
#घोषणा IO_INR_SCC1A_TXERR	26	/* SCC1A transmit memory पढ़ो error */
#घोषणा IO_INR_SCC1A_RXDMA	25	/* SCC1A receive half page */
#घोषणा IO_INR_SCC1A_RXERR	24	/* SCC1A receive overrun */
#घोषणा IO_INR_RES_23		23	/* unused */
#घोषणा IO_INR_RES_22		22	/* unused */
#घोषणा IO_INR_RES_21		21	/* unused */
#घोषणा IO_INR_RES_20		20	/* unused */

					/* Maxine */
#घोषणा IO_INR_AB_TXDMA		27	/* ACCESS.bus transmit page end */
#घोषणा IO_INR_AB_TXERR		26	/* ACCESS.bus xmit memory पढ़ो error */
#घोषणा IO_INR_AB_RXDMA		25	/* ACCESS.bus receive half page */
#घोषणा IO_INR_AB_RXERR		24	/* ACCESS.bus receive overrun */
#घोषणा IO_INR_FLOPPY_ERR	23	/* FDC error */
#घोषणा IO_INR_ISDN_TXDMA	22	/* ISDN xmit buffer poपूर्णांकer loaded */
#घोषणा IO_INR_ISDN_RXDMA	21	/* ISDN recv buffer poपूर्णांकer loaded */
#घोषणा IO_INR_ISDN_ERR		20	/* ISDN memory पढ़ो/overrun error */

#घोषणा IO_INR_DMA		16	/* first DMA IRQ */

/*
 * The lower 16 bits are प्रणाली-specअगरic and thus defined in
 * प्रणाली-specअगरic headers.
 */


#घोषणा IO_IRQ_BASE		8	/* first IRQ asचिन्हित to I/O ASIC */
#घोषणा IO_IRQ_LINES		32	/* number of I/O ASIC पूर्णांकerrupts */

#घोषणा IO_IRQ_NR(n)		((n) + IO_IRQ_BASE)
#घोषणा IO_IRQ_MASK(n)		(1 << (n))
#घोषणा IO_IRQ_ALL		0x0000ffff
#घोषणा IO_IRQ_DMA		0xffff0000

#पूर्ण_अगर /* __ASM_DEC_IOASIC_INTS_H */
