<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम BCM6368 GPIO unit (pinctrl + GPIO)
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

#घोषणा BCM6368_NUM_GPIOS	38

#घोषणा BCM6368_MODE_REG	0x18
#घोषणा BCM6368_BASEMODE_REG	0x38
#घोषणा  BCM6368_BASEMODE_MASK	0x7
#घोषणा  BCM6368_BASEMODE_GPIO	0x0
#घोषणा  BCM6368_BASEMODE_UART1	0x1

काष्ठा bcm6368_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित * स्थिर pins;
	स्थिर अचिन्हित num_pins;
पूर्ण;

काष्ठा bcm6368_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित num_groups;

	अचिन्हित dir_out:16;
	अचिन्हित basemode:3;
पूर्ण;

काष्ठा bcm6368_priv अणु
	काष्ठा regmap_field *overlays;
पूर्ण;

#घोषणा BCM6368_BASEMODE_PIN(a, b)		\
	अणु					\
		.number = a,			\
		.name = b,			\
		.drv_data = (व्योम *)true	\
	पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc bcm6368_pins[] = अणु
	PINCTRL_PIN(0, "gpio0"),
	PINCTRL_PIN(1, "gpio1"),
	PINCTRL_PIN(2, "gpio2"),
	PINCTRL_PIN(3, "gpio3"),
	PINCTRL_PIN(4, "gpio4"),
	PINCTRL_PIN(5, "gpio5"),
	PINCTRL_PIN(6, "gpio6"),
	PINCTRL_PIN(7, "gpio7"),
	PINCTRL_PIN(8, "gpio8"),
	PINCTRL_PIN(9, "gpio9"),
	PINCTRL_PIN(10, "gpio10"),
	PINCTRL_PIN(11, "gpio11"),
	PINCTRL_PIN(12, "gpio12"),
	PINCTRL_PIN(13, "gpio13"),
	PINCTRL_PIN(14, "gpio14"),
	PINCTRL_PIN(15, "gpio15"),
	PINCTRL_PIN(16, "gpio16"),
	PINCTRL_PIN(17, "gpio17"),
	PINCTRL_PIN(18, "gpio18"),
	PINCTRL_PIN(19, "gpio19"),
	PINCTRL_PIN(20, "gpio20"),
	PINCTRL_PIN(21, "gpio21"),
	PINCTRL_PIN(22, "gpio22"),
	PINCTRL_PIN(23, "gpio23"),
	PINCTRL_PIN(24, "gpio24"),
	PINCTRL_PIN(25, "gpio25"),
	PINCTRL_PIN(26, "gpio26"),
	PINCTRL_PIN(27, "gpio27"),
	PINCTRL_PIN(28, "gpio28"),
	PINCTRL_PIN(29, "gpio29"),
	BCM6368_BASEMODE_PIN(30, "gpio30"),
	BCM6368_BASEMODE_PIN(31, "gpio31"),
	BCM6368_BASEMODE_PIN(32, "gpio32"),
	BCM6368_BASEMODE_PIN(33, "gpio33"),
	PINCTRL_PIN(34, "gpio34"),
	PINCTRL_PIN(35, "gpio35"),
	PINCTRL_PIN(36, "gpio36"),
	PINCTRL_PIN(37, "gpio37"),
पूर्ण;

