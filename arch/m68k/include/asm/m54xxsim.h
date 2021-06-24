<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	m54xxsim.h -- ColdFire 547x/548x System Integration Unit support.
 */

#अगर_अघोषित	m54xxsim_h
#घोषणा m54xxsim_h

#घोषणा	CPU_NAME		"COLDFIRE(m54xx)"
#घोषणा	CPU_INSTR_PER_JIFFY	2
#घोषणा	MCF_BUSCLK		(MCF_CLK / 2)
#घोषणा	MACHINE			MACH_M54XX
#घोषणा	FPUTYPE			FPU_COLDFIRE
#घोषणा	IOMEMBASE		MCF_MBAR
#घोषणा	IOMEMSIZE		0x01000000

#समावेश <यंत्र/m54xxacr.h>

#घोषणा MCFINT_VECBASE		64

/*
 *      Interrupt Controller Registers
 */
#घोषणा MCFICM_INTC0		(MCF_MBAR + 0x700) 	/* Base क्रम Interrupt Ctrl 0 */

#घोषणा MCFINTC_IPRH		0x00		/* Interrupt pending 32-63 */
#घोषणा MCFINTC_IPRL		0x04		/* Interrupt pending 1-31 */
#घोषणा MCFINTC_IMRH		0x08		/* Interrupt mask 32-63 */
#घोषणा MCFINTC_IMRL		0x0c		/* Interrupt mask 1-31 */
#घोषणा MCFINTC_INTFRCH		0x10		/* Interrupt क्रमce 32-63 */
#घोषणा MCFINTC_INTFRCL		0x14		/* Interrupt क्रमce 1-31 */
#घोषणा MCFINTC_IRLR		0x18		/* */
#घोषणा MCFINTC_IACKL		0x19		/* */
#घोषणा MCFINTC_ICR0		0x40		/* Base ICR रेजिस्टर */

/*
 *	UART module.
 */
#घोषणा MCFUART_BASE0		(MCF_MBAR + 0x8600)	/* Base address UART0 */
#घोषणा MCFUART_BASE1		(MCF_MBAR + 0x8700)	/* Base address UART1 */
#घोषणा MCFUART_BASE2		(MCF_MBAR + 0x8800)	/* Base address UART2 */
#घोषणा MCFUART_BASE3		(MCF_MBAR + 0x8900)	/* Base address UART3 */

/*
 *	Define प्रणाली peripheral IRQ usage.
 */
#घोषणा MCF_IRQ_TIMER		(MCFINT_VECBASE + 54)	/* Slice Timer 0 */
#घोषणा MCF_IRQ_PROखाताR	(MCFINT_VECBASE + 53)	/* Slice Timer 1 */
#घोषणा MCF_IRQ_I2C0		(MCFINT_VECBASE + 40)
#घोषणा MCF_IRQ_UART0		(MCFINT_VECBASE + 35)
#घोषणा MCF_IRQ_UART1		(MCFINT_VECBASE + 34)
#घोषणा MCF_IRQ_UART2		(MCFINT_VECBASE + 33)
#घोषणा MCF_IRQ_UART3		(MCFINT_VECBASE + 32)

/*
 *	Slice Timer support.
 */
#घोषणा MCFSLT_TIMER0		(MCF_MBAR + 0x900)	/* Base addr TIMER0 */
#घोषणा MCFSLT_TIMER1		(MCF_MBAR + 0x910)	/* Base addr TIMER1 */

/*
 *	Generic GPIO support
 */
#घोषणा MCFGPIO_PODR		(MCF_MBAR + 0xA00)
#घोषणा MCFGPIO_PDDR		(MCF_MBAR + 0xA10)
#घोषणा MCFGPIO_PPDR		(MCF_MBAR + 0xA20)
#घोषणा MCFGPIO_SETR		(MCF_MBAR + 0xA20)
#घोषणा MCFGPIO_CLRR		(MCF_MBAR + 0xA30)

#घोषणा MCFGPIO_PIN_MAX		136	/* 128 gpio + 8 eport */
#घोषणा MCFGPIO_IRQ_MAX		8
#घोषणा MCFGPIO_IRQ_VECBASE	MCFINT_VECBASE

/*
 *	EDGE Port support.
 */
#घोषणा	MCFEPORT_EPPAR		(MCF_MBAR + 0xf00)	/* Pin assignment */
#घोषणा	MCFEPORT_EPDDR		(MCF_MBAR + 0xf04)	/* Data direction */
#घोषणा	MCFEPORT_EPIER		(MCF_MBAR + 0xf05)	/* Interrupt enable */
#घोषणा	MCFEPORT_EPDR		(MCF_MBAR + 0xf08)	/* Port data (w) */
#घोषणा	MCFEPORT_EPPDR		(MCF_MBAR + 0xf09)	/* Port data (r) */
#घोषणा	MCFEPORT_EPFR		(MCF_MBAR + 0xf0c)	/* Flags */

/*
 *	Pin Assignment रेजिस्टर definitions
 */
#घोषणा MCFGPIO_PAR_FBCTL	(MCF_MBAR + 0xA40)
#घोषणा MCFGPIO_PAR_FBCS	(MCF_MBAR + 0xA42)
#घोषणा MCFGPIO_PAR_DMA		(MCF_MBAR + 0xA43)
#घोषणा MCFGPIO_PAR_FECI2CIRQ	(MCF_MBAR + 0xA44)
#घोषणा MCFGPIO_PAR_PCIBG	(MCF_MBAR + 0xA48)	/* PCI bus grant */
#घोषणा MCFGPIO_PAR_PCIBR	(MCF_MBAR + 0xA4A)	/* PCI */
#घोषणा MCFGPIO_PAR_PSC0	(MCF_MBAR + 0xA4F)
#घोषणा MCFGPIO_PAR_PSC1	(MCF_MBAR + 0xA4E)
#घोषणा MCFGPIO_PAR_PSC2	(MCF_MBAR + 0xA4D)
#घोषणा MCFGPIO_PAR_PSC3	(MCF_MBAR + 0xA4C)
#घोषणा MCFGPIO_PAR_DSPI	(MCF_MBAR + 0xA50)
#घोषणा MCFGPIO_PAR_TIMER	(MCF_MBAR + 0xA52)

#घोषणा MCF_PAR_SDA		(0x0008)
#घोषणा MCF_PAR_SCL		(0x0004)
#घोषणा MCF_PAR_PSC_TXD		(0x04)
#घोषणा MCF_PAR_PSC_RXD		(0x08)
#घोषणा MCF_PAR_PSC_CTS_GPIO	(0x00)
#घोषणा MCF_PAR_PSC_CTS_BCLK	(0x80)
#घोषणा MCF_PAR_PSC_CTS_CTS	(0xC0)
#घोषणा MCF_PAR_PSC_RTS_GPIO    (0x00)
#घोषणा MCF_PAR_PSC_RTS_FSYNC	(0x20)
#घोषणा MCF_PAR_PSC_RTS_RTS	(0x30)
#घोषणा MCF_PAR_PSC_CANRX	(0x40)

#घोषणा MCF_PAR_FECI2CIRQ	(MCF_MBAR + 0x00000a44)	/* FEC/I2C/IRQ */
#घोषणा MCF_PAR_FECI2CIRQ_SDA	(1 << 3)
#घोषणा MCF_PAR_FECI2CIRQ_SCL	(1 << 2)

/*
 * I2C module.
 */
#घोषणा MCFI2C_BASE0		(MCF_MBAR + 0x8f00)
#घोषणा MCFI2C_SIZE0		0x40

#पूर्ण_अगर	/* m54xxsim_h */
