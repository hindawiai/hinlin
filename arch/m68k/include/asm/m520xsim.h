<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *  m520xsim.h -- ColdFire 5207/5208 System Integration Module support.
 *
 *  (C) Copyright 2005, Intec Automation (mike@steroidmicros.com)
 */

/****************************************************************************/
#अगर_अघोषित m520xsim_h
#घोषणा m520xsim_h
/****************************************************************************/

#घोषणा	CPU_NAME		"COLDFIRE(m520x)"
#घोषणा	CPU_INSTR_PER_JIFFY	3
#घोषणा	MCF_BUSCLK		(MCF_CLK / 2)

#समावेश <यंत्र/m52xxacr.h>

/*
 *  Define the 520x SIM रेजिस्टर set addresses.
 */
#घोषणा MCFICM_INTC0        0xFC048000  /* Base क्रम Interrupt Ctrl 0 */
#घोषणा MCFINTC_IPRH        0x00        /* Interrupt pending 32-63 */
#घोषणा MCFINTC_IPRL        0x04        /* Interrupt pending 1-31 */
#घोषणा MCFINTC_IMRH        0x08        /* Interrupt mask 32-63 */
#घोषणा MCFINTC_IMRL        0x0c        /* Interrupt mask 1-31 */
#घोषणा MCFINTC_INTFRCH     0x10        /* Interrupt क्रमce 32-63 */
#घोषणा MCFINTC_INTFRCL     0x14        /* Interrupt क्रमce 1-31 */
#घोषणा MCFINTC_SIMR        0x1c        /* Set पूर्णांकerrupt mask 0-63 */
#घोषणा MCFINTC_CIMR        0x1d        /* Clear पूर्णांकerrupt mask 0-63 */
#घोषणा MCFINTC_ICR0        0x40        /* Base ICR रेजिस्टर */

/*
 *  The common पूर्णांकerrupt controller code just wants to know the असलolute
 *  address to the SIMR and CIMR रेजिस्टरs (not offsets पूर्णांकo IPSBAR).
 *  The 520x family only has a single INTC unit.
 */
#घोषणा MCFINTC0_SIMR       (MCFICM_INTC0 + MCFINTC_SIMR)
#घोषणा MCFINTC0_CIMR       (MCFICM_INTC0 + MCFINTC_CIMR)
#घोषणा	MCFINTC0_ICR0       (MCFICM_INTC0 + MCFINTC_ICR0)
#घोषणा MCFINTC1_SIMR       (0)
#घोषणा MCFINTC1_CIMR       (0)
#घोषणा	MCFINTC1_ICR0       (0)
#घोषणा MCFINTC2_SIMR       (0)
#घोषणा MCFINTC2_CIMR       (0)
#घोषणा MCFINTC2_ICR0       (0)

#घोषणा MCFINT_VECBASE      64
#घोषणा MCFINT_UART0        26          /* Interrupt number क्रम UART0 */
#घोषणा MCFINT_UART1        27          /* Interrupt number क्रम UART1 */
#घोषणा MCFINT_UART2        28          /* Interrupt number क्रम UART2 */
#घोषणा MCFINT_I2C0         30          /* Interrupt number क्रम I2C */
#घोषणा MCFINT_QSPI         31          /* Interrupt number क्रम QSPI */
#घोषणा MCFINT_FECRX0	    36		/* Interrupt number क्रम FEC RX */
#घोषणा MCFINT_FECTX0	    40		/* Interrupt number क्रम FEC RX */
#घोषणा MCFINT_FECENTC0	    42		/* Interrupt number क्रम FEC RX */
#घोषणा MCFINT_PIT1         4           /* Interrupt number क्रम PIT1 (PIT0 in processor) */

#घोषणा MCF_IRQ_UART0	    (MCFINT_VECBASE + MCFINT_UART0)
#घोषणा MCF_IRQ_UART1	    (MCFINT_VECBASE + MCFINT_UART1)
#घोषणा MCF_IRQ_UART2	    (MCFINT_VECBASE + MCFINT_UART2)