अटल अचिन्हित gpio0_pins[] = अणु 0 पूर्ण;
अटल अचिन्हित gpio1_pins[] = अणु 1 पूर्ण;
अटल अचिन्हित gpio2_pins[] = अणु 2 पूर्ण;
अटल अचिन्हित gpio3_pins[] = अणु 3 पूर्ण;
अटल अचिन्हित gpio4_pins[] = अणु 4 पूर्ण;
अटल अचिन्हित gpio5_pins[] = अणु 5 पूर्ण;
अटल अचिन्हित gpio6_pins[] = अणु 6 पूर्ण;
अटल अचिन्हित gpio7_pins[] = अणु 7 पूर्ण;
अटल अचिन्हित gpio8_pins[] = अणु 8 पूर्ण;
अटल अचिन्हित gpio9_pins[] = अणु 9 पूर्ण;
अटल अचिन्हित gpio10_pins[] = अणु 10 पूर्ण;
अटल अचिन्हित gpio11_pins[] = अणु 11 पूर्ण;
अटल अचिन्हित gpio12_pins[] = अणु 12 पूर्ण;
अटल अचिन्हित gpio13_pins[] = अणु 13 पूर्ण;
अटल अचिन्हित gpio14_pins[] = अणु 14 पूर्ण;
अटल अचिन्हित gpio15_pins[] = अणु 15 पूर्ण;
अटल अचिन्हित gpio16_pins[] = अणु 16 पूर्ण;
अटल अचिन्हित gpio17_pins[] = अणु 17 पूर्ण;
अटल अचिन्हित gpio18_pins[] = अणु 18 पूर्ण;
अटल अचिन्हित gpio19_pins[] = अणु 19 पूर्ण;
अटल अचिन्हित gpio20_pins[] = अणु 20 पूर्ण;
अटल अचिन्हित gpio21_pins[] = अणु 21 पूर्ण;
अटल अचिन्हित gpio22_pins[] = अणु 22 पूर्ण;
अटल अचिन्हित gpio23_pins[] = अणु 23 पूर्ण;
अटल अचिन्हित gpio24_pins[] = अणु 24 पूर्ण;
अटल अचिन्हित gpio25_pins[] = अणु 25 पूर्ण;
अटल अचिन्हित gpio26_pins[] = अणु 26 पूर्ण;
अटल अचिन्हित gpio27_pins[] = अणु 27 पूर्ण;
अटल अचिन्हित gpio28_pins[] = अणु 28 पूर्ण;
अटल अचिन्हित gpio29_pins[] = अणु 29 पूर्ण;
अटल अचिन्हित gpio30_pins[] = अणु 30 पूर्ण;
अटल अचिन्हित gpio31_pins[] = अणु 31 पूर्ण;
अटल अचिन्हित uart1_grp_pins[] = अणु 30, 31, 32, 33 पूर्ण;

