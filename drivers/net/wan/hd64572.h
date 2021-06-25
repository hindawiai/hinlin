<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * hd64572.h	Description of the Hitachi HD64572 (SCA-II), valid क्रम 
 * 		CPU modes 0 & 2.
 *
 * Author:	Ivan Passos <ivan@cyclades.com>
 *
 * Copyright:   (c) 2000-2001 Cyclades Corp.
 *
 * $Log: hd64572.h,v $
 * Revision 3.1  2001/06/15 12:41:10  regina
 * upping major version number
 *
 * Revision 1.1.1.1  2001/06/13 20:24:49  daniela
 * PC300 initial CVS version (3.4.0-pre1)
 *
 * Revision 1.0 2000/01/25 ivan
 * Initial version.
 */

#अगर_अघोषित __HD64572_H
#घोषणा __HD64572_H

/* Illegal Access Register */
#घोषणा	ILAR	0x00

/* Wait Controller Registers */
#घोषणा PABR0L	0x20	/* Physical Addr Boundary Register 0 L */
#घोषणा PABR0H	0x21	/* Physical Addr Boundary Register 0 H */
#घोषणा PABR1L	0x22	/* Physical Addr Boundary Register 1 L */
#घोषणा PABR1H	0x23	/* Physical Addr Boundary Register 1 H */
#घोषणा WCRL	0x24	/* Wait Control Register L */
#घोषणा WCRM	0x25	/* Wait Control Register M */
#घोषणा WCRH	0x26	/* Wait Control Register H */

/* Interrupt Registers */
#घोषणा IVR	0x60	/* Interrupt Vector Register */
#घोषणा IMVR	0x64	/* Interrupt Modअगरied Vector Register */
#घोषणा ITCR	0x68	/* Interrupt Control Register */
#घोषणा ISR0	0x6c	/* Interrupt Status Register 0 */
#घोषणा ISR1	0x70	/* Interrupt Status Register 1 */
#घोषणा IER0	0x74	/* Interrupt Enable Register 0 */
#घोषणा IER1	0x78	/* Interrupt Enable Register 1 */

/* Register Access Macros (chan is 0 or 1 in _any_ हाल) */
#घोषणा	M_REG(reg, chan)	(reg + 0x80*chan)		/* MSCI */
#घोषणा	DRX_REG(reg, chan)	(reg + 0x40*chan)		/* DMA Rx */
#घोषणा	DTX_REG(reg, chan)	(reg + 0x20*(2*chan + 1))	/* DMA Tx */
#घोषणा	TRX_REG(reg, chan)	(reg + 0x20*chan)		/* Timer Rx */
#घोषणा	TTX_REG(reg, chan)	(reg + 0x10*(2*chan + 1))	/* Timer Tx */
#घोषणा	ST_REG(reg, chan)	(reg + 0x80*chan)		/* Status Cnt */
#घोषणा IR0_DRX(val, chan)	((val)<<(8*(chan)))		/* Int DMA Rx */
#घोषणा IR0_DTX(val, chan)	((val)<<(4*(2*chan + 1)))	/* Int DMA Tx */
#घोषणा IR0_M(val, chan)	((val)<<(8*(chan)))		/* Int MSCI */

/* MSCI Channel Registers */
#घोषणा MSCI0_OFFSET 0x00
#घोषणा MSCI1_OFFSET 0x80

