<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	m5407sim.h -- ColdFire 5407 System Integration Module support.
 *
 *	(C) Copyright 2000,  Lineo (www.lineo.com)
 *	(C) Copyright 1999,  Moreton Bay Ventures Pty Ltd.
 *
 *      Modअगरied by David W. Miller क्रम the MCF5307 Eval Board.
 */

/****************************************************************************/
#अगर_अघोषित	m5407sim_h
#घोषणा	m5407sim_h
/****************************************************************************/

#घोषणा	CPU_NAME		"COLDFIRE(m5407)"
#घोषणा	CPU_INSTR_PER_JIFFY	3
#घोषणा	MCF_BUSCLK		(MCF_CLK / 2)

#समावेश <यंत्र/m54xxacr.h>

/*
 *	Define the 5407 SIM रेजिस्टर set addresses.
 */
#घोषणा	MCFSIM_RSR		(MCF_MBAR + 0x00)	/* Reset Status */
#घोषणा	MCFSIM_SYPCR		(MCF_MBAR + 0x01)	/* System Protection */
#घोषणा	MCFSIM_SWIVR		(MCF_MBAR + 0x02)	/* SW Watchकरोg पूर्णांकr */
#घोषणा	MCFSIM_SWSR		(MCF_MBAR + 0x03)	/* SW Watchकरोg service*/
#घोषणा	MCFSIM_PAR		(MCF_MBAR + 0x04)	/* Pin Assignment */
#घोषणा	MCFSIM_IRQPAR		(MCF_MBAR + 0x06)	/* Intr Assignment */
#घोषणा	MCFSIM_PLLCR		(MCF_MBAR + 0x08)	/* PLL Ctrl */
#घोषणा	MCFSIM_MPARK		(MCF_MBAR + 0x0C)	/* BUS Master Ctrl */
#घोषणा	MCFSIM_IPR		(MCF_MBAR + 0x40)	/* Interrupt Pending */
#घोषणा	MCFSIM_IMR		(MCF_MBAR + 0x44)	/* Interrupt Mask */
#घोषणा	MCFSIM_AVR		(MCF_MBAR + 0x4b)	/* Autovector Ctrl */
#घोषणा	MCFSIM_ICR0		(MCF_MBAR + 0x4c)	/* Intr Ctrl reg 0 */
#घोषणा	MCFSIM_ICR1		(MCF_MBAR + 0x4d)	/* Intr Ctrl reg 1 */
#घोषणा	MCFSIM_ICR2		(MCF_MBAR + 0x4e)	/* Intr Ctrl reg 2 */
#घोषणा	MCFSIM_ICR3		(MCF_MBAR + 0x4f)	/* Intr Ctrl reg 3 */
#घोषणा	MCFSIM_ICR4		(MCF_MBAR + 0x50)	/* Intr Ctrl reg 4 */
#घोषणा	MCFSIM_ICR5		(MCF_MBAR + 0x51)	/* Intr Ctrl reg 5 */
#घोषणा	MCFSIM_ICR6		(MCF_MBAR + 0x52)	/* Intr Ctrl reg 6 */
#घोषणा	MCFSIM_ICR7		(MCF_MBAR + 0x53)	/* Intr Ctrl reg 7 */
#घोषणा	MCFSIM_ICR8		(MCF_MBAR + 0x54)	/* Intr Ctrl reg 8 */
#घोषणा	MCFSIM_ICR9		(MCF_MBAR + 0x55)	/* Intr Ctrl reg 9 */
#घोषणा	MCFSIM_ICR10		(MCF_MBAR + 0x56)	/* Intr Ctrl reg 10 */
#घोषणा	MCFSIM_ICR11		(MCF_MBAR + 0x57)	/* Intr Ctrl reg 11 */

#घोषणा MCFSIM_CSAR0		(MCF_MBAR + 0x80)	/* CS 0 Address reg */
#घोषणा MCFSIM_CSMR0		(MCF_MBAR + 0x84)	/* CS 0 Mask reg */
#घोषणा MCFSIM_CSCR0		(MCF_MBAR + 0x8a)	/* CS 0 Control reg */
#घोषणा MCFSIM_CSAR1		(MCF_MBAR + 0x8c)	/* CS 1 Address reg */
#घोषणा MCFSIM_CSMR1		(MCF_MBAR + 0x90)	/* CS 1 Mask reg */
#घोषणा MCFSIM_CSCR1		(MCF_MBAR + 0x96)	/* CS 1 Control reg */

#घोषणा MCFSIM_CSAR2		(MCF_MBAR + 0x98)	/* CS 2 Address reg */
#घोषणा MCFSIM_CSMR2		(MCF_MBAR + 0x9c)	/* CS 2 Mask reg */
#घोषणा MCFSIM_CSCR2		(MCF_MBAR + 0xa2)	/* CS 2 Control reg */
#घोषणा MCFSIM_CSAR3		(MCF_MBAR + 0xa4)	/* CS 3 Address reg */
#घोषणा MCFSIM_CSMR3		(MCF_MBAR + 0xa8)	/* CS 3 Mask reg */
#घोषणा MCFSIM_CSCR3		(MCF_MBAR + 0xae)	/* CS 3 Control reg */
#घोषणा MCFSIM_CSAR4		(MCF_MBAR + 0xb0)	/* CS 4 Address reg */
#घोषणा MCFSIM_CSMR4		(MCF_MBAR + 0xb4)	/* CS 4 Mask reg */
#घोषणा MCFSIM_CSCR4		(MCF_MBAR + 0xba)	/* CS 4 Control reg */
#घोषणा MCFSIM_CSAR5		(MCF_MBAR + 0xbc)	/* CS 5 Address reg */
#घोषणा MCFSIM_CSMR5		(MCF_MBAR + 0xc0)	/* CS 5 Mask reg */
#घोषणा MCFSIM_CSCR5		(MCF_MBAR + 0xc6)	/* CS 5 Control reg */
#घोषणा MCFSIM_CSAR6		(MCF_MBAR + 0xc8)	/* CS 6 Address reg */
#घोषणा MCFSIM_CSMR6		(MCF_MBAR + 0xcc)	/* CS 6 Mask reg */
#घोषणा MCFSIM_CSCR6		(MCF_MBAR + 0xd2)	/* CS 6 Control reg */
#घोषणा MCFSIM_CSAR7		(MCF_MBAR + 0xd4)	/* CS 7 Address reg */
#घोषणा MCFSIM_CSMR7		(MCF_MBAR + 0xd8)	/* CS 7 Mask reg */
#घोषणा MCFSIM_CSCR7		(MCF_MBAR + 0xde)	/* CS 7 Control reg */

