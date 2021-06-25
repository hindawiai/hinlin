<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	mcfdma.h -- Coldfire पूर्णांकernal DMA support defines.
 *
 *	(C) Copyright 1999, Rob Scott (rscott@mtrob.ml.org)
 */

/****************************************************************************/
#अगर_अघोषित	mcfdma_h
#घोषणा	mcfdma_h
/****************************************************************************/

#अगर !defined(CONFIG_M5272)

/*
 *	Define the DMA रेजिस्टर set addresses.
 *      Note: these are दीर्घword रेजिस्टरs, use अचिन्हित दीर्घ as data type
 */
#घोषणा	MCFDMA_SAR		0x00		/* DMA source address (r/w) */
#घोषणा	MCFDMA_DAR		0x01		/* DMA destination adr (r/w) */
/* these are word रेजिस्टरs, use अचिन्हित लघु data type */
#घोषणा	MCFDMA_DCR		0x04		/* DMA control reg (r/w) */
#घोषणा	MCFDMA_BCR		0x06		/* DMA byte count reg (r/w) */
/* these are byte रेजिस्टरs, use unsiged अक्षर data type */
#घोषणा	MCFDMA_DSR		0x10		/* DMA status reg (r/w) */
#घोषणा	MCFDMA_DIVR		0x14		/* DMA पूर्णांकerrupt vec (r/w) */

/*
 *	Bit definitions क्रम the DMA Control Register (DCR).
 */
#घोषणा	MCFDMA_DCR_INT	        0x8000		/* Enable completion irq */
#घोषणा	MCFDMA_DCR_EEXT	        0x4000		/* Enable बाह्यal DMA req */
#घोषणा	MCFDMA_DCR_CS 	        0x2000		/* Enable cycle steal */
#घोषणा	MCFDMA_DCR_AA   	0x1000		/* Enable स्वतः alignment */
#घोषणा	MCFDMA_DCR_BWC_MASK  	0x0E00		/* Bandwidth ctl mask */
#घोषणा MCFDMA_DCR_BWC_512      0x0200          /* Bandwidth:   512 Bytes */
#घोषणा MCFDMA_DCR_BWC_1024     0x0400          /* Bandwidth:  1024 Bytes */
#घोषणा MCFDMA_DCR_BWC_2048     0x0600          /* Bandwidth:  2048 Bytes */
#घोषणा MCFDMA_DCR_BWC_4096     0x0800          /* Bandwidth:  4096 Bytes */
#घोषणा MCFDMA_DCR_BWC_8192     0x0a00          /* Bandwidth:  8192 Bytes */
#घोषणा MCFDMA_DCR_BWC_16384    0x0c00          /* Bandwidth: 16384 Bytes */
#घोषणा MCFDMA_DCR_BWC_32768    0x0e00          /* Bandwidth: 32768 Bytes */
#घोषणा	MCFDMA_DCR_SAA         	0x0100		/* Single Address Access */
#घोषणा	MCFDMA_DCR_S_RW        	0x0080		/* SAA पढ़ो/ग_लिखो value */
#घोषणा	MCFDMA_DCR_SINC        	0x0040		/* Source addr inc enable */
#घोषणा	MCFDMA_DCR_SSIZE_MASK  	0x0030		/* Src xfer size */
#घोषणा	MCFDMA_DCR_SSIZE_LONG  	0x0000		/* Src xfer size, 00 = दीर्घw */
#घोषणा	MCFDMA_DCR_SSIZE_BYTE  	0x0010		/* Src xfer size, 01 = byte */
#घोषणा	MCFDMA_DCR_SSIZE_WORD  	0x0020		/* Src xfer size, 10 = word */
#घोषणा	MCFDMA_DCR_SSIZE_LINE  	0x0030		/* Src xfer size, 11 = line */
#घोषणा	MCFDMA_DCR_DINC        	0x0008		/* Dest addr inc enable */
#घोषणा	MCFDMA_DCR_DSIZE_MASK  	0x0006		/* Dest xfer size */
#घोषणा	MCFDMA_DCR_DSIZE_LONG  	0x0000		/* Dest xfer size, 00 = दीर्घ */
#घोषणा	MCFDMA_DCR_DSIZE_BYTE  	0x0002		/* Dest xfer size, 01 = byte */
#घोषणा	MCFDMA_DCR_DSIZE_WORD  	0x0004		/* Dest xfer size, 10 = word */
#घोषणा	MCFDMA_DCR_DSIZE_LINE  	0x0006		/* Dest xfer size, 11 = line */
#घोषणा	MCFDMA_DCR_START       	0x0001		/* Start transfer */

/*
 *	Bit definitions क्रम the DMA Status Register (DSR).
 */
#घोषणा	MCFDMA_DSR_CE	        0x40		/* Config error */
#घोषणा	MCFDMA_DSR_BES	        0x20		/* Bus Error on source */
#घोषणा	MCFDMA_DSR_BED 	        0x10		/* Bus Error on dest */
#घोषणा	MCFDMA_DSR_REQ   	0x04		/* Requests reमुख्यing */
#घोषणा	MCFDMA_DSR_BSY  	0x02		/* Busy */
#घोषणा	MCFDMA_DSR_DONE        	0x01		/* DMA transfer complete */