#घोषणा MD0	0x138	/* Mode reg 0 */
#घोषणा MD1	0x139	/* Mode reg 1 */
#घोषणा MD2	0x13a	/* Mode reg 2 */
#घोषणा MD3	0x13b	/* Mode reg 3 */
#घोषणा CTL	0x130	/* Control reg */
#घोषणा RXS	0x13c	/* RX घड़ी source */
#घोषणा TXS	0x13d	/* TX घड़ी source */
#घोषणा EXS	0x13e	/* External घड़ी input selection */
#घोषणा TMCT	0x144	/* Time स्थिरant (Tx) */
#घोषणा TMCR	0x145	/* Time स्थिरant (Rx) */
#घोषणा CMD	0x128	/* Command reg */
#घोषणा ST0	0x118	/* Status reg 0 */
#घोषणा ST1	0x119	/* Status reg 1 */
#घोषणा ST2	0x11a	/* Status reg 2 */
#घोषणा ST3	0x11b	/* Status reg 3 */
#घोषणा ST4	0x11c	/* Status reg 4 */
#घोषणा FST	0x11d	/* frame Status reg  */
#घोषणा IE0	0x120	/* Interrupt enable reg 0 */
#घोषणा IE1	0x121	/* Interrupt enable reg 1 */
#घोषणा IE2	0x122	/* Interrupt enable reg 2 */
#घोषणा IE4	0x124	/* Interrupt enable reg 4 */
#घोषणा FIE	0x125	/* Frame Interrupt enable reg  */
#घोषणा SA0	0x140	/* Syn Address reg 0 */
#घोषणा SA1	0x141	/* Syn Address reg 1 */
#घोषणा IDL	0x142	/* Idle रेजिस्टर */
#घोषणा TRBL	0x100	/* TX/RX buffer reg L */ 
#घोषणा TRBK	0x101	/* TX/RX buffer reg K */ 
#घोषणा TRBJ	0x102	/* TX/RX buffer reg J */ 
#घोषणा TRBH	0x103	/* TX/RX buffer reg H */ 
#घोषणा TRC0	0x148	/* TX Ready control reg 0 */ 
#घोषणा TRC1	0x149	/* TX Ready control reg 1 */ 
#घोषणा RRC	0x14a	/* RX Ready control reg */ 
#घोषणा CST0	0x108	/* Current Status Register 0 */ 
#घोषणा CST1	0x109	/* Current Status Register 1 */ 
#घोषणा CST2	0x10a	/* Current Status Register 2 */ 
#घोषणा CST3	0x10b	/* Current Status Register 3 */ 
#घोषणा GPO	0x131	/* General Purpose Output Pin Ctl Reg */
#घोषणा TFS	0x14b	/* Tx Start Threshold Ctl Reg */
#घोषणा TFN	0x143	/* Inter-transmit-frame Time Fill Ctl Reg */
#घोषणा TBN	0x110	/* Tx Buffer Number Reg */
#घोषणा RBN	0x111	/* Rx Buffer Number Reg */
#घोषणा TNR0	0x150	/* Tx DMA Request Ctl Reg 0 */
#घोषणा TNR1	0x151	/* Tx DMA Request Ctl Reg 1 */
#घोषणा TCR	0x152	/* Tx DMA Critical Request Reg */
#घोषणा RNR	0x154	/* Rx DMA Request Ctl Reg */
#घोषणा RCR	0x156	/* Rx DMA Critical Request Reg */

/* Timer Registers */
#घोषणा TIMER0RX_OFFSET 0x00
#घोषणा TIMER0TX_OFFSET 0x10
#घोषणा TIMER1RX_OFFSET 0x20
#घोषणा TIMER1TX_OFFSET 0x30

#घोषणा TCNTL	0x200	/* Timer Upcounter L */
#घोषणा TCNTH	0x201	/* Timer Upcounter H */
#घोषणा TCONRL	0x204	/* Timer Constant Register L */
#घोषणा TCONRH	0x205	/* Timer Constant Register H */
#घोषणा TCSR	0x206	/* Timer Control/Status Register */
#घोषणा TEPR	0x207	/* Timer Expand Prescale Register */

