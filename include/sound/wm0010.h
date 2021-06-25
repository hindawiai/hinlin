<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * wm0010.h -- Platक्रमm data क्रम WM0010 DSP Driver
 *
 * Copyright 2012 Wolfson Microelectronics PLC.
 *
 * Author: Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित WM0010_PDATA_H
#घोषणा WM0010_PDATA_H

काष्ठा wm0010_pdata अणु
	पूर्णांक gpio_reset;

	/* Set अगर there is an inverter between the GPIO controlling
	 * the reset संकेत and the device.
	 */
	पूर्णांक reset_active_high;
	पूर्णांक irq_flags;
पूर्ण;

#पूर्ण_अगर
