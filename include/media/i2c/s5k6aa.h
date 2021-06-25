<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * S5K6AAFX camera sensor driver header
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित S5K6AA_H
#घोषणा S5K6AA_H

#समावेश <media/v4l2-mediabus.h>

/**
 * काष्ठा s5k6aa_gpio - data काष्ठाure describing a GPIO
 * @gpio:  GPIO number
 * @level: indicates active state of the @gpio
 */
काष्ठा s5k6aa_gpio अणु
	पूर्णांक gpio;
	पूर्णांक level;
पूर्ण;

/**
 * काष्ठा s5k6aa_platक्रमm_data - s5k6aa driver platक्रमm data
 * @set_घातer:   an additional callback to the board code, called
 *               after enabling the regulators and beक्रमe चयनing
 *               the sensor off
 * @mclk_frequency: sensor's master घड़ी frequency in Hz
 * @gpio_reset:  GPIO driving RESET pin
 * @gpio_stby:   GPIO driving STBY pin
 * @bus_type:    bus type
 * @nlanes:      maximum number of MIPI-CSI lanes used
 * @horiz_flip:  शेष horizontal image flip value, non zero to enable
 * @vert_flip:   शेष vertical image flip value, non zero to enable
 */

काष्ठा s5k6aa_platक्रमm_data अणु
	पूर्णांक (*set_घातer)(पूर्णांक enable);
	अचिन्हित दीर्घ mclk_frequency;
	काष्ठा s5k6aa_gpio gpio_reset;
	काष्ठा s5k6aa_gpio gpio_stby;
	क्रमागत v4l2_mbus_type bus_type;
	u8 nlanes;
	u8 horiz_flip;
	u8 vert_flip;
पूर्ण;

#पूर्ण_अगर /* S5K6AA_H */