/* DMA रेजिस्टरs */
#घोषणा PCR		0x40		/* DMA priority control reg */
#घोषणा DRR		0x44		/* DMA reset reg */
#घोषणा DMER		0x07		/* DMA Master Enable reg */
#घोषणा BTCR		0x08		/* Burst Tx Ctl Reg */
#घोषणा BOLR		0x0c		/* Back-off Length Reg */
#घोषणा DSR_RX(chan)	(0x48 + 2*chan)	/* DMA Status Reg (Rx) */
#घोषणा DSR_TX(chan)	(0x49 + 2*chan)	/* DMA Status Reg (Tx) */
#घोषणा सूची_RX(chan)	(0x4c + 2*chan)	/* DMA Interrupt Enable Reg (Rx) */
#घोषणा सूची_TX(chan)	(0x4d + 2*chan)	/* DMA Interrupt Enable Reg (Tx) */
#घोषणा FCT_RX(chan)	(0x50 + 2*chan)	/* Frame End Interrupt Counter (Rx) */
#घोषणा FCT_TX(chan)	(0x51 + 2*chan)	/* Frame End Interrupt Counter (Tx) */
#घोषणा DMR_RX(chan)	(0x54 + 2*chan)	/* DMA Mode Reg (Rx) */
#घोषणा DMR_TX(chan)	(0x55 + 2*chan)	/* DMA Mode Reg (Tx) */
#घोषणा DCR_RX(chan)	(0x58 + 2*chan)	/* DMA Command Reg (Rx) */
#घोषणा DCR_TX(chan)	(0x59 + 2*chan)	/* DMA Command Reg (Tx) */

/* DMA Channel Registers */
#घोषणा DMAC0RX_OFFSET 0x00
#घोषणा DMAC0TX_OFFSET 0x20
#घोषणा DMAC1RX_OFFSET 0x40
#घोषणा DMAC1TX_OFFSET 0x60

#घोषणा DARL	0x80	/* Dest Addr Register L (single-block, RX only) */
#घोषणा DARH	0x81	/* Dest Addr Register H (single-block, RX only) */
#घोषणा DARB	0x82	/* Dest Addr Register B (single-block, RX only) */
#घोषणा DARBH	0x83	/* Dest Addr Register BH (single-block, RX only) */
#घोषणा SARL	0x80	/* Source Addr Register L (single-block, TX only) */
#घोषणा SARH	0x81	/* Source Addr Register H (single-block, TX only) */
#घोषणा SARB	0x82	/* Source Addr Register B (single-block, TX only) */
#घोषणा DARBH	0x83	/* Source Addr Register BH (single-block, TX only) */
#घोषणा BARL	0x80	/* Buffer Addr Register L (chained-block) */
#घोषणा BARH	0x81	/* Buffer Addr Register H (chained-block) */
#घोषणा BARB	0x82	/* Buffer Addr Register B (chained-block) */
#घोषणा BARBH	0x83	/* Buffer Addr Register BH (chained-block) */
#घोषणा CDAL	0x84	/* Current Descriptor Addr Register L */
#घोषणा CDAH	0x85	/* Current Descriptor Addr Register H */
#घोषणा CDAB	0x86	/* Current Descriptor Addr Register B */
#घोषणा CDABH	0x87	/* Current Descriptor Addr Register BH */
#घोषणा EDAL	0x88	/* Error Descriptor Addr Register L */
#घोषणा EDAH	0x89	/* Error Descriptor Addr Register H */
#घोषणा EDAB	0x8a	/* Error Descriptor Addr Register B */
#घोषणा EDABH	0x8b	/* Error Descriptor Addr Register BH */
#घोषणा BFLL	0x90	/* RX Buffer Length L (only RX) */
#घोषणा BFLH	0x91	/* RX Buffer Length H (only RX) */
#घोषणा BCRL	0x8c	/* Byte Count Register L */
#घोषणा BCRH	0x8d	/* Byte Count Register H */

/* Block Descriptor Structure */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ	next;		/* poपूर्णांकer to next block descriptor */
	अचिन्हित दीर्घ	ptbuf;		/* buffer poपूर्णांकer */
	अचिन्हित लघु	len;		/* data length */
	अचिन्हित अक्षर	status;		/* status */
	अचिन्हित अक्षर	filler[5];	/* alignment filler (16 bytes) */ 
पूर्ण pcsca_bd_t;

/* Block Descriptor Structure */
प्रकार काष्ठा अणु
	u32 cp;			/* poपूर्णांकer to next block descriptor */
	u32 bp;			/* buffer poपूर्णांकer */
	u16 len;		/* data length */
	u8 stat;		/* status */
	u8 unused;		/* pads to 4-byte boundary */
