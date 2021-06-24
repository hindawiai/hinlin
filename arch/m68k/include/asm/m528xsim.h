<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	m528xsim.h -- ColdFire 5280/5282 System Integration Module support.
 *
 *	(C) Copyright 2003, Greg Ungerer (gerg@snapgear.com)
 */

/****************************************************************************/
#अगर_अघोषित	m528xsim_h
#घोषणा	m528xsim_h
/****************************************************************************/

#घोषणा	CPU_NAME		"COLDFIRE(m528x)"
#घोषणा	CPU_INSTR_PER_JIFFY	3
#घोषणा	MCF_BUSCLK		MCF_CLK

#समावेश <यंत्र/m52xxacr.h>

/*
 *	Define the 5280/5282 SIM रेजिस्टर set addresses.
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
#घोषणा	MCFINT_PIT1		55		/* Interrupt number क्रम PIT1 */

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
#घोषणा	MCFSIM_DCR		(MCF_IPSBAR + 0x00000044) /* Control */
#घोषणा	MCFSIM_DACR0		(MCF_IPSBAR + 0x00000048) /* Base address 0 */
#घोषणा	MCFSIM_DMR0		(MCF_IPSBAR + 0x0000004c) /* Address mask 0 */
#घोषणा	MCFSIM_DACR1		(MCF_IPSBAR + 0x00000050) /* Base address 1 */
#घोषणा	MCFSIM_DMR1		(MCF_IPSBAR + 0x00000054) /* Address mask 1 */

/*
 *	DMA unit base addresses.
 */
#घोषणा	MCFDMA_BASE0		(MCF_IPSBAR + 0x00000100)
#घोषणा	MCFDMA_BASE1		(MCF_IPSBAR + 0x00000140)
#घोषणा	MCFDMA_BASE2		(MCF_IPSBAR + 0x00000180)
#घोषणा	MCFDMA_BASE3		(MCF_IPSBAR + 0x000001C0)

/*
 *	UART module.
 */
#घोषणा	MCFUART_BASE0		(MCF_IPSBAR + 0x00000200)
#घोषणा	MCFUART_BASE1		(MCF_IPSBAR + 0x00000240)
#घोषणा	MCFUART_BASE2		(MCF_IPSBAR + 0x00000280)

/*
 *	FEC ethernet module.
 */
#घोषणा	MCFFEC_BASE0		(MCF_IPSBAR + 0x00001000)
#घोषणा	MCFFEC_SIZE0		0x800

/*
 *	QSPI module.
 */
#घोषणा	MCFQSPI_BASE		(MCF_IPSBAR + 0x340)
#घोषणा	MCFQSPI_SIZE		0x40

#घोषणा	MCFQSPI_CS0		147
#घोषणा	MCFQSPI_CS1		148
#घोषणा	MCFQSPI_CS2		149
#घोषणा	MCFQSPI_CS3		150

/*
 * 	GPIO रेजिस्टरs
 */
#घोषणा MCFGPIO_PODR_A		(MCF_IPSBAR + 0x00100000)
#घोषणा MCFGPIO_PODR_B		(MCF_IPSBAR + 0x00100001)
#घोषणा MCFGPIO_PODR_C		(MCF_IPSBAR + 0x00100002)
#घोषणा MCFGPIO_PODR_D		(MCF_IPSBAR + 0x00100003)
#घोषणा MCFGPIO_PODR_E		(MCF_IPSBAR + 0x00100004)
#घोषणा MCFGPIO_PODR_F		(MCF_IPSBAR + 0x00100005)
#घोषणा MCFGPIO_PODR_G		(MCF_IPSBAR + 0x00100006)
#घोषणा MCFGPIO_PODR_H		(MCF_IPSBAR + 0x00100007)
#घोषणा MCFGPIO_PODR_J		(MCF_IPSBAR + 0x00100008)
#घोषणा MCFGPIO_PODR_DD		(MCF_IPSBAR + 0x00100009)
#घोषणा MCFGPIO_PODR_EH		(MCF_IPSBAR + 0x0010000A)
#घोषणा MCFGPIO_PODR_EL		(MCF_IPSBAR + 0x0010000B)
#घोषणा MCFGPIO_PODR_AS		(MCF_IPSBAR + 0x0010000C)
#घोषणा MCFGPIO_PODR_QS		(MCF_IPSBAR + 0x0010000D)
#घोषणा MCFGPIO_PODR_SD		(MCF_IPSBAR + 0x0010000E)
#घोषणा MCFGPIO_PODR_TC		(MCF_IPSBAR + 0x0010000F)
#घोषणा MCFGPIO_PODR_TD		(MCF_IPSBAR + 0x00100010)
#घोषणा MCFGPIO_PODR_UA		(MCF_IPSBAR + 0x00100011)

