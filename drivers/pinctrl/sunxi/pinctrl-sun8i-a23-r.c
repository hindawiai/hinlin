<शैली गुरु>
/*
 * Allwinner A23 SoCs special pins pinctrl driver.
 *
 * Copyright (C) 2014 Chen-Yu Tsai
 * Chen-Yu Tsai <wens@csie.org>
 *
 * Copyright (C) 2014 Boris Brezillon
 * Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 *
 * Copyright (C) 2014 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/reset.h>

#समावेश "pinctrl-sunxi.h"

अटल स्थिर काष्ठा sunxi_desc_pin sun8i_a23_r_pins[] = अणु
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_rsb"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "s_i2c"),		/* SCK */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 0)),	/* PL_EINT0 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_rsb"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "s_i2c"),		/* SDA */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 1)),	/* PL_EINT1 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uart"),	/* TX */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 2)),	/* PL_EINT2 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uart"),	/* RX */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 3)),	/* PL_EINT3 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_jtag"),	/* MS */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 4)),	/* PL_EINT4 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_jtag"),	/* CK */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 5)),	/* PL_EINT5 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_jtag"),	/* DO */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 6)),	/* PL_EINT6 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x3, "s_jtag"),	/* DI */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 7)),	/* PL_EINT7 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_twi"),		/* SCK */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 8)),	/* PL_EINT8 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 9),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_twi"),		/* SDA */
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 9)),	/* PL_EINT9 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 10),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_pwm"),
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 10)),	/* PL_EINT10 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 11),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x4, 0, 11)),	/* PL_EINT11 */
पूर्ण;

अटल स्थिर काष्ठा sunxi_pinctrl_desc sun8i_a23_r_pinctrl_data = अणु
	.pins = sun8i_a23_r_pins,
	.npins = ARRAY_SIZE(sun8i_a23_r_pins),
	.pin_base = PL_BASE,
	.irq_banks = 1,
	.disable_strict_mode = true,
पूर्ण;

अटल पूर्णांक sun8i_a23_r_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा reset_control *rstc;
	पूर्णांक ret;

	rstc = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(rstc)) अणु
		ret = PTR_ERR(rstc);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
		dev_err(&pdev->dev, "Reset controller missing err=%d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(rstc);
	अगर (ret)
		वापस ret;

	ret = sunxi_pinctrl_init(pdev,
				 &sun8i_a23_r_pinctrl_data);

	अगर (ret)
		reset_control_निश्चित(rstc);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun8i_a23_r_pinctrl_match[] = अणु
	अणु .compatible = "allwinner,sun8i-a23-r-pinctrl", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun8i_a23_r_pinctrl_driver = अणु
	.probe	= sun8i_a23_r_pinctrl_probe,
	.driver	= अणु
		.name		= "sun8i-a23-r-pinctrl",
		.of_match_table	= sun8i_a23_r_pinctrl_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sun8i_a23_r_pinctrl_driver);
