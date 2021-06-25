<शैली गुरु>
/*
 * DaVinci GPIO Platक्रमm Related Defines
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __DAVINCI_GPIO_PLATFORM_H
#घोषणा __DAVINCI_GPIO_PLATFORM_H

काष्ठा davinci_gpio_platक्रमm_data अणु
	bool	no_स्वतः_base;
	u32	base;
	u32	ngpio;
	u32	gpio_unbanked;
पूर्ण;

/* Convert GPIO संकेत to GPIO pin number */
#घोषणा GPIO_TO_PIN(bank, gpio)	(16 * (bank) + (gpio))

#पूर्ण_अगर
