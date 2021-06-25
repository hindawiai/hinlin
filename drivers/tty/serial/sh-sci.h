<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/bitops.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पन.स>

#घोषणा SCI_MAJOR		204
#घोषणा SCI_MINOR_START		8


/*
 * SCI रेजिस्टर subset common क्रम all port types.
 * Not all रेजिस्टरs will exist on all parts.
 */
क्रमागत अणु
	SCSMR,				/* Serial Mode Register */
	SCBRR,				/* Bit Rate Register */
	SCSCR,				/* Serial Control Register */
	SCxSR,				/* Serial Status Register */
	SCFCR,				/* FIFO Control Register */
	SCFDR,				/* FIFO Data Count Register */
	SCxTDR,				/* Transmit (FIFO) Data Register */
	SCxRDR,				/* Receive (FIFO) Data Register */
	SCLSR,				/* Line Status Register */
	SCTFDR,				/* Transmit FIFO Data Count Register */
	SCRFDR,				/* Receive FIFO Data Count Register */
	SCSPTR,				/* Serial Port Register */
	HSSRR,				/* Sampling Rate Register */
	SCPCR,				/* Serial Port Control Register */
	SCPDR,				/* Serial Port Data Register */
	SCDL,				/* BRG Frequency Division Register */
	SCCKS,				/* BRG Clock Select Register */
	HSRTRGR,			/* Rx FIFO Data Count Trigger Register */
	HSTTRGR,			/* Tx FIFO Data Count Trigger Register */

	SCIx_NR_REGS,
पूर्ण;


/* SCSMR (Serial Mode Register) */
#घोषणा SCSMR_C_A	BIT(7)	/* Communication Mode */
#घोषणा SCSMR_CSYNC	BIT(7)	/*   - Clocked synchronous mode */
#घोषणा SCSMR_ASYNC	0	/*   - Asynchronous mode */
#घोषणा SCSMR_CHR	BIT(6)	/* 7-bit Character Length */
#घोषणा SCSMR_PE	BIT(5)	/* Parity Enable */
#घोषणा SCSMR_ODD	BIT(4)	/* Odd Parity */
#घोषणा SCSMR_STOP	BIT(3)	/* Stop Bit Length */
#घोषणा SCSMR_CKS	0x0003	/* Clock Select */

/* Serial Mode Register, SCIFA/SCIFB only bits */
#घोषणा SCSMR_CKEDG	BIT(12)	/* Transmit/Receive Clock Edge Select */
#घोषणा SCSMR_SRC_MASK	0x0700	/* Sampling Control */
#घोषणा SCSMR_SRC_16	0x0000	/* Sampling rate 1/16 */
#घोषणा SCSMR_SRC_5	0x0100	/* Sampling rate 1/5 */
#घोषणा SCSMR_SRC_7	0x0200	/* Sampling rate 1/7 */
#घोषणा SCSMR_SRC_11	0x0300	/* Sampling rate 1/11 */
#घोषणा SCSMR_SRC_13	0x0400	/* Sampling rate 1/13 */
#घोषणा SCSMR_SRC_17	0x0500	/* Sampling rate 1/17 */
#घोषणा SCSMR_SRC_19	0x0600	/* Sampling rate 1/19 */
#घोषणा SCSMR_SRC_27	0x0700	/* Sampling rate 1/27 */

/* Serial Control Register, SCIFA/SCIFB only bits */
#घोषणा SCSCR_TDRQE	BIT(15)	/* Tx Data Transfer Request Enable */
#घोषणा SCSCR_RDRQE	BIT(14)	/* Rx Data Transfer Request Enable */

/* Serial Control Register, HSCIF-only bits */
#घोषणा HSSCR_TOT_SHIFT	14

/* SCxSR (Serial Status Register) on SCI */
#घोषणा SCI_TDRE	BIT(7)	/* Transmit Data Register Empty */
#घोषणा SCI_RDRF	BIT(6)	/* Receive Data Register Full */
#घोषणा SCI_ORER	BIT(5)	/* Overrun Error */
#घोषणा SCI_FER		BIT(4)	/* Framing Error */
#घोषणा SCI_PER		BIT(3)	/* Parity Error */
#घोषणा SCI_TEND	BIT(2)	/* Transmit End */
#घोषणा SCI_RESERVED	0x03	/* All reserved bits */

