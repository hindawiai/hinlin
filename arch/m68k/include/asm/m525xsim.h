<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	m525xsim.h -- ColdFire 525x System Integration Module support.
 *
 *	(C) Copyright 2012, Steven king <sfking@fdwdc.com>
 *	(C) Copyright 2002, Greg Ungerer (gerg@snapgear.com)
 */

/****************************************************************************/
#अगर_अघोषित	m525xsim_h
#घोषणा m525xsim_h
/****************************************************************************/

/*
 *	This header supports ColdFire 5249, 5251 and 5253. There are a few
 *	little dअगरferences between them, but most of the peripheral support
 *	can be used by all of them.
 */
#घोषणा CPU_NAME		"COLDFIRE(m525x)"
#घोषणा CPU_INSTR_PER_JIFFY	3
#घोषणा MCF_BUSCLK		(MCF_CLK / 2)

#समावेश <यंत्र/m52xxacr.h>

/*
 *	The 525x has a second MBAR region, define its address.
 */
#घोषणा MCF_MBAR2		0x80000000

/*
 *	Define the 525x SIM रेजिस्टर set addresses.
 */
#घोषणा MCFSIM_RSR		(MCF_MBAR + 0x00)	/* Reset Status */
#घोषणा MCFSIM_SYPCR		(MCF_MBAR + 0x01)	/* System Protection */
#घोषणा MCFSIM_SWIVR		(MCF_MBAR + 0x02)	/* SW Watchकरोg पूर्णांकr */
#घोषणा MCFSIM_SWSR		(MCF_MBAR + 0x03)	/* SW Watchकरोg srv */
#घोषणा MCFSIM_MPARK		(MCF_MBAR + 0x0C)	/* BUS Master Ctrl */
#घोषणा MCFSIM_IPR		(MCF_MBAR + 0x40)	/* Interrupt Pending */
#घोषणा MCFSIM_IMR		(MCF_MBAR + 0x44)	/* Interrupt Mask */
#घोषणा MCFSIM_ICR0		(MCF_MBAR + 0x4c)	/* Intr Ctrl reg 0 */
#घोषणा MCFSIM_ICR1		(MCF_MBAR + 0x4d)	/* Intr Ctrl reg 1 */
#घोषणा MCFSIM_ICR2		(MCF_MBAR + 0x4e)	/* Intr Ctrl reg 2 */
#घोषणा MCFSIM_ICR3		(MCF_MBAR + 0x4f)	/* Intr Ctrl reg 3 */
#घोषणा MCFSIM_ICR4		(MCF_MBAR + 0x50)	/* Intr Ctrl reg 4 */
#घोषणा MCFSIM_ICR5		(MCF_MBAR + 0x51)	/* Intr Ctrl reg 5 */
#घोषणा MCFSIM_ICR6		(MCF_MBAR + 0x52)	/* Intr Ctrl reg 6 */
#घोषणा MCFSIM_ICR7		(MCF_MBAR + 0x53)	/* Intr Ctrl reg 7 */
#घोषणा MCFSIM_ICR8		(MCF_MBAR + 0x54)	/* Intr Ctrl reg 8 */
#घोषणा MCFSIM_ICR9		(MCF_MBAR + 0x55)	/* Intr Ctrl reg 9 */
#घोषणा MCFSIM_ICR10		(MCF_MBAR + 0x56)	/* Intr Ctrl reg 10 */
#घोषणा MCFSIM_ICR11		(MCF_MBAR + 0x57)	/* Intr Ctrl reg 11 */

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

#घोषणा MCFSIM_DCR		(MCF_MBAR + 0x100)	/* DRAM Control */
#घोषणा MCFSIM_DACR0		(MCF_MBAR + 0x108)	/* DRAM 0 Addr/Ctrl */
#घोषणा MCFSIM_DMR0		(MCF_MBAR + 0x10c)	/* DRAM 0 Mask */
#घोषणा MCFSIM_DACR1		(MCF_MBAR + 0x110)	/* DRAM 1 Addr/Ctrl */
#घोषणा MCFSIM_DMR1		(MCF_MBAR + 0x114)	/* DRAM 1 Mask */

