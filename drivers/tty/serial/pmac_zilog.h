<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PMAC_ZILOG_H__
#घोषणा __PMAC_ZILOG_H__

/*
 * At most 2 ESCCs with 2 ports each
 */
#घोषणा MAX_ZS_PORTS	4

/* 
 * We wrap our port काष्ठाure around the generic uart_port.
 */
#घोषणा NUM_ZSREGS    17

काष्ठा uart_pmac_port अणु
	काष्ठा uart_port		port;
	काष्ठा uart_pmac_port		*mate;

#अगर_घोषित CONFIG_PPC_PMAC
	/* macio_dev क्रम the escc holding this port (maybe be null on
	 * early inited port)
	 */
	काष्ठा macio_dev		*dev;
	/* device node to this port, this poपूर्णांकs to one of 2 childs
	 * of "escc" node (ie. ch-a or ch-b)
	 */
	काष्ठा device_node		*node;
#अन्यथा
	काष्ठा platक्रमm_device		*pdev;
#पूर्ण_अगर

	/* Port type as obtained from device tree (IRDA, modem, ...) */
	पूर्णांक				port_type;
	u8				curregs[NUM_ZSREGS];

	अचिन्हित पूर्णांक			flags;
#घोषणा PMACZILOG_FLAG_IS_CONS		0x00000001
#घोषणा PMACZILOG_FLAG_IS_KGDB		0x00000002
#घोषणा PMACZILOG_FLAG_MODEM_STATUS	0x00000004
#घोषणा PMACZILOG_FLAG_IS_CHANNEL_A	0x00000008
#घोषणा PMACZILOG_FLAG_REGS_HELD	0x00000010
#घोषणा PMACZILOG_FLAG_TX_STOPPED	0x00000020
#घोषणा PMACZILOG_FLAG_TX_ACTIVE	0x00000040
#घोषणा PMACZILOG_FLAG_IS_IRDA		0x00000100
#घोषणा PMACZILOG_FLAG_IS_INTMODEM	0x00000200
#घोषणा PMACZILOG_FLAG_HAS_DMA		0x00000400
#घोषणा PMACZILOG_FLAG_RSRC_REQUESTED	0x00000800
#घोषणा PMACZILOG_FLAG_IS_OPEN		0x00002000
#घोषणा PMACZILOG_FLAG_IS_EXTCLK	0x00008000
#घोषणा PMACZILOG_FLAG_BREAK		0x00010000

	अचिन्हित अक्षर			parity_mask;
	अचिन्हित अक्षर			prev_status;

	अस्थिर u8			__iomem *control_reg;
	अस्थिर u8			__iomem *data_reg;

#अगर_घोषित CONFIG_PPC_PMAC
	अचिन्हित पूर्णांक			tx_dma_irq;
	अचिन्हित पूर्णांक			rx_dma_irq;
	अस्थिर काष्ठा dbdma_regs	__iomem *tx_dma_regs;
	अस्थिर काष्ठा dbdma_regs	__iomem *rx_dma_regs;
#पूर्ण_अगर

	अचिन्हित अक्षर			irq_name[8];

	काष्ठा ktermios			termios_cache;
पूर्ण;

#घोषणा to_pmz(p) ((काष्ठा uart_pmac_port *)(p))

अटल अंतरभूत काष्ठा uart_pmac_port *pmz_get_port_A(काष्ठा uart_pmac_port *uap)
अणु
	अगर (uap->flags & PMACZILOG_FLAG_IS_CHANNEL_A)
		वापस uap;
	वापस uap->mate;
पूर्ण

/*
 * Register accessors. Note that we करोn't need to enक्रमce a recovery
 * delay on PCI PowerMac hardware, it's dealt in HW by the MacIO chip,
 * though अगर we try to use this driver on older machines, we might have
 * to add it back
 */
