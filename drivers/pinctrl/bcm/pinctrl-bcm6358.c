<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम BCM6358 GPIO unit (pinctrl + GPIO)
 *
 * Copyright (C) 2021 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 * Copyright (C) 2016 Jonas Gorski <jonas.gorski@gmail.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "../pinctrl-utils.h"

#समावेश "pinctrl-bcm63xx.h"

#घोषणा BCM6358_NUM_GPIOS		40

#घोषणा BCM6358_MODE_REG		0x18
#घोषणा  BCM6358_MODE_MUX_NONE		0
#घोषणा  BCM6358_MODE_MUX_EBI_CS	BIT(5)
#घोषणा  BCM6358_MODE_MUX_UART1		BIT(6)
#घोषणा  BCM6358_MODE_MUX_SPI_CS	BIT(7)
#घोषणा  BCM6358_MODE_MUX_ASYNC_MODEM	BIT(8)
#घोषणा  BCM6358_MODE_MUX_LEGACY_LED	BIT(9)
#घोषणा  BCM6358_MODE_MUX_SERIAL_LED	BIT(10)
#घोषणा  BCM6358_MODE_MUX_LED		BIT(11)
#घोषणा  BCM6358_MODE_MUX_UTOPIA	BIT(12)
#घोषणा  BCM6358_MODE_MUX_CLKRST	BIT(13)
#घोषणा  BCM6358_MODE_MUX_PWM_SYN_CLK	BIT(14)
#घोषणा  BCM6358_MODE_MUX_SYS_IRQ	BIT(15)

काष्ठा bcm6358_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित * स्थिर pins;
	स्थिर अचिन्हित num_pins;

	स्थिर uपूर्णांक16_t mode_val;

	/* non-GPIO function muxes require the gpio direction to be set */
	स्थिर uपूर्णांक16_t direction;
पूर्ण;

काष्ठा bcm6358_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित num_groups;
पूर्ण;

काष्ठा bcm6358_priv अणु
	काष्ठा regmap_field *overlays;
पूर्ण;

