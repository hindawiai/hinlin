<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम BCM6362 GPIO unit (pinctrl + GPIO)
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

#घोषणा BCM6362_BANK_GPIOS	32
#घोषणा BCM6362_NUM_GPIOS	48
#घोषणा BCM6362_NUM_LEDS	24

#घोषणा BCM6362_LED_REG		0x10
#घोषणा BCM6362_MODE_REG	0x18
#घोषणा BCM6362_CTRL_REG	0x1c
#घोषणा BCM6362_BASEMODE_REG	0x38
#घोषणा  BASEMODE_न_अंकD		BIT(2)

क्रमागत bcm6362_pinctrl_reg अणु
	BCM6362_LEDCTRL,
	BCM6362_MODE,
	BCM6362_CTRL,
	BCM6362_BASEMODE,
पूर्ण;

काष्ठा bcm6362_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित * स्थिर pins;
	स्थिर अचिन्हित num_pins;
पूर्ण;

काष्ठा bcm6362_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित num_groups;

	क्रमागत bcm6362_pinctrl_reg reg;
	uपूर्णांक32_t basemode_mask;
पूर्ण;

#घोषणा BCM6362_PIN(a, b, mask)			\
	अणु					\
		.number = a,			\
		.name = b,			\
		.drv_data = (व्योम *)(mask),	\
	पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc bcm6362_pins[] = अणु
	PINCTRL_PIN(0, "gpio0"),
	PINCTRL_PIN(1, "gpio1"),
	PINCTRL_PIN(2, "gpio2"),
	PINCTRL_PIN(3, "gpio3"),
	PINCTRL_PIN(4, "gpio4"),
	PINCTRL_PIN(5, "gpio5"),
	PINCTRL_PIN(6, "gpio6"),
	PINCTRL_PIN(7, "gpio7"),
	BCM6362_PIN(8, "gpio8", BASEMODE_न_अंकD),
	PINCTRL_PIN(9, "gpio9"),
	PINCTRL_PIN(10, "gpio10"),
	PINCTRL_PIN(11, "gpio11"),
	BCM6362_PIN(12, "gpio12", BASEMODE_न_अंकD),
	BCM6362_PIN(13, "gpio13", BASEMODE_न_अंकD),
	BCM6362_PIN(14, "gpio14", BASEMODE_न_अंकD),
	BCM6362_PIN(15, "gpio15", BASEMODE_न_अंकD),
	BCM6362_PIN(16, "gpio16", BASEMODE_न_अंकD),
	BCM6362_PIN(17, "gpio17", BASEMODE_न_अंकD),
	BCM6362_PIN(18, "gpio18", BASEMODE_न_अंकD),
	BCM6362_PIN(19, "gpio19", BASEMODE_न_अंकD),
	BCM6362_PIN(20, "gpio20", BASEMODE_न_अंकD),
	BCM6362_PIN(21, "gpio21", BASEMODE_न_अंकD),
	BCM6362_PIN(22, "gpio22", BASEMODE_न_अंकD),
	BCM6362_PIN(23, "gpio23", BASEMODE_न_अंकD),
	PINCTRL_PIN(24, "gpio24"),
	PINCTRL_PIN(25, "gpio25"),
	PINCTRL_PIN(26, "gpio26"),
	BCM6362_PIN(27, "gpio27", BASEMODE_न_अंकD),
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

अटल अचिन्हित nand_grp_pins[] = अणु
	8, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 27,
पूर्ण;

