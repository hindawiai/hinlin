<शैली गुरु>
/*
 * Allwinner A31 SoCs special pins pinctrl driver.
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

अटल स्थिर काष्ठा sunxi_desc_pin sun6i_a31_r_pins[] = अणु
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c"),		/* SCK */
		  SUNXI_FUNCTION(0x3, "s_p2wi")),	/* SCK */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_i2c"),		/* SDA */
		  SUNXI_FUNCTION(0x3, "s_p2wi")),	/* SDA */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uart")),	/* TX */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_uart")),	/* RX */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION(0x2, "s_ir")),		/* RX */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 0, 0),	/* PL_EINT0 */
		  SUNXI_FUNCTION(0x3, "s_jtag")),	/* MS */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 0, 1),	/* PL_EINT1 */
		  SUNXI_FUNCTION(0x3, "s_jtag")),	/* CK */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 0, 2),	/* PL_EINT2 */
		  SUNXI_FUNCTION(0x3, "s_jtag")),	/* DO */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(L, 8),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 0, 3),	/* PL_EINT3 */
		  SUNXI_FUNCTION(0x3, "s_jtag")),	/* DI */
	/* Hole */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 0),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 1, 0)),	/* PM_EINT0 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 1),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 1, 1)),	/* PM_EINT1 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 2),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 1, 2),	/* PM_EINT2 */
		  SUNXI_FUNCTION(0x3, "1wire")),
	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 3),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 1, 3)),	/* PM_EINT3 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 4),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 1, 4)),	/* PM_EINT4 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 5),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 1, 5)),	/* PM_EINT5 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 6),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 1, 6)),	/* PM_EINT6 */
	SUNXI_PIN(SUNXI_PINCTRL_PIN(M, 7),
		  SUNXI_FUNCTION(0x0, "gpio_in"),
		  SUNXI_FUNCTION(0x1, "gpio_out"),
		  SUNXI_FUNCTION_IRQ_BANK(0x2, 1, 7),	/* PM_EINT7 */
		  SUNXI_FUNCTION(0x3, "rtc")),		/* CLKO */
पूर्ण;

अटल स्थिर काष्ठा sunxi_pinctrl_desc sun6i_a31_r_pinctrl_data = अणु
	.pins = sun6i_a31_r_pins,
	.npins = ARRAY_SIZE(sun6i_a31_r_pins),
	.pin_base = PL_BASE,
	.irq_banks = 2,
	.disable_strict_mode = true,
पूर्ण;

अटल पूर्णांक sun6i_a31_r_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा reset_control *rstc;
	पूर्णांक ret;

	rstc = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(rstc)) अणु
		dev_err(&pdev->dev, "Reset controller missing\n");
		वापस PTR_ERR(rstc);
	पूर्ण

	ret = reset_control_deनिश्चित(rstc);
	अगर (ret)
		वापस ret;

	ret = sunxi_pinctrl_init(pdev,
				 &sun6i_a31_r_pinctrl_data);

	अगर (ret)
		reset_control_निश्चित(rstc);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun6i_a31_r_pinctrl_match[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-r-pinctrl", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun6i_a31_r_pinctrl_driver = अणु
	.probe	= sun6i_a31_r_pinctrl_probe,
	.driver	= अणु
		.name		= "sun6i-a31-r-pinctrl",
		.of_match_table	= sun6i_a31_r_pinctrl_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sun6i_a31_r_pinctrl_driver);