पूर्णpkt_desc;


/*
	Descriptor Status definitions:

	Bit	Transmission	Reception

	7	EOM		EOM
	6	-		Short Frame
	5	-		Abort
	4	-		Residual bit
	3	Underrun	Overrun	
	2	-		CRC
	1	Ownership	Ownership
	0	EOT		-
*/
#घोषणा DST_EOT		0x01	/* End of transmit command */
#घोषणा DST_OSB		0x02	/* Ownership bit */
#घोषणा DST_CRC		0x04	/* CRC Error */
#घोषणा DST_OVR		0x08	/* Overrun */
#घोषणा DST_UDR		0x08	/* Underrun */
#घोषणा DST_RBIT	0x10	/* Residual bit */
#घोषणा DST_ABT		0x20	/* Abort */
#घोषणा DST_SHRT	0x40	/* Short Frame  */
#घोषणा DST_EOM		0x80	/* End of Message  */

/* Packet Descriptor Status bits */

#घोषणा ST_TX_EOM     0x80	/* End of frame */
#घोषणा ST_TX_UNDRRUN 0x08
#घोषणा ST_TX_OWNRSHP 0x02
#घोषणा ST_TX_EOT     0x01	/* End of transmission */

#घोषणा ST_RX_EOM     0x80	/* End of frame */
#घोषणा ST_RX_SHORT   0x40	/* Short frame */
#घोषणा ST_RX_ABORT   0x20	/* Abort */
#घोषणा ST_RX_RESBIT  0x10	/* Residual bit */
#घोषणा ST_RX_OVERRUN 0x08	/* Overrun */
#घोषणा ST_RX_CRC     0x04	/* CRC */
#घोषणा ST_RX_OWNRSHP 0x02

#घोषणा ST_ERROR_MASK 0x7C

/* Status Counter Registers */
#घोषणा CMCR	0x158	/* Counter Master Ctl Reg */
#घोषणा TECNTL	0x160	/* Tx EOM Counter L */
#घोषणा TECNTM	0x161	/* Tx EOM Counter M */
#घोषणा TECNTH	0x162	/* Tx EOM Counter H */
#घोषणा TECCR	0x163	/* Tx EOM Counter Ctl Reg */
#घोषणा URCNTL	0x164	/* Underrun Counter L */
#घोषणा URCNTH	0x165	/* Underrun Counter H */
#घोषणा URCCR	0x167	/* Underrun Counter Ctl Reg */
#घोषणा RECNTL	0x168	/* Rx EOM Counter L */
#घोषणा RECNTM	0x169	/* Rx EOM Counter M */
#घोषणा RECNTH	0x16a	/* Rx EOM Counter H */
#घोषणा RECCR	0x16b	/* Rx EOM Counter Ctl Reg */
#घोषणा ORCNTL	0x16c	/* Overrun Counter L */
#घोषणा ORCNTH	0x16d	/* Overrun Counter H */
#घोषणा ORCCR	0x16f	/* Overrun Counter Ctl Reg */
#घोषणा CECNTL	0x170	/* CRC Counter L */
#घोषणा CECNTH	0x171	/* CRC Counter H */
#घोषणा CECCR	0x173	/* CRC Counter Ctl Reg */
#घोषणा ABCNTL	0x174	/* Abort frame Counter L */
#घोषणा ABCNTH	0x175	/* Abort frame Counter H */
#घोषणा ABCCR	0x177	/* Abort frame Counter Ctl Reg */
#घोषणा SHCNTL	0x178	/* Short frame Counter L */
#घोषणा SHCNTH	0x179	/* Short frame Counter H */
#घोषणा SHCCR	0x17b	/* Short frame Counter Ctl Reg */
#घोषणा RSCNTL	0x17c	/* Residual bit Counter L */
#घोषणा RSCNTH	0x17d	/* Residual bit Counter H */
#घोषणा RSCCR	0x17f	/* Residual bit Counter Ctl Reg */