#घोषणा BCM6362_GROUP(n)				\
	अणु						\
		.name = #n,				\
		.pins = n##_pins,			\
		.num_pins = ARRAY_SIZE(n##_pins),	\
	पूर्ण

अटल काष्ठा bcm6362_pingroup bcm6362_groups[] = अणु
	BCM6362_GROUP(gpio0),
	BCM6362_GROUP(gpio1),
	BCM6362_GROUP(gpio2),
	BCM6362_GROUP(gpio3),
	BCM6362_GROUP(gpio4),
	BCM6362_GROUP(gpio5),
	BCM6362_GROUP(gpio6),
	BCM6362_GROUP(gpio7),
	BCM6362_GROUP(gpio8),
	BCM6362_GROUP(gpio9),
	BCM6362_GROUP(gpio10),
	BCM6362_GROUP(gpio11),
	BCM6362_GROUP(gpio12),
	BCM6362_GROUP(gpio13),
	BCM6362_GROUP(gpio14),
	BCM6362_GROUP(gpio15),
	BCM6362_GROUP(gpio16),
	BCM6362_GROUP(gpio17),
	BCM6362_GROUP(gpio18),
	BCM6362_GROUP(gpio19),
	BCM6362_GROUP(gpio20),
	BCM6362_GROUP(gpio21),
	BCM6362_GROUP(gpio22),
	BCM6362_GROUP(gpio23),
	BCM6362_GROUP(gpio24),
	BCM6362_GROUP(gpio25),
	BCM6362_GROUP(gpio26),
	BCM6362_GROUP(gpio27),
	BCM6362_GROUP(gpio28),
	BCM6362_GROUP(gpio29),
	BCM6362_GROUP(gpio30),
	BCM6362_GROUP(gpio31),
	BCM6362_GROUP(gpio32),
	BCM6362_GROUP(gpio33),
	BCM6362_GROUP(gpio34),
	BCM6362_GROUP(gpio35),
	BCM6362_GROUP(gpio36),
	BCM6362_GROUP(gpio37),
	BCM6362_GROUP(gpio38),
	BCM6362_GROUP(gpio39),
	BCM6362_GROUP(gpio40),
	BCM6362_GROUP(gpio41),
	BCM6362_GROUP(gpio42),
	BCM6362_GROUP(gpio43),
	BCM6362_GROUP(gpio44),
	BCM6362_GROUP(gpio45),
	BCM6362_GROUP(gpio46),
	BCM6362_GROUP(gpio47),
	BCM6362_GROUP(nand_grp),
पूर्ण;

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

अटल स्थिर अक्षर * स्थिर usb_device_led_groups[] = अणु
	"gpio0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sys_irq_groups[] = अणु
	"gpio1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_clk_groups[] = अणु
	"gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर serial_led_data_groups[] = अणु
	"gpio3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर robosw_led_data_groups[] = अणु
	"gpio4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर robosw_led_clk_groups[] = अणु
	"gpio5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर robosw_led0_groups[] = अणु
	"gpio6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर robosw_led1_groups[] = अणु
	"gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर inet_led_groups[] = अणु
	"gpio8",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_cs2_groups[] = अणु
	"gpio9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_cs3_groups[] = अणु
	"gpio10",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ntr_pulse_groups[] = अणु
	"gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_scts_groups[] = अणु
	"gpio12",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_srts_groups[] = अणु
	"gpio13",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_sdin_groups[] = अणु
	"gpio14",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_sकरोut_groups[] = अणु
	"gpio15",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adsl_spi_miso_groups[] = अणु
	"gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adsl_spi_mosi_groups[] = अणु
	"gpio17",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adsl_spi_clk_groups[] = अणु
	"gpio18",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adsl_spi_cs_groups[] = अणु
	"gpio19",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy0_led_groups[] = अणु
	"gpio20",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy1_led_groups[] = अणु
	"gpio21",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy2_led_groups[] = अणु
	"gpio22",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ephy3_led_groups[] = अणु
	"gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ext_irq0_groups[] = अणु
	"gpio24",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ext_irq1_groups[] = अणु
	"gpio25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ext_irq2_groups[] = अणु
	"gpio26",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ext_irq3_groups[] = अणु
	"gpio27",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wअगरi_groups[] = अणु
	"gpio32",
	"gpio33",
	"gpio34",
	"gpio35",
	"gpio36",
	"gpio37",
	"gpio38",
	"gpio39",
	"gpio40",
	"gpio41",
	"gpio42",
	"gpio43",
	"gpio44",
	"gpio45",
	"gpio46",
	"gpio47",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nand_groups[] = अणु
	"nand_grp",
पूर्ण;

#घोषणा BCM6362_LED_FUN(n)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.reg = BCM6362_LEDCTRL,			\
	पूर्ण

#घोषणा BCM6362_MODE_FUN(n)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.reg = BCM6362_MODE,			\
	पूर्ण

#घोषणा BCM6362_CTRL_FUN(n)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.reg = BCM6362_CTRL,			\
	पूर्ण

#घोषणा BCM6362_BASEMODE_FUN(n, mask)			\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.num_groups = ARRAY_SIZE(n##_groups),	\
		.reg = BCM6362_BASEMODE,		\
		.basemode_mask = (mask),		\
	पूर्ण

अटल स्थिर काष्ठा bcm6362_function bcm6362_funcs[] = अणु
	BCM6362_LED_FUN(led),
	BCM6362_MODE_FUN(usb_device_led),
	BCM6362_MODE_FUN(sys_irq),
	BCM6362_MODE_FUN(serial_led_clk),
	BCM6362_MODE_FUN(serial_led_data),
	BCM6362_MODE_FUN(robosw_led_data),
	BCM6362_MODE_FUN(robosw_led_clk),
	BCM6362_MODE_FUN(robosw_led0),
	BCM6362_MODE_FUN(robosw_led1),
	BCM6362_MODE_FUN(inet_led),
	BCM6362_MODE_FUN(spi_cs2),
	BCM6362_MODE_FUN(spi_cs3),
	BCM6362_MODE_FUN(ntr_pulse),
	BCM6362_MODE_FUN(uart1_scts),
	BCM6362_MODE_FUN(uart1_srts),
	BCM6362_MODE_FUN(uart1_sdin),
	BCM6362_MODE_FUN(uart1_sकरोut),
	BCM6362_MODE_FUN(adsl_spi_miso),
	BCM6362_MODE_FUN(adsl_spi_mosi),
	BCM6362_MODE_FUN(adsl_spi_clk),
	BCM6362_MODE_FUN(adsl_spi_cs),
	BCM6362_MODE_FUN(ephy0_led),
	BCM6362_MODE_FUN(ephy1_led),
	BCM6362_MODE_FUN(ephy2_led),
	BCM6362_MODE_FUN(ephy3_led),
	BCM6362_MODE_FUN(ext_irq0),
	BCM6362_MODE_FUN(ext_irq1),
	BCM6362_MODE_FUN(ext_irq2),
	BCM6362_MODE_FUN(ext_irq3),
	BCM6362_CTRL_FUN(wअगरi),
	BCM6362_BASEMODE_FUN(nand, BASEMODE_न_अंकD),
पूर्ण;

अटल पूर्णांक bcm6362_pinctrl_get_group_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6362_groups);
पूर्ण

