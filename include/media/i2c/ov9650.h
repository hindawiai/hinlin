<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OV9650/OV9652 camera sensors driver
 *
 * Copyright (C) 2013 Sylwester Nawrocki <sylvester.nawrocki@gmail.com>
 */
#अगर_अघोषित OV9650_H_
#घोषणा OV9650_H_

/**
 * काष्ठा ov9650_platक्रमm_data - ov9650 driver platक्रमm data
 * @mclk_frequency: the sensor's master घड़ी frequency in Hz
 * @gpio_pwdn:	    number of a GPIO connected to OV965X PWDN pin
 * @gpio_reset:     number of a GPIO connected to OV965X RESET pin
 *
 * If any of @gpio_pwdn or @gpio_reset are unused then they should be
 * set to a negative value. @mclk_frequency must always be specअगरied.
 */
काष्ठा ov9650_platक्रमm_data अणु
	अचिन्हित दीर्घ mclk_frequency;
	पूर्णांक gpio_pwdn;
	पूर्णांक gpio_reset;
पूर्ण;
#पूर्ण_अगर /* OV9650_H_ */
