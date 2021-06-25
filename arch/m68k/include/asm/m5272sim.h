<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	m5272sim.h -- ColdFire 5272 System Integration Module support.
 *
 *	(C) Copyright 1999, Greg Ungerer (gerg@snapgear.com)
 * 	(C) Copyright 2000, Lineo Inc. (www.lineo.com) 
 */

/****************************************************************************/
#अगर_अघोषित	m5272sim_h
#घोषणा	m5272sim_h
/****************************************************************************/

#घोषणा	CPU_NAME		"COLDFIRE(m5272)"
#घोषणा	CPU_INSTR_PER_JIFFY	3
#घोषणा	MCF_BUSCLK		MCF_CLK

#समावेश <यंत्र/m52xxacr.h>

/*
 *	Define the 5272 SIM रेजिस्टर set addresses.
 */
#घोषणा	MCFSIM_SCR		(MCF_MBAR + 0x04)	/* SIM Config reg */
#घोषणा	MCFSIM_SPR		(MCF_MBAR + 0x06)	/* System Protection */
#घोषणा	MCFSIM_PMR		(MCF_MBAR + 0x08)	/* Power Management */
#घोषणा	MCFSIM_APMR		(MCF_MBAR + 0x0e)	/* Active Low Power */
#घोषणा	MCFSIM_सूची		(MCF_MBAR + 0x10)	/* Device Identity */

#घोषणा	MCFSIM_ICR1		(MCF_MBAR + 0x20)	/* Intr Ctrl reg 1 */
#घोषणा	MCFSIM_ICR2		(MCF_MBAR + 0x24)	/* Intr Ctrl reg 2 */
#घोषणा	MCFSIM_ICR3		(MCF_MBAR + 0x28)	/* Intr Ctrl reg 3 */
#घोषणा	MCFSIM_ICR4		(MCF_MBAR + 0x2c)	/* Intr Ctrl reg 4 */

#घोषणा	MCFSIM_ISR		(MCF_MBAR + 0x30)	/* Intr Source */
#घोषणा	MCFSIM_PITR		(MCF_MBAR + 0x34)	/* Intr Transition */
#घोषणा	MCFSIM_PIWR		(MCF_MBAR + 0x38)	/* Intr Wakeup */
#घोषणा	MCFSIM_PIVR		(MCF_MBAR + 0x3f)	/* Intr Vector */

#घोषणा	MCFSIM_WRRR		(MCF_MBAR + 0x280)	/* Watchकरोg reference */
#घोषणा	MCFSIM_WIRR		(MCF_MBAR + 0x284)	/* Watchकरोg पूर्णांकerrupt */
#घोषणा	MCFSIM_WCR		(MCF_MBAR + 0x288)	/* Watchकरोg counter */
#घोषणा	MCFSIM_WER		(MCF_MBAR + 0x28c)	/* Watchकरोg event */

#घोषणा	MCFSIM_CSBR0		(MCF_MBAR + 0x40)	/* CS0 Base Address */
#घोषणा	MCFSIM_CSOR0		(MCF_MBAR + 0x44)	/* CS0 Option */
#घोषणा	MCFSIM_CSBR1		(MCF_MBAR + 0x48)	/* CS1 Base Address */
#घोषणा	MCFSIM_CSOR1		(MCF_MBAR + 0x4c)	/* CS1 Option */
#घोषणा	MCFSIM_CSBR2		(MCF_MBAR + 0x50)	/* CS2 Base Address */
#घोषणा	MCFSIM_CSOR2		(MCF_MBAR + 0x54)	/* CS2 Option */
#घोषणा	MCFSIM_CSBR3		(MCF_MBAR + 0x58)	/* CS3 Base Address */
#घोषणा	MCFSIM_CSOR3		(MCF_MBAR + 0x5c)	/* CS3 Option */
#घोषणा	MCFSIM_CSBR4		(MCF_MBAR + 0x60)	/* CS4 Base Address */
#घोषणा	MCFSIM_CSOR4		(MCF_MBAR + 0x64)	/* CS4 Option */
#घोषणा	MCFSIM_CSBR5		(MCF_MBAR + 0x68)	/* CS5 Base Address */
#घोषणा	MCFSIM_CSOR5		(MCF_MBAR + 0x6c)	/* CS5 Option */
#घोषणा	MCFSIM_CSBR6		(MCF_MBAR + 0x70)	/* CS6 Base Address */
#घोषणा	MCFSIM_CSOR6		(MCF_MBAR + 0x74)	/* CS6 Option */
#घोषणा	MCFSIM_CSBR7		(MCF_MBAR + 0x78)	/* CS7 Base Address */
#घोषणा	MCFSIM_CSOR7		(MCF_MBAR + 0x7c)	/* CS7 Option */

#घोषणा	MCFSIM_SDCR		(MCF_MBAR + 0x180)	/* SDRAM Config */
#घोषणा	MCFSIM_SDTR		(MCF_MBAR + 0x184)	/* SDRAM Timing */
#घोषणा	MCFSIM_DCAR0		(MCF_MBAR + 0x4c)	/* DRAM 0 Address */
#घोषणा	MCFSIM_DCMR0		(MCF_MBAR + 0x50)	/* DRAM 0 Mask */
#घोषणा	MCFSIM_DCCR0		(MCF_MBAR + 0x57)	/* DRAM 0 Control */
#घोषणा	MCFSIM_DCAR1		(MCF_MBAR + 0x58)	/* DRAM 1 Address */
#घोषणा	MCFSIM_DCMR1		(MCF_MBAR + 0x5c)	/* DRAM 1 Mask reg */
#घोषणा	MCFSIM_DCCR1		(MCF_MBAR + 0x63)	/* DRAM 1 Control */