/*
 * Secondary Interrupt Controller (in MBAR2)
*/
#घोषणा MCFINTC2_INTBASE	(MCF_MBAR2 + 0x168)	/* Base Vector Reg */
#घोषणा MCFINTC2_INTPRI1	(MCF_MBAR2 + 0x140)	/* 0-7 priority */
#घोषणा MCFINTC2_INTPRI2	(MCF_MBAR2 + 0x144)	/* 8-15 priority */
#घोषणा MCFINTC2_INTPRI3	(MCF_MBAR2 + 0x148)	/* 16-23 priority */
#घोषणा MCFINTC2_INTPRI4	(MCF_MBAR2 + 0x14c)	/* 24-31 priority */
#घोषणा MCFINTC2_INTPRI5	(MCF_MBAR2 + 0x150)	/* 32-39 priority */
#घोषणा MCFINTC2_INTPRI6	(MCF_MBAR2 + 0x154)	/* 40-47 priority */
#घोषणा MCFINTC2_INTPRI7	(MCF_MBAR2 + 0x158)	/* 48-55 priority */
#घोषणा MCFINTC2_INTPRI8	(MCF_MBAR2 + 0x15c)	/* 56-63 priority */

#घोषणा MCFINTC2_INTPRI_REG(i)	(MCFINTC2_INTPRI1 + \
				((((i) - MCFINTC2_VECBASE) / 8) * 4))
#घोषणा MCFINTC2_INTPRI_BITS(b, i)	((b) << (((i) % 8) * 4))

/*
 *	Timer module.
 */
#घोषणा MCFTIMER_BASE1		(MCF_MBAR + 0x140)	/* Base of TIMER1 */
#घोषणा MCFTIMER_BASE2		(MCF_MBAR + 0x180)	/* Base of TIMER2 */

/*
 *	UART module.
 */
#घोषणा MCFUART_BASE0		(MCF_MBAR + 0x1c0)	/* Base address UART0 */
#घोषणा MCFUART_BASE1		(MCF_MBAR + 0x200)	/* Base address UART1 */

/*
 *	QSPI module.
 */
#घोषणा MCFQSPI_BASE		(MCF_MBAR + 0x400)	/* Base address QSPI */
#घोषणा MCFQSPI_SIZE		0x40			/* Register set size */

#अगर_घोषित CONFIG_M5249
#घोषणा MCFQSPI_CS0		29
#घोषणा MCFQSPI_CS1		24
#घोषणा MCFQSPI_CS2		21
#घोषणा MCFQSPI_CS3		22
#अन्यथा
#घोषणा MCFQSPI_CS0		15
#घोषणा MCFQSPI_CS1		16
#घोषणा MCFQSPI_CS2		24
#घोषणा MCFQSPI_CS3		28
#पूर्ण_अगर

/*
 *	I2C module.
 */
#घोषणा MCFI2C_BASE0		(MCF_MBAR + 0x280)	/* Base address I2C0 */
#घोषणा MCFI2C_SIZE0		0x20			/* Register set size */

#घोषणा MCFI2C_BASE1		(MCF_MBAR2 + 0x440)	/* Base address I2C1 */
#घोषणा MCFI2C_SIZE1		0x20			/* Register set size */

/*
 *	DMA unit base addresses.
 */
#घोषणा MCFDMA_BASE0		(MCF_MBAR + 0x300)	/* Base address DMA 0 */
#घोषणा MCFDMA_BASE1		(MCF_MBAR + 0x340)	/* Base address DMA 1 */
#घोषणा MCFDMA_BASE2		(MCF_MBAR + 0x380)	/* Base address DMA 2 */
#घोषणा MCFDMA_BASE3		(MCF_MBAR + 0x3C0)	/* Base address DMA 3 */

/*
 *	Some symbol defines क्रम the above...
 */
#घोषणा MCFSIM_SWDICR		MCFSIM_ICR0	/* Watchकरोg समयr ICR */
#घोषणा MCFSIM_TIMER1ICR	MCFSIM_ICR1	/* Timer 1 ICR */
#घोषणा MCFSIM_TIMER2ICR	MCFSIM_ICR2	/* Timer 2 ICR */
#घोषणा MCFSIM_I2CICR		MCFSIM_ICR3	/* I2C ICR */
#घोषणा MCFSIM_UART1ICR		MCFSIM_ICR4	/* UART 1 ICR */
#घोषणा MCFSIM_UART2ICR		MCFSIM_ICR5	/* UART 2 ICR */
#घोषणा MCFSIM_DMA0ICR		MCFSIM_ICR6	/* DMA 0 ICR */
#घोषणा MCFSIM_DMA1ICR		MCFSIM_ICR7	/* DMA 1 ICR */
#घोषणा MCFSIM_DMA2ICR		MCFSIM_ICR8	/* DMA 2 ICR */
#घोषणा MCFSIM_DMA3ICR		MCFSIM_ICR9	/* DMA 3 ICR */
#घोषणा MCFSIM_QSPIICR		MCFSIM_ICR10	/* QSPI ICR */

