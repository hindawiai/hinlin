<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * drivers/watchकरोg/at91sam9_wdt.h
 *
 * Copyright (C) 2007 Andrew Victor
 * Copyright (C) 2007 Aपंचांगel Corporation.
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * Watchकरोg Timer (WDT) - System peripherals regsters.
 * Based on AT91SAM9261 datasheet revision D.
 * Based on SAM9X60 datasheet.
 *
 */

#अगर_अघोषित AT91_WDT_H
#घोषणा AT91_WDT_H

#समावेश <linux/bits.h>

#घोषणा AT91_WDT_CR		0x00			/* Watchकरोg Control Register */
#घोषणा  AT91_WDT_WDRSTT	BIT(0)			/* Restart */
#घोषणा  AT91_WDT_KEY		(0xa5UL << 24)		/* KEY Password */

#घोषणा AT91_WDT_MR		0x04			/* Watchकरोg Mode Register */
#घोषणा  AT91_WDT_WDV		(0xfffUL << 0)		/* Counter Value */
#घोषणा  AT91_WDT_SET_WDV(x)	((x) & AT91_WDT_WDV)
#घोषणा  AT91_SAM9X60_PERIODRST	BIT(4)		/* Period Reset */
#घोषणा  AT91_SAM9X60_RPTHRST	BIT(5)		/* Minimum Restart Period */
#घोषणा  AT91_WDT_WDFIEN	BIT(12)		/* Fault Interrupt Enable */
#घोषणा  AT91_SAM9X60_WDDIS	BIT(12)		/* Watchकरोg Disable */
#घोषणा  AT91_WDT_WDRSTEN	BIT(13)		/* Reset Processor */
#घोषणा  AT91_WDT_WDRPROC	BIT(14)		/* Timer Restart */
#घोषणा  AT91_WDT_WDDIS		BIT(15)		/* Watchकरोg Disable */
#घोषणा  AT91_WDT_WDD		(0xfffUL << 16)		/* Delta Value */
#घोषणा  AT91_WDT_SET_WDD(x)	(((x) << 16) & AT91_WDT_WDD)
#घोषणा  AT91_WDT_WDDBGHLT	BIT(28)		/* Debug Halt */
#घोषणा  AT91_WDT_WDIDLEHLT	BIT(29)		/* Idle Halt */

#घोषणा AT91_WDT_SR		0x08		/* Watchकरोg Status Register */
#घोषणा  AT91_WDT_WDUNF		BIT(0)		/* Watchकरोg Underflow */
#घोषणा  AT91_WDT_WDERR		BIT(1)		/* Watchकरोg Error */

/* Watchकरोg Timer Value Register */
#घोषणा AT91_SAM9X60_VR		0x08

/* Watchकरोg Winकरोw Level Register */
#घोषणा AT91_SAM9X60_WLR	0x0c
/* Watchकरोg Period Value */
#घोषणा  AT91_SAM9X60_COUNTER	(0xfffUL << 0)
#घोषणा  AT91_SAM9X60_SET_COUNTER(x)	((x) & AT91_SAM9X60_COUNTER)

/* Interrupt Enable Register */
#घोषणा AT91_SAM9X60_IER	0x14
/* Period Interrupt Enable */
#घोषणा  AT91_SAM9X60_PERINT	BIT(0)
/* Interrupt Disable Register */
#घोषणा AT91_SAM9X60_IDR	0x18
/* Interrupt Status Register */
#घोषणा AT91_SAM9X60_ISR	0x1c

#पूर्ण_अगर