#घोषणा MCF_IRQ_FECRX0	    (MCFINT_VECBASE + MCFINT_FECRX0)
#घोषणा MCF_IRQ_FECTX0	    (MCFINT_VECBASE + MCFINT_FECTX0)
#घोषणा MCF_IRQ_FECENTC0    (MCFINT_VECBASE + MCFINT_FECENTC0)

#घोषणा	MCF_IRQ_QSPI	    (MCFINT_VECBASE + MCFINT_QSPI)
#घोषणा MCF_IRQ_PIT1        (MCFINT_VECBASE + MCFINT_PIT1)

#घोषणा MCF_IRQ_I2C0        (MCFINT_VECBASE + MCFINT_I2C0)
/*
 *  SDRAM configuration रेजिस्टरs.
 */
#घोषणा MCFSIM_SDMR         0xFC0a8000	/* SDRAM Mode/Extended Mode Register */
#घोषणा MCFSIM_SDCR         0xFC0a8004	/* SDRAM Control Register */
#घोषणा MCFSIM_SDCFG1       0xFC0a8008	/* SDRAM Configuration Register 1 */
#घोषणा MCFSIM_SDCFG2       0xFC0a800c	/* SDRAM Configuration Register 2 */
#घोषणा MCFSIM_SDCS0        0xFC0a8110	/* SDRAM Chip Select 0 Configuration */
#घोषणा MCFSIM_SDCS1        0xFC0a8114	/* SDRAM Chip Select 1 Configuration */

/*
 * EPORT and GPIO रेजिस्टरs.
 */
#घोषणा MCFEPORT_EPPAR			0xFC088000
#घोषणा MCFEPORT_EPDDR			0xFC088002
#घोषणा MCFEPORT_EPIER			0xFC088003
#घोषणा MCFEPORT_EPDR			0xFC088004
#घोषणा MCFEPORT_EPPDR			0xFC088005
#घोषणा MCFEPORT_EPFR			0xFC088006

#घोषणा MCFGPIO_PODR_BUSCTL		0xFC0A4000
#घोषणा MCFGPIO_PODR_BE			0xFC0A4001
#घोषणा MCFGPIO_PODR_CS			0xFC0A4002
#घोषणा MCFGPIO_PODR_FECI2C		0xFC0A4003
#घोषणा MCFGPIO_PODR_QSPI		0xFC0A4004
#घोषणा MCFGPIO_PODR_TIMER		0xFC0A4005
#घोषणा MCFGPIO_PODR_UART		0xFC0A4006
#घोषणा MCFGPIO_PODR_FECH		0xFC0A4007
#घोषणा MCFGPIO_PODR_FECL		0xFC0A4008

#घोषणा MCFGPIO_PDDR_BUSCTL		0xFC0A400C
#घोषणा MCFGPIO_PDDR_BE			0xFC0A400D
#घोषणा MCFGPIO_PDDR_CS			0xFC0A400E
#घोषणा MCFGPIO_PDDR_FECI2C		0xFC0A400F
#घोषणा MCFGPIO_PDDR_QSPI		0xFC0A4010
#घोषणा MCFGPIO_PDDR_TIMER		0xFC0A4011
#घोषणा MCFGPIO_PDDR_UART		0xFC0A4012
#घोषणा MCFGPIO_PDDR_FECH		0xFC0A4013
#घोषणा MCFGPIO_PDDR_FECL		0xFC0A4014

#घोषणा MCFGPIO_PPDSDR_CS		0xFC0A401A
#घोषणा MCFGPIO_PPDSDR_FECI2C		0xFC0A401B
#घोषणा MCFGPIO_PPDSDR_QSPI		0xFC0A401C
#घोषणा MCFGPIO_PPDSDR_TIMER		0xFC0A401D
#घोषणा MCFGPIO_PPDSDR_UART		0xFC0A401E
#घोषणा MCFGPIO_PPDSDR_FECH		0xFC0A401F
#घोषणा MCFGPIO_PPDSDR_FECL		0xFC0A4020

