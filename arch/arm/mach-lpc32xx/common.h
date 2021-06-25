<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/arm/mach-lpc32xx/common.h
 *
 * Author: Kevin Wells <kevin.wells@nxp.com>
 *
 * Copyright (C) 2009-2010 NXP Semiconductors
 */

#अगर_अघोषित __LPC32XX_COMMON_H
#घोषणा __LPC32XX_COMMON_H

#समावेश <linux/init.h>

/*
 * Other arch specअगरic काष्ठाures and functions
 */
बाह्य व्योम __init lpc32xx_map_io(व्योम);
बाह्य व्योम __init lpc32xx_serial_init(व्योम);

/*
 * Returns the LPC32xx unique 128-bit chip ID
 */
बाह्य व्योम lpc32xx_get_uid(u32 devid[4]);

/*
 * Poपूर्णांकers used क्रम sizing and copying suspend function data
 */
बाह्य पूर्णांक lpc32xx_sys_suspend(व्योम);
बाह्य पूर्णांक lpc32xx_sys_suspend_sz;

#पूर्ण_अगर