/* Register Programming Constants */

#घोषणा IR0_DMIC	0x00000001
#घोषणा IR0_DMIB	0x00000002
#घोषणा IR0_DMIA	0x00000004
#घोषणा IR0_EFT		0x00000008
#घोषणा IR0_DMAREQ	0x00010000
#घोषणा IR0_TXINT	0x00020000
#घोषणा IR0_RXINTB	0x00040000
#घोषणा IR0_RXINTA	0x00080000
#घोषणा IR0_TXRDY	0x00100000
#घोषणा IR0_RXRDY	0x00200000

#घोषणा MD0_CRC16_0	0x00
#घोषणा MD0_CRC16_1	0x01
#घोषणा MD0_CRC32	0x02
#घोषणा MD0_CRC_CCITT	0x03
#घोषणा MD0_CRCC0	0x04
#घोषणा MD0_CRCC1	0x08
#घोषणा MD0_AUTO_ENA	0x10
#घोषणा MD0_ASYNC	0x00
#घोषणा MD0_BY_MSYNC	0x20
#घोषणा MD0_BY_BISYNC	0x40
#घोषणा MD0_BY_EXT	0x60
#घोषणा MD0_BIT_SYNC	0x80
#घोषणा MD0_TRANSP	0xc0

#घोषणा MD0_HDLC        0x80	/* Bit-sync HDLC mode */

#घोषणा MD0_CRC_NONE	0x00
#घोषणा MD0_CRC_16_0	0x04
#घोषणा MD0_CRC_16	0x05
#घोषणा MD0_CRC_ITU32	0x06
#घोषणा MD0_CRC_ITU	0x07

#घोषणा MD1_NOADDR	0x00
#घोषणा MD1_SADDR1	0x40
#घोषणा MD1_SADDR2	0x80
#घोषणा MD1_DADDR	0xc0

#घोषणा MD2_NRZI_IEEE	0x40
#घोषणा MD2_MANCHESTER	0x80
#घोषणा MD2_FM_MARK	0xA0
#घोषणा MD2_FM_SPACE	0xC0
#घोषणा MD2_LOOPBACK	0x03	/* Local data Loopback */

#घोषणा MD2_F_DUPLEX	0x00
#घोषणा MD2_AUTO_ECHO	0x01
#घोषणा MD2_LOOP_HI_Z	0x02
#घोषणा MD2_LOOP_MIR	0x03
#घोषणा MD2_ADPLL_X8	0x00
#घोषणा MD2_ADPLL_X16	0x08
#घोषणा MD2_ADPLL_X32	0x10
#घोषणा MD2_NRZ		0x00
#घोषणा MD2_NRZI	0x20
#घोषणा MD2_NRZ_IEEE	0x40
#घोषणा MD2_MANCH	0x00
#घोषणा MD2_FM1		0x20
#घोषणा MD2_FM0		0x40
#घोषणा MD2_FM		0x80

#घोषणा CTL_RTS		0x01
#घोषणा CTL_DTR		0x02
#घोषणा CTL_SYN		0x04
#घोषणा CTL_IDLC	0x10
#घोषणा CTL_UDRNC	0x20
#घोषणा CTL_URSKP	0x40
#घोषणा CTL_URCT	0x80

#घोषणा CTL_NORTS	0x01
#घोषणा CTL_NODTR	0x02
#घोषणा CTL_IDLE	0x10

#घोषणा	RXS_BR0		0x01
#घोषणा	RXS_BR1		0x02
#घोषणा	RXS_BR2		0x04
#घोषणा	RXS_BR3		0x08
#घोषणा	RXS_ECLK	0x00
#घोषणा	RXS_ECLK_NS	0x20
#घोषणा	RXS_IBRG	0x40
#घोषणा	RXS_PLL1	0x50
#घोषणा	RXS_PLL2	0x60
#घोषणा	RXS_PLL3	0x70
#घोषणा	RXS_DRTXC	0x80

