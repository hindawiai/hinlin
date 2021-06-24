<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	m523xsim.h -- ColdFire 523x System Integration Module support.
 *
 *	(C) Copyright 2003-2005, Greg Ungerer <gerg@snapgear.com>
 */

/****************************************************************************/
#अगर_अघोषित	m523xsim_h
#घोषणा	m523xsim_h
/****************************************************************************/

#घोषणा	CPU_NAME		"COLDFIRE(m523x)"
#घोषणा	CPU_INSTR_PER_JIFFY	3
#घोषणा	MCF_BUSCLK		(MCF_CLK / 2)

#समावेश <यंत्र/m52xxacr.h>

/*
 *	Define the 523x SIM रेजिस्टर set addresses.
 */
#घोषणा	MCFICM_INTC0		(MCF_IPSBAR + 0x0c00)	/* Base क्रम Interrupt Ctrl 0 */
#घोषणा	MCFICM_INTC1		(MCF_IPSBAR + 0x0d00)	/* Base क्रम Interrupt Ctrl 0 */

#घोषणा	MCFINTC_IPRH		0x00		/* Interrupt pending 32-63 */
#घोषणा	MCFINTC_IPRL		0x04		/* Interrupt pending 1-31 */
#घोषणा	MCFINTC_IMRH		0x08		/* Interrupt mask 32-63 */
#घोषणा	MCFINTC_IMRL		0x0c		/* Interrupt mask 1-31 */
#घोषणा	MCFINTC_INTFRCH		0x10		/* Interrupt क्रमce 32-63 */
#घोषणा	MCFINTC_INTFRCL		0x14		/* Interrupt क्रमce 1-31 */
#घोषणा	MCFINTC_IRLR		0x18		/* */
#घोषणा	MCFINTC_IACKL		0x19		/* */
#घोषणा	MCFINTC_ICR0		0x40		/* Base ICR रेजिस्टर */

#घोषणा	MCFINT_VECBASE		64		/* Vector base number */
#घोषणा	MCFINT_UART0		13		/* Interrupt number क्रम UART0 */
#घोषणा	MCFINT_UART1		14		/* Interrupt number क्रम UART1 */
#घोषणा	MCFINT_UART2		15		/* Interrupt number क्रम UART2 */
#घोषणा	MCFINT_I2C0		17		/* Interrupt number क्रम I2C */
#घोषणा	MCFINT_QSPI		18		/* Interrupt number क्रम QSPI */
#घोषणा	MCFINT_FECRX0		23		/* Interrupt number क्रम FEC */
#घोषणा	MCFINT_FECTX0		27		/* Interrupt number क्रम FEC */
#घोषणा	MCFINT_FECENTC0		29		/* Interrupt number क्रम FEC */
#घोषणा	MCFINT_PIT1		36		/* Interrupt number क्रम PIT1 */

#घोषणा	MCF_IRQ_UART0	        (MCFINT_VECBASE + MCFINT_UART0)
#घोषणा	MCF_IRQ_UART1	        (MCFINT_VECBASE + MCFINT_UART1)
#घोषणा	MCF_IRQ_UART2	        (MCFINT_VECBASE + MCFINT_UART2)

#घोषणा	MCF_IRQ_FECRX0		(MCFINT_VECBASE + MCFINT_FECRX0)
#घोषणा	MCF_IRQ_FECTX0		(MCFINT_VECBASE + MCFINT_FECTX0)
#घोषणा	MCF_IRQ_FECENTC0	(MCFINT_VECBASE + MCFINT_FECENTC0)

#घोषणा	MCF_IRQ_QSPI		(MCFINT_VECBASE + MCFINT_QSPI)
#घोषणा MCF_IRQ_PIT1		(MCFINT_VECBASE + MCFINT_PIT1)
#घोषणा	MCF_IRQ_I2C0		(MCFINT_VECBASE + MCFINT_I2C0)

/*
 *	SDRAM configuration रेजिस्टरs.
 */
#घोषणा	MCFSIM_DCR		(MCF_IPSBAR + 0x44)	/* Control */
#घोषणा	MCFSIM_DACR0		(MCF_IPSBAR + 0x48)	/* Base address 0 */
#घोषणा	MCFSIM_DMR0		(MCF_IPSBAR + 0x4c)	/* Address mask 0 */
#घोषणा	MCFSIM_DACR1		(MCF_IPSBAR + 0x50)	/* Base address 1 */
#घोषणा	MCFSIM_DMR1		(MCF_IPSBAR + 0x54)	/* Address mask 1 */

/*
 *  Reset Control Unit (relative to IPSBAR).
 */
#घोषणा	MCF_RCR			(MCF_IPSBAR + 0x110000)
#घोषणा	MCF_RSR			(MCF_IPSBAR + 0x110001)

#घोषणा	MCF_RCR_SWRESET		0x80		/* Software reset bit */
#घोषणा	MCF_RCR_FRCSTOUT	0x40		/* Force बाह्यal reset */

/*
 *  UART module.
 */
