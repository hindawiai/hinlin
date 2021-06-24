<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * S5K4ECGX image sensor header file
 *
 * Copyright (C) 2012, Linaro
 * Copyright (C) 2012, Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित S5K4ECGX_H
#घोषणा S5K4ECGX_H

/**
 * काष्ठा s5k4ecgx_gpio - data काष्ठाure describing a GPIO
 * @gpio: GPIO number
 * @level: indicates active state of the @gpio
 */
काष्ठा s5k4ecgx_gpio अणु
	पूर्णांक gpio;
	पूर्णांक level;
पूर्ण;

/**
 * काष्ठा s5k4ecgx_platक्रमm_data - s5k4ecgx driver platक्रमm data
 * @gpio_reset:	 GPIO driving RESET pin
 * @gpio_stby:	 GPIO driving STBY pin
 */

काष्ठा s5k4ecgx_platक्रमm_data अणु
	काष्ठा s5k4ecgx_gpio gpio_reset;
	काष्ठा s5k4ecgx_gpio gpio_stby;
पूर्ण;

#पूर्ण_अगर /* S5K4ECGX_H */
