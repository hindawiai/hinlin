<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  linux/drivers/अक्षर/watchकरोg/omap_wdt.h
 *
 *  BRIEF MODULE DESCRIPTION
 *      OMAP Watchकरोg समयr रेजिस्टर definitions
 *
 *  Copyright (C) 2004 Texas Instruments.
 */

#अगर_अघोषित _OMAP_WATCHDOG_H
#घोषणा _OMAP_WATCHDOG_H

#घोषणा OMAP_WATCHDOG_REV		(0x00)
#घोषणा OMAP_WATCHDOG_SYS_CONFIG	(0x10)
#घोषणा OMAP_WATCHDOG_STATUS		(0x14)
#घोषणा OMAP_WATCHDOG_CNTRL		(0x24)
#घोषणा OMAP_WATCHDOG_CRR		(0x28)
#घोषणा OMAP_WATCHDOG_LDR		(0x2c)
#घोषणा OMAP_WATCHDOG_TGR		(0x30)
#घोषणा OMAP_WATCHDOG_WPS		(0x34)
#घोषणा OMAP_WATCHDOG_SPR		(0x48)

/* Using the prescaler, the OMAP watchकरोg could go क्रम many
 * months beक्रमe firing.  These limits work without scaling,
 * with the 60 second शेष assumed by most tools and करोcs.
 */
#घोषणा TIMER_MARGIN_MAX	(24 * 60 * 60)	/* 1 day */
#घोषणा TIMER_MARGIN_DEFAULT	60	/* 60 secs */
#घोषणा TIMER_MARGIN_MIN	1

#घोषणा PTV			0	/* prescale */
#घोषणा GET_WLDR_VAL(secs)	(0xffffffff - ((secs) * (32768/(1<<PTV))) + 1)
#घोषणा GET_WCCR_SECS(val)	((0xffffffff - (val) + 1) / (32768/(1<<PTV)))

#पूर्ण_अगर				/* _OMAP_WATCHDOG_H */
