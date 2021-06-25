<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Copyright (C) 2012 Dialog Semiconductor Ltd.
 */
#अगर_अघोषित __DA9055_PDATA_H
#घोषणा __DA9055_PDATA_H

#घोषणा DA9055_MAX_REGULATORS	8

काष्ठा da9055;
काष्ठा gpio_desc;

क्रमागत gpio_select अणु
	NO_GPIO = 0,
	GPIO_1,
	GPIO_2
पूर्ण;

काष्ठा da9055_pdata अणु
	पूर्णांक (*init) (काष्ठा da9055 *da9055);
	पूर्णांक irq_base;
	पूर्णांक gpio_base;

	काष्ठा regulator_init_data *regulators[DA9055_MAX_REGULATORS];
	/* Enable RTC in RESET Mode */
	bool reset_enable;
	/*
	 * GPI muxed pin to control
	 * regulator state A/B, 0 अगर not available.
	 */
	पूर्णांक *gpio_ren;
	/*
	 * GPI muxed pin to control
	 * regulator set, 0 अगर not available.
	 */
	पूर्णांक *gpio_rsel;
	/*
	 * Regulator mode control bits value (GPI offset) that
	 * controls the regulator state, 0 अगर not available.
	 */
	क्रमागत gpio_select *reg_ren;
	/*
	 * Regulator mode control bits value (GPI offset) that
	 * controls the regulator set A/B, 0 अगर  not available.
	 */
	क्रमागत gpio_select *reg_rsel;
	/* GPIO descriptors to enable regulator, शून्य अगर not available */
	काष्ठा gpio_desc **ena_gpiods;
पूर्ण;
#पूर्ण_अगर /* __DA9055_PDATA_H */
