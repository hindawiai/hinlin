<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम AUO in-cell touchscreens
 *
 * Copyright (c) 2011 Heiko Stuebner <heiko@sntech.de>
 *
 * based on auo_touch.h from Dell Streak kernel
 *
 * Copyright (c) 2008 QUALCOMM Incorporated.
 * Copyright (c) 2008 QUALCOMM USA, INC.
 */

#अगर_अघोषित __AUO_PIXCIR_TS_H__
#घोषणा __AUO_PIXCIR_TS_H__

/*
 * Interrupt modes:
 * periodical:		पूर्णांकerrupt is निश्चितed periodicaly
 * compare coordinates:	पूर्णांकerrupt is निश्चितed when coordinates change
 * indicate touch:	पूर्णांकerrupt is निश्चितed during touch
 */
#घोषणा AUO_PIXCIR_INT_PERIODICAL	0x00
#घोषणा AUO_PIXCIR_INT_COMP_COORD	0x01
#घोषणा AUO_PIXCIR_INT_TOUCH_IND	0x02

/*
 * @gpio_पूर्णांक		पूर्णांकerrupt gpio
 * @पूर्णांक_setting		one of AUO_PIXCIR_INT_*
 * @init_hw		hardwarespecअगरic init
 * @निकास_hw		hardwarespecअगरic shutकरोwn
 * @x_max		x-resolution
 * @y_max		y-resolution
 */
काष्ठा auo_pixcir_ts_platdata अणु
	पूर्णांक gpio_पूर्णांक;
	पूर्णांक gpio_rst;

	पूर्णांक पूर्णांक_setting;

	अचिन्हित पूर्णांक x_max;
	अचिन्हित पूर्णांक y_max;
पूर्ण;

#पूर्ण_अगर