#घोषणा	MCFUART_BASE0		(MCF_MBAR + 0x100) /* Base address UART0 */
#घोषणा	MCFUART_BASE1		(MCF_MBAR + 0x140) /* Base address UART1 */

#घोषणा	MCFSIM_PACNT		(MCF_MBAR + 0x80) /* Port A Control (r/w) */
#घोषणा	MCFSIM_PADDR		(MCF_MBAR + 0x84) /* Port A Direction (r/w) */
#घोषणा	MCFSIM_PADAT		(MCF_MBAR + 0x86) /* Port A Data (r/w) */
#घोषणा	MCFSIM_PBCNT		(MCF_MBAR + 0x88) /* Port B Control (r/w) */
#घोषणा	MCFSIM_PBDDR		(MCF_MBAR + 0x8c) /* Port B Direction (r/w) */
#घोषणा	MCFSIM_PBDAT		(MCF_MBAR + 0x8e) /* Port B Data (r/w) */
#घोषणा	MCFSIM_PCDDR		(MCF_MBAR + 0x94) /* Port C Direction (r/w) */
#घोषणा	MCFSIM_PCDAT		(MCF_MBAR + 0x96) /* Port C Data (r/w) */
#घोषणा	MCFSIM_PDCNT		(MCF_MBAR + 0x98) /* Port D Control (r/w) */

#घोषणा	MCFDMA_BASE0		(MCF_MBAR + 0xe0) /* Base address DMA 0 */

#घोषणा	MCFTIMER_BASE1		(MCF_MBAR + 0x200) /* Base address TIMER1 */
#घोषणा	MCFTIMER_BASE2		(MCF_MBAR + 0x220) /* Base address TIMER2 */
#घोषणा	MCFTIMER_BASE3		(MCF_MBAR + 0x240) /* Base address TIMER4 */
#घोषणा	MCFTIMER_BASE4		(MCF_MBAR + 0x260) /* Base address TIMER3 */

#घोषणा	MCFFEC_BASE0		(MCF_MBAR + 0x840) /* Base FEC ethernet */
#घोषणा	MCFFEC_SIZE0		0x1d0

/*
 *	Define प्रणाली peripheral IRQ usage.
 */
#घोषणा	MCFINT_VECBASE		64		/* Base of पूर्णांकerrupts */
#घोषणा	MCF_IRQ_SPURIOUS	64		/* User Spurious */
#घोषणा	MCF_IRQ_EINT1		65		/* External Interrupt 1 */
#घोषणा	MCF_IRQ_EINT2		66		/* External Interrupt 2 */
#घोषणा	MCF_IRQ_EINT3		67		/* External Interrupt 3 */
#घोषणा	MCF_IRQ_EINT4		68		/* External Interrupt 4 */
#घोषणा	MCF_IRQ_TIMER1		69		/* Timer 1 */
#घोषणा	MCF_IRQ_TIMER2		70		/* Timer 2 */
#घोषणा	MCF_IRQ_TIMER3		71		/* Timer 3 */
#घोषणा	MCF_IRQ_TIMER4		72		/* Timer 4 */
#घोषणा	MCF_IRQ_UART0		73		/* UART 0 */
#घोषणा	MCF_IRQ_UART1		74		/* UART 1 */
#घोषणा	MCF_IRQ_PLIP		75		/* PLIC 2Khz Periodic */
#घोषणा	MCF_IRQ_PLIA		76		/* PLIC Asynchronous */
#घोषणा	MCF_IRQ_USB0		77		/* USB Endpoपूर्णांक 0 */
#घोषणा	MCF_IRQ_USB1		78		/* USB Endpoपूर्णांक 1 */
#घोषणा	MCF_IRQ_USB2		79		/* USB Endpoपूर्णांक 2 */
#घोषणा	MCF_IRQ_USB3		80		/* USB Endpoपूर्णांक 3 */
#घोषणा	MCF_IRQ_USB4		81		/* USB Endpoपूर्णांक 4 */
#घोषणा	MCF_IRQ_USB5		82		/* USB Endpoपूर्णांक 5 */
#घोषणा	MCF_IRQ_USB6		83		/* USB Endpoपूर्णांक 6 */
#घोषणा	MCF_IRQ_USB7		84		/* USB Endpoपूर्णांक 7 */
#घोषणा	MCF_IRQ_DMA		85		/* DMA Controller */
#घोषणा	MCF_IRQ_FECRX0		86		/* Ethernet Receiver */
#घोषणा	MCF_IRQ_FECTX0		87		/* Ethernet Transmitter */
#घोषणा	MCF_IRQ_FECENTC0	88		/* Ethernet Non-Time Critical */
#घोषणा	MCF_IRQ_QSPI		89		/* Queued Serial Interface */
#घोषणा	MCF_IRQ_EINT5		90		/* External Interrupt 5 */
#घोषणा	MCF_IRQ_EINT6		91		/* External Interrupt 6 */
#घोषणा	MCF_IRQ_SWTO		92		/* Software Watchकरोg */
#घोषणा	MCFINT_VECMAX		95		/* Maxmum पूर्णांकerrupt */

#घोषणा	MCF_IRQ_TIMER		MCF_IRQ_TIMER1
#घोषणा	MCF_IRQ_PROखाताR	MCF_IRQ_TIMER2

/*
 * Generic GPIO support
 */
#घोषणा MCFGPIO_PIN_MAX		48
#घोषणा MCFGPIO_IRQ_MAX		-1
#घोषणा MCFGPIO_IRQ_VECBASE	-1

/****************************************************************************/
#पूर्ण_अगर	/* m5272sim_h */