अटल स्थिर अक्षर *bcm6362_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित group)
अणु
	वापस bcm6362_groups[group].name;
पूर्ण

अटल पूर्णांक bcm6362_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित group, स्थिर अचिन्हित **pins,
					  अचिन्हित *num_pins)
अणु
	*pins = bcm6362_groups[group].pins;
	*num_pins = bcm6362_groups[group].num_pins;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6362_pinctrl_get_func_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(bcm6362_funcs);
पूर्ण

अटल स्थिर अक्षर *bcm6362_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
						 अचिन्हित selector)
अणु
	वापस bcm6362_funcs[selector].name;
पूर्ण

अटल पूर्णांक bcm6362_pinctrl_get_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित selector,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	*groups = bcm6362_funcs[selector].groups;
	*num_groups = bcm6362_funcs[selector].num_groups;

	वापस 0;
पूर्ण

अटल व्योम bcm6362_set_gpio(काष्ठा bcm63xx_pinctrl *pc, अचिन्हित pin)
अणु
	स्थिर काष्ठा pinctrl_pin_desc *desc = &bcm6362_pins[pin];
	अचिन्हित पूर्णांक basemode = (uपूर्णांकptr_t)desc->drv_data;
	अचिन्हित पूर्णांक mask = bcm63xx_bank_pin(pin);

	अगर (basemode)
		regmap_update_bits(pc->regs, BCM6362_BASEMODE_REG, basemode, 0);

	अगर (pin < BCM63XX_BANK_GPIOS) अणु
		/* base mode 0 => gpio 1 => mux function */
		regmap_update_bits(pc->regs, BCM6362_MODE_REG, mask, 0);

		/* pins 0-23 might be muxed to led */
		अगर (pin < BCM6362_NUM_LEDS)
			regmap_update_bits(pc->regs, BCM6362_LED_REG, mask, 0);
	पूर्ण अन्यथा अणु
		/* ctrl reg 0 => wअगरi function 1 => gpio */
		regmap_update_bits(pc->regs, BCM6362_CTRL_REG, mask, mask);
	पूर्ण