#घोषणा BCM6358_GPIO_PIN(a, b, bit1, bit2, bit3)		\
	अणु							\
		.number = a,					\
		.name = b,					\
		.drv_data = (व्योम *)(BCM6358_MODE_MUX_##bit1 |	\
				     BCM6358_MODE_MUX_##bit2 |	\
				     BCM6358_MODE_MUX_##bit3),	\
	पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc bcm6358_pins[] = अणु
	BCM6358_GPIO_PIN(0, "gpio0", LED, NONE, NONE),
	BCM6358_GPIO_PIN(1, "gpio1", LED, NONE, NONE),
	BCM6358_GPIO_PIN(2, "gpio2", LED, NONE, NONE),
	BCM6358_GPIO_PIN(3, "gpio3", LED, NONE, NONE),
	PINCTRL_PIN(4, "gpio4"),
	BCM6358_GPIO_PIN(5, "gpio5", SYS_IRQ, NONE, NONE),
	BCM6358_GPIO_PIN(6, "gpio6", SERIAL_LED, NONE, NONE),
	BCM6358_GPIO_PIN(7, "gpio7", SERIAL_LED, NONE, NONE),
	BCM6358_GPIO_PIN(8, "gpio8", PWM_SYN_CLK, NONE, NONE),
	BCM6358_GPIO_PIN(9, "gpio09", LEGACY_LED, NONE, NONE),
	BCM6358_GPIO_PIN(10, "gpio10", LEGACY_LED, NONE, NONE),
	BCM6358_GPIO_PIN(11, "gpio11", LEGACY_LED, NONE, NONE),
	BCM6358_GPIO_PIN(12, "gpio12", LEGACY_LED, ASYNC_MODEM, UTOPIA),
	BCM6358_GPIO_PIN(13, "gpio13", LEGACY_LED, ASYNC_MODEM, UTOPIA),
	BCM6358_GPIO_PIN(14, "gpio14", LEGACY_LED, ASYNC_MODEM, UTOPIA),
	BCM6358_GPIO_PIN(15, "gpio15", LEGACY_LED, ASYNC_MODEM, UTOPIA),
	PINCTRL_PIN(16, "gpio16"),
	PINCTRL_PIN(17, "gpio17"),
	PINCTRL_PIN(18, "gpio18"),
	PINCTRL_PIN(19, "gpio19"),
	PINCTRL_PIN(20, "gpio20"),
	PINCTRL_PIN(21, "gpio21"),
	BCM6358_GPIO_PIN(22, "gpio22", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(23, "gpio23", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(24, "gpio24", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(25, "gpio25", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(26, "gpio26", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(27, "gpio27", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(28, "gpio28", UTOPIA, UART1, NONE),
	BCM6358_GPIO_PIN(29, "gpio29", UTOPIA, UART1, NONE),
	BCM6358_GPIO_PIN(30, "gpio30", UTOPIA, UART1, EBI_CS),
	BCM6358_GPIO_PIN(31, "gpio31", UTOPIA, UART1, EBI_CS),
	BCM6358_GPIO_PIN(32, "gpio32", SPI_CS, NONE, NONE),
	BCM6358_GPIO_PIN(33, "gpio33", SPI_CS, NONE, NONE),
	PINCTRL_PIN(34, "gpio34"),
	PINCTRL_PIN(35, "gpio35"),
	PINCTRL_PIN(36, "gpio36"),
	PINCTRL_PIN(37, "gpio37"),
	PINCTRL_PIN(38, "gpio38"),
	PINCTRL_PIN(39, "gpio39"),
पूर्ण;

अटल अचिन्हित ebi_cs_grp_pins[] = अणु 30, 31 पूर्ण;

अटल अचिन्हित uart1_grp_pins[] = अणु 28, 29, 30, 31 पूर्ण;

अटल अचिन्हित spi_cs_grp_pins[] = अणु 32, 33 पूर्ण;

अटल अचिन्हित async_modem_grp_pins[] = अणु 12, 13, 14, 15 पूर्ण;

अटल अचिन्हित serial_led_grp_pins[] = अणु 6, 7 पूर्ण;

अटल अचिन्हित legacy_led_grp_pins[] = अणु 9, 10, 11, 12, 13, 14, 15 पूर्ण;

अटल अचिन्हित led_grp_pins[] = अणु 0, 1, 2, 3 पूर्ण;

अटल अचिन्हित utopia_grp_pins[] = अणु
	12, 13, 14, 15, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
पूर्ण;

अटल अचिन्हित pwm_syn_clk_grp_pins[] = अणु 8 पूर्ण;

अटल अचिन्हित sys_irq_grp_pins[] = अणु 5 पूर्ण;

#घोषणा BCM6358_GPIO_MUX_GROUP(n, bit, dir)			\
	अणु							\
		.name = #n,					\
		.pins = n##_pins,				\
		.num_pins = ARRAY_SIZE(n##_pins),		\
		.mode_val = BCM6358_MODE_MUX_##bit,		\
		.direction = dir,				\
	पूर्ण

अटल स्थिर काष्ठा bcm6358_pingroup bcm6358_groups[] = अणु
	BCM6358_GPIO_MUX_GROUP(ebi_cs_grp, EBI_CS, 0x3),
	BCM6358_GPIO_MUX_GROUP(uart1_grp, UART1, 0x2),
	BCM6358_GPIO_MUX_GROUP(spi_cs_grp, SPI_CS, 0x6),
	BCM6358_GPIO_MUX_GROUP(async_modem_grp, ASYNC_MODEM, 0x6),
	BCM6358_GPIO_MUX_GROUP(legacy_led_grp, LEGACY_LED, 0x7f),
	BCM6358_GPIO_MUX_GROUP(serial_led_grp, SERIAL_LED, 0x3),
	BCM6358_GPIO_MUX_GROUP(led_grp, LED, 0xf),
	BCM6358_GPIO_MUX_GROUP(utopia_grp, UTOPIA, 0x000f),
	BCM6358_GPIO_MUX_GROUP(pwm_syn_clk_grp, PWM_SYN_CLK, 0x1),
	BCM6358_GPIO_MUX_GROUP(sys_irq_grp, SYS_IRQ, 0x1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर ebi_cs_groups[] = अणु
	"ebi_cs_grp"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_groups[] = अणु
	"uart1_grp"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_cs_2_3_groups[] = अणु
	"spi_cs_2_3_grp"
पूर्ण;

अटल स्थिर अक्षर * स्थिर async_modem_groups[] = अणु
	"async_modem_grp"
पूर्ण;

अटल स्थिर अक्षर * स्थिर legacy_led_groups[] = अणु
	"legacy_led_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_groups[] = अणु
	"serial_led_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर led_groups[] = अणु
	"led_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर clkrst_groups[] = अणु
	"clkrst_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_syn_clk_groups[] = अणु
	"pwm_syn_clk_grp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sys_irq_groups[] = अणु
	"sys_irq_grp",
पूर्ण;

#घोषणा BCM6358_FUN(n)					\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
	पूर्ण

अटल स्थिर काष्ठा bcm6358_function bcm6358_funcs[] = अणु
	BCM6358_FUN(ebi_cs),
	BCM6358_FUN(uart1),
	BCM6358_FUN(spi_cs_2_3),
	BCM6358_FUN(async_modem),
	BCM6358_FUN(legacy_led),
	BCM6358_FUN(serial_led),
	BCM6358_FUN(led),
	BCM6358_FUN(clkrst),
	BCM6358_FUN(pwm_syn_clk),
	BCM6358_FUN(sys_irq),
पूर्ण;

अटल पूर्णांक bcm6358_pinctrl_get_group_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6358_groups);
पूर्ण

अटल स्थिर अक्षर *bcm6358_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित group)
अणु
	वापस bcm6358_groups[group].name;
पूर्ण

अटल पूर्णांक bcm6358_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित group, स्थिर अचिन्हित **pins,
					  अचिन्हित *num_pins)
अणु
	*pins = bcm6358_groups[group].pins;
	*num_pins = bcm6358_groups[group].num_pins;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6358_pinctrl_get_func_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6358_funcs);
पूर्ण

अटल स्थिर अक्षर *bcm6358_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
						 अचिन्हित selector)
अणु
	वापस bcm6358_funcs[selector].name;
पूर्ण

अटल पूर्णांक bcm6358_pinctrl_get_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित selector,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	*groups = bcm6358_funcs[selector].groups;
	*num_groups = bcm6358_funcs[selector].num_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6358_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित selector, अचिन्हित group)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा bcm6358_priv *priv = pc->driver_data;
	स्थिर काष्ठा bcm6358_pingroup *pg = &bcm6358_groups[group];
	अचिन्हित पूर्णांक val = pg->mode_val;
	अचिन्हित पूर्णांक mask = val;
	अचिन्हित pin;

	क्रम (pin = 0; pin < pg->num_pins; pin++)
		mask |= (अचिन्हित दीर्घ)bcm6358_pins[pin].drv_data;

	regmap_field_update_bits(priv->overlays, mask, val);

	क्रम (pin = 0; pin < pg->num_pins; pin++) अणु
		काष्ठा pinctrl_gpio_range *range;
		अचिन्हित पूर्णांक hw_gpio = bcm6358_pins[pin].number;

		range = pinctrl_find_gpio_range_from_pin(pctldev, hw_gpio);
		अगर (range) अणु
			काष्ठा gpio_chip *gc = range->gc;

			अगर (pg->direction & BIT(pin))
				gc->direction_output(gc, hw_gpio, 0);
			अन्यथा
				gc->direction_input(gc, hw_gpio);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6358_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा pinctrl_gpio_range *range,
				       अचिन्हित offset)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा bcm6358_priv *priv = pc->driver_data;
	अचिन्हित पूर्णांक mask;

	mask = (अचिन्हित दीर्घ) bcm6358_pins[offset].drv_data;
	अगर (!mask)
		वापस 0;

	/* disable all functions using this pin */
	वापस regmap_field_update_bits(priv->overlays, mask, 0);
पूर्ण

अटल काष्ठा pinctrl_ops bcm6358_pctl_ops = अणु
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.get_group_name = bcm6358_pinctrl_get_group_name,
	.get_group_pins = bcm6358_pinctrl_get_group_pins,
	.get_groups_count = bcm6358_pinctrl_get_group_count,
पूर्ण;

अटल काष्ठा pinmux_ops bcm6358_pmx_ops = अणु
	.get_function_groups = bcm6358_pinctrl_get_groups,
	.get_function_name = bcm6358_pinctrl_get_func_name,
	.get_functions_count = bcm6358_pinctrl_get_func_count,
	.gpio_request_enable = bcm6358_gpio_request_enable,
	.set_mux = bcm6358_pinctrl_set_mux,
	.strict = true,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_pinctrl_soc bcm6358_soc = अणु
	.ngpios = BCM6358_NUM_GPIOS,
	.npins = ARRAY_SIZE(bcm6358_pins),
	.pctl_ops = &bcm6358_pctl_ops,
	.pins = bcm6358_pins,
	.pmx_ops = &bcm6358_pmx_ops,
पूर्ण;

अटल पूर्णांक bcm6358_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा reg_field overlays = REG_FIELD(BCM6358_MODE_REG, 0, 15);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm63xx_pinctrl *pc;
	काष्ठा bcm6358_priv *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	err = bcm63xx_pinctrl_probe(pdev, &bcm6358_soc, (व्योम *) priv);
	अगर (err)
		वापस err;

	pc = platक्रमm_get_drvdata(pdev);

	priv->overlays = devm_regmap_field_alloc(dev, pc->regs, overlays);
	अगर (IS_ERR(priv->overlays))
		वापस PTR_ERR(priv->overlays);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6358_pinctrl_match[] = अणु
	अणु .compatible = "brcm,bcm6358-pinctrl", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm6358_pinctrl_driver = अणु
	.probe = bcm6358_pinctrl_probe,
	.driver = अणु
		.name = "bcm6358-pinctrl",
		.of_match_table = bcm6358_pinctrl_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(bcm6358_pinctrl_driver);
