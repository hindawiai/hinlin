<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	m5206sim.h -- ColdFire 5206 System Integration Module support.
 *
 *	(C) Copyright 1999, Greg Ungerer (gerg@snapgear.com)
 * 	(C) Copyright 2000, Lineo Inc. (www.lineo.com) 
 */

/****************************************************************************/
#अगर_अघोषित	m5206sim_h
#घोषणा	m5206sim_h
/****************************************************************************/

#घोषणा	CPU_NAME		"COLDFIRE(m5206)"
#घोषणा	CPU_INSTR_PER_JIFFY	3
#घोषणा	MCF_BUSCLK		MCF_CLK

#समावेश <यंत्र/m52xxacr.h>

/*
 *	Define the 5206 SIM रेजिस्टर set addresses.
 */
#घोषणा	MCFSIM_SIMR		(MCF_MBAR + 0x03)	/* SIM Config reg */
#घोषणा	MCFSIM_ICR1		(MCF_MBAR + 0x14)	/* Intr Ctrl reg 1 */
#घोषणा	MCFSIM_ICR2		(MCF_MBAR + 0x15)	/* Intr Ctrl reg 2 */
#घोषणा	MCFSIM_ICR3		(MCF_MBAR + 0x16)	/* Intr Ctrl reg 3 */
#घोषणा	MCFSIM_ICR4		(MCF_MBAR + 0x17)	/* Intr Ctrl reg 4 */
#घोषणा	MCFSIM_ICR5		(MCF_MBAR + 0x18)	/* Intr Ctrl reg 5 */
#घोषणा	MCFSIM_ICR6		(MCF_MBAR + 0x19)	/* Intr Ctrl reg 6 */
#घोषणा	MCFSIM_ICR7		(MCF_MBAR + 0x1a)	/* Intr Ctrl reg 7 */
#घोषणा	MCFSIM_ICR8		(MCF_MBAR + 0x1b)	/* Intr Ctrl reg 8 */
#घोषणा	MCFSIM_ICR9		(MCF_MBAR + 0x1c)	/* Intr Ctrl reg 9 */
#घोषणा	MCFSIM_ICR10		(MCF_MBAR + 0x1d)	/* Intr Ctrl reg 10 */
#घोषणा	MCFSIM_ICR11		(MCF_MBAR + 0x1e)	/* Intr Ctrl reg 11 */
#घोषणा	MCFSIM_ICR12		(MCF_MBAR + 0x1f)	/* Intr Ctrl reg 12 */
#घोषणा	MCFSIM_ICR13		(MCF_MBAR + 0x20)	/* Intr Ctrl reg 13 */
#अगर_घोषित CONFIG_M5206e
#घोषणा	MCFSIM_ICR14		(MCF_MBAR + 0x21)	/* Intr Ctrl reg 14 */
#घोषणा	MCFSIM_ICR15		(MCF_MBAR + 0x22)	/* Intr Ctrl reg 15 */
#पूर्ण_अगर

#घोषणा	MCFSIM_IMR		(MCF_MBAR + 0x36)	/* Interrupt Mask */
#घोषणा	MCFSIM_IPR		(MCF_MBAR + 0x3a)	/* Interrupt Pending */

#घोषणा	MCFSIM_RSR		(MCF_MBAR + 0x40)	/* Reset Status */
#घोषणा	MCFSIM_SYPCR		(MCF_MBAR + 0x41)	/* System Protection */

#घोषणा	MCFSIM_SWIVR		(MCF_MBAR + 0x42)	/* SW Watchकरोg पूर्णांकr */
#घोषणा	MCFSIM_SWSR		(MCF_MBAR + 0x43)	/* SW Watchकरोg srv */