#घोषणा MCFSIM_DCR		(MCF_MBAR + 0x100)	/* DRAM Control */
#घोषणा MCFSIM_DACR0		(MCF_MBAR + 0x108)	/* DRAM 0 Addr/Ctrl */
#घोषणा MCFSIM_DMR0		(MCF_MBAR + 0x10c)	/* DRAM 0 Mask */
#घोषणा MCFSIM_DACR1		(MCF_MBAR + 0x110)	/* DRAM 1 Addr/Ctrl */
#घोषणा MCFSIM_DMR1		(MCF_MBAR + 0x114)	/* DRAM 1 Mask */

/*
 *	Timer module.
 */
#घोषणा MCFTIMER_BASE1		(MCF_MBAR + 0x140)	/* Base of TIMER1 */
#घोषणा MCFTIMER_BASE2		(MCF_MBAR + 0x180)	/* Base of TIMER2 */

#घोषणा MCFUART_BASE0		(MCF_MBAR + 0x1c0)	/* Base address UART0 */
#घोषणा MCFUART_BASE1		(MCF_MBAR + 0x200)	/* Base address UART1 */

#घोषणा	MCFSIM_PADDR		(MCF_MBAR + 0x244)
#घोषणा	MCFSIM_PADAT		(MCF_MBAR + 0x248)

/*
 *	DMA unit base addresses.
 */
#घोषणा MCFDMA_BASE0		(MCF_MBAR + 0x300)	/* Base address DMA 0 */
#घोषणा MCFDMA_BASE1		(MCF_MBAR + 0x340)	/* Base address DMA 1 */
#घोषणा MCFDMA_BASE2		(MCF_MBAR + 0x380)	/* Base address DMA 2 */
#घोषणा MCFDMA_BASE3		(MCF_MBAR + 0x3C0)	/* Base address DMA 3 */

/*
 * Generic GPIO support
 */
#घोषणा MCFGPIO_PIN_MAX		16
#घोषणा MCFGPIO_IRQ_MAX		-1
#घोषणा MCFGPIO_IRQ_VECBASE	-1

/*
 *	Some symbol defines क्रम the above...
 */
#घोषणा	MCFSIM_SWDICR		MCFSIM_ICR0	/* Watchकरोg समयr ICR */
#घोषणा	MCFSIM_TIMER1ICR	MCFSIM_ICR1	/* Timer 1 ICR */
#घोषणा	MCFSIM_TIMER2ICR	MCFSIM_ICR2	/* Timer 2 ICR */
#घोषणा	MCFSIM_I2CICR		MCFSIM_ICR3	/* I2C ICR */
#घोषणा	MCFSIM_UART1ICR		MCFSIM_ICR4	/* UART 1 ICR */
#घोषणा	MCFSIM_UART2ICR		MCFSIM_ICR5	/* UART 2 ICR */
#घोषणा	MCFSIM_DMA0ICR		MCFSIM_ICR6	/* DMA 0 ICR */
#घोषणा	MCFSIM_DMA1ICR		MCFSIM_ICR7	/* DMA 1 ICR */
#घोषणा	MCFSIM_DMA2ICR		MCFSIM_ICR8	/* DMA 2 ICR */
#घोषणा	MCFSIM_DMA3ICR		MCFSIM_ICR9	/* DMA 3 ICR */

/*
 *	Some symbol defines क्रम the Parallel Port Pin Assignment Register
 */
#घोषणा MCFSIM_PAR_DREQ0        0x40            /* Set to select DREQ0 input */
                                                /* Clear to select par I/O */
#घोषणा MCFSIM_PAR_DREQ1        0x20            /* Select DREQ1 input */
                                                /* Clear to select par I/O */

/*
 *       Defines क्रम the IRQPAR Register
 */
#घोषणा IRQ5_LEVEL4		0x80
#घोषणा IRQ3_LEVEL6		0x40
#घोषणा IRQ1_LEVEL2		0x20

/*
 *	Define प्रणाली peripheral IRQ usage.
 */
#घोषणा	MCF_IRQ_I2C0		29		/* I2C, Level 5 */
#घोषणा	MCF_IRQ_TIMER		30		/* Timer0, Level 6 */
#घोषणा	MCF_IRQ_PROखाताR	31		/* Timer1, Level 7 */
#घोषणा	MCF_IRQ_UART0		73		/* UART0 */
#घोषणा	MCF_IRQ_UART1		74		/* UART1 */

/*
 * I2C module
 */
#घोषणा	MCFI2C_BASE0		(MCF_MBAR + 0x280)
#घोषणा	MCFI2C_SIZE0		0x40

/****************************************************************************/
#पूर्ण_अगर	/* m5407sim_h */
