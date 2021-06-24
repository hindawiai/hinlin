<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/************************************************************************
 *
 *	16654.H		Definitions क्रम 16C654 UART used on EdgePorts
 *
 *	Copyright (C) 1998 Inside Out Networks, Inc.
 *
 ************************************************************************/

#अगर !defined(_16654_H)
#घोषणा	_16654_H

/************************************************************************
 *
 *			D e f i n e s   /   T y p e d e f s
 *
 ************************************************************************/

	//
	// UART रेजिस्टर numbers
	// Numbers 0-7 are passed to the Edgeport directly. Numbers 8 and
	// above are used पूर्णांकernally to indicate that we must enable access
	// to them via LCR bit 0x80 or LCR = 0xBF.
	// The रेजिस्टर number sent to the Edgeport is then (x & 0x7).
	//
	// Driver must not access रेजिस्टरs that affect operation of the
	// the EdgePort firmware -- that includes THR, RHR, IER, FCR.


#घोषणा THR			0	// ! Transmit Holding Register (Write)
#घोषणा RDR			0	// ! Receive Holding Register (Read)
#घोषणा IER			1	// ! Interrupt Enable Register
#घोषणा FCR			2	// ! Fअगरo Control Register (Write)
#घोषणा ISR			2	// Interrupt Status Register (Read)
#घोषणा LCR			3	// Line Control Register
#घोषणा MCR			4	// Modem Control Register
#घोषणा LSR			5	// Line Status Register
#घोषणा MSR			6	// Modem Status Register
#घोषणा SPR			7	// ScratchPad Register
#घोषणा DLL			8	// Bank2[ 0 ] Divisor Latch LSB
#घोषणा DLM			9	// Bank2[ 1 ] Divisor Latch MSB
#घोषणा EFR			10	// Bank2[ 2 ] Extended Function Register
//efine unused			11	// Bank2[ 3 ]
#घोषणा XON1			12	// Bank2[ 4 ] Xon-1
#घोषणा XON2			13	// Bank2[ 5 ] Xon-2
#घोषणा XOFF1			14	// Bank2[ 6 ] Xoff-1
#घोषणा XOFF2			15	// Bank2[ 7 ] Xoff-2

#घोषणा	NUM_16654_REGS		16

#घोषणा IS_REG_2ND_BANK(x)	((x) >= 8)

	//
	// Bit definitions क्रम each रेजिस्टर
	//

#घोषणा IER_RX			0x01	// Enable receive पूर्णांकerrupt
#घोषणा IER_TX			0x02	// Enable transmit पूर्णांकerrupt
#घोषणा IER_RXS			0x04	// Enable receive status पूर्णांकerrupt
#घोषणा IER_MDM			0x08	// Enable modem status पूर्णांकerrupt
#घोषणा IER_SLEEP		0x10	// Enable sleep mode
#घोषणा IER_XOFF		0x20	// Enable s/w flow control (XOFF) पूर्णांकerrupt
#घोषणा IER_RTS			0x40	// Enable RTS पूर्णांकerrupt
#घोषणा IER_CTS			0x80	// Enable CTS पूर्णांकerrupt
#घोषणा IER_ENABLE_ALL		0xFF	// Enable all पूर्णांकs


#घोषणा FCR_FIFO_EN		0x01	// Enable FIFOs
#घोषणा FCR_RXCLR		0x02	// Reset Rx FIFO
#घोषणा FCR_TXCLR		0x04	// Reset Tx FIFO
#घोषणा FCR_DMA_BLK		0x08	// Enable DMA block mode
#घोषणा FCR_TX_LEVEL_MASK	0x30	// Mask क्रम Tx FIFO Level
#घोषणा FCR_TX_LEVEL_8		0x00	// Tx FIFO Level =  8 bytes
#घोषणा FCR_TX_LEVEL_16		0x10	// Tx FIFO Level = 16 bytes
#घोषणा FCR_TX_LEVEL_32		0x20	// Tx FIFO Level = 32 bytes
#घोषणा FCR_TX_LEVEL_56		0x30	// Tx FIFO Level = 56 bytes
#घोषणा FCR_RX_LEVEL_MASK	0xC0	// Mask क्रम Rx FIFO Level
#घोषणा FCR_RX_LEVEL_8		0x00	// Rx FIFO Level =  8 bytes
#घोषणा FCR_RX_LEVEL_16		0x40	// Rx FIFO Level = 16 bytes
#घोषणा FCR_RX_LEVEL_56		0x80	// Rx FIFO Level = 56 bytes
#घोषणा FCR_RX_LEVEL_60		0xC0	// Rx FIFO Level = 60 bytes