#घोषणा	MCFSIM_DCRR		(MCF_MBAR + 0x46) /* DRAM Refresh reg (r/w) */
#घोषणा	MCFSIM_DCTR		(MCF_MBAR + 0x4a) /* DRAM Timing reg (r/w) */
#घोषणा	MCFSIM_DAR0		(MCF_MBAR + 0x4c) /* DRAM 0 Address reg(r/w) */
#घोषणा	MCFSIM_DMR0		(MCF_MBAR + 0x50) /* DRAM 0 Mask reg (r/w) */
#घोषणा	MCFSIM_DCR0		(MCF_MBAR + 0x57) /* DRAM 0 Control reg (r/w) */
#घोषणा	MCFSIM_DAR1		(MCF_MBAR + 0x58) /* DRAM 1 Address reg (r/w) */
#घोषणा	MCFSIM_DMR1		(MCF_MBAR + 0x5c) /* DRAM 1 Mask reg (r/w) */
#घोषणा	MCFSIM_DCR1		(MCF_MBAR + 0x63) /* DRAM 1 Control reg (r/w) */

#घोषणा	MCFSIM_CSAR0		(MCF_MBAR + 0x64)	/* CS 0 Address reg */
#घोषणा	MCFSIM_CSMR0		(MCF_MBAR + 0x68)	/* CS 0 Mask reg */
#घोषणा	MCFSIM_CSCR0		(MCF_MBAR + 0x6e)	/* CS 0 Control reg */
#घोषणा	MCFSIM_CSAR1		(MCF_MBAR + 0x70)	/* CS 1 Address reg */
#घोषणा	MCFSIM_CSMR1		(MCF_MBAR + 0x74)	/* CS 1 Mask reg */
#घोषणा	MCFSIM_CSCR1		(MCF_MBAR + 0x7a)	/* CS 1 Control reg */
#घोषणा	MCFSIM_CSAR2		(MCF_MBAR + 0x7c)	/* CS 2 Address reg */
#घोषणा	MCFSIM_CSMR2		(MCF_MBAR + 0x80)	/* CS 2 Mask reg */
#घोषणा	MCFSIM_CSCR2		(MCF_MBAR + 0x86)	/* CS 2 Control reg */
#घोषणा	MCFSIM_CSAR3		(MCF_MBAR + 0x88)	/* CS 3 Address reg */
#घोषणा	MCFSIM_CSMR3		(MCF_MBAR + 0x8c)	/* CS 3 Mask reg */
#घोषणा	MCFSIM_CSCR3		(MCF_MBAR + 0x92)	/* CS 3 Control reg */
#घोषणा	MCFSIM_CSAR4		(MCF_MBAR + 0x94)	/* CS 4 Address reg */
#घोषणा	MCFSIM_CSMR4		(MCF_MBAR + 0x98)	/* CS 4 Mask reg */
#घोषणा	MCFSIM_CSCR4		(MCF_MBAR + 0x9e)	/* CS 4 Control reg */
#घोषणा	MCFSIM_CSAR5		(MCF_MBAR + 0xa0)	/* CS 5 Address reg */
#घोषणा	MCFSIM_CSMR5		(MCF_MBAR + 0xa4)	/* CS 5 Mask reg */
#घोषणा	MCFSIM_CSCR5		(MCF_MBAR + 0xaa)	/* CS 5 Control reg */
#घोषणा	MCFSIM_CSAR6		(MCF_MBAR + 0xac)	/* CS 6 Address reg */
#घोषणा	MCFSIM_CSMR6		(MCF_MBAR + 0xb0)	/* CS 6 Mask reg */
#घोषणा	MCFSIM_CSCR6		(MCF_MBAR + 0xb6)	/* CS 6 Control reg */
#घोषणा	MCFSIM_CSAR7		(MCF_MBAR + 0xb8)	/* CS 7 Address reg */
#घोषणा	MCFSIM_CSMR7		(MCF_MBAR + 0xbc)	/* CS 7 Mask reg */
#घोषणा	MCFSIM_CSCR7		(MCF_MBAR + 0xc2)	/* CS 7 Control reg */
#घोषणा	MCFSIM_DMCR		(MCF_MBAR + 0xc6)	/* Default control */

#अगर_घोषित CONFIG_M5206e
#घोषणा	MCFSIM_PAR		(MCF_MBAR + 0xca)	/* Pin Assignment */
#अन्यथा
#घोषणा	MCFSIM_PAR		(MCF_MBAR + 0xcb)	/* Pin Assignment */
#पूर्ण_अगर