#घोषणा MCFGPIO_PDDR_A		(MCF_IPSBAR + 0x00100014)
#घोषणा MCFGPIO_PDDR_B		(MCF_IPSBAR + 0x00100015)
#घोषणा MCFGPIO_PDDR_C		(MCF_IPSBAR + 0x00100016)
#घोषणा MCFGPIO_PDDR_D		(MCF_IPSBAR + 0x00100017)
#घोषणा MCFGPIO_PDDR_E		(MCF_IPSBAR + 0x00100018)
#घोषणा MCFGPIO_PDDR_F		(MCF_IPSBAR + 0x00100019)
#घोषणा MCFGPIO_PDDR_G		(MCF_IPSBAR + 0x0010001A)
#घोषणा MCFGPIO_PDDR_H		(MCF_IPSBAR + 0x0010001B)
#घोषणा MCFGPIO_PDDR_J		(MCF_IPSBAR + 0x0010001C)
#घोषणा MCFGPIO_PDDR_DD		(MCF_IPSBAR + 0x0010001D)
#घोषणा MCFGPIO_PDDR_EH		(MCF_IPSBAR + 0x0010001E)
#घोषणा MCFGPIO_PDDR_EL		(MCF_IPSBAR + 0x0010001F)
#घोषणा MCFGPIO_PDDR_AS		(MCF_IPSBAR + 0x00100020)
#घोषणा MCFGPIO_PDDR_QS		(MCF_IPSBAR + 0x00100021)
#घोषणा MCFGPIO_PDDR_SD		(MCF_IPSBAR + 0x00100022)
#घोषणा MCFGPIO_PDDR_TC		(MCF_IPSBAR + 0x00100023)
#घोषणा MCFGPIO_PDDR_TD		(MCF_IPSBAR + 0x00100024)
#घोषणा MCFGPIO_PDDR_UA		(MCF_IPSBAR + 0x00100025)

#घोषणा MCFGPIO_PPDSDR_A	(MCF_IPSBAR + 0x00100028)
#घोषणा MCFGPIO_PPDSDR_B	(MCF_IPSBAR + 0x00100029)
#घोषणा MCFGPIO_PPDSDR_C	(MCF_IPSBAR + 0x0010002A)
#घोषणा MCFGPIO_PPDSDR_D	(MCF_IPSBAR + 0x0010002B)
#घोषणा MCFGPIO_PPDSDR_E	(MCF_IPSBAR + 0x0010002C)
#घोषणा MCFGPIO_PPDSDR_F	(MCF_IPSBAR + 0x0010002D)
#घोषणा MCFGPIO_PPDSDR_G	(MCF_IPSBAR + 0x0010002E)
#घोषणा MCFGPIO_PPDSDR_H	(MCF_IPSBAR + 0x0010002F)
#घोषणा MCFGPIO_PPDSDR_J	(MCF_IPSBAR + 0x00100030)
#घोषणा MCFGPIO_PPDSDR_DD	(MCF_IPSBAR + 0x00100031)
#घोषणा MCFGPIO_PPDSDR_EH	(MCF_IPSBAR + 0x00100032)
#घोषणा MCFGPIO_PPDSDR_EL	(MCF_IPSBAR + 0x00100033)
#घोषणा MCFGPIO_PPDSDR_AS	(MCF_IPSBAR + 0x00100034)
#घोषणा MCFGPIO_PPDSDR_QS	(MCF_IPSBAR + 0x00100035)
#घोषणा MCFGPIO_PPDSDR_SD	(MCF_IPSBAR + 0x00100036)
#घोषणा MCFGPIO_PPDSDR_TC	(MCF_IPSBAR + 0x00100037)
#घोषणा MCFGPIO_PPDSDR_TD	(MCF_IPSBAR + 0x00100038)
#घोषणा MCFGPIO_PPDSDR_UA	(MCF_IPSBAR + 0x00100039)

#घोषणा MCFGPIO_PCLRR_A		(MCF_IPSBAR + 0x0010003C)
#घोषणा MCFGPIO_PCLRR_B		(MCF_IPSBAR + 0x0010003D)
#घोषणा MCFGPIO_PCLRR_C		(MCF_IPSBAR + 0x0010003E)
#घोषणा MCFGPIO_PCLRR_D		(MCF_IPSBAR + 0x0010003F)
#घोषणा MCFGPIO_PCLRR_E		(MCF_IPSBAR + 0x00100040)
#घोषणा MCFGPIO_PCLRR_F		(MCF_IPSBAR + 0x00100041)
#घोषणा MCFGPIO_PCLRR_G		(MCF_IPSBAR + 0x00100042)
#घोषणा MCFGPIO_PCLRR_H		(MCF_IPSBAR + 0x00100043)
#घोषणा MCFGPIO_PCLRR_J		(MCF_IPSBAR + 0x00100044)
#घोषणा MCFGPIO_PCLRR_DD	(MCF_IPSBAR + 0x00100045)
#घोषणा MCFGPIO_PCLRR_EH	(MCF_IPSBAR + 0x00100046)
#घोषणा MCFGPIO_PCLRR_EL	(MCF_IPSBAR + 0x00100047)
#घोषणा MCFGPIO_PCLRR_AS	(MCF_IPSBAR + 0x00100048)
#घोषणा MCFGPIO_PCLRR_QS	(MCF_IPSBAR + 0x00100049)
#घोषणा MCFGPIO_PCLRR_SD	(MCF_IPSBAR + 0x0010004A)
#घोषणा MCFGPIO_PCLRR_TC	(MCF_IPSBAR + 0x0010004B)
#घोषणा MCFGPIO_PCLRR_TD	(MCF_IPSBAR + 0x0010004C)
#घोषणा MCFGPIO_PCLRR_UA	(MCF_IPSBAR + 0x0010004D)