#घोषणा ISR_INT_MDM_STATUS	0x00	// Modem status पूर्णांक pending
#घोषणा ISR_INT_NONE		0x01	// No पूर्णांकerrupt pending
#घोषणा ISR_INT_TXRDY		0x02	// Tx पढ़ोy पूर्णांक pending
#घोषणा ISR_INT_RXRDY		0x04	// Rx पढ़ोy पूर्णांक pending
#घोषणा ISR_INT_LINE_STATUS	0x06	// Line status पूर्णांक pending
#घोषणा ISR_INT_RX_TIMEOUT	0x0C	// Rx समयout पूर्णांक pending
#घोषणा ISR_INT_RX_XOFF		0x10	// Rx Xoff पूर्णांक pending
#घोषणा ISR_INT_RTS_CTS		0x20	// RTS/CTS change पूर्णांक pending
#घोषणा ISR_FIFO_ENABLED	0xC0	// Bits set अगर FIFOs enabled
#घोषणा ISR_INT_BITS_MASK	0x3E	// Mask to isolate valid पूर्णांक causes


#घोषणा LCR_BITS_5		0x00	// 5 bits/अक्षर
#घोषणा LCR_BITS_6		0x01	// 6 bits/अक्षर
#घोषणा LCR_BITS_7		0x02	// 7 bits/अक्षर
#घोषणा LCR_BITS_8		0x03	// 8 bits/अक्षर
#घोषणा LCR_BITS_MASK		0x03	// Mask क्रम bits/अक्षर field

#घोषणा LCR_STOP_1		0x00	// 1 stop bit
#घोषणा LCR_STOP_1_5		0x04	// 1.5 stop bits (अगर 5   bits/अक्षर)
#घोषणा LCR_STOP_2		0x04	// 2 stop bits   (अगर 6-8 bits/अक्षर)
#घोषणा LCR_STOP_MASK		0x04	// Mask क्रम stop bits field

#घोषणा LCR_PAR_NONE		0x00	// No parity
#घोषणा LCR_PAR_ODD		0x08	// Odd parity
#घोषणा LCR_PAR_EVEN		0x18	// Even parity
#घोषणा LCR_PAR_MARK		0x28	// Force parity bit to 1
#घोषणा LCR_PAR_SPACE		0x38	// Force parity bit to 0
#घोषणा LCR_PAR_MASK		0x38	// Mask क्रम parity field

#घोषणा LCR_SET_BREAK		0x40	// Set Break condition
#घोषणा LCR_DL_ENABLE		0x80	// Enable access to भागisor latch

#घोषणा LCR_ACCESS_EFR		0xBF	// Load this value to access DLL,DLM,
					// and also the '654-only रेजिस्टरs
					// EFR, XON1, XON2, XOFF1, XOFF2


#घोषणा MCR_DTR			0x01	// Assert DTR
#घोषणा MCR_RTS			0x02	// Assert RTS
#घोषणा MCR_OUT1		0x04	// Loopback only: Sets state of RI
#घोषणा MCR_MASTER_IE		0x08	// Enable पूर्णांकerrupt outमाला_दो
#घोषणा MCR_LOOPBACK		0x10	// Set पूर्णांकernal (digital) loopback mode
#घोषणा MCR_XON_ANY		0x20	// Enable any अक्षर to निकास XOFF mode
#घोषणा MCR_IR_ENABLE		0x40	// Enable IrDA functions
#घोषणा MCR_BRG_DIV_4		0x80	// Divide baud rate clk by /4 instead of /1


#घोषणा LSR_RX_AVAIL		0x01	// Rx data available
#घोषणा LSR_OVER_ERR		0x02	// Rx overrun
#घोषणा LSR_PAR_ERR		0x04	// Rx parity error
#घोषणा LSR_FRM_ERR		0x08	// Rx framing error
#घोषणा LSR_BREAK		0x10	// Rx अवरोध condition detected
#घोषणा LSR_TX_EMPTY		0x20	// Tx Fअगरo empty
#घोषणा LSR_TX_ALL_EMPTY	0x40	// Tx Fअगरo and shअगरt रेजिस्टर empty
#घोषणा LSR_FIFO_ERR		0x80	// Rx Fअगरo contains at least 1 erred अक्षर


