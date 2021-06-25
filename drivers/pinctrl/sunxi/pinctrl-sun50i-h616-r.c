<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Allwinner H616 R_PIO pin controller driver
 *
 * Copyright (C) 2020 Arm Ltd.
 * Based on क्रमmer work, which is:
 *   Copyright (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/reset.h>

#समावेश "pinctrl-sunxi.h"

अटल स्थिर काष्ठा sunxi_desc_pin sun50i_h616_r_pins[] = अणु
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_rsb"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "s_i2c")),	/* SCK */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_rsb"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "s_i2c")),	/* SDA */
पूर्ण;

अटल स्थिर काष्ठा sunxi_pinctrl_desc sun50i_h616_r_pinctrl_data = अणु
	.pins = sun50i_h616_r_pins,
	.npins = ARRAY_SIZE(sun50i_h616_r_pins),
	.pin_base = PL_BASE,
पूर्ण;

अटल पूर्णांक sun50i_h616_r_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस sunxi_pinctrl_init(pdev,
				  &sun50i_h616_r_pinctrl_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun50i_h616_r_pinctrl_match[] = अणु
	अणु .compatible = "allwinner,sun50i-h616-r-pinctrl", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun50i_h616_r_pinctrl_driver = अणु
	.probe	= sun50i_h616_r_pinctrl_probe,
	.driver	= अणु
		.name		= "sun50i-h616-r-pinctrl",
		.of_match_table	= sun50i_h616_r_pinctrl_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sun50i_h616_r_pinctrl_driver);