#घोषणा SCI_DEFAULT_ERROR_MASK (SCI_PER | SCI_FER)

#घोषणा SCI_RDxF_CLEAR	(u32)(~(SCI_RESERVED | SCI_RDRF))
#घोषणा SCI_ERROR_CLEAR	(u32)(~(SCI_RESERVED | SCI_PER | SCI_FER | SCI_ORER))
#घोषणा SCI_TDxE_CLEAR	(u32)(~(SCI_RESERVED | SCI_TEND | SCI_TDRE))
#घोषणा SCI_BREAK_CLEAR	(u32)(~(SCI_RESERVED | SCI_PER | SCI_FER | SCI_ORER))

/* SCxSR (Serial Status Register) on SCIF, SCIFA, SCIFB, HSCIF */
#घोषणा SCIF_ER		BIT(7)	/* Receive Error */
#घोषणा SCIF_TEND	BIT(6)	/* Transmission End */
#घोषणा SCIF_TDFE	BIT(5)	/* Transmit FIFO Data Empty */
#घोषणा SCIF_BRK	BIT(4)	/* Break Detect */
#घोषणा SCIF_FER	BIT(3)	/* Framing Error */
#घोषणा SCIF_PER	BIT(2)	/* Parity Error */
#घोषणा SCIF_RDF	BIT(1)	/* Receive FIFO Data Full */
#घोषणा SCIF_DR		BIT(0)	/* Receive Data Ready */
/* SCIF only (optional) */
#घोषणा SCIF_PERC	0xf000	/* Number of Parity Errors */
#घोषणा SCIF_FERC	0x0f00	/* Number of Framing Errors */
/*SCIFA/SCIFB and SCIF on SH7705/SH7720/SH7721 only */
#घोषणा SCIFA_ORER	BIT(9)	/* Overrun Error */

#घोषणा SCIF_DEFAULT_ERROR_MASK (SCIF_PER | SCIF_FER | SCIF_BRK | SCIF_ER)

#घोषणा SCIF_RDxF_CLEAR		(u32)(~(SCIF_DR | SCIF_RDF))
#घोषणा SCIF_ERROR_CLEAR	(u32)(~(SCIF_PER | SCIF_FER | SCIF_ER))
#घोषणा SCIF_TDxE_CLEAR		(u32)(~(SCIF_TDFE))
#घोषणा SCIF_BREAK_CLEAR	(u32)(~(SCIF_PER | SCIF_FER | SCIF_BRK))

/* SCFCR (FIFO Control Register) */
#घोषणा SCFCR_RTRG1	BIT(7)	/* Receive FIFO Data Count Trigger */
#घोषणा SCFCR_RTRG0	BIT(6)
#घोषणा SCFCR_TTRG1	BIT(5)	/* Transmit FIFO Data Count Trigger */
#घोषणा SCFCR_TTRG0	BIT(4)
#घोषणा SCFCR_MCE	BIT(3)	/* Modem Control Enable */
#घोषणा SCFCR_TFRST	BIT(2)	/* Transmit FIFO Data Register Reset */
#घोषणा SCFCR_RFRST	BIT(1)	/* Receive FIFO Data Register Reset */
#घोषणा SCFCR_LOOP	BIT(0)	/* Loopback Test */

/* SCLSR (Line Status Register) on (H)SCIF */
#घोषणा SCLSR_TO	BIT(2)	/* Timeout */
#घोषणा SCLSR_ORER	BIT(0)	/* Overrun Error */

/* SCSPTR (Serial Port Register), optional */
#घोषणा SCSPTR_RTSIO	BIT(7)	/* Serial Port RTS# Pin Input/Output */
#घोषणा SCSPTR_RTSDT	BIT(6)	/* Serial Port RTS# Pin Data */
#घोषणा SCSPTR_CTSIO	BIT(5)	/* Serial Port CTS# Pin Input/Output */
#घोषणा SCSPTR_CTSDT	BIT(4)	/* Serial Port CTS# Pin Data */
#घोषणा SCSPTR_SCKIO	BIT(3)	/* Serial Port Clock Pin Input/Output */
#घोषणा SCSPTR_SCKDT	BIT(2)	/* Serial Port Clock Pin Data */
#घोषणा SCSPTR_SPB2IO	BIT(1)	/* Serial Port Break Input/Output */
#घोषणा SCSPTR_SPB2DT	BIT(0)	/* Serial Port Break Data */

