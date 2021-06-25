<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * include/linux/aपंचांगel_serial.h
 *
 * Copyright (C) 2005 Ivan Kokshaysky
 * Copyright (C) SAN People
 *
 * USART रेजिस्टरs.
 * Based on AT91RM9200 datasheet revision E.
 */

#अगर_अघोषित ATMEL_SERIAL_H
#घोषणा ATMEL_SERIAL_H

#घोषणा ATMEL_US_CR		0x00	/* Control Register */
#घोषणा	ATMEL_US_RSTRX		BIT(2)	/* Reset Receiver */
#घोषणा	ATMEL_US_RSTTX		BIT(3)	/* Reset Transmitter */
#घोषणा	ATMEL_US_RXEN		BIT(4)	/* Receiver Enable */
#घोषणा	ATMEL_US_RXDIS		BIT(5)	/* Receiver Disable */
#घोषणा	ATMEL_US_TXEN		BIT(6)	/* Transmitter Enable */
#घोषणा	ATMEL_US_TXDIS		BIT(7)	/* Transmitter Disable */
#घोषणा	ATMEL_US_RSTSTA		BIT(8)	/* Reset Status Bits */
#घोषणा	ATMEL_US_STTBRK		BIT(9)	/* Start Break */
#घोषणा	ATMEL_US_STPBRK		BIT(10)	/* Stop Break */
#घोषणा	ATMEL_US_STTTO		BIT(11)	/* Start Time-out */
#घोषणा	ATMEL_US_SENDA		BIT(12)	/* Send Address */
#घोषणा	ATMEL_US_RSTIT		BIT(13)	/* Reset Iterations */
#घोषणा	ATMEL_US_RSTNACK	BIT(14)	/* Reset Non Acknowledge */
#घोषणा	ATMEL_US_RETTO		BIT(15)	/* Rearm Time-out */
#घोषणा	ATMEL_US_DTREN		BIT(16)	/* Data Terminal Ready Enable */
#घोषणा	ATMEL_US_DTRDIS		BIT(17)	/* Data Terminal Ready Disable */
#घोषणा	ATMEL_US_RTSEN		BIT(18)	/* Request To Send Enable */
#घोषणा	ATMEL_US_RTSDIS		BIT(19)	/* Request To Send Disable */
#घोषणा	ATMEL_US_TXFCLR		BIT(24)	/* Transmit FIFO Clear */
#घोषणा	ATMEL_US_RXFCLR		BIT(25)	/* Receive FIFO Clear */
#घोषणा	ATMEL_US_TXFLCLR	BIT(26)	/* Transmit FIFO Lock Clear */
#घोषणा	ATMEL_US_FIFOEN		BIT(30)	/* FIFO enable */
#घोषणा	ATMEL_US_FIFODIS	BIT(31)	/* FIFO disable */

