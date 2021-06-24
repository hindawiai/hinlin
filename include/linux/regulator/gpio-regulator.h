<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * gpio-regulator.h
 *
 * Copyright 2011 Heiko Stuebner <heiko@sntech.de>
 *
 * based on fixed.h
 *
 * Copyright 2008 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 * Copyright (c) 2009 Nokia Corporation
 * Roger Quadros <ext-roger.quadros@nokia.com>
 */

#अगर_अघोषित __REGULATOR_GPIO_H
#घोषणा __REGULATOR_GPIO_H

#समावेश <linux/gpio/consumer.h>

काष्ठा regulator_init_data;

क्रमागत regulator_type;

/**
 * काष्ठा gpio_regulator_state - state description
 * @value:		microvolts or microamps
 * @gpios:		bitfield of gpio target-states क्रम the value
 *
 * This काष्ठाure describes a supported setting of the regulator
 * and the necessary gpio-state to achieve it.
 *
 * The n-th bit in the bitfield describes the state of the n-th GPIO
 * from the gpios-array defined in gpio_regulator_config below.
 */
काष्ठा gpio_regulator_state अणु
	पूर्णांक value;
	पूर्णांक gpios;
पूर्ण;

/**
 * काष्ठा gpio_regulator_config - config काष्ठाure
 * @supply_name:	Name of the regulator supply
 * @enabled_at_boot:	Whether regulator has been enabled at
 *			boot or not. 1 = Yes, 0 = No
 *			This is used to keep the regulator at
 *			the शेष state
 * @startup_delay:	Start-up समय in microseconds
 * @gflags:		Array of GPIO configuration flags क्रम initial
 *			states
 * @ngpios:		Number of GPIOs and configurations available
 * @states:		Array of gpio_regulator_state entries describing
 *			the gpio state क्रम specअगरic voltages
 * @nr_states:		Number of states available
 * @regulator_type:	either REGULATOR_CURRENT or REGULATOR_VOLTAGE
 * @init_data:		regulator_init_data
 *
 * This काष्ठाure contains gpio-voltage regulator configuration
 * inक्रमmation that must be passed by platक्रमm code to the
 * gpio-voltage regulator driver.
 */
काष्ठा gpio_regulator_config अणु
	स्थिर अक्षर *supply_name;

	अचिन्हित enabled_at_boot:1;
	अचिन्हित startup_delay;

	क्रमागत gpiod_flags *gflags;
	पूर्णांक ngpios;

	काष्ठा gpio_regulator_state *states;
	पूर्णांक nr_states;

	क्रमागत regulator_type type;
	काष्ठा regulator_init_data *init_data;
पूर्ण;

#पूर्ण_अगर
