<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Oxक्रमd Semiconductor OXNAS SoC Family pinctrl driver
 *
 * Copyright (C) 2016 Neil Armstrong <narmstrong@baylibre.com>
 *
 * Based on pinctrl-pic32.c
 * Joshua Henderson, <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश "pinctrl-utils.h"

#घोषणा PINS_PER_BANK		32

#घोषणा GPIO_BANK_START(bank)		((bank) * PINS_PER_BANK)

/* OX810 Regmap Offsets */
#घोषणा PINMUX_810_PRIMARY_SEL0		0x0c
#घोषणा PINMUX_810_SECONDARY_SEL0	0x14
#घोषणा PINMUX_810_TERTIARY_SEL0	0x8c
#घोषणा PINMUX_810_PRIMARY_SEL1		0x10
#घोषणा PINMUX_810_SECONDARY_SEL1	0x18
#घोषणा PINMUX_810_TERTIARY_SEL1	0x90
#घोषणा PINMUX_810_PULLUP_CTRL0		0xac
#घोषणा PINMUX_810_PULLUP_CTRL1		0xb0

/* OX820 Regmap Offsets */
#घोषणा PINMUX_820_BANK_OFFSET		0x100000
#घोषणा PINMUX_820_SECONDARY_SEL	0x14
#घोषणा PINMUX_820_TERTIARY_SEL		0x8c
#घोषणा PINMUX_820_QUATERNARY_SEL	0x94
#घोषणा PINMUX_820_DEBUG_SEL		0x9c
#घोषणा PINMUX_820_ALTERNATIVE_SEL	0xa4
#घोषणा PINMUX_820_PULLUP_CTRL		0xac

/* GPIO Registers */
#घोषणा INPUT_VALUE	0x00
#घोषणा OUTPUT_EN	0x04
#घोषणा IRQ_PENDING	0x0c
#घोषणा OUTPUT_SET	0x14
#घोषणा OUTPUT_CLEAR	0x18
#घोषणा OUTPUT_EN_SET	0x1c
#घोषणा OUTPUT_EN_CLEAR	0x20
#घोषणा RE_IRQ_ENABLE	0x28
#घोषणा FE_IRQ_ENABLE	0x2c

काष्ठा oxnas_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
पूर्ण;

काष्ठा oxnas_pin_group अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक pin;
	अचिन्हित पूर्णांक bank;
	काष्ठा oxnas_desc_function *functions;
पूर्ण;

काष्ठा oxnas_desc_function अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक fct;
पूर्ण;

काष्ठा oxnas_gpio_bank अणु
	व्योम __iomem *reg_base;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा irq_chip irq_chip;
	अचिन्हित पूर्णांक id;
पूर्ण;

काष्ठा oxnas_pinctrl अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctldev;
	स्थिर काष्ठा oxnas_function *functions;
	अचिन्हित पूर्णांक nfunctions;
	स्थिर काष्ठा oxnas_pin_group *groups;
	अचिन्हित पूर्णांक ngroups;
	काष्ठा oxnas_gpio_bank *gpio_banks;
	अचिन्हित पूर्णांक nbanks;
पूर्ण;

काष्ठा oxnas_pinctrl_data अणु
	काष्ठा pinctrl_desc *desc;
	काष्ठा oxnas_pinctrl *pctl;
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc oxnas_ox810se_pins[] = अणु
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
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc oxnas_ox820_pins[] = अणु
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

अटल स्थिर अक्षर * स्थिर oxnas_ox810se_fct0_group[] = अणु
	"gpio0",  "gpio1",  "gpio2",  "gpio3",
	"gpio4",  "gpio5",  "gpio6",  "gpio7",
	"gpio8",  "gpio9",  "gpio10", "gpio11",
	"gpio12", "gpio13", "gpio14", "gpio15",
	"gpio16", "gpio17", "gpio18", "gpio19",
	"gpio20", "gpio21", "gpio22", "gpio23",
	"gpio24", "gpio25", "gpio26", "gpio27",
	"gpio28", "gpio29", "gpio30", "gpio31",
	"gpio32", "gpio33", "gpio34"
पूर्ण;

