<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम BCM6318 GPIO unit (pinctrl + GPIO)
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

#घोषणा BCM6318_NUM_GPIOS	50
#घोषणा BCM6318_NUM_MUX		48

#घोषणा BCM6318_MODE_REG	0x18
#घोषणा BCM6318_MUX_REG		0x1c
#घोषणा  BCM6328_MUX_MASK	GENMASK(1, 0)
#घोषणा BCM6318_PAD_REG		0x54
#घोषणा  BCM6328_PAD_MASK	GENMASK(3, 0)

काष्ठा bcm6318_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित * स्थिर pins;
	स्थिर अचिन्हित num_pins;
पूर्ण;

काष्ठा bcm6318_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित num_groups;

	अचिन्हित mode_val:1;
	अचिन्हित mux_val:2;
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc bcm6318_pins[] = अणु
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
	PINCTRL_PIN(32, "gpio32"),
	PINCTRL_PIN(33, "gpio33"),
	PINCTRL_PIN(34, "gpio34"),
	PINCTRL_PIN(35, "gpio35"),
	PINCTRL_PIN(36, "gpio36"),
	PINCTRL_PIN(37, "gpio37"),
	PINCTRL_PIN(38, "gpio38"),
	PINCTRL_PIN(39, "gpio39"),
	PINCTRL_PIN(40, "gpio40"),
	PINCTRL_PIN(41, "gpio41"),
	PINCTRL_PIN(42, "gpio42"),
	PINCTRL_PIN(43, "gpio43"),
	PINCTRL_PIN(44, "gpio44"),
	PINCTRL_PIN(45, "gpio45"),
	PINCTRL_PIN(46, "gpio46"),
	PINCTRL_PIN(47, "gpio47"),
	PINCTRL_PIN(48, "gpio48"),
	PINCTRL_PIN(49, "gpio49"),
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
अटल अचिन्हित gpio32_pins[] = अणु 32 पूर्ण;
अटल अचिन्हित gpio33_pins[] = अणु 33 पूर्ण;
अटल अचिन्हित gpio34_pins[] = अणु 34 पूर्ण;
अटल अचिन्हित gpio35_pins[] = अणु 35 पूर्ण;
अटल अचिन्हित gpio36_pins[] = अणु 36 पूर्ण;
अटल अचिन्हित gpio37_pins[] = अणु 37 पूर्ण;
अटल अचिन्हित gpio38_pins[] = अणु 38 पूर्ण;
अटल अचिन्हित gpio39_pins[] = अणु 39 पूर्ण;
अटल अचिन्हित gpio40_pins[] = अणु 40 पूर्ण;
अटल अचिन्हित gpio41_pins[] = अणु 41 पूर्ण;
अटल अचिन्हित gpio42_pins[] = अणु 42 पूर्ण;
अटल अचिन्हित gpio43_pins[] = अणु 43 पूर्ण;
अटल अचिन्हित gpio44_pins[] = अणु 44 पूर्ण;
अटल अचिन्हित gpio45_pins[] = अणु 45 पूर्ण;
अटल अचिन्हित gpio46_pins[] = अणु 46 पूर्ण;
अटल अचिन्हित gpio47_pins[] = अणु 47 पूर्ण;
अटल अचिन्हित gpio48_pins[] = अणु 48 पूर्ण;
अटल अचिन्हित gpio49_pins[] = अणु 49 पूर्ण;