/* HSSRR HSCIF */
#घोषणा HSCIF_SRE	BIT(15)	/* Sampling Rate Register Enable */
#घोषणा HSCIF_SRDE	BIT(14) /* Sampling Poपूर्णांक Register Enable */

#घोषणा HSCIF_SRHP_SHIFT	8
#घोषणा HSCIF_SRHP_MASK		0x0f00

/* SCPCR (Serial Port Control Register), SCIFA/SCIFB only */
#घोषणा SCPCR_RTSC	BIT(4)	/* Serial Port RTS# Pin / Output Pin */
#घोषणा SCPCR_CTSC	BIT(3)	/* Serial Port CTS# Pin / Input Pin */
#घोषणा SCPCR_SCKC	BIT(2)	/* Serial Port SCK Pin / Output Pin */
#घोषणा SCPCR_RXDC	BIT(1)	/* Serial Port RXD Pin / Input Pin */
#घोषणा SCPCR_TXDC	BIT(0)	/* Serial Port TXD Pin / Output Pin */

/* SCPDR (Serial Port Data Register), SCIFA/SCIFB only */
#घोषणा SCPDR_RTSD	BIT(4)	/* Serial Port RTS# Output Pin Data */
#घोषणा SCPDR_CTSD	BIT(3)	/* Serial Port CTS# Input Pin Data */
#घोषणा SCPDR_SCKD	BIT(2)	/* Serial Port SCK Output Pin Data */
#घोषणा SCPDR_RXDD	BIT(1)	/* Serial Port RXD Input Pin Data */
#घोषणा SCPDR_TXDD	BIT(0)	/* Serial Port TXD Output Pin Data */

/*
 * BRG Clock Select Register (Some SCIF and HSCIF)
 * The Baud Rate Generator क्रम बाह्यal घड़ी can provide a घड़ी source क्रम
 * the sampling घड़ी. It outमाला_दो either its frequency भागided घड़ी, or the
 * (unभागided) (H)SCK बाह्यal घड़ी.
 */
#घोषणा SCCKS_CKS	BIT(15)	/* Select (H)SCK (1) or भागided SC_CLK (0) */
#घोषणा SCCKS_XIN	BIT(14)	/* SC_CLK uses bus घड़ी (1) or SCIF_CLK (0) */

#घोषणा SCxSR_TEND(port)	(((port)->type == PORT_SCI) ? SCI_TEND   : SCIF_TEND)
#घोषणा SCxSR_RDxF(port)	(((port)->type == PORT_SCI) ? SCI_RDRF   : SCIF_DR | SCIF_RDF)
#घोषणा SCxSR_TDxE(port)	(((port)->type == PORT_SCI) ? SCI_TDRE   : SCIF_TDFE)
#घोषणा SCxSR_FER(port)		(((port)->type == PORT_SCI) ? SCI_FER    : SCIF_FER)
#घोषणा SCxSR_PER(port)		(((port)->type == PORT_SCI) ? SCI_PER    : SCIF_PER)
#घोषणा SCxSR_BRK(port)		(((port)->type == PORT_SCI) ? 0x00       : SCIF_BRK)

#घोषणा SCxSR_ERRORS(port)	(to_sci_port(port)->params->error_mask)

#घोषणा SCxSR_RDxF_CLEAR(port) \
	(((port)->type == PORT_SCI) ? SCI_RDxF_CLEAR : SCIF_RDxF_CLEAR)
#घोषणा SCxSR_ERROR_CLEAR(port) \
	(to_sci_port(port)->params->error_clear)
#घोषणा SCxSR_TDxE_CLEAR(port) \
	(((port)->type == PORT_SCI) ? SCI_TDxE_CLEAR : SCIF_TDxE_CLEAR)
#घोषणा SCxSR_BREAK_CLEAR(port) \
	(((port)->type == PORT_SCI) ? SCI_BREAK_CLEAR : SCIF_BREAK_CLEAR)