#घोषणा MCFGPIO_PBCDPAR		(MCF_IPSBAR + 0x00100050)
#घोषणा MCFGPIO_PFPAR		(MCF_IPSBAR + 0x00100051)
#घोषणा MCFGPIO_PEPAR		(MCF_IPSBAR + 0x00100052)
#घोषणा MCFGPIO_PJPAR		(MCF_IPSBAR + 0x00100054)
#घोषणा MCFGPIO_PSDPAR		(MCF_IPSBAR + 0x00100055)
#घोषणा MCFGPIO_PASPAR		(MCF_IPSBAR + 0x00100056)
#घोषणा MCFGPIO_PEHLPAR		(MCF_IPSBAR + 0x00100058)
#घोषणा MCFGPIO_PQSPAR		(MCF_IPSBAR + 0x00100059)
#घोषणा MCFGPIO_PTCPAR		(MCF_IPSBAR + 0x0010005A)
#घोषणा MCFGPIO_PTDPAR		(MCF_IPSBAR + 0x0010005B)
#घोषणा MCFGPIO_PUAPAR		(MCF_IPSBAR + 0x0010005C)

/*
 * PIT समयr base addresses.
 */
#घोषणा	MCFPIT_BASE1		(MCF_IPSBAR + 0x00150000)
#घोषणा	MCFPIT_BASE2		(MCF_IPSBAR + 0x00160000)
#घोषणा	MCFPIT_BASE3		(MCF_IPSBAR + 0x00170000)
#घोषणा	MCFPIT_BASE4		(MCF_IPSBAR + 0x00180000)

/*
 * 	Edge Port रेजिस्टरs
 */
#घोषणा MCFEPORT_EPPAR		(MCF_IPSBAR + 0x00130000)
#घोषणा MCFEPORT_EPDDR		(MCF_IPSBAR + 0x00130002)
#घोषणा MCFEPORT_EPIER		(MCF_IPSBAR + 0x00130003)
#घोषणा MCFEPORT_EPDR		(MCF_IPSBAR + 0x00130004)
#घोषणा MCFEPORT_EPPDR		(MCF_IPSBAR + 0x00130005)
#घोषणा MCFEPORT_EPFR		(MCF_IPSBAR + 0x00130006)

/*
 * 	Queued ADC रेजिस्टरs
 */
#घोषणा MCFQADC_PORTQA		(MCF_IPSBAR + 0x00190006)
#घोषणा MCFQADC_PORTQB		(MCF_IPSBAR + 0x00190007)
#घोषणा MCFQADC_DDRQA		(MCF_IPSBAR + 0x00190008)
#घोषणा MCFQADC_DDRQB		(MCF_IPSBAR + 0x00190009)

/*
 * 	General Purpose Timers रेजिस्टरs
 */
#घोषणा MCFGPTA_GPTPORT		(MCF_IPSBAR + 0x001A001D)
#घोषणा MCFGPTA_GPTDDR		(MCF_IPSBAR + 0x001A001E)
#घोषणा MCFGPTB_GPTPORT		(MCF_IPSBAR + 0x001B001D)
#घोषणा MCFGPTB_GPTDDR		(MCF_IPSBAR + 0x001B001E)
/*
 *
 * definitions क्रम generic gpio support
 *
 */
#घोषणा MCFGPIO_PODR		MCFGPIO_PODR_A	/* port output data */
#घोषणा MCFGPIO_PDDR		MCFGPIO_PDDR_A	/* port data direction */
#घोषणा MCFGPIO_PPDR		MCFGPIO_PPDSDR_A/* port pin data */
#घोषणा MCFGPIO_SETR		MCFGPIO_PPDSDR_A/* set output */
#घोषणा MCFGPIO_CLRR		MCFGPIO_PCLRR_A	/* clr output */

#घोषणा MCFGPIO_IRQ_MAX		8
#घोषणा MCFGPIO_IRQ_VECBASE	MCFINT_VECBASE
#घोषणा MCFGPIO_PIN_MAX		180

/*
 *  Reset Control Unit (relative to IPSBAR).
 */
#घोषणा	MCF_RCR			(MCF_IPSBAR + 0x110000)
#घोषणा	MCF_RSR			(MCF_IPSBAR + 0x110001)

#घोषणा	MCF_RCR_SWRESET		0x80		/* Software reset bit */
#घोषणा	MCF_RCR_FRCSTOUT	0x40		/* Force बाह्यal reset */

/*
 * I2C module
 */
#घोषणा	MCFI2C_BASE0		(MCF_IPSBAR + 0x300)
#घोषणा	MCFI2C_SIZE0		0x40

/****************************************************************************/
#पूर्ण_अगर	/* m528xsim_h */