#घोषणा BCM6318_GROUP(n)					\
	अणु							\
		.name = #n,					\
		.pins = n##_pins,				\
		.num_pins = ARRAY_SIZE(n##_pins),		\
	पूर्ण

अटल काष्ठा bcm6318_pingroup bcm6318_groups[] = अणु
	BCM6318_GROUP(gpio0),
	BCM6318_GROUP(gpio1),
	BCM6318_GROUP(gpio2),
	BCM6318_GROUP(gpio3),
	BCM6318_GROUP(gpio4),
	BCM6318_GROUP(gpio5),
	BCM6318_GROUP(gpio6),
	BCM6318_GROUP(gpio7),
	BCM6318_GROUP(gpio8),
	BCM6318_GROUP(gpio9),
	BCM6318_GROUP(gpio10),
	BCM6318_GROUP(gpio11),
	BCM6318_GROUP(gpio12),
	BCM6318_GROUP(gpio13),
	BCM6318_GROUP(gpio14),
	BCM6318_GROUP(gpio15),
	BCM6318_GROUP(gpio16),
	BCM6318_GROUP(gpio17),
	BCM6318_GROUP(gpio18),
	BCM6318_GROUP(gpio19),
	BCM6318_GROUP(gpio20),
	BCM6318_GROUP(gpio21),
	BCM6318_GROUP(gpio22),
	BCM6318_GROUP(gpio23),
	BCM6318_GROUP(gpio24),
	BCM6318_GROUP(gpio25),
	BCM6318_GROUP(gpio26),
	BCM6318_GROUP(gpio27),
	BCM6318_GROUP(gpio28),
	BCM6318_GROUP(gpio29),
	BCM6318_GROUP(gpio30),
	BCM6318_GROUP(gpio31),
	BCM6318_GROUP(gpio32),
	BCM6318_GROUP(gpio33),
	BCM6318_GROUP(gpio34),
	BCM6318_GROUP(gpio35),
	BCM6318_GROUP(gpio36),
	BCM6318_GROUP(gpio37),
	BCM6318_GROUP(gpio38),
	BCM6318_GROUP(gpio39),
	BCM6318_GROUP(gpio40),
	BCM6318_GROUP(gpio41),
	BCM6318_GROUP(gpio42),
	BCM6318_GROUP(gpio43),
	BCM6318_GROUP(gpio44),
	BCM6318_GROUP(gpio45),
	BCM6318_GROUP(gpio46),
	BCM6318_GROUP(gpio47),
	BCM6318_GROUP(gpio48),
	BCM6318_GROUP(gpio49),
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
अटल स्थिर अक्षर * स्थिर ephy0_spd_led_groups[] = अणु
	"gpio0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy1_spd_led_groups[] = अणु
	"gpio1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy2_spd_led_groups[] = अणु
	"gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy3_spd_led_groups[] = अणु
	"gpio3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy0_act_led_groups[] = अणु
	"gpio4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy1_act_led_groups[] = अणु
	"gpio5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy2_act_led_groups[] = अणु
	"gpio6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy3_act_led_groups[] = अणु
	"gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_data_groups[] = अणु
	"gpio6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_clk_groups[] = अणु
	"gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर inet_act_led_groups[] = अणु
	"gpio8",
पूर्ण;

अटल स्थिर अक्षर * स्थिर inet_fail_led_groups[] = अणु
	"gpio9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsl_led_groups[] = अणु
	"gpio10",
पूर्ण;

अटल स्थिर अक्षर * स्थिर post_fail_led_groups[] = अणु
	"gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wlan_wps_led_groups[] = अणु
	"gpio12",
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_pwron_groups[] = अणु
	"gpio13",
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_device_led_groups[] = अणु
	"gpio13",
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_active_groups[] = अणु
	"gpio40",
पूर्ण;

#घोषणा BCM6318_MODE_FUN(n)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.mode_val = 1,				\
	पूर्ण

#घोषणा BCM6318_MUX_FUN(n, mux)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.mux_val = mux,				\
	पूर्ण

अटल स्थिर काष्ठा bcm6318_function bcm6318_funcs[] = अणु
	BCM6318_MODE_FUN(led),
	BCM6318_MUX_FUN(ephy0_spd_led, 1),
	BCM6318_MUX_FUN(ephy1_spd_led, 1),
	BCM6318_MUX_FUN(ephy2_spd_led, 1),
	BCM6318_MUX_FUN(ephy3_spd_led, 1),
	BCM6318_MUX_FUN(ephy0_act_led, 1),
	BCM6318_MUX_FUN(ephy1_act_led, 1),
	BCM6318_MUX_FUN(ephy2_act_led, 1),
	BCM6318_MUX_FUN(ephy3_act_led, 1),
	BCM6318_MUX_FUN(serial_led_data, 3),
	BCM6318_MUX_FUN(serial_led_clk, 3),
	BCM6318_MUX_FUN(inet_act_led, 1),
	BCM6318_MUX_FUN(inet_fail_led, 1),
	BCM6318_MUX_FUN(dsl_led, 1),
	BCM6318_MUX_FUN(post_fail_led, 1),
	BCM6318_MUX_FUN(wlan_wps_led, 1),
	BCM6318_MUX_FUN(usb_pwron, 1),
	BCM6318_MUX_FUN(usb_device_led, 2),
	BCM6318_MUX_FUN(usb_active, 2),
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक bcm6318_mux_off(अचिन्हित पूर्णांक pin)
अणु
	वापस BCM6318_MUX_REG + (pin / 16) * 4;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bcm6318_pad_off(अचिन्हित पूर्णांक pin)
अणु
	वापस BCM6318_PAD_REG + (pin / 8) * 4;
पूर्ण

अटल पूर्णांक bcm6318_pinctrl_get_group_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6318_groups);
पूर्ण

