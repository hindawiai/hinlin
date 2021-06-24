<शैली गुरु>
/*
 * Samsung LSI S5C73M3 8M pixel camera driver
 *
 * Copyright (C) 2012, Samsung Electronics, Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 * Andrzej Hajda <a.hajda@samsung.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#अगर_अघोषित MEDIA_S5C73M3__
#घोषणा MEDIA_S5C73M3__

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-mediabus.h>

/**
 * काष्ठा s5c73m3_gpio - data काष्ठाure describing a GPIO
 * @gpio:  GPIO number
 * @level: indicates active state of the @gpio
 */
काष्ठा s5c73m3_gpio अणु
	पूर्णांक gpio;
	पूर्णांक level;
पूर्ण;

/**
 * काष्ठा s5c73m3_platक्रमm_data - s5c73m3 driver platक्रमm data
 * @mclk_frequency: sensor's master घड़ी frequency in Hz
 * @gpio_reset:  GPIO driving RESET pin
 * @gpio_stby:   GPIO driving STBY pin
 * @bus_type:    bus type
 * @nlanes:      maximum number of MIPI-CSI lanes used
 * @horiz_flip:  शेष horizontal image flip value, non zero to enable
 * @vert_flip:   शेष vertical image flip value, non zero to enable
 */

काष्ठा s5c73m3_platक्रमm_data अणु
	अचिन्हित दीर्घ mclk_frequency;

	काष्ठा s5c73m3_gpio gpio_reset;
	काष्ठा s5c73m3_gpio gpio_stby;

	क्रमागत v4l2_mbus_type bus_type;
	u8 nlanes;
	u8 horiz_flip;
	u8 vert_flip;
पूर्ण;

#पूर्ण_अगर /* MEDIA_S5C73M3__ */