#घोषणा	MCFTIMER_BASE1		(MCF_MBAR + 0x100)	/* Base of TIMER1 */
#घोषणा	MCFTIMER_BASE2		(MCF_MBAR + 0x120)	/* Base of TIMER2 */

#घोषणा	MCFSIM_PADDR		(MCF_MBAR + 0x1c5)	/* Parallel Direction (r/w) */
#घोषणा	MCFSIM_PADAT		(MCF_MBAR + 0x1c9)	/* Parallel Port Value (r/w) */

#घोषणा	MCFDMA_BASE0		(MCF_MBAR + 0x200)	/* Base address DMA 0 */
#घोषणा	MCFDMA_BASE1		(MCF_MBAR + 0x240)	/* Base address DMA 1 */

#अगर defined(CONFIG_NETtel)
#घोषणा	MCFUART_BASE0		(MCF_MBAR + 0x180)	/* Base address UART0 */
#घोषणा	MCFUART_BASE1		(MCF_MBAR + 0x140)	/* Base address UART1 */
#अन्यथा
#घोषणा	MCFUART_BASE0		(MCF_MBAR + 0x140)	/* Base address UART0 */
#घोषणा	MCFUART_BASE1		(MCF_MBAR + 0x180)	/* Base address UART1 */
#पूर्ण_अगर

/*
 *	Define प्रणाली peripheral IRQ usage.
 */
#घोषणा	MCF_IRQ_I2C0		29		/* I2C, Level 5 */
#घोषणा	MCF_IRQ_TIMER		30		/* Timer0, Level 6 */
#घोषणा	MCF_IRQ_PROखाताR	31		/* Timer1, Level 7 */
#घोषणा	MCF_IRQ_UART0		73		/* UART0 */
#घोषणा	MCF_IRQ_UART1		74		/* UART1 */

/*
 *	Generic GPIO
 */
#घोषणा MCFGPIO_PIN_MAX		8
#घोषणा MCFGPIO_IRQ_VECBASE	-1
#घोषणा MCFGPIO_IRQ_MAX		-1

/*
 *	Some symbol defines क्रम the Parallel Port Pin Assignment Register
 */
#अगर_घोषित CONFIG_M5206e
#घोषणा MCFSIM_PAR_DREQ0        0x100           /* Set to select DREQ0 input */
                                                /* Clear to select T0 input */
#घोषणा MCFSIM_PAR_DREQ1        0x200           /* Select DREQ1 input */
                                                /* Clear to select T0 output */
#पूर्ण_अगर

/*
 *	Some symbol defines क्रम the Interrupt Control Register
 */
#घोषणा	MCFSIM_SWDICR		MCFSIM_ICR8	/* Watchकरोg समयr ICR */
#घोषणा	MCFSIM_TIMER1ICR	MCFSIM_ICR9	/* Timer 1 ICR */
#घोषणा	MCFSIM_TIMER2ICR	MCFSIM_ICR10	/* Timer 2 ICR */
#घोषणा	MCFSIM_I2CICR		MCFSIM_ICR11	/* I2C ICR */
#घोषणा	MCFSIM_UART1ICR		MCFSIM_ICR12	/* UART 1 ICR */
#घोषणा	MCFSIM_UART2ICR		MCFSIM_ICR13	/* UART 2 ICR */
#अगर_घोषित CONFIG_M5206e
#घोषणा	MCFSIM_DMA1ICR		MCFSIM_ICR14	/* DMA 1 ICR */
#घोषणा	MCFSIM_DMA2ICR		MCFSIM_ICR15	/* DMA 2 ICR */
#पूर्ण_अगर

/*
 * I2C Controller
*/
#घोषणा MCFI2C_BASE0		(MCF_MBAR + 0x1e0)
#घोषणा MCFI2C_SIZE0		0x40

/****************************************************************************/
#पूर्ण_अगर	/* m5206sim_h */
