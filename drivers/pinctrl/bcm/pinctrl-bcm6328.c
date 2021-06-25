<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम BCM6328 GPIO unit (pinctrl + GPIO)
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

#घोषणा BCM6328_NUM_GPIOS	32

#घोषणा BCM6328_MODE_REG	0x18
#घोषणा BCM6328_MUX_HI_REG	0x1c
#घोषणा BCM6328_MUX_LO_REG	0x20
#घोषणा BCM6328_MUX_OTHER_REG	0x24
#घोषणा  BCM6328_MUX_MASK	GENMASK(1, 0)

काष्ठा bcm6328_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित * स्थिर pins;
	स्थिर अचिन्हित num_pins;
पूर्ण;

काष्ठा bcm6328_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित num_groups;

	अचिन्हित mode_val:1;
	अचिन्हित mux_val:2;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bcm6328_mux[] = अणु
	BCM6328_MUX_LO_REG,
	BCM6328_MUX_HI_REG,
	BCM6328_MUX_OTHER_REG
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc bcm6328_pins[] = अणु
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
	PINCTRL_PIN(30, "gpio30"),
	PINCTRL_PIN(31, "gpio31"),

	/*
	 * No idea where they really are; so let's put them according
	 * to their mux offsets.
	 */
	PINCTRL_PIN(36, "hsspi_cs1"),
	PINCTRL_PIN(38, "usb_p2"),
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

अटल अचिन्हित hsspi_cs1_pins[] = अणु 36 पूर्ण;
अटल अचिन्हित usb_port1_pins[] = अणु 38 पूर्ण;

#घोषणा BCM6328_GROUP(n)					\
	अणु							\
		.name = #n,					\
		.pins = n##_pins,				\
		.num_pins = ARRAY_SIZE(n##_pins),		\
	पूर्ण

अटल काष्ठा bcm6328_pingroup bcm6328_groups[] = अणु
	BCM6328_GROUP(gpio0),
	BCM6328_GROUP(gpio1),
	BCM6328_GROUP(gpio2),
	BCM6328_GROUP(gpio3),
	BCM6328_GROUP(gpio4),
	BCM6328_GROUP(gpio5),
	BCM6328_GROUP(gpio6),
	BCM6328_GROUP(gpio7),
	BCM6328_GROUP(gpio8),
	BCM6328_GROUP(gpio9),
	BCM6328_GROUP(gpio10),
	BCM6328_GROUP(gpio11),
	BCM6328_GROUP(gpio12),
	BCM6328_GROUP(gpio13),
	BCM6328_GROUP(gpio14),
	BCM6328_GROUP(gpio15),
	BCM6328_GROUP(gpio16),
	BCM6328_GROUP(gpio17),
	BCM6328_GROUP(gpio18),
	BCM6328_GROUP(gpio19),
	BCM6328_GROUP(gpio20),
	BCM6328_GROUP(gpio21),
	BCM6328_GROUP(gpio22),
	BCM6328_GROUP(gpio23),
	BCM6328_GROUP(gpio24),
	BCM6328_GROUP(gpio25),
	BCM6328_GROUP(gpio26),
	BCM6328_GROUP(gpio27),
	BCM6328_GROUP(gpio28),
	BCM6328_GROUP(gpio29),
	BCM6328_GROUP(gpio30),
	BCM6328_GROUP(gpio31),

	BCM6328_GROUP(hsspi_cs1),
	BCM6328_GROUP(usb_port1),
पूर्ण;

/* GPIO_MODE */
अटल स्थिर अक्षर * स्थिर led_groups[] = अणु
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio13",
	"gpio14",
	"gpio15",
	"gpio16",
	"gpio17",
	"gpio18",
	"gpio19",
	"gpio20",
	"gpio21",
	"gpio22",
	"gpio23",
पूर्ण;

/* PINMUX_SEL */
अटल स्थिर अक्षर * स्थिर serial_led_data_groups[] = अणु
	"gpio6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_clk_groups[] = अणु
	"gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर inet_act_led_groups[] = अणु
	"gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcie_clkreq_groups[] = अणु
	"gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy0_act_led_groups[] = अणु
	"gpio25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy1_act_led_groups[] = अणु
	"gpio26",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy2_act_led_groups[] = अणु
	"gpio27",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy3_act_led_groups[] = अणु
	"gpio28",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hsspi_cs1_groups[] = अणु
	"hsspi_cs1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_host_port_groups[] = अणु
	"usb_port1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_device_port_groups[] = अणु
	"usb_port1",
पूर्ण;

#घोषणा BCM6328_MODE_FUN(n)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.mode_val = 1,				\
	पूर्ण

#घोषणा BCM6328_MUX_FUN(n, mux)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.mux_val = mux,				\
	पूर्ण

अटल स्थिर काष्ठा bcm6328_function bcm6328_funcs[] = अणु
	BCM6328_MODE_FUN(led),
	BCM6328_MUX_FUN(serial_led_data, 2),
	BCM6328_MUX_FUN(serial_led_clk, 2),
	BCM6328_MUX_FUN(inet_act_led, 1),
	BCM6328_MUX_FUN(pcie_clkreq, 2),
	BCM6328_MUX_FUN(ephy0_act_led, 1),
	BCM6328_MUX_FUN(ephy1_act_led, 1),
	BCM6328_MUX_FUN(ephy2_act_led, 1),
	BCM6328_MUX_FUN(ephy3_act_led, 1),
	BCM6328_MUX_FUN(hsspi_cs1, 2),
	BCM6328_MUX_FUN(usb_host_port, 1),
	BCM6328_MUX_FUN(usb_device_port, 2),
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक bcm6328_mux_off(अचिन्हित पूर्णांक pin)
अणु
	वापस bcm6328_mux[pin / 16];
पूर्ण

अटल पूर्णांक bcm6328_pinctrl_get_group_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6328_groups);
पूर्ण