#अन्यथा /* This is an MCF5272 */

#घोषणा MCFDMA_DMR        0x00    /* Mode Register (r/w) */
#घोषणा MCFDMA_सूची        0x03    /* Interrupt trigger रेजिस्टर (r/w) */
#घोषणा MCFDMA_DSAR       0x03    /* Source Address रेजिस्टर (r/w) */
#घोषणा MCFDMA_DDAR       0x04    /* Destination Address रेजिस्टर (r/w) */
#घोषणा MCFDMA_DBCR       0x02    /* Byte Count Register (r/w) */

/* Bit definitions क्रम the DMA Mode Register (DMR) */
#घोषणा MCFDMA_DMR_RESET     0x80000000L /* Reset bit */
#घोषणा MCFDMA_DMR_EN        0x40000000L /* DMA enable */
#घोषणा MCFDMA_DMR_RQM       0x000C0000L /* Request Mode Mask */
#घोषणा MCFDMA_DMR_RQM_DUAL  0x000C0000L /* Dual address mode, the only valid mode */
#घोषणा MCFDMA_DMR_DSTM      0x00002000L /* Destination addressing mask */
#घोषणा MCFDMA_DMR_DSTM_SA   0x00000000L /* Destination uses अटल addressing */
#घोषणा MCFDMA_DMR_DSTM_IA   0x00002000L /* Destination uses incremental addressing */
#घोषणा MCFDMA_DMR_DSTT_UD   0x00000400L /* Destination is user data */
#घोषणा MCFDMA_DMR_DSTT_UC   0x00000800L /* Destination is user code */
#घोषणा MCFDMA_DMR_DSTT_SD   0x00001400L /* Destination is supervisor data */
#घोषणा MCFDMA_DMR_DSTT_SC   0x00001800L /* Destination is supervisor code */
#घोषणा MCFDMA_DMR_DSTS_OFF  0x8         /* offset to the destination size bits */
#घोषणा MCFDMA_DMR_DSTS_LONG 0x00000000L /* Long destination size */
#घोषणा MCFDMA_DMR_DSTS_BYTE 0x00000100L /* Byte destination size */
#घोषणा MCFDMA_DMR_DSTS_WORD 0x00000200L /* Word destination size */
#घोषणा MCFDMA_DMR_DSTS_LINE 0x00000300L /* Line destination size */
#घोषणा MCFDMA_DMR_SRCM      0x00000020L /* Source addressing mask */
#घोषणा MCFDMA_DMR_SRCM_SA   0x00000000L /* Source uses अटल addressing */
#घोषणा MCFDMA_DMR_SRCM_IA   0x00000020L /* Source uses incremental addressing */
#घोषणा MCFDMA_DMR_SRCT_UD   0x00000004L /* Source is user data */
#घोषणा MCFDMA_DMR_SRCT_UC   0x00000008L /* Source is user code */
#घोषणा MCFDMA_DMR_SRCT_SD   0x00000014L /* Source is supervisor data */
#घोषणा MCFDMA_DMR_SRCT_SC   0x00000018L /* Source is supervisor code */
#घोषणा MCFDMA_DMR_SRCS_OFF  0x0         /* Offset to the source size bits */
#घोषणा MCFDMA_DMR_SRCS_LONG 0x00000000L /* Long source size */
#घोषणा MCFDMA_DMR_SRCS_BYTE 0x00000001L /* Byte source size */
#घोषणा MCFDMA_DMR_SRCS_WORD 0x00000002L /* Word source size */
#घोषणा MCFDMA_DMR_SRCS_LINE 0x00000003L /* Line source size */

/* Bit definitions क्रम the DMA पूर्णांकerrupt रेजिस्टर (सूची) */
#घोषणा MCFDMA_सूची_INVEN     0x1000 /* Invalid Combination पूर्णांकerrupt enable */
#घोषणा MCFDMA_सूची_ASCEN     0x0800 /* Address Sequence Complete (Completion) पूर्णांकerrupt enable */
#घोषणा MCFDMA_सूची_TEEN      0x0200 /* Transfer Error पूर्णांकerrupt enable */
#घोषणा MCFDMA_सूची_TCEN      0x0100 /* Transfer Complete (a bus transfer, that is) पूर्णांकerrupt enable */
#घोषणा MCFDMA_सूची_INV       0x0010 /* Invalid Combination */
#घोषणा MCFDMA_सूची_ASC       0x0008 /* Address Sequence Complete (DMA Completion) */
#घोषणा MCFDMA_सूची_TE        0x0002 /* Transfer Error */
#घोषणा MCFDMA_सूची_TC        0x0001 /* Transfer Complete */

#पूर्ण_अगर /* !defined(CONFIG_M5272) */ 

/****************************************************************************/
#पूर्ण_अगर	/* mcfdma_h */
