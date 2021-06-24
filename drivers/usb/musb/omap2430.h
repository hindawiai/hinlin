<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2005-2006 by Texas Instruments
 */

#अगर_अघोषित __MUSB_OMAP243X_H__
#घोषणा __MUSB_OMAP243X_H__

#समावेश <linux/platक्रमm_data/usb-omap.h>

/*
 * OMAP2430-specअगरic definitions
 */

#घोषणा OTG_REVISION		0x400

#घोषणा OTG_SYSCONFIG		0x404
#	define	MIDLEMODE	12	/* bit position */
#	define	FORCESTDBY		(0 << MIDLEMODE)
#	define	NOSTDBY			(1 << MIDLEMODE)
#	define	SMARTSTDBY		(2 << MIDLEMODE)

#	define	SIDLEMODE		3	/* bit position */
#	define	FORCEIDLE		(0 << SIDLEMODE)
#	define	NOIDLE			(1 << SIDLEMODE)
#	define	SMARTIDLE		(2 << SIDLEMODE)

#	define	ENABLEWAKEUP		(1 << 2)
#	define	SOFTRST			(1 << 1)
#	define	AUTOIDLE		(1 << 0)

#घोषणा OTG_SYSSTATUS		0x408
#	define	RESETDONE		(1 << 0)

#घोषणा OTG_INTERFSEL		0x40c
#	define	EXTCP			(1 << 2)
#	define	PHYSEL			0	/* bit position */
#	define	UTMI_8BIT		(0 << PHYSEL)
#	define	ULPI_12PIN		(1 << PHYSEL)
#	define	ULPI_8PIN		(2 << PHYSEL)

#घोषणा OTG_SIMENABLE		0x410
#	define	TM1			(1 << 0)

#घोषणा OTG_FORCESTDBY		0x414
#	define	ENABLEFORCE		(1 << 0)

#पूर्ण_अगर	/* __MUSB_OMAP243X_H__ */