अटल स्थिर अक्षर *bcm6328_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित group)
अणु
	वापस bcm6328_groups[group].name;
पूर्ण

अटल पूर्णांक bcm6328_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित group, स्थिर अचिन्हित **pins,
					  अचिन्हित *num_pins)
अणु
	*pins = bcm6328_groups[group].pins;
	*num_pins = bcm6328_groups[group].num_pins;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6328_pinctrl_get_func_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6328_funcs);
पूर्ण

अटल स्थिर अक्षर *bcm6328_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
						 अचिन्हित selector)
अणु
	वापस bcm6328_funcs[selector].name;
पूर्ण

अटल पूर्णांक bcm6328_pinctrl_get_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित selector,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	*groups = bcm6328_funcs[selector].groups;
	*num_groups = bcm6328_funcs[selector].num_groups;

	वापस 0;
पूर्ण

अटल व्योम bcm6328_rmw_mux(काष्ठा bcm63xx_pinctrl *pc, अचिन्हित pin,
			    अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक mux)
अणु
	अगर (pin < BCM6328_NUM_GPIOS)
		regmap_update_bits(pc->regs, BCM6328_MODE_REG, BIT(pin),
				   mode ? BIT(pin) : 0);

	regmap_update_bits(pc->regs, bcm6328_mux_off(pin),
			   BCM6328_MUX_MASK << ((pin % 16) * 2),
			   mux << ((pin % 16) * 2));
पूर्ण

अटल पूर्णांक bcm6328_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित selector, अचिन्हित group)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा bcm6328_pingroup *pg = &bcm6328_groups[group];
	स्थिर काष्ठा bcm6328_function *f = &bcm6328_funcs[selector];

	bcm6328_rmw_mux(pc, pg->pins[0], f->mode_val, f->mux_val);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6328_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा pinctrl_gpio_range *range,
				       अचिन्हित offset)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);

	/* disable all functions using this pin */
	bcm6328_rmw_mux(pc, offset, 0, 0);

	वापस 0;
पूर्ण

अटल काष्ठा pinctrl_ops bcm6328_pctl_ops = अणु
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.get_group_name = bcm6328_pinctrl_get_group_name,
	.get_group_pins = bcm6328_pinctrl_get_group_pins,
	.get_groups_count = bcm6328_pinctrl_get_group_count,
पूर्ण;

अटल काष्ठा pinmux_ops bcm6328_pmx_ops = अणु
	.get_function_groups = bcm6328_pinctrl_get_groups,
	.get_function_name = bcm6328_pinctrl_get_func_name,
	.get_functions_count = bcm6328_pinctrl_get_func_count,
	.gpio_request_enable = bcm6328_gpio_request_enable,
	.set_mux = bcm6328_pinctrl_set_mux,
	.strict = true,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_pinctrl_soc bcm6328_soc = अणु
	.ngpios = BCM6328_NUM_GPIOS,
	.npins = ARRAY_SIZE(bcm6328_pins),
	.pctl_ops = &bcm6328_pctl_ops,
	.pins = bcm6328_pins,
	.pmx_ops = &bcm6328_pmx_ops,
पूर्ण;

अटल पूर्णांक bcm6328_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस bcm63xx_pinctrl_probe(pdev, &bcm6328_soc, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6328_pinctrl_match[] = अणु
	अणु .compatible = "brcm,bcm6328-pinctrl", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm6328_pinctrl_driver = अणु
	.probe = bcm6328_pinctrl_probe,
	.driver = अणु
		.name = "bcm6328-pinctrl",
		.of_match_table = bcm6328_pinctrl_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(bcm6328_pinctrl_driver);
