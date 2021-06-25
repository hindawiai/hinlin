<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-sa1100/include/mach/irqs.h
 *
 * Copyright (C) 1996 Russell King
 * Copyright (C) 1998 Deborah Wallach (updates क्रम SA1100/Brutus).
 * Copyright (C) 1999 Nicolas Pitre (full GPIO irq isolation)
 *
 * 2001/11/14	RMK	Cleaned up and standardised a lot of the IRQs.
 */

#घोषणा	IRQ_GPIO0_SC		1
#घोषणा	IRQ_GPIO1_SC		2
#घोषणा	IRQ_GPIO2_SC		3
#घोषणा	IRQ_GPIO3_SC		4
#घोषणा	IRQ_GPIO4_SC		5
#घोषणा	IRQ_GPIO5_SC		6
#घोषणा	IRQ_GPIO6_SC		7
#घोषणा	IRQ_GPIO7_SC		8
#घोषणा	IRQ_GPIO8_SC		9
#घोषणा	IRQ_GPIO9_SC		10
#घोषणा	IRQ_GPIO10_SC		11
#घोषणा	IRQ_GPIO11_27		12
#घोषणा	IRQ_LCD			13	/* LCD controller           */
#घोषणा	IRQ_Ser0UDC		14	/* Ser. port 0 UDC          */
#घोषणा	IRQ_Ser1SDLC		15	/* Ser. port 1 SDLC         */
#घोषणा	IRQ_Ser1UART		16	/* Ser. port 1 UART         */
#घोषणा	IRQ_Ser2ICP		17	/* Ser. port 2 ICP          */
#घोषणा	IRQ_Ser3UART		18	/* Ser. port 3 UART         */
#घोषणा	IRQ_Ser4MCP		19	/* Ser. port 4 MCP          */
#घोषणा	IRQ_Ser4SSP		20	/* Ser. port 4 SSP          */
#घोषणा	IRQ_DMA0		21	/* DMA controller channel 0 */
#घोषणा	IRQ_DMA1		22	/* DMA controller channel 1 */
#घोषणा	IRQ_DMA2		23	/* DMA controller channel 2 */
#घोषणा	IRQ_DMA3		24	/* DMA controller channel 3 */
#घोषणा	IRQ_DMA4		25	/* DMA controller channel 4 */
#घोषणा	IRQ_DMA5		26	/* DMA controller channel 5 */
#घोषणा	IRQ_OST0		27	/* OS Timer match 0         */
#घोषणा	IRQ_OST1		28	/* OS Timer match 1         */
#घोषणा	IRQ_OST2		29	/* OS Timer match 2         */
#घोषणा	IRQ_OST3		30	/* OS Timer match 3         */
#घोषणा	IRQ_RTC1Hz		31	/* RTC 1 Hz घड़ी           */
#घोषणा	IRQ_RTCAlrm		32	/* RTC Alarm                */

#घोषणा	IRQ_GPIO0		33
#घोषणा	IRQ_GPIO1		34
#घोषणा	IRQ_GPIO2		35
#घोषणा	IRQ_GPIO3		36
#घोषणा	IRQ_GPIO4		37
#घोषणा	IRQ_GPIO5		38
#घोषणा	IRQ_GPIO6		39
#घोषणा	IRQ_GPIO7		40
#घोषणा	IRQ_GPIO8		41
#घोषणा	IRQ_GPIO9		42
#घोषणा	IRQ_GPIO10		43
#घोषणा	IRQ_GPIO11		44
#घोषणा	IRQ_GPIO12		45
#घोषणा	IRQ_GPIO13		46
#घोषणा	IRQ_GPIO14		47
#घोषणा	IRQ_GPIO15		48
#घोषणा	IRQ_GPIO16		49
#घोषणा	IRQ_GPIO17		50
#घोषणा	IRQ_GPIO18		51
#घोषणा	IRQ_GPIO19		52
#घोषणा	IRQ_GPIO20		53
#घोषणा	IRQ_GPIO21		54
#घोषणा	IRQ_GPIO22		55
#घोषणा	IRQ_GPIO23		56
#घोषणा	IRQ_GPIO24		57
#घोषणा	IRQ_GPIO25		58
#घोषणा	IRQ_GPIO26		59
#घोषणा	IRQ_GPIO27		60

/*
 * The next 16 पूर्णांकerrupts are क्रम board specअगरic purposes.  Since
 * the kernel can only run on one machine at a समय, we can re-use
 * these.  If you need more, increase IRQ_BOARD_END, but keep it
 * within sensible limits.  IRQs 61 to 76 are available.
 */
#घोषणा IRQ_BOARD_START		61
#घोषणा IRQ_BOARD_END		77

/*
 * Figure out the MAX IRQ number.
 *
 * Neponset, SA1111 and UCB1x00 are sparse IRQ aware, so can dynamically
 * allocate their IRQs above NR_IRQS.
 *
 * LoCoMo has 4 additional IRQs, but is not sparse IRQ aware, and so has
 * to be included in the NR_IRQS calculation.
 */
#अगर_घोषित CONFIG_SHARP_LOCOMO
#घोषणा NR_IRQS_LOCOMO		4
#अन्यथा
#घोषणा NR_IRQS_LOCOMO		0
#पूर्ण_अगर

#अगर_अघोषित NR_IRQS
#घोषणा NR_IRQS (IRQ_BOARD_START + NR_IRQS_LOCOMO)
#पूर्ण_अगर
#घोषणा SA1100_NR_IRQS (IRQ_BOARD_START + NR_IRQS_LOCOMO)