/*
 *	Define प्रणाली peripheral IRQ usage.
 */
#घोषणा MCF_IRQ_QSPI		28		/* QSPI, Level 4 */
#घोषणा MCF_IRQ_I2C0		29
#घोषणा MCF_IRQ_TIMER		30		/* Timer0, Level 6 */
#घोषणा MCF_IRQ_PROखाताR	31		/* Timer1, Level 7 */

#घोषणा MCF_IRQ_UART0		73		/* UART0 */
#घोषणा MCF_IRQ_UART1		74		/* UART1 */

/*
 * Define the base पूर्णांकerrupt क्रम the second पूर्णांकerrupt controller.
 * We set it to 128, out of the way of the base पूर्णांकerrupts, and plenty
 * of room क्रम its 64 पूर्णांकerrupts.
 */
#घोषणा MCFINTC2_VECBASE	128

#घोषणा MCF_IRQ_GPIO0		(MCFINTC2_VECBASE + 32)
#घोषणा MCF_IRQ_GPIO1		(MCFINTC2_VECBASE + 33)
#घोषणा MCF_IRQ_GPIO2		(MCFINTC2_VECBASE + 34)
#घोषणा MCF_IRQ_GPIO3		(MCFINTC2_VECBASE + 35)
#घोषणा MCF_IRQ_GPIO4		(MCFINTC2_VECBASE + 36)
#घोषणा MCF_IRQ_GPIO5		(MCFINTC2_VECBASE + 37)
#घोषणा MCF_IRQ_GPIO6		(MCFINTC2_VECBASE + 38)
#घोषणा MCF_IRQ_GPIO7		(MCFINTC2_VECBASE + 39)

#घोषणा MCF_IRQ_USBWUP		(MCFINTC2_VECBASE + 40)
#घोषणा MCF_IRQ_I2C1		(MCFINTC2_VECBASE + 62)

/*
 *	General purpose IO रेजिस्टरs (in MBAR2).
 */
#घोषणा MCFSIM2_GPIOREAD	(MCF_MBAR2 + 0x000)	/* GPIO पढ़ो values */
#घोषणा MCFSIM2_GPIOWRITE	(MCF_MBAR2 + 0x004)	/* GPIO ग_लिखो values */
#घोषणा MCFSIM2_GPIOENABLE	(MCF_MBAR2 + 0x008)	/* GPIO enabled */
#घोषणा MCFSIM2_GPIOFUNC	(MCF_MBAR2 + 0x00C)	/* GPIO function */
#घोषणा MCFSIM2_GPIO1READ	(MCF_MBAR2 + 0x0B0)	/* GPIO1 पढ़ो values */
#घोषणा MCFSIM2_GPIO1WRITE	(MCF_MBAR2 + 0x0B4)	/* GPIO1 ग_लिखो values */
#घोषणा MCFSIM2_GPIO1ENABLE	(MCF_MBAR2 + 0x0B8)	/* GPIO1 enabled */
#घोषणा MCFSIM2_GPIO1FUNC	(MCF_MBAR2 + 0x0BC)	/* GPIO1 function */

#घोषणा MCFSIM2_GPIOINTSTAT	(MCF_MBAR2 + 0xc0)	/* GPIO पूर्णांकr status */
#घोषणा MCFSIM2_GPIOINTCLEAR	(MCF_MBAR2 + 0xc0)	/* GPIO पूर्णांकr clear */
#घोषणा MCFSIM2_GPIOINTENABLE	(MCF_MBAR2 + 0xc4)	/* GPIO पूर्णांकr enable */

#घोषणा MCFSIM2_DMAROUTE	(MCF_MBAR2 + 0x188)     /* DMA routing */
#घोषणा MCFSIM2_IDECONFIG1	(MCF_MBAR2 + 0x18c)	/* IDEconfig1 */
#घोषणा MCFSIM2_IDECONFIG2	(MCF_MBAR2 + 0x190)	/* IDEconfig2 */

/*
 * Generic GPIO support
 */