अटल स्थिर अक्षर * स्थिर oxnas_ox810se_fct3_group[] = अणु
	"gpio0",  "gpio1",  "gpio2",  "gpio3",
	"gpio4",  "gpio5",  "gpio6",  "gpio7",
	"gpio8",  "gpio9",
	"gpio20",
	"gpio22", "gpio23", "gpio24", "gpio25",
	"gpio26", "gpio27", "gpio28", "gpio29",
	"gpio30", "gpio31", "gpio32", "gpio33",
	"gpio34"
पूर्ण;

अटल स्थिर अक्षर * स्थिर oxnas_ox820_fct0_group[] = अणु
	"gpio0",  "gpio1",  "gpio2",  "gpio3",
	"gpio4",  "gpio5",  "gpio6",  "gpio7",
	"gpio8",  "gpio9",  "gpio10", "gpio11",
	"gpio12", "gpio13", "gpio14", "gpio15",
	"gpio16", "gpio17", "gpio18", "gpio19",
	"gpio20", "gpio21", "gpio22", "gpio23",
	"gpio24", "gpio25", "gpio26", "gpio27",
	"gpio28", "gpio29", "gpio30", "gpio31",
	"gpio32", "gpio33", "gpio34", "gpio35",
	"gpio36", "gpio37", "gpio38", "gpio39",
	"gpio40", "gpio41", "gpio42", "gpio43",
	"gpio44", "gpio45", "gpio46", "gpio47",
	"gpio48", "gpio49"
पूर्ण;

अटल स्थिर अक्षर * स्थिर oxnas_ox820_fct1_group[] = अणु
	"gpio3", "gpio4",
	"gpio12", "gpio13", "gpio14", "gpio15",
	"gpio16", "gpio17", "gpio18", "gpio19",
	"gpio20", "gpio21", "gpio22", "gpio23",
	"gpio24"
पूर्ण;

अटल स्थिर अक्षर * स्थिर oxnas_ox820_fct4_group[] = अणु
	"gpio5", "gpio6", "gpio7", "gpio8",
	"gpio24", "gpio25", "gpio26", "gpio27",
	"gpio40", "gpio41", "gpio42", "gpio43"
पूर्ण;

अटल स्थिर अक्षर * स्थिर oxnas_ox820_fct5_group[] = अणु
	"gpio28", "gpio29", "gpio30", "gpio31"
पूर्ण;