अटल स्थिर अक्षर *bcm6318_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित group)
अणु
	वापस bcm6318_groups[group].name;
पूर्ण

अटल पूर्णांक bcm6318_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित group, स्थिर अचिन्हित **pins,
					  अचिन्हित *num_pins)
अणु
	*pins = bcm6318_groups[group].pins;
	*num_pins = bcm6318_groups[group].num_pins;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6318_pinctrl_get_func_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6318_funcs);
पूर्ण

अटल स्थिर अक्षर *bcm6318_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
						 अचिन्हित selector)
अणु
	वापस bcm6318_funcs[selector].name;
पूर्ण

अटल पूर्णांक bcm6318_pinctrl_get_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित selector,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	*groups = bcm6318_funcs[selector].groups;
	*num_groups = bcm6318_funcs[selector].num_groups;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bcm6318_rmw_mux(काष्ठा bcm63xx_pinctrl *pc, अचिन्हित pin,
				   अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक mux)
अणु
	अगर (pin < BCM63XX_BANK_GPIOS)
		regmap_update_bits(pc->regs, BCM6318_MODE_REG, BIT(pin),
				   mode ? BIT(pin) : 0);

	अगर (pin < BCM6318_NUM_MUX)
		regmap_update_bits(pc->regs,
				   bcm6318_mux_off(pin),
				   BCM6328_MUX_MASK << ((pin % 16) * 2),
				   mux << ((pin % 16) * 2));
पूर्ण

अटल अंतरभूत व्योम bcm6318_set_pad(काष्ठा bcm63xx_pinctrl *pc, अचिन्हित pin,
				   uपूर्णांक8_t val)
अणु
	regmap_update_bits(pc->regs, bcm6318_pad_off(pin),
			   BCM6328_PAD_MASK << ((pin % 8) * 4),
			   val << ((pin % 8) * 4));
पूर्ण

अटल पूर्णांक bcm6318_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित selector, अचिन्हित group)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा bcm6318_pingroup *pg = &bcm6318_groups[group];
	स्थिर काष्ठा bcm6318_function *f = &bcm6318_funcs[selector];

	bcm6318_rmw_mux(pc, pg->pins[0], f->mode_val, f->mux_val);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6318_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा pinctrl_gpio_range *range,
				       अचिन्हित offset)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);

	/* disable all functions using this pin */
	अगर (offset < 13) अणु
		/* GPIOs 0-12 use mux 0 as GPIO function */
		bcm6318_rmw_mux(pc, offset, 0, 0);
	पूर्ण अन्यथा अगर (offset < 42) अणु
		/* GPIOs 13-41 use mux 3 as GPIO function */
		bcm6318_rmw_mux(pc, offset, 0, 3);

		bcm6318_set_pad(pc, offset, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pinctrl_ops bcm6318_pctl_ops = अणु
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.get_group_name = bcm6318_pinctrl_get_group_name,
	.get_group_pins = bcm6318_pinctrl_get_group_pins,
	.get_groups_count = bcm6318_pinctrl_get_group_count,
पूर्ण;

अटल काष्ठा pinmux_ops bcm6318_pmx_ops = अणु
	.get_function_groups = bcm6318_pinctrl_get_groups,
	.get_function_name = bcm6318_pinctrl_get_func_name,
	.get_functions_count = bcm6318_pinctrl_get_func_count,
	.gpio_request_enable = bcm6318_gpio_request_enable,
	.set_mux = bcm6318_pinctrl_set_mux,
	.strict = true,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_pinctrl_soc bcm6318_soc = अणु
	.ngpios = BCM6318_NUM_GPIOS,
	.npins = ARRAY_SIZE(bcm6318_pins),
	.pctl_ops = &bcm6318_pctl_ops,
	.pins = bcm6318_pins,
	.pmx_ops = &bcm6318_pmx_ops,
पूर्ण;

अटल पूर्णांक bcm6318_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस bcm63xx_pinctrl_probe(pdev, &bcm6318_soc, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6318_pinctrl_match[] = अणु
	अणु .compatible = "brcm,bcm6318-pinctrl", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm6318_pinctrl_driver = अणु
	.probe = bcm6318_pinctrl_probe,
	.driver = अणु
		.name = "bcm6318-pinctrl",
		.of_match_table = bcm6318_pinctrl_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(bcm6318_pinctrl_driver);