#घोषणा MCFGPIO_PIN_MAX		64
#अगर_घोषित CONFIG_M5249
#घोषणा MCFGPIO_IRQ_MAX		-1
#घोषणा MCFGPIO_IRQ_VECBASE	-1
#अन्यथा
#घोषणा MCFGPIO_IRQ_MAX		7
#घोषणा MCFGPIO_IRQ_VECBASE	MCF_IRQ_GPIO0
#पूर्ण_अगर

/****************************************************************************/

#अगर_घोषित __ASSEMBLER__
#अगर_घोषित CONFIG_M5249C3
/*
 *	The M5249C3 board needs a little help getting all its SIM devices
 *	initialized at kernel start समय. dBUG करोesn't set much up, so
 *	we need to करो it manually.
 */
.macro m5249c3_setup
	/*
	 *	Set MBAR1 and MBAR2, just inहाल they are not set.
	 */
	movel	#0x10000001,%a0
	movec	%a0,%MBAR			/* map MBAR region */
	subql	#1,%a0				/* get MBAR address in a0 */

	movel	#0x80000001,%a1
	movec	%a1,#3086			/* map MBAR2 region */
	subql	#1,%a1				/* get MBAR2 address in a1 */

	/*
	 *      Move secondary पूर्णांकerrupts to their base (128).
	 */
	moveb	#MCFINTC2_VECBASE,%d0
	moveb	%d0,0x16b(%a1)			/* पूर्णांकerrupt base रेजिस्टर */

	/*
	 *      Work around broken CSMR0/DRAM vector problem.
	 */
	movel	#0x001F0021,%d0			/* disable C/I bit */
	movel	%d0,0x84(%a0)			/* set CSMR0 */

	/*
	 *	Disable the PLL firstly. (Who knows what state it is
	 *	in here!).
	 */
	movel	0x180(%a1),%d0			/* get current PLL value */
	andl	#0xfffffffe,%d0			/* PLL bypass first */
	movel	%d0,0x180(%a1)			/* set PLL रेजिस्टर */
	nop

#अगर CONFIG_CLOCK_FREQ == 140000000
	/*
	 *	Set initial घड़ी frequency. This assumes M5249C3 board
	 *	is fitted with 11.2896MHz crystal. It will program the
	 *	PLL क्रम 140MHz. Lets go fast :-)
	 */
	movel	#0x125a40f0,%d0			/* set क्रम 140MHz */
	movel	%d0,0x180(%a1)			/* set PLL रेजिस्टर */
	orl	#0x1,%d0
	movel	%d0,0x180(%a1)			/* set PLL रेजिस्टर */
#पूर्ण_अगर

	/*
	 *	Setup CS1 क्रम ethernet controller.
	 *	(Setup as per M5249C3 करोco).
	 */
	movel  #0xe0000000,%d0			/* CS1 mapped at 0xe0000000 */
	movel  %d0,0x8c(%a0)
	movel  #0x001f0021,%d0			/* CS1 size of 1Mb */
	movel  %d0,0x90(%a0)
	movew  #0x0080,%d0			/* CS1 = 16bit port, AA */
	movew  %d0,0x96(%a0)

	/*
	 *	Setup CS2 क्रम IDE पूर्णांकerface.
	 */
	movel	#0x50000000,%d0			/* CS2 mapped at 0x50000000 */
	movel	%d0,0x98(%a0)
	movel	#0x001f0001,%d0			/* CS2 size of 1MB */
	movel	%d0,0x9c(%a0)
	movew	#0x0080,%d0			/* CS2 = 16bit, TA */
	movew	%d0,0xa2(%a0)

	movel	#0x00107000,%d0			/* IDEconfig1 */
	movel	%d0,0x18c(%a1)
	movel	#0x000c0400,%d0			/* IDEconfig2 */
	movel	%d0,0x190(%a1)

	movel	#0x00080000,%d0			/* GPIO19, IDE reset bit */
	orl	%d0,0xc(%a1)			/* function GPIO19 */
	orl	%d0,0x8(%a1)			/* enable GPIO19 as output */
        orl	%d0,0x4(%a1)			/* de-निश्चित IDE reset */
.endm

#घोषणा	PLATFORM_SETUP	m5249c3_setup

#पूर्ण_अगर /* CONFIG_M5249C3 */
#पूर्ण_अगर /* __ASSEMBLER__ */
/****************************************************************************/
#पूर्ण_अगर	/* m525xsim_h */
