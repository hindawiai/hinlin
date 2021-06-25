<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * i2c-mux-gpio पूर्णांकerface to platक्रमm code
 *
 * Peter Korsgaard <peter.korsgaard@barco.com>
 */

#अगर_अघोषित _LINUX_I2C_MUX_GPIO_H
#घोषणा _LINUX_I2C_MUX_GPIO_H

/* MUX has no specअगरic idle mode */
#घोषणा I2C_MUX_GPIO_NO_IDLE	((अचिन्हित)-1)

/**
 * काष्ठा i2c_mux_gpio_platक्रमm_data - Platक्रमm-dependent data क्रम i2c-mux-gpio
 * @parent: Parent I2C bus adapter number
 * @base_nr: Base I2C bus number to number adapters from or zero क्रम dynamic
 * @values: Array of biपंचांगasks of GPIO settings (low/high) क्रम each
 *	position
 * @n_values: Number of multiplexer positions (busses to instantiate)
 * @classes: Optional I2C स्वतः-detection classes
 * @idle: Biपंचांगask to ग_लिखो to MUX when idle or GPIO_I2CMUX_NO_IDLE अगर not used
 */
काष्ठा i2c_mux_gpio_platक्रमm_data अणु
	पूर्णांक parent;
	पूर्णांक base_nr;
	स्थिर अचिन्हित *values;
	पूर्णांक n_values;
	स्थिर अचिन्हित *classes;
	अचिन्हित idle;
पूर्ण;

#पूर्ण_अगर /* _LINUX_I2C_MUX_GPIO_H */