पूर्ण

अटल पूर्णांक bcm6362_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित selector, अचिन्हित group)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा bcm6362_pingroup *pg = &bcm6362_groups[group];
	स्थिर काष्ठा bcm6362_function *f = &bcm6362_funcs[selector];
	अचिन्हित i;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक val, mask;

	क्रम (i = 0; i < pg->num_pins; i++)
		bcm6362_set_gpio(pc, pg->pins[i]);

	चयन (f->reg) अणु
	हाल BCM6362_LEDCTRL:
		reg = BCM6362_LED_REG;
		mask = BIT(pg->pins[0]);
		val = BIT(pg->pins[0]);
		अवरोध;
	हाल BCM6362_MODE:
		reg = BCM6362_MODE_REG;
		mask = BIT(pg->pins[0]);
		val = BIT(pg->pins[0]);
		अवरोध;
	हाल BCM6362_CTRL:
		reg = BCM6362_CTRL_REG;
		mask = BIT(pg->pins[0]);
		val = 0;
		अवरोध;
	हाल BCM6362_BASEMODE:
		reg = BCM6362_BASEMODE_REG;
		mask = f->basemode_mask;
		val = f->basemode_mask;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(pc->regs, reg, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6362_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा pinctrl_gpio_range *range,
				       अचिन्हित offset)
अणु
	काष्ठा bcm63xx_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);

	/* disable all functions using this pin */
	bcm6362_set_gpio(pc, offset);

	वापस 0;
पूर्ण

अटल काष्ठा pinctrl_ops bcm6362_pctl_ops = अणु
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.get_group_name = bcm6362_pinctrl_get_group_name,
	.get_group_pins = bcm6362_pinctrl_get_group_pins,
	.get_groups_count = bcm6362_pinctrl_get_group_count,
पूर्ण;

अटल काष्ठा pinmux_ops bcm6362_pmx_ops = अणु
	.get_function_groups = bcm6362_pinctrl_get_groups,
	.get_function_name = bcm6362_pinctrl_get_func_name,
	.get_functions_count = bcm6362_pinctrl_get_func_count,
	.gpio_request_enable = bcm6362_gpio_request_enable,
	.set_mux = bcm6362_pinctrl_set_mux,
	.strict = true,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_pinctrl_soc bcm6362_soc = अणु
	.ngpios = BCM6362_NUM_GPIOS,
	.npins = ARRAY_SIZE(bcm6362_pins),
	.pctl_ops = &bcm6362_pctl_ops,
	.pins = bcm6362_pins,
	.pmx_ops = &bcm6362_pmx_ops,
पूर्ण;

अटल पूर्णांक bcm6362_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस bcm63xx_pinctrl_probe(pdev, &bcm6362_soc, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6362_pinctrl_match[] = अणु
	अणु .compatible = "brcm,bcm6362-pinctrl", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm6362_pinctrl_driver = अणु
	.probe = bcm6362_pinctrl_probe,
	.driver = अणु
		.name = "bcm6362-pinctrl",
		.of_match_table = bcm6362_pinctrl_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(bcm6362_pinctrl_driver);