#घोषणा MCFGPIO_PCLRR_BUSCTL		0xFC0A4024
#घोषणा MCFGPIO_PCLRR_BE		0xFC0A4025
#घोषणा MCFGPIO_PCLRR_CS		0xFC0A4026
#घोषणा MCFGPIO_PCLRR_FECI2C		0xFC0A4027
#घोषणा MCFGPIO_PCLRR_QSPI		0xFC0A4028
#घोषणा MCFGPIO_PCLRR_TIMER		0xFC0A4029
#घोषणा MCFGPIO_PCLRR_UART		0xFC0A402A
#घोषणा MCFGPIO_PCLRR_FECH		0xFC0A402B
#घोषणा MCFGPIO_PCLRR_FECL		0xFC0A402C

/*
 * Generic GPIO support
 */
#घोषणा MCFGPIO_PODR			MCFGPIO_PODR_CS
#घोषणा MCFGPIO_PDDR			MCFGPIO_PDDR_CS
#घोषणा MCFGPIO_PPDR			MCFGPIO_PPDSDR_CS
#घोषणा MCFGPIO_SETR			MCFGPIO_PPDSDR_CS
#घोषणा MCFGPIO_CLRR			MCFGPIO_PCLRR_CS

#घोषणा MCFGPIO_PIN_MAX			80
#घोषणा MCFGPIO_IRQ_MAX			8
#घोषणा MCFGPIO_IRQ_VECBASE		MCFINT_VECBASE

#घोषणा MCF_GPIO_PAR_UART		0xFC0A4036
#घोषणा MCF_GPIO_PAR_FECI2C		0xFC0A4033
#घोषणा MCF_GPIO_PAR_QSPI		0xFC0A4034
#घोषणा MCF_GPIO_PAR_FEC		0xFC0A4038

#घोषणा MCF_GPIO_PAR_UART_PAR_URXD0         (0x0001)
#घोषणा MCF_GPIO_PAR_UART_PAR_UTXD0         (0x0002)

#घोषणा MCF_GPIO_PAR_UART_PAR_URXD1         (0x0040)
#घोषणा MCF_GPIO_PAR_UART_PAR_UTXD1         (0x0080)

#घोषणा MCF_GPIO_PAR_FECI2C_PAR_SDA_URXD2   (0x02)
#घोषणा MCF_GPIO_PAR_FECI2C_PAR_SCL_UTXD2   (0x04)

/*
 *  PIT समयr module.
 */
#घोषणा	MCFPIT_BASE1		0xFC080000	/* Base address of TIMER1 */
#घोषणा	MCFPIT_BASE2		0xFC084000	/* Base address of TIMER2 */

/*
 *  UART module.
 */
#घोषणा MCFUART_BASE0		0xFC060000	/* Base address of UART0 */
#घोषणा MCFUART_BASE1		0xFC064000	/* Base address of UART1 */
#घोषणा MCFUART_BASE2		0xFC068000	/* Base address of UART2 */

/*
 *  FEC module.
 */
#घोषणा	MCFFEC_BASE0		0xFC030000	/* Base of FEC ethernet */
#घोषणा	MCFFEC_SIZE0		0x800		/* Register set size */

/*
 *  QSPI module.
 */
#घोषणा	MCFQSPI_BASE		0xFC05C000	/* Base of QSPI module */
#घोषणा	MCFQSPI_SIZE		0x40		/* Register set size */

#घोषणा	MCFQSPI_CS0		46
#घोषणा	MCFQSPI_CS1		47
#घोषणा	MCFQSPI_CS2		27

/*
 *  Reset Control Unit.
 */
#घोषणा	MCF_RCR			0xFC0A0000
#घोषणा	MCF_RSR			0xFC0A0001

#घोषणा	MCF_RCR_SWRESET		0x80		/* Software reset bit */
#घोषणा	MCF_RCR_FRCSTOUT	0x40		/* Force बाह्यal reset */

/*
 *  Power Management.
 */
#घोषणा MCFPM_WCR		0xfc040013
#घोषणा MCFPM_PPMSR0		0xfc04002c
#घोषणा MCFPM_PPMCR0		0xfc04002d
#घोषणा MCFPM_PPMHR0		0xfc040030
#घोषणा MCFPM_PPMLR0		0xfc040034
#घोषणा MCFPM_LPCR		0xfc0a0007

/*
 * I2C module.
 */
#घोषणा MCFI2C_BASE0		0xFC058000
#घोषणा MCFI2C_SIZE0		0x40

/****************************************************************************/
#पूर्ण_अगर  /* m520xsim_h */