#घोषणा BCM6368_GROUP(n)				\
	अणु						\
		.name = #n,				\
		.pins = n##_pins,			\
		.num_pins = ARRAY_SIZE(n##_pins),	\
	पूर्ण

अटल काष्ठा bcm6368_pingroup bcm6368_groups[] = अणु
	BCM6368_GROUP(gpio0),
	BCM6368_GROUP(gpio1),
	BCM6368_GROUP(gpio2),
	BCM6368_GROUP(gpio3),
	BCM6368_GROUP(gpio4),
	BCM6368_GROUP(gpio5),
	BCM6368_GROUP(gpio6),
	BCM6368_GROUP(gpio7),
	BCM6368_GROUP(gpio8),
	BCM6368_GROUP(gpio9),
	BCM6368_GROUP(gpio10),
	BCM6368_GROUP(gpio11),
	BCM6368_GROUP(gpio12),
	BCM6368_GROUP(gpio13),
	BCM6368_GROUP(gpio14),
	BCM6368_GROUP(gpio15),
	BCM6368_GROUP(gpio16),
	BCM6368_GROUP(gpio17),
	BCM6368_GROUP(gpio18),
	BCM6368_GROUP(gpio19),
	BCM6368_GROUP(gpio20),
	BCM6368_GROUP(gpio21),
	BCM6368_GROUP(gpio22),
	BCM6368_GROUP(gpio23),
	BCM6368_GROUP(gpio24),
	BCM6368_GROUP(gpio25),
	BCM6368_GROUP(gpio26),
	BCM6368_GROUP(gpio27),
	BCM6368_GROUP(gpio28),
	BCM6368_GROUP(gpio29),
	BCM6368_GROUP(gpio30),
	BCM6368_GROUP(gpio31),
	BCM6368_GROUP(uart1_grp),
पूर्ण;

अटल स्थिर अक्षर * स्थिर analog_afe_0_groups[] = अणु
	"gpio0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर analog_afe_1_groups[] = अणु
	"gpio1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sys_irq_groups[] = अणु
	"gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_data_groups[] = अणु
	"gpio3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_clk_groups[] = अणु
	"gpio4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर inet_led_groups[] = अणु
	"gpio5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy0_led_groups[] = अणु
	"gpio6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy1_led_groups[] = अणु
	"gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy2_led_groups[] = अणु
	"gpio8",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy3_led_groups[] = अणु
	"gpio9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर robosw_led_data_groups[] = अणु
	"gpio10",
पूर्ण;

अटल स्थिर अक्षर * स्थिर robosw_led_clk_groups[] = अणु
	"gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर robosw_led0_groups[] = अणु
	"gpio12",
पूर्ण;

अटल स्थिर अक्षर * स्थिर robosw_led1_groups[] = अणु
	"gpio13",
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_device_led_groups[] = अणु
	"gpio14",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pci_req1_groups[] = अणु
	"gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pci_gnt1_groups[] = अणु
	"gpio17",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pci_पूर्णांकb_groups[] = अणु
	"gpio18",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pci_req0_groups[] = अणु
	"gpio19",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pci_gnt0_groups[] = अणु
	"gpio20",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcmcia_cd1_groups[] = अणु
	"gpio22",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcmcia_cd2_groups[] = अणु
	"gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcmcia_vs1_groups[] = अणु
	"gpio24",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcmcia_vs2_groups[] = अणु
	"gpio25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ebi_cs2_groups[] = अणु
	"gpio26",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ebi_cs3_groups[] = अणु
	"gpio27",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_cs2_groups[] = अणु
	"gpio28",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_cs3_groups[] = अणु
	"gpio29",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_cs4_groups[] = अणु
	"gpio30",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_cs5_groups[] = अणु
	"gpio31",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_groups[] = अणु
	"uart1_grp",
पूर्ण;

#घोषणा BCM6368_FUN(n, out)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.dir_out = out,				\
	पूर्ण

#घोषणा BCM6368_BASEMODE_FUN(n, val, out)		\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.basemode = BCM6368_BASEMODE_##val,	\
		.dir_out = out,				\
	पूर्ण

अटल स्थिर काष्ठा bcm6368_function bcm6368_funcs[] = अणु
	BCM6368_FUN(analog_afe_0, 1),
	BCM6368_FUN(analog_afe_1, 1),
	BCM6368_FUN(sys_irq, 1),
	BCM6368_FUN(serial_led_data, 1),
	BCM6368_FUN(serial_led_clk, 1),
	BCM6368_FUN(inet_led, 1),
	BCM6368_FUN(ephy0_led, 1),
	BCM6368_FUN(ephy1_led, 1),
	BCM6368_FUN(ephy2_led, 1),
	BCM6368_FUN(ephy3_led, 1),
	BCM6368_FUN(robosw_led_data, 1),
	BCM6368_FUN(robosw_led_clk, 1),
	BCM6368_FUN(robosw_led0, 1),
	BCM6368_FUN(robosw_led1, 1),
	BCM6368_FUN(usb_device_led, 1),
	BCM6368_FUN(pci_req1, 0),
	BCM6368_FUN(pci_gnt1, 0),
	BCM6368_FUN(pci_पूर्णांकb, 0),
	BCM6368_FUN(pci_req0, 0),
	BCM6368_FUN(pci_gnt0, 0),
	BCM6368_FUN(pcmcia_cd1, 0),
	BCM6368_FUN(pcmcia_cd2, 0),
	BCM6368_FUN(pcmcia_vs1, 0),
	BCM6368_FUN(pcmcia_vs2, 0),
	BCM6368_FUN(ebi_cs2, 1),
	BCM6368_FUN(ebi_cs3, 1),
	BCM6368_FUN(spi_cs2, 1),
	BCM6368_FUN(spi_cs3, 1),
	BCM6368_FUN(spi_cs4, 1),
	BCM6368_FUN(spi_cs5, 1),
	BCM6368_BASEMODE_FUN(uart1, UART1, 0x6),
पूर्ण;

अटल पूर्णांक bcm6368_pinctrl_get_group_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6368_groups);
पूर्ण

अटल स्थिर अक्षर *bcm6368_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित group)
अणु
	वापस bcm6368_groups[group].name;
पूर्ण

अटल पूर्णांक bcm6368_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित group, स्थिर अचिन्हित **pins,
					  अचिन्हित *num_pins)
अणु
	*pins = bcm6368_groups[group].pins;
	*num_pins = bcm6368_groups[group].num_pins;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6368_pinctrl_get_func_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6368_funcs);
पूर्ण

अटल स्थिर अक्षर *bcm6368_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
						 अचिन्हित selector)
अणु
	वापस bcm6368_funcs[selector].name;
पूर्ण