#घोषणा	TXS_BR0		0x01
#घोषणा	TXS_BR1		0x02
#घोषणा	TXS_BR2		0x04
#घोषणा	TXS_BR3		0x08
#घोषणा	TXS_ECLK	0x00
#घोषणा	TXS_IBRG	0x40
#घोषणा	TXS_RCLK	0x60
#घोषणा	TXS_DTRXC	0x80

#घोषणा	EXS_RES0	0x01
#घोषणा	EXS_RES1	0x02
#घोषणा	EXS_RES2	0x04
#घोषणा	EXS_TES0	0x10
#घोषणा	EXS_TES1	0x20
#घोषणा	EXS_TES2	0x40

#घोषणा CLK_BRG_MASK	0x0F
#घोषणा CLK_PIN_OUT	0x80
#घोषणा CLK_LINE    	0x00	/* घड़ी line input */
#घोषणा CLK_BRG     	0x40	/* पूर्णांकernal baud rate generator */
#घोषणा CLK_TX_RXCLK	0x60	/* TX घड़ी from RX घड़ी */

#घोषणा CMD_RX_RST	0x11
#घोषणा CMD_RX_ENA	0x12
#घोषणा CMD_RX_DIS	0x13
#घोषणा CMD_RX_CRC_INIT	0x14
#घोषणा CMD_RX_MSG_REJ	0x15
#घोषणा CMD_RX_MP_SRCH	0x16
#घोषणा CMD_RX_CRC_EXC	0x17
#घोषणा CMD_RX_CRC_FRC	0x18
#घोषणा CMD_TX_RST	0x01
#घोषणा CMD_TX_ENA	0x02
#घोषणा CMD_TX_DISA	0x03
#घोषणा CMD_TX_CRC_INIT	0x04
#घोषणा CMD_TX_CRC_EXC	0x05
#घोषणा CMD_TX_EOM	0x06
#घोषणा CMD_TX_ABORT	0x07
#घोषणा CMD_TX_MP_ON	0x08
#घोषणा CMD_TX_BUF_CLR	0x09
#घोषणा CMD_TX_DISB	0x0b
#घोषणा CMD_CH_RST	0x21
#घोषणा CMD_SRCH_MODE	0x31
#घोषणा CMD_NOP		0x00

#घोषणा CMD_RESET	0x21
#घोषणा CMD_TX_ENABLE	0x02
#घोषणा CMD_RX_ENABLE	0x12

#घोषणा ST0_RXRDY	0x01
#घोषणा ST0_TXRDY	0x02
#घोषणा ST0_RXINTB	0x20
#घोषणा ST0_RXINTA	0x40
#घोषणा ST0_TXINT	0x80

#घोषणा ST1_IDLE	0x01
#घोषणा ST1_ABORT	0x02
#घोषणा ST1_CDCD	0x04
#घोषणा ST1_CCTS	0x08
#घोषणा ST1_SYN_FLAG	0x10
#घोषणा ST1_CLMD	0x20
#घोषणा ST1_TXIDLE	0x40
#घोषणा ST1_UDRN	0x80

#घोषणा ST2_CRCE	0x04
#घोषणा ST2_ONRN	0x08
#घोषणा ST2_RBIT	0x10
#घोषणा ST2_ABORT	0x20
#घोषणा ST2_SHORT	0x40
#घोषणा ST2_EOM		0x80

#घोषणा ST3_RX_ENA	0x01
#घोषणा ST3_TX_ENA	0x02
#घोषणा ST3_DCD		0x04
#घोषणा ST3_CTS		0x08
#घोषणा ST3_SRCH_MODE	0x10
#घोषणा ST3_SLOOP	0x20
#घोषणा ST3_GPI		0x80

#घोषणा ST4_RDNR	0x01
#घोषणा ST4_RDCR	0x02
#घोषणा ST4_TDNR	0x04
#घोषणा ST4_TDCR	0x08
#घोषणा ST4_OCLM	0x20
#घोषणा ST4_CFT		0x40
#घोषणा ST4_CGPI	0x80

