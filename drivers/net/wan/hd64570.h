<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __HD64570_H
#घोषणा __HD64570_H

/* SCA HD64570 रेजिस्टर definitions - all addresses क्रम mode 0 (8086 MPU)
   and 1 (64180 MPU). For modes 2 and 3, XOR the address with 0x01.

   Source: HD64570 SCA User's Manual
*/



/* SCA Control Registers */
#घोषणा LPR    0x00		/* Low Power */

/* Wait controller रेजिस्टरs */
#घोषणा PABR0  0x02		/* Physical Address Boundary 0 */
#घोषणा PABR1  0x03		/* Physical Address Boundary 1 */
#घोषणा WCRL   0x04		/* Wait Control L */
#घोषणा WCRM   0x05		/* Wait Control M */
#घोषणा WCRH   0x06		/* Wait Control H */

#घोषणा PCR    0x08		/* DMA Priority Control */
#घोषणा DMER   0x09		/* DMA Master Enable */


/* Interrupt रेजिस्टरs */
#घोषणा ISR0   0x10		/* Interrupt Status 0  */
#घोषणा ISR1   0x11		/* Interrupt Status 1  */
#घोषणा ISR2   0x12		/* Interrupt Status 2  */

#घोषणा IER0   0x14		/* Interrupt Enable 0  */
#घोषणा IER1   0x15		/* Interrupt Enable 1  */
#घोषणा IER2   0x16		/* Interrupt Enable 2  */

#घोषणा ITCR   0x18		/* Interrupt Control */
#घोषणा IVR    0x1A		/* Interrupt Vector */
#घोषणा IMVR   0x1C		/* Interrupt Modअगरied Vector */



/* MSCI channel (port) 0 रेजिस्टरs - offset 0x20
   MSCI channel (port) 1 रेजिस्टरs - offset 0x40 */

#घोषणा MSCI0_OFFSET 0x20
#घोषणा MSCI1_OFFSET 0x40

#घोषणा TRBL   0x00		/* TX/RX buffer L */ 
#घोषणा TRBH   0x01		/* TX/RX buffer H */ 
#घोषणा ST0    0x02		/* Status 0 */
#घोषणा ST1    0x03		/* Status 1 */
#घोषणा ST2    0x04		/* Status 2 */
#घोषणा ST3    0x05		/* Status 3 */
#घोषणा FST    0x06		/* Frame Status  */
#घोषणा IE0    0x08		/* Interrupt Enable 0 */
#घोषणा IE1    0x09		/* Interrupt Enable 1 */
#घोषणा IE2    0x0A		/* Interrupt Enable 2 */
#घोषणा FIE    0x0B		/* Frame Interrupt Enable  */
#घोषणा CMD    0x0C		/* Command */
#घोषणा MD0    0x0E		/* Mode 0 */
#घोषणा MD1    0x0F		/* Mode 1 */
#घोषणा MD2    0x10		/* Mode 2 */
#घोषणा CTL    0x11		/* Control */
#घोषणा SA0    0x12		/* Sync/Address 0 */
#घोषणा SA1    0x13		/* Sync/Address 1 */
#घोषणा IDL    0x14		/* Idle Pattern */
#घोषणा TMC    0x15		/* Time Constant */
#घोषणा RXS    0x16		/* RX Clock Source */
#घोषणा TXS    0x17		/* TX Clock Source */
#घोषणा TRC0   0x18		/* TX Ready Control 0 */ 
#घोषणा TRC1   0x19		/* TX Ready Control 1 */ 
#घोषणा RRC    0x1A		/* RX Ready Control */ 
#घोषणा CST0   0x1C		/* Current Status 0 */
#घोषणा CST1   0x1D		/* Current Status 1 */


/* Timer channel 0 (port 0 RX) रेजिस्टरs - offset 0x60
   Timer channel 1 (port 0 TX) रेजिस्टरs - offset 0x68
   Timer channel 2 (port 1 RX) रेजिस्टरs - offset 0x70
   Timer channel 3 (port 1 TX) रेजिस्टरs - offset 0x78
*/

#घोषणा TIMER0RX_OFFSET 0x60
#घोषणा TIMER0TX_OFFSET 0x68
#घोषणा TIMER1RX_OFFSET 0x70
#घोषणा TIMER1TX_OFFSET 0x78