#घोषणा EDGEPORT_MSR_DELTA_CTS	0x01	// CTS changed from last पढ़ो
#घोषणा EDGEPORT_MSR_DELTA_DSR	0x02	// DSR changed from last पढ़ो
#घोषणा EDGEPORT_MSR_DELTA_RI	0x04	// RI  changed from 0 -> 1
#घोषणा EDGEPORT_MSR_DELTA_CD	0x08	// CD  changed from last पढ़ो
#घोषणा EDGEPORT_MSR_CTS	0x10	// Current state of CTS
#घोषणा EDGEPORT_MSR_DSR	0x20	// Current state of DSR
#घोषणा EDGEPORT_MSR_RI		0x40	// Current state of RI
#घोषणा EDGEPORT_MSR_CD		0x80	// Current state of CD



					//	Tx		Rx
					//-------------------------------
#घोषणा EFR_SWFC_NONE		0x00	//	None		None
#घोषणा EFR_SWFC_RX1		0x02 	//	None		XOFF1
#घोषणा EFR_SWFC_RX2		0x01 	//	None		XOFF2
#घोषणा EFR_SWFC_RX12		0x03 	//	None		XOFF1 & XOFF2
#घोषणा EFR_SWFC_TX1		0x08 	//	XOFF1		None
#घोषणा EFR_SWFC_TX1_RX1	0x0a 	//	XOFF1		XOFF1
#घोषणा EFR_SWFC_TX1_RX2	0x09 	//	XOFF1		XOFF2
#घोषणा EFR_SWFC_TX1_RX12	0x0b 	//	XOFF1		XOFF1 & XOFF2
#घोषणा EFR_SWFC_TX2		0x04 	//	XOFF2		None
#घोषणा EFR_SWFC_TX2_RX1	0x06 	//	XOFF2		XOFF1
#घोषणा EFR_SWFC_TX2_RX2	0x05 	//	XOFF2		XOFF2
#घोषणा EFR_SWFC_TX2_RX12	0x07 	//	XOFF2		XOFF1 & XOFF2
#घोषणा EFR_SWFC_TX12		0x0c 	//	XOFF1 & XOFF2	None
#घोषणा EFR_SWFC_TX12_RX1	0x0e 	//	XOFF1 & XOFF2	XOFF1
#घोषणा EFR_SWFC_TX12_RX2	0x0d 	//	XOFF1 & XOFF2	XOFF2
#घोषणा EFR_SWFC_TX12_RX12	0x0f 	//	XOFF1 & XOFF2	XOFF1 & XOFF2

#घोषणा EFR_TX_FC_MASK		0x0c	// Mask to isolate Rx flow control
#घोषणा EFR_TX_FC_NONE		0x00	// No Tx Xon/Xoff flow control
#घोषणा EFR_TX_FC_X1		0x08	// Transmit Xon1/Xoff1
#घोषणा EFR_TX_FC_X2		0x04	// Transmit Xon2/Xoff2
#घोषणा EFR_TX_FC_X1_2		0x0c	// Transmit Xon1&2/Xoff1&2

#घोषणा EFR_RX_FC_MASK		0x03	// Mask to isolate Rx flow control
#घोषणा EFR_RX_FC_NONE		0x00	// No Rx Xon/Xoff flow control
#घोषणा EFR_RX_FC_X1		0x02	// Receiver compares Xon1/Xoff1
#घोषणा EFR_RX_FC_X2		0x01	// Receiver compares Xon2/Xoff2
#घोषणा EFR_RX_FC_X1_2		0x03	// Receiver compares Xon1&2/Xoff1&2


#घोषणा EFR_SWFC_MASK		0x0F	// Mask क्रम software flow control field
#घोषणा EFR_ENABLE_16654	0x10	// Enable 16C654 features
#घोषणा EFR_SPEC_DETECT		0x20	// Enable special अक्षरacter detect पूर्णांकerrupt
#घोषणा EFR_AUTO_RTS		0x40	// Use RTS क्रम Rx flow control
#घोषणा EFR_AUTO_CTS		0x80	// Use CTS क्रम Tx flow control

#पूर्ण_अगर	// अगर !defined(_16654_H)