#घोषणा MCFUART_BASE0		(MCF_IPSBAR + 0x200)
#घोषणा MCFUART_BASE1		(MCF_IPSBAR + 0x240)
#घोषणा MCFUART_BASE2		(MCF_IPSBAR + 0x280)

/*
 *  FEC ethernet module.
 */
#घोषणा	MCFFEC_BASE0		(MCF_IPSBAR + 0x1000)
#घोषणा	MCFFEC_SIZE0		0x800

/*
 *  QSPI module.
 */
#घोषणा	MCFQSPI_BASE		(MCF_IPSBAR + 0x340)
#घोषणा	MCFQSPI_SIZE		0x40

#घोषणा	MCFQSPI_CS0		91
#घोषणा	MCFQSPI_CS1		92
#घोषणा	MCFQSPI_CS2		103
#घोषणा	MCFQSPI_CS3		99

/*
 *  GPIO module.
 */
#घोषणा MCFGPIO_PODR_ADDR	(MCF_IPSBAR + 0x100000)
#घोषणा MCFGPIO_PODR_DATAH	(MCF_IPSBAR + 0x100001)
#घोषणा MCFGPIO_PODR_DATAL	(MCF_IPSBAR + 0x100002)
#घोषणा MCFGPIO_PODR_BUSCTL	(MCF_IPSBAR + 0x100003)
#घोषणा MCFGPIO_PODR_BS		(MCF_IPSBAR + 0x100004)
#घोषणा MCFGPIO_PODR_CS		(MCF_IPSBAR + 0x100005)
#घोषणा MCFGPIO_PODR_SDRAM	(MCF_IPSBAR + 0x100006)
#घोषणा MCFGPIO_PODR_FECI2C	(MCF_IPSBAR + 0x100007)
#घोषणा MCFGPIO_PODR_UARTH	(MCF_IPSBAR + 0x100008)
#घोषणा MCFGPIO_PODR_UARTL	(MCF_IPSBAR + 0x100009)
#घोषणा MCFGPIO_PODR_QSPI	(MCF_IPSBAR + 0x10000A)
#घोषणा MCFGPIO_PODR_TIMER	(MCF_IPSBAR + 0x10000B)
#घोषणा MCFGPIO_PODR_ETPU	(MCF_IPSBAR + 0x10000C)

#घोषणा MCFGPIO_PDDR_ADDR	(MCF_IPSBAR + 0x100010)
#घोषणा MCFGPIO_PDDR_DATAH	(MCF_IPSBAR + 0x100011)
#घोषणा MCFGPIO_PDDR_DATAL	(MCF_IPSBAR + 0x100012)
#घोषणा MCFGPIO_PDDR_BUSCTL	(MCF_IPSBAR + 0x100013)
#घोषणा MCFGPIO_PDDR_BS		(MCF_IPSBAR + 0x100014)
#घोषणा MCFGPIO_PDDR_CS		(MCF_IPSBAR + 0x100015)
#घोषणा MCFGPIO_PDDR_SDRAM	(MCF_IPSBAR + 0x100016)
#घोषणा MCFGPIO_PDDR_FECI2C	(MCF_IPSBAR + 0x100017)
#घोषणा MCFGPIO_PDDR_UARTH	(MCF_IPSBAR + 0x100018)
#घोषणा MCFGPIO_PDDR_UARTL	(MCF_IPSBAR + 0x100019)
#घोषणा MCFGPIO_PDDR_QSPI	(MCF_IPSBAR + 0x10001A)
#घोषणा MCFGPIO_PDDR_TIMER	(MCF_IPSBAR + 0x10001B)
#घोषणा MCFGPIO_PDDR_ETPU	(MCF_IPSBAR + 0x10001C)

#घोषणा MCFGPIO_PPDSDR_ADDR	(MCF_IPSBAR + 0x100020)
#घोषणा MCFGPIO_PPDSDR_DATAH	(MCF_IPSBAR + 0x100021)
#घोषणा MCFGPIO_PPDSDR_DATAL	(MCF_IPSBAR + 0x100022)
#घोषणा MCFGPIO_PPDSDR_BUSCTL	(MCF_IPSBAR + 0x100023)
#घोषणा MCFGPIO_PPDSDR_BS	(MCF_IPSBAR + 0x100024)
#घोषणा MCFGPIO_PPDSDR_CS	(MCF_IPSBAR + 0x100025)
#घोषणा MCFGPIO_PPDSDR_SDRAM	(MCF_IPSBAR + 0x100026)
#घोषणा MCFGPIO_PPDSDR_FECI2C	(MCF_IPSBAR + 0x100027)
#घोषणा MCFGPIO_PPDSDR_UARTH	(MCF_IPSBAR + 0x100028)
#घोषणा MCFGPIO_PPDSDR_UARTL	(MCF_IPSBAR + 0x100029)
#घोषणा MCFGPIO_PPDSDR_QSPI	(MCF_IPSBAR + 0x10002A)
#घोषणा MCFGPIO_PPDSDR_TIMER	(MCF_IPSBAR + 0x10002B)
#घोषणा MCFGPIO_PPDSDR_ETPU	(MCF_IPSBAR + 0x10002C)