#घोषणा FST_CRCEF	0x04
#घोषणा FST_OVRNF	0x08
#घोषणा FST_RBIF	0x10
#घोषणा FST_ABTF	0x20
#घोषणा FST_SHRTF	0x40
#घोषणा FST_EOMF	0x80

#घोषणा IE0_RXRDY	0x01
#घोषणा IE0_TXRDY	0x02
#घोषणा IE0_RXINTB	0x20
#घोषणा IE0_RXINTA	0x40
#घोषणा IE0_TXINT	0x80
#घोषणा IE0_UDRN	0x00008000 /* TX underrun MSCI पूर्णांकerrupt enable */
#घोषणा IE0_CDCD	0x00000400 /* CD level change पूर्णांकerrupt enable */

#घोषणा IE1_IDLD	0x01
#घोषणा IE1_ABTD	0x02
#घोषणा IE1_CDCD	0x04
#घोषणा IE1_CCTS	0x08
#घोषणा IE1_SYNCD	0x10
#घोषणा IE1_CLMD	0x20
#घोषणा IE1_IDL		0x40
#घोषणा IE1_UDRN	0x80

#घोषणा IE2_CRCE	0x04
#घोषणा IE2_OVRN	0x08
#घोषणा IE2_RBIT	0x10
#घोषणा IE2_ABT		0x20
#घोषणा IE2_SHRT	0x40
#घोषणा IE2_EOM		0x80

#घोषणा IE4_RDNR	0x01
#घोषणा IE4_RDCR	0x02
#घोषणा IE4_TDNR	0x04
#घोषणा IE4_TDCR	0x08
#घोषणा IE4_OCLM	0x20
#घोषणा IE4_CFT		0x40
#घोषणा IE4_CGPI	0x80

#घोषणा FIE_CRCEF	0x04
#घोषणा FIE_OVRNF	0x08
#घोषणा FIE_RBIF	0x10
#घोषणा FIE_ABTF	0x20
#घोषणा FIE_SHRTF	0x40
#घोषणा FIE_EOMF	0x80

#घोषणा DSR_DWE		0x01
#घोषणा DSR_DE		0x02
#घोषणा DSR_REF		0x04
#घोषणा DSR_UDRF	0x04
#घोषणा DSR_COA		0x08
#घोषणा DSR_COF		0x10
#घोषणा DSR_BOF		0x20
#घोषणा DSR_EOM		0x40
#घोषणा DSR_EOT		0x80

#घोषणा सूची_REF		0x04
#घोषणा सूची_UDRF	0x04
#घोषणा सूची_COA		0x08
#घोषणा सूची_COF		0x10
#घोषणा सूची_BOF		0x20
#घोषणा सूची_EOM		0x40
#घोषणा सूची_EOT		0x80

#घोषणा सूची_REFE	0x04
#घोषणा सूची_UDRFE	0x04
#घोषणा सूची_COAE	0x08
#घोषणा सूची_COFE	0x10
#घोषणा सूची_BOFE	0x20
#घोषणा सूची_EOME	0x40
#घोषणा सूची_EOTE	0x80

#घोषणा DMR_CNTE	0x02
#घोषणा DMR_NF		0x04
#घोषणा DMR_SEOME	0x08
#घोषणा DMR_TMOD	0x10

#घोषणा DMER_DME        0x80	/* DMA Master Enable */

#घोषणा DCR_SW_ABT	0x01
#घोषणा DCR_FCT_CLR	0x02

#घोषणा DCR_ABORT	0x01
#घोषणा DCR_CLEAR_खातापूर्ण	0x02

#घोषणा PCR_COTE	0x80
#घोषणा PCR_PR0		0x01
#घोषणा PCR_PR1		0x02
#घोषणा PCR_PR2		0x04
#घोषणा PCR_CCC		0x08
#घोषणा PCR_BRC		0x10
#घोषणा PCR_OSB		0x40
#घोषणा PCR_BURST	0x80

#पूर्ण_अगर /* (__HD64572_H) */