#घोषणा ATMEL_US_MR		0x04	/* Mode Register */
#घोषणा	ATMEL_US_USMODE		GENMASK(3, 0)	/* Mode of the USART */
#घोषणा		ATMEL_US_USMODE_NORMAL		0
#घोषणा		ATMEL_US_USMODE_RS485		1
#घोषणा		ATMEL_US_USMODE_HWHS		2
#घोषणा		ATMEL_US_USMODE_MODEM		3
#घोषणा		ATMEL_US_USMODE_ISO7816_T0	4
#घोषणा		ATMEL_US_USMODE_ISO7816_T1	6
#घोषणा		ATMEL_US_USMODE_IRDA		8
#घोषणा	ATMEL_US_USCLKS		GENMASK(5, 4)	/* Clock Selection */
#घोषणा		ATMEL_US_USCLKS_MCK		(0 <<  4)
#घोषणा		ATMEL_US_USCLKS_MCK_DIV8	(1 <<  4)
#घोषणा		ATMEL_US_USCLKS_SCK		(3 <<  4)
#घोषणा	ATMEL_US_CHRL		GENMASK(7, 6)	/* Character Length */
#घोषणा		ATMEL_US_CHRL_5			(0 <<  6)
#घोषणा		ATMEL_US_CHRL_6			(1 <<  6)
#घोषणा		ATMEL_US_CHRL_7			(2 <<  6)
#घोषणा		ATMEL_US_CHRL_8			(3 <<  6)
#घोषणा	ATMEL_US_SYNC		BIT(8)		/* Synchronous Mode Select */
#घोषणा	ATMEL_US_PAR		GENMASK(11, 9)	/* Parity Type */
#घोषणा		ATMEL_US_PAR_EVEN		(0 <<  9)
#घोषणा		ATMEL_US_PAR_ODD		(1 <<  9)
#घोषणा		ATMEL_US_PAR_SPACE		(2 <<  9)
#घोषणा		ATMEL_US_PAR_MARK		(3 <<  9)
#घोषणा		ATMEL_US_PAR_NONE		(4 <<  9)
#घोषणा		ATMEL_US_PAR_MULTI_DROP		(6 <<  9)
#घोषणा	ATMEL_US_NBSTOP		GENMASK(13, 12)	/* Number of Stop Bits */
#घोषणा		ATMEL_US_NBSTOP_1		(0 << 12)
#घोषणा		ATMEL_US_NBSTOP_1_5		(1 << 12)
#घोषणा		ATMEL_US_NBSTOP_2		(2 << 12)
#घोषणा	ATMEL_US_CHMODE		GENMASK(15, 14)	/* Channel Mode */
#घोषणा		ATMEL_US_CHMODE_NORMAL		(0 << 14)
#घोषणा		ATMEL_US_CHMODE_ECHO		(1 << 14)
#घोषणा		ATMEL_US_CHMODE_LOC_LOOP	(2 << 14)
#घोषणा		ATMEL_US_CHMODE_REM_LOOP	(3 << 14)
#घोषणा	ATMEL_US_MSBF		BIT(16)	/* Bit Order */
#घोषणा	ATMEL_US_MODE9		BIT(17)	/* 9-bit Character Length */
#घोषणा	ATMEL_US_CLKO		BIT(18)	/* Clock Output Select */
#घोषणा	ATMEL_US_OVER		BIT(19)	/* Oversampling Mode */
#घोषणा	ATMEL_US_INACK		BIT(20)	/* Inhibit Non Acknowledge */
#घोषणा	ATMEL_US_DSNACK		BIT(21)	/* Disable Successive NACK */
#घोषणा	ATMEL_US_MAX_ITER_MASK	GENMASK(26, 24)	/* Max Iterations */
#घोषणा	ATMEL_US_MAX_ITER(n)	(((n) << 24) & ATMEL_US_MAX_ITER_MASK)
#घोषणा	ATMEL_US_FILTER		BIT(28)	/* Infrared Receive Line Filter */

#घोषणा ATMEL_US_IER		0x08	/* Interrupt Enable Register */
#घोषणा	ATMEL_US_RXRDY		BIT(0)	/* Receiver Ready */
#घोषणा	ATMEL_US_TXRDY		BIT(1)	/* Transmitter Ready */
#घोषणा	ATMEL_US_RXBRK		BIT(2)	/* Break Received / End of Break */
#घोषणा	ATMEL_US_ENDRX		BIT(3)	/* End of Receiver Transfer */
#घोषणा	ATMEL_US_ENDTX		BIT(4)	/* End of Transmitter Transfer */
#घोषणा	ATMEL_US_OVRE		BIT(5)	/* Overrun Error */
#घोषणा	ATMEL_US_FRAME		BIT(6)	/* Framing Error */
#घोषणा	ATMEL_US_PARE		BIT(7)	/* Parity Error */
#घोषणा	ATMEL_US_TIMEOUT	BIT(8)	/* Receiver Time-out */
#घोषणा	ATMEL_US_TXEMPTY	BIT(9)	/* Transmitter Empty */
#घोषणा	ATMEL_US_ITERATION	BIT(10)	/* Max number of Repetitions Reached */
#घोषणा	ATMEL_US_TXBUFE		BIT(11)	/* Transmission Buffer Empty */
#घोषणा	ATMEL_US_RXBUFF		BIT(12)	/* Reception Buffer Full */
#घोषणा	ATMEL_US_NACK		BIT(13)	/* Non Acknowledge */
#घोषणा	ATMEL_US_RIIC		BIT(16)	/* Ring Indicator Input Change */
#घोषणा	ATMEL_US_DSRIC		BIT(17)	/* Data Set Ready Input Change */
#घोषणा	ATMEL_US_DCDIC		BIT(18)	/* Data Carrier Detect Input Change */
#घोषणा	ATMEL_US_CTSIC		BIT(19)	/* Clear to Send Input Change */
#घोषणा	ATMEL_US_RI		BIT(20)	/* RI */
#घोषणा	ATMEL_US_DSR		BIT(21)	/* DSR */
#घोषणा	ATMEL_US_DCD		BIT(22)	/* DCD */
#घोषणा	ATMEL_US_CTS		BIT(23)	/* CTS */

#घोषणा ATMEL_US_IDR		0x0c	/* Interrupt Disable Register */
#घोषणा ATMEL_US_IMR		0x10	/* Interrupt Mask Register */
#घोषणा ATMEL_US_CSR		0x14	/* Channel Status Register */
#घोषणा ATMEL_US_RHR		0x18	/* Receiver Holding Register */
#घोषणा ATMEL_US_THR		0x1c	/* Transmitter Holding Register */
#घोषणा	ATMEL_US_SYNH		BIT(15)	/* Transmit/Receive Sync */