अटल पूर्णांक bcm6368_pinctrl_get_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित selector,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	*groups = bcm6368_funcs[selector].groups;
	*num_groups = bcm6368_funcs[selector].num_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6368_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित selector, अचिन्हित group)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा bcm6368_priv *priv = pc->driver_data;
	स्थिर काष्ठा bcm6368_pingroup *pg = &bcm6368_groups[group];
	स्थिर काष्ठा bcm6368_function *fun = &bcm6368_funcs[selector];
	पूर्णांक i, pin;

	अगर (fun->basemode) अणु
		अचिन्हित पूर्णांक mask = 0;

		क्रम (i = 0; i < pg->num_pins; i++) अणु
			pin = pg->pins[i];
			अगर (pin < BCM63XX_BANK_GPIOS)
				mask |= BIT(pin);
		पूर्ण

		regmap_update_bits(pc->regs, BCM6368_MODE_REG, mask, 0);
		regmap_field_ग_लिखो(priv->overlays, fun->basemode);
	पूर्ण अन्यथा अणु
		pin = pg->pins[0];

		अगर (bcm6368_pins[pin].drv_data)
			regmap_field_ग_लिखो(priv->overlays,
					   BCM6368_BASEMODE_GPIO);

		regmap_update_bits(pc->regs, BCM6368_MODE_REG, BIT(pin),
				   BIT(pin));
	पूर्ण

	क्रम (pin = 0; pin < pg->num_pins; pin++) अणु
		काष्ठा pinctrl_gpio_range *range;
		पूर्णांक hw_gpio = bcm6368_pins[pin].number;

		range = pinctrl_find_gpio_range_from_pin(pctldev, hw_gpio);
		अगर (range) अणु
			काष्ठा gpio_chip *gc = range->gc;

			अगर (fun->dir_out & BIT(pin))
				gc->direction_output(gc, hw_gpio, 0);
			अन्यथा
				gc->direction_input(gc, hw_gpio);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6368_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा pinctrl_gpio_range *range,
				       अचिन्हित offset)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा bcm6368_priv *priv = pc->driver_data;

	अगर (offset >= BCM63XX_BANK_GPIOS && !bcm6368_pins[offset].drv_data)
		वापस 0;

	/* disable all functions using this pin */
	अगर (offset < BCM63XX_BANK_GPIOS)
		regmap_update_bits(pc->regs, BCM6368_MODE_REG, BIT(offset), 0);

	अगर (bcm6368_pins[offset].drv_data)
		regmap_field_ग_लिखो(priv->overlays, BCM6368_BASEMODE_GPIO);

	वापस 0;
पूर्ण

अटल काष्ठा pinctrl_ops bcm6368_pctl_ops = अणु
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.get_group_name = bcm6368_pinctrl_get_group_name,
	.get_group_pins = bcm6368_pinctrl_get_group_pins,
	.get_groups_count = bcm6368_pinctrl_get_group_count,
पूर्ण;

अटल काष्ठा pinmux_ops bcm6368_pmx_ops = अणु
	.get_function_groups = bcm6368_pinctrl_get_groups,
	.get_function_name = bcm6368_pinctrl_get_func_name,
	.get_functions_count = bcm6368_pinctrl_get_func_count,
	.gpio_request_enable = bcm6368_gpio_request_enable,
	.set_mux = bcm6368_pinctrl_set_mux,
	.strict = true,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_pinctrl_soc bcm6368_soc = अणु
	.ngpios = BCM6368_NUM_GPIOS,
	.npins = ARRAY_SIZE(bcm6368_pins),
	.pctl_ops = &bcm6368_pctl_ops,
	.pins = bcm6368_pins,
	.pmx_ops = &bcm6368_pmx_ops,
पूर्ण;

अटल पूर्णांक bcm6368_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा reg_field overlays = REG_FIELD(BCM6368_BASEMODE_REG, 0, 15);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm63xx_pinctrl *pc;
	काष्ठा bcm6368_priv *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	err = bcm63xx_pinctrl_probe(pdev, &bcm6368_soc, (व्योम *) priv);
	अगर (err)
		वापस err;

	pc = platक्रमm_get_drvdata(pdev);

	priv->overlays = devm_regmap_field_alloc(dev, pc->regs, overlays);
	अगर (IS_ERR(priv->overlays))
		वापस PTR_ERR(priv->overlays);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6368_pinctrl_match[] = अणु
	अणु .compatible = "brcm,bcm6368-pinctrl", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm6368_pinctrl_driver = अणु
	.probe = bcm6368_pinctrl_probe,
	.driver = अणु
		.name = "bcm6368-pinctrl",
		.of_match_table = bcm6368_pinctrl_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(bcm6368_pinctrl_driver);
