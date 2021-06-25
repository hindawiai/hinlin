<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * i2c-gpio पूर्णांकerface to platक्रमm code
 *
 * Copyright (C) 2007 Aपंचांगel Corporation
 */
#अगर_अघोषित _LINUX_I2C_GPIO_H
#घोषणा _LINUX_I2C_GPIO_H

/**
 * काष्ठा i2c_gpio_platक्रमm_data - Platक्रमm-dependent data क्रम i2c-gpio
 * @udelay: संकेत toggle delay. SCL frequency is (500 / udelay) kHz
 * @समयout: घड़ी stretching समयout in jअगरfies. If the slave keeps
 *	SCL low क्रम दीर्घer than this, the transfer will समय out.
 * @sda_is_खोलो_drain: SDA is configured as खोलो drain, i.e. the pin
 *	isn't actively driven high when setting the output value high.
 *	gpio_get_value() must वापस the actual pin state even अगर the
 *	pin is configured as an output.
 * @scl_is_खोलो_drain: SCL is set up as खोलो drain. Same requirements
 *	as क्रम sda_is_खोलो_drain apply.
 * @scl_is_output_only: SCL output drivers cannot be turned off.
 */
काष्ठा i2c_gpio_platक्रमm_data अणु
	पूर्णांक		udelay;
	पूर्णांक		समयout;
	अचिन्हित पूर्णांक	sda_is_खोलो_drain:1;
	अचिन्हित पूर्णांक	scl_is_खोलो_drain:1;
	अचिन्हित पूर्णांक	scl_is_output_only:1;
पूर्ण;

#पूर्ण_अगर /* _LINUX_I2C_GPIO_H */