#घोषणा ATMEL_US_BRGR		0x20	/* Baud Rate Generator Register */
#घोषणा	ATMEL_US_CD		GENMASK(15, 0)	/* Clock Divider */
#घोषणा ATMEL_US_FP_OFFSET	16	/* Fractional Part */
#घोषणा ATMEL_US_FP_MASK	0x7

#घोषणा ATMEL_US_RTOR		0x24	/* Receiver Time-out Register क्रम USART */
#घोषणा ATMEL_UA_RTOR		0x28	/* Receiver Time-out Register क्रम UART */
#घोषणा	ATMEL_US_TO		GENMASK(15, 0)	/* Time-out Value */

#घोषणा ATMEL_US_TTGR		0x28	/* Transmitter Timeguard Register */
#घोषणा	ATMEL_US_TG		GENMASK(7, 0)	/* Timeguard Value */

#घोषणा ATMEL_US_FIDI		0x40	/* FI DI Ratio Register */
#घोषणा ATMEL_US_NER		0x44	/* Number of Errors Register */
#घोषणा ATMEL_US_IF		0x4c	/* IrDA Filter Register */

#घोषणा ATMEL_US_CMPR		0x90	/* Comparaison Register */
#घोषणा ATMEL_US_FMR		0xa0	/* FIFO Mode Register */
#घोषणा	ATMEL_US_TXRDYM(data)	(((data) & 0x3) << 0)	/* TX Ready Mode */
#घोषणा	ATMEL_US_RXRDYM(data)	(((data) & 0x3) << 4)	/* RX Ready Mode */
#घोषणा		ATMEL_US_ONE_DATA	0x0
#घोषणा		ATMEL_US_TWO_DATA	0x1
#घोषणा		ATMEL_US_FOUR_DATA	0x2
#घोषणा	ATMEL_US_FRTSC		BIT(7)	/* FIFO RTS pin Control */
#घोषणा	ATMEL_US_TXFTHRES(thr)	(((thr) & 0x3f) << 8)	/* TX FIFO Threshold */
#घोषणा	ATMEL_US_RXFTHRES(thr)	(((thr) & 0x3f) << 16)	/* RX FIFO Threshold */
#घोषणा	ATMEL_US_RXFTHRES2(thr)	(((thr) & 0x3f) << 24)	/* RX FIFO Threshold2 */

#घोषणा ATMEL_US_FLR		0xa4	/* FIFO Level Register */
#घोषणा	ATMEL_US_TXFL(reg)	(((reg) >> 0) & 0x3f)	/* TX FIFO Level */
#घोषणा	ATMEL_US_RXFL(reg)	(((reg) >> 16) & 0x3f)	/* RX FIFO Level */

#घोषणा ATMEL_US_FIER		0xa8	/* FIFO Interrupt Enable Register */
#घोषणा ATMEL_US_FIDR		0xac	/* FIFO Interrupt Disable Register */
#घोषणा ATMEL_US_FIMR		0xb0	/* FIFO Interrupt Mask Register */
#घोषणा ATMEL_US_FESR		0xb4	/* FIFO Event Status Register */
#घोषणा	ATMEL_US_TXFEF		BIT(0)	/* Transmit FIFO Empty Flag */
#घोषणा	ATMEL_US_TXFFF		BIT(1)	/* Transmit FIFO Full Flag */
#घोषणा	ATMEL_US_TXFTHF		BIT(2)	/* Transmit FIFO Threshold Flag */
#घोषणा	ATMEL_US_RXFEF		BIT(3)	/* Receive FIFO Empty Flag */
#घोषणा	ATMEL_US_RXFFF		BIT(4)	/* Receive FIFO Full Flag */
#घोषणा	ATMEL_US_RXFTHF		BIT(5)	/* Receive FIFO Threshold Flag */
#घोषणा	ATMEL_US_TXFPTEF	BIT(6)	/* Transmit FIFO Poपूर्णांकer Error Flag */
#घोषणा	ATMEL_US_RXFPTEF	BIT(7)	/* Receive FIFO Poपूर्णांकer Error Flag */
#घोषणा	ATMEL_US_TXFLOCK	BIT(8)	/* Transmit FIFO Lock (FESR only) */
#घोषणा	ATMEL_US_RXFTHF2	BIT(9)	/* Receive FIFO Threshold Flag 2 */

#घोषणा ATMEL_US_NAME		0xf0	/* Ip Name */
#घोषणा ATMEL_US_VERSION	0xfc	/* Ip Version */

#पूर्ण_अगर
