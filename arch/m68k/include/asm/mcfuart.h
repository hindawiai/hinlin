<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	mcfuart.h -- ColdFire पूर्णांकernal UART support defines.
 *
 *	(C) Copyright 1999-2003, Greg Ungerer (gerg@snapgear.com)
 * 	(C) Copyright 2000, Lineo Inc. (www.lineo.com) 
 */

/****************************************************************************/
#अगर_अघोषित	mcfuart_h
#घोषणा	mcfuart_h
/****************************************************************************/

#समावेश <linux/serial_core.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा mcf_platक्रमm_uart अणु
	अचिन्हित दीर्घ	mapbase;	/* Physical address base */
	व्योम __iomem	*membase;	/* Virtual address अगर mapped */
	अचिन्हित पूर्णांक	irq;		/* Interrupt vector */
	अचिन्हित पूर्णांक	uartclk;	/* UART घड़ी rate */
पूर्ण;

/*
 *	Define the ColdFire UART रेजिस्टर set addresses.
 */
#घोषणा	MCFUART_UMR		0x00		/* Mode रेजिस्टर (r/w) */
#घोषणा	MCFUART_USR		0x04		/* Status रेजिस्टर (r) */
#घोषणा	MCFUART_UCSR		0x04		/* Clock Select (w) */
#घोषणा	MCFUART_UCR		0x08		/* Command रेजिस्टर (w) */
#घोषणा	MCFUART_URB		0x0c		/* Receiver Buffer (r) */
#घोषणा	MCFUART_UTB		0x0c		/* Transmit Buffer (w) */
#घोषणा	MCFUART_UIPCR		0x10		/* Input Port Change (r) */
#घोषणा	MCFUART_UACR		0x10		/* Auxiliary Control (w) */
#घोषणा	MCFUART_UISR		0x14		/* Interrupt Status (r) */
#घोषणा	MCFUART_UIMR		0x14		/* Interrupt Mask (w) */
#घोषणा	MCFUART_UBG1		0x18		/* Baud Rate MSB (r/w) */
#घोषणा	MCFUART_UBG2		0x1c		/* Baud Rate LSB (r/w) */
#अगर_घोषित	CONFIG_M5272
#घोषणा	MCFUART_UTF		0x28		/* Transmitter FIFO (r/w) */
#घोषणा	MCFUART_URF		0x2c		/* Receiver FIFO (r/w) */
#घोषणा	MCFUART_UFPD		0x30		/* Frac Prec. Divider (r/w) */
#पूर्ण_अगर
#अगर defined(CONFIG_M5206) || defined(CONFIG_M5206e) || \
	defined(CONFIG_M5249) || defined(CONFIG_M525x) || \
	defined(CONFIG_M5307) || defined(CONFIG_M5407)
#घोषणा	MCFUART_UIVR		0x30		/* Interrupt Vector (r/w) */
#पूर्ण_अगर
#घोषणा	MCFUART_UIPR		0x34		/* Input Port (r) */
#घोषणा	MCFUART_UOP1		0x38		/* Output Port Bit Set (w) */
#घोषणा	MCFUART_UOP0		0x3c		/* Output Port Bit Reset (w) */


/*
 *	Define bit flags in Mode Register 1 (MR1).
 */
#घोषणा	MCFUART_MR1_RXRTS	0x80		/* Auto RTS flow control */
#घोषणा	MCFUART_MR1_RXIRQFULL	0x40		/* RX IRQ type FULL */
#घोषणा	MCFUART_MR1_RXIRQRDY	0x00		/* RX IRQ type RDY */
#घोषणा	MCFUART_MR1_RXERRBLOCK	0x20		/* RX block error mode */
#घोषणा	MCFUART_MR1_RXERRCHAR	0x00		/* RX अक्षर error mode */

#घोषणा	MCFUART_MR1_PARITYNONE	0x10		/* No parity */
#घोषणा	MCFUART_MR1_PARITYEVEN	0x00		/* Even parity */
#घोषणा	MCFUART_MR1_PARITYODD	0x04		/* Odd parity */
#घोषणा	MCFUART_MR1_PARITYSPACE	0x08		/* Space parity */
#घोषणा	MCFUART_MR1_PARITYMARK	0x0c		/* Mark parity */

#घोषणा	MCFUART_MR1_CS5		0x00		/* 5 bits per अक्षर */
#घोषणा	MCFUART_MR1_CS6		0x01		/* 6 bits per अक्षर */
#घोषणा	MCFUART_MR1_CS7		0x02		/* 7 bits per अक्षर */
#घोषणा	MCFUART_MR1_CS8		0x03		/* 8 bits per अक्षर */

/*
 *	Define bit flags in Mode Register 2 (MR2).
 */
#घोषणा	MCFUART_MR2_LOOPBACK	0x80		/* Loopback mode */
#घोषणा	MCFUART_MR2_REMOTELOOP	0xc0		/* Remote loopback mode */
#घोषणा	MCFUART_MR2_AUTOECHO	0x40		/* Automatic echo */
#घोषणा	MCFUART_MR2_TXRTS	0x20		/* Assert RTS on TX */
#घोषणा	MCFUART_MR2_TXCTS	0x10		/* Auto CTS flow control */

#घोषणा	MCFUART_MR2_STOP1	0x07		/* 1 stop bit */
#घोषणा	MCFUART_MR2_STOP15	0x08		/* 1.5 stop bits */
#घोषणा	MCFUART_MR2_STOP2	0x0f		/* 2 stop bits */

/*
 *	Define bit flags in Status Register (USR).
 */