अटल अंतरभूत u8 पढ़ो_zsreg(काष्ठा uart_pmac_port *port, u8 reg)
अणु
	अगर (reg != 0)
		ग_लिखोb(reg, port->control_reg);
	वापस पढ़ोb(port->control_reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_zsreg(काष्ठा uart_pmac_port *port, u8 reg, u8 value)
अणु
	अगर (reg != 0)
		ग_लिखोb(reg, port->control_reg);
	ग_लिखोb(value, port->control_reg);
पूर्ण

अटल अंतरभूत u8 पढ़ो_zsdata(काष्ठा uart_pmac_port *port)
अणु
	वापस पढ़ोb(port->data_reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_zsdata(काष्ठा uart_pmac_port *port, u8 data)
अणु
	ग_लिखोb(data, port->data_reg);
पूर्ण

अटल अंतरभूत व्योम zssync(काष्ठा uart_pmac_port *port)
अणु
	(व्योम)पढ़ोb(port->control_reg);
पूर्ण

/* Conversion routines to/from brg समय स्थिरants from/to bits
 * per second.
 */
#घोषणा BRG_TO_BPS(brg, freq) ((freq) / 2 / ((brg) + 2))
#घोषणा BPS_TO_BRG(bps, freq) ((((freq) + (bps)) / (2 * (bps))) - 2)

#घोषणा ZS_CLOCK         3686400	/* Z8530 RTxC input घड़ी rate */

/* The Zilog रेजिस्टर set */

#घोषणा	FLAG	0x7e

/* Write Register 0 */
#घोषणा	R0	0		/* Register selects */
#घोषणा	R1	1
#घोषणा	R2	2
#घोषणा	R3	3
#घोषणा	R4	4
#घोषणा	R5	5
#घोषणा	R6	6
#घोषणा	R7	7
#घोषणा	R8	8
#घोषणा	R9	9
#घोषणा	R10	10
#घोषणा	R11	11
#घोषणा	R12	12
#घोषणा	R13	13
#घोषणा	R14	14
#घोषणा	R15	15
#घोषणा	R7P	16

#घोषणा	शून्यCODE	0	/* Null Code */
#घोषणा	POINT_HIGH	0x8	/* Select upper half of रेजिस्टरs */
#घोषणा	RES_EXT_INT	0x10	/* Reset Ext. Status Interrupts */
#घोषणा	SEND_ABORT	0x18	/* HDLC Abort */
#घोषणा	RES_RxINT_FC	0x20	/* Reset RxINT on First Character */
#घोषणा	RES_Tx_P	0x28	/* Reset TxINT Pending */
#घोषणा	ERR_RES		0x30	/* Error Reset */
#घोषणा	RES_H_IUS	0x38	/* Reset highest IUS */

#घोषणा	RES_Rx_CRC	0x40	/* Reset Rx CRC Checker */
#घोषणा	RES_Tx_CRC	0x80	/* Reset Tx CRC Checker */
#घोषणा	RES_EOM_L	0xC0	/* Reset EOM latch */

/* Write Register 1 */

#घोषणा	EXT_INT_ENAB	0x1	/* Ext Int Enable */
#घोषणा	TxINT_ENAB	0x2	/* Tx Int Enable */
#घोषणा	PAR_SPEC	0x4	/* Parity is special condition */

#घोषणा	RxINT_DISAB	0	/* Rx Int Disable */
#घोषणा	RxINT_FCERR	0x8	/* Rx Int on First Character Only or Error */
#घोषणा	INT_ALL_Rx	0x10	/* Int on all Rx Characters or error */
#घोषणा	INT_ERR_Rx	0x18	/* Int on error only */
#घोषणा RxINT_MASK	0x18

#घोषणा	WT_RDY_RT	0x20	/* W/Req reflects recv अगर 1, xmit अगर 0 */
#घोषणा	WT_FN_RDYFN	0x40	/* W/Req pin is DMA request अगर 1, रुको अगर 0 */
#घोषणा	WT_RDY_ENAB	0x80	/* Enable W/Req pin */

/* Write Register #2 (Interrupt Vector) */

/* Write Register 3 */

#घोषणा	RxENABLE	0x1	/* Rx Enable */
#घोषणा	SYNC_L_INH	0x2	/* Sync Character Load Inhibit */
#घोषणा	ADD_SM		0x4	/* Address Search Mode (SDLC) */
#घोषणा	RxCRC_ENAB	0x8	/* Rx CRC Enable */
#घोषणा	ENT_HM		0x10	/* Enter Hunt Mode */
#घोषणा	AUTO_ENAB	0x20	/* Auto Enables */
#घोषणा	Rx5		0x0	/* Rx 5 Bits/Character */
#घोषणा	Rx7		0x40	/* Rx 7 Bits/Character */
#घोषणा	Rx6		0x80	/* Rx 6 Bits/Character */
#घोषणा	Rx8		0xc0	/* Rx 8 Bits/Character */
#घोषणा RxN_MASK	0xc0

/* Write Register 4 */

#घोषणा	PAR_ENAB	0x1	/* Parity Enable */
#घोषणा	PAR_EVEN	0x2	/* Parity Even/Odd* */

#घोषणा	SYNC_ENAB	0	/* Sync Modes Enable */
#घोषणा	SB1		0x4	/* 1 stop bit/अक्षर */
#घोषणा	SB15		0x8	/* 1.5 stop bits/अक्षर */
#घोषणा	SB2		0xc	/* 2 stop bits/अक्षर */
#घोषणा SB_MASK		0xc

#घोषणा	MONSYNC		0	/* 8 Bit Sync अक्षरacter */
#घोषणा	BISYNC		0x10	/* 16 bit sync अक्षरacter */
#घोषणा	SDLC		0x20	/* SDLC Mode (01111110 Sync Flag) */
#घोषणा	EXTSYNC		0x30	/* External Sync Mode */

#घोषणा	X1CLK		0x0	/* x1 घड़ी mode */
#घोषणा	X16CLK		0x40	/* x16 घड़ी mode */
#घोषणा	X32CLK		0x80	/* x32 घड़ी mode */
#घोषणा	X64CLK		0xC0	/* x64 घड़ी mode */
#घोषणा XCLK_MASK	0xC0

/* Write Register 5 */

#घोषणा	TxCRC_ENAB	0x1	/* Tx CRC Enable */
#घोषणा	RTS		0x2	/* RTS */
#घोषणा	SDLC_CRC	0x4	/* SDLC/CRC-16 */
#घोषणा	TxENABLE	0x8	/* Tx Enable */
#घोषणा	SND_BRK		0x10	/* Send Break */
#घोषणा	Tx5		0x0	/* Tx 5 bits (or less)/अक्षरacter */
#घोषणा	Tx7		0x20	/* Tx 7 bits/अक्षरacter */
#घोषणा	Tx6		0x40	/* Tx 6 bits/अक्षरacter */
#घोषणा	Tx8		0x60	/* Tx 8 bits/अक्षरacter */
#घोषणा TxN_MASK	0x60
#घोषणा	DTR		0x80	/* DTR */

/* Write Register 6 (Sync bits 0-7/SDLC Address Field) */

/* Write Register 7 (Sync bits 8-15/SDLC 01111110) */

/* Write Register 7' (Some enhanced feature control) */
#घोषणा	ENEXREAD	0x40	/* Enable पढ़ो of some ग_लिखो रेजिस्टरs */

/* Write Register 8 (transmit buffer) */

/* Write Register 9 (Master पूर्णांकerrupt control) */
#घोषणा	VIS	1	/* Vector Includes Status */
#घोषणा	NV	2	/* No Vector */
#घोषणा	DLC	4	/* Disable Lower Chain */
#घोषणा	MIE	8	/* Master Interrupt Enable */
#घोषणा	STATHI	0x10	/* Status high */
#घोषणा	NORESET	0	/* No reset on ग_लिखो to R9 */
#घोषणा	CHRB	0x40	/* Reset channel B */
#घोषणा	CHRA	0x80	/* Reset channel A */
#घोषणा	FHWRES	0xc0	/* Force hardware reset */

/* Write Register 10 (misc control bits) */
#घोषणा	BIT6	1	/* 6 bit/8bit sync */
#घोषणा	LOOPMODE 2	/* SDLC Loop mode */
#घोषणा	ABUNDER	4	/* Abort/flag on SDLC xmit underrun */
#घोषणा	MARKIDLE 8	/* Mark/flag on idle */
#घोषणा	GAOP	0x10	/* Go active on poll */
#घोषणा	NRZ	0	/* NRZ mode */
#घोषणा	NRZI	0x20	/* NRZI mode */
#घोषणा	FM1	0x40	/* FM1 (transition = 1) */
#घोषणा	FM0	0x60	/* FM0 (transition = 0) */
#घोषणा	CRCPS	0x80	/* CRC Preset I/O */

/* Write Register 11 (Clock Mode control) */
#घोषणा	TRxCXT	0	/* TRxC = Xtal output */
#घोषणा	TRxCTC	1	/* TRxC = Transmit घड़ी */
#घोषणा	TRxCBR	2	/* TRxC = BR Generator Output */
#घोषणा	TRxCDP	3	/* TRxC = DPLL output */
#घोषणा	TRxCOI	4	/* TRxC O/I */
#घोषणा	TCRTxCP	0	/* Transmit घड़ी = RTxC pin */
#घोषणा	TCTRxCP	8	/* Transmit घड़ी = TRxC pin */
#घोषणा	TCBR	0x10	/* Transmit घड़ी = BR Generator output */
#घोषणा	TCDPLL	0x18	/* Transmit घड़ी = DPLL output */
#घोषणा	RCRTxCP	0	/* Receive घड़ी = RTxC pin */
#घोषणा	RCTRxCP	0x20	/* Receive घड़ी = TRxC pin */
#घोषणा	RCBR	0x40	/* Receive घड़ी = BR Generator output */
#घोषणा	RCDPLL	0x60	/* Receive घड़ी = DPLL output */
#घोषणा	RTxCX	0x80	/* RTxC Xtal/No Xtal */

/* Write Register 12 (lower byte of baud rate generator समय स्थिरant) */

/* Write Register 13 (upper byte of baud rate generator समय स्थिरant) */

/* Write Register 14 (Misc control bits) */
#घोषणा	BRENAB	1	/* Baud rate generator enable */
#घोषणा	BRSRC	2	/* Baud rate generator source */
#घोषणा	DTRREQ	4	/* DTR/Request function */
#घोषणा	AUTOECHO 8	/* Auto Echo */
#घोषणा	LOOPBAK	0x10	/* Local loopback */
#घोषणा	SEARCH	0x20	/* Enter search mode */
#घोषणा	RMC	0x40	/* Reset missing घड़ी */
#घोषणा	DISDPLL	0x60	/* Disable DPLL */
#घोषणा	SSBR	0x80	/* Set DPLL source = BR generator */
#घोषणा	SSRTxC	0xa0	/* Set DPLL source = RTxC */
#घोषणा	SFMM	0xc0	/* Set FM mode */
#घोषणा	SNRZI	0xe0	/* Set NRZI mode */

/* Write Register 15 (बाह्यal/status पूर्णांकerrupt control) */
#घोषणा	EN85C30	1	/* Enable some 85c30-enhanced रेजिस्टरs */
#घोषणा	ZCIE	2	/* Zero count IE */
#घोषणा	ENSTFIFO 4	/* Enable status FIFO (SDLC) */
#घोषणा	DCDIE	8	/* DCD IE */
#घोषणा	SYNCIE	0x10	/* Sync/hunt IE */
#घोषणा	CTSIE	0x20	/* CTS IE */
#घोषणा	TxUIE	0x40	/* Tx Underrun/EOM IE */
#घोषणा	BRKIE	0x80	/* Break/Abort IE */


/* Read Register 0 */
#घोषणा	Rx_CH_AV	0x1	/* Rx Character Available */
#घोषणा	ZCOUNT		0x2	/* Zero count */
#घोषणा	Tx_BUF_EMP	0x4	/* Tx Buffer empty */
#घोषणा	DCD		0x8	/* DCD */
#घोषणा	SYNC_HUNT	0x10	/* Sync/hunt */
#घोषणा	CTS		0x20	/* CTS */
#घोषणा	TxEOM		0x40	/* Tx underrun */
#घोषणा	BRK_ABRT	0x80	/* Break/Abort */

/* Read Register 1 */
#घोषणा	ALL_SNT		0x1	/* All sent */
/* Residue Data क्रम 8 Rx bits/अक्षर programmed */
#घोषणा	RES3		0x8	/* 0/3 */
#घोषणा	RES4		0x4	/* 0/4 */
#घोषणा	RES5		0xc	/* 0/5 */
#घोषणा	RES6		0x2	/* 0/6 */
#घोषणा	RES7		0xa	/* 0/7 */
#घोषणा	RES8		0x6	/* 0/8 */
#घोषणा	RES18		0xe	/* 1/8 */
#घोषणा	RES28		0x0	/* 2/8 */
/* Special Rx Condition Interrupts */
#घोषणा	PAR_ERR		0x10	/* Parity error */
#घोषणा	Rx_OVR		0x20	/* Rx Overrun Error */
#घोषणा	CRC_ERR		0x40	/* CRC/Framing Error */
#घोषणा	END_FR		0x80	/* End of Frame (SDLC) */

/* Read Register 2 (channel b only) - Interrupt vector */
#घोषणा	CHB_Tx_EMPTY	0x00
#घोषणा	CHB_EXT_STAT	0x02
#घोषणा	CHB_Rx_AVAIL	0x04
#घोषणा	CHB_SPECIAL	0x06
#घोषणा	CHA_Tx_EMPTY	0x08
#घोषणा	CHA_EXT_STAT	0x0a
#घोषणा	CHA_Rx_AVAIL	0x0c
#घोषणा	CHA_SPECIAL	0x0e
#घोषणा	STATUS_MASK	0x06

/* Read Register 3 (पूर्णांकerrupt pending रेजिस्टर) ch a only */
#घोषणा	CHBEXT	0x1		/* Channel B Ext/Stat IP */
#घोषणा	CHBTxIP	0x2		/* Channel B Tx IP */
#घोषणा	CHBRxIP	0x4		/* Channel B Rx IP */
#घोषणा	CHAEXT	0x8		/* Channel A Ext/Stat IP */
#घोषणा	CHATxIP	0x10		/* Channel A Tx IP */
#घोषणा	CHARxIP	0x20		/* Channel A Rx IP */

/* Read Register 8 (receive data रेजिस्टर) */

/* Read Register 10  (misc status bits) */
#घोषणा	ONLOOP	2		/* On loop */
#घोषणा	LOOPSEND 0x10		/* Loop sending */
#घोषणा	CLK2MIS	0x40		/* Two घड़ीs missing */
#घोषणा	CLK1MIS	0x80		/* One घड़ी missing */

/* Read Register 12 (lower byte of baud rate generator स्थिरant) */

/* Read Register 13 (upper byte of baud rate generator स्थिरant) */

/* Read Register 15 (value of WR 15) */

/* Misc macros */
#घोषणा ZS_CLEARERR(port)    (ग_लिखो_zsreg(port, 0, ERR_RES))
#घोषणा ZS_CLEARFIFO(port)   करो अणु                       \
				     पढ़ो_zsdata(port); \
				     पढ़ो_zsdata(port); \
				     पढ़ो_zsdata(port); \
				पूर्ण जबतक(0)

#घोषणा ZS_IS_CONS(UP)			((UP)->flags & PMACZILOG_FLAG_IS_CONS)
#घोषणा ZS_IS_KGDB(UP)			((UP)->flags & PMACZILOG_FLAG_IS_KGDB)
#घोषणा ZS_IS_CHANNEL_A(UP)		((UP)->flags & PMACZILOG_FLAG_IS_CHANNEL_A)
#घोषणा ZS_REGS_HELD(UP)		((UP)->flags & PMACZILOG_FLAG_REGS_HELD)
#घोषणा ZS_TX_STOPPED(UP)		((UP)->flags & PMACZILOG_FLAG_TX_STOPPED)
#घोषणा ZS_TX_ACTIVE(UP)		((UP)->flags & PMACZILOG_FLAG_TX_ACTIVE)
#घोषणा ZS_WANTS_MODEM_STATUS(UP)	((UP)->flags & PMACZILOG_FLAG_MODEM_STATUS)
#घोषणा ZS_IS_IRDA(UP)			((UP)->flags & PMACZILOG_FLAG_IS_IRDA)
#घोषणा ZS_IS_INTMODEM(UP)		((UP)->flags & PMACZILOG_FLAG_IS_INTMODEM)
#घोषणा ZS_HAS_DMA(UP)			((UP)->flags & PMACZILOG_FLAG_HAS_DMA)
#घोषणा ZS_IS_OPEN(UP)			((UP)->flags & PMACZILOG_FLAG_IS_OPEN)
#घोषणा ZS_IS_EXTCLK(UP)		((UP)->flags & PMACZILOG_FLAG_IS_EXTCLK)

#पूर्ण_अगर /* __PMAC_ZILOG_H__ */