#घोषणा TCNTL  0x00		/* Up-counter L */
#घोषणा TCNTH  0x01		/* Up-counter H */
#घोषणा TCONRL 0x02		/* Constant L */
#घोषणा TCONRH 0x03		/* Constant H */
#घोषणा TCSR   0x04		/* Control/Status */
#घोषणा TEPR   0x05		/* Expand Prescale */



/* DMA channel 0 (port 0 RX) रेजिस्टरs - offset 0x80
   DMA channel 1 (port 0 TX) रेजिस्टरs - offset 0xA0
   DMA channel 2 (port 1 RX) रेजिस्टरs - offset 0xC0
   DMA channel 3 (port 1 TX) रेजिस्टरs - offset 0xE0
*/

#घोषणा DMAC0RX_OFFSET 0x80
#घोषणा DMAC0TX_OFFSET 0xA0
#घोषणा DMAC1RX_OFFSET 0xC0
#घोषणा DMAC1TX_OFFSET 0xE0

#घोषणा BARL   0x00		/* Buffer Address L (chained block) */
#घोषणा BARH   0x01		/* Buffer Address H (chained block) */
#घोषणा BARB   0x02		/* Buffer Address B (chained block) */

#घोषणा DARL   0x00		/* RX Destination Addr L (single block) */
#घोषणा DARH   0x01		/* RX Destination Addr H (single block) */
#घोषणा DARB   0x02		/* RX Destination Addr B (single block) */

#घोषणा SARL   0x04		/* TX Source Address L (single block) */
#घोषणा SARH   0x05		/* TX Source Address H (single block) */
#घोषणा SARB   0x06		/* TX Source Address B (single block) */

#घोषणा CPB    0x06		/* Chain Poपूर्णांकer Base (chained block) */

#घोषणा CDAL   0x08		/* Current Descriptor Addr L (chained block) */
#घोषणा CDAH   0x09		/* Current Descriptor Addr H (chained block) */
#घोषणा EDAL   0x0A		/* Error Descriptor Addr L (chained block) */
#घोषणा EDAH   0x0B		/* Error Descriptor Addr H (chained block) */
#घोषणा BFLL   0x0C		/* RX Receive Buffer Length L (chained block)*/
#घोषणा BFLH   0x0D		/* RX Receive Buffer Length H (chained block)*/
#घोषणा BCRL   0x0E		/* Byte Count L */
#घोषणा BCRH   0x0F		/* Byte Count H */
#घोषणा DSR    0x10		/* DMA Status */
#घोषणा DSR_RX(node) (DSR + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
#घोषणा DSR_TX(node) (DSR + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
#घोषणा DMR    0x11		/* DMA Mode */
#घोषणा DMR_RX(node) (DMR + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
#घोषणा DMR_TX(node) (DMR + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
#घोषणा FCT    0x13		/* Frame End Interrupt Counter */
#घोषणा FCT_RX(node) (FCT + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
#घोषणा FCT_TX(node) (FCT + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
#घोषणा सूची    0x14		/* DMA Interrupt Enable */
#घोषणा सूची_RX(node) (सूची + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
#घोषणा सूची_TX(node) (सूची + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))
#घोषणा DCR    0x15		/* DMA Command  */
#घोषणा DCR_RX(node) (DCR + (node ? DMAC1RX_OFFSET : DMAC0RX_OFFSET))
#घोषणा DCR_TX(node) (DCR + (node ? DMAC1TX_OFFSET : DMAC0TX_OFFSET))




/* Descriptor Structure */

प्रकार काष्ठा अणु
	u16 cp;			/* Chain Poपूर्णांकer */
	u32 bp;			/* Buffer Poपूर्णांकer (24 bits) */
	u16 len;		/* Data Length */
	u8 stat;		/* Status */
	u8 unused;		/* pads to 2-byte boundary */
पूर्ण__packed pkt_desc;


/* Packet Descriptor Status bits */

#घोषणा ST_TX_EOM     0x80	/* End of frame */
#घोषणा ST_TX_EOT     0x01	/* End of transmission */

#घोषणा ST_RX_EOM     0x80	/* End of frame */
#घोषणा ST_RX_SHORT   0x40	/* Short frame */
#घोषणा ST_RX_ABORT   0x20	/* Abort */
#घोषणा ST_RX_RESBIT  0x10	/* Residual bit */
#घोषणा ST_RX_OVERRUN 0x08	/* Overrun */
#घोषणा ST_RX_CRC     0x04	/* CRC */