#घोषणा FUNCTION(_name, _gr)					\
	अणु							\
		.name = #_name,					\
		.groups = oxnas_##_gr##_group,			\
		.ngroups = ARRAY_SIZE(oxnas_##_gr##_group),	\
	पूर्ण

अटल स्थिर काष्ठा oxnas_function oxnas_ox810se_functions[] = अणु
	FUNCTION(gpio, ox810se_fct0),
	FUNCTION(fct3, ox810se_fct3),
पूर्ण;

अटल स्थिर काष्ठा oxnas_function oxnas_ox820_functions[] = अणु
	FUNCTION(gpio, ox820_fct0),
	FUNCTION(fct1, ox820_fct1),
	FUNCTION(fct4, ox820_fct4),
	FUNCTION(fct5, ox820_fct5),
पूर्ण;

#घोषणा OXNAS_PINCTRL_GROUP(_pin, _name, ...)				\
	अणु								\
		.name = #_name,						\
		.pin = _pin,						\
		.bank = _pin / PINS_PER_BANK,				\
		.functions = (काष्ठा oxnas_desc_function[])अणु		\
			__VA_ARGS__, अणु पूर्ण पूर्ण,				\
	पूर्ण

#घोषणा OXNAS_PINCTRL_FUNCTION(_name, _fct)		\
	अणु						\
		.name = #_name,				\
		.fct = _fct,				\
	पूर्ण

अटल स्थिर काष्ठा oxnas_pin_group oxnas_ox810se_groups[] = अणु
	OXNAS_PINCTRL_GROUP(0, gpio0,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(1, gpio1,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(2, gpio2,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(3, gpio3,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(4, gpio4,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(5, gpio5,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(6, gpio6,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(7, gpio7,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(8, gpio8,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(9, gpio9,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(10, gpio10,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(11, gpio11,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(12, gpio12,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(13, gpio13,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(14, gpio14,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(15, gpio15,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(16, gpio16,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(17, gpio17,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(18, gpio18,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(19, gpio19,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(20, gpio20,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(21, gpio21,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(22, gpio22,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(23, gpio23,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(24, gpio24,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(25, gpio25,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(26, gpio26,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(27, gpio27,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(28, gpio28,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(29, gpio29,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(30, gpio30,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(31, gpio31,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(32, gpio32,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(33, gpio33,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
	OXNAS_PINCTRL_GROUP(34, gpio34,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct3, 3)),
पूर्ण;

अटल स्थिर काष्ठा oxnas_pin_group oxnas_ox820_groups[] = अणु
	OXNAS_PINCTRL_GROUP(0, gpio0,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(1, gpio1,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(2, gpio2,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(3, gpio3,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(4, gpio4,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(5, gpio5,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(6, gpio6,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(7, gpio7,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(8, gpio8,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(9, gpio9,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(10, gpio10,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(11, gpio11,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(12, gpio12,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(13, gpio13,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(14, gpio14,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(15, gpio15,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(16, gpio16,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(17, gpio17,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(18, gpio18,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(19, gpio19,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(20, gpio20,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(21, gpio21,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(22, gpio22,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(23, gpio23,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1)),
	OXNAS_PINCTRL_GROUP(24, gpio24,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct1, 1),
			OXNAS_PINCTRL_FUNCTION(fct4, 5)),
	OXNAS_PINCTRL_GROUP(25, gpio25,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(26, gpio26,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(27, gpio27,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(28, gpio28,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct5, 5)),
	OXNAS_PINCTRL_GROUP(29, gpio29,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct5, 5)),
	OXNAS_PINCTRL_GROUP(30, gpio30,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct5, 5)),
	OXNAS_PINCTRL_GROUP(31, gpio31,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct5, 5)),
	OXNAS_PINCTRL_GROUP(32, gpio32,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(33, gpio33,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(34, gpio34,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(35, gpio35,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(36, gpio36,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(37, gpio37,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(38, gpio38,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(39, gpio39,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(40, gpio40,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(41, gpio41,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(42, gpio42,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(43, gpio43,
			OXNAS_PINCTRL_FUNCTION(gpio, 0),
			OXNAS_PINCTRL_FUNCTION(fct4, 4)),
	OXNAS_PINCTRL_GROUP(44, gpio44,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(45, gpio45,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(46, gpio46,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(47, gpio47,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(48, gpio48,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
	OXNAS_PINCTRL_GROUP(49, gpio49,
			OXNAS_PINCTRL_FUNCTION(gpio, 0)),
पूर्ण;

अटल अंतरभूत काष्ठा oxnas_gpio_bank *pctl_to_bank(काष्ठा oxnas_pinctrl *pctl,
						   अचिन्हित पूर्णांक pin)
अणु
	वापस &pctl->gpio_banks[pin / PINS_PER_BANK];
पूर्ण

अटल पूर्णांक oxnas_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->ngroups;
पूर्ण

अटल स्थिर अक्षर *oxnas_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित पूर्णांक group)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->groups[group].name;
पूर्ण

अटल पूर्णांक oxnas_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक group,
					स्थिर अचिन्हित पूर्णांक **pins,
					अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*pins = &pctl->groups[group].pin;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops oxnas_pinctrl_ops = अणु
	.get_groups_count = oxnas_pinctrl_get_groups_count,
	.get_group_name = oxnas_pinctrl_get_group_name,
	.get_group_pins = oxnas_pinctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक oxnas_pinmux_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->nfunctions;
पूर्ण

अटल स्थिर अक्षर *
oxnas_pinmux_get_function_name(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक func)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->functions[func].name;
पूर्ण

अटल पूर्णांक oxnas_pinmux_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित पूर्णांक func,
					    स्थिर अक्षर * स्थिर **groups,
					    अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctl->functions[func].groups;
	*num_groups = pctl->functions[func].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_ox810se_pinmux_enable(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक group)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा oxnas_pin_group *pg = &pctl->groups[group];
	स्थिर काष्ठा oxnas_function *pf = &pctl->functions[func];
	स्थिर अक्षर *fname = pf->name;
	काष्ठा oxnas_desc_function *functions = pg->functions;
	u32 mask = BIT(pg->pin);

	जबतक (functions->name) अणु
		अगर (!म_भेद(functions->name, fname)) अणु
			dev_dbg(pctl->dev,
				"setting function %s bank %d pin %d fct %d mask %x\n",
				fname, pg->bank, pg->pin,
				functions->fct, mask);

			regmap_ग_लिखो_bits(pctl->regmap,
					  (pg->bank ?
						PINMUX_810_PRIMARY_SEL1 :
						PINMUX_810_PRIMARY_SEL0),
					  mask,
					  (functions->fct == 1 ?
						mask : 0));
			regmap_ग_लिखो_bits(pctl->regmap,
					  (pg->bank ?
						PINMUX_810_SECONDARY_SEL1 :
						PINMUX_810_SECONDARY_SEL0),
					  mask,
					  (functions->fct == 2 ?
						mask : 0));
			regmap_ग_लिखो_bits(pctl->regmap,
					  (pg->bank ?
						PINMUX_810_TERTIARY_SEL1 :
						PINMUX_810_TERTIARY_SEL0),
					  mask,
					  (functions->fct == 3 ?
						mask : 0));

			वापस 0;
		पूर्ण

		functions++;
	पूर्ण

	dev_err(pctl->dev, "cannot mux pin %u to function %u\n", group, func);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक oxnas_ox820_pinmux_enable(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक group)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा oxnas_pin_group *pg = &pctl->groups[group];
	स्थिर काष्ठा oxnas_function *pf = &pctl->functions[func];
	स्थिर अक्षर *fname = pf->name;
	काष्ठा oxnas_desc_function *functions = pg->functions;
	अचिन्हित पूर्णांक offset = (pg->bank ? PINMUX_820_BANK_OFFSET : 0);
	u32 mask = BIT(pg->pin);

	जबतक (functions->name) अणु
		अगर (!म_भेद(functions->name, fname)) अणु
			dev_dbg(pctl->dev,
				"setting function %s bank %d pin %d fct %d mask %x\n",
				fname, pg->bank, pg->pin,
				functions->fct, mask);

			regmap_ग_लिखो_bits(pctl->regmap,
					  offset + PINMUX_820_SECONDARY_SEL,
					  mask,
					  (functions->fct == 1 ?
						mask : 0));
			regmap_ग_लिखो_bits(pctl->regmap,
					  offset + PINMUX_820_TERTIARY_SEL,
					  mask,
					  (functions->fct == 2 ?
						mask : 0));
			regmap_ग_लिखो_bits(pctl->regmap,
					  offset + PINMUX_820_QUATERNARY_SEL,
					  mask,
					  (functions->fct == 3 ?
						mask : 0));
			regmap_ग_लिखो_bits(pctl->regmap,
					  offset + PINMUX_820_DEBUG_SEL,
					  mask,
					  (functions->fct == 4 ?
						mask : 0));
			regmap_ग_लिखो_bits(pctl->regmap,
					  offset + PINMUX_820_ALTERNATIVE_SEL,
					  mask,
					  (functions->fct == 5 ?
						mask : 0));

			वापस 0;
		पूर्ण

		functions++;
	पूर्ण

	dev_err(pctl->dev, "cannot mux pin %u to function %u\n", group, func);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक oxnas_ox810se_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
					     काष्ठा pinctrl_gpio_range *range,
					     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(range->gc);
	u32 mask = BIT(offset - bank->gpio_chip.base);

	dev_dbg(pctl->dev, "requesting gpio %d in bank %d (id %d) with mask 0x%x\n",
		offset, bank->gpio_chip.base, bank->id, mask);

	regmap_ग_लिखो_bits(pctl->regmap,
			  (bank->id ?
				PINMUX_810_PRIMARY_SEL1 :
				PINMUX_810_PRIMARY_SEL0),
			  mask, 0);
	regmap_ग_लिखो_bits(pctl->regmap,
			  (bank->id ?
				PINMUX_810_SECONDARY_SEL1 :
				PINMUX_810_SECONDARY_SEL0),
			  mask, 0);
	regmap_ग_लिखो_bits(pctl->regmap,
			  (bank->id ?
				PINMUX_810_TERTIARY_SEL1 :
				PINMUX_810_TERTIARY_SEL0),
			  mask, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_ox820_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
					   काष्ठा pinctrl_gpio_range *range,
					   अचिन्हित पूर्णांक offset)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(range->gc);
	अचिन्हित पूर्णांक bank_offset = (bank->id ? PINMUX_820_BANK_OFFSET : 0);
	u32 mask = BIT(offset - bank->gpio_chip.base);

	dev_dbg(pctl->dev, "requesting gpio %d in bank %d (id %d) with mask 0x%x\n",
		offset, bank->gpio_chip.base, bank->id, mask);

	regmap_ग_लिखो_bits(pctl->regmap,
			  bank_offset + PINMUX_820_SECONDARY_SEL,
			  mask, 0);
	regmap_ग_लिखो_bits(pctl->regmap,
			  bank_offset + PINMUX_820_TERTIARY_SEL,
			  mask, 0);
	regmap_ग_लिखो_bits(pctl->regmap,
			  bank_offset + PINMUX_820_QUATERNARY_SEL,
			  mask, 0);
	regmap_ग_लिखो_bits(pctl->regmap,
			  bank_offset + PINMUX_820_DEBUG_SEL,
			  mask, 0);
	regmap_ग_लिखो_bits(pctl->regmap,
			  bank_offset + PINMUX_820_ALTERNATIVE_SEL,
			  mask, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_gpio_get_direction(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(chip);
	u32 mask = BIT(offset);

	अगर (पढ़ोl_relaxed(bank->reg_base + OUTPUT_EN) & mask)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक oxnas_gpio_direction_input(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(chip);
	u32 mask = BIT(offset);

	ग_लिखोl_relaxed(mask, bank->reg_base + OUTPUT_EN_CLEAR);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(chip);
	u32 mask = BIT(offset);

	वापस (पढ़ोl_relaxed(bank->reg_base + INPUT_VALUE) & mask) != 0;
पूर्ण

अटल व्योम oxnas_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			       पूर्णांक value)
अणु
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(chip);
	u32 mask = BIT(offset);

	अगर (value)
		ग_लिखोl_relaxed(mask, bank->reg_base + OUTPUT_SET);
	अन्यथा
		ग_लिखोl_relaxed(mask, bank->reg_base + OUTPUT_CLEAR);
पूर्ण

अटल पूर्णांक oxnas_gpio_direction_output(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(chip);
	u32 mask = BIT(offset);

	oxnas_gpio_set(chip, offset, value);
	ग_लिखोl_relaxed(mask, bank->reg_base + OUTPUT_EN_SET);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_gpio_range *range,
				    अचिन्हित पूर्णांक offset, bool input)
अणु
	काष्ठा gpio_chip *chip = range->gc;

	अगर (input)
		oxnas_gpio_direction_input(chip, offset);
	अन्यथा
		oxnas_gpio_direction_output(chip, offset, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops oxnas_ox810se_pinmux_ops = अणु
	.get_functions_count = oxnas_pinmux_get_functions_count,
	.get_function_name = oxnas_pinmux_get_function_name,
	.get_function_groups = oxnas_pinmux_get_function_groups,
	.set_mux = oxnas_ox810se_pinmux_enable,
	.gpio_request_enable = oxnas_ox810se_gpio_request_enable,
	.gpio_set_direction = oxnas_gpio_set_direction,
पूर्ण;

अटल स्थिर काष्ठा pinmux_ops oxnas_ox820_pinmux_ops = अणु
	.get_functions_count = oxnas_pinmux_get_functions_count,
	.get_function_name = oxnas_pinmux_get_function_name,
	.get_function_groups = oxnas_pinmux_get_function_groups,
	.set_mux = oxnas_ox820_pinmux_enable,
	.gpio_request_enable = oxnas_ox820_gpio_request_enable,
	.gpio_set_direction = oxnas_gpio_set_direction,
पूर्ण;

अटल पूर्णांक oxnas_ox810se_pinconf_get(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा oxnas_gpio_bank *bank = pctl_to_bank(pctl, pin);
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	u32 mask = BIT(pin - bank->gpio_chip.base);
	पूर्णांक ret;
	u32 arg;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		ret = regmap_पढ़ो(pctl->regmap,
				  (bank->id ?
					PINMUX_810_PULLUP_CTRL1 :
					PINMUX_810_PULLUP_CTRL0),
				  &arg);
		अगर (ret)
			वापस ret;

		arg = !!(arg & mask);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_ox820_pinconf_get(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा oxnas_gpio_bank *bank = pctl_to_bank(pctl, pin);
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	अचिन्हित पूर्णांक bank_offset = (bank->id ? PINMUX_820_BANK_OFFSET : 0);
	u32 mask = BIT(pin - bank->gpio_chip.base);
	पूर्णांक ret;
	u32 arg;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		ret = regmap_पढ़ो(pctl->regmap,
				  bank_offset + PINMUX_820_PULLUP_CTRL,
				  &arg);
		अगर (ret)
			वापस ret;

		arg = !!(arg & mask);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_ox810se_pinconf_set(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *configs,
				     अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा oxnas_gpio_bank *bank = pctl_to_bank(pctl, pin);
	अचिन्हित पूर्णांक param;
	अचिन्हित पूर्णांक i;
	u32 offset = pin - bank->gpio_chip.base;
	u32 mask = BIT(offset);

	dev_dbg(pctl->dev, "setting pin %d bank %d mask 0x%x\n",
		pin, bank->gpio_chip.base, mask);

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			dev_dbg(pctl->dev, "   pullup\n");
			regmap_ग_लिखो_bits(pctl->regmap,
					  (bank->id ?
						PINMUX_810_PULLUP_CTRL1 :
						PINMUX_810_PULLUP_CTRL0),
					  mask, mask);
			अवरोध;
		शेष:
			dev_err(pctl->dev, "Property %u not supported\n",
				param);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_ox820_pinconf_set(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *configs,
				   अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा oxnas_gpio_bank *bank = pctl_to_bank(pctl, pin);
	अचिन्हित पूर्णांक bank_offset = (bank->id ? PINMUX_820_BANK_OFFSET : 0);
	अचिन्हित पूर्णांक param;
	अचिन्हित पूर्णांक i;
	u32 offset = pin - bank->gpio_chip.base;
	u32 mask = BIT(offset);

	dev_dbg(pctl->dev, "setting pin %d bank %d mask 0x%x\n",
		pin, bank->gpio_chip.base, mask);

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			dev_dbg(pctl->dev, "   pullup\n");
			regmap_ग_लिखो_bits(pctl->regmap,
					  bank_offset + PINMUX_820_PULLUP_CTRL,
					  mask, mask);
			अवरोध;
		शेष:
			dev_err(pctl->dev, "Property %u not supported\n",
				param);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops oxnas_ox810se_pinconf_ops = अणु
	.pin_config_get = oxnas_ox810se_pinconf_get,
	.pin_config_set = oxnas_ox810se_pinconf_set,
	.is_generic = true,
पूर्ण;

अटल स्थिर काष्ठा pinconf_ops oxnas_ox820_pinconf_ops = अणु
	.pin_config_get = oxnas_ox820_pinconf_get,
	.pin_config_set = oxnas_ox820_pinconf_set,
	.is_generic = true,
पूर्ण;

अटल व्योम oxnas_gpio_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(chip);
	u32 mask = BIT(data->hwirq);

	ग_लिखोl(mask, bank->reg_base + IRQ_PENDING);
पूर्ण

अटल व्योम oxnas_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक type = irqd_get_trigger_type(data);
	u32 mask = BIT(data->hwirq);

	अगर (type & IRQ_TYPE_EDGE_RISING)
		ग_लिखोl(पढ़ोl(bank->reg_base + RE_IRQ_ENABLE) & ~mask,
		       bank->reg_base + RE_IRQ_ENABLE);

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		ग_लिखोl(पढ़ोl(bank->reg_base + FE_IRQ_ENABLE) & ~mask,
		       bank->reg_base + FE_IRQ_ENABLE);
पूर्ण

अटल व्योम oxnas_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक type = irqd_get_trigger_type(data);
	u32 mask = BIT(data->hwirq);

	अगर (type & IRQ_TYPE_EDGE_RISING)
		ग_लिखोl(पढ़ोl(bank->reg_base + RE_IRQ_ENABLE) | mask,
		       bank->reg_base + RE_IRQ_ENABLE);

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		ग_लिखोl(पढ़ोl(bank->reg_base + FE_IRQ_ENABLE) | mask,
		       bank->reg_base + FE_IRQ_ENABLE);
पूर्ण

अटल अचिन्हित पूर्णांक oxnas_gpio_irq_startup(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);

	oxnas_gpio_direction_input(chip, data->hwirq);
	oxnas_gpio_irq_unmask(data);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	अगर ((type & (IRQ_TYPE_EDGE_RISING|IRQ_TYPE_EDGE_FALLING)) == 0)
		वापस -EINVAL;

	irq_set_handler_locked(data, handle_edge_irq);

	वापस 0;
पूर्ण

अटल व्योम oxnas_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा oxnas_gpio_bank *bank = gpiochip_get_data(gc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ stat;
	अचिन्हित पूर्णांक pin;

	chained_irq_enter(chip, desc);

	stat = पढ़ोl(bank->reg_base + IRQ_PENDING);

	क्रम_each_set_bit(pin, &stat, BITS_PER_LONG)
		generic_handle_irq(irq_linear_revmap(gc->irq.करोमुख्य, pin));

	chained_irq_निकास(chip, desc);
पूर्ण

#घोषणा GPIO_BANK(_bank)						\
	अणु								\
		.gpio_chip = अणु						\
			.label = "GPIO" #_bank,				\
			.request = gpiochip_generic_request,		\
			.मुक्त = gpiochip_generic_मुक्त,			\
			.get_direction = oxnas_gpio_get_direction,	\
			.direction_input = oxnas_gpio_direction_input,	\
			.direction_output = oxnas_gpio_direction_output, \
			.get = oxnas_gpio_get,				\
			.set = oxnas_gpio_set,				\
			.ngpio = PINS_PER_BANK,				\
			.base = GPIO_BANK_START(_bank),			\
			.owner = THIS_MODULE,				\
			.can_sleep = 0,					\
		पूर्ण,							\
		.irq_chip = अणु						\
			.name = "GPIO" #_bank,				\
			.irq_startup = oxnas_gpio_irq_startup,	\
			.irq_ack = oxnas_gpio_irq_ack,		\
			.irq_mask = oxnas_gpio_irq_mask,		\
			.irq_unmask = oxnas_gpio_irq_unmask,		\
			.irq_set_type = oxnas_gpio_irq_set_type,	\
		पूर्ण,							\
	पूर्ण

अटल काष्ठा oxnas_gpio_bank oxnas_gpio_banks[] = अणु
	GPIO_BANK(0),
	GPIO_BANK(1),
पूर्ण;

अटल काष्ठा oxnas_pinctrl ox810se_pinctrl = अणु
	.functions = oxnas_ox810se_functions,
	.nfunctions = ARRAY_SIZE(oxnas_ox810se_functions),
	.groups = oxnas_ox810se_groups,
	.ngroups = ARRAY_SIZE(oxnas_ox810se_groups),
	.gpio_banks = oxnas_gpio_banks,
	.nbanks = ARRAY_SIZE(oxnas_gpio_banks),
पूर्ण;

अटल काष्ठा pinctrl_desc oxnas_ox810se_pinctrl_desc = अणु
	.name = "oxnas-pinctrl",
	.pins = oxnas_ox810se_pins,
	.npins = ARRAY_SIZE(oxnas_ox810se_pins),
	.pctlops = &oxnas_pinctrl_ops,
	.pmxops = &oxnas_ox810se_pinmux_ops,
	.confops = &oxnas_ox810se_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा oxnas_pinctrl ox820_pinctrl = अणु
	.functions = oxnas_ox820_functions,
	.nfunctions = ARRAY_SIZE(oxnas_ox820_functions),
	.groups = oxnas_ox820_groups,
	.ngroups = ARRAY_SIZE(oxnas_ox820_groups),
	.gpio_banks = oxnas_gpio_banks,
	.nbanks = ARRAY_SIZE(oxnas_gpio_banks),
पूर्ण;

अटल काष्ठा pinctrl_desc oxnas_ox820_pinctrl_desc = अणु
	.name = "oxnas-pinctrl",
	.pins = oxnas_ox820_pins,
	.npins = ARRAY_SIZE(oxnas_ox820_pins),
	.pctlops = &oxnas_pinctrl_ops,
	.pmxops = &oxnas_ox820_pinmux_ops,
	.confops = &oxnas_ox820_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा oxnas_pinctrl_data oxnas_ox810se_pinctrl_data = अणु
	.desc = &oxnas_ox810se_pinctrl_desc,
	.pctl = &ox810se_pinctrl,
पूर्ण;

अटल काष्ठा oxnas_pinctrl_data oxnas_ox820_pinctrl_data = अणु
	.desc = &oxnas_ox820_pinctrl_desc,
	.pctl = &ox820_pinctrl,
पूर्ण;

अटल स्थिर काष्ठा of_device_id oxnas_pinctrl_of_match[] = अणु
	अणु .compatible = "oxsemi,ox810se-pinctrl",
	  .data = &oxnas_ox810se_pinctrl_data
	पूर्ण,
	अणु .compatible = "oxsemi,ox820-pinctrl",
	  .data = &oxnas_ox820_pinctrl_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक oxnas_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id;
	स्थिर काष्ठा oxnas_pinctrl_data *data;
	काष्ठा oxnas_pinctrl *pctl;

	id = of_match_node(oxnas_pinctrl_of_match, pdev->dev.of_node);
	अगर (!id)
		वापस -ENODEV;

	data = id->data;
	अगर (!data || !data->pctl || !data->desc)
		वापस -EINVAL;

	pctl = devm_kzalloc(&pdev->dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;
	pctl->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, pctl);

	pctl->regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						       "oxsemi,sys-ctrl");
	अगर (IS_ERR(pctl->regmap)) अणु
		dev_err(&pdev->dev, "failed to get sys ctrl regmap\n");
		वापस -ENODEV;
	पूर्ण

	pctl->functions = data->pctl->functions;
	pctl->nfunctions = data->pctl->nfunctions;
	pctl->groups = data->pctl->groups;
	pctl->ngroups = data->pctl->ngroups;
	pctl->gpio_banks = data->pctl->gpio_banks;
	pctl->nbanks = data->pctl->nbanks;

	pctl->pctldev = pinctrl_रेजिस्टर(data->desc, &pdev->dev, pctl);
	अगर (IS_ERR(pctl->pctldev)) अणु
		dev_err(&pdev->dev, "Failed to register pinctrl device\n");
		वापस PTR_ERR(pctl->pctldev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा of_phandle_args pinspec;
	काष्ठा oxnas_gpio_bank *bank;
	अचिन्हित पूर्णांक id, ngpios;
	पूर्णांक irq, ret;
	काष्ठा gpio_irq_chip *girq;

	अगर (of_parse_phandle_with_fixed_args(np, "gpio-ranges",
					     3, 0, &pinspec)) अणु
		dev_err(&pdev->dev, "gpio-ranges property not found\n");
		वापस -EINVAL;
	पूर्ण

	id = pinspec.args[1] / PINS_PER_BANK;
	ngpios = pinspec.args[2];

	अगर (id >= ARRAY_SIZE(oxnas_gpio_banks)) अणु
		dev_err(&pdev->dev, "invalid gpio-ranges base arg\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ngpios > PINS_PER_BANK) अणु
		dev_err(&pdev->dev, "invalid gpio-ranges count arg\n");
		वापस -EINVAL;
	पूर्ण

	bank = &oxnas_gpio_banks[id];

	bank->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(bank->reg_base))
		वापस PTR_ERR(bank->reg_base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	bank->id = id;
	bank->gpio_chip.parent = &pdev->dev;
	bank->gpio_chip.of_node = np;
	bank->gpio_chip.ngpio = ngpios;
	girq = &bank->gpio_chip.irq;
	girq->chip = &bank->irq_chip;
	girq->parent_handler = oxnas_gpio_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(&pdev->dev, 1, माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;
	girq->parents[0] = irq;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	ret = gpiochip_add_data(&bank->gpio_chip, bank);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to add GPIO chip %u: %d\n",
			id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver oxnas_pinctrl_driver = अणु
	.driver = अणु
		.name = "oxnas-pinctrl",
		.of_match_table = oxnas_pinctrl_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = oxnas_pinctrl_probe,
पूर्ण;

अटल स्थिर काष्ठा of_device_id oxnas_gpio_of_match[] = अणु
	अणु .compatible = "oxsemi,ox810se-gpio", पूर्ण,
	अणु .compatible = "oxsemi,ox820-gpio", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver oxnas_gpio_driver = अणु
	.driver = अणु
		.name = "oxnas-gpio",
		.of_match_table = oxnas_gpio_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = oxnas_gpio_probe,
पूर्ण;

अटल पूर्णांक __init oxnas_gpio_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&oxnas_gpio_driver);
पूर्ण
arch_initcall(oxnas_gpio_रेजिस्टर);

अटल पूर्णांक __init oxnas_pinctrl_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&oxnas_pinctrl_driver);
पूर्ण
arch_initcall(oxnas_pinctrl_रेजिस्टर);