#घोषणा	MCFUART_USR_RXBREAK	0x80		/* Received BREAK */
#घोषणा	MCFUART_USR_RXFRAMING	0x40		/* Received framing error */
#घोषणा	MCFUART_USR_RXPARITY	0x20		/* Received parity error */
#घोषणा	MCFUART_USR_RXOVERRUN	0x10		/* Received overrun error */
#घोषणा	MCFUART_USR_TXEMPTY	0x08		/* Transmitter empty */
#घोषणा	MCFUART_USR_TXREADY	0x04		/* Transmitter पढ़ोy */
#घोषणा	MCFUART_USR_RXFULL	0x02		/* Receiver full */
#घोषणा	MCFUART_USR_RXREADY	0x01		/* Receiver पढ़ोy */

#घोषणा	MCFUART_USR_RXERR	(MCFUART_USR_RXBREAK | MCFUART_USR_RXFRAMING | \
				MCFUART_USR_RXPARITY | MCFUART_USR_RXOVERRUN)

/*
 *	Define bit flags in Clock Select Register (UCSR).
 */
#घोषणा	MCFUART_UCSR_RXCLKTIMER	0xd0		/* RX घड़ी is समयr */
#घोषणा	MCFUART_UCSR_RXCLKEXT16	0xe0		/* RX घड़ी is बाह्यal x16 */
#घोषणा	MCFUART_UCSR_RXCLKEXT1	0xf0		/* RX घड़ी is बाह्यal x1 */

#घोषणा	MCFUART_UCSR_TXCLKTIMER	0x0d		/* TX घड़ी is समयr */
#घोषणा	MCFUART_UCSR_TXCLKEXT16	0x0e		/* TX घड़ी is बाह्यal x16 */
#घोषणा	MCFUART_UCSR_TXCLKEXT1	0x0f		/* TX घड़ी is बाह्यal x1 */

/*
 *	Define bit flags in Command Register (UCR).
 */
#घोषणा	MCFUART_UCR_CMDशून्य		0x00	/* No command */
#घोषणा	MCFUART_UCR_CMDRESETMRPTR	0x10	/* Reset MR poपूर्णांकer */
#घोषणा	MCFUART_UCR_CMDRESETRX		0x20	/* Reset receiver */
#घोषणा	MCFUART_UCR_CMDRESETTX		0x30	/* Reset transmitter */
#घोषणा	MCFUART_UCR_CMDRESETERR		0x40	/* Reset error status */
#घोषणा	MCFUART_UCR_CMDRESETBREAK	0x50	/* Reset BREAK change */
#घोषणा	MCFUART_UCR_CMDBREAKSTART	0x60	/* Start BREAK */
#घोषणा	MCFUART_UCR_CMDBREAKSTOP	0x70	/* Stop BREAK */

#घोषणा	MCFUART_UCR_TXशून्य	0x00		/* No TX command */
#घोषणा	MCFUART_UCR_TXENABLE	0x04		/* Enable TX */
#घोषणा	MCFUART_UCR_TXDISABLE	0x08		/* Disable TX */
#घोषणा	MCFUART_UCR_RXशून्य	0x00		/* No RX command */
#घोषणा	MCFUART_UCR_RXENABLE	0x01		/* Enable RX */
#घोषणा	MCFUART_UCR_RXDISABLE	0x02		/* Disable RX */

/*
 *	Define bit flags in Input Port Change Register (UIPCR).
 */
#घोषणा	MCFUART_UIPCR_CTSCOS	0x10		/* CTS change of state */
#घोषणा	MCFUART_UIPCR_CTS	0x01		/* CTS value */

/*
 *	Define bit flags in Input Port Register (UIP).
 */
#घोषणा	MCFUART_UIPR_CTS	0x01		/* CTS value */

/*
 *	Define bit flags in Output Port Registers (UOP).
 *	Clear bit by writing to UOP0, set by writing to UOP1.
 */
#घोषणा	MCFUART_UOP_RTS		0x01		/* RTS set or clear */

/*
 *	Define bit flags in the Auxiliary Control Register (UACR).
 */
#घोषणा	MCFUART_UACR_IEC	0x01		/* Input enable control */

/*
 *	Define bit flags in Interrupt Status Register (UISR).
 *	These same bits are used क्रम the Interrupt Mask Register (UIMR).
 */
#घोषणा	MCFUART_UIR_COS		0x80		/* Change of state (CTS) */
#घोषणा	MCFUART_UIR_DELTABREAK	0x04		/* Break start or stop */
#घोषणा	MCFUART_UIR_RXREADY	0x02		/* Receiver पढ़ोy */
#घोषणा	MCFUART_UIR_TXREADY	0x01		/* Transmitter पढ़ोy */

#अगर_घोषित	CONFIG_M5272
/*
 *	Define bit flags in the Transmitter FIFO Register (UTF).
 */
#घोषणा	MCFUART_UTF_TXB		0x1f		/* Transmitter data level */
#घोषणा	MCFUART_UTF_FULL	0x20		/* Transmitter fअगरo full */
#घोषणा	MCFUART_UTF_TXS		0xc0		/* Transmitter status */

/*
 *	Define bit flags in the Receiver FIFO Register (URF).
 */
#घोषणा	MCFUART_URF_RXB		0x1f		/* Receiver data level */
#घोषणा	MCFUART_URF_FULL	0x20		/* Receiver fअगरo full */
#घोषणा	MCFUART_URF_RXS		0xc0		/* Receiver status */
#पूर्ण_अगर

#अगर defined(CONFIG_M54xx)
#घोषणा MCFUART_TXFIFOSIZE	512
#या_अगर defined(CONFIG_M5272)
#घोषणा MCFUART_TXFIFOSIZE	25
#अन्यथा
#घोषणा MCFUART_TXFIFOSIZE	1
#पूर्ण_अगर
/****************************************************************************/
#पूर्ण_अगर	/* mcfuart_h */