#घोषणा ST_ERROR_MASK 0x7C

#घोषणा सूची_EOTE      0x80      /* Transfer completed */
#घोषणा सूची_EOME      0x40      /* Frame Transfer Completed (chained-block) */
#घोषणा सूची_BOFE      0x20      /* Buffer Overflow/Underflow (chained-block)*/
#घोषणा सूची_COFE      0x10      /* Counter Overflow (chained-block) */


#घोषणा DSR_EOT       0x80      /* Transfer completed */
#घोषणा DSR_EOM       0x40      /* Frame Transfer Completed (chained-block) */
#घोषणा DSR_BOF       0x20      /* Buffer Overflow/Underflow (chained-block)*/
#घोषणा DSR_COF       0x10      /* Counter Overflow (chained-block) */
#घोषणा DSR_DE        0x02	/* DMA Enable */
#घोषणा DSR_DWE       0x01      /* DMA Write Disable */

/* DMA Master Enable Register (DMER) bits */
#घोषणा DMER_DME      0x80	/* DMA Master Enable */


#घोषणा CMD_RESET     0x21	/* Reset Channel */
#घोषणा CMD_TX_ENABLE 0x02	/* Start transmitter */
#घोषणा CMD_RX_ENABLE 0x12	/* Start receiver */

#घोषणा MD0_HDLC      0x80	/* Bit-sync HDLC mode */
#घोषणा MD0_CRC_ENA   0x04	/* Enable CRC code calculation */
#घोषणा MD0_CRC_CCITT 0x02	/* CCITT CRC instead of CRC-16 */
#घोषणा MD0_CRC_PR1   0x01	/* Initial all-ones instead of all-zeros */

#घोषणा MD0_CRC_NONE  0x00
#घोषणा MD0_CRC_16_0  0x04
#घोषणा MD0_CRC_16    0x05
#घोषणा MD0_CRC_ITU_0 0x06
#घोषणा MD0_CRC_ITU   0x07

#घोषणा MD2_NRZ	      0x00
#घोषणा MD2_NRZI      0x20
#घोषणा MD2_MANCHESTER 0x80
#घोषणा MD2_FM_MARK   0xA0
#घोषणा MD2_FM_SPACE  0xC0
#घोषणा MD2_LOOPBACK  0x03      /* Local data Loopback */

#घोषणा CTL_NORTS     0x01
#घोषणा CTL_IDLE      0x10	/* Transmit an idle pattern */
#घोषणा CTL_UDRNC     0x20	/* Idle after CRC or FCS+flag transmission */

#घोषणा ST0_TXRDY     0x02	/* TX पढ़ोy */
#घोषणा ST0_RXRDY     0x01	/* RX पढ़ोy */

#घोषणा ST1_UDRN      0x80	/* MSCI TX underrun */
#घोषणा ST1_CDCD      0x04	/* DCD level changed */

#घोषणा ST3_CTS       0x08	/* modem input - /CTS */
#घोषणा ST3_DCD       0x04	/* modem input - /DCD */

#घोषणा IE0_TXINT     0x80	/* TX INT MSCI पूर्णांकerrupt enable */
#घोषणा IE0_RXINTA    0x40	/* RX INT A MSCI पूर्णांकerrupt enable */
#घोषणा IE1_UDRN      0x80	/* TX underrun MSCI पूर्णांकerrupt enable */
#घोषणा IE1_CDCD      0x04	/* DCD level changed */

#घोषणा DCR_ABORT     0x01	/* Software पात command */
#घोषणा DCR_CLEAR_खातापूर्ण 0x02	/* Clear खातापूर्ण पूर्णांकerrupt */

/* TX and RX Clock Source - RXS and TXS */
#घोषणा CLK_BRG_MASK  0x0F
#घोषणा CLK_LINE_RX   0x00	/* TX/RX घड़ी line input */
#घोषणा CLK_LINE_TX   0x00	/* TX/RX line input */
#घोषणा CLK_BRG_RX    0x40	/* पूर्णांकernal baud rate generator */
#घोषणा CLK_BRG_TX    0x40	/* पूर्णांकernal baud rate generator */
#घोषणा CLK_RXCLK_TX  0x60	/* TX घड़ी from RX घड़ी */

#पूर्ण_अगर
