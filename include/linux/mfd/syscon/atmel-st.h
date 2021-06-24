<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2005 Ivan Kokshaysky
 * Copyright (C) SAN People
 *
 * System Timer (ST) - System peripherals रेजिस्टरs.
 * Based on AT91RM9200 datasheet revision E.
 */

#अगर_अघोषित _LINUX_MFD_SYSCON_ATMEL_ST_H
#घोषणा _LINUX_MFD_SYSCON_ATMEL_ST_H

#समावेश <linux/bitops.h>

#घोषणा AT91_ST_CR	0x00	/* Control Register */
#घोषणा		AT91_ST_WDRST	BIT(0)	/* Watchकरोg Timer Restart */

#घोषणा AT91_ST_PIMR	0x04	/* Period Interval Mode Register */
#घोषणा		AT91_ST_PIV	0xffff	/* Period Interval Value */

#घोषणा AT91_ST_WDMR	0x08	/* Watchकरोg Mode Register */
#घोषणा		AT91_ST_WDV	0xffff	/* Watchकरोg Counter Value */
#घोषणा		AT91_ST_RSTEN	BIT(16)	/* Reset Enable */
#घोषणा		AT91_ST_EXTEN	BIT(17)	/* External Signal Assertion Enable */

#घोषणा AT91_ST_RTMR	0x0c	/* Real-समय Mode Register */
#घोषणा		AT91_ST_RTPRES	0xffff	/* Real-समय Prescalar Value */

#घोषणा AT91_ST_SR	0x10	/* Status Register */
#घोषणा		AT91_ST_PITS	BIT(0)	/* Period Interval Timer Status */
#घोषणा		AT91_ST_WDOVF	BIT(1)	/* Watchकरोg Overflow */
#घोषणा		AT91_ST_RTTINC	BIT(2)	/* Real-समय Timer Increment */
#घोषणा		AT91_ST_ALMS	BIT(3)	/* Alarm Status */

#घोषणा AT91_ST_IER	0x14	/* Interrupt Enable Register */
#घोषणा AT91_ST_IDR	0x18	/* Interrupt Disable Register */
#घोषणा AT91_ST_IMR	0x1c	/* Interrupt Mask Register */

#घोषणा AT91_ST_RTAR	0x20	/* Real-समय Alarm Register */
#घोषणा		AT91_ST_ALMV	0xfffff	/* Alarm Value */

#घोषणा AT91_ST_CRTR	0x24	/* Current Real-समय Register */
#घोषणा		AT91_ST_CRTV	0xfffff	/* Current Real-Time Value */

#पूर्ण_अगर /* _LINUX_MFD_SYSCON_ATMEL_ST_H */