#घोषणा MCFGPIO_PCLRR_ADDR	(MCF_IPSBAR + 0x100030)
#घोषणा MCFGPIO_PCLRR_DATAH	(MCF_IPSBAR + 0x100031)
#घोषणा MCFGPIO_PCLRR_DATAL	(MCF_IPSBAR + 0x100032)
#घोषणा MCFGPIO_PCLRR_BUSCTL	(MCF_IPSBAR + 0x100033)
#घोषणा MCFGPIO_PCLRR_BS	(MCF_IPSBAR + 0x100034)
#घोषणा MCFGPIO_PCLRR_CS	(MCF_IPSBAR + 0x100035)
#घोषणा MCFGPIO_PCLRR_SDRAM	(MCF_IPSBAR + 0x100036)
#घोषणा MCFGPIO_PCLRR_FECI2C	(MCF_IPSBAR + 0x100037)
#घोषणा MCFGPIO_PCLRR_UARTH	(MCF_IPSBAR + 0x100038)
#घोषणा MCFGPIO_PCLRR_UARTL	(MCF_IPSBAR + 0x100039)
#घोषणा MCFGPIO_PCLRR_QSPI	(MCF_IPSBAR + 0x10003A)
#घोषणा MCFGPIO_PCLRR_TIMER	(MCF_IPSBAR + 0x10003B)
#घोषणा MCFGPIO_PCLRR_ETPU	(MCF_IPSBAR + 0x10003C)

/*
 * PIT समयr base addresses.
 */
#घोषणा	MCFPIT_BASE1		(MCF_IPSBAR + 0x150000)
#घोषणा	MCFPIT_BASE2		(MCF_IPSBAR + 0x160000)
#घोषणा	MCFPIT_BASE3		(MCF_IPSBAR + 0x170000)
#घोषणा	MCFPIT_BASE4		(MCF_IPSBAR + 0x180000)

/*
 * EPort
 */
#घोषणा MCFEPORT_EPPAR		(MCF_IPSBAR + 0x130000)
#घोषणा MCFEPORT_EPDDR		(MCF_IPSBAR + 0x130002)
#घोषणा MCFEPORT_EPIER		(MCF_IPSBAR + 0x130003)
#घोषणा MCFEPORT_EPDR		(MCF_IPSBAR + 0x130004)
#घोषणा MCFEPORT_EPPDR		(MCF_IPSBAR + 0x130005)
#घोषणा MCFEPORT_EPFR		(MCF_IPSBAR + 0x130006)

/*
 * Generic GPIO support
 */
#घोषणा MCFGPIO_PODR		MCFGPIO_PODR_ADDR
#घोषणा MCFGPIO_PDDR		MCFGPIO_PDDR_ADDR
#घोषणा MCFGPIO_PPDR		MCFGPIO_PPDSDR_ADDR
#घोषणा MCFGPIO_SETR		MCFGPIO_PPDSDR_ADDR
#घोषणा MCFGPIO_CLRR		MCFGPIO_PCLRR_ADDR

#घोषणा MCFGPIO_PIN_MAX		107
#घोषणा MCFGPIO_IRQ_MAX		8
#घोषणा MCFGPIO_IRQ_VECBASE	MCFINT_VECBASE

/*
 * Pin Assignment
*/
#घोषणा	MCFGPIO_PAR_AD		(MCF_IPSBAR + 0x100040)
#घोषणा	MCFGPIO_PAR_BUSCTL	(MCF_IPSBAR + 0x100042)
#घोषणा	MCFGPIO_PAR_BS		(MCF_IPSBAR + 0x100044)
#घोषणा	MCFGPIO_PAR_CS		(MCF_IPSBAR + 0x100045)
#घोषणा	MCFGPIO_PAR_SDRAM	(MCF_IPSBAR + 0x100046)
#घोषणा	MCFGPIO_PAR_FECI2C	(MCF_IPSBAR + 0x100047)
#घोषणा	MCFGPIO_PAR_UART	(MCF_IPSBAR + 0x100048)
#घोषणा	MCFGPIO_PAR_QSPI	(MCF_IPSBAR + 0x10004A)
#घोषणा	MCFGPIO_PAR_TIMER	(MCF_IPSBAR + 0x10004C)
#घोषणा	MCFGPIO_PAR_ETPU	(MCF_IPSBAR + 0x10004E)

/*
 * DMA unit base addresses.
 */
#घोषणा	MCFDMA_BASE0		(MCF_IPSBAR + 0x100)
#घोषणा	MCFDMA_BASE1		(MCF_IPSBAR + 0x140)
#घोषणा	MCFDMA_BASE2		(MCF_IPSBAR + 0x180)
#घोषणा	MCFDMA_BASE3		(MCF_IPSBAR + 0x1C0)

/*
 * I2C module.
 */
#घोषणा	MCFI2C_BASE0		(MCF_IPSBAR + 0x300)
#घोषणा	MCFI2C_SIZE0		0x40

/****************************************************************************/
#पूर्ण_अगर	/* m523xsim_h */
