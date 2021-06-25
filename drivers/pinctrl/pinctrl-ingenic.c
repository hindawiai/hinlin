<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ingenic SoCs pinctrl driver
 *
 * Copyright (c) 2017 Paul Cercueil <paul@crapouillou.net>
 * Copyright (c) 2017, 2019 Paul Boddie <paul@boddie.org.uk>
 * Copyright (c) 2019, 2020 ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinmux.h"

#घोषणा GPIO_PIN					0x00
#घोषणा GPIO_MSK					0x20

#घोषणा JZ4730_GPIO_DATA			0x00
#घोषणा JZ4730_GPIO_GPसूची			0x04
#घोषणा JZ4730_GPIO_GPPUR			0x0c
#घोषणा JZ4730_GPIO_GPALR			0x10
#घोषणा JZ4730_GPIO_GPAUR			0x14
#घोषणा JZ4730_GPIO_GPIDLR			0x18
#घोषणा JZ4730_GPIO_GPIDUR			0x1c
#घोषणा JZ4730_GPIO_GPIER			0x20
#घोषणा JZ4730_GPIO_GPIMR			0x24
#घोषणा JZ4730_GPIO_GPFR			0x28

#घोषणा JZ4740_GPIO_DATA			0x10
#घोषणा JZ4740_GPIO_PULL_DIS		0x30
#घोषणा JZ4740_GPIO_FUNC			0x40
#घोषणा JZ4740_GPIO_SELECT			0x50
#घोषणा JZ4740_GPIO_सूची				0x60
#घोषणा JZ4740_GPIO_TRIG			0x70
#घोषणा JZ4740_GPIO_FLAG			0x80

#घोषणा JZ4770_GPIO_INT				0x10
#घोषणा JZ4770_GPIO_PAT1			0x30
#घोषणा JZ4770_GPIO_PAT0			0x40
#घोषणा JZ4770_GPIO_FLAG			0x50
#घोषणा JZ4770_GPIO_PEN				0x70

#घोषणा X1830_GPIO_PEL				0x110
#घोषणा X1830_GPIO_PEH				0x120
#घोषणा X1830_GPIO_SR				0x150
#घोषणा X1830_GPIO_SMT				0x160

#घोषणा X2000_GPIO_EDG				0x70
#घोषणा X2000_GPIO_PEPU				0x80
#घोषणा X2000_GPIO_PEPD				0x90
#घोषणा X2000_GPIO_SR				0xd0
#घोषणा X2000_GPIO_SMT				0xe0

#घोषणा REG_SET(x)					((x) + 0x4)
#घोषणा REG_CLEAR(x)				((x) + 0x8)

#घोषणा REG_PZ_BASE(x)				((x) * 7)
#घोषणा REG_PZ_GID2LD(x)			((x) * 7 + 0xf0)

#घोषणा GPIO_PULL_DIS				0
#घोषणा GPIO_PULL_UP				1
#घोषणा GPIO_PULL_DOWN				2

#घोषणा PINS_PER_GPIO_CHIP			32
#घोषणा JZ4730_PINS_PER_PAIRED_REG	16

#घोषणा INGENIC_PIN_GROUP_FUNCS(name, id, funcs)		\
	अणु						\
		name,					\
		id##_pins,				\
		ARRAY_SIZE(id##_pins),			\
		funcs,					\
	पूर्ण

#घोषणा INGENIC_PIN_GROUP(name, id, func)		\
	INGENIC_PIN_GROUP_FUNCS(name, id, (व्योम *)(func))

क्रमागत jz_version अणु
	ID_JZ4730,
	ID_JZ4740,
	ID_JZ4725B,
	ID_JZ4750,
	ID_JZ4755,
	ID_JZ4760,
	ID_JZ4770,
	ID_JZ4775,
	ID_JZ4780,
	ID_X1000,
	ID_X1500,
	ID_X1830,
	ID_X2000,
पूर्ण;

काष्ठा ingenic_chip_info अणु
	अचिन्हित पूर्णांक num_chips;
	अचिन्हित पूर्णांक reg_offset;
	क्रमागत jz_version version;

	स्थिर काष्ठा group_desc *groups;
	अचिन्हित पूर्णांक num_groups;

	स्थिर काष्ठा function_desc *functions;
	अचिन्हित पूर्णांक num_functions;

	स्थिर u32 *pull_ups, *pull_करोwns;
पूर्ण;

काष्ठा ingenic_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा regmap *map;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा pinctrl_pin_desc *pdesc;

	स्थिर काष्ठा ingenic_chip_info *info;
पूर्ण;

काष्ठा ingenic_gpio_chip अणु
	काष्ठा ingenic_pinctrl *jzpc;
	काष्ठा gpio_chip gc;
	काष्ठा irq_chip irq_chip;
	अचिन्हित पूर्णांक irq, reg_base;
पूर्ण;

अटल स्थिर u32 jz4730_pull_ups[4] = अणु
	0x3fa3320f, 0xf200ffff, 0xffffffff, 0xffffffff,
पूर्ण;

अटल स्थिर u32 jz4730_pull_करोwns[4] = अणु
	0x00000df0, 0x0dff0000, 0x00000000, 0x00000000,
पूर्ण;

अटल पूर्णांक jz4730_mmc_1bit_pins[] = अणु 0x27, 0x26, 0x22, पूर्ण;
अटल पूर्णांक jz4730_mmc_4bit_pins[] = अणु 0x23, 0x24, 0x25, पूर्ण;
अटल पूर्णांक jz4730_uart0_data_pins[] = अणु 0x7e, 0x7f, पूर्ण;
अटल पूर्णांक jz4730_uart1_data_pins[] = अणु 0x18, 0x19, पूर्ण;
अटल पूर्णांक jz4730_uart2_data_pins[] = अणु 0x6f, 0x7d, पूर्ण;
अटल पूर्णांक jz4730_uart3_data_pins[] = अणु 0x10, 0x15, पूर्ण;
अटल पूर्णांक jz4730_uart3_hwflow_pins[] = अणु 0x11, 0x17, पूर्ण;
अटल पूर्णांक jz4730_lcd_8bit_pins[] = अणु
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	0x3a, 0x39, 0x38,
पूर्ण;
अटल पूर्णांक jz4730_lcd_16bit_pins[] = अणु
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
पूर्ण;
अटल पूर्णांक jz4730_lcd_special_pins[] = अणु 0x3d, 0x3c, 0x3e, 0x3f, पूर्ण;
अटल पूर्णांक jz4730_lcd_generic_pins[] = अणु 0x3b, पूर्ण;
अटल पूर्णांक jz4730_nand_cs1_pins[] = अणु 0x53, पूर्ण;
अटल पूर्णांक jz4730_nand_cs2_pins[] = अणु 0x54, पूर्ण;
अटल पूर्णांक jz4730_nand_cs3_pins[] = अणु 0x55, पूर्ण;
अटल पूर्णांक jz4730_nand_cs4_pins[] = अणु 0x56, पूर्ण;
अटल पूर्णांक jz4730_nand_cs5_pins[] = अणु 0x57, पूर्ण;
अटल पूर्णांक jz4730_pwm_pwm0_pins[] = अणु 0x5e, पूर्ण;
अटल पूर्णांक jz4730_pwm_pwm1_pins[] = अणु 0x5f, पूर्ण;

अटल u8 jz4730_lcd_8bit_funcs[] = अणु 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, पूर्ण;

अटल स्थिर काष्ठा group_desc jz4730_groups[] = अणु
	INGENIC_PIN_GROUP("mmc-1bit", jz4730_mmc_1bit, 1),
	INGENIC_PIN_GROUP("mmc-4bit", jz4730_mmc_4bit, 1),
	INGENIC_PIN_GROUP("uart0-data", jz4730_uart0_data, 1),
	INGENIC_PIN_GROUP("uart1-data", jz4730_uart1_data, 1),
	INGENIC_PIN_GROUP("uart2-data", jz4730_uart2_data, 1),
	INGENIC_PIN_GROUP("uart3-data", jz4730_uart3_data, 1),
	INGENIC_PIN_GROUP("uart3-hwflow", jz4730_uart3_hwflow, 1),
	INGENIC_PIN_GROUP_FUNCS("lcd-8bit", jz4730_lcd_8bit, jz4730_lcd_8bit_funcs),
	INGENIC_PIN_GROUP("lcd-16bit", jz4730_lcd_16bit, 1),
	INGENIC_PIN_GROUP("lcd-special", jz4730_lcd_special, 1),
	INGENIC_PIN_GROUP("lcd-generic", jz4730_lcd_generic, 1),
	INGENIC_PIN_GROUP("nand-cs1", jz4730_nand_cs1, 1),
	INGENIC_PIN_GROUP("nand-cs2", jz4730_nand_cs2, 1),
	INGENIC_PIN_GROUP("nand-cs3", jz4730_nand_cs3, 1),
	INGENIC_PIN_GROUP("nand-cs4", jz4730_nand_cs4, 1),
	INGENIC_PIN_GROUP("nand-cs5", jz4730_nand_cs5, 1),
	INGENIC_PIN_GROUP("pwm0", jz4730_pwm_pwm0, 1),
	INGENIC_PIN_GROUP("pwm1", jz4730_pwm_pwm1, 1),
पूर्ण;

अटल स्थिर अक्षर *jz4730_mmc_groups[] = अणु "mmc-1bit", "mmc-4bit", पूर्ण;
अटल स्थिर अक्षर *jz4730_uart0_groups[] = अणु "uart0-data", पूर्ण;
अटल स्थिर अक्षर *jz4730_uart1_groups[] = अणु "uart1-data", पूर्ण;
अटल स्थिर अक्षर *jz4730_uart2_groups[] = अणु "uart2-data", पूर्ण;
अटल स्थिर अक्षर *jz4730_uart3_groups[] = अणु "uart3-data", "uart3-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4730_lcd_groups[] = अणु
	"lcd-8bit", "lcd-16bit", "lcd-special", "lcd-generic",
पूर्ण;
अटल स्थिर अक्षर *jz4730_nand_groups[] = अणु
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4", "nand-cs5",
पूर्ण;
अटल स्थिर अक्षर *jz4730_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *jz4730_pwm1_groups[] = अणु "pwm1", पूर्ण;

अटल स्थिर काष्ठा function_desc jz4730_functions[] = अणु
	अणु "mmc", jz4730_mmc_groups, ARRAY_SIZE(jz4730_mmc_groups), पूर्ण,
	अणु "uart0", jz4730_uart0_groups, ARRAY_SIZE(jz4730_uart0_groups), पूर्ण,
	अणु "uart1", jz4730_uart1_groups, ARRAY_SIZE(jz4730_uart1_groups), पूर्ण,
	अणु "uart2", jz4730_uart2_groups, ARRAY_SIZE(jz4730_uart2_groups), पूर्ण,
	अणु "uart3", jz4730_uart3_groups, ARRAY_SIZE(jz4730_uart3_groups), पूर्ण,
	अणु "lcd", jz4730_lcd_groups, ARRAY_SIZE(jz4730_lcd_groups), पूर्ण,
	अणु "nand", jz4730_nand_groups, ARRAY_SIZE(jz4730_nand_groups), पूर्ण,
	अणु "pwm0", jz4730_pwm0_groups, ARRAY_SIZE(jz4730_pwm0_groups), पूर्ण,
	अणु "pwm1", jz4730_pwm1_groups, ARRAY_SIZE(jz4730_pwm1_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info jz4730_chip_info = अणु
	.num_chips = 4,
	.reg_offset = 0x30,
	.version = ID_JZ4730,
	.groups = jz4730_groups,
	.num_groups = ARRAY_SIZE(jz4730_groups),
	.functions = jz4730_functions,
	.num_functions = ARRAY_SIZE(jz4730_functions),
	.pull_ups = jz4730_pull_ups,
	.pull_करोwns = jz4730_pull_करोwns,
पूर्ण;

अटल स्थिर u32 jz4740_pull_ups[4] = अणु
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
पूर्ण;

अटल स्थिर u32 jz4740_pull_करोwns[4] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

अटल पूर्णांक jz4740_mmc_1bit_pins[] = अणु 0x69, 0x68, 0x6a, पूर्ण;
अटल पूर्णांक jz4740_mmc_4bit_pins[] = अणु 0x6b, 0x6c, 0x6d, पूर्ण;
अटल पूर्णांक jz4740_uart0_data_pins[] = अणु 0x7a, 0x79, पूर्ण;
अटल पूर्णांक jz4740_uart0_hwflow_pins[] = अणु 0x7e, 0x7f, पूर्ण;
अटल पूर्णांक jz4740_uart1_data_pins[] = अणु 0x7e, 0x7f, पूर्ण;
अटल पूर्णांक jz4740_lcd_8bit_pins[] = अणु
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x52, 0x53, 0x54,
पूर्ण;
अटल पूर्णांक jz4740_lcd_16bit_pins[] = अणु
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
पूर्ण;
अटल पूर्णांक jz4740_lcd_18bit_pins[] = अणु 0x50, 0x51, पूर्ण;
अटल पूर्णांक jz4740_lcd_special_pins[] = अणु 0x31, 0x32, 0x56, 0x57, पूर्ण;
अटल पूर्णांक jz4740_lcd_generic_pins[] = अणु 0x55, पूर्ण;
अटल पूर्णांक jz4740_nand_cs1_pins[] = अणु 0x39, पूर्ण;
अटल पूर्णांक jz4740_nand_cs2_pins[] = अणु 0x3a, पूर्ण;
अटल पूर्णांक jz4740_nand_cs3_pins[] = अणु 0x3b, पूर्ण;
अटल पूर्णांक jz4740_nand_cs4_pins[] = अणु 0x3c, पूर्ण;
अटल पूर्णांक jz4740_nand_fre_fwe_pins[] = अणु 0x5c, 0x5d, पूर्ण;
अटल पूर्णांक jz4740_pwm_pwm0_pins[] = अणु 0x77, पूर्ण;
अटल पूर्णांक jz4740_pwm_pwm1_pins[] = अणु 0x78, पूर्ण;
अटल पूर्णांक jz4740_pwm_pwm2_pins[] = अणु 0x79, पूर्ण;
अटल पूर्णांक jz4740_pwm_pwm3_pins[] = अणु 0x7a, पूर्ण;
अटल पूर्णांक jz4740_pwm_pwm4_pins[] = अणु 0x7b, पूर्ण;
अटल पूर्णांक jz4740_pwm_pwm5_pins[] = अणु 0x7c, पूर्ण;
अटल पूर्णांक jz4740_pwm_pwm6_pins[] = अणु 0x7e, पूर्ण;
अटल पूर्णांक jz4740_pwm_pwm7_pins[] = अणु 0x7f, पूर्ण;

अटल स्थिर काष्ठा group_desc jz4740_groups[] = अणु
	INGENIC_PIN_GROUP("mmc-1bit", jz4740_mmc_1bit, 0),
	INGENIC_PIN_GROUP("mmc-4bit", jz4740_mmc_4bit, 0),
	INGENIC_PIN_GROUP("uart0-data", jz4740_uart0_data, 1),
	INGENIC_PIN_GROUP("uart0-hwflow", jz4740_uart0_hwflow, 1),
	INGENIC_PIN_GROUP("uart1-data", jz4740_uart1_data, 2),
	INGENIC_PIN_GROUP("lcd-8bit", jz4740_lcd_8bit, 0),
	INGENIC_PIN_GROUP("lcd-16bit", jz4740_lcd_16bit, 0),
	INGENIC_PIN_GROUP("lcd-18bit", jz4740_lcd_18bit, 0),
	INGENIC_PIN_GROUP("lcd-special", jz4740_lcd_special, 0),
	INGENIC_PIN_GROUP("lcd-generic", jz4740_lcd_generic, 0),
	INGENIC_PIN_GROUP("nand-cs1", jz4740_nand_cs1, 0),
	INGENIC_PIN_GROUP("nand-cs2", jz4740_nand_cs2, 0),
	INGENIC_PIN_GROUP("nand-cs3", jz4740_nand_cs3, 0),
	INGENIC_PIN_GROUP("nand-cs4", jz4740_nand_cs4, 0),
	INGENIC_PIN_GROUP("nand-fre-fwe", jz4740_nand_fre_fwe, 0),
	INGENIC_PIN_GROUP("pwm0", jz4740_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", jz4740_pwm_pwm1, 0),
	INGENIC_PIN_GROUP("pwm2", jz4740_pwm_pwm2, 0),
	INGENIC_PIN_GROUP("pwm3", jz4740_pwm_pwm3, 0),
	INGENIC_PIN_GROUP("pwm4", jz4740_pwm_pwm4, 0),
	INGENIC_PIN_GROUP("pwm5", jz4740_pwm_pwm5, 0),
	INGENIC_PIN_GROUP("pwm6", jz4740_pwm_pwm6, 0),
	INGENIC_PIN_GROUP("pwm7", jz4740_pwm_pwm7, 0),
पूर्ण;

अटल स्थिर अक्षर *jz4740_mmc_groups[] = अणु "mmc-1bit", "mmc-4bit", पूर्ण;
अटल स्थिर अक्षर *jz4740_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4740_uart1_groups[] = अणु "uart1-data", पूर्ण;
अटल स्थिर अक्षर *jz4740_lcd_groups[] = अणु
	"lcd-8bit", "lcd-16bit", "lcd-18bit", "lcd-special", "lcd-generic",
पूर्ण;
अटल स्थिर अक्षर *jz4740_nand_groups[] = अणु
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4", "nand-fre-fwe",
पूर्ण;
अटल स्थिर अक्षर *jz4740_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *jz4740_pwm1_groups[] = अणु "pwm1", पूर्ण;
अटल स्थिर अक्षर *jz4740_pwm2_groups[] = अणु "pwm2", पूर्ण;
अटल स्थिर अक्षर *jz4740_pwm3_groups[] = अणु "pwm3", पूर्ण;
अटल स्थिर अक्षर *jz4740_pwm4_groups[] = अणु "pwm4", पूर्ण;
अटल स्थिर अक्षर *jz4740_pwm5_groups[] = अणु "pwm5", पूर्ण;
अटल स्थिर अक्षर *jz4740_pwm6_groups[] = अणु "pwm6", पूर्ण;
अटल स्थिर अक्षर *jz4740_pwm7_groups[] = अणु "pwm7", पूर्ण;

अटल स्थिर काष्ठा function_desc jz4740_functions[] = अणु
	अणु "mmc", jz4740_mmc_groups, ARRAY_SIZE(jz4740_mmc_groups), पूर्ण,
	अणु "uart0", jz4740_uart0_groups, ARRAY_SIZE(jz4740_uart0_groups), पूर्ण,
	अणु "uart1", jz4740_uart1_groups, ARRAY_SIZE(jz4740_uart1_groups), पूर्ण,
	अणु "lcd", jz4740_lcd_groups, ARRAY_SIZE(jz4740_lcd_groups), पूर्ण,
	अणु "nand", jz4740_nand_groups, ARRAY_SIZE(jz4740_nand_groups), पूर्ण,
	अणु "pwm0", jz4740_pwm0_groups, ARRAY_SIZE(jz4740_pwm0_groups), पूर्ण,
	अणु "pwm1", jz4740_pwm1_groups, ARRAY_SIZE(jz4740_pwm1_groups), पूर्ण,
	अणु "pwm2", jz4740_pwm2_groups, ARRAY_SIZE(jz4740_pwm2_groups), पूर्ण,
	अणु "pwm3", jz4740_pwm3_groups, ARRAY_SIZE(jz4740_pwm3_groups), पूर्ण,
	अणु "pwm4", jz4740_pwm4_groups, ARRAY_SIZE(jz4740_pwm4_groups), पूर्ण,
	अणु "pwm5", jz4740_pwm5_groups, ARRAY_SIZE(jz4740_pwm5_groups), पूर्ण,
	अणु "pwm6", jz4740_pwm6_groups, ARRAY_SIZE(jz4740_pwm6_groups), पूर्ण,
	अणु "pwm7", jz4740_pwm7_groups, ARRAY_SIZE(jz4740_pwm7_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info jz4740_chip_info = अणु
	.num_chips = 4,
	.reg_offset = 0x100,
	.version = ID_JZ4740,
	.groups = jz4740_groups,
	.num_groups = ARRAY_SIZE(jz4740_groups),
	.functions = jz4740_functions,
	.num_functions = ARRAY_SIZE(jz4740_functions),
	.pull_ups = jz4740_pull_ups,
	.pull_करोwns = jz4740_pull_करोwns,
पूर्ण;

अटल पूर्णांक jz4725b_mmc0_1bit_pins[] = अणु 0x48, 0x49, 0x5c, पूर्ण;
अटल पूर्णांक jz4725b_mmc0_4bit_pins[] = अणु 0x5d, 0x5b, 0x56, पूर्ण;
अटल पूर्णांक jz4725b_mmc1_1bit_pins[] = अणु 0x7a, 0x7b, 0x7c, पूर्ण;
अटल पूर्णांक jz4725b_mmc1_4bit_pins[] = अणु 0x7d, 0x7e, 0x7f, पूर्ण;
अटल पूर्णांक jz4725b_uart_data_pins[] = अणु 0x4c, 0x4d, पूर्ण;
अटल पूर्णांक jz4725b_lcd_8bit_pins[] = अणु
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x72, 0x73, 0x74,
पूर्ण;
अटल पूर्णांक jz4725b_lcd_16bit_pins[] = अणु
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
पूर्ण;
अटल पूर्णांक jz4725b_lcd_18bit_pins[] = अणु 0x70, 0x71, पूर्ण;
अटल पूर्णांक jz4725b_lcd_24bit_pins[] = अणु 0x76, 0x77, 0x78, 0x79, पूर्ण;
अटल पूर्णांक jz4725b_lcd_special_pins[] = अणु 0x76, 0x77, 0x78, 0x79, पूर्ण;
अटल पूर्णांक jz4725b_lcd_generic_pins[] = अणु 0x75, पूर्ण;
अटल पूर्णांक jz4725b_nand_cs1_pins[] = अणु 0x55, पूर्ण;
अटल पूर्णांक jz4725b_nand_cs2_pins[] = अणु 0x56, पूर्ण;
अटल पूर्णांक jz4725b_nand_cs3_pins[] = अणु 0x57, पूर्ण;
अटल पूर्णांक jz4725b_nand_cs4_pins[] = अणु 0x58, पूर्ण;
अटल पूर्णांक jz4725b_nand_cle_ale_pins[] = अणु 0x48, 0x49 पूर्ण;
अटल पूर्णांक jz4725b_nand_fre_fwe_pins[] = अणु 0x5c, 0x5d पूर्ण;
अटल पूर्णांक jz4725b_pwm_pwm0_pins[] = अणु 0x4a, पूर्ण;
अटल पूर्णांक jz4725b_pwm_pwm1_pins[] = अणु 0x4b, पूर्ण;
अटल पूर्णांक jz4725b_pwm_pwm2_pins[] = अणु 0x4c, पूर्ण;
अटल पूर्णांक jz4725b_pwm_pwm3_pins[] = अणु 0x4d, पूर्ण;
अटल पूर्णांक jz4725b_pwm_pwm4_pins[] = अणु 0x4e, पूर्ण;
अटल पूर्णांक jz4725b_pwm_pwm5_pins[] = अणु 0x4f, पूर्ण;

अटल u8 jz4725b_mmc0_4bit_funcs[] = अणु 1, 0, 1, पूर्ण;

अटल स्थिर काष्ठा group_desc jz4725b_groups[] = अणु
	INGENIC_PIN_GROUP("mmc0-1bit", jz4725b_mmc0_1bit, 1),
	INGENIC_PIN_GROUP_FUNCS("mmc0-4bit", jz4725b_mmc0_4bit,
				jz4725b_mmc0_4bit_funcs),
	INGENIC_PIN_GROUP("mmc1-1bit", jz4725b_mmc1_1bit, 0),
	INGENIC_PIN_GROUP("mmc1-4bit", jz4725b_mmc1_4bit, 0),
	INGENIC_PIN_GROUP("uart-data", jz4725b_uart_data, 1),
	INGENIC_PIN_GROUP("lcd-8bit", jz4725b_lcd_8bit, 0),
	INGENIC_PIN_GROUP("lcd-16bit", jz4725b_lcd_16bit, 0),
	INGENIC_PIN_GROUP("lcd-18bit", jz4725b_lcd_18bit, 0),
	INGENIC_PIN_GROUP("lcd-24bit", jz4725b_lcd_24bit, 1),
	INGENIC_PIN_GROUP("lcd-special", jz4725b_lcd_special, 0),
	INGENIC_PIN_GROUP("lcd-generic", jz4725b_lcd_generic, 0),
	INGENIC_PIN_GROUP("nand-cs1", jz4725b_nand_cs1, 0),
	INGENIC_PIN_GROUP("nand-cs2", jz4725b_nand_cs2, 0),
	INGENIC_PIN_GROUP("nand-cs3", jz4725b_nand_cs3, 0),
	INGENIC_PIN_GROUP("nand-cs4", jz4725b_nand_cs4, 0),
	INGENIC_PIN_GROUP("nand-cle-ale", jz4725b_nand_cle_ale, 0),
	INGENIC_PIN_GROUP("nand-fre-fwe", jz4725b_nand_fre_fwe, 0),
	INGENIC_PIN_GROUP("pwm0", jz4725b_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", jz4725b_pwm_pwm1, 0),
	INGENIC_PIN_GROUP("pwm2", jz4725b_pwm_pwm2, 0),
	INGENIC_PIN_GROUP("pwm3", jz4725b_pwm_pwm3, 0),
	INGENIC_PIN_GROUP("pwm4", jz4725b_pwm_pwm4, 0),
	INGENIC_PIN_GROUP("pwm5", jz4725b_pwm_pwm5, 0),
पूर्ण;

अटल स्थिर अक्षर *jz4725b_mmc0_groups[] = अणु "mmc0-1bit", "mmc0-4bit", पूर्ण;
अटल स्थिर अक्षर *jz4725b_mmc1_groups[] = अणु "mmc1-1bit", "mmc1-4bit", पूर्ण;
अटल स्थिर अक्षर *jz4725b_uart_groups[] = अणु "uart-data", पूर्ण;
अटल स्थिर अक्षर *jz4725b_lcd_groups[] = अणु
	"lcd-8bit", "lcd-16bit", "lcd-18bit", "lcd-24bit",
	"lcd-special", "lcd-generic",
पूर्ण;
अटल स्थिर अक्षर *jz4725b_nand_groups[] = अणु
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4",
	"nand-cle-ale", "nand-fre-fwe",
पूर्ण;
अटल स्थिर अक्षर *jz4725b_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *jz4725b_pwm1_groups[] = अणु "pwm1", पूर्ण;
अटल स्थिर अक्षर *jz4725b_pwm2_groups[] = अणु "pwm2", पूर्ण;
अटल स्थिर अक्षर *jz4725b_pwm3_groups[] = अणु "pwm3", पूर्ण;
अटल स्थिर अक्षर *jz4725b_pwm4_groups[] = अणु "pwm4", पूर्ण;
अटल स्थिर अक्षर *jz4725b_pwm5_groups[] = अणु "pwm5", पूर्ण;

अटल स्थिर काष्ठा function_desc jz4725b_functions[] = अणु
	अणु "mmc0", jz4725b_mmc0_groups, ARRAY_SIZE(jz4725b_mmc0_groups), पूर्ण,
	अणु "mmc1", jz4725b_mmc1_groups, ARRAY_SIZE(jz4725b_mmc1_groups), पूर्ण,
	अणु "uart", jz4725b_uart_groups, ARRAY_SIZE(jz4725b_uart_groups), पूर्ण,
	अणु "nand", jz4725b_nand_groups, ARRAY_SIZE(jz4725b_nand_groups), पूर्ण,
	अणु "pwm0", jz4725b_pwm0_groups, ARRAY_SIZE(jz4725b_pwm0_groups), पूर्ण,
	अणु "pwm1", jz4725b_pwm1_groups, ARRAY_SIZE(jz4725b_pwm1_groups), पूर्ण,
	अणु "pwm2", jz4725b_pwm2_groups, ARRAY_SIZE(jz4725b_pwm2_groups), पूर्ण,
	अणु "pwm3", jz4725b_pwm3_groups, ARRAY_SIZE(jz4725b_pwm3_groups), पूर्ण,
	अणु "pwm4", jz4725b_pwm4_groups, ARRAY_SIZE(jz4725b_pwm4_groups), पूर्ण,
	अणु "pwm5", jz4725b_pwm5_groups, ARRAY_SIZE(jz4725b_pwm5_groups), पूर्ण,
	अणु "lcd", jz4725b_lcd_groups, ARRAY_SIZE(jz4725b_lcd_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info jz4725b_chip_info = अणु
	.num_chips = 4,
	.reg_offset = 0x100,
	.version = ID_JZ4725B,
	.groups = jz4725b_groups,
	.num_groups = ARRAY_SIZE(jz4725b_groups),
	.functions = jz4725b_functions,
	.num_functions = ARRAY_SIZE(jz4725b_functions),
	.pull_ups = jz4740_pull_ups,
	.pull_करोwns = jz4740_pull_करोwns,
पूर्ण;

अटल स्थिर u32 jz4750_pull_ups[6] = अणु
	0xffffffff, 0xffffffff, 0x3fffffff, 0x7fffffff, 0x1fff3fff, 0x00ffffff,
पूर्ण;

अटल स्थिर u32 jz4750_pull_करोwns[6] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

अटल पूर्णांक jz4750_uart0_data_pins[] = अणु 0xa4, 0xa5, पूर्ण;
अटल पूर्णांक jz4750_uart0_hwflow_pins[] = अणु 0xa6, 0xa7, पूर्ण;
अटल पूर्णांक jz4750_uart1_data_pins[] = अणु 0x90, 0x91, पूर्ण;
अटल पूर्णांक jz4750_uart1_hwflow_pins[] = अणु 0x92, 0x93, पूर्ण;
अटल पूर्णांक jz4750_uart2_data_pins[] = अणु 0x9b, 0x9a, पूर्ण;
अटल पूर्णांक jz4750_uart3_data_pins[] = अणु 0xb0, 0xb1, पूर्ण;
अटल पूर्णांक jz4750_uart3_hwflow_pins[] = अणु 0xb2, 0xb3, पूर्ण;
अटल पूर्णांक jz4750_mmc0_1bit_pins[] = अणु 0xa8, 0xa9, 0xa0, पूर्ण;
अटल पूर्णांक jz4750_mmc0_4bit_pins[] = अणु 0xa1, 0xa2, 0xa3, पूर्ण;
अटल पूर्णांक jz4750_mmc0_8bit_pins[] = अणु 0xa4, 0xa5, 0xa6, 0xa7, पूर्ण;
अटल पूर्णांक jz4750_mmc1_1bit_pins[] = अणु 0xae, 0xaf, 0xaa, पूर्ण;
अटल पूर्णांक jz4750_mmc1_4bit_pins[] = अणु 0xab, 0xac, 0xad, पूर्ण;
अटल पूर्णांक jz4750_i2c_pins[] = अणु 0x8c, 0x8d, पूर्ण;
अटल पूर्णांक jz4750_cim_pins[] = अणु
	0x89, 0x8b, 0x8a, 0x88,
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
पूर्ण;
अटल पूर्णांक jz4750_lcd_8bit_pins[] = अणु
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x72, 0x73, 0x74,
पूर्ण;
अटल पूर्णांक jz4750_lcd_16bit_pins[] = अणु
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
पूर्ण;
अटल पूर्णांक jz4750_lcd_18bit_pins[] = अणु 0x70, 0x71, पूर्ण;
अटल पूर्णांक jz4750_lcd_24bit_pins[] = अणु 0x76, 0x77, 0x78, 0x79, 0xb2, 0xb3, पूर्ण;
अटल पूर्णांक jz4750_lcd_special_pins[] = अणु 0x76, 0x77, 0x78, 0x79, पूर्ण;
अटल पूर्णांक jz4750_lcd_generic_pins[] = अणु 0x75, पूर्ण;
अटल पूर्णांक jz4750_nand_cs1_pins[] = अणु 0x55, पूर्ण;
अटल पूर्णांक jz4750_nand_cs2_pins[] = अणु 0x56, पूर्ण;
अटल पूर्णांक jz4750_nand_cs3_pins[] = अणु 0x57, पूर्ण;
अटल पूर्णांक jz4750_nand_cs4_pins[] = अणु 0x58, पूर्ण;
अटल पूर्णांक jz4750_nand_fre_fwe_pins[] = अणु 0x5c, 0x5d, पूर्ण;
अटल पूर्णांक jz4750_pwm_pwm0_pins[] = अणु 0x94, पूर्ण;
अटल पूर्णांक jz4750_pwm_pwm1_pins[] = अणु 0x95, पूर्ण;
अटल पूर्णांक jz4750_pwm_pwm2_pins[] = अणु 0x96, पूर्ण;
अटल पूर्णांक jz4750_pwm_pwm3_pins[] = अणु 0x97, पूर्ण;
अटल पूर्णांक jz4750_pwm_pwm4_pins[] = अणु 0x98, पूर्ण;
अटल पूर्णांक jz4750_pwm_pwm5_pins[] = अणु 0x99, पूर्ण;

अटल स्थिर काष्ठा group_desc jz4750_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", jz4750_uart0_data, 1),
	INGENIC_PIN_GROUP("uart0-hwflow", jz4750_uart0_hwflow, 1),
	INGENIC_PIN_GROUP("uart1-data", jz4750_uart1_data, 0),
	INGENIC_PIN_GROUP("uart1-hwflow", jz4750_uart1_hwflow, 0),
	INGENIC_PIN_GROUP("uart2-data", jz4750_uart2_data, 1),
	INGENIC_PIN_GROUP("uart3-data", jz4750_uart3_data, 0),
	INGENIC_PIN_GROUP("uart3-hwflow", jz4750_uart3_hwflow, 0),
	INGENIC_PIN_GROUP("mmc0-1bit", jz4750_mmc0_1bit, 0),
	INGENIC_PIN_GROUP("mmc0-4bit", jz4750_mmc0_4bit, 0),
	INGENIC_PIN_GROUP("mmc0-8bit", jz4750_mmc0_8bit, 0),
	INGENIC_PIN_GROUP("mmc1-1bit", jz4750_mmc1_1bit, 0),
	INGENIC_PIN_GROUP("mmc1-4bit", jz4750_mmc1_4bit, 0),
	INGENIC_PIN_GROUP("i2c-data", jz4750_i2c, 0),
	INGENIC_PIN_GROUP("cim-data", jz4750_cim, 0),
	INGENIC_PIN_GROUP("lcd-8bit", jz4750_lcd_8bit, 0),
	INGENIC_PIN_GROUP("lcd-16bit", jz4750_lcd_16bit, 0),
	INGENIC_PIN_GROUP("lcd-18bit", jz4750_lcd_18bit, 0),
	INGENIC_PIN_GROUP("lcd-24bit", jz4750_lcd_24bit, 1),
	INGENIC_PIN_GROUP("lcd-special", jz4750_lcd_special, 0),
	INGENIC_PIN_GROUP("lcd-generic", jz4750_lcd_generic, 0),
	INGENIC_PIN_GROUP("nand-cs1", jz4750_nand_cs1, 0),
	INGENIC_PIN_GROUP("nand-cs2", jz4750_nand_cs2, 0),
	INGENIC_PIN_GROUP("nand-cs3", jz4750_nand_cs3, 0),
	INGENIC_PIN_GROUP("nand-cs4", jz4750_nand_cs4, 0),
	INGENIC_PIN_GROUP("nand-fre-fwe", jz4750_nand_fre_fwe, 0),
	INGENIC_PIN_GROUP("pwm0", jz4750_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", jz4750_pwm_pwm1, 0),
	INGENIC_PIN_GROUP("pwm2", jz4750_pwm_pwm2, 0),
	INGENIC_PIN_GROUP("pwm3", jz4750_pwm_pwm3, 0),
	INGENIC_PIN_GROUP("pwm4", jz4750_pwm_pwm4, 0),
	INGENIC_PIN_GROUP("pwm5", jz4750_pwm_pwm5, 0),
पूर्ण;

अटल स्थिर अक्षर *jz4750_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4750_uart1_groups[] = अणु "uart1-data", "uart1-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4750_uart2_groups[] = अणु "uart2-data", पूर्ण;
अटल स्थिर अक्षर *jz4750_uart3_groups[] = अणु "uart3-data", "uart3-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4750_mmc0_groups[] = अणु
	"mmc0-1bit", "mmc0-4bit", "mmc0-8bit",
पूर्ण;
अटल स्थिर अक्षर *jz4750_mmc1_groups[] = अणु "mmc0-1bit", "mmc0-4bit", पूर्ण;
अटल स्थिर अक्षर *jz4750_i2c_groups[] = अणु "i2c-data", पूर्ण;
अटल स्थिर अक्षर *jz4750_cim_groups[] = अणु "cim-data", पूर्ण;
अटल स्थिर अक्षर *jz4750_lcd_groups[] = अणु
	"lcd-8bit", "lcd-16bit", "lcd-18bit", "lcd-24bit",
	"lcd-special", "lcd-generic",
पूर्ण;
अटल स्थिर अक्षर *jz4750_nand_groups[] = अणु
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4", "nand-fre-fwe",
पूर्ण;
अटल स्थिर अक्षर *jz4750_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *jz4750_pwm1_groups[] = अणु "pwm1", पूर्ण;
अटल स्थिर अक्षर *jz4750_pwm2_groups[] = अणु "pwm2", पूर्ण;
अटल स्थिर अक्षर *jz4750_pwm3_groups[] = अणु "pwm3", पूर्ण;
अटल स्थिर अक्षर *jz4750_pwm4_groups[] = अणु "pwm4", पूर्ण;
अटल स्थिर अक्षर *jz4750_pwm5_groups[] = अणु "pwm5", पूर्ण;

अटल स्थिर काष्ठा function_desc jz4750_functions[] = अणु
	अणु "uart0", jz4750_uart0_groups, ARRAY_SIZE(jz4750_uart0_groups), पूर्ण,
	अणु "uart1", jz4750_uart1_groups, ARRAY_SIZE(jz4750_uart1_groups), पूर्ण,
	अणु "uart2", jz4750_uart2_groups, ARRAY_SIZE(jz4750_uart2_groups), पूर्ण,
	अणु "uart3", jz4750_uart3_groups, ARRAY_SIZE(jz4750_uart3_groups), पूर्ण,
	अणु "mmc0", jz4750_mmc0_groups, ARRAY_SIZE(jz4750_mmc0_groups), पूर्ण,
	अणु "mmc1", jz4750_mmc1_groups, ARRAY_SIZE(jz4750_mmc1_groups), पूर्ण,
	अणु "i2c", jz4750_i2c_groups, ARRAY_SIZE(jz4750_i2c_groups), पूर्ण,
	अणु "cim", jz4750_cim_groups, ARRAY_SIZE(jz4750_cim_groups), पूर्ण,
	अणु "lcd", jz4750_lcd_groups, ARRAY_SIZE(jz4750_lcd_groups), पूर्ण,
	अणु "nand", jz4750_nand_groups, ARRAY_SIZE(jz4750_nand_groups), पूर्ण,
	अणु "pwm0", jz4750_pwm0_groups, ARRAY_SIZE(jz4750_pwm0_groups), पूर्ण,
	अणु "pwm1", jz4750_pwm1_groups, ARRAY_SIZE(jz4750_pwm1_groups), पूर्ण,
	अणु "pwm2", jz4750_pwm2_groups, ARRAY_SIZE(jz4750_pwm2_groups), पूर्ण,
	अणु "pwm3", jz4750_pwm3_groups, ARRAY_SIZE(jz4750_pwm3_groups), पूर्ण,
	अणु "pwm4", jz4750_pwm4_groups, ARRAY_SIZE(jz4750_pwm4_groups), पूर्ण,
	अणु "pwm5", jz4750_pwm5_groups, ARRAY_SIZE(jz4750_pwm5_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info jz4750_chip_info = अणु
	.num_chips = 6,
	.reg_offset = 0x100,
	.version = ID_JZ4750,
	.groups = jz4750_groups,
	.num_groups = ARRAY_SIZE(jz4750_groups),
	.functions = jz4750_functions,
	.num_functions = ARRAY_SIZE(jz4750_functions),
	.pull_ups = jz4750_pull_ups,
	.pull_करोwns = jz4750_pull_करोwns,
पूर्ण;

अटल स्थिर u32 jz4755_pull_ups[6] = अणु
	0xffffffff, 0xffffffff, 0x0fffffff, 0xffffffff, 0x33dc3fff, 0x0000fc00,
पूर्ण;

अटल स्थिर u32 jz4755_pull_करोwns[6] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

अटल पूर्णांक jz4755_uart0_data_pins[] = अणु 0x7c, 0x7d, पूर्ण;
अटल पूर्णांक jz4755_uart0_hwflow_pins[] = अणु 0x7e, 0x7f, पूर्ण;
अटल पूर्णांक jz4755_uart1_data_pins[] = अणु 0x97, 0x99, पूर्ण;
अटल पूर्णांक jz4755_uart2_data_pins[] = अणु 0x9f, पूर्ण;
अटल पूर्णांक jz4755_mmc0_1bit_pins[] = अणु 0x2f, 0x50, 0x5c, पूर्ण;
अटल पूर्णांक jz4755_mmc0_4bit_pins[] = अणु 0x5d, 0x5b, 0x51, पूर्ण;
अटल पूर्णांक jz4755_mmc1_1bit_pins[] = अणु 0x3a, 0x3d, 0x3c, पूर्ण;
अटल पूर्णांक jz4755_mmc1_4bit_pins[] = अणु 0x3b, 0x3e, 0x3f, पूर्ण;
अटल पूर्णांक jz4755_i2c_pins[] = अणु 0x8c, 0x8d, पूर्ण;
अटल पूर्णांक jz4755_cim_pins[] = अणु
	0x89, 0x8b, 0x8a, 0x88,
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
पूर्ण;
अटल पूर्णांक jz4755_lcd_8bit_pins[] = अणु
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x72, 0x73, 0x74,
पूर्ण;
अटल पूर्णांक jz4755_lcd_16bit_pins[] = अणु
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
पूर्ण;
अटल पूर्णांक jz4755_lcd_18bit_pins[] = अणु 0x70, 0x71, पूर्ण;
अटल पूर्णांक jz4755_lcd_24bit_pins[] = अणु 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, पूर्ण;
अटल पूर्णांक jz4755_lcd_special_pins[] = अणु 0x76, 0x77, 0x78, 0x79, पूर्ण;
अटल पूर्णांक jz4755_lcd_generic_pins[] = अणु 0x75, पूर्ण;
अटल पूर्णांक jz4755_nand_cs1_pins[] = अणु 0x55, पूर्ण;
अटल पूर्णांक jz4755_nand_cs2_pins[] = अणु 0x56, पूर्ण;
अटल पूर्णांक jz4755_nand_cs3_pins[] = अणु 0x57, पूर्ण;
अटल पूर्णांक jz4755_nand_cs4_pins[] = अणु 0x58, पूर्ण;
अटल पूर्णांक jz4755_nand_fre_fwe_pins[] = अणु 0x5c, 0x5d, पूर्ण;
अटल पूर्णांक jz4755_pwm_pwm0_pins[] = अणु 0x94, पूर्ण;
अटल पूर्णांक jz4755_pwm_pwm1_pins[] = अणु 0xab, पूर्ण;
अटल पूर्णांक jz4755_pwm_pwm2_pins[] = अणु 0x96, पूर्ण;
अटल पूर्णांक jz4755_pwm_pwm3_pins[] = अणु 0x97, पूर्ण;
अटल पूर्णांक jz4755_pwm_pwm4_pins[] = अणु 0x98, पूर्ण;
अटल पूर्णांक jz4755_pwm_pwm5_pins[] = अणु 0x99, पूर्ण;

अटल u8 jz4755_mmc0_1bit_funcs[] = अणु 2, 2, 1, पूर्ण;
अटल u8 jz4755_mmc0_4bit_funcs[] = अणु 1, 0, 1, पूर्ण;
अटल u8 jz4755_lcd_24bit_funcs[] = अणु 1, 1, 1, 1, 0, 0, पूर्ण;

अटल स्थिर काष्ठा group_desc jz4755_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", jz4755_uart0_data, 0),
	INGENIC_PIN_GROUP("uart0-hwflow", jz4755_uart0_hwflow, 0),
	INGENIC_PIN_GROUP("uart1-data", jz4755_uart1_data, 0),
	INGENIC_PIN_GROUP("uart2-data", jz4755_uart2_data, 1),
	INGENIC_PIN_GROUP_FUNCS("mmc0-1bit", jz4755_mmc0_1bit,
				jz4755_mmc0_1bit_funcs),
	INGENIC_PIN_GROUP_FUNCS("mmc0-4bit", jz4755_mmc0_4bit,
				jz4755_mmc0_4bit_funcs),
	INGENIC_PIN_GROUP("mmc1-1bit", jz4755_mmc1_1bit, 1),
	INGENIC_PIN_GROUP("mmc1-4bit", jz4755_mmc1_4bit, 1),
	INGENIC_PIN_GROUP("i2c-data", jz4755_i2c, 0),
	INGENIC_PIN_GROUP("cim-data", jz4755_cim, 0),
	INGENIC_PIN_GROUP("lcd-8bit", jz4755_lcd_8bit, 0),
	INGENIC_PIN_GROUP("lcd-16bit", jz4755_lcd_16bit, 0),
	INGENIC_PIN_GROUP("lcd-18bit", jz4755_lcd_18bit, 0),
	INGENIC_PIN_GROUP_FUNCS("lcd-24bit", jz4755_lcd_24bit,
				jz4755_lcd_24bit_funcs),
	INGENIC_PIN_GROUP("lcd-special", jz4755_lcd_special, 0),
	INGENIC_PIN_GROUP("lcd-generic", jz4755_lcd_generic, 0),
	INGENIC_PIN_GROUP("nand-cs1", jz4755_nand_cs1, 0),
	INGENIC_PIN_GROUP("nand-cs2", jz4755_nand_cs2, 0),
	INGENIC_PIN_GROUP("nand-cs3", jz4755_nand_cs3, 0),
	INGENIC_PIN_GROUP("nand-cs4", jz4755_nand_cs4, 0),
	INGENIC_PIN_GROUP("nand-fre-fwe", jz4755_nand_fre_fwe, 0),
	INGENIC_PIN_GROUP("pwm0", jz4755_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", jz4755_pwm_pwm1, 1),
	INGENIC_PIN_GROUP("pwm2", jz4755_pwm_pwm2, 0),
	INGENIC_PIN_GROUP("pwm3", jz4755_pwm_pwm3, 0),
	INGENIC_PIN_GROUP("pwm4", jz4755_pwm_pwm4, 0),
	INGENIC_PIN_GROUP("pwm5", jz4755_pwm_pwm5, 0),
पूर्ण;

अटल स्थिर अक्षर *jz4755_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4755_uart1_groups[] = अणु "uart1-data", पूर्ण;
अटल स्थिर अक्षर *jz4755_uart2_groups[] = अणु "uart2-data", पूर्ण;
अटल स्थिर अक्षर *jz4755_mmc0_groups[] = अणु "mmc0-1bit", "mmc0-4bit", पूर्ण;
अटल स्थिर अक्षर *jz4755_mmc1_groups[] = अणु "mmc0-1bit", "mmc0-4bit", पूर्ण;
अटल स्थिर अक्षर *jz4755_i2c_groups[] = अणु "i2c-data", पूर्ण;
अटल स्थिर अक्षर *jz4755_cim_groups[] = अणु "cim-data", पूर्ण;
अटल स्थिर अक्षर *jz4755_lcd_groups[] = अणु
	"lcd-8bit", "lcd-16bit", "lcd-18bit", "lcd-24bit",
	"lcd-special", "lcd-generic",
पूर्ण;
अटल स्थिर अक्षर *jz4755_nand_groups[] = अणु
	"nand-cs1", "nand-cs2", "nand-cs3", "nand-cs4", "nand-fre-fwe",
पूर्ण;
अटल स्थिर अक्षर *jz4755_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *jz4755_pwm1_groups[] = अणु "pwm1", पूर्ण;
अटल स्थिर अक्षर *jz4755_pwm2_groups[] = अणु "pwm2", पूर्ण;
अटल स्थिर अक्षर *jz4755_pwm3_groups[] = अणु "pwm3", पूर्ण;
अटल स्थिर अक्षर *jz4755_pwm4_groups[] = अणु "pwm4", पूर्ण;
अटल स्थिर अक्षर *jz4755_pwm5_groups[] = अणु "pwm5", पूर्ण;

अटल स्थिर काष्ठा function_desc jz4755_functions[] = अणु
	अणु "uart0", jz4755_uart0_groups, ARRAY_SIZE(jz4755_uart0_groups), पूर्ण,
	अणु "uart1", jz4755_uart1_groups, ARRAY_SIZE(jz4755_uart1_groups), पूर्ण,
	अणु "uart2", jz4755_uart2_groups, ARRAY_SIZE(jz4755_uart2_groups), पूर्ण,
	अणु "mmc0", jz4755_mmc0_groups, ARRAY_SIZE(jz4755_mmc0_groups), पूर्ण,
	अणु "mmc1", jz4755_mmc1_groups, ARRAY_SIZE(jz4755_mmc1_groups), पूर्ण,
	अणु "i2c", jz4755_i2c_groups, ARRAY_SIZE(jz4755_i2c_groups), पूर्ण,
	अणु "cim", jz4755_cim_groups, ARRAY_SIZE(jz4755_cim_groups), पूर्ण,
	अणु "lcd", jz4755_lcd_groups, ARRAY_SIZE(jz4755_lcd_groups), पूर्ण,
	अणु "nand", jz4755_nand_groups, ARRAY_SIZE(jz4755_nand_groups), पूर्ण,
	अणु "pwm0", jz4755_pwm0_groups, ARRAY_SIZE(jz4755_pwm0_groups), पूर्ण,
	अणु "pwm1", jz4755_pwm1_groups, ARRAY_SIZE(jz4755_pwm1_groups), पूर्ण,
	अणु "pwm2", jz4755_pwm2_groups, ARRAY_SIZE(jz4755_pwm2_groups), पूर्ण,
	अणु "pwm3", jz4755_pwm3_groups, ARRAY_SIZE(jz4755_pwm3_groups), पूर्ण,
	अणु "pwm4", jz4755_pwm4_groups, ARRAY_SIZE(jz4755_pwm4_groups), पूर्ण,
	अणु "pwm5", jz4755_pwm5_groups, ARRAY_SIZE(jz4755_pwm5_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info jz4755_chip_info = अणु
	.num_chips = 6,
	.reg_offset = 0x100,
	.version = ID_JZ4755,
	.groups = jz4755_groups,
	.num_groups = ARRAY_SIZE(jz4755_groups),
	.functions = jz4755_functions,
	.num_functions = ARRAY_SIZE(jz4755_functions),
	.pull_ups = jz4755_pull_ups,
	.pull_करोwns = jz4755_pull_करोwns,
पूर्ण;

अटल स्थिर u32 jz4760_pull_ups[6] = अणु
	0xffffffff, 0xfffcf3ff, 0xffffffff, 0xffffcfff, 0xfffffb7c, 0xfffff00f,
पूर्ण;

अटल स्थिर u32 jz4760_pull_करोwns[6] = अणु
	0x00000000, 0x00030c00, 0x00000000, 0x00003000, 0x00000483, 0x00000ff0,
पूर्ण;

अटल पूर्णांक jz4760_uart0_data_pins[] = अणु 0xa0, 0xa3, पूर्ण;
अटल पूर्णांक jz4760_uart0_hwflow_pins[] = अणु 0xa1, 0xa2, पूर्ण;
अटल पूर्णांक jz4760_uart1_data_pins[] = अणु 0x7a, 0x7c, पूर्ण;
अटल पूर्णांक jz4760_uart1_hwflow_pins[] = अणु 0x7b, 0x7d, पूर्ण;
अटल पूर्णांक jz4760_uart2_data_pins[] = अणु 0x5c, 0x5e, पूर्ण;
अटल पूर्णांक jz4760_uart2_hwflow_pins[] = अणु 0x5d, 0x5f, पूर्ण;
अटल पूर्णांक jz4760_uart3_data_pins[] = अणु 0x6c, 0x85, पूर्ण;
अटल पूर्णांक jz4760_uart3_hwflow_pins[] = अणु 0x88, 0x89, पूर्ण;
अटल पूर्णांक jz4760_mmc0_1bit_a_pins[] = अणु 0x12, 0x13, 0x14, पूर्ण;
अटल पूर्णांक jz4760_mmc0_4bit_a_pins[] = अणु 0x15, 0x16, 0x17, पूर्ण;
अटल पूर्णांक jz4760_mmc0_1bit_e_pins[] = अणु 0x9c, 0x9d, 0x94, पूर्ण;
अटल पूर्णांक jz4760_mmc0_4bit_e_pins[] = अणु 0x95, 0x96, 0x97, पूर्ण;
अटल पूर्णांक jz4760_mmc0_8bit_e_pins[] = अणु 0x98, 0x99, 0x9a, 0x9b, पूर्ण;
अटल पूर्णांक jz4760_mmc1_1bit_d_pins[] = अणु 0x78, 0x79, 0x74, पूर्ण;
अटल पूर्णांक jz4760_mmc1_4bit_d_pins[] = अणु 0x75, 0x76, 0x77, पूर्ण;
अटल पूर्णांक jz4760_mmc1_1bit_e_pins[] = अणु 0x9c, 0x9d, 0x94, पूर्ण;
अटल पूर्णांक jz4760_mmc1_4bit_e_pins[] = अणु 0x95, 0x96, 0x97, पूर्ण;
अटल पूर्णांक jz4760_mmc1_8bit_e_pins[] = अणु 0x98, 0x99, 0x9a, 0x9b, पूर्ण;
अटल पूर्णांक jz4760_mmc2_1bit_b_pins[] = अणु 0x3c, 0x3d, 0x34, पूर्ण;
अटल पूर्णांक jz4760_mmc2_4bit_b_pins[] = अणु 0x35, 0x3e, 0x3f, पूर्ण;
अटल पूर्णांक jz4760_mmc2_1bit_e_pins[] = अणु 0x9c, 0x9d, 0x94, पूर्ण;
अटल पूर्णांक jz4760_mmc2_4bit_e_pins[] = अणु 0x95, 0x96, 0x97, पूर्ण;
अटल पूर्णांक jz4760_mmc2_8bit_e_pins[] = अणु 0x98, 0x99, 0x9a, 0x9b, पूर्ण;
अटल पूर्णांक jz4760_nemc_8bit_data_pins[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
पूर्ण;
अटल पूर्णांक jz4760_nemc_16bit_data_pins[] = अणु
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
पूर्ण;
अटल पूर्णांक jz4760_nemc_cle_ale_pins[] = अणु 0x20, 0x21, पूर्ण;
अटल पूर्णांक jz4760_nemc_addr_pins[] = अणु 0x22, 0x23, 0x24, 0x25, पूर्ण;
अटल पूर्णांक jz4760_nemc_rd_we_pins[] = अणु 0x10, 0x11, पूर्ण;
अटल पूर्णांक jz4760_nemc_frd_fwe_pins[] = अणु 0x12, 0x13, पूर्ण;
अटल पूर्णांक jz4760_nemc_रुको_pins[] = अणु 0x1b, पूर्ण;
अटल पूर्णांक jz4760_nemc_cs1_pins[] = अणु 0x15, पूर्ण;
अटल पूर्णांक jz4760_nemc_cs2_pins[] = अणु 0x16, पूर्ण;
अटल पूर्णांक jz4760_nemc_cs3_pins[] = अणु 0x17, पूर्ण;
अटल पूर्णांक jz4760_nemc_cs4_pins[] = अणु 0x18, पूर्ण;
अटल पूर्णांक jz4760_nemc_cs5_pins[] = अणु 0x19, पूर्ण;
अटल पूर्णांक jz4760_nemc_cs6_pins[] = अणु 0x1a, पूर्ण;
अटल पूर्णांक jz4760_i2c0_pins[] = अणु 0x7e, 0x7f, पूर्ण;
अटल पूर्णांक jz4760_i2c1_pins[] = अणु 0x9e, 0x9f, पूर्ण;
अटल पूर्णांक jz4760_cim_pins[] = अणु
	0x26, 0x27, 0x28, 0x29,
	0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
पूर्ण;
अटल पूर्णांक jz4760_lcd_8bit_pins[] = अणु
	0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x4c,
	0x4d, 0x52, 0x53,
पूर्ण;
अटल पूर्णांक jz4760_lcd_16bit_pins[] = अणु
	0x4e, 0x4f, 0x50, 0x51, 0x56, 0x57, 0x58, 0x59,
पूर्ण;
अटल पूर्णांक jz4760_lcd_18bit_pins[] = अणु
	0x5a, 0x5b,
पूर्ण;
अटल पूर्णांक jz4760_lcd_24bit_pins[] = अणु
	0x40, 0x41, 0x4a, 0x4b, 0x54, 0x55,
पूर्ण;
अटल पूर्णांक jz4760_lcd_special_pins[] = अणु 0x54, 0x4a, 0x41, 0x40, पूर्ण;
अटल पूर्णांक jz4760_lcd_generic_pins[] = अणु 0x49, पूर्ण;
अटल पूर्णांक jz4760_pwm_pwm0_pins[] = अणु 0x80, पूर्ण;
अटल पूर्णांक jz4760_pwm_pwm1_pins[] = अणु 0x81, पूर्ण;
अटल पूर्णांक jz4760_pwm_pwm2_pins[] = अणु 0x82, पूर्ण;
अटल पूर्णांक jz4760_pwm_pwm3_pins[] = अणु 0x83, पूर्ण;
अटल पूर्णांक jz4760_pwm_pwm4_pins[] = अणु 0x84, पूर्ण;
अटल पूर्णांक jz4760_pwm_pwm5_pins[] = अणु 0x85, पूर्ण;
अटल पूर्णांक jz4760_pwm_pwm6_pins[] = अणु 0x6a, पूर्ण;
अटल पूर्णांक jz4760_pwm_pwm7_pins[] = अणु 0x6b, पूर्ण;
अटल पूर्णांक jz4760_otg_pins[] = अणु 0x8a, पूर्ण;

अटल u8 jz4760_uart3_data_funcs[] = अणु 0, 1, पूर्ण;
अटल u8 jz4760_mmc0_1bit_a_funcs[] = अणु 1, 1, 0, पूर्ण;

अटल स्थिर काष्ठा group_desc jz4760_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", jz4760_uart0_data, 0),
	INGENIC_PIN_GROUP("uart0-hwflow", jz4760_uart0_hwflow, 0),
	INGENIC_PIN_GROUP("uart1-data", jz4760_uart1_data, 0),
	INGENIC_PIN_GROUP("uart1-hwflow", jz4760_uart1_hwflow, 0),
	INGENIC_PIN_GROUP("uart2-data", jz4760_uart2_data, 0),
	INGENIC_PIN_GROUP("uart2-hwflow", jz4760_uart2_hwflow, 0),
	INGENIC_PIN_GROUP_FUNCS("uart3-data", jz4760_uart3_data,
				jz4760_uart3_data_funcs),
	INGENIC_PIN_GROUP("uart3-hwflow", jz4760_uart3_hwflow, 0),
	INGENIC_PIN_GROUP_FUNCS("mmc0-1bit-a", jz4760_mmc0_1bit_a,
				jz4760_mmc0_1bit_a_funcs),
	INGENIC_PIN_GROUP("mmc0-4bit-a", jz4760_mmc0_4bit_a, 1),
	INGENIC_PIN_GROUP("mmc0-1bit-e", jz4760_mmc0_1bit_e, 0),
	INGENIC_PIN_GROUP("mmc0-4bit-e", jz4760_mmc0_4bit_e, 0),
	INGENIC_PIN_GROUP("mmc0-8bit-e", jz4760_mmc0_8bit_e, 0),
	INGENIC_PIN_GROUP("mmc1-1bit-d", jz4760_mmc1_1bit_d, 0),
	INGENIC_PIN_GROUP("mmc1-4bit-d", jz4760_mmc1_4bit_d, 0),
	INGENIC_PIN_GROUP("mmc1-1bit-e", jz4760_mmc1_1bit_e, 1),
	INGENIC_PIN_GROUP("mmc1-4bit-e", jz4760_mmc1_4bit_e, 1),
	INGENIC_PIN_GROUP("mmc1-8bit-e", jz4760_mmc1_8bit_e, 1),
	INGENIC_PIN_GROUP("mmc2-1bit-b", jz4760_mmc2_1bit_b, 0),
	INGENIC_PIN_GROUP("mmc2-4bit-b", jz4760_mmc2_4bit_b, 0),
	INGENIC_PIN_GROUP("mmc2-1bit-e", jz4760_mmc2_1bit_e, 2),
	INGENIC_PIN_GROUP("mmc2-4bit-e", jz4760_mmc2_4bit_e, 2),
	INGENIC_PIN_GROUP("mmc2-8bit-e", jz4760_mmc2_8bit_e, 2),
	INGENIC_PIN_GROUP("nemc-8bit-data", jz4760_nemc_8bit_data, 0),
	INGENIC_PIN_GROUP("nemc-16bit-data", jz4760_nemc_16bit_data, 0),
	INGENIC_PIN_GROUP("nemc-cle-ale", jz4760_nemc_cle_ale, 0),
	INGENIC_PIN_GROUP("nemc-addr", jz4760_nemc_addr, 0),
	INGENIC_PIN_GROUP("nemc-rd-we", jz4760_nemc_rd_we, 0),
	INGENIC_PIN_GROUP("nemc-frd-fwe", jz4760_nemc_frd_fwe, 0),
	INGENIC_PIN_GROUP("nemc-wait", jz4760_nemc_रुको, 0),
	INGENIC_PIN_GROUP("nemc-cs1", jz4760_nemc_cs1, 0),
	INGENIC_PIN_GROUP("nemc-cs2", jz4760_nemc_cs2, 0),
	INGENIC_PIN_GROUP("nemc-cs3", jz4760_nemc_cs3, 0),
	INGENIC_PIN_GROUP("nemc-cs4", jz4760_nemc_cs4, 0),
	INGENIC_PIN_GROUP("nemc-cs5", jz4760_nemc_cs5, 0),
	INGENIC_PIN_GROUP("nemc-cs6", jz4760_nemc_cs6, 0),
	INGENIC_PIN_GROUP("i2c0-data", jz4760_i2c0, 0),
	INGENIC_PIN_GROUP("i2c1-data", jz4760_i2c1, 0),
	INGENIC_PIN_GROUP("cim-data", jz4760_cim, 0),
	INGENIC_PIN_GROUP("lcd-8bit", jz4760_lcd_8bit, 0),
	INGENIC_PIN_GROUP("lcd-16bit", jz4760_lcd_16bit, 0),
	INGENIC_PIN_GROUP("lcd-18bit", jz4760_lcd_18bit, 0),
	INGENIC_PIN_GROUP("lcd-24bit", jz4760_lcd_24bit, 0),
	INGENIC_PIN_GROUP("lcd-special", jz4760_lcd_special, 1),
	INGENIC_PIN_GROUP("lcd-generic", jz4760_lcd_generic, 0),
	INGENIC_PIN_GROUP("pwm0", jz4760_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", jz4760_pwm_pwm1, 0),
	INGENIC_PIN_GROUP("pwm2", jz4760_pwm_pwm2, 0),
	INGENIC_PIN_GROUP("pwm3", jz4760_pwm_pwm3, 0),
	INGENIC_PIN_GROUP("pwm4", jz4760_pwm_pwm4, 0),
	INGENIC_PIN_GROUP("pwm5", jz4760_pwm_pwm5, 0),
	INGENIC_PIN_GROUP("pwm6", jz4760_pwm_pwm6, 0),
	INGENIC_PIN_GROUP("pwm7", jz4760_pwm_pwm7, 0),
	INGENIC_PIN_GROUP("otg-vbus", jz4760_otg, 0),
पूर्ण;

अटल स्थिर अक्षर *jz4760_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4760_uart1_groups[] = अणु "uart1-data", "uart1-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4760_uart2_groups[] = अणु "uart2-data", "uart2-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4760_uart3_groups[] = अणु "uart3-data", "uart3-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4760_mmc0_groups[] = अणु
	"mmc0-1bit-a", "mmc0-4bit-a",
	"mmc0-1bit-e", "mmc0-4bit-e", "mmc0-8bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4760_mmc1_groups[] = अणु
	"mmc1-1bit-d", "mmc1-4bit-d",
	"mmc1-1bit-e", "mmc1-4bit-e", "mmc1-8bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4760_mmc2_groups[] = अणु
	"mmc2-1bit-b", "mmc2-4bit-b",
	"mmc2-1bit-e", "mmc2-4bit-e", "mmc2-8bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4760_nemc_groups[] = अणु
	"nemc-8bit-data", "nemc-16bit-data", "nemc-cle-ale",
	"nemc-addr", "nemc-rd-we", "nemc-frd-fwe", "nemc-wait",
पूर्ण;
अटल स्थिर अक्षर *jz4760_cs1_groups[] = अणु "nemc-cs1", पूर्ण;
अटल स्थिर अक्षर *jz4760_cs2_groups[] = अणु "nemc-cs2", पूर्ण;
अटल स्थिर अक्षर *jz4760_cs3_groups[] = अणु "nemc-cs3", पूर्ण;
अटल स्थिर अक्षर *jz4760_cs4_groups[] = अणु "nemc-cs4", पूर्ण;
अटल स्थिर अक्षर *jz4760_cs5_groups[] = अणु "nemc-cs5", पूर्ण;
अटल स्थिर अक्षर *jz4760_cs6_groups[] = अणु "nemc-cs6", पूर्ण;
अटल स्थिर अक्षर *jz4760_i2c0_groups[] = अणु "i2c0-data", पूर्ण;
अटल स्थिर अक्षर *jz4760_i2c1_groups[] = अणु "i2c1-data", पूर्ण;
अटल स्थिर अक्षर *jz4760_cim_groups[] = अणु "cim-data", पूर्ण;
अटल स्थिर अक्षर *jz4760_lcd_groups[] = अणु
	"lcd-8bit", "lcd-16bit", "lcd-18bit", "lcd-24bit",
	"lcd-special", "lcd-generic",
पूर्ण;
अटल स्थिर अक्षर *jz4760_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *jz4760_pwm1_groups[] = अणु "pwm1", पूर्ण;
अटल स्थिर अक्षर *jz4760_pwm2_groups[] = अणु "pwm2", पूर्ण;
अटल स्थिर अक्षर *jz4760_pwm3_groups[] = अणु "pwm3", पूर्ण;
अटल स्थिर अक्षर *jz4760_pwm4_groups[] = अणु "pwm4", पूर्ण;
अटल स्थिर अक्षर *jz4760_pwm5_groups[] = अणु "pwm5", पूर्ण;
अटल स्थिर अक्षर *jz4760_pwm6_groups[] = अणु "pwm6", पूर्ण;
अटल स्थिर अक्षर *jz4760_pwm7_groups[] = अणु "pwm7", पूर्ण;
अटल स्थिर अक्षर *jz4760_otg_groups[] = अणु "otg-vbus", पूर्ण;

अटल स्थिर काष्ठा function_desc jz4760_functions[] = अणु
	अणु "uart0", jz4760_uart0_groups, ARRAY_SIZE(jz4760_uart0_groups), पूर्ण,
	अणु "uart1", jz4760_uart1_groups, ARRAY_SIZE(jz4760_uart1_groups), पूर्ण,
	अणु "uart2", jz4760_uart2_groups, ARRAY_SIZE(jz4760_uart2_groups), पूर्ण,
	अणु "uart3", jz4760_uart3_groups, ARRAY_SIZE(jz4760_uart3_groups), पूर्ण,
	अणु "mmc0", jz4760_mmc0_groups, ARRAY_SIZE(jz4760_mmc0_groups), पूर्ण,
	अणु "mmc1", jz4760_mmc1_groups, ARRAY_SIZE(jz4760_mmc1_groups), पूर्ण,
	अणु "mmc2", jz4760_mmc2_groups, ARRAY_SIZE(jz4760_mmc2_groups), पूर्ण,
	अणु "nemc", jz4760_nemc_groups, ARRAY_SIZE(jz4760_nemc_groups), पूर्ण,
	अणु "nemc-cs1", jz4760_cs1_groups, ARRAY_SIZE(jz4760_cs1_groups), पूर्ण,
	अणु "nemc-cs2", jz4760_cs2_groups, ARRAY_SIZE(jz4760_cs2_groups), पूर्ण,
	अणु "nemc-cs3", jz4760_cs3_groups, ARRAY_SIZE(jz4760_cs3_groups), पूर्ण,
	अणु "nemc-cs4", jz4760_cs4_groups, ARRAY_SIZE(jz4760_cs4_groups), पूर्ण,
	अणु "nemc-cs5", jz4760_cs5_groups, ARRAY_SIZE(jz4760_cs5_groups), पूर्ण,
	अणु "nemc-cs6", jz4760_cs6_groups, ARRAY_SIZE(jz4760_cs6_groups), पूर्ण,
	अणु "i2c0", jz4760_i2c0_groups, ARRAY_SIZE(jz4760_i2c0_groups), पूर्ण,
	अणु "i2c1", jz4760_i2c1_groups, ARRAY_SIZE(jz4760_i2c1_groups), पूर्ण,
	अणु "cim", jz4760_cim_groups, ARRAY_SIZE(jz4760_cim_groups), पूर्ण,
	अणु "lcd", jz4760_lcd_groups, ARRAY_SIZE(jz4760_lcd_groups), पूर्ण,
	अणु "pwm0", jz4760_pwm0_groups, ARRAY_SIZE(jz4760_pwm0_groups), पूर्ण,
	अणु "pwm1", jz4760_pwm1_groups, ARRAY_SIZE(jz4760_pwm1_groups), पूर्ण,
	अणु "pwm2", jz4760_pwm2_groups, ARRAY_SIZE(jz4760_pwm2_groups), पूर्ण,
	अणु "pwm3", jz4760_pwm3_groups, ARRAY_SIZE(jz4760_pwm3_groups), पूर्ण,
	अणु "pwm4", jz4760_pwm4_groups, ARRAY_SIZE(jz4760_pwm4_groups), पूर्ण,
	अणु "pwm5", jz4760_pwm5_groups, ARRAY_SIZE(jz4760_pwm5_groups), पूर्ण,
	अणु "pwm6", jz4760_pwm6_groups, ARRAY_SIZE(jz4760_pwm6_groups), पूर्ण,
	अणु "pwm7", jz4760_pwm7_groups, ARRAY_SIZE(jz4760_pwm7_groups), पूर्ण,
	अणु "otg", jz4760_otg_groups, ARRAY_SIZE(jz4760_otg_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info jz4760_chip_info = अणु
	.num_chips = 6,
	.reg_offset = 0x100,
	.version = ID_JZ4760,
	.groups = jz4760_groups,
	.num_groups = ARRAY_SIZE(jz4760_groups),
	.functions = jz4760_functions,
	.num_functions = ARRAY_SIZE(jz4760_functions),
	.pull_ups = jz4760_pull_ups,
	.pull_करोwns = jz4760_pull_करोwns,
पूर्ण;

अटल स्थिर u32 jz4770_pull_ups[6] = अणु
	0x3fffffff, 0xfff0030c, 0xffffffff, 0xffff4fff, 0xfffffb7c, 0xffa7f00f,
पूर्ण;

अटल स्थिर u32 jz4770_pull_करोwns[6] = अणु
	0x00000000, 0x000f0c03, 0x00000000, 0x0000b000, 0x00000483, 0x00580ff0,
पूर्ण;

अटल पूर्णांक jz4770_uart0_data_pins[] = अणु 0xa0, 0xa3, पूर्ण;
अटल पूर्णांक jz4770_uart0_hwflow_pins[] = अणु 0xa1, 0xa2, पूर्ण;
अटल पूर्णांक jz4770_uart1_data_pins[] = अणु 0x7a, 0x7c, पूर्ण;
अटल पूर्णांक jz4770_uart1_hwflow_pins[] = अणु 0x7b, 0x7d, पूर्ण;
अटल पूर्णांक jz4770_uart2_data_pins[] = अणु 0x5c, 0x5e, पूर्ण;
अटल पूर्णांक jz4770_uart2_hwflow_pins[] = अणु 0x5d, 0x5f, पूर्ण;
अटल पूर्णांक jz4770_uart3_data_pins[] = अणु 0x6c, 0x85, पूर्ण;
अटल पूर्णांक jz4770_uart3_hwflow_pins[] = अणु 0x88, 0x89, पूर्ण;
अटल पूर्णांक jz4770_ssi0_dt_a_pins[] = अणु 0x15, पूर्ण;
अटल पूर्णांक jz4770_ssi0_dt_b_pins[] = अणु 0x35, पूर्ण;
अटल पूर्णांक jz4770_ssi0_dt_d_pins[] = अणु 0x75, पूर्ण;
अटल पूर्णांक jz4770_ssi0_dt_e_pins[] = अणु 0x91, पूर्ण;
अटल पूर्णांक jz4770_ssi0_dr_a_pins[] = अणु 0x14, पूर्ण;
अटल पूर्णांक jz4770_ssi0_dr_b_pins[] = अणु 0x34, पूर्ण;
अटल पूर्णांक jz4770_ssi0_dr_d_pins[] = अणु 0x74, पूर्ण;
अटल पूर्णांक jz4770_ssi0_dr_e_pins[] = अणु 0x8e, पूर्ण;
अटल पूर्णांक jz4770_ssi0_clk_a_pins[] = अणु 0x12, पूर्ण;
अटल पूर्णांक jz4770_ssi0_clk_b_pins[] = अणु 0x3c, पूर्ण;
अटल पूर्णांक jz4770_ssi0_clk_d_pins[] = अणु 0x78, पूर्ण;
अटल पूर्णांक jz4770_ssi0_clk_e_pins[] = अणु 0x8f, पूर्ण;
अटल पूर्णांक jz4770_ssi0_gpc_b_pins[] = अणु 0x3e, पूर्ण;
अटल पूर्णांक jz4770_ssi0_gpc_d_pins[] = अणु 0x76, पूर्ण;
अटल पूर्णांक jz4770_ssi0_gpc_e_pins[] = अणु 0x93, पूर्ण;
अटल पूर्णांक jz4770_ssi0_ce0_a_pins[] = अणु 0x13, पूर्ण;
अटल पूर्णांक jz4770_ssi0_ce0_b_pins[] = अणु 0x3d, पूर्ण;
अटल पूर्णांक jz4770_ssi0_ce0_d_pins[] = अणु 0x79, पूर्ण;
अटल पूर्णांक jz4770_ssi0_ce0_e_pins[] = अणु 0x90, पूर्ण;
अटल पूर्णांक jz4770_ssi0_ce1_b_pins[] = अणु 0x3f, पूर्ण;
अटल पूर्णांक jz4770_ssi0_ce1_d_pins[] = अणु 0x77, पूर्ण;
अटल पूर्णांक jz4770_ssi0_ce1_e_pins[] = अणु 0x92, पूर्ण;
अटल पूर्णांक jz4770_ssi1_dt_b_pins[] = अणु 0x35, पूर्ण;
अटल पूर्णांक jz4770_ssi1_dt_d_pins[] = अणु 0x75, पूर्ण;
अटल पूर्णांक jz4770_ssi1_dt_e_pins[] = अणु 0x91, पूर्ण;
अटल पूर्णांक jz4770_ssi1_dr_b_pins[] = अणु 0x34, पूर्ण;
अटल पूर्णांक jz4770_ssi1_dr_d_pins[] = अणु 0x74, पूर्ण;
अटल पूर्णांक jz4770_ssi1_dr_e_pins[] = अणु 0x8e, पूर्ण;
अटल पूर्णांक jz4770_ssi1_clk_b_pins[] = अणु 0x3c, पूर्ण;
अटल पूर्णांक jz4770_ssi1_clk_d_pins[] = अणु 0x78, पूर्ण;
अटल पूर्णांक jz4770_ssi1_clk_e_pins[] = अणु 0x8f, पूर्ण;
अटल पूर्णांक jz4770_ssi1_gpc_b_pins[] = अणु 0x3e, पूर्ण;
अटल पूर्णांक jz4770_ssi1_gpc_d_pins[] = अणु 0x76, पूर्ण;
अटल पूर्णांक jz4770_ssi1_gpc_e_pins[] = अणु 0x93, पूर्ण;
अटल पूर्णांक jz4770_ssi1_ce0_b_pins[] = अणु 0x3d, पूर्ण;
अटल पूर्णांक jz4770_ssi1_ce0_d_pins[] = अणु 0x79, पूर्ण;
अटल पूर्णांक jz4770_ssi1_ce0_e_pins[] = अणु 0x90, पूर्ण;
अटल पूर्णांक jz4770_ssi1_ce1_b_pins[] = अणु 0x3f, पूर्ण;
अटल पूर्णांक jz4770_ssi1_ce1_d_pins[] = अणु 0x77, पूर्ण;
अटल पूर्णांक jz4770_ssi1_ce1_e_pins[] = अणु 0x92, पूर्ण;
अटल पूर्णांक jz4770_mmc0_1bit_a_pins[] = अणु 0x12, 0x13, 0x14, पूर्ण;
अटल पूर्णांक jz4770_mmc0_4bit_a_pins[] = अणु 0x15, 0x16, 0x17, पूर्ण;
अटल पूर्णांक jz4770_mmc0_1bit_e_pins[] = अणु 0x9c, 0x9d, 0x94, पूर्ण;
अटल पूर्णांक jz4770_mmc0_4bit_e_pins[] = अणु 0x95, 0x96, 0x97, पूर्ण;
अटल पूर्णांक jz4770_mmc0_8bit_e_pins[] = अणु 0x98, 0x99, 0x9a, 0x9b, पूर्ण;
अटल पूर्णांक jz4770_mmc1_1bit_d_pins[] = अणु 0x78, 0x79, 0x74, पूर्ण;
अटल पूर्णांक jz4770_mmc1_4bit_d_pins[] = अणु 0x75, 0x76, 0x77, पूर्ण;
अटल पूर्णांक jz4770_mmc1_1bit_e_pins[] = अणु 0x9c, 0x9d, 0x94, पूर्ण;
अटल पूर्णांक jz4770_mmc1_4bit_e_pins[] = अणु 0x95, 0x96, 0x97, पूर्ण;
अटल पूर्णांक jz4770_mmc1_8bit_e_pins[] = अणु 0x98, 0x99, 0x9a, 0x9b, पूर्ण;
अटल पूर्णांक jz4770_mmc2_1bit_b_pins[] = अणु 0x3c, 0x3d, 0x34, पूर्ण;
अटल पूर्णांक jz4770_mmc2_4bit_b_pins[] = अणु 0x35, 0x3e, 0x3f, पूर्ण;
अटल पूर्णांक jz4770_mmc2_1bit_e_pins[] = अणु 0x9c, 0x9d, 0x94, पूर्ण;
अटल पूर्णांक jz4770_mmc2_4bit_e_pins[] = अणु 0x95, 0x96, 0x97, पूर्ण;
अटल पूर्णांक jz4770_mmc2_8bit_e_pins[] = अणु 0x98, 0x99, 0x9a, 0x9b, पूर्ण;
अटल पूर्णांक jz4770_nemc_8bit_data_pins[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
पूर्ण;
अटल पूर्णांक jz4770_nemc_16bit_data_pins[] = अणु
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
पूर्ण;
अटल पूर्णांक jz4770_nemc_cle_ale_pins[] = अणु 0x20, 0x21, पूर्ण;
अटल पूर्णांक jz4770_nemc_addr_pins[] = अणु 0x22, 0x23, 0x24, 0x25, पूर्ण;
अटल पूर्णांक jz4770_nemc_rd_we_pins[] = अणु 0x10, 0x11, पूर्ण;
अटल पूर्णांक jz4770_nemc_frd_fwe_pins[] = अणु 0x12, 0x13, पूर्ण;
अटल पूर्णांक jz4770_nemc_रुको_pins[] = अणु 0x1b, पूर्ण;
अटल पूर्णांक jz4770_nemc_cs1_pins[] = अणु 0x15, पूर्ण;
अटल पूर्णांक jz4770_nemc_cs2_pins[] = अणु 0x16, पूर्ण;
अटल पूर्णांक jz4770_nemc_cs3_pins[] = अणु 0x17, पूर्ण;
अटल पूर्णांक jz4770_nemc_cs4_pins[] = अणु 0x18, पूर्ण;
अटल पूर्णांक jz4770_nemc_cs5_pins[] = अणु 0x19, पूर्ण;
अटल पूर्णांक jz4770_nemc_cs6_pins[] = अणु 0x1a, पूर्ण;
अटल पूर्णांक jz4770_i2c0_pins[] = अणु 0x7e, 0x7f, पूर्ण;
अटल पूर्णांक jz4770_i2c1_pins[] = अणु 0x9e, 0x9f, पूर्ण;
अटल पूर्णांक jz4770_i2c2_pins[] = अणु 0xb0, 0xb1, पूर्ण;
अटल पूर्णांक jz4770_cim_8bit_pins[] = अणु
	0x26, 0x27, 0x28, 0x29,
	0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
पूर्ण;
अटल पूर्णांक jz4770_cim_12bit_pins[] = अणु
	0x32, 0x33, 0xb0, 0xb1,
पूर्ण;
अटल पूर्णांक jz4770_lcd_8bit_pins[] = अणु
	0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x4c, 0x4d,
	0x48, 0x52, 0x53,
पूर्ण;
अटल पूर्णांक jz4770_lcd_16bit_pins[] = अणु
	0x4e, 0x4f, 0x50, 0x51, 0x56, 0x57, 0x58, 0x59,
पूर्ण;
अटल पूर्णांक jz4770_lcd_18bit_pins[] = अणु
	0x5a, 0x5b,
पूर्ण;
अटल पूर्णांक jz4770_lcd_24bit_pins[] = अणु
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
	0x58, 0x59, 0x5a, 0x5b,
पूर्ण;
अटल पूर्णांक jz4770_lcd_special_pins[] = अणु 0x54, 0x4a, 0x41, 0x40, पूर्ण;
अटल पूर्णांक jz4770_lcd_generic_pins[] = अणु 0x49, पूर्ण;
अटल पूर्णांक jz4770_pwm_pwm0_pins[] = अणु 0x80, पूर्ण;
अटल पूर्णांक jz4770_pwm_pwm1_pins[] = अणु 0x81, पूर्ण;
अटल पूर्णांक jz4770_pwm_pwm2_pins[] = अणु 0x82, पूर्ण;
अटल पूर्णांक jz4770_pwm_pwm3_pins[] = अणु 0x83, पूर्ण;
अटल पूर्णांक jz4770_pwm_pwm4_pins[] = अणु 0x84, पूर्ण;
अटल पूर्णांक jz4770_pwm_pwm5_pins[] = अणु 0x85, पूर्ण;
अटल पूर्णांक jz4770_pwm_pwm6_pins[] = अणु 0x6a, पूर्ण;
अटल पूर्णांक jz4770_pwm_pwm7_pins[] = अणु 0x6b, पूर्ण;
अटल पूर्णांक jz4770_mac_rmii_pins[] = अणु
	0xa9, 0xab, 0xaa, 0xac, 0xa5, 0xa4, 0xad, 0xae, 0xa6, 0xa8,
पूर्ण;
अटल पूर्णांक jz4770_mac_mii_pins[] = अणु
	0x7b, 0x7a, 0x7d, 0x7c, 0xa7, 0x24, 0xaf,
पूर्ण;

अटल स्थिर काष्ठा group_desc jz4770_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", jz4770_uart0_data, 0),
	INGENIC_PIN_GROUP("uart0-hwflow", jz4770_uart0_hwflow, 0),
	INGENIC_PIN_GROUP("uart1-data", jz4770_uart1_data, 0),
	INGENIC_PIN_GROUP("uart1-hwflow", jz4770_uart1_hwflow, 0),
	INGENIC_PIN_GROUP("uart2-data", jz4770_uart2_data, 0),
	INGENIC_PIN_GROUP("uart2-hwflow", jz4770_uart2_hwflow, 0),
	INGENIC_PIN_GROUP_FUNCS("uart3-data", jz4770_uart3_data,
				jz4760_uart3_data_funcs),
	INGENIC_PIN_GROUP("uart3-hwflow", jz4770_uart3_hwflow, 0),
	INGENIC_PIN_GROUP("ssi0-dt-a", jz4770_ssi0_dt_a, 2),
	INGENIC_PIN_GROUP("ssi0-dt-b", jz4770_ssi0_dt_b, 1),
	INGENIC_PIN_GROUP("ssi0-dt-d", jz4770_ssi0_dt_d, 1),
	INGENIC_PIN_GROUP("ssi0-dt-e", jz4770_ssi0_dt_e, 0),
	INGENIC_PIN_GROUP("ssi0-dr-a", jz4770_ssi0_dr_a, 1),
	INGENIC_PIN_GROUP("ssi0-dr-b", jz4770_ssi0_dr_b, 1),
	INGENIC_PIN_GROUP("ssi0-dr-d", jz4770_ssi0_dr_d, 1),
	INGENIC_PIN_GROUP("ssi0-dr-e", jz4770_ssi0_dr_e, 0),
	INGENIC_PIN_GROUP("ssi0-clk-a", jz4770_ssi0_clk_a, 2),
	INGENIC_PIN_GROUP("ssi0-clk-b", jz4770_ssi0_clk_b, 1),
	INGENIC_PIN_GROUP("ssi0-clk-d", jz4770_ssi0_clk_d, 1),
	INGENIC_PIN_GROUP("ssi0-clk-e", jz4770_ssi0_clk_e, 0),
	INGENIC_PIN_GROUP("ssi0-gpc-b", jz4770_ssi0_gpc_b, 1),
	INGENIC_PIN_GROUP("ssi0-gpc-d", jz4770_ssi0_gpc_d, 1),
	INGENIC_PIN_GROUP("ssi0-gpc-e", jz4770_ssi0_gpc_e, 0),
	INGENIC_PIN_GROUP("ssi0-ce0-a", jz4770_ssi0_ce0_a, 2),
	INGENIC_PIN_GROUP("ssi0-ce0-b", jz4770_ssi0_ce0_b, 1),
	INGENIC_PIN_GROUP("ssi0-ce0-d", jz4770_ssi0_ce0_d, 1),
	INGENIC_PIN_GROUP("ssi0-ce0-e", jz4770_ssi0_ce0_e, 0),
	INGENIC_PIN_GROUP("ssi0-ce1-b", jz4770_ssi0_ce1_b, 1),
	INGENIC_PIN_GROUP("ssi0-ce1-d", jz4770_ssi0_ce1_d, 1),
	INGENIC_PIN_GROUP("ssi0-ce1-e", jz4770_ssi0_ce1_e, 0),
	INGENIC_PIN_GROUP("ssi1-dt-b", jz4770_ssi1_dt_b, 2),
	INGENIC_PIN_GROUP("ssi1-dt-d", jz4770_ssi1_dt_d, 2),
	INGENIC_PIN_GROUP("ssi1-dt-e", jz4770_ssi1_dt_e, 1),
	INGENIC_PIN_GROUP("ssi1-dr-b", jz4770_ssi1_dr_b, 2),
	INGENIC_PIN_GROUP("ssi1-dr-d", jz4770_ssi1_dr_d, 2),
	INGENIC_PIN_GROUP("ssi1-dr-e", jz4770_ssi1_dr_e, 1),
	INGENIC_PIN_GROUP("ssi1-clk-b", jz4770_ssi1_clk_b, 2),
	INGENIC_PIN_GROUP("ssi1-clk-d", jz4770_ssi1_clk_d, 2),
	INGENIC_PIN_GROUP("ssi1-clk-e", jz4770_ssi1_clk_e, 1),
	INGENIC_PIN_GROUP("ssi1-gpc-b", jz4770_ssi1_gpc_b, 2),
	INGENIC_PIN_GROUP("ssi1-gpc-d", jz4770_ssi1_gpc_d, 2),
	INGENIC_PIN_GROUP("ssi1-gpc-e", jz4770_ssi1_gpc_e, 1),
	INGENIC_PIN_GROUP("ssi1-ce0-b", jz4770_ssi1_ce0_b, 2),
	INGENIC_PIN_GROUP("ssi1-ce0-d", jz4770_ssi1_ce0_d, 2),
	INGENIC_PIN_GROUP("ssi1-ce0-e", jz4770_ssi1_ce0_e, 1),
	INGENIC_PIN_GROUP("ssi1-ce1-b", jz4770_ssi1_ce1_b, 2),
	INGENIC_PIN_GROUP("ssi1-ce1-d", jz4770_ssi1_ce1_d, 2),
	INGENIC_PIN_GROUP("ssi1-ce1-e", jz4770_ssi1_ce1_e, 1),
	INGENIC_PIN_GROUP_FUNCS("mmc0-1bit-a", jz4770_mmc0_1bit_a,
				jz4760_mmc0_1bit_a_funcs),
	INGENIC_PIN_GROUP("mmc0-4bit-a", jz4770_mmc0_4bit_a, 1),
	INGENIC_PIN_GROUP("mmc0-1bit-e", jz4770_mmc0_1bit_e, 0),
	INGENIC_PIN_GROUP("mmc0-4bit-e", jz4770_mmc0_4bit_e, 0),
	INGENIC_PIN_GROUP("mmc0-8bit-e", jz4770_mmc0_8bit_e, 0),
	INGENIC_PIN_GROUP("mmc1-1bit-d", jz4770_mmc1_1bit_d, 0),
	INGENIC_PIN_GROUP("mmc1-4bit-d", jz4770_mmc1_4bit_d, 0),
	INGENIC_PIN_GROUP("mmc1-1bit-e", jz4770_mmc1_1bit_e, 1),
	INGENIC_PIN_GROUP("mmc1-4bit-e", jz4770_mmc1_4bit_e, 1),
	INGENIC_PIN_GROUP("mmc1-8bit-e", jz4770_mmc1_8bit_e, 1),
	INGENIC_PIN_GROUP("mmc2-1bit-b", jz4770_mmc2_1bit_b, 0),
	INGENIC_PIN_GROUP("mmc2-4bit-b", jz4770_mmc2_4bit_b, 0),
	INGENIC_PIN_GROUP("mmc2-1bit-e", jz4770_mmc2_1bit_e, 2),
	INGENIC_PIN_GROUP("mmc2-4bit-e", jz4770_mmc2_4bit_e, 2),
	INGENIC_PIN_GROUP("mmc2-8bit-e", jz4770_mmc2_8bit_e, 2),
	INGENIC_PIN_GROUP("nemc-8bit-data", jz4770_nemc_8bit_data, 0),
	INGENIC_PIN_GROUP("nemc-16bit-data", jz4770_nemc_16bit_data, 0),
	INGENIC_PIN_GROUP("nemc-cle-ale", jz4770_nemc_cle_ale, 0),
	INGENIC_PIN_GROUP("nemc-addr", jz4770_nemc_addr, 0),
	INGENIC_PIN_GROUP("nemc-rd-we", jz4770_nemc_rd_we, 0),
	INGENIC_PIN_GROUP("nemc-frd-fwe", jz4770_nemc_frd_fwe, 0),
	INGENIC_PIN_GROUP("nemc-wait", jz4770_nemc_रुको, 0),
	INGENIC_PIN_GROUP("nemc-cs1", jz4770_nemc_cs1, 0),
	INGENIC_PIN_GROUP("nemc-cs2", jz4770_nemc_cs2, 0),
	INGENIC_PIN_GROUP("nemc-cs3", jz4770_nemc_cs3, 0),
	INGENIC_PIN_GROUP("nemc-cs4", jz4770_nemc_cs4, 0),
	INGENIC_PIN_GROUP("nemc-cs5", jz4770_nemc_cs5, 0),
	INGENIC_PIN_GROUP("nemc-cs6", jz4770_nemc_cs6, 0),
	INGENIC_PIN_GROUP("i2c0-data", jz4770_i2c0, 0),
	INGENIC_PIN_GROUP("i2c1-data", jz4770_i2c1, 0),
	INGENIC_PIN_GROUP("i2c2-data", jz4770_i2c2, 2),
	INGENIC_PIN_GROUP("cim-data-8bit", jz4770_cim_8bit, 0),
	INGENIC_PIN_GROUP("cim-data-12bit", jz4770_cim_12bit, 0),
	INGENIC_PIN_GROUP("lcd-8bit", jz4770_lcd_8bit, 0),
	INGENIC_PIN_GROUP("lcd-16bit", jz4770_lcd_16bit, 0),
	INGENIC_PIN_GROUP("lcd-18bit", jz4770_lcd_18bit, 0),
	INGENIC_PIN_GROUP("lcd-24bit", jz4770_lcd_24bit, 0),
	INGENIC_PIN_GROUP("lcd-special", jz4770_lcd_special, 1),
	INGENIC_PIN_GROUP("lcd-generic", jz4770_lcd_generic, 0),
	INGENIC_PIN_GROUP("pwm0", jz4770_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", jz4770_pwm_pwm1, 0),
	INGENIC_PIN_GROUP("pwm2", jz4770_pwm_pwm2, 0),
	INGENIC_PIN_GROUP("pwm3", jz4770_pwm_pwm3, 0),
	INGENIC_PIN_GROUP("pwm4", jz4770_pwm_pwm4, 0),
	INGENIC_PIN_GROUP("pwm5", jz4770_pwm_pwm5, 0),
	INGENIC_PIN_GROUP("pwm6", jz4770_pwm_pwm6, 0),
	INGENIC_PIN_GROUP("pwm7", jz4770_pwm_pwm7, 0),
	INGENIC_PIN_GROUP("mac-rmii", jz4770_mac_rmii, 0),
	INGENIC_PIN_GROUP("mac-mii", jz4770_mac_mii, 0),
	INGENIC_PIN_GROUP("otg-vbus", jz4760_otg, 0),
पूर्ण;

अटल स्थिर अक्षर *jz4770_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4770_uart1_groups[] = अणु "uart1-data", "uart1-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4770_uart2_groups[] = अणु "uart2-data", "uart2-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4770_uart3_groups[] = अणु "uart3-data", "uart3-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4770_ssi0_groups[] = अणु
	"ssi0-dt-a", "ssi0-dt-b", "ssi0-dt-d", "ssi0-dt-e",
	"ssi0-dr-a", "ssi0-dr-b", "ssi0-dr-d", "ssi0-dr-e",
	"ssi0-clk-a", "ssi0-clk-b", "ssi0-clk-d", "ssi0-clk-e",
	"ssi0-gpc-b", "ssi0-gpc-d", "ssi0-gpc-e",
	"ssi0-ce0-a", "ssi0-ce0-b", "ssi0-ce0-d", "ssi0-ce0-e",
	"ssi0-ce1-b", "ssi0-ce1-d", "ssi0-ce1-e",
पूर्ण;
अटल स्थिर अक्षर *jz4770_ssi1_groups[] = अणु
	"ssi1-dt-b", "ssi1-dt-d", "ssi1-dt-e",
	"ssi1-dr-b", "ssi1-dr-d", "ssi1-dr-e",
	"ssi1-clk-b", "ssi1-clk-d", "ssi1-clk-e",
	"ssi1-gpc-b", "ssi1-gpc-d", "ssi1-gpc-e",
	"ssi1-ce0-b", "ssi1-ce0-d", "ssi1-ce0-e",
	"ssi1-ce1-b", "ssi1-ce1-d", "ssi1-ce1-e",
पूर्ण;
अटल स्थिर अक्षर *jz4770_mmc0_groups[] = अणु
	"mmc0-1bit-a", "mmc0-4bit-a",
	"mmc0-1bit-e", "mmc0-4bit-e", "mmc0-8bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4770_mmc1_groups[] = अणु
	"mmc1-1bit-d", "mmc1-4bit-d",
	"mmc1-1bit-e", "mmc1-4bit-e", "mmc1-8bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4770_mmc2_groups[] = अणु
	"mmc2-1bit-b", "mmc2-4bit-b",
	"mmc2-1bit-e", "mmc2-4bit-e", "mmc2-8bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4770_nemc_groups[] = अणु
	"nemc-8bit-data", "nemc-16bit-data", "nemc-cle-ale",
	"nemc-addr", "nemc-rd-we", "nemc-frd-fwe", "nemc-wait",
पूर्ण;
अटल स्थिर अक्षर *jz4770_cs1_groups[] = अणु "nemc-cs1", पूर्ण;
अटल स्थिर अक्षर *jz4770_cs2_groups[] = अणु "nemc-cs2", पूर्ण;
अटल स्थिर अक्षर *jz4770_cs3_groups[] = अणु "nemc-cs3", पूर्ण;
अटल स्थिर अक्षर *jz4770_cs4_groups[] = अणु "nemc-cs4", पूर्ण;
अटल स्थिर अक्षर *jz4770_cs5_groups[] = अणु "nemc-cs5", पूर्ण;
अटल स्थिर अक्षर *jz4770_cs6_groups[] = अणु "nemc-cs6", पूर्ण;
अटल स्थिर अक्षर *jz4770_i2c0_groups[] = अणु "i2c0-data", पूर्ण;
अटल स्थिर अक्षर *jz4770_i2c1_groups[] = अणु "i2c1-data", पूर्ण;
अटल स्थिर अक्षर *jz4770_i2c2_groups[] = अणु "i2c2-data", पूर्ण;
अटल स्थिर अक्षर *jz4770_cim_groups[] = अणु "cim-data-8bit", "cim-data-12bit", पूर्ण;
अटल स्थिर अक्षर *jz4770_lcd_groups[] = अणु
	"lcd-8bit", "lcd-16bit", "lcd-18bit", "lcd-24bit",
	"lcd-special", "lcd-generic",
पूर्ण;
अटल स्थिर अक्षर *jz4770_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *jz4770_pwm1_groups[] = अणु "pwm1", पूर्ण;
अटल स्थिर अक्षर *jz4770_pwm2_groups[] = अणु "pwm2", पूर्ण;
अटल स्थिर अक्षर *jz4770_pwm3_groups[] = अणु "pwm3", पूर्ण;
अटल स्थिर अक्षर *jz4770_pwm4_groups[] = अणु "pwm4", पूर्ण;
अटल स्थिर अक्षर *jz4770_pwm5_groups[] = अणु "pwm5", पूर्ण;
अटल स्थिर अक्षर *jz4770_pwm6_groups[] = अणु "pwm6", पूर्ण;
अटल स्थिर अक्षर *jz4770_pwm7_groups[] = अणु "pwm7", पूर्ण;
अटल स्थिर अक्षर *jz4770_mac_groups[] = अणु "mac-rmii", "mac-mii", पूर्ण;

अटल स्थिर काष्ठा function_desc jz4770_functions[] = अणु
	अणु "uart0", jz4770_uart0_groups, ARRAY_SIZE(jz4770_uart0_groups), पूर्ण,
	अणु "uart1", jz4770_uart1_groups, ARRAY_SIZE(jz4770_uart1_groups), पूर्ण,
	अणु "uart2", jz4770_uart2_groups, ARRAY_SIZE(jz4770_uart2_groups), पूर्ण,
	अणु "uart3", jz4770_uart3_groups, ARRAY_SIZE(jz4770_uart3_groups), पूर्ण,
	अणु "ssi0", jz4770_ssi0_groups, ARRAY_SIZE(jz4770_ssi0_groups), पूर्ण,
	अणु "ssi1", jz4770_ssi1_groups, ARRAY_SIZE(jz4770_ssi1_groups), पूर्ण,
	अणु "mmc0", jz4770_mmc0_groups, ARRAY_SIZE(jz4770_mmc0_groups), पूर्ण,
	अणु "mmc1", jz4770_mmc1_groups, ARRAY_SIZE(jz4770_mmc1_groups), पूर्ण,
	अणु "mmc2", jz4770_mmc2_groups, ARRAY_SIZE(jz4770_mmc2_groups), पूर्ण,
	अणु "nemc", jz4770_nemc_groups, ARRAY_SIZE(jz4770_nemc_groups), पूर्ण,
	अणु "nemc-cs1", jz4770_cs1_groups, ARRAY_SIZE(jz4770_cs1_groups), पूर्ण,
	अणु "nemc-cs2", jz4770_cs2_groups, ARRAY_SIZE(jz4770_cs2_groups), पूर्ण,
	अणु "nemc-cs3", jz4770_cs3_groups, ARRAY_SIZE(jz4770_cs3_groups), पूर्ण,
	अणु "nemc-cs4", jz4770_cs4_groups, ARRAY_SIZE(jz4770_cs4_groups), पूर्ण,
	अणु "nemc-cs5", jz4770_cs5_groups, ARRAY_SIZE(jz4770_cs5_groups), पूर्ण,
	अणु "nemc-cs6", jz4770_cs6_groups, ARRAY_SIZE(jz4770_cs6_groups), पूर्ण,
	अणु "i2c0", jz4770_i2c0_groups, ARRAY_SIZE(jz4770_i2c0_groups), पूर्ण,
	अणु "i2c1", jz4770_i2c1_groups, ARRAY_SIZE(jz4770_i2c1_groups), पूर्ण,
	अणु "i2c2", jz4770_i2c2_groups, ARRAY_SIZE(jz4770_i2c2_groups), पूर्ण,
	अणु "cim", jz4770_cim_groups, ARRAY_SIZE(jz4770_cim_groups), पूर्ण,
	अणु "lcd", jz4770_lcd_groups, ARRAY_SIZE(jz4770_lcd_groups), पूर्ण,
	अणु "pwm0", jz4770_pwm0_groups, ARRAY_SIZE(jz4770_pwm0_groups), पूर्ण,
	अणु "pwm1", jz4770_pwm1_groups, ARRAY_SIZE(jz4770_pwm1_groups), पूर्ण,
	अणु "pwm2", jz4770_pwm2_groups, ARRAY_SIZE(jz4770_pwm2_groups), पूर्ण,
	अणु "pwm3", jz4770_pwm3_groups, ARRAY_SIZE(jz4770_pwm3_groups), पूर्ण,
	अणु "pwm4", jz4770_pwm4_groups, ARRAY_SIZE(jz4770_pwm4_groups), पूर्ण,
	अणु "pwm5", jz4770_pwm5_groups, ARRAY_SIZE(jz4770_pwm5_groups), पूर्ण,
	अणु "pwm6", jz4770_pwm6_groups, ARRAY_SIZE(jz4770_pwm6_groups), पूर्ण,
	अणु "pwm7", jz4770_pwm7_groups, ARRAY_SIZE(jz4770_pwm7_groups), पूर्ण,
	अणु "mac", jz4770_mac_groups, ARRAY_SIZE(jz4770_mac_groups), पूर्ण,
	अणु "otg", jz4760_otg_groups, ARRAY_SIZE(jz4760_otg_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info jz4770_chip_info = अणु
	.num_chips = 6,
	.reg_offset = 0x100,
	.version = ID_JZ4770,
	.groups = jz4770_groups,
	.num_groups = ARRAY_SIZE(jz4770_groups),
	.functions = jz4770_functions,
	.num_functions = ARRAY_SIZE(jz4770_functions),
	.pull_ups = jz4770_pull_ups,
	.pull_करोwns = jz4770_pull_करोwns,
पूर्ण;

अटल स्थिर u32 jz4775_pull_ups[7] = अणु
	0x28ff00ff, 0xf030f3fc, 0x0fffffff, 0xfffe4000, 0xf0f0000c, 0x0000f00f, 0x0000f3c0,
पूर्ण;

अटल स्थिर u32 jz4775_pull_करोwns[7] = अणु
	0x00000000, 0x00030c03, 0x00000000, 0x00008000, 0x00000403, 0x00000ff0, 0x00030c00,
पूर्ण;

अटल पूर्णांक jz4775_uart0_data_pins[] = अणु 0xa0, 0xa3, पूर्ण;
अटल पूर्णांक jz4775_uart0_hwflow_pins[] = अणु 0xa1, 0xa2, पूर्ण;
अटल पूर्णांक jz4775_uart1_data_pins[] = अणु 0x7a, 0x7c, पूर्ण;
अटल पूर्णांक jz4775_uart1_hwflow_pins[] = अणु 0x7b, 0x7d, पूर्ण;
अटल पूर्णांक jz4775_uart2_data_c_pins[] = अणु 0x54, 0x4a, पूर्ण;
अटल पूर्णांक jz4775_uart2_data_f_pins[] = अणु 0xa5, 0xa4, पूर्ण;
अटल पूर्णांक jz4775_uart3_data_pins[] = अणु 0x1e, 0x1f, पूर्ण;
अटल पूर्णांक jz4775_ssi_dt_a_pins[] = अणु 0x13, पूर्ण;
अटल पूर्णांक jz4775_ssi_dt_d_pins[] = अणु 0x75, पूर्ण;
अटल पूर्णांक jz4775_ssi_dr_a_pins[] = अणु 0x14, पूर्ण;
अटल पूर्णांक jz4775_ssi_dr_d_pins[] = अणु 0x74, पूर्ण;
अटल पूर्णांक jz4775_ssi_clk_a_pins[] = अणु 0x12, पूर्ण;
अटल पूर्णांक jz4775_ssi_clk_d_pins[] = अणु 0x78, पूर्ण;
अटल पूर्णांक jz4775_ssi_gpc_pins[] = अणु 0x76, पूर्ण;
अटल पूर्णांक jz4775_ssi_ce0_a_pins[] = अणु 0x17, पूर्ण;
अटल पूर्णांक jz4775_ssi_ce0_d_pins[] = अणु 0x79, पूर्ण;
अटल पूर्णांक jz4775_ssi_ce1_pins[] = अणु 0x77, पूर्ण;
अटल पूर्णांक jz4775_mmc0_1bit_a_pins[] = अणु 0x12, 0x13, 0x14, पूर्ण;
अटल पूर्णांक jz4775_mmc0_4bit_a_pins[] = अणु 0x15, 0x16, 0x17, पूर्ण;
अटल पूर्णांक jz4775_mmc0_8bit_a_pins[] = अणु 0x04, 0x05, 0x06, 0x07, पूर्ण;
अटल पूर्णांक jz4775_mmc0_1bit_e_pins[] = अणु 0x9c, 0x9d, 0x94, पूर्ण;
अटल पूर्णांक jz4775_mmc0_4bit_e_pins[] = अणु 0x95, 0x96, 0x97, पूर्ण;
अटल पूर्णांक jz4775_mmc1_1bit_d_pins[] = अणु 0x78, 0x79, 0x74, पूर्ण;
अटल पूर्णांक jz4775_mmc1_4bit_d_pins[] = अणु 0x75, 0x76, 0x77, पूर्ण;
अटल पूर्णांक jz4775_mmc1_1bit_e_pins[] = अणु 0x9c, 0x9d, 0x94, पूर्ण;
अटल पूर्णांक jz4775_mmc1_4bit_e_pins[] = अणु 0x95, 0x96, 0x97, पूर्ण;
अटल पूर्णांक jz4775_mmc2_1bit_b_pins[] = अणु 0x3c, 0x3d, 0x34, पूर्ण;
अटल पूर्णांक jz4775_mmc2_4bit_b_pins[] = अणु 0x35, 0x3e, 0x3f, पूर्ण;
अटल पूर्णांक jz4775_mmc2_1bit_e_pins[] = अणु 0x9c, 0x9d, 0x94, पूर्ण;
अटल पूर्णांक jz4775_mmc2_4bit_e_pins[] = अणु 0x95, 0x96, 0x97, पूर्ण;
अटल पूर्णांक jz4775_nemc_8bit_data_pins[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
पूर्ण;
अटल पूर्णांक jz4775_nemc_16bit_data_pins[] = अणु
	0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1,
पूर्ण;
अटल पूर्णांक jz4775_nemc_cle_ale_pins[] = अणु 0x20, 0x21, पूर्ण;
अटल पूर्णांक jz4775_nemc_addr_pins[] = अणु 0x22, 0x23, 0x24, 0x25, पूर्ण;
अटल पूर्णांक jz4775_nemc_rd_we_pins[] = अणु 0x10, 0x11, पूर्ण;
अटल पूर्णांक jz4775_nemc_frd_fwe_pins[] = अणु 0x12, 0x13, पूर्ण;
अटल पूर्णांक jz4775_nemc_रुको_pins[] = अणु 0x1b, पूर्ण;
अटल पूर्णांक jz4775_nemc_cs1_pins[] = अणु 0x15, पूर्ण;
अटल पूर्णांक jz4775_nemc_cs2_pins[] = अणु 0x16, पूर्ण;
अटल पूर्णांक jz4775_nemc_cs3_pins[] = अणु 0x17, पूर्ण;
अटल पूर्णांक jz4775_i2c0_pins[] = अणु 0x7e, 0x7f, पूर्ण;
अटल पूर्णांक jz4775_i2c1_pins[] = अणु 0x9e, 0x9f, पूर्ण;
अटल पूर्णांक jz4775_i2c2_pins[] = अणु 0x80, 0x83, पूर्ण;
अटल पूर्णांक jz4775_i2s_data_tx_pins[] = अणु 0xa3, पूर्ण;
अटल पूर्णांक jz4775_i2s_data_rx_pins[] = अणु 0xa2, पूर्ण;
अटल पूर्णांक jz4775_i2s_clk_txrx_pins[] = अणु 0xa0, 0xa1, पूर्ण;
अटल पूर्णांक jz4775_i2s_sysclk_pins[] = अणु 0x83, पूर्ण;
अटल पूर्णांक jz4775_dmic_pins[] = अणु 0xaa, 0xab, पूर्ण;
अटल पूर्णांक jz4775_cim_pins[] = अणु
	0x26, 0x27, 0x28, 0x29,
	0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
पूर्ण;
अटल पूर्णांक jz4775_lcd_8bit_pins[] = अणु
	0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x4c, 0x4d,
	0x48, 0x52, 0x53,
पूर्ण;
अटल पूर्णांक jz4775_lcd_16bit_pins[] = अणु
	0x4e, 0x4f, 0x50, 0x51, 0x56, 0x57, 0x58, 0x59,
पूर्ण;
अटल पूर्णांक jz4775_lcd_18bit_pins[] = अणु
	0x5a, 0x5b,
पूर्ण;
अटल पूर्णांक jz4775_lcd_24bit_pins[] = अणु
	0x40, 0x41, 0x4a, 0x4b, 0x54, 0x55,
पूर्ण;
अटल पूर्णांक jz4775_lcd_special_pins[] = अणु 0x54, 0x4a, 0x41, 0x40, पूर्ण;
अटल पूर्णांक jz4775_lcd_generic_pins[] = अणु 0x49, पूर्ण;
अटल पूर्णांक jz4775_pwm_pwm0_pins[] = अणु 0x80, पूर्ण;
अटल पूर्णांक jz4775_pwm_pwm1_pins[] = अणु 0x81, पूर्ण;
अटल पूर्णांक jz4775_pwm_pwm2_pins[] = अणु 0x82, पूर्ण;
अटल पूर्णांक jz4775_pwm_pwm3_pins[] = अणु 0x83, पूर्ण;
अटल पूर्णांक jz4775_mac_rmii_pins[] = अणु
	0xa9, 0xab, 0xaa, 0xac, 0xa5, 0xa4, 0xad, 0xae, 0xa6, 0xa8,
पूर्ण;
अटल पूर्णांक jz4775_mac_mii_pins[] = अणु
	0x7b, 0x7a, 0x7d, 0x7c, 0xa7, 0x24, 0xaf,
पूर्ण;
अटल पूर्णांक jz4775_mac_rgmii_pins[] = अणु
	0xa9, 0x7b, 0x7a, 0xab, 0xaa, 0xac, 0x7d, 0x7c, 0xa5, 0xa4,
	0xad, 0xae, 0xa7, 0xa6,
पूर्ण;
अटल पूर्णांक jz4775_mac_gmii_pins[] = अणु
	0x31, 0x30, 0x2f, 0x2e, 0x2d, 0x2c, 0x2b, 0x2a,
	0xa8, 0x28, 0x24, 0xaf,
पूर्ण;
अटल पूर्णांक jz4775_otg_pins[] = अणु 0x8a, पूर्ण;

अटल u8 jz4775_uart3_data_funcs[] = अणु 0, 1, पूर्ण;
अटल u8 jz4775_mac_mii_funcs[] = अणु 1, 1, 1, 1, 0, 1, 0, पूर्ण;
अटल u8 jz4775_mac_rgmii_funcs[] = अणु
	0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
	0, 0, 0, 0,
पूर्ण;
अटल u8 jz4775_mac_gmii_funcs[] = अणु
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 1, 1, 0,
पूर्ण;

अटल स्थिर काष्ठा group_desc jz4775_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", jz4775_uart0_data, 0),
	INGENIC_PIN_GROUP("uart0-hwflow", jz4775_uart0_hwflow, 0),
	INGENIC_PIN_GROUP("uart1-data", jz4775_uart1_data, 0),
	INGENIC_PIN_GROUP("uart1-hwflow", jz4775_uart1_hwflow, 0),
	INGENIC_PIN_GROUP("uart2-data-c", jz4775_uart2_data_c, 2),
	INGENIC_PIN_GROUP("uart2-data-f", jz4775_uart2_data_f, 1),
	INGENIC_PIN_GROUP_FUNCS("uart3-data", jz4775_uart3_data,
				jz4775_uart3_data_funcs),
	INGENIC_PIN_GROUP("ssi-dt-a", jz4775_ssi_dt_a, 2),
	INGENIC_PIN_GROUP("ssi-dt-d", jz4775_ssi_dt_d, 1),
	INGENIC_PIN_GROUP("ssi-dr-a", jz4775_ssi_dr_a, 2),
	INGENIC_PIN_GROUP("ssi-dr-d", jz4775_ssi_dr_d, 1),
	INGENIC_PIN_GROUP("ssi-clk-a", jz4775_ssi_clk_a, 2),
	INGENIC_PIN_GROUP("ssi-clk-d", jz4775_ssi_clk_d, 1),
	INGENIC_PIN_GROUP("ssi-gpc", jz4775_ssi_gpc, 1),
	INGENIC_PIN_GROUP("ssi-ce0-a", jz4775_ssi_ce0_a, 2),
	INGENIC_PIN_GROUP("ssi-ce0-d", jz4775_ssi_ce0_d, 1),
	INGENIC_PIN_GROUP("ssi-ce1", jz4775_ssi_ce1, 1),
	INGENIC_PIN_GROUP("mmc0-1bit-a", jz4775_mmc0_1bit_a, 1),
	INGENIC_PIN_GROUP("mmc0-4bit-a", jz4775_mmc0_4bit_a, 1),
	INGENIC_PIN_GROUP("mmc0-8bit-a", jz4775_mmc0_8bit_a, 1),
	INGENIC_PIN_GROUP("mmc0-1bit-e", jz4775_mmc0_1bit_e, 0),
	INGENIC_PIN_GROUP("mmc0-4bit-e", jz4775_mmc0_4bit_e, 0),
	INGENIC_PIN_GROUP("mmc1-1bit-d", jz4775_mmc1_1bit_d, 0),
	INGENIC_PIN_GROUP("mmc1-4bit-d", jz4775_mmc1_4bit_d, 0),
	INGENIC_PIN_GROUP("mmc1-1bit-e", jz4775_mmc1_1bit_e, 1),
	INGENIC_PIN_GROUP("mmc1-4bit-e", jz4775_mmc1_4bit_e, 1),
	INGENIC_PIN_GROUP("mmc2-1bit-b", jz4775_mmc2_1bit_b, 0),
	INGENIC_PIN_GROUP("mmc2-4bit-b", jz4775_mmc2_4bit_b, 0),
	INGENIC_PIN_GROUP("mmc2-1bit-e", jz4775_mmc2_1bit_e, 2),
	INGENIC_PIN_GROUP("mmc2-4bit-e", jz4775_mmc2_4bit_e, 2),
	INGENIC_PIN_GROUP("nemc-8bit-data", jz4775_nemc_8bit_data, 0),
	INGENIC_PIN_GROUP("nemc-16bit-data", jz4775_nemc_16bit_data, 1),
	INGENIC_PIN_GROUP("nemc-cle-ale", jz4775_nemc_cle_ale, 0),
	INGENIC_PIN_GROUP("nemc-addr", jz4775_nemc_addr, 0),
	INGENIC_PIN_GROUP("nemc-rd-we", jz4775_nemc_rd_we, 0),
	INGENIC_PIN_GROUP("nemc-frd-fwe", jz4775_nemc_frd_fwe, 0),
	INGENIC_PIN_GROUP("nemc-wait", jz4775_nemc_रुको, 0),
	INGENIC_PIN_GROUP("nemc-cs1", jz4775_nemc_cs1, 0),
	INGENIC_PIN_GROUP("nemc-cs2", jz4775_nemc_cs2, 0),
	INGENIC_PIN_GROUP("nemc-cs3", jz4775_nemc_cs3, 0),
	INGENIC_PIN_GROUP("i2c0-data", jz4775_i2c0, 0),
	INGENIC_PIN_GROUP("i2c1-data", jz4775_i2c1, 0),
	INGENIC_PIN_GROUP("i2c2-data", jz4775_i2c2, 1),
	INGENIC_PIN_GROUP("i2s-data-tx", jz4775_i2s_data_tx, 1),
	INGENIC_PIN_GROUP("i2s-data-rx", jz4775_i2s_data_rx, 1),
	INGENIC_PIN_GROUP("i2s-clk-txrx", jz4775_i2s_clk_txrx, 1),
	INGENIC_PIN_GROUP("i2s-sysclk", jz4775_i2s_sysclk, 2),
	INGENIC_PIN_GROUP("dmic", jz4775_dmic, 1),
	INGENIC_PIN_GROUP("cim-data", jz4775_cim, 0),
	INGENIC_PIN_GROUP("lcd-8bit", jz4775_lcd_8bit, 0),
	INGENIC_PIN_GROUP("lcd-16bit", jz4775_lcd_16bit, 0),
	INGENIC_PIN_GROUP("lcd-18bit", jz4775_lcd_18bit, 0),
	INGENIC_PIN_GROUP("lcd-24bit", jz4775_lcd_24bit, 0),
	INGENIC_PIN_GROUP("lcd-generic", jz4775_lcd_generic, 0),
	INGENIC_PIN_GROUP("lcd-special", jz4775_lcd_special, 1),
	INGENIC_PIN_GROUP("pwm0", jz4775_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", jz4775_pwm_pwm1, 0),
	INGENIC_PIN_GROUP("pwm2", jz4775_pwm_pwm2, 0),
	INGENIC_PIN_GROUP("pwm3", jz4775_pwm_pwm3, 0),
	INGENIC_PIN_GROUP("mac-rmii", jz4775_mac_rmii, 0),
	INGENIC_PIN_GROUP_FUNCS("mac-mii", jz4775_mac_mii,
				jz4775_mac_mii_funcs),
	INGENIC_PIN_GROUP_FUNCS("mac-rgmii", jz4775_mac_rgmii,
				jz4775_mac_rgmii_funcs),
	INGENIC_PIN_GROUP_FUNCS("mac-gmii", jz4775_mac_gmii,
				jz4775_mac_gmii_funcs),
	INGENIC_PIN_GROUP("otg-vbus", jz4775_otg, 0),
पूर्ण;

अटल स्थिर अक्षर *jz4775_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4775_uart1_groups[] = अणु "uart1-data", "uart1-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4775_uart2_groups[] = अणु "uart2-data-c", "uart2-data-f", पूर्ण;
अटल स्थिर अक्षर *jz4775_uart3_groups[] = अणु "uart3-data", पूर्ण;
अटल स्थिर अक्षर *jz4775_ssi_groups[] = अणु
	"ssi-dt-a", "ssi-dt-d",
	"ssi-dr-a", "ssi-dr-d",
	"ssi-clk-a", "ssi-clk-d",
	"ssi-gpc",
	"ssi-ce0-a", "ssi-ce0-d",
	"ssi-ce1",
पूर्ण;
अटल स्थिर अक्षर *jz4775_mmc0_groups[] = अणु
	"mmc0-1bit-a", "mmc0-4bit-a", "mmc0-8bit-a",
	"mmc0-1bit-e", "mmc0-4bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4775_mmc1_groups[] = अणु
	"mmc1-1bit-d", "mmc1-4bit-d",
	"mmc1-1bit-e", "mmc1-4bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4775_mmc2_groups[] = अणु
	"mmc2-1bit-b", "mmc2-4bit-b",
	"mmc2-1bit-e", "mmc2-4bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4775_nemc_groups[] = अणु
	"nemc-8bit-data", "nemc-16bit-data", "nemc-cle-ale",
	"nemc-addr", "nemc-rd-we", "nemc-frd-fwe", "nemc-wait",
पूर्ण;
अटल स्थिर अक्षर *jz4775_cs1_groups[] = अणु "nemc-cs1", पूर्ण;
अटल स्थिर अक्षर *jz4775_cs2_groups[] = अणु "nemc-cs2", पूर्ण;
अटल स्थिर अक्षर *jz4775_cs3_groups[] = अणु "nemc-cs3", पूर्ण;
अटल स्थिर अक्षर *jz4775_i2c0_groups[] = अणु "i2c0-data", पूर्ण;
अटल स्थिर अक्षर *jz4775_i2c1_groups[] = अणु "i2c1-data", पूर्ण;
अटल स्थिर अक्षर *jz4775_i2c2_groups[] = अणु "i2c2-data", पूर्ण;
अटल स्थिर अक्षर *jz4775_i2s_groups[] = अणु
	"i2s-data-tx", "i2s-data-rx", "i2s-clk-txrx", "i2s-sysclk",
पूर्ण;
अटल स्थिर अक्षर *jz4775_dmic_groups[] = अणु "dmic", पूर्ण;
अटल स्थिर अक्षर *jz4775_cim_groups[] = अणु "cim-data", पूर्ण;
अटल स्थिर अक्षर *jz4775_lcd_groups[] = अणु
	"lcd-8bit", "lcd-16bit", "lcd-18bit", "lcd-24bit",
	"lcd-special", "lcd-generic",
पूर्ण;
अटल स्थिर अक्षर *jz4775_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *jz4775_pwm1_groups[] = अणु "pwm1", पूर्ण;
अटल स्थिर अक्षर *jz4775_pwm2_groups[] = अणु "pwm2", पूर्ण;
अटल स्थिर अक्षर *jz4775_pwm3_groups[] = अणु "pwm3", पूर्ण;
अटल स्थिर अक्षर *jz4775_mac_groups[] = अणु
	"mac-rmii", "mac-mii", "mac-rgmii", "mac-gmii",
पूर्ण;
अटल स्थिर अक्षर *jz4775_otg_groups[] = अणु "otg-vbus", पूर्ण;

अटल स्थिर काष्ठा function_desc jz4775_functions[] = अणु
	अणु "uart0", jz4775_uart0_groups, ARRAY_SIZE(jz4775_uart0_groups), पूर्ण,
	अणु "uart1", jz4775_uart1_groups, ARRAY_SIZE(jz4775_uart1_groups), पूर्ण,
	अणु "uart2", jz4775_uart2_groups, ARRAY_SIZE(jz4775_uart2_groups), पूर्ण,
	अणु "uart3", jz4775_uart3_groups, ARRAY_SIZE(jz4775_uart3_groups), पूर्ण,
	अणु "ssi", jz4775_ssi_groups, ARRAY_SIZE(jz4775_ssi_groups), पूर्ण,
	अणु "mmc0", jz4775_mmc0_groups, ARRAY_SIZE(jz4775_mmc0_groups), पूर्ण,
	अणु "mmc1", jz4775_mmc1_groups, ARRAY_SIZE(jz4775_mmc1_groups), पूर्ण,
	अणु "mmc2", jz4775_mmc2_groups, ARRAY_SIZE(jz4775_mmc2_groups), पूर्ण,
	अणु "nemc", jz4775_nemc_groups, ARRAY_SIZE(jz4775_nemc_groups), पूर्ण,
	अणु "nemc-cs1", jz4775_cs1_groups, ARRAY_SIZE(jz4775_cs1_groups), पूर्ण,
	अणु "nemc-cs2", jz4775_cs2_groups, ARRAY_SIZE(jz4775_cs2_groups), पूर्ण,
	अणु "nemc-cs3", jz4775_cs3_groups, ARRAY_SIZE(jz4775_cs3_groups), पूर्ण,
	अणु "i2c0", jz4775_i2c0_groups, ARRAY_SIZE(jz4775_i2c0_groups), पूर्ण,
	अणु "i2c1", jz4775_i2c1_groups, ARRAY_SIZE(jz4775_i2c1_groups), पूर्ण,
	अणु "i2c2", jz4775_i2c2_groups, ARRAY_SIZE(jz4775_i2c2_groups), पूर्ण,
	अणु "i2s", jz4775_i2s_groups, ARRAY_SIZE(jz4775_i2s_groups), पूर्ण,
	अणु "dmic", jz4775_dmic_groups, ARRAY_SIZE(jz4775_dmic_groups), पूर्ण,
	अणु "cim", jz4775_cim_groups, ARRAY_SIZE(jz4775_cim_groups), पूर्ण,
	अणु "lcd", jz4775_lcd_groups, ARRAY_SIZE(jz4775_lcd_groups), पूर्ण,
	अणु "pwm0", jz4775_pwm0_groups, ARRAY_SIZE(jz4775_pwm0_groups), पूर्ण,
	अणु "pwm1", jz4775_pwm1_groups, ARRAY_SIZE(jz4775_pwm1_groups), पूर्ण,
	अणु "pwm2", jz4775_pwm2_groups, ARRAY_SIZE(jz4775_pwm2_groups), पूर्ण,
	अणु "pwm3", jz4775_pwm3_groups, ARRAY_SIZE(jz4775_pwm3_groups), पूर्ण,
	अणु "mac", jz4775_mac_groups, ARRAY_SIZE(jz4775_mac_groups), पूर्ण,
	अणु "otg", jz4775_otg_groups, ARRAY_SIZE(jz4775_otg_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info jz4775_chip_info = अणु
	.num_chips = 7,
	.reg_offset = 0x100,
	.version = ID_JZ4775,
	.groups = jz4775_groups,
	.num_groups = ARRAY_SIZE(jz4775_groups),
	.functions = jz4775_functions,
	.num_functions = ARRAY_SIZE(jz4775_functions),
	.pull_ups = jz4775_pull_ups,
	.pull_करोwns = jz4775_pull_करोwns,
पूर्ण;

अटल स्थिर u32 jz4780_pull_ups[6] = अणु
	0x3fffffff, 0xfff0f3fc, 0x0fffffff, 0xffff4fff, 0xfffffb7c, 0x7fa7f00f,
पूर्ण;

अटल स्थिर u32 jz4780_pull_करोwns[6] = अणु
	0x00000000, 0x000f0c03, 0x00000000, 0x0000b000, 0x00000483, 0x00580ff0,
पूर्ण;

अटल पूर्णांक jz4780_uart2_data_pins[] = अणु 0x66, 0x67, पूर्ण;
अटल पूर्णांक jz4780_uart2_hwflow_pins[] = अणु 0x65, 0x64, पूर्ण;
अटल पूर्णांक jz4780_uart4_data_pins[] = अणु 0x54, 0x4a, पूर्ण;
अटल पूर्णांक jz4780_ssi0_dt_a_19_pins[] = अणु 0x13, पूर्ण;
अटल पूर्णांक jz4780_ssi0_dt_a_21_pins[] = अणु 0x15, पूर्ण;
अटल पूर्णांक jz4780_ssi0_dt_a_28_pins[] = अणु 0x1c, पूर्ण;
अटल पूर्णांक jz4780_ssi0_dt_b_pins[] = अणु 0x3d, पूर्ण;
अटल पूर्णांक jz4780_ssi0_dt_d_pins[] = अणु 0x79, पूर्ण;
अटल पूर्णांक jz4780_ssi0_dr_a_20_pins[] = अणु 0x14, पूर्ण;
अटल पूर्णांक jz4780_ssi0_dr_a_27_pins[] = अणु 0x1b, पूर्ण;
अटल पूर्णांक jz4780_ssi0_dr_b_pins[] = अणु 0x34, पूर्ण;
अटल पूर्णांक jz4780_ssi0_dr_d_pins[] = अणु 0x74, पूर्ण;
अटल पूर्णांक jz4780_ssi0_clk_a_pins[] = अणु 0x12, पूर्ण;
अटल पूर्णांक jz4780_ssi0_clk_b_5_pins[] = अणु 0x25, पूर्ण;
अटल पूर्णांक jz4780_ssi0_clk_b_28_pins[] = अणु 0x3c, पूर्ण;
अटल पूर्णांक jz4780_ssi0_clk_d_pins[] = अणु 0x78, पूर्ण;
अटल पूर्णांक jz4780_ssi0_gpc_b_pins[] = अणु 0x3e, पूर्ण;
अटल पूर्णांक jz4780_ssi0_gpc_d_pins[] = अणु 0x76, पूर्ण;
अटल पूर्णांक jz4780_ssi0_ce0_a_23_pins[] = अणु 0x17, पूर्ण;
अटल पूर्णांक jz4780_ssi0_ce0_a_25_pins[] = अणु 0x19, पूर्ण;
अटल पूर्णांक jz4780_ssi0_ce0_b_pins[] = अणु 0x3f, पूर्ण;
अटल पूर्णांक jz4780_ssi0_ce0_d_pins[] = अणु 0x77, पूर्ण;
अटल पूर्णांक jz4780_ssi0_ce1_b_pins[] = अणु 0x35, पूर्ण;
अटल पूर्णांक jz4780_ssi0_ce1_d_pins[] = अणु 0x75, पूर्ण;
अटल पूर्णांक jz4780_ssi1_dt_b_pins[] = अणु 0x3d, पूर्ण;
अटल पूर्णांक jz4780_ssi1_dt_d_pins[] = अणु 0x79, पूर्ण;
अटल पूर्णांक jz4780_ssi1_dr_b_pins[] = अणु 0x34, पूर्ण;
अटल पूर्णांक jz4780_ssi1_dr_d_pins[] = अणु 0x74, पूर्ण;
अटल पूर्णांक jz4780_ssi1_clk_b_pins[] = अणु 0x3c, पूर्ण;
अटल पूर्णांक jz4780_ssi1_clk_d_pins[] = अणु 0x78, पूर्ण;
अटल पूर्णांक jz4780_ssi1_gpc_b_pins[] = अणु 0x3e, पूर्ण;
अटल पूर्णांक jz4780_ssi1_gpc_d_pins[] = अणु 0x76, पूर्ण;
अटल पूर्णांक jz4780_ssi1_ce0_b_pins[] = अणु 0x3f, पूर्ण;
अटल पूर्णांक jz4780_ssi1_ce0_d_pins[] = अणु 0x77, पूर्ण;
अटल पूर्णांक jz4780_ssi1_ce1_b_pins[] = अणु 0x35, पूर्ण;
अटल पूर्णांक jz4780_ssi1_ce1_d_pins[] = अणु 0x75, पूर्ण;
अटल पूर्णांक jz4780_mmc0_8bit_a_pins[] = अणु 0x04, 0x05, 0x06, 0x07, 0x18, पूर्ण;
अटल पूर्णांक jz4780_i2c3_pins[] = अणु 0x6a, 0x6b, पूर्ण;
अटल पूर्णांक jz4780_i2c4_e_pins[] = अणु 0x8c, 0x8d, पूर्ण;
अटल पूर्णांक jz4780_i2c4_f_pins[] = अणु 0xb9, 0xb8, पूर्ण;
अटल पूर्णांक jz4780_i2s_data_tx_pins[] = अणु 0x87, पूर्ण;
अटल पूर्णांक jz4780_i2s_data_rx_pins[] = अणु 0x86, पूर्ण;
अटल पूर्णांक jz4780_i2s_clk_txrx_pins[] = अणु 0x6c, 0x6d, पूर्ण;
अटल पूर्णांक jz4780_i2s_clk_rx_pins[] = अणु 0x88, 0x89, पूर्ण;
अटल पूर्णांक jz4780_i2s_sysclk_pins[] = अणु 0x85, पूर्ण;
अटल पूर्णांक jz4780_dmic_pins[] = अणु 0x32, 0x33, पूर्ण;
अटल पूर्णांक jz4780_hdmi_ddc_pins[] = अणु 0xb9, 0xb8, पूर्ण;

अटल u8 jz4780_i2s_clk_txrx_funcs[] = अणु 1, 0, पूर्ण;

अटल स्थिर काष्ठा group_desc jz4780_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", jz4770_uart0_data, 0),
	INGENIC_PIN_GROUP("uart0-hwflow", jz4770_uart0_hwflow, 0),
	INGENIC_PIN_GROUP("uart1-data", jz4770_uart1_data, 0),
	INGENIC_PIN_GROUP("uart1-hwflow", jz4770_uart1_hwflow, 0),
	INGENIC_PIN_GROUP("uart2-data", jz4780_uart2_data, 1),
	INGENIC_PIN_GROUP("uart2-hwflow", jz4780_uart2_hwflow, 1),
	INGENIC_PIN_GROUP_FUNCS("uart3-data", jz4770_uart3_data,
				jz4760_uart3_data_funcs),
	INGENIC_PIN_GROUP("uart3-hwflow", jz4770_uart3_hwflow, 0),
	INGENIC_PIN_GROUP("uart4-data", jz4780_uart4_data, 2),
	INGENIC_PIN_GROUP("ssi0-dt-a-19", jz4780_ssi0_dt_a_19, 2),
	INGENIC_PIN_GROUP("ssi0-dt-a-21", jz4780_ssi0_dt_a_21, 2),
	INGENIC_PIN_GROUP("ssi0-dt-a-28", jz4780_ssi0_dt_a_28, 2),
	INGENIC_PIN_GROUP("ssi0-dt-b", jz4780_ssi0_dt_b, 1),
	INGENIC_PIN_GROUP("ssi0-dt-d", jz4780_ssi0_dt_d, 1),
	INGENIC_PIN_GROUP("ssi0-dt-e", jz4770_ssi0_dt_e, 0),
	INGENIC_PIN_GROUP("ssi0-dr-a-20", jz4780_ssi0_dr_a_20, 2),
	INGENIC_PIN_GROUP("ssi0-dr-a-27", jz4780_ssi0_dr_a_27, 2),
	INGENIC_PIN_GROUP("ssi0-dr-b", jz4780_ssi0_dr_b, 1),
	INGENIC_PIN_GROUP("ssi0-dr-d", jz4780_ssi0_dr_d, 1),
	INGENIC_PIN_GROUP("ssi0-dr-e", jz4770_ssi0_dr_e, 0),
	INGENIC_PIN_GROUP("ssi0-clk-a", jz4780_ssi0_clk_a, 2),
	INGENIC_PIN_GROUP("ssi0-clk-b-5", jz4780_ssi0_clk_b_5, 1),
	INGENIC_PIN_GROUP("ssi0-clk-b-28", jz4780_ssi0_clk_b_28, 1),
	INGENIC_PIN_GROUP("ssi0-clk-d", jz4780_ssi0_clk_d, 1),
	INGENIC_PIN_GROUP("ssi0-clk-e", jz4770_ssi0_clk_e, 0),
	INGENIC_PIN_GROUP("ssi0-gpc-b", jz4780_ssi0_gpc_b, 1),
	INGENIC_PIN_GROUP("ssi0-gpc-d", jz4780_ssi0_gpc_d, 1),
	INGENIC_PIN_GROUP("ssi0-gpc-e", jz4770_ssi0_gpc_e, 0),
	INGENIC_PIN_GROUP("ssi0-ce0-a-23", jz4780_ssi0_ce0_a_23, 2),
	INGENIC_PIN_GROUP("ssi0-ce0-a-25", jz4780_ssi0_ce0_a_25, 2),
	INGENIC_PIN_GROUP("ssi0-ce0-b", jz4780_ssi0_ce0_b, 1),
	INGENIC_PIN_GROUP("ssi0-ce0-d", jz4780_ssi0_ce0_d, 1),
	INGENIC_PIN_GROUP("ssi0-ce0-e", jz4770_ssi0_ce0_e, 0),
	INGENIC_PIN_GROUP("ssi0-ce1-b", jz4780_ssi0_ce1_b, 1),
	INGENIC_PIN_GROUP("ssi0-ce1-d", jz4780_ssi0_ce1_d, 1),
	INGENIC_PIN_GROUP("ssi0-ce1-e", jz4770_ssi0_ce1_e, 0),
	INGENIC_PIN_GROUP("ssi1-dt-b", jz4780_ssi1_dt_b, 2),
	INGENIC_PIN_GROUP("ssi1-dt-d", jz4780_ssi1_dt_d, 2),
	INGENIC_PIN_GROUP("ssi1-dt-e", jz4770_ssi1_dt_e, 1),
	INGENIC_PIN_GROUP("ssi1-dr-b", jz4780_ssi1_dr_b, 2),
	INGENIC_PIN_GROUP("ssi1-dr-d", jz4780_ssi1_dr_d, 2),
	INGENIC_PIN_GROUP("ssi1-dr-e", jz4770_ssi1_dr_e, 1),
	INGENIC_PIN_GROUP("ssi1-clk-b", jz4780_ssi1_clk_b, 2),
	INGENIC_PIN_GROUP("ssi1-clk-d", jz4780_ssi1_clk_d, 2),
	INGENIC_PIN_GROUP("ssi1-clk-e", jz4770_ssi1_clk_e, 1),
	INGENIC_PIN_GROUP("ssi1-gpc-b", jz4780_ssi1_gpc_b, 2),
	INGENIC_PIN_GROUP("ssi1-gpc-d", jz4780_ssi1_gpc_d, 2),
	INGENIC_PIN_GROUP("ssi1-gpc-e", jz4770_ssi1_gpc_e, 1),
	INGENIC_PIN_GROUP("ssi1-ce0-b", jz4780_ssi1_ce0_b, 2),
	INGENIC_PIN_GROUP("ssi1-ce0-d", jz4780_ssi1_ce0_d, 2),
	INGENIC_PIN_GROUP("ssi1-ce0-e", jz4770_ssi1_ce0_e, 1),
	INGENIC_PIN_GROUP("ssi1-ce1-b", jz4780_ssi1_ce1_b, 2),
	INGENIC_PIN_GROUP("ssi1-ce1-d", jz4780_ssi1_ce1_d, 2),
	INGENIC_PIN_GROUP("ssi1-ce1-e", jz4770_ssi1_ce1_e, 1),
	INGENIC_PIN_GROUP_FUNCS("mmc0-1bit-a", jz4770_mmc0_1bit_a,
				jz4760_mmc0_1bit_a_funcs),
	INGENIC_PIN_GROUP("mmc0-4bit-a", jz4770_mmc0_4bit_a, 1),
	INGENIC_PIN_GROUP("mmc0-8bit-a", jz4780_mmc0_8bit_a, 1),
	INGENIC_PIN_GROUP("mmc0-1bit-e", jz4770_mmc0_1bit_e, 0),
	INGENIC_PIN_GROUP("mmc0-4bit-e", jz4770_mmc0_4bit_e, 0),
	INGENIC_PIN_GROUP("mmc1-1bit-d", jz4770_mmc1_1bit_d, 0),
	INGENIC_PIN_GROUP("mmc1-4bit-d", jz4770_mmc1_4bit_d, 0),
	INGENIC_PIN_GROUP("mmc1-1bit-e", jz4770_mmc1_1bit_e, 1),
	INGENIC_PIN_GROUP("mmc1-4bit-e", jz4770_mmc1_4bit_e, 1),
	INGENIC_PIN_GROUP("mmc2-1bit-b", jz4770_mmc2_1bit_b, 0),
	INGENIC_PIN_GROUP("mmc2-4bit-b", jz4770_mmc2_4bit_b, 0),
	INGENIC_PIN_GROUP("mmc2-1bit-e", jz4770_mmc2_1bit_e, 2),
	INGENIC_PIN_GROUP("mmc2-4bit-e", jz4770_mmc2_4bit_e, 2),
	INGENIC_PIN_GROUP("nemc-data", jz4770_nemc_8bit_data, 0),
	INGENIC_PIN_GROUP("nemc-cle-ale", jz4770_nemc_cle_ale, 0),
	INGENIC_PIN_GROUP("nemc-addr", jz4770_nemc_addr, 0),
	INGENIC_PIN_GROUP("nemc-rd-we", jz4770_nemc_rd_we, 0),
	INGENIC_PIN_GROUP("nemc-frd-fwe", jz4770_nemc_frd_fwe, 0),
	INGENIC_PIN_GROUP("nemc-wait", jz4770_nemc_रुको, 0),
	INGENIC_PIN_GROUP("nemc-cs1", jz4770_nemc_cs1, 0),
	INGENIC_PIN_GROUP("nemc-cs2", jz4770_nemc_cs2, 0),
	INGENIC_PIN_GROUP("nemc-cs3", jz4770_nemc_cs3, 0),
	INGENIC_PIN_GROUP("nemc-cs4", jz4770_nemc_cs4, 0),
	INGENIC_PIN_GROUP("nemc-cs5", jz4770_nemc_cs5, 0),
	INGENIC_PIN_GROUP("nemc-cs6", jz4770_nemc_cs6, 0),
	INGENIC_PIN_GROUP("i2c0-data", jz4770_i2c0, 0),
	INGENIC_PIN_GROUP("i2c1-data", jz4770_i2c1, 0),
	INGENIC_PIN_GROUP("i2c2-data", jz4770_i2c2, 2),
	INGENIC_PIN_GROUP("i2c3-data", jz4780_i2c3, 1),
	INGENIC_PIN_GROUP("i2c4-data-e", jz4780_i2c4_e, 1),
	INGENIC_PIN_GROUP("i2c4-data-f", jz4780_i2c4_f, 1),
	INGENIC_PIN_GROUP("i2s-data-tx", jz4780_i2s_data_tx, 0),
	INGENIC_PIN_GROUP("i2s-data-rx", jz4780_i2s_data_rx, 0),
	INGENIC_PIN_GROUP_FUNCS("i2s-clk-txrx", jz4780_i2s_clk_txrx,
				jz4780_i2s_clk_txrx_funcs),
	INGENIC_PIN_GROUP("i2s-clk-rx", jz4780_i2s_clk_rx, 1),
	INGENIC_PIN_GROUP("i2s-sysclk", jz4780_i2s_sysclk, 2),
	INGENIC_PIN_GROUP("dmic", jz4780_dmic, 1),
	INGENIC_PIN_GROUP("hdmi-ddc", jz4780_hdmi_ddc, 0),
	INGENIC_PIN_GROUP("cim-data", jz4770_cim_8bit, 0),
	INGENIC_PIN_GROUP("cim-data-12bit", jz4770_cim_12bit, 0),
	INGENIC_PIN_GROUP("lcd-8bit", jz4770_lcd_8bit, 0),
	INGENIC_PIN_GROUP("lcd-16bit", jz4770_lcd_16bit, 0),
	INGENIC_PIN_GROUP("lcd-18bit", jz4770_lcd_18bit, 0),
	INGENIC_PIN_GROUP("lcd-24bit", jz4770_lcd_24bit, 0),
	INGENIC_PIN_GROUP("lcd-special", jz4770_lcd_special, 1),
	INGENIC_PIN_GROUP("lcd-generic", jz4770_lcd_generic, 0),
	INGENIC_PIN_GROUP("pwm0", jz4770_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", jz4770_pwm_pwm1, 0),
	INGENIC_PIN_GROUP("pwm2", jz4770_pwm_pwm2, 0),
	INGENIC_PIN_GROUP("pwm3", jz4770_pwm_pwm3, 0),
	INGENIC_PIN_GROUP("pwm4", jz4770_pwm_pwm4, 0),
	INGENIC_PIN_GROUP("pwm5", jz4770_pwm_pwm5, 0),
	INGENIC_PIN_GROUP("pwm6", jz4770_pwm_pwm6, 0),
	INGENIC_PIN_GROUP("pwm7", jz4770_pwm_pwm7, 0),
पूर्ण;

अटल स्थिर अक्षर *jz4780_uart2_groups[] = अणु "uart2-data", "uart2-hwflow", पूर्ण;
अटल स्थिर अक्षर *jz4780_uart4_groups[] = अणु "uart4-data", पूर्ण;
अटल स्थिर अक्षर *jz4780_ssi0_groups[] = अणु
	"ssi0-dt-a-19", "ssi0-dt-a-21", "ssi0-dt-a-28", "ssi0-dt-b", "ssi0-dt-d", "ssi0-dt-e",
	"ssi0-dr-a-20", "ssi0-dr-a-27", "ssi0-dr-b", "ssi0-dr-d", "ssi0-dr-e",
	"ssi0-clk-a", "ssi0-clk-b-5", "ssi0-clk-b-28", "ssi0-clk-d", "ssi0-clk-e",
	"ssi0-gpc-b", "ssi0-gpc-d", "ssi0-gpc-e",
	"ssi0-ce0-a-23", "ssi0-ce0-a-25", "ssi0-ce0-b", "ssi0-ce0-d", "ssi0-ce0-e",
	"ssi0-ce1-b", "ssi0-ce1-d", "ssi0-ce1-e",
पूर्ण;
अटल स्थिर अक्षर *jz4780_ssi1_groups[] = अणु
	"ssi1-dt-b", "ssi1-dt-d", "ssi1-dt-e",
	"ssi1-dr-b", "ssi1-dr-d", "ssi1-dr-e",
	"ssi1-clk-b", "ssi1-clk-d", "ssi1-clk-e",
	"ssi1-gpc-b", "ssi1-gpc-d", "ssi1-gpc-e",
	"ssi1-ce0-b", "ssi1-ce0-d", "ssi1-ce0-e",
	"ssi1-ce1-b", "ssi1-ce1-d", "ssi1-ce1-e",
पूर्ण;
अटल स्थिर अक्षर *jz4780_mmc0_groups[] = अणु
	"mmc0-1bit-a", "mmc0-4bit-a", "mmc0-8bit-a",
	"mmc0-1bit-e", "mmc0-4bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4780_mmc1_groups[] = अणु
	"mmc1-1bit-d", "mmc1-4bit-d", "mmc1-1bit-e", "mmc1-4bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4780_mmc2_groups[] = अणु
	"mmc2-1bit-b", "mmc2-4bit-b", "mmc2-1bit-e", "mmc2-4bit-e",
पूर्ण;
अटल स्थिर अक्षर *jz4780_nemc_groups[] = अणु
	"nemc-data", "nemc-cle-ale", "nemc-addr",
	"nemc-rd-we", "nemc-frd-fwe", "nemc-wait",
पूर्ण;
अटल स्थिर अक्षर *jz4780_i2c3_groups[] = अणु "i2c3-data", पूर्ण;
अटल स्थिर अक्षर *jz4780_i2c4_groups[] = अणु "i2c4-data-e", "i2c4-data-f", पूर्ण;
अटल स्थिर अक्षर *jz4780_i2s_groups[] = अणु
	"i2s-data-tx", "i2s-data-rx", "i2s-clk-txrx", "i2s-clk-rx", "i2s-sysclk",
पूर्ण;
अटल स्थिर अक्षर *jz4780_dmic_groups[] = अणु "dmic", पूर्ण;
अटल स्थिर अक्षर *jz4780_cim_groups[] = अणु "cim-data", पूर्ण;
अटल स्थिर अक्षर *jz4780_hdmi_ddc_groups[] = अणु "hdmi-ddc", पूर्ण;

अटल स्थिर काष्ठा function_desc jz4780_functions[] = अणु
	अणु "uart0", jz4770_uart0_groups, ARRAY_SIZE(jz4770_uart0_groups), पूर्ण,
	अणु "uart1", jz4770_uart1_groups, ARRAY_SIZE(jz4770_uart1_groups), पूर्ण,
	अणु "uart2", jz4780_uart2_groups, ARRAY_SIZE(jz4780_uart2_groups), पूर्ण,
	अणु "uart3", jz4770_uart3_groups, ARRAY_SIZE(jz4770_uart3_groups), पूर्ण,
	अणु "uart4", jz4780_uart4_groups, ARRAY_SIZE(jz4780_uart4_groups), पूर्ण,
	अणु "ssi0", jz4780_ssi0_groups, ARRAY_SIZE(jz4780_ssi0_groups), पूर्ण,
	अणु "ssi1", jz4780_ssi1_groups, ARRAY_SIZE(jz4780_ssi1_groups), पूर्ण,
	अणु "mmc0", jz4780_mmc0_groups, ARRAY_SIZE(jz4780_mmc0_groups), पूर्ण,
	अणु "mmc1", jz4780_mmc1_groups, ARRAY_SIZE(jz4780_mmc1_groups), पूर्ण,
	अणु "mmc2", jz4780_mmc2_groups, ARRAY_SIZE(jz4780_mmc2_groups), पूर्ण,
	अणु "nemc", jz4780_nemc_groups, ARRAY_SIZE(jz4780_nemc_groups), पूर्ण,
	अणु "nemc-cs1", jz4770_cs1_groups, ARRAY_SIZE(jz4770_cs1_groups), पूर्ण,
	अणु "nemc-cs2", jz4770_cs2_groups, ARRAY_SIZE(jz4770_cs2_groups), पूर्ण,
	अणु "nemc-cs3", jz4770_cs3_groups, ARRAY_SIZE(jz4770_cs3_groups), पूर्ण,
	अणु "nemc-cs4", jz4770_cs4_groups, ARRAY_SIZE(jz4770_cs4_groups), पूर्ण,
	अणु "nemc-cs5", jz4770_cs5_groups, ARRAY_SIZE(jz4770_cs5_groups), पूर्ण,
	अणु "nemc-cs6", jz4770_cs6_groups, ARRAY_SIZE(jz4770_cs6_groups), पूर्ण,
	अणु "i2c0", jz4770_i2c0_groups, ARRAY_SIZE(jz4770_i2c0_groups), पूर्ण,
	अणु "i2c1", jz4770_i2c1_groups, ARRAY_SIZE(jz4770_i2c1_groups), पूर्ण,
	अणु "i2c2", jz4770_i2c2_groups, ARRAY_SIZE(jz4770_i2c2_groups), पूर्ण,
	अणु "i2c3", jz4780_i2c3_groups, ARRAY_SIZE(jz4780_i2c3_groups), पूर्ण,
	अणु "i2c4", jz4780_i2c4_groups, ARRAY_SIZE(jz4780_i2c4_groups), पूर्ण,
	अणु "i2s", jz4780_i2s_groups, ARRAY_SIZE(jz4780_i2s_groups), पूर्ण,
	अणु "dmic", jz4780_dmic_groups, ARRAY_SIZE(jz4780_dmic_groups), पूर्ण,
	अणु "cim", jz4780_cim_groups, ARRAY_SIZE(jz4780_cim_groups), पूर्ण,
	अणु "lcd", jz4770_lcd_groups, ARRAY_SIZE(jz4770_lcd_groups), पूर्ण,
	अणु "pwm0", jz4770_pwm0_groups, ARRAY_SIZE(jz4770_pwm0_groups), पूर्ण,
	अणु "pwm1", jz4770_pwm1_groups, ARRAY_SIZE(jz4770_pwm1_groups), पूर्ण,
	अणु "pwm2", jz4770_pwm2_groups, ARRAY_SIZE(jz4770_pwm2_groups), पूर्ण,
	अणु "pwm3", jz4770_pwm3_groups, ARRAY_SIZE(jz4770_pwm3_groups), पूर्ण,
	अणु "pwm4", jz4770_pwm4_groups, ARRAY_SIZE(jz4770_pwm4_groups), पूर्ण,
	अणु "pwm5", jz4770_pwm5_groups, ARRAY_SIZE(jz4770_pwm5_groups), पूर्ण,
	अणु "pwm6", jz4770_pwm6_groups, ARRAY_SIZE(jz4770_pwm6_groups), पूर्ण,
	अणु "pwm7", jz4770_pwm7_groups, ARRAY_SIZE(jz4770_pwm7_groups), पूर्ण,
	अणु "hdmi-ddc", jz4780_hdmi_ddc_groups,
		      ARRAY_SIZE(jz4780_hdmi_ddc_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info jz4780_chip_info = अणु
	.num_chips = 6,
	.reg_offset = 0x100,
	.version = ID_JZ4780,
	.groups = jz4780_groups,
	.num_groups = ARRAY_SIZE(jz4780_groups),
	.functions = jz4780_functions,
	.num_functions = ARRAY_SIZE(jz4780_functions),
	.pull_ups = jz4780_pull_ups,
	.pull_करोwns = jz4780_pull_करोwns,
पूर्ण;

अटल स्थिर u32 x1000_pull_ups[4] = अणु
	0xffffffff, 0xfdffffff, 0x0dffffff, 0x0000003f,
पूर्ण;

अटल स्थिर u32 x1000_pull_करोwns[4] = अणु
	0x00000000, 0x02000000, 0x02000000, 0x00000000,
पूर्ण;

अटल पूर्णांक x1000_uart0_data_pins[] = अणु 0x4a, 0x4b, पूर्ण;
अटल पूर्णांक x1000_uart0_hwflow_pins[] = अणु 0x4c, 0x4d, पूर्ण;
अटल पूर्णांक x1000_uart1_data_a_pins[] = अणु 0x04, 0x05, पूर्ण;
अटल पूर्णांक x1000_uart1_data_d_pins[] = अणु 0x62, 0x63, पूर्ण;
अटल पूर्णांक x1000_uart1_hwflow_pins[] = अणु 0x64, 0x65, पूर्ण;
अटल पूर्णांक x1000_uart2_data_a_pins[] = अणु 0x02, 0x03, पूर्ण;
अटल पूर्णांक x1000_uart2_data_d_pins[] = अणु 0x65, 0x64, पूर्ण;
अटल पूर्णांक x1000_sfc_pins[] = अणु 0x1d, 0x1c, 0x1e, 0x1f, 0x1a, 0x1b, पूर्ण;
अटल पूर्णांक x1000_ssi_dt_a_22_pins[] = अणु 0x16, पूर्ण;
अटल पूर्णांक x1000_ssi_dt_a_29_pins[] = अणु 0x1d, पूर्ण;
अटल पूर्णांक x1000_ssi_dt_d_pins[] = अणु 0x62, पूर्ण;
अटल पूर्णांक x1000_ssi_dr_a_23_pins[] = अणु 0x17, पूर्ण;
अटल पूर्णांक x1000_ssi_dr_a_28_pins[] = अणु 0x1c, पूर्ण;
अटल पूर्णांक x1000_ssi_dr_d_pins[] = अणु 0x63, पूर्ण;
अटल पूर्णांक x1000_ssi_clk_a_24_pins[] = अणु 0x18, पूर्ण;
अटल पूर्णांक x1000_ssi_clk_a_26_pins[] = अणु 0x1a, पूर्ण;
अटल पूर्णांक x1000_ssi_clk_d_pins[] = अणु 0x60, पूर्ण;
अटल पूर्णांक x1000_ssi_gpc_a_20_pins[] = अणु 0x14, पूर्ण;
अटल पूर्णांक x1000_ssi_gpc_a_31_pins[] = अणु 0x1f, पूर्ण;
अटल पूर्णांक x1000_ssi_ce0_a_25_pins[] = अणु 0x19, पूर्ण;
अटल पूर्णांक x1000_ssi_ce0_a_27_pins[] = अणु 0x1b, पूर्ण;
अटल पूर्णांक x1000_ssi_ce0_d_pins[] = अणु 0x61, पूर्ण;
अटल पूर्णांक x1000_ssi_ce1_a_21_pins[] = अणु 0x15, पूर्ण;
अटल पूर्णांक x1000_ssi_ce1_a_30_pins[] = अणु 0x1e, पूर्ण;
अटल पूर्णांक x1000_mmc0_1bit_pins[] = अणु 0x18, 0x19, 0x17, पूर्ण;
अटल पूर्णांक x1000_mmc0_4bit_pins[] = अणु 0x16, 0x15, 0x14, पूर्ण;
अटल पूर्णांक x1000_mmc0_8bit_pins[] = अणु 0x13, 0x12, 0x11, 0x10, पूर्ण;
अटल पूर्णांक x1000_mmc1_1bit_pins[] = अणु 0x40, 0x41, 0x42, पूर्ण;
अटल पूर्णांक x1000_mmc1_4bit_pins[] = अणु 0x43, 0x44, 0x45, पूर्ण;
अटल पूर्णांक x1000_emc_8bit_data_pins[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
पूर्ण;
अटल पूर्णांक x1000_emc_16bit_data_pins[] = अणु
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
पूर्ण;
अटल पूर्णांक x1000_emc_addr_pins[] = अणु
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
पूर्ण;
अटल पूर्णांक x1000_emc_rd_we_pins[] = अणु 0x30, 0x31, पूर्ण;
अटल पूर्णांक x1000_emc_रुको_pins[] = अणु 0x34, पूर्ण;
अटल पूर्णांक x1000_emc_cs1_pins[] = अणु 0x32, पूर्ण;
अटल पूर्णांक x1000_emc_cs2_pins[] = अणु 0x33, पूर्ण;
अटल पूर्णांक x1000_i2c0_pins[] = अणु 0x38, 0x37, पूर्ण;
अटल पूर्णांक x1000_i2c1_a_pins[] = अणु 0x01, 0x00, पूर्ण;
अटल पूर्णांक x1000_i2c1_c_pins[] = अणु 0x5b, 0x5a, पूर्ण;
अटल पूर्णांक x1000_i2c2_pins[] = अणु 0x61, 0x60, पूर्ण;
अटल पूर्णांक x1000_i2s_data_tx_pins[] = अणु 0x24, पूर्ण;
अटल पूर्णांक x1000_i2s_data_rx_pins[] = अणु 0x23, पूर्ण;
अटल पूर्णांक x1000_i2s_clk_txrx_pins[] = अणु 0x21, 0x22, पूर्ण;
अटल पूर्णांक x1000_i2s_sysclk_pins[] = अणु 0x20, पूर्ण;
अटल पूर्णांक x1000_dmic0_pins[] = अणु 0x35, 0x36, पूर्ण;
अटल पूर्णांक x1000_dmic1_pins[] = अणु 0x25, पूर्ण;
अटल पूर्णांक x1000_cim_pins[] = अणु
	0x08, 0x09, 0x0a, 0x0b,
	0x13, 0x12, 0x11, 0x10, 0x0f, 0x0e, 0x0d, 0x0c,
पूर्ण;
अटल पूर्णांक x1000_lcd_8bit_pins[] = अणु
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x30, 0x31, 0x32, 0x33, 0x34,
पूर्ण;
अटल पूर्णांक x1000_lcd_16bit_pins[] = अणु
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
पूर्ण;
अटल पूर्णांक x1000_pwm_pwm0_pins[] = अणु 0x59, पूर्ण;
अटल पूर्णांक x1000_pwm_pwm1_pins[] = अणु 0x5a, पूर्ण;
अटल पूर्णांक x1000_pwm_pwm2_pins[] = अणु 0x5b, पूर्ण;
अटल पूर्णांक x1000_pwm_pwm3_pins[] = अणु 0x26, पूर्ण;
अटल पूर्णांक x1000_pwm_pwm4_pins[] = अणु 0x58, पूर्ण;
अटल पूर्णांक x1000_mac_pins[] = अणु
	0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x26,
पूर्ण;

अटल स्थिर काष्ठा group_desc x1000_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", x1000_uart0_data, 0),
	INGENIC_PIN_GROUP("uart0-hwflow", x1000_uart0_hwflow, 0),
	INGENIC_PIN_GROUP("uart1-data-a", x1000_uart1_data_a, 2),
	INGENIC_PIN_GROUP("uart1-data-d", x1000_uart1_data_d, 1),
	INGENIC_PIN_GROUP("uart1-hwflow", x1000_uart1_hwflow, 1),
	INGENIC_PIN_GROUP("uart2-data-a", x1000_uart2_data_a, 2),
	INGENIC_PIN_GROUP("uart2-data-d", x1000_uart2_data_d, 0),
	INGENIC_PIN_GROUP("sfc", x1000_sfc, 1),
	INGENIC_PIN_GROUP("ssi-dt-a-22", x1000_ssi_dt_a_22, 2),
	INGENIC_PIN_GROUP("ssi-dt-a-29", x1000_ssi_dt_a_29, 2),
	INGENIC_PIN_GROUP("ssi-dt-d", x1000_ssi_dt_d, 0),
	INGENIC_PIN_GROUP("ssi-dr-a-23", x1000_ssi_dr_a_23, 2),
	INGENIC_PIN_GROUP("ssi-dr-a-28", x1000_ssi_dr_a_28, 2),
	INGENIC_PIN_GROUP("ssi-dr-d", x1000_ssi_dr_d, 0),
	INGENIC_PIN_GROUP("ssi-clk-a-24", x1000_ssi_clk_a_24, 2),
	INGENIC_PIN_GROUP("ssi-clk-a-26", x1000_ssi_clk_a_26, 2),
	INGENIC_PIN_GROUP("ssi-clk-d", x1000_ssi_clk_d, 0),
	INGENIC_PIN_GROUP("ssi-gpc-a-20", x1000_ssi_gpc_a_20, 2),
	INGENIC_PIN_GROUP("ssi-gpc-a-31", x1000_ssi_gpc_a_31, 2),
	INGENIC_PIN_GROUP("ssi-ce0-a-25", x1000_ssi_ce0_a_25, 2),
	INGENIC_PIN_GROUP("ssi-ce0-a-27", x1000_ssi_ce0_a_27, 2),
	INGENIC_PIN_GROUP("ssi-ce0-d", x1000_ssi_ce0_d, 0),
	INGENIC_PIN_GROUP("ssi-ce1-a-21", x1000_ssi_ce1_a_21, 2),
	INGENIC_PIN_GROUP("ssi-ce1-a-30", x1000_ssi_ce1_a_30, 2),
	INGENIC_PIN_GROUP("mmc0-1bit", x1000_mmc0_1bit, 1),
	INGENIC_PIN_GROUP("mmc0-4bit", x1000_mmc0_4bit, 1),
	INGENIC_PIN_GROUP("mmc0-8bit", x1000_mmc0_8bit, 1),
	INGENIC_PIN_GROUP("mmc1-1bit", x1000_mmc1_1bit, 0),
	INGENIC_PIN_GROUP("mmc1-4bit", x1000_mmc1_4bit, 0),
	INGENIC_PIN_GROUP("emc-8bit-data", x1000_emc_8bit_data, 0),
	INGENIC_PIN_GROUP("emc-16bit-data", x1000_emc_16bit_data, 0),
	INGENIC_PIN_GROUP("emc-addr", x1000_emc_addr, 0),
	INGENIC_PIN_GROUP("emc-rd-we", x1000_emc_rd_we, 0),
	INGENIC_PIN_GROUP("emc-wait", x1000_emc_रुको, 0),
	INGENIC_PIN_GROUP("emc-cs1", x1000_emc_cs1, 0),
	INGENIC_PIN_GROUP("emc-cs2", x1000_emc_cs2, 0),
	INGENIC_PIN_GROUP("i2c0-data", x1000_i2c0, 0),
	INGENIC_PIN_GROUP("i2c1-data-a", x1000_i2c1_a, 2),
	INGENIC_PIN_GROUP("i2c1-data-c", x1000_i2c1_c, 0),
	INGENIC_PIN_GROUP("i2c2-data", x1000_i2c2, 1),
	INGENIC_PIN_GROUP("i2s-data-tx", x1000_i2s_data_tx, 1),
	INGENIC_PIN_GROUP("i2s-data-rx", x1000_i2s_data_rx, 1),
	INGENIC_PIN_GROUP("i2s-clk-txrx", x1000_i2s_clk_txrx, 1),
	INGENIC_PIN_GROUP("i2s-sysclk", x1000_i2s_sysclk, 1),
	INGENIC_PIN_GROUP("dmic0", x1000_dmic0, 0),
	INGENIC_PIN_GROUP("dmic1", x1000_dmic1, 1),
	INGENIC_PIN_GROUP("cim-data", x1000_cim, 2),
	INGENIC_PIN_GROUP("lcd-8bit", x1000_lcd_8bit, 1),
	INGENIC_PIN_GROUP("lcd-16bit", x1000_lcd_16bit, 1),
	INGENIC_PIN_GROUP("pwm0", x1000_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", x1000_pwm_pwm1, 1),
	INGENIC_PIN_GROUP("pwm2", x1000_pwm_pwm2, 1),
	INGENIC_PIN_GROUP("pwm3", x1000_pwm_pwm3, 2),
	INGENIC_PIN_GROUP("pwm4", x1000_pwm_pwm4, 0),
	INGENIC_PIN_GROUP("mac", x1000_mac, 1),
पूर्ण;

अटल स्थिर अक्षर *x1000_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *x1000_uart1_groups[] = अणु
	"uart1-data-a", "uart1-data-d", "uart1-hwflow",
पूर्ण;
अटल स्थिर अक्षर *x1000_uart2_groups[] = अणु "uart2-data-a", "uart2-data-d", पूर्ण;
अटल स्थिर अक्षर *x1000_sfc_groups[] = अणु "sfc", पूर्ण;
अटल स्थिर अक्षर *x1000_ssi_groups[] = अणु
	"ssi-dt-a-22", "ssi-dt-a-29", "ssi-dt-d",
	"ssi-dr-a-23", "ssi-dr-a-28", "ssi-dr-d",
	"ssi-clk-a-24", "ssi-clk-a-26", "ssi-clk-d",
	"ssi-gpc-a-20", "ssi-gpc-a-31",
	"ssi-ce0-a-25", "ssi-ce0-a-27", "ssi-ce0-d",
	"ssi-ce1-a-21", "ssi-ce1-a-30",
पूर्ण;
अटल स्थिर अक्षर *x1000_mmc0_groups[] = अणु
	"mmc0-1bit", "mmc0-4bit", "mmc0-8bit",
पूर्ण;
अटल स्थिर अक्षर *x1000_mmc1_groups[] = अणु
	"mmc1-1bit", "mmc1-4bit",
पूर्ण;
अटल स्थिर अक्षर *x1000_emc_groups[] = अणु
	"emc-8bit-data", "emc-16bit-data",
	"emc-addr", "emc-rd-we", "emc-wait",
पूर्ण;
अटल स्थिर अक्षर *x1000_cs1_groups[] = अणु "emc-cs1", पूर्ण;
अटल स्थिर अक्षर *x1000_cs2_groups[] = अणु "emc-cs2", पूर्ण;
अटल स्थिर अक्षर *x1000_i2c0_groups[] = अणु "i2c0-data", पूर्ण;
अटल स्थिर अक्षर *x1000_i2c1_groups[] = अणु "i2c1-data-a", "i2c1-data-c", पूर्ण;
अटल स्थिर अक्षर *x1000_i2c2_groups[] = अणु "i2c2-data", पूर्ण;
अटल स्थिर अक्षर *x1000_i2s_groups[] = अणु
	"i2s-data-tx", "i2s-data-rx", "i2s-clk-txrx", "i2s-sysclk",
पूर्ण;
अटल स्थिर अक्षर *x1000_dmic_groups[] = अणु "dmic0", "dmic1", पूर्ण;
अटल स्थिर अक्षर *x1000_cim_groups[] = अणु "cim-data", पूर्ण;
अटल स्थिर अक्षर *x1000_lcd_groups[] = अणु "lcd-8bit", "lcd-16bit", पूर्ण;
अटल स्थिर अक्षर *x1000_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *x1000_pwm1_groups[] = अणु "pwm1", पूर्ण;
अटल स्थिर अक्षर *x1000_pwm2_groups[] = अणु "pwm2", पूर्ण;
अटल स्थिर अक्षर *x1000_pwm3_groups[] = अणु "pwm3", पूर्ण;
अटल स्थिर अक्षर *x1000_pwm4_groups[] = अणु "pwm4", पूर्ण;
अटल स्थिर अक्षर *x1000_mac_groups[] = अणु "mac", पूर्ण;

अटल स्थिर काष्ठा function_desc x1000_functions[] = अणु
	अणु "uart0", x1000_uart0_groups, ARRAY_SIZE(x1000_uart0_groups), पूर्ण,
	अणु "uart1", x1000_uart1_groups, ARRAY_SIZE(x1000_uart1_groups), पूर्ण,
	अणु "uart2", x1000_uart2_groups, ARRAY_SIZE(x1000_uart2_groups), पूर्ण,
	अणु "sfc", x1000_sfc_groups, ARRAY_SIZE(x1000_sfc_groups), पूर्ण,
	अणु "ssi", x1000_ssi_groups, ARRAY_SIZE(x1000_ssi_groups), पूर्ण,
	अणु "mmc0", x1000_mmc0_groups, ARRAY_SIZE(x1000_mmc0_groups), पूर्ण,
	अणु "mmc1", x1000_mmc1_groups, ARRAY_SIZE(x1000_mmc1_groups), पूर्ण,
	अणु "emc", x1000_emc_groups, ARRAY_SIZE(x1000_emc_groups), पूर्ण,
	अणु "emc-cs1", x1000_cs1_groups, ARRAY_SIZE(x1000_cs1_groups), पूर्ण,
	अणु "emc-cs2", x1000_cs2_groups, ARRAY_SIZE(x1000_cs2_groups), पूर्ण,
	अणु "i2c0", x1000_i2c0_groups, ARRAY_SIZE(x1000_i2c0_groups), पूर्ण,
	अणु "i2c1", x1000_i2c1_groups, ARRAY_SIZE(x1000_i2c1_groups), पूर्ण,
	अणु "i2c2", x1000_i2c2_groups, ARRAY_SIZE(x1000_i2c2_groups), पूर्ण,
	अणु "i2s", x1000_i2s_groups, ARRAY_SIZE(x1000_i2s_groups), पूर्ण,
	अणु "dmic", x1000_dmic_groups, ARRAY_SIZE(x1000_dmic_groups), पूर्ण,
	अणु "cim", x1000_cim_groups, ARRAY_SIZE(x1000_cim_groups), पूर्ण,
	अणु "lcd", x1000_lcd_groups, ARRAY_SIZE(x1000_lcd_groups), पूर्ण,
	अणु "pwm0", x1000_pwm0_groups, ARRAY_SIZE(x1000_pwm0_groups), पूर्ण,
	अणु "pwm1", x1000_pwm1_groups, ARRAY_SIZE(x1000_pwm1_groups), पूर्ण,
	अणु "pwm2", x1000_pwm2_groups, ARRAY_SIZE(x1000_pwm2_groups), पूर्ण,
	अणु "pwm3", x1000_pwm3_groups, ARRAY_SIZE(x1000_pwm3_groups), पूर्ण,
	अणु "pwm4", x1000_pwm4_groups, ARRAY_SIZE(x1000_pwm4_groups), पूर्ण,
	अणु "mac", x1000_mac_groups, ARRAY_SIZE(x1000_mac_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info x1000_chip_info = अणु
	.num_chips = 4,
	.reg_offset = 0x100,
	.version = ID_X1000,
	.groups = x1000_groups,
	.num_groups = ARRAY_SIZE(x1000_groups),
	.functions = x1000_functions,
	.num_functions = ARRAY_SIZE(x1000_functions),
	.pull_ups = x1000_pull_ups,
	.pull_करोwns = x1000_pull_करोwns,
पूर्ण;

अटल पूर्णांक x1500_uart0_data_pins[] = अणु 0x4a, 0x4b, पूर्ण;
अटल पूर्णांक x1500_uart0_hwflow_pins[] = अणु 0x4c, 0x4d, पूर्ण;
अटल पूर्णांक x1500_uart1_data_a_pins[] = अणु 0x04, 0x05, पूर्ण;
अटल पूर्णांक x1500_uart1_data_d_pins[] = अणु 0x62, 0x63, पूर्ण;
अटल पूर्णांक x1500_uart1_hwflow_pins[] = अणु 0x64, 0x65, पूर्ण;
अटल पूर्णांक x1500_uart2_data_a_pins[] = अणु 0x02, 0x03, पूर्ण;
अटल पूर्णांक x1500_uart2_data_d_pins[] = अणु 0x65, 0x64, पूर्ण;
अटल पूर्णांक x1500_mmc_1bit_pins[] = अणु 0x18, 0x19, 0x17, पूर्ण;
अटल पूर्णांक x1500_mmc_4bit_pins[] = अणु 0x16, 0x15, 0x14, पूर्ण;
अटल पूर्णांक x1500_i2c0_pins[] = अणु 0x38, 0x37, पूर्ण;
अटल पूर्णांक x1500_i2c1_a_pins[] = अणु 0x01, 0x00, पूर्ण;
अटल पूर्णांक x1500_i2c1_c_pins[] = अणु 0x5b, 0x5a, पूर्ण;
अटल पूर्णांक x1500_i2c2_pins[] = अणु 0x61, 0x60, पूर्ण;
अटल पूर्णांक x1500_i2s_data_tx_pins[] = अणु 0x24, पूर्ण;
अटल पूर्णांक x1500_i2s_data_rx_pins[] = अणु 0x23, पूर्ण;
अटल पूर्णांक x1500_i2s_clk_txrx_pins[] = अणु 0x21, 0x22, पूर्ण;
अटल पूर्णांक x1500_i2s_sysclk_pins[] = अणु 0x20, पूर्ण;
अटल पूर्णांक x1500_dmic0_pins[] = अणु 0x35, 0x36, पूर्ण;
अटल पूर्णांक x1500_dmic1_pins[] = अणु 0x25, पूर्ण;
अटल पूर्णांक x1500_cim_pins[] = अणु
	0x08, 0x09, 0x0a, 0x0b,
	0x13, 0x12, 0x11, 0x10, 0x0f, 0x0e, 0x0d, 0x0c,
पूर्ण;
अटल पूर्णांक x1500_pwm_pwm0_pins[] = अणु 0x59, पूर्ण;
अटल पूर्णांक x1500_pwm_pwm1_pins[] = अणु 0x5a, पूर्ण;
अटल पूर्णांक x1500_pwm_pwm2_pins[] = अणु 0x5b, पूर्ण;
अटल पूर्णांक x1500_pwm_pwm3_pins[] = अणु 0x26, पूर्ण;
अटल पूर्णांक x1500_pwm_pwm4_pins[] = अणु 0x58, पूर्ण;

अटल स्थिर काष्ठा group_desc x1500_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", x1500_uart0_data, 0),
	INGENIC_PIN_GROUP("uart0-hwflow", x1500_uart0_hwflow, 0),
	INGENIC_PIN_GROUP("uart1-data-a", x1500_uart1_data_a, 2),
	INGENIC_PIN_GROUP("uart1-data-d", x1500_uart1_data_d, 1),
	INGENIC_PIN_GROUP("uart1-hwflow", x1500_uart1_hwflow, 1),
	INGENIC_PIN_GROUP("uart2-data-a", x1500_uart2_data_a, 2),
	INGENIC_PIN_GROUP("uart2-data-d", x1500_uart2_data_d, 0),
	INGENIC_PIN_GROUP("sfc", x1000_sfc, 1),
	INGENIC_PIN_GROUP("mmc-1bit", x1500_mmc_1bit, 1),
	INGENIC_PIN_GROUP("mmc-4bit", x1500_mmc_4bit, 1),
	INGENIC_PIN_GROUP("i2c0-data", x1500_i2c0, 0),
	INGENIC_PIN_GROUP("i2c1-data-a", x1500_i2c1_a, 2),
	INGENIC_PIN_GROUP("i2c1-data-c", x1500_i2c1_c, 0),
	INGENIC_PIN_GROUP("i2c2-data", x1500_i2c2, 1),
	INGENIC_PIN_GROUP("i2s-data-tx", x1500_i2s_data_tx, 1),
	INGENIC_PIN_GROUP("i2s-data-rx", x1500_i2s_data_rx, 1),
	INGENIC_PIN_GROUP("i2s-clk-txrx", x1500_i2s_clk_txrx, 1),
	INGENIC_PIN_GROUP("i2s-sysclk", x1500_i2s_sysclk, 1),
	INGENIC_PIN_GROUP("dmic0", x1500_dmic0, 0),
	INGENIC_PIN_GROUP("dmic1", x1500_dmic1, 1),
	INGENIC_PIN_GROUP("cim-data", x1500_cim, 2),
	INGENIC_PIN_GROUP("pwm0", x1500_pwm_pwm0, 0),
	INGENIC_PIN_GROUP("pwm1", x1500_pwm_pwm1, 1),
	INGENIC_PIN_GROUP("pwm2", x1500_pwm_pwm2, 1),
	INGENIC_PIN_GROUP("pwm3", x1500_pwm_pwm3, 2),
	INGENIC_PIN_GROUP("pwm4", x1500_pwm_pwm4, 0),
पूर्ण;

अटल स्थिर अक्षर *x1500_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *x1500_uart1_groups[] = अणु
	"uart1-data-a", "uart1-data-d", "uart1-hwflow",
पूर्ण;
अटल स्थिर अक्षर *x1500_uart2_groups[] = अणु "uart2-data-a", "uart2-data-d", पूर्ण;
अटल स्थिर अक्षर *x1500_mmc_groups[] = अणु "mmc-1bit", "mmc-4bit", पूर्ण;
अटल स्थिर अक्षर *x1500_i2c0_groups[] = अणु "i2c0-data", पूर्ण;
अटल स्थिर अक्षर *x1500_i2c1_groups[] = अणु "i2c1-data-a", "i2c1-data-c", पूर्ण;
अटल स्थिर अक्षर *x1500_i2c2_groups[] = अणु "i2c2-data", पूर्ण;
अटल स्थिर अक्षर *x1500_i2s_groups[] = अणु
	"i2s-data-tx", "i2s-data-rx", "i2s-clk-txrx", "i2s-sysclk",
पूर्ण;
अटल स्थिर अक्षर *x1500_dmic_groups[] = अणु "dmic0", "dmic1", पूर्ण;
अटल स्थिर अक्षर *x1500_cim_groups[] = अणु "cim-data", पूर्ण;
अटल स्थिर अक्षर *x1500_pwm0_groups[] = अणु "pwm0", पूर्ण;
अटल स्थिर अक्षर *x1500_pwm1_groups[] = अणु "pwm1", पूर्ण;
अटल स्थिर अक्षर *x1500_pwm2_groups[] = अणु "pwm2", पूर्ण;
अटल स्थिर अक्षर *x1500_pwm3_groups[] = अणु "pwm3", पूर्ण;
अटल स्थिर अक्षर *x1500_pwm4_groups[] = अणु "pwm4", पूर्ण;

अटल स्थिर काष्ठा function_desc x1500_functions[] = अणु
	अणु "uart0", x1500_uart0_groups, ARRAY_SIZE(x1500_uart0_groups), पूर्ण,
	अणु "uart1", x1500_uart1_groups, ARRAY_SIZE(x1500_uart1_groups), पूर्ण,
	अणु "uart2", x1500_uart2_groups, ARRAY_SIZE(x1500_uart2_groups), पूर्ण,
	अणु "sfc", x1000_sfc_groups, ARRAY_SIZE(x1000_sfc_groups), पूर्ण,
	अणु "mmc", x1500_mmc_groups, ARRAY_SIZE(x1500_mmc_groups), पूर्ण,
	अणु "i2c0", x1500_i2c0_groups, ARRAY_SIZE(x1500_i2c0_groups), पूर्ण,
	अणु "i2c1", x1500_i2c1_groups, ARRAY_SIZE(x1500_i2c1_groups), पूर्ण,
	अणु "i2c2", x1500_i2c2_groups, ARRAY_SIZE(x1500_i2c2_groups), पूर्ण,
	अणु "i2s", x1500_i2s_groups, ARRAY_SIZE(x1500_i2s_groups), पूर्ण,
	अणु "dmic", x1500_dmic_groups, ARRAY_SIZE(x1500_dmic_groups), पूर्ण,
	अणु "cim", x1500_cim_groups, ARRAY_SIZE(x1500_cim_groups), पूर्ण,
	अणु "pwm0", x1500_pwm0_groups, ARRAY_SIZE(x1500_pwm0_groups), पूर्ण,
	अणु "pwm1", x1500_pwm1_groups, ARRAY_SIZE(x1500_pwm1_groups), पूर्ण,
	अणु "pwm2", x1500_pwm2_groups, ARRAY_SIZE(x1500_pwm2_groups), पूर्ण,
	अणु "pwm3", x1500_pwm3_groups, ARRAY_SIZE(x1500_pwm3_groups), पूर्ण,
	अणु "pwm4", x1500_pwm4_groups, ARRAY_SIZE(x1500_pwm4_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info x1500_chip_info = अणु
	.num_chips = 4,
	.reg_offset = 0x100,
	.version = ID_X1500,
	.groups = x1500_groups,
	.num_groups = ARRAY_SIZE(x1500_groups),
	.functions = x1500_functions,
	.num_functions = ARRAY_SIZE(x1500_functions),
	.pull_ups = x1000_pull_ups,
	.pull_करोwns = x1000_pull_करोwns,
पूर्ण;

अटल स्थिर u32 x1830_pull_ups[4] = अणु
	0x5fdfffc0, 0xffffefff, 0x1ffffbff, 0x0fcff3fc,
पूर्ण;

अटल स्थिर u32 x1830_pull_करोwns[4] = अणु
	0x5fdfffc0, 0xffffefff, 0x1ffffbff, 0x0fcff3fc,
पूर्ण;

अटल पूर्णांक x1830_uart0_data_pins[] = अणु 0x33, 0x36, पूर्ण;
अटल पूर्णांक x1830_uart0_hwflow_pins[] = अणु 0x34, 0x35, पूर्ण;
अटल पूर्णांक x1830_uart1_data_pins[] = अणु 0x38, 0x37, पूर्ण;
अटल पूर्णांक x1830_sfc_pins[] = अणु 0x17, 0x18, 0x1a, 0x19, 0x1b, 0x1c, पूर्ण;
अटल पूर्णांक x1830_ssi0_dt_pins[] = अणु 0x4c, पूर्ण;
अटल पूर्णांक x1830_ssi0_dr_pins[] = अणु 0x4b, पूर्ण;
अटल पूर्णांक x1830_ssi0_clk_pins[] = अणु 0x4f, पूर्ण;
अटल पूर्णांक x1830_ssi0_gpc_pins[] = अणु 0x4d, पूर्ण;
अटल पूर्णांक x1830_ssi0_ce0_pins[] = अणु 0x50, पूर्ण;
अटल पूर्णांक x1830_ssi0_ce1_pins[] = अणु 0x4e, पूर्ण;
अटल पूर्णांक x1830_ssi1_dt_c_pins[] = अणु 0x53, पूर्ण;
अटल पूर्णांक x1830_ssi1_dt_d_pins[] = अणु 0x62, पूर्ण;
अटल पूर्णांक x1830_ssi1_dr_c_pins[] = अणु 0x54, पूर्ण;
अटल पूर्णांक x1830_ssi1_dr_d_pins[] = अणु 0x63, पूर्ण;
अटल पूर्णांक x1830_ssi1_clk_c_pins[] = अणु 0x57, पूर्ण;
अटल पूर्णांक x1830_ssi1_clk_d_pins[] = अणु 0x66, पूर्ण;
अटल पूर्णांक x1830_ssi1_gpc_c_pins[] = अणु 0x55, पूर्ण;
अटल पूर्णांक x1830_ssi1_gpc_d_pins[] = अणु 0x64, पूर्ण;
अटल पूर्णांक x1830_ssi1_ce0_c_pins[] = अणु 0x58, पूर्ण;
अटल पूर्णांक x1830_ssi1_ce0_d_pins[] = अणु 0x67, पूर्ण;
अटल पूर्णांक x1830_ssi1_ce1_c_pins[] = अणु 0x56, पूर्ण;
अटल पूर्णांक x1830_ssi1_ce1_d_pins[] = अणु 0x65, पूर्ण;
अटल पूर्णांक x1830_mmc0_1bit_pins[] = अणु 0x24, 0x25, 0x20, पूर्ण;
अटल पूर्णांक x1830_mmc0_4bit_pins[] = अणु 0x21, 0x22, 0x23, पूर्ण;
अटल पूर्णांक x1830_mmc1_1bit_pins[] = अणु 0x42, 0x43, 0x44, पूर्ण;
अटल पूर्णांक x1830_mmc1_4bit_pins[] = अणु 0x45, 0x46, 0x47, पूर्ण;
अटल पूर्णांक x1830_i2c0_pins[] = अणु 0x0c, 0x0d, पूर्ण;
अटल पूर्णांक x1830_i2c1_pins[] = अणु 0x39, 0x3a, पूर्ण;
अटल पूर्णांक x1830_i2c2_pins[] = अणु 0x5b, 0x5c, पूर्ण;
अटल पूर्णांक x1830_i2s_data_tx_pins[] = अणु 0x53, पूर्ण;
अटल पूर्णांक x1830_i2s_data_rx_pins[] = अणु 0x54, पूर्ण;
अटल पूर्णांक x1830_i2s_clk_txrx_pins[] = अणु 0x58, 0x52, पूर्ण;
अटल पूर्णांक x1830_i2s_clk_rx_pins[] = अणु 0x56, 0x55, पूर्ण;
अटल पूर्णांक x1830_i2s_sysclk_pins[] = अणु 0x57, पूर्ण;
अटल पूर्णांक x1830_dmic0_pins[] = अणु 0x48, 0x59, पूर्ण;
अटल पूर्णांक x1830_dmic1_pins[] = अणु 0x5a, पूर्ण;
अटल पूर्णांक x1830_lcd_tft_8bit_pins[] = अणु
	0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x68, 0x73, 0x72, 0x69,
पूर्ण;
अटल पूर्णांक x1830_lcd_tft_24bit_pins[] = अणु
	0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71,
	0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b,
पूर्ण;
अटल पूर्णांक x1830_lcd_slcd_8bit_pins[] = अणु
	0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x6c, 0x6d,
	0x69, 0x72, 0x73, 0x7b, 0x7a,
पूर्ण;
अटल पूर्णांक x1830_lcd_slcd_16bit_pins[] = अणु
	0x6e, 0x6f, 0x70, 0x71, 0x76, 0x77, 0x78, 0x79,
पूर्ण;
अटल पूर्णांक x1830_pwm_pwm0_b_pins[] = अणु 0x31, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm0_c_pins[] = अणु 0x4b, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm1_b_pins[] = अणु 0x32, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm1_c_pins[] = अणु 0x4c, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm2_c_8_pins[] = अणु 0x48, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm2_c_13_pins[] = अणु 0x4d, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm3_c_9_pins[] = अणु 0x49, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm3_c_14_pins[] = अणु 0x4e, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm4_c_15_pins[] = अणु 0x4f, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm4_c_25_pins[] = अणु 0x59, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm5_c_16_pins[] = अणु 0x50, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm5_c_26_pins[] = अणु 0x5a, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm6_c_17_pins[] = अणु 0x51, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm6_c_27_pins[] = अणु 0x5b, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm7_c_18_pins[] = अणु 0x52, पूर्ण;
अटल पूर्णांक x1830_pwm_pwm7_c_28_pins[] = अणु 0x5c, पूर्ण;
अटल पूर्णांक x1830_mac_pins[] = अणु
	0x29, 0x30, 0x2f, 0x28, 0x2e, 0x2d, 0x2a, 0x2b, 0x26, 0x27,
पूर्ण;

अटल स्थिर काष्ठा group_desc x1830_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", x1830_uart0_data, 0),
	INGENIC_PIN_GROUP("uart0-hwflow", x1830_uart0_hwflow, 0),
	INGENIC_PIN_GROUP("uart1-data", x1830_uart1_data, 0),
	INGENIC_PIN_GROUP("sfc", x1830_sfc, 1),
	INGENIC_PIN_GROUP("ssi0-dt", x1830_ssi0_dt, 0),
	INGENIC_PIN_GROUP("ssi0-dr", x1830_ssi0_dr, 0),
	INGENIC_PIN_GROUP("ssi0-clk", x1830_ssi0_clk, 0),
	INGENIC_PIN_GROUP("ssi0-gpc", x1830_ssi0_gpc, 0),
	INGENIC_PIN_GROUP("ssi0-ce0", x1830_ssi0_ce0, 0),
	INGENIC_PIN_GROUP("ssi0-ce1", x1830_ssi0_ce1, 0),
	INGENIC_PIN_GROUP("ssi1-dt-c", x1830_ssi1_dt_c, 1),
	INGENIC_PIN_GROUP("ssi1-dr-c", x1830_ssi1_dr_c, 1),
	INGENIC_PIN_GROUP("ssi1-clk-c", x1830_ssi1_clk_c, 1),
	INGENIC_PIN_GROUP("ssi1-gpc-c", x1830_ssi1_gpc_c, 1),
	INGENIC_PIN_GROUP("ssi1-ce0-c", x1830_ssi1_ce0_c, 1),
	INGENIC_PIN_GROUP("ssi1-ce1-c", x1830_ssi1_ce1_c, 1),
	INGENIC_PIN_GROUP("ssi1-dt-d", x1830_ssi1_dt_d, 2),
	INGENIC_PIN_GROUP("ssi1-dr-d", x1830_ssi1_dr_d, 2),
	INGENIC_PIN_GROUP("ssi1-clk-d", x1830_ssi1_clk_d, 2),
	INGENIC_PIN_GROUP("ssi1-gpc-d", x1830_ssi1_gpc_d, 2),
	INGENIC_PIN_GROUP("ssi1-ce0-d", x1830_ssi1_ce0_d, 2),
	INGENIC_PIN_GROUP("ssi1-ce1-d", x1830_ssi1_ce1_d, 2),
	INGENIC_PIN_GROUP("mmc0-1bit", x1830_mmc0_1bit, 0),
	INGENIC_PIN_GROUP("mmc0-4bit", x1830_mmc0_4bit, 0),
	INGENIC_PIN_GROUP("mmc1-1bit", x1830_mmc1_1bit, 0),
	INGENIC_PIN_GROUP("mmc1-4bit", x1830_mmc1_4bit, 0),
	INGENIC_PIN_GROUP("i2c0-data", x1830_i2c0, 1),
	INGENIC_PIN_GROUP("i2c1-data", x1830_i2c1, 0),
	INGENIC_PIN_GROUP("i2c2-data", x1830_i2c2, 1),
	INGENIC_PIN_GROUP("i2s-data-tx", x1830_i2s_data_tx, 0),
	INGENIC_PIN_GROUP("i2s-data-rx", x1830_i2s_data_rx, 0),
	INGENIC_PIN_GROUP("i2s-clk-txrx", x1830_i2s_clk_txrx, 0),
	INGENIC_PIN_GROUP("i2s-clk-rx", x1830_i2s_clk_rx, 0),
	INGENIC_PIN_GROUP("i2s-sysclk", x1830_i2s_sysclk, 0),
	INGENIC_PIN_GROUP("dmic0", x1830_dmic0, 2),
	INGENIC_PIN_GROUP("dmic1", x1830_dmic1, 2),
	INGENIC_PIN_GROUP("lcd-tft-8bit", x1830_lcd_tft_8bit, 0),
	INGENIC_PIN_GROUP("lcd-tft-24bit", x1830_lcd_tft_24bit, 0),
	INGENIC_PIN_GROUP("lcd-slcd-8bit", x1830_lcd_slcd_8bit, 1),
	INGENIC_PIN_GROUP("lcd-slcd-16bit", x1830_lcd_slcd_16bit, 1),
	INGENIC_PIN_GROUP("pwm0-b", x1830_pwm_pwm0_b, 0),
	INGENIC_PIN_GROUP("pwm0-c", x1830_pwm_pwm0_c, 1),
	INGENIC_PIN_GROUP("pwm1-b", x1830_pwm_pwm1_b, 0),
	INGENIC_PIN_GROUP("pwm1-c", x1830_pwm_pwm1_c, 1),
	INGENIC_PIN_GROUP("pwm2-c-8", x1830_pwm_pwm2_c_8, 0),
	INGENIC_PIN_GROUP("pwm2-c-13", x1830_pwm_pwm2_c_13, 1),
	INGENIC_PIN_GROUP("pwm3-c-9", x1830_pwm_pwm3_c_9, 0),
	INGENIC_PIN_GROUP("pwm3-c-14", x1830_pwm_pwm3_c_14, 1),
	INGENIC_PIN_GROUP("pwm4-c-15", x1830_pwm_pwm4_c_15, 1),
	INGENIC_PIN_GROUP("pwm4-c-25", x1830_pwm_pwm4_c_25, 0),
	INGENIC_PIN_GROUP("pwm5-c-16", x1830_pwm_pwm5_c_16, 1),
	INGENIC_PIN_GROUP("pwm5-c-26", x1830_pwm_pwm5_c_26, 0),
	INGENIC_PIN_GROUP("pwm6-c-17", x1830_pwm_pwm6_c_17, 1),
	INGENIC_PIN_GROUP("pwm6-c-27", x1830_pwm_pwm6_c_27, 0),
	INGENIC_PIN_GROUP("pwm7-c-18", x1830_pwm_pwm7_c_18, 1),
	INGENIC_PIN_GROUP("pwm7-c-28", x1830_pwm_pwm7_c_28, 0),
	INGENIC_PIN_GROUP("mac", x1830_mac, 0),
पूर्ण;

अटल स्थिर अक्षर *x1830_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *x1830_uart1_groups[] = अणु "uart1-data", पूर्ण;
अटल स्थिर अक्षर *x1830_sfc_groups[] = अणु "sfc", पूर्ण;
अटल स्थिर अक्षर *x1830_ssi0_groups[] = अणु
	"ssi0-dt", "ssi0-dr", "ssi0-clk", "ssi0-gpc", "ssi0-ce0", "ssi0-ce1",
पूर्ण;
अटल स्थिर अक्षर *x1830_ssi1_groups[] = अणु
	"ssi1-dt-c", "ssi1-dt-d",
	"ssi1-dr-c", "ssi1-dr-d",
	"ssi1-clk-c", "ssi1-clk-d",
	"ssi1-gpc-c", "ssi1-gpc-d",
	"ssi1-ce0-c", "ssi1-ce0-d",
	"ssi1-ce1-c", "ssi1-ce1-d",
पूर्ण;
अटल स्थिर अक्षर *x1830_mmc0_groups[] = अणु "mmc0-1bit", "mmc0-4bit", पूर्ण;
अटल स्थिर अक्षर *x1830_mmc1_groups[] = अणु "mmc1-1bit", "mmc1-4bit", पूर्ण;
अटल स्थिर अक्षर *x1830_i2c0_groups[] = अणु "i2c0-data", पूर्ण;
अटल स्थिर अक्षर *x1830_i2c1_groups[] = अणु "i2c1-data", पूर्ण;
अटल स्थिर अक्षर *x1830_i2c2_groups[] = अणु "i2c2-data", पूर्ण;
अटल स्थिर अक्षर *x1830_i2s_groups[] = अणु
	"i2s-data-tx", "i2s-data-rx", "i2s-clk-txrx", "i2s-clk-rx", "i2s-sysclk",
पूर्ण;
अटल स्थिर अक्षर *x1830_dmic_groups[] = अणु "dmic0", "dmic1", पूर्ण;
अटल स्थिर अक्षर *x1830_lcd_groups[] = अणु
	"lcd-tft-8bit", "lcd-tft-24bit", "lcd-slcd-8bit", "lcd-slcd-16bit",
पूर्ण;
अटल स्थिर अक्षर *x1830_pwm0_groups[] = अणु "pwm0-b", "pwm0-c", पूर्ण;
अटल स्थिर अक्षर *x1830_pwm1_groups[] = अणु "pwm1-b", "pwm1-c", पूर्ण;
अटल स्थिर अक्षर *x1830_pwm2_groups[] = अणु "pwm2-c-8", "pwm2-c-13", पूर्ण;
अटल स्थिर अक्षर *x1830_pwm3_groups[] = अणु "pwm3-c-9", "pwm3-c-14", पूर्ण;
अटल स्थिर अक्षर *x1830_pwm4_groups[] = अणु "pwm4-c-15", "pwm4-c-25", पूर्ण;
अटल स्थिर अक्षर *x1830_pwm5_groups[] = अणु "pwm5-c-16", "pwm5-c-26", पूर्ण;
अटल स्थिर अक्षर *x1830_pwm6_groups[] = अणु "pwm6-c-17", "pwm6-c-27", पूर्ण;
अटल स्थिर अक्षर *x1830_pwm7_groups[] = अणु "pwm7-c-18", "pwm7-c-28", पूर्ण;
अटल स्थिर अक्षर *x1830_mac_groups[] = अणु "mac", पूर्ण;

अटल स्थिर काष्ठा function_desc x1830_functions[] = अणु
	अणु "uart0", x1830_uart0_groups, ARRAY_SIZE(x1830_uart0_groups), पूर्ण,
	अणु "uart1", x1830_uart1_groups, ARRAY_SIZE(x1830_uart1_groups), पूर्ण,
	अणु "sfc", x1830_sfc_groups, ARRAY_SIZE(x1830_sfc_groups), पूर्ण,
	अणु "ssi0", x1830_ssi0_groups, ARRAY_SIZE(x1830_ssi0_groups), पूर्ण,
	अणु "ssi1", x1830_ssi1_groups, ARRAY_SIZE(x1830_ssi1_groups), पूर्ण,
	अणु "mmc0", x1830_mmc0_groups, ARRAY_SIZE(x1830_mmc0_groups), पूर्ण,
	अणु "mmc1", x1830_mmc1_groups, ARRAY_SIZE(x1830_mmc1_groups), पूर्ण,
	अणु "i2c0", x1830_i2c0_groups, ARRAY_SIZE(x1830_i2c0_groups), पूर्ण,
	अणु "i2c1", x1830_i2c1_groups, ARRAY_SIZE(x1830_i2c1_groups), पूर्ण,
	अणु "i2c2", x1830_i2c2_groups, ARRAY_SIZE(x1830_i2c2_groups), पूर्ण,
	अणु "i2s", x1830_i2s_groups, ARRAY_SIZE(x1830_i2s_groups), पूर्ण,
	अणु "dmic", x1830_dmic_groups, ARRAY_SIZE(x1830_dmic_groups), पूर्ण,
	अणु "lcd", x1830_lcd_groups, ARRAY_SIZE(x1830_lcd_groups), पूर्ण,
	अणु "pwm0", x1830_pwm0_groups, ARRAY_SIZE(x1830_pwm0_groups), पूर्ण,
	अणु "pwm1", x1830_pwm1_groups, ARRAY_SIZE(x1830_pwm1_groups), पूर्ण,
	अणु "pwm2", x1830_pwm2_groups, ARRAY_SIZE(x1830_pwm2_groups), पूर्ण,
	अणु "pwm3", x1830_pwm3_groups, ARRAY_SIZE(x1830_pwm3_groups), पूर्ण,
	अणु "pwm4", x1830_pwm4_groups, ARRAY_SIZE(x1830_pwm4_groups), पूर्ण,
	अणु "pwm5", x1830_pwm5_groups, ARRAY_SIZE(x1830_pwm4_groups), पूर्ण,
	अणु "pwm6", x1830_pwm6_groups, ARRAY_SIZE(x1830_pwm4_groups), पूर्ण,
	अणु "pwm7", x1830_pwm7_groups, ARRAY_SIZE(x1830_pwm4_groups), पूर्ण,
	अणु "mac", x1830_mac_groups, ARRAY_SIZE(x1830_mac_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info x1830_chip_info = अणु
	.num_chips = 4,
	.reg_offset = 0x1000,
	.version = ID_X1830,
	.groups = x1830_groups,
	.num_groups = ARRAY_SIZE(x1830_groups),
	.functions = x1830_functions,
	.num_functions = ARRAY_SIZE(x1830_functions),
	.pull_ups = x1830_pull_ups,
	.pull_करोwns = x1830_pull_करोwns,
पूर्ण;

अटल स्थिर u32 x2000_pull_ups[5] = अणु
	0x0003ffff, 0xffffffff, 0x1ff0ffff, 0xc7fe3f3f, 0x8fff003f,
पूर्ण;

अटल स्थिर u32 x2000_pull_करोwns[5] = अणु
	0x0003ffff, 0xffffffff, 0x1ff0ffff, 0x00000000, 0x8fff003f,
पूर्ण;

अटल पूर्णांक x2000_uart0_data_pins[] = अणु 0x77, 0x78, पूर्ण;
अटल पूर्णांक x2000_uart0_hwflow_pins[] = अणु 0x79, 0x7a, पूर्ण;
अटल पूर्णांक x2000_uart1_data_pins[] = अणु 0x57, 0x58, पूर्ण;
अटल पूर्णांक x2000_uart1_hwflow_pins[] = अणु 0x55, 0x56, पूर्ण;
अटल पूर्णांक x2000_uart2_data_pins[] = अणु 0x7e, 0x7f, पूर्ण;
अटल पूर्णांक x2000_uart3_data_c_pins[] = अणु 0x59, 0x5a, पूर्ण;
अटल पूर्णांक x2000_uart3_data_d_pins[] = अणु 0x62, 0x63, पूर्ण;
अटल पूर्णांक x2000_uart3_hwflow_c_pins[] = अणु 0x5b, 0x5c, पूर्ण;
अटल पूर्णांक x2000_uart3_hwflow_d_pins[] = अणु 0x60, 0x61, पूर्ण;
अटल पूर्णांक x2000_uart4_data_a_pins[] = अणु 0x02, 0x03, पूर्ण;
अटल पूर्णांक x2000_uart4_data_c_pins[] = अणु 0x4b, 0x4c, पूर्ण;
अटल पूर्णांक x2000_uart4_hwflow_a_pins[] = अणु 0x00, 0x01, पूर्ण;
अटल पूर्णांक x2000_uart4_hwflow_c_pins[] = अणु 0x49, 0x4a, पूर्ण;
अटल पूर्णांक x2000_uart5_data_a_pins[] = अणु 0x04, 0x05, पूर्ण;
अटल पूर्णांक x2000_uart5_data_c_pins[] = अणु 0x45, 0x46, पूर्ण;
अटल पूर्णांक x2000_uart6_data_a_pins[] = अणु 0x06, 0x07, पूर्ण;
अटल पूर्णांक x2000_uart6_data_c_pins[] = अणु 0x47, 0x48, पूर्ण;
अटल पूर्णांक x2000_uart7_data_a_pins[] = अणु 0x08, 0x09, पूर्ण;
अटल पूर्णांक x2000_uart7_data_c_pins[] = अणु 0x41, 0x42, पूर्ण;
अटल पूर्णांक x2000_uart8_data_pins[] = अणु 0x3c, 0x3d, पूर्ण;
अटल पूर्णांक x2000_uart9_data_pins[] = अणु 0x3e, 0x3f, पूर्ण;
अटल पूर्णांक x2000_sfc0_d_pins[] = अणु 0x73, 0x74, 0x75, 0x76, 0x71, 0x72, पूर्ण;
अटल पूर्णांक x2000_sfc0_e_pins[] = अणु 0x92, 0x93, 0x94, 0x95, 0x90, 0x91, पूर्ण;
अटल पूर्णांक x2000_sfc1_pins[] = अणु 0x77, 0x78, 0x79, 0x7a, पूर्ण;
अटल पूर्णांक x2000_ssi0_dt_b_pins[] = अणु 0x3e, पूर्ण;
अटल पूर्णांक x2000_ssi0_dt_d_pins[] = अणु 0x69, पूर्ण;
अटल पूर्णांक x2000_ssi0_dr_b_pins[] = अणु 0x3d, पूर्ण;
अटल पूर्णांक x2000_ssi0_dr_d_pins[] = अणु 0x6a, पूर्ण;
अटल पूर्णांक x2000_ssi0_clk_b_pins[] = अणु 0x3f, पूर्ण;
अटल पूर्णांक x2000_ssi0_clk_d_pins[] = अणु 0x68, पूर्ण;
अटल पूर्णांक x2000_ssi0_ce0_b_pins[] = अणु 0x3c, पूर्ण;
अटल पूर्णांक x2000_ssi0_ce0_d_pins[] = अणु 0x6d, पूर्ण;
अटल पूर्णांक x2000_ssi1_dt_c_pins[] = अणु 0x4b, पूर्ण;
अटल पूर्णांक x2000_ssi1_dt_d_pins[] = अणु 0x72, पूर्ण;
अटल पूर्णांक x2000_ssi1_dt_e_pins[] = अणु 0x91, पूर्ण;
अटल पूर्णांक x2000_ssi1_dr_c_pins[] = अणु 0x4a, पूर्ण;
अटल पूर्णांक x2000_ssi1_dr_d_pins[] = अणु 0x73, पूर्ण;
अटल पूर्णांक x2000_ssi1_dr_e_pins[] = अणु 0x92, पूर्ण;
अटल पूर्णांक x2000_ssi1_clk_c_pins[] = अणु 0x4c, पूर्ण;
अटल पूर्णांक x2000_ssi1_clk_d_pins[] = अणु 0x71, पूर्ण;
अटल पूर्णांक x2000_ssi1_clk_e_pins[] = अणु 0x90, पूर्ण;
अटल पूर्णांक x2000_ssi1_ce0_c_pins[] = अणु 0x49, पूर्ण;
अटल पूर्णांक x2000_ssi1_ce0_d_pins[] = अणु 0x76, पूर्ण;
अटल पूर्णांक x2000_ssi1_ce0_e_pins[] = अणु 0x95, पूर्ण;
अटल पूर्णांक x2000_mmc0_1bit_pins[] = अणु 0x71, 0x72, 0x73, पूर्ण;
अटल पूर्णांक x2000_mmc0_4bit_pins[] = अणु 0x74, 0x75, 0x75, पूर्ण;
अटल पूर्णांक x2000_mmc0_8bit_pins[] = अणु 0x77, 0x78, 0x79, 0x7a, पूर्ण;
अटल पूर्णांक x2000_mmc1_1bit_pins[] = अणु 0x68, 0x69, 0x6a, पूर्ण;
अटल पूर्णांक x2000_mmc1_4bit_pins[] = अणु 0x6b, 0x6c, 0x6d, पूर्ण;
अटल पूर्णांक x2000_mmc2_1bit_pins[] = अणु 0x80, 0x81, 0x82, पूर्ण;
अटल पूर्णांक x2000_mmc2_4bit_pins[] = अणु 0x83, 0x84, 0x85, पूर्ण;
अटल पूर्णांक x2000_emc_8bit_data_pins[] = अणु
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
पूर्ण;
अटल पूर्णांक x2000_emc_16bit_data_pins[] = अणु
	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
पूर्ण;
अटल पूर्णांक x2000_emc_addr_pins[] = अणु
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x28, 0x29, 0x2a, 0x2b, 0x2c,
पूर्ण;
अटल पूर्णांक x2000_emc_rd_we_pins[] = अणु 0x2d, 0x2e, पूर्ण;
अटल पूर्णांक x2000_emc_रुको_pins[] = अणु 0x2f, पूर्ण;
अटल पूर्णांक x2000_emc_cs1_pins[] = अणु 0x57, पूर्ण;
अटल पूर्णांक x2000_emc_cs2_pins[] = अणु 0x58, पूर्ण;
अटल पूर्णांक x2000_i2c0_pins[] = अणु 0x4e, 0x4d, पूर्ण;
अटल पूर्णांक x2000_i2c1_c_pins[] = अणु 0x58, 0x57, पूर्ण;
अटल पूर्णांक x2000_i2c1_d_pins[] = अणु 0x6c, 0x6b, पूर्ण;
अटल पूर्णांक x2000_i2c2_b_pins[] = अणु 0x37, 0x36, पूर्ण;
अटल पूर्णांक x2000_i2c2_d_pins[] = अणु 0x75, 0x74, पूर्ण;
अटल पूर्णांक x2000_i2c2_e_pins[] = अणु 0x94, 0x93, पूर्ण;
अटल पूर्णांक x2000_i2c3_a_pins[] = अणु 0x11, 0x10, पूर्ण;
अटल पूर्णांक x2000_i2c3_d_pins[] = अणु 0x7f, 0x7e, पूर्ण;
अटल पूर्णांक x2000_i2c4_c_pins[] = अणु 0x5a, 0x59, पूर्ण;
अटल पूर्णांक x2000_i2c4_d_pins[] = अणु 0x61, 0x60, पूर्ण;
अटल पूर्णांक x2000_i2c5_c_pins[] = अणु 0x5c, 0x5b, पूर्ण;
अटल पूर्णांक x2000_i2c5_d_pins[] = अणु 0x65, 0x64, पूर्ण;
अटल पूर्णांक x2000_i2s1_data_tx_pins[] = अणु 0x47, पूर्ण;
अटल पूर्णांक x2000_i2s1_data_rx_pins[] = अणु 0x44, पूर्ण;
अटल पूर्णांक x2000_i2s1_clk_tx_pins[] = अणु 0x45, 0x46, पूर्ण;
अटल पूर्णांक x2000_i2s1_clk_rx_pins[] = अणु 0x42, 0x43, पूर्ण;
अटल पूर्णांक x2000_i2s1_sysclk_tx_pins[] = अणु 0x48, पूर्ण;
अटल पूर्णांक x2000_i2s1_sysclk_rx_pins[] = अणु 0x41, पूर्ण;
अटल पूर्णांक x2000_i2s2_data_rx0_pins[] = अणु 0x0a, पूर्ण;
अटल पूर्णांक x2000_i2s2_data_rx1_pins[] = अणु 0x0b, पूर्ण;
अटल पूर्णांक x2000_i2s2_data_rx2_pins[] = अणु 0x0c, पूर्ण;
अटल पूर्णांक x2000_i2s2_data_rx3_pins[] = अणु 0x0d, पूर्ण;
अटल पूर्णांक x2000_i2s2_clk_rx_pins[] = अणु 0x11, 0x09, पूर्ण;
अटल पूर्णांक x2000_i2s2_sysclk_rx_pins[] = अणु 0x07, पूर्ण;
अटल पूर्णांक x2000_i2s3_data_tx0_pins[] = अणु 0x03, पूर्ण;
अटल पूर्णांक x2000_i2s3_data_tx1_pins[] = अणु 0x04, पूर्ण;
अटल पूर्णांक x2000_i2s3_data_tx2_pins[] = अणु 0x05, पूर्ण;
अटल पूर्णांक x2000_i2s3_data_tx3_pins[] = अणु 0x06, पूर्ण;
अटल पूर्णांक x2000_i2s3_clk_tx_pins[] = अणु 0x10, 0x02, पूर्ण;
अटल पूर्णांक x2000_i2s3_sysclk_tx_pins[] = अणु 0x00, पूर्ण;
अटल पूर्णांक x2000_dmic0_pins[] = अणु 0x54, 0x55, पूर्ण;
अटल पूर्णांक x2000_dmic1_pins[] = अणु 0x56, पूर्ण;
अटल पूर्णांक x2000_dmic2_pins[] = अणु 0x57, पूर्ण;
अटल पूर्णांक x2000_dmic3_pins[] = अणु 0x58, पूर्ण;
अटल पूर्णांक x2000_cim_8bit_pins[] = अणु
	0x0e, 0x0c, 0x0d, 0x4f,
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
पूर्ण;
अटल पूर्णांक x2000_cim_12bit_pins[] = अणु 0x08, 0x09, 0x0a, 0x0b, पूर्ण;
अटल पूर्णांक x2000_lcd_tft_8bit_pins[] = अणु
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x38, 0x3a, 0x39, 0x3b,
पूर्ण;
अटल पूर्णांक x2000_lcd_tft_16bit_pins[] = अणु
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
पूर्ण;
अटल पूर्णांक x2000_lcd_tft_18bit_pins[] = अणु
	0x30, 0x31,
पूर्ण;
अटल पूर्णांक x2000_lcd_tft_24bit_pins[] = अणु
	0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
पूर्ण;
अटल पूर्णांक x2000_lcd_slcd_8bit_pins[] = अणु
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x3a, 0x38, 0x3b, 0x30, 0x39,
पूर्ण;
अटल पूर्णांक x2000_pwm_pwm0_c_pins[] = अणु 0x40, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm0_d_pins[] = अणु 0x7e, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm1_c_pins[] = अणु 0x41, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm1_d_pins[] = अणु 0x7f, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm2_c_pins[] = अणु 0x42, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm2_e_pins[] = अणु 0x80, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm3_c_pins[] = अणु 0x43, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm3_e_pins[] = अणु 0x81, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm4_c_pins[] = अणु 0x44, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm4_e_pins[] = अणु 0x82, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm5_c_pins[] = अणु 0x45, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm5_e_pins[] = अणु 0x83, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm6_c_pins[] = अणु 0x46, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm6_e_pins[] = अणु 0x84, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm7_c_pins[] = अणु 0x47, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm7_e_pins[] = अणु 0x85, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm8_pins[] = अणु 0x48, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm9_pins[] = अणु 0x49, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm10_pins[] = अणु 0x4a, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm11_pins[] = अणु 0x4b, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm12_pins[] = अणु 0x4c, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm13_pins[] = अणु 0x4d, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm14_pins[] = अणु 0x4e, पूर्ण;
अटल पूर्णांक x2000_pwm_pwm15_pins[] = अणु 0x4f, पूर्ण;
अटल पूर्णांक x2000_mac0_rmii_pins[] = अणु
	0x4b, 0x47, 0x46, 0x4a, 0x43, 0x42, 0x4c, 0x4d, 0x4e, 0x41,
पूर्ण;
अटल पूर्णांक x2000_mac0_rgmii_pins[] = अणु
	0x4b, 0x49, 0x48, 0x47, 0x46, 0x4a, 0x45, 0x44, 0x43, 0x42,
	0x4c, 0x4d, 0x4f, 0x4e, 0x41,
पूर्ण;
अटल पूर्णांक x2000_mac1_rmii_pins[] = अणु
	0x32, 0x2d, 0x2c, 0x31, 0x29, 0x28, 0x33, 0x34, 0x35, 0x37,
पूर्ण;
अटल पूर्णांक x2000_mac1_rgmii_pins[] = अणु
	0x32, 0x2f, 0x2e, 0x2d, 0x2c, 0x31, 0x2b, 0x2a, 0x29, 0x28,
	0x33, 0x34, 0x36, 0x35, 0x37,
पूर्ण;
अटल पूर्णांक x2000_otg_pins[] = अणु 0x96, पूर्ण;

अटल u8 x2000_cim_8bit_funcs[] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, पूर्ण;

अटल स्थिर काष्ठा group_desc x2000_groups[] = अणु
	INGENIC_PIN_GROUP("uart0-data", x2000_uart0_data, 2),
	INGENIC_PIN_GROUP("uart0-hwflow", x2000_uart0_hwflow, 2),
	INGENIC_PIN_GROUP("uart1-data", x2000_uart1_data, 1),
	INGENIC_PIN_GROUP("uart1-hwflow", x2000_uart1_hwflow, 1),
	INGENIC_PIN_GROUP("uart2-data", x2000_uart2_data, 0),
	INGENIC_PIN_GROUP("uart3-data-c", x2000_uart3_data_c, 0),
	INGENIC_PIN_GROUP("uart3-data-d", x2000_uart3_data_d, 1),
	INGENIC_PIN_GROUP("uart3-hwflow-c", x2000_uart3_hwflow_c, 0),
	INGENIC_PIN_GROUP("uart3-hwflow-d", x2000_uart3_hwflow_d, 1),
	INGENIC_PIN_GROUP("uart4-data-a", x2000_uart4_data_a, 1),
	INGENIC_PIN_GROUP("uart4-data-c", x2000_uart4_data_c, 3),
	INGENIC_PIN_GROUP("uart4-hwflow-a", x2000_uart4_hwflow_a, 1),
	INGENIC_PIN_GROUP("uart4-hwflow-c", x2000_uart4_hwflow_c, 3),
	INGENIC_PIN_GROUP("uart5-data-a", x2000_uart5_data_a, 1),
	INGENIC_PIN_GROUP("uart5-data-c", x2000_uart5_data_c, 3),
	INGENIC_PIN_GROUP("uart6-data-a", x2000_uart6_data_a, 1),
	INGENIC_PIN_GROUP("uart6-data-c", x2000_uart6_data_c, 3),
	INGENIC_PIN_GROUP("uart7-data-a", x2000_uart7_data_a, 1),
	INGENIC_PIN_GROUP("uart7-data-c", x2000_uart7_data_c, 3),
	INGENIC_PIN_GROUP("uart8-data", x2000_uart8_data, 3),
	INGENIC_PIN_GROUP("uart9-data", x2000_uart9_data, 3),
	INGENIC_PIN_GROUP("sfc0-d", x2000_sfc0_d, 1),
	INGENIC_PIN_GROUP("sfc0-e", x2000_sfc0_e, 0),
	INGENIC_PIN_GROUP("sfc1", x2000_sfc1, 1),
	INGENIC_PIN_GROUP("ssi0-dt-b", x2000_ssi0_dt_b, 1),
	INGENIC_PIN_GROUP("ssi0-dt-d", x2000_ssi0_dt_d, 1),
	INGENIC_PIN_GROUP("ssi0-dr-b", x2000_ssi0_dr_b, 1),
	INGENIC_PIN_GROUP("ssi0-dr-d", x2000_ssi0_dr_d, 1),
	INGENIC_PIN_GROUP("ssi0-clk-b", x2000_ssi0_clk_b, 1),
	INGENIC_PIN_GROUP("ssi0-clk-d", x2000_ssi0_clk_d, 1),
	INGENIC_PIN_GROUP("ssi0-ce0-b", x2000_ssi0_ce0_b, 1),
	INGENIC_PIN_GROUP("ssi0-ce0-d", x2000_ssi0_ce0_d, 1),
	INGENIC_PIN_GROUP("ssi1-dt-c", x2000_ssi1_dt_c, 2),
	INGENIC_PIN_GROUP("ssi1-dt-d", x2000_ssi1_dt_d, 2),
	INGENIC_PIN_GROUP("ssi1-dt-e", x2000_ssi1_dt_e, 1),
	INGENIC_PIN_GROUP("ssi1-dr-c", x2000_ssi1_dr_c, 2),
	INGENIC_PIN_GROUP("ssi1-dr-d", x2000_ssi1_dr_d, 2),
	INGENIC_PIN_GROUP("ssi1-dr-e", x2000_ssi1_dr_e, 1),
	INGENIC_PIN_GROUP("ssi1-clk-c", x2000_ssi1_clk_c, 2),
	INGENIC_PIN_GROUP("ssi1-clk-d", x2000_ssi1_clk_d, 2),
	INGENIC_PIN_GROUP("ssi1-clk-e", x2000_ssi1_clk_e, 1),
	INGENIC_PIN_GROUP("ssi1-ce0-c", x2000_ssi1_ce0_c, 2),
	INGENIC_PIN_GROUP("ssi1-ce0-d", x2000_ssi1_ce0_d, 2),
	INGENIC_PIN_GROUP("ssi1-ce0-e", x2000_ssi1_ce0_e, 1),
	INGENIC_PIN_GROUP("mmc0-1bit", x2000_mmc0_1bit, 0),
	INGENIC_PIN_GROUP("mmc0-4bit", x2000_mmc0_4bit, 0),
	INGENIC_PIN_GROUP("mmc0-8bit", x2000_mmc0_8bit, 0),
	INGENIC_PIN_GROUP("mmc1-1bit", x2000_mmc1_1bit, 0),
	INGENIC_PIN_GROUP("mmc1-4bit", x2000_mmc1_4bit, 0),
	INGENIC_PIN_GROUP("mmc2-1bit", x2000_mmc2_1bit, 0),
	INGENIC_PIN_GROUP("mmc2-4bit", x2000_mmc2_4bit, 0),
	INGENIC_PIN_GROUP("emc-8bit-data", x2000_emc_8bit_data, 0),
	INGENIC_PIN_GROUP("emc-16bit-data", x2000_emc_16bit_data, 0),
	INGENIC_PIN_GROUP("emc-addr", x2000_emc_addr, 0),
	INGENIC_PIN_GROUP("emc-rd-we", x2000_emc_rd_we, 0),
	INGENIC_PIN_GROUP("emc-wait", x2000_emc_रुको, 0),
	INGENIC_PIN_GROUP("emc-cs1", x2000_emc_cs1, 3),
	INGENIC_PIN_GROUP("emc-cs2", x2000_emc_cs2, 3),
	INGENIC_PIN_GROUP("i2c0-data", x2000_i2c0, 3),
	INGENIC_PIN_GROUP("i2c1-data-c", x2000_i2c1_c, 2),
	INGENIC_PIN_GROUP("i2c1-data-d", x2000_i2c1_d, 1),
	INGENIC_PIN_GROUP("i2c2-data-b", x2000_i2c2_b, 2),
	INGENIC_PIN_GROUP("i2c2-data-d", x2000_i2c2_d, 2),
	INGENIC_PIN_GROUP("i2c2-data-e", x2000_i2c2_e, 1),
	INGENIC_PIN_GROUP("i2c3-data-a", x2000_i2c3_a, 0),
	INGENIC_PIN_GROUP("i2c3-data-d", x2000_i2c3_d, 1),
	INGENIC_PIN_GROUP("i2c4-data-c", x2000_i2c4_c, 1),
	INGENIC_PIN_GROUP("i2c4-data-d", x2000_i2c4_d, 2),
	INGENIC_PIN_GROUP("i2c5-data-c", x2000_i2c5_c, 1),
	INGENIC_PIN_GROUP("i2c5-data-d", x2000_i2c5_d, 1),
	INGENIC_PIN_GROUP("i2s1-data-tx", x2000_i2s1_data_tx, 2),
	INGENIC_PIN_GROUP("i2s1-data-rx", x2000_i2s1_data_rx, 2),
	INGENIC_PIN_GROUP("i2s1-clk-tx", x2000_i2s1_clk_tx, 2),
	INGENIC_PIN_GROUP("i2s1-clk-rx", x2000_i2s1_clk_rx, 2),
	INGENIC_PIN_GROUP("i2s1-sysclk-tx", x2000_i2s1_sysclk_tx, 2),
	INGENIC_PIN_GROUP("i2s1-sysclk-rx", x2000_i2s1_sysclk_rx, 2),
	INGENIC_PIN_GROUP("i2s2-data-rx0", x2000_i2s2_data_rx0, 2),
	INGENIC_PIN_GROUP("i2s2-data-rx1", x2000_i2s2_data_rx1, 2),
	INGENIC_PIN_GROUP("i2s2-data-rx2", x2000_i2s2_data_rx2, 2),
	INGENIC_PIN_GROUP("i2s2-data-rx3", x2000_i2s2_data_rx3, 2),
	INGENIC_PIN_GROUP("i2s2-clk-rx", x2000_i2s2_clk_rx, 2),
	INGENIC_PIN_GROUP("i2s2-sysclk-rx", x2000_i2s2_sysclk_rx, 2),
	INGENIC_PIN_GROUP("i2s3-data-tx0", x2000_i2s3_data_tx0, 2),
	INGENIC_PIN_GROUP("i2s3-data-tx1", x2000_i2s3_data_tx1, 2),
	INGENIC_PIN_GROUP("i2s3-data-tx2", x2000_i2s3_data_tx2, 2),
	INGENIC_PIN_GROUP("i2s3-data-tx3", x2000_i2s3_data_tx3, 2),
	INGENIC_PIN_GROUP("i2s3-clk-tx", x2000_i2s3_clk_tx, 2),
	INGENIC_PIN_GROUP("i2s3-sysclk-tx", x2000_i2s3_sysclk_tx, 2),
	INGENIC_PIN_GROUP("dmic0", x2000_dmic0, 0),
	INGENIC_PIN_GROUP("dmic1", x2000_dmic1, 0),
	INGENIC_PIN_GROUP("dmic2", x2000_dmic2, 0),
	INGENIC_PIN_GROUP("dmic3", x2000_dmic3, 0),
	INGENIC_PIN_GROUP_FUNCS("cim-data-8bit", x2000_cim_8bit,
				x2000_cim_8bit_funcs),
	INGENIC_PIN_GROUP("cim-data-12bit", x2000_cim_12bit, 0),
	INGENIC_PIN_GROUP("lcd-tft-8bit", x2000_lcd_tft_8bit, 1),
	INGENIC_PIN_GROUP("lcd-tft-16bit", x2000_lcd_tft_16bit, 1),
	INGENIC_PIN_GROUP("lcd-tft-18bit", x2000_lcd_tft_18bit, 1),
	INGENIC_PIN_GROUP("lcd-tft-24bit", x2000_lcd_tft_24bit, 1),
	INGENIC_PIN_GROUP("lcd-slcd-8bit", x2000_lcd_slcd_8bit, 2),
	INGENIC_PIN_GROUP("lcd-slcd-16bit", x2000_lcd_tft_16bit, 2),
	INGENIC_PIN_GROUP("pwm0-c", x2000_pwm_pwm0_c, 0),
	INGENIC_PIN_GROUP("pwm0-d", x2000_pwm_pwm0_d, 2),
	INGENIC_PIN_GROUP("pwm1-c", x2000_pwm_pwm1_c, 0),
	INGENIC_PIN_GROUP("pwm1-d", x2000_pwm_pwm1_d, 2),
	INGENIC_PIN_GROUP("pwm2-c", x2000_pwm_pwm2_c, 0),
	INGENIC_PIN_GROUP("pwm2-e", x2000_pwm_pwm2_e, 1),
	INGENIC_PIN_GROUP("pwm3-c", x2000_pwm_pwm3_c, 0),
	INGENIC_PIN_GROUP("pwm3-e", x2000_pwm_pwm3_e, 1),
	INGENIC_PIN_GROUP("pwm4-c", x2000_pwm_pwm4_c, 0),
	INGENIC_PIN_GROUP("pwm4-e", x2000_pwm_pwm4_e, 1),
	INGENIC_PIN_GROUP("pwm5-c", x2000_pwm_pwm5_c, 0),
	INGENIC_PIN_GROUP("pwm5-e", x2000_pwm_pwm5_e, 1),
	INGENIC_PIN_GROUP("pwm6-c", x2000_pwm_pwm6_c, 0),
	INGENIC_PIN_GROUP("pwm6-e", x2000_pwm_pwm6_e, 1),
	INGENIC_PIN_GROUP("pwm7-c", x2000_pwm_pwm7_c, 0),
	INGENIC_PIN_GROUP("pwm7-e", x2000_pwm_pwm7_e, 1),
	INGENIC_PIN_GROUP("pwm8", x2000_pwm_pwm8, 0),
	INGENIC_PIN_GROUP("pwm9", x2000_pwm_pwm9, 0),
	INGENIC_PIN_GROUP("pwm10", x2000_pwm_pwm10, 0),
	INGENIC_PIN_GROUP("pwm11", x2000_pwm_pwm11, 0),
	INGENIC_PIN_GROUP("pwm12", x2000_pwm_pwm12, 0),
	INGENIC_PIN_GROUP("pwm13", x2000_pwm_pwm13, 0),
	INGENIC_PIN_GROUP("pwm14", x2000_pwm_pwm14, 0),
	INGENIC_PIN_GROUP("pwm15", x2000_pwm_pwm15, 0),
	INGENIC_PIN_GROUP("mac0-rmii", x2000_mac0_rmii, 1),
	INGENIC_PIN_GROUP("mac0-rgmii", x2000_mac0_rgmii, 1),
	INGENIC_PIN_GROUP("mac1-rmii", x2000_mac1_rmii, 3),
	INGENIC_PIN_GROUP("mac1-rgmii", x2000_mac1_rgmii, 3),
	INGENIC_PIN_GROUP("otg-vbus", x2000_otg, 0),
पूर्ण;

अटल स्थिर अक्षर *x2000_uart0_groups[] = अणु "uart0-data", "uart0-hwflow", पूर्ण;
अटल स्थिर अक्षर *x2000_uart1_groups[] = अणु "uart1-data", "uart1-hwflow", पूर्ण;
अटल स्थिर अक्षर *x2000_uart2_groups[] = अणु "uart2-data", पूर्ण;
अटल स्थिर अक्षर *x2000_uart3_groups[] = अणु
	"uart3-data-c", "uart3-data-d", "uart3-hwflow-c", "uart3-hwflow-d",
पूर्ण;
अटल स्थिर अक्षर *x2000_uart4_groups[] = अणु
	"uart4-data-a", "uart4-data-c", "uart4-hwflow-a", "uart4-hwflow-c",
पूर्ण;
अटल स्थिर अक्षर *x2000_uart5_groups[] = अणु "uart5-data-a", "uart5-data-c", पूर्ण;
अटल स्थिर अक्षर *x2000_uart6_groups[] = अणु "uart6-data-a", "uart6-data-c", पूर्ण;
अटल स्थिर अक्षर *x2000_uart7_groups[] = अणु "uart7-data-a", "uart7-data-c", पूर्ण;
अटल स्थिर अक्षर *x2000_uart8_groups[] = अणु "uart8-data", पूर्ण;
अटल स्थिर अक्षर *x2000_uart9_groups[] = अणु "uart9-data", पूर्ण;
अटल स्थिर अक्षर *x2000_sfc_groups[] = अणु "sfc0-d", "sfc0-e", "sfc1", पूर्ण;
अटल स्थिर अक्षर *x2000_ssi0_groups[] = अणु
	"ssi0-dt-b", "ssi0-dt-d",
	"ssi0-dr-b", "ssi0-dr-d",
	"ssi0-clk-b", "ssi0-clk-d",
	"ssi0-ce0-b", "ssi0-ce0-d",
पूर्ण;
अटल स्थिर अक्षर *x2000_ssi1_groups[] = अणु
	"ssi1-dt-c", "ssi1-dt-d", "ssi1-dt-e",
	"ssi1-dr-c", "ssi1-dr-d", "ssi1-dr-e",
	"ssi1-clk-c", "ssi1-clk-d", "ssi1-clk-e",
	"ssi1-ce0-c", "ssi1-ce0-d", "ssi1-ce0-e",
पूर्ण;
अटल स्थिर अक्षर *x2000_mmc0_groups[] = अणु "mmc0-1bit", "mmc0-4bit", "mmc0-8bit", पूर्ण;
अटल स्थिर अक्षर *x2000_mmc1_groups[] = अणु "mmc1-1bit", "mmc1-4bit", पूर्ण;
अटल स्थिर अक्षर *x2000_mmc2_groups[] = अणु "mmc2-1bit", "mmc2-4bit", पूर्ण;
अटल स्थिर अक्षर *x2000_emc_groups[] = अणु
	"emc-8bit-data", "emc-16bit-data",
	"emc-addr", "emc-rd-we", "emc-wait",
पूर्ण;
अटल स्थिर अक्षर *x2000_cs1_groups[] = अणु "emc-cs1", पूर्ण;
अटल स्थिर अक्षर *x2000_cs2_groups[] = अणु "emc-cs2", पूर्ण;
अटल स्थिर अक्षर *x2000_i2c0_groups[] = अणु "i2c0-data", पूर्ण;
अटल स्थिर अक्षर *x2000_i2c1_groups[] = अणु "i2c1-data-c", "i2c1-data-d", पूर्ण;
अटल स्थिर अक्षर *x2000_i2c2_groups[] = अणु "i2c2-data-b", "i2c2-data-d", पूर्ण;
अटल स्थिर अक्षर *x2000_i2c3_groups[] = अणु "i2c3-data-a", "i2c3-data-d", पूर्ण;
अटल स्थिर अक्षर *x2000_i2c4_groups[] = अणु "i2c4-data-c", "i2c4-data-d", पूर्ण;
अटल स्थिर अक्षर *x2000_i2c5_groups[] = अणु "i2c5-data-c", "i2c5-data-d", पूर्ण;
अटल स्थिर अक्षर *x2000_i2s1_groups[] = अणु
	"i2s1-data-tx", "i2s1-data-rx",
	"i2s1-clk-tx", "i2s1-clk-rx",
	"i2s1-sysclk-tx", "i2s1-sysclk-rx",
पूर्ण;
अटल स्थिर अक्षर *x2000_i2s2_groups[] = अणु
	"i2s2-data-rx0", "i2s2-data-rx1", "i2s2-data-rx2", "i2s2-data-rx3",
	"i2s2-clk-rx", "i2s2-sysclk-rx",
पूर्ण;
अटल स्थिर अक्षर *x2000_i2s3_groups[] = अणु
	"i2s3-data-tx0", "i2s3-data-tx1", "i2s3-data-tx2", "i2s3-data-tx3",
	"i2s3-clk-tx", "i2s3-sysclk-tx",
पूर्ण;
अटल स्थिर अक्षर *x2000_dmic_groups[] = अणु "dmic0", "dmic1", "dmic2", "dmic3", पूर्ण;
अटल स्थिर अक्षर *x2000_cim_groups[] = अणु "cim-data-8bit", "cim-data-12bit", पूर्ण;
अटल स्थिर अक्षर *x2000_lcd_groups[] = अणु
	"lcd-tft-8bit", "lcd-tft-16bit", "lcd-tft-18bit", "lcd-tft-24bit",
	"lcd-slcd-8bit", "lcd-slcd-16bit",
पूर्ण;
अटल स्थिर अक्षर *x2000_pwm0_groups[] = अणु "pwm0-c", "pwm0-d", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm1_groups[] = अणु "pwm1-c", "pwm1-d", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm2_groups[] = अणु "pwm2-c", "pwm2-e", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm3_groups[] = अणु "pwm3-c", "pwm3-r", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm4_groups[] = अणु "pwm4-c", "pwm4-e", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm5_groups[] = अणु "pwm5-c", "pwm5-e", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm6_groups[] = अणु "pwm6-c", "pwm6-e", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm7_groups[] = अणु "pwm7-c", "pwm7-e", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm8_groups[] = अणु "pwm8", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm9_groups[] = अणु "pwm9", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm10_groups[] = अणु "pwm10", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm11_groups[] = अणु "pwm11", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm12_groups[] = अणु "pwm12", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm13_groups[] = अणु "pwm13", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm14_groups[] = अणु "pwm14", पूर्ण;
अटल स्थिर अक्षर *x2000_pwm15_groups[] = अणु "pwm15", पूर्ण;
अटल स्थिर अक्षर *x2000_mac0_groups[] = अणु "mac0-rmii", "mac0-rgmii", पूर्ण;
अटल स्थिर अक्षर *x2000_mac1_groups[] = अणु "mac1-rmii", "mac1-rgmii", पूर्ण;
अटल स्थिर अक्षर *x2000_otg_groups[] = अणु "otg-vbus", पूर्ण;

अटल स्थिर काष्ठा function_desc x2000_functions[] = अणु
	अणु "uart0", x2000_uart0_groups, ARRAY_SIZE(x2000_uart0_groups), पूर्ण,
	अणु "uart1", x2000_uart1_groups, ARRAY_SIZE(x2000_uart1_groups), पूर्ण,
	अणु "uart2", x2000_uart2_groups, ARRAY_SIZE(x2000_uart2_groups), पूर्ण,
	अणु "uart3", x2000_uart3_groups, ARRAY_SIZE(x2000_uart3_groups), पूर्ण,
	अणु "uart4", x2000_uart4_groups, ARRAY_SIZE(x2000_uart4_groups), पूर्ण,
	अणु "uart5", x2000_uart5_groups, ARRAY_SIZE(x2000_uart5_groups), पूर्ण,
	अणु "uart6", x2000_uart6_groups, ARRAY_SIZE(x2000_uart6_groups), पूर्ण,
	अणु "uart7", x2000_uart7_groups, ARRAY_SIZE(x2000_uart7_groups), पूर्ण,
	अणु "uart8", x2000_uart8_groups, ARRAY_SIZE(x2000_uart8_groups), पूर्ण,
	अणु "uart9", x2000_uart9_groups, ARRAY_SIZE(x2000_uart9_groups), पूर्ण,
	अणु "sfc", x2000_sfc_groups, ARRAY_SIZE(x2000_sfc_groups), पूर्ण,
	अणु "ssi0", x2000_ssi0_groups, ARRAY_SIZE(x2000_ssi0_groups), पूर्ण,
	अणु "ssi1", x2000_ssi1_groups, ARRAY_SIZE(x2000_ssi1_groups), पूर्ण,
	अणु "mmc0", x2000_mmc0_groups, ARRAY_SIZE(x2000_mmc0_groups), पूर्ण,
	अणु "mmc1", x2000_mmc1_groups, ARRAY_SIZE(x2000_mmc1_groups), पूर्ण,
	अणु "mmc2", x2000_mmc2_groups, ARRAY_SIZE(x2000_mmc2_groups), पूर्ण,
	अणु "emc", x2000_emc_groups, ARRAY_SIZE(x2000_emc_groups), पूर्ण,
	अणु "emc-cs1", x2000_cs1_groups, ARRAY_SIZE(x2000_cs1_groups), पूर्ण,
	अणु "emc-cs2", x2000_cs2_groups, ARRAY_SIZE(x2000_cs2_groups), पूर्ण,
	अणु "i2c0", x2000_i2c0_groups, ARRAY_SIZE(x2000_i2c0_groups), पूर्ण,
	अणु "i2c1", x2000_i2c1_groups, ARRAY_SIZE(x2000_i2c1_groups), पूर्ण,
	अणु "i2c2", x2000_i2c2_groups, ARRAY_SIZE(x2000_i2c2_groups), पूर्ण,
	अणु "i2c3", x2000_i2c3_groups, ARRAY_SIZE(x2000_i2c3_groups), पूर्ण,
	अणु "i2c4", x2000_i2c4_groups, ARRAY_SIZE(x2000_i2c4_groups), पूर्ण,
	अणु "i2c5", x2000_i2c5_groups, ARRAY_SIZE(x2000_i2c5_groups), पूर्ण,
	अणु "i2s1", x2000_i2s1_groups, ARRAY_SIZE(x2000_i2s1_groups), पूर्ण,
	अणु "i2s2", x2000_i2s2_groups, ARRAY_SIZE(x2000_i2s2_groups), पूर्ण,
	अणु "i2s3", x2000_i2s3_groups, ARRAY_SIZE(x2000_i2s3_groups), पूर्ण,
	अणु "dmic", x2000_dmic_groups, ARRAY_SIZE(x2000_dmic_groups), पूर्ण,
	अणु "cim", x2000_cim_groups, ARRAY_SIZE(x2000_cim_groups), पूर्ण,
	अणु "lcd", x2000_lcd_groups, ARRAY_SIZE(x2000_lcd_groups), पूर्ण,
	अणु "pwm0", x2000_pwm0_groups, ARRAY_SIZE(x2000_pwm0_groups), पूर्ण,
	अणु "pwm1", x2000_pwm1_groups, ARRAY_SIZE(x2000_pwm1_groups), पूर्ण,
	अणु "pwm2", x2000_pwm2_groups, ARRAY_SIZE(x2000_pwm2_groups), पूर्ण,
	अणु "pwm3", x2000_pwm3_groups, ARRAY_SIZE(x2000_pwm3_groups), पूर्ण,
	अणु "pwm4", x2000_pwm4_groups, ARRAY_SIZE(x2000_pwm4_groups), पूर्ण,
	अणु "pwm5", x2000_pwm5_groups, ARRAY_SIZE(x2000_pwm5_groups), पूर्ण,
	अणु "pwm6", x2000_pwm6_groups, ARRAY_SIZE(x2000_pwm6_groups), पूर्ण,
	अणु "pwm7", x2000_pwm7_groups, ARRAY_SIZE(x2000_pwm7_groups), पूर्ण,
	अणु "pwm8", x2000_pwm8_groups, ARRAY_SIZE(x2000_pwm8_groups), पूर्ण,
	अणु "pwm9", x2000_pwm9_groups, ARRAY_SIZE(x2000_pwm9_groups), पूर्ण,
	अणु "pwm10", x2000_pwm10_groups, ARRAY_SIZE(x2000_pwm10_groups), पूर्ण,
	अणु "pwm11", x2000_pwm11_groups, ARRAY_SIZE(x2000_pwm11_groups), पूर्ण,
	अणु "pwm12", x2000_pwm12_groups, ARRAY_SIZE(x2000_pwm12_groups), पूर्ण,
	अणु "pwm13", x2000_pwm13_groups, ARRAY_SIZE(x2000_pwm13_groups), पूर्ण,
	अणु "pwm14", x2000_pwm14_groups, ARRAY_SIZE(x2000_pwm14_groups), पूर्ण,
	अणु "pwm15", x2000_pwm15_groups, ARRAY_SIZE(x2000_pwm15_groups), पूर्ण,
	अणु "mac0", x2000_mac0_groups, ARRAY_SIZE(x2000_mac0_groups), पूर्ण,
	अणु "mac1", x2000_mac1_groups, ARRAY_SIZE(x2000_mac1_groups), पूर्ण,
	अणु "otg", x2000_otg_groups, ARRAY_SIZE(x2000_otg_groups), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_chip_info x2000_chip_info = अणु
	.num_chips = 5,
	.reg_offset = 0x100,
	.version = ID_X2000,
	.groups = x2000_groups,
	.num_groups = ARRAY_SIZE(x2000_groups),
	.functions = x2000_functions,
	.num_functions = ARRAY_SIZE(x2000_functions),
	.pull_ups = x2000_pull_ups,
	.pull_करोwns = x2000_pull_करोwns,
पूर्ण;

अटल u32 ingenic_gpio_पढ़ो_reg(काष्ठा ingenic_gpio_chip *jzgc, u8 reg)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(jzgc->jzpc->map, jzgc->reg_base + reg, &val);

	वापस (u32) val;
पूर्ण

अटल व्योम ingenic_gpio_set_bit(काष्ठा ingenic_gpio_chip *jzgc,
		u8 reg, u8 offset, bool set)
अणु
	अगर (jzgc->jzpc->info->version == ID_JZ4730) अणु
		regmap_update_bits(jzgc->jzpc->map, jzgc->reg_base + reg,
				BIT(offset), set ? BIT(offset) : 0);
		वापस;
	पूर्ण

	अगर (set)
		reg = REG_SET(reg);
	अन्यथा
		reg = REG_CLEAR(reg);

	regmap_ग_लिखो(jzgc->jzpc->map, jzgc->reg_base + reg, BIT(offset));
पूर्ण

अटल व्योम ingenic_gpio_shaकरोw_set_bit(काष्ठा ingenic_gpio_chip *jzgc,
		u8 reg, u8 offset, bool set)
अणु
	अगर (set)
		reg = REG_SET(reg);
	अन्यथा
		reg = REG_CLEAR(reg);

	regmap_ग_लिखो(jzgc->jzpc->map, REG_PZ_BASE(
			jzgc->jzpc->info->reg_offset) + reg, BIT(offset));
पूर्ण

अटल व्योम ingenic_gpio_shaकरोw_set_bit_load(काष्ठा ingenic_gpio_chip *jzgc)
अणु
	regmap_ग_लिखो(jzgc->jzpc->map, REG_PZ_GID2LD(
			jzgc->jzpc->info->reg_offset),
			jzgc->gc.base / PINS_PER_GPIO_CHIP);
पूर्ण

अटल व्योम jz4730_gpio_set_bits(काष्ठा ingenic_gpio_chip *jzgc,
		u8 reg_upper, u8 reg_lower, u8 offset, u8 value)
अणु
	/*
	 * JZ4730 function and IRQ रेजिस्टरs support two-bits-per-pin
	 * definitions, split पूर्णांकo two groups of 16.
	 */
	u8 reg = offset < JZ4730_PINS_PER_PAIRED_REG ? reg_lower : reg_upper;
	अचिन्हित पूर्णांक idx = offset % JZ4730_PINS_PER_PAIRED_REG;
	अचिन्हित पूर्णांक mask = GENMASK(1, 0) << idx * 2;

	regmap_update_bits(jzgc->jzpc->map, jzgc->reg_base + reg, mask, value << (idx * 2));
पूर्ण

अटल अंतरभूत bool ingenic_gpio_get_value(काष्ठा ingenic_gpio_chip *jzgc,
					  u8 offset)
अणु
	अचिन्हित पूर्णांक val = ingenic_gpio_पढ़ो_reg(jzgc, GPIO_PIN);

	वापस !!(val & BIT(offset));
पूर्ण

अटल व्योम ingenic_gpio_set_value(काष्ठा ingenic_gpio_chip *jzgc,
				   u8 offset, पूर्णांक value)
अणु
	अगर (jzgc->jzpc->info->version >= ID_JZ4770)
		ingenic_gpio_set_bit(jzgc, JZ4770_GPIO_PAT0, offset, !!value);
	अन्यथा अगर (jzgc->jzpc->info->version >= ID_JZ4740)
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_DATA, offset, !!value);
	अन्यथा
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_DATA, offset, !!value);
पूर्ण

अटल व्योम irq_set_type(काष्ठा ingenic_gpio_chip *jzgc,
		u8 offset, अचिन्हित पूर्णांक type)
अणु
	u8 reg1, reg2;
	bool val1, val2, val3;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		val1 = val2 = false;
		val3 = true;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		val1 = val2 = true;
		val3 = false;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		val1 = val3 = false;
		val2 = true;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		val1 = true;
		val2 = val3 = false;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
	शेष:
		val1 = val2 = val3 = false;
		अवरोध;
	पूर्ण

	अगर (jzgc->jzpc->info->version >= ID_JZ4770) अणु
		reg1 = JZ4770_GPIO_PAT1;
		reg2 = JZ4770_GPIO_PAT0;
	पूर्ण अन्यथा अगर (jzgc->jzpc->info->version >= ID_JZ4740) अणु
		reg1 = JZ4740_GPIO_TRIG;
		reg2 = JZ4740_GPIO_सूची;
	पूर्ण अन्यथा अणु
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPसूची, offset, false);
		jz4730_gpio_set_bits(jzgc, JZ4730_GPIO_GPIDUR,
				JZ4730_GPIO_GPIDLR, offset, (val2 << 1) | val1);
		वापस;
	पूर्ण

	अगर (jzgc->jzpc->info->version >= ID_X2000) अणु
		ingenic_gpio_shaकरोw_set_bit(jzgc, reg2, offset, val1);
		ingenic_gpio_shaकरोw_set_bit(jzgc, reg1, offset, val2);
		ingenic_gpio_shaकरोw_set_bit_load(jzgc);
		ingenic_gpio_set_bit(jzgc, X2000_GPIO_EDG, offset, val3);
	पूर्ण अन्यथा अगर (jzgc->jzpc->info->version >= ID_X1000) अणु
		ingenic_gpio_shaकरोw_set_bit(jzgc, reg2, offset, val1);
		ingenic_gpio_shaकरोw_set_bit(jzgc, reg1, offset, val2);
		ingenic_gpio_shaकरोw_set_bit_load(jzgc);
	पूर्ण अन्यथा अणु
		ingenic_gpio_set_bit(jzgc, reg2, offset, val1);
		ingenic_gpio_set_bit(jzgc, reg1, offset, val2);
	पूर्ण
पूर्ण

अटल व्योम ingenic_gpio_irq_mask(काष्ठा irq_data *irqd)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	पूर्णांक irq = irqd->hwirq;

	अगर (jzgc->jzpc->info->version >= ID_JZ4740)
		ingenic_gpio_set_bit(jzgc, GPIO_MSK, irq, true);
	अन्यथा
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPIMR, irq, true);
पूर्ण

अटल व्योम ingenic_gpio_irq_unmask(काष्ठा irq_data *irqd)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	पूर्णांक irq = irqd->hwirq;

	अगर (jzgc->jzpc->info->version >= ID_JZ4740)
		ingenic_gpio_set_bit(jzgc, GPIO_MSK, irq, false);
	अन्यथा
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPIMR, irq, false);
पूर्ण

अटल व्योम ingenic_gpio_irq_enable(काष्ठा irq_data *irqd)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	पूर्णांक irq = irqd->hwirq;

	अगर (jzgc->jzpc->info->version >= ID_JZ4770)
		ingenic_gpio_set_bit(jzgc, JZ4770_GPIO_INT, irq, true);
	अन्यथा अगर (jzgc->jzpc->info->version >= ID_JZ4740)
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_SELECT, irq, true);
	अन्यथा
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPIER, irq, true);

	ingenic_gpio_irq_unmask(irqd);
पूर्ण

अटल व्योम ingenic_gpio_irq_disable(काष्ठा irq_data *irqd)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	पूर्णांक irq = irqd->hwirq;

	ingenic_gpio_irq_mask(irqd);

	अगर (jzgc->jzpc->info->version >= ID_JZ4770)
		ingenic_gpio_set_bit(jzgc, JZ4770_GPIO_INT, irq, false);
	अन्यथा अगर (jzgc->jzpc->info->version >= ID_JZ4740)
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_SELECT, irq, false);
	अन्यथा
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPIER, irq, false);
पूर्ण

अटल व्योम ingenic_gpio_irq_ack(काष्ठा irq_data *irqd)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	पूर्णांक irq = irqd->hwirq;
	bool high;

	अगर ((irqd_get_trigger_type(irqd) == IRQ_TYPE_EDGE_BOTH) &&
		(jzgc->jzpc->info->version < ID_X2000)) अणु
		/*
		 * Switch to an पूर्णांकerrupt क्रम the opposite edge to the one that
		 * triggered the पूर्णांकerrupt being ACKed.
		 */
		high = ingenic_gpio_get_value(jzgc, irq);
		अगर (high)
			irq_set_type(jzgc, irq, IRQ_TYPE_LEVEL_LOW);
		अन्यथा
			irq_set_type(jzgc, irq, IRQ_TYPE_LEVEL_HIGH);
	पूर्ण

	अगर (jzgc->jzpc->info->version >= ID_JZ4770)
		ingenic_gpio_set_bit(jzgc, JZ4770_GPIO_FLAG, irq, false);
	अन्यथा अगर (jzgc->jzpc->info->version >= ID_JZ4740)
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_DATA, irq, true);
	अन्यथा
		ingenic_gpio_set_bit(jzgc, JZ4730_GPIO_GPFR, irq, false);
पूर्ण

अटल पूर्णांक ingenic_gpio_irq_set_type(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_EDGE_FALLING:
		irq_set_handler_locked(irqd, handle_edge_irq);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_set_handler_locked(irqd, handle_level_irq);
		अवरोध;
	शेष:
		irq_set_handler_locked(irqd, handle_bad_irq);
	पूर्ण

	अगर ((type == IRQ_TYPE_EDGE_BOTH) && (jzgc->jzpc->info->version < ID_X2000)) अणु
		/*
		 * The hardware करोes not support पूर्णांकerrupts on both edges. The
		 * best we can करो is to set up a single-edge पूर्णांकerrupt and then
		 * चयन to the opposing edge when ACKing the पूर्णांकerrupt.
		 */
		bool high = ingenic_gpio_get_value(jzgc, irqd->hwirq);

		type = high ? IRQ_TYPE_LEVEL_LOW : IRQ_TYPE_LEVEL_HIGH;
	पूर्ण

	irq_set_type(jzgc, irqd->hwirq, type);
	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_gpio_irq_set_wake(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(irqd);
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	वापस irq_set_irq_wake(jzgc->irq, on);
पूर्ण

अटल व्योम ingenic_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	काष्ठा irq_chip *irq_chip = irq_data_get_irq_chip(&desc->irq_data);
	अचिन्हित दीर्घ flag, i;

	chained_irq_enter(irq_chip, desc);

	अगर (jzgc->jzpc->info->version >= ID_JZ4770)
		flag = ingenic_gpio_पढ़ो_reg(jzgc, JZ4770_GPIO_FLAG);
	अन्यथा अगर (jzgc->jzpc->info->version >= ID_JZ4740)
		flag = ingenic_gpio_पढ़ो_reg(jzgc, JZ4740_GPIO_FLAG);
	अन्यथा
		flag = ingenic_gpio_पढ़ो_reg(jzgc, JZ4730_GPIO_GPFR);

	क्रम_each_set_bit(i, &flag, 32)
		generic_handle_irq(irq_linear_revmap(gc->irq.करोमुख्य, i));
	chained_irq_निकास(irq_chip, desc);
पूर्ण

अटल व्योम ingenic_gpio_set(काष्ठा gpio_chip *gc,
		अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	ingenic_gpio_set_value(jzgc, offset, value);
पूर्ण

अटल पूर्णांक ingenic_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);

	वापस (पूर्णांक) ingenic_gpio_get_value(jzgc, offset);
पूर्ण

अटल पूर्णांक ingenic_gpio_direction_input(काष्ठा gpio_chip *gc,
		अचिन्हित पूर्णांक offset)
अणु
	वापस pinctrl_gpio_direction_input(gc->base + offset);
पूर्ण

अटल पूर्णांक ingenic_gpio_direction_output(काष्ठा gpio_chip *gc,
		अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	ingenic_gpio_set(gc, offset, value);
	वापस pinctrl_gpio_direction_output(gc->base + offset);
पूर्ण

अटल अंतरभूत व्योम ingenic_config_pin(काष्ठा ingenic_pinctrl *jzpc,
		अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक reg, bool set)
अणु
	अचिन्हित पूर्णांक idx = pin % PINS_PER_GPIO_CHIP;
	अचिन्हित पूर्णांक offt = pin / PINS_PER_GPIO_CHIP;

	अगर (set) अणु
		अगर (jzpc->info->version >= ID_JZ4740)
			regmap_ग_लिखो(jzpc->map, offt * jzpc->info->reg_offset +
					REG_SET(reg), BIT(idx));
		अन्यथा
			regmap_set_bits(jzpc->map, offt * jzpc->info->reg_offset +
					reg, BIT(idx));
	पूर्ण अन्यथा अणु
		अगर (jzpc->info->version >= ID_JZ4740)
			regmap_ग_लिखो(jzpc->map, offt * jzpc->info->reg_offset +
					REG_CLEAR(reg), BIT(idx));
		अन्यथा
			regmap_clear_bits(jzpc->map, offt * jzpc->info->reg_offset +
					reg, BIT(idx));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ingenic_shaकरोw_config_pin(काष्ठा ingenic_pinctrl *jzpc,
		अचिन्हित पूर्णांक pin, u8 reg, bool set)
अणु
	अचिन्हित पूर्णांक idx = pin % PINS_PER_GPIO_CHIP;

	regmap_ग_लिखो(jzpc->map, REG_PZ_BASE(jzpc->info->reg_offset) +
			(set ? REG_SET(reg) : REG_CLEAR(reg)), BIT(idx));
पूर्ण

अटल अंतरभूत व्योम ingenic_shaकरोw_config_pin_load(काष्ठा ingenic_pinctrl *jzpc,
		अचिन्हित पूर्णांक pin)
अणु
	regmap_ग_लिखो(jzpc->map, REG_PZ_GID2LD(jzpc->info->reg_offset),
			pin / PINS_PER_GPIO_CHIP);
पूर्ण

अटल अंतरभूत व्योम jz4730_config_pin_function(काष्ठा ingenic_pinctrl *jzpc,
		अचिन्हित पूर्णांक pin, u8 reg_upper, u8 reg_lower, u8 value)
अणु
	/*
	 * JZ4730 function and IRQ रेजिस्टरs support two-bits-per-pin
	 * definitions, split पूर्णांकo two groups of 16.
	 */
	अचिन्हित पूर्णांक idx = pin % JZ4730_PINS_PER_PAIRED_REG;
	अचिन्हित पूर्णांक mask = GENMASK(1, 0) << idx * 2;
	अचिन्हित पूर्णांक offt = pin / PINS_PER_GPIO_CHIP;
	u8 reg = (pin % PINS_PER_GPIO_CHIP) < JZ4730_PINS_PER_PAIRED_REG ? reg_lower : reg_upper;

	regmap_update_bits(jzpc->map, offt * jzpc->info->reg_offset + reg,
			mask, value << (idx * 2));
पूर्ण

अटल अंतरभूत bool ingenic_get_pin_config(काष्ठा ingenic_pinctrl *jzpc,
		अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक idx = pin % PINS_PER_GPIO_CHIP;
	अचिन्हित पूर्णांक offt = pin / PINS_PER_GPIO_CHIP;
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(jzpc->map, offt * jzpc->info->reg_offset + reg, &val);

	वापस val & BIT(idx);
पूर्ण

अटल पूर्णांक ingenic_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ingenic_gpio_chip *jzgc = gpiochip_get_data(gc);
	काष्ठा ingenic_pinctrl *jzpc = jzgc->jzpc;
	अचिन्हित पूर्णांक pin = gc->base + offset;

	अगर (jzpc->info->version >= ID_JZ4770) अणु
		अगर (ingenic_get_pin_config(jzpc, pin, JZ4770_GPIO_INT) ||
		    ingenic_get_pin_config(jzpc, pin, JZ4770_GPIO_PAT1))
			वापस GPIO_LINE_सूचीECTION_IN;
		वापस GPIO_LINE_सूचीECTION_OUT;
	पूर्ण अन्यथा अगर (jzpc->info->version == ID_JZ4730) अणु
		अगर (!ingenic_get_pin_config(jzpc, pin, JZ4730_GPIO_GPसूची))
			वापस GPIO_LINE_सूचीECTION_IN;
		वापस GPIO_LINE_सूचीECTION_OUT;
	पूर्ण

	अगर (ingenic_get_pin_config(jzpc, pin, JZ4740_GPIO_SELECT))
		वापस GPIO_LINE_सूचीECTION_IN;

	अगर (ingenic_get_pin_config(jzpc, pin, JZ4740_GPIO_सूची))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops ingenic_pctlops = अणु
	.get_groups_count = pinctrl_generic_get_group_count,
	.get_group_name = pinctrl_generic_get_group_name,
	.get_group_pins = pinctrl_generic_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक ingenic_gpio_irq_request(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	पूर्णांक ret;

	ret = ingenic_gpio_direction_input(gpio_chip, data->hwirq);
	अगर (ret)
		वापस ret;

	वापस gpiochip_reqres_irq(gpio_chip, data->hwirq);
पूर्ण

अटल व्योम ingenic_gpio_irq_release(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);

	वापस gpiochip_relres_irq(gpio_chip, data->hwirq);
पूर्ण

अटल पूर्णांक ingenic_pinmux_set_pin_fn(काष्ठा ingenic_pinctrl *jzpc,
		पूर्णांक pin, पूर्णांक func)
अणु
	अचिन्हित पूर्णांक idx = pin % PINS_PER_GPIO_CHIP;
	अचिन्हित पूर्णांक offt = pin / PINS_PER_GPIO_CHIP;

	dev_dbg(jzpc->dev, "set pin P%c%u to function %u\n",
			'A' + offt, idx, func);

	अगर (jzpc->info->version >= ID_X1000) अणु
		ingenic_shaकरोw_config_pin(jzpc, pin, JZ4770_GPIO_INT, false);
		ingenic_shaकरोw_config_pin(jzpc, pin, GPIO_MSK, false);
		ingenic_shaकरोw_config_pin(jzpc, pin, JZ4770_GPIO_PAT1, func & 0x2);
		ingenic_shaकरोw_config_pin(jzpc, pin, JZ4770_GPIO_PAT0, func & 0x1);
		ingenic_shaकरोw_config_pin_load(jzpc, pin);
	पूर्ण अन्यथा अगर (jzpc->info->version >= ID_JZ4770) अणु
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_INT, false);
		ingenic_config_pin(jzpc, pin, GPIO_MSK, false);
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PAT1, func & 0x2);
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PAT0, func & 0x1);
	पूर्ण अन्यथा अगर (jzpc->info->version >= ID_JZ4740) अणु
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_FUNC, true);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_TRIG, func & 0x2);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_SELECT, func & 0x1);
	पूर्ण अन्यथा अणु
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_GPIER, false);
		jz4730_config_pin_function(jzpc, pin, JZ4730_GPIO_GPAUR, JZ4730_GPIO_GPALR, func);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक selector, अचिन्हित पूर्णांक group)
अणु
	काष्ठा ingenic_pinctrl *jzpc = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा function_desc *func;
	काष्ठा group_desc *grp;
	अचिन्हित पूर्णांक i;
	uपूर्णांकptr_t mode;
	u8 *pin_modes;

	func = pinmux_generic_get_function(pctldev, selector);
	अगर (!func)
		वापस -EINVAL;

	grp = pinctrl_generic_get_group(pctldev, group);
	अगर (!grp)
		वापस -EINVAL;

	dev_dbg(pctldev->dev, "enable function %s group %s\n",
		func->name, grp->name);

	mode = (uपूर्णांकptr_t)grp->data;
	अगर (mode <= 3) अणु
		क्रम (i = 0; i < grp->num_pins; i++)
			ingenic_pinmux_set_pin_fn(jzpc, grp->pins[i], mode);
	पूर्ण अन्यथा अणु
		pin_modes = grp->data;

		क्रम (i = 0; i < grp->num_pins; i++)
			ingenic_pinmux_set_pin_fn(jzpc, grp->pins[i], pin_modes[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_pinmux_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_gpio_range *range,
		अचिन्हित पूर्णांक pin, bool input)
अणु
	काष्ठा ingenic_pinctrl *jzpc = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक idx = pin % PINS_PER_GPIO_CHIP;
	अचिन्हित पूर्णांक offt = pin / PINS_PER_GPIO_CHIP;

	dev_dbg(pctldev->dev, "set pin P%c%u to %sput\n",
			'A' + offt, idx, input ? "in" : "out");

	अगर (jzpc->info->version >= ID_X1000) अणु
		ingenic_shaकरोw_config_pin(jzpc, pin, JZ4770_GPIO_INT, false);
		ingenic_shaकरोw_config_pin(jzpc, pin, GPIO_MSK, true);
		ingenic_shaकरोw_config_pin(jzpc, pin, JZ4770_GPIO_PAT1, input);
		ingenic_shaकरोw_config_pin_load(jzpc, pin);
	पूर्ण अन्यथा अगर (jzpc->info->version >= ID_JZ4770) अणु
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_INT, false);
		ingenic_config_pin(jzpc, pin, GPIO_MSK, true);
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PAT1, input);
	पूर्ण अन्यथा अगर (jzpc->info->version >= ID_JZ4740) अणु
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_SELECT, false);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_सूची, !input);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_FUNC, false);
	पूर्ण अन्यथा अणु
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_GPIER, false);
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_GPसूची, !input);
		jz4730_config_pin_function(jzpc, pin, JZ4730_GPIO_GPAUR, JZ4730_GPIO_GPALR, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops ingenic_pmxops = अणु
	.get_functions_count = pinmux_generic_get_function_count,
	.get_function_name = pinmux_generic_get_function_name,
	.get_function_groups = pinmux_generic_get_function_groups,
	.set_mux = ingenic_pinmux_set_mux,
	.gpio_set_direction = ingenic_pinmux_gpio_set_direction,
पूर्ण;

अटल पूर्णांक ingenic_pinconf_get(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा ingenic_pinctrl *jzpc = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अचिन्हित पूर्णांक idx = pin % PINS_PER_GPIO_CHIP;
	अचिन्हित पूर्णांक offt = pin / PINS_PER_GPIO_CHIP;
	अचिन्हित पूर्णांक arg = 1;
	अचिन्हित पूर्णांक bias, reg;
	bool pull, pullup, pullकरोwn;

	अगर (jzpc->info->version >= ID_X2000) अणु
		pullup = ingenic_get_pin_config(jzpc, pin, X2000_GPIO_PEPU) &&
				!ingenic_get_pin_config(jzpc, pin, X2000_GPIO_PEPD) &&
				(jzpc->info->pull_ups[offt] & BIT(idx));
		pullकरोwn = ingenic_get_pin_config(jzpc, pin, X2000_GPIO_PEPD) &&
				!ingenic_get_pin_config(jzpc, pin, X2000_GPIO_PEPU) &&
				(jzpc->info->pull_करोwns[offt] & BIT(idx));

	पूर्ण अन्यथा अगर (jzpc->info->version >= ID_X1830) अणु
		अचिन्हित पूर्णांक half = PINS_PER_GPIO_CHIP / 2;
		अचिन्हित पूर्णांक idxh = (pin % half) * 2;

		अगर (idx < half)
			regmap_पढ़ो(jzpc->map, offt * jzpc->info->reg_offset +
					X1830_GPIO_PEL, &bias);
		अन्यथा
			regmap_पढ़ो(jzpc->map, offt * jzpc->info->reg_offset +
					X1830_GPIO_PEH, &bias);

		bias = (bias >> idxh) & (GPIO_PULL_UP | GPIO_PULL_DOWN);

		pullup = (bias == GPIO_PULL_UP) && (jzpc->info->pull_ups[offt] & BIT(idx));
		pullकरोwn = (bias == GPIO_PULL_DOWN) && (jzpc->info->pull_करोwns[offt] & BIT(idx));

	पूर्ण अन्यथा अणु
		अगर (jzpc->info->version >= ID_JZ4770)
			pull = !ingenic_get_pin_config(jzpc, pin, JZ4770_GPIO_PEN);
		अन्यथा अगर (jzpc->info->version >= ID_JZ4740)
			pull = !ingenic_get_pin_config(jzpc, pin, JZ4740_GPIO_PULL_DIS);
		अन्यथा
			pull = ingenic_get_pin_config(jzpc, pin, JZ4730_GPIO_GPPUR);

		pullup = pull && (jzpc->info->pull_ups[offt] & BIT(idx));
		pullकरोwn = pull && (jzpc->info->pull_करोwns[offt] & BIT(idx));
	पूर्ण

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pullup || pullकरोwn)
			वापस -EINVAL;

		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (!pullup)
			वापस -EINVAL;

		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (!pullकरोwn)
			वापस -EINVAL;

		अवरोध;

	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (jzpc->info->version >= ID_X2000)
			reg = X2000_GPIO_SMT;
		अन्यथा अगर (jzpc->info->version >= ID_X1830)
			reg = X1830_GPIO_SMT;
		अन्यथा
			वापस -EINVAL;

		arg = !!ingenic_get_pin_config(jzpc, pin, reg);
		अवरोध;

	हाल PIN_CONFIG_SLEW_RATE:
		अगर (jzpc->info->version >= ID_X2000)
			reg = X2000_GPIO_SR;
		अन्यथा अगर (jzpc->info->version >= ID_X1830)
			reg = X1830_GPIO_SR;
		अन्यथा
			वापस -EINVAL;

		arg = !!ingenic_get_pin_config(jzpc, pin, reg);
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल व्योम ingenic_set_bias(काष्ठा ingenic_pinctrl *jzpc,
		अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक bias)
अणु
	अगर (jzpc->info->version >= ID_X2000) अणु
		चयन (bias) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPD, false);
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPU, true);
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPU, false);
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPD, true);
			अवरोध;

		हाल PIN_CONFIG_BIAS_DISABLE:
		शेष:
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPU, false);
			ingenic_config_pin(jzpc, pin, X2000_GPIO_PEPD, false);
		पूर्ण

	पूर्ण अन्यथा अगर (jzpc->info->version >= ID_X1830) अणु
		अचिन्हित पूर्णांक idx = pin % PINS_PER_GPIO_CHIP;
		अचिन्हित पूर्णांक half = PINS_PER_GPIO_CHIP / 2;
		अचिन्हित पूर्णांक idxh = (pin % half) * 2;
		अचिन्हित पूर्णांक offt = pin / PINS_PER_GPIO_CHIP;

		अगर (idx < half) अणु
			regmap_ग_लिखो(jzpc->map, offt * jzpc->info->reg_offset +
					REG_CLEAR(X1830_GPIO_PEL), 3 << idxh);
			regmap_ग_लिखो(jzpc->map, offt * jzpc->info->reg_offset +
					REG_SET(X1830_GPIO_PEL), bias << idxh);
		पूर्ण अन्यथा अणु
			regmap_ग_लिखो(jzpc->map, offt * jzpc->info->reg_offset +
					REG_CLEAR(X1830_GPIO_PEH), 3 << idxh);
			regmap_ग_लिखो(jzpc->map, offt * jzpc->info->reg_offset +
					REG_SET(X1830_GPIO_PEH), bias << idxh);
		पूर्ण

	पूर्ण अन्यथा अगर (jzpc->info->version >= ID_JZ4770) अणु
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PEN, !bias);
	पूर्ण अन्यथा अगर (jzpc->info->version >= ID_JZ4740) अणु
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_PULL_DIS, !bias);
	पूर्ण अन्यथा अणु
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_GPPUR, bias);
	पूर्ण
पूर्ण

अटल व्योम ingenic_set_schmitt_trigger(काष्ठा ingenic_pinctrl *jzpc,
		अचिन्हित पूर्णांक pin, bool enable)
अणु
	अगर (jzpc->info->version >= ID_X2000)
		ingenic_config_pin(jzpc, pin, X2000_GPIO_SMT, enable);
	अन्यथा
		ingenic_config_pin(jzpc, pin, X1830_GPIO_SMT, enable);
पूर्ण

अटल व्योम ingenic_set_output_level(काष्ठा ingenic_pinctrl *jzpc,
				     अचिन्हित पूर्णांक pin, bool high)
अणु
	अगर (jzpc->info->version >= ID_JZ4770)
		ingenic_config_pin(jzpc, pin, JZ4770_GPIO_PAT0, high);
	अन्यथा अगर (jzpc->info->version >= ID_JZ4740)
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_DATA, high);
	अन्यथा
		ingenic_config_pin(jzpc, pin, JZ4730_GPIO_DATA, high);
पूर्ण

अटल व्योम ingenic_set_slew_rate(काष्ठा ingenic_pinctrl *jzpc,
		अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक slew)
अणु
	अगर (jzpc->info->version >= ID_X2000)
		ingenic_config_pin(jzpc, pin, X2000_GPIO_SR, slew);
	अन्यथा
		ingenic_config_pin(jzpc, pin, X1830_GPIO_SR, slew);
पूर्ण

अटल पूर्णांक ingenic_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
		अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा ingenic_pinctrl *jzpc = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक idx = pin % PINS_PER_GPIO_CHIP;
	अचिन्हित पूर्णांक offt = pin / PINS_PER_GPIO_CHIP;
	अचिन्हित पूर्णांक cfg, arg;
	पूर्णांक ret;

	क्रम (cfg = 0; cfg < num_configs; cfg++) अणु
		चयन (pinconf_to_config_param(configs[cfg])) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		हाल PIN_CONFIG_OUTPUT:
		हाल PIN_CONFIG_SLEW_RATE:
			जारी;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	क्रम (cfg = 0; cfg < num_configs; cfg++) अणु
		arg = pinconf_to_config_argument(configs[cfg]);

		चयन (pinconf_to_config_param(configs[cfg])) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			dev_dbg(jzpc->dev, "disable pull-over for pin P%c%u\n",
					'A' + offt, idx);
			ingenic_set_bias(jzpc, pin, GPIO_PULL_DIS);
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
			अगर (!(jzpc->info->pull_ups[offt] & BIT(idx)))
				वापस -EINVAL;
			dev_dbg(jzpc->dev, "set pull-up for pin P%c%u\n",
					'A' + offt, idx);
			ingenic_set_bias(jzpc, pin, GPIO_PULL_UP);
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			अगर (!(jzpc->info->pull_करोwns[offt] & BIT(idx)))
				वापस -EINVAL;
			dev_dbg(jzpc->dev, "set pull-down for pin P%c%u\n",
					'A' + offt, idx);
			ingenic_set_bias(jzpc, pin, GPIO_PULL_DOWN);
			अवरोध;

		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			अगर (jzpc->info->version < ID_X1830)
				वापस -EINVAL;

			ingenic_set_schmitt_trigger(jzpc, pin, arg);
			अवरोध;

		हाल PIN_CONFIG_OUTPUT:
			ret = pinctrl_gpio_direction_output(pin);
			अगर (ret)
				वापस ret;

			ingenic_set_output_level(jzpc, pin, arg);
			अवरोध;

		हाल PIN_CONFIG_SLEW_RATE:
			अगर (jzpc->info->version < ID_X1830)
				वापस -EINVAL;

			ingenic_set_slew_rate(jzpc, pin, arg);
			अवरोध;

		शेष:
			/* unreachable */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *config)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक i, npins, old = 0;
	पूर्णांक ret;

	ret = pinctrl_generic_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < npins; i++) अणु
		अगर (ingenic_pinconf_get(pctldev, pins[i], config))
			वापस -ENOTSUPP;

		/* configs करो not match between two pins */
		अगर (i && (old != *config))
			वापस -ENOTSUPP;

		old = *config;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *configs,
		अचिन्हित पूर्णांक num_configs)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक i, npins;
	पूर्णांक ret;

	ret = pinctrl_generic_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < npins; i++) अणु
		ret = ingenic_pinconf_set(pctldev,
				pins[i], configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops ingenic_confops = अणु
	.is_generic = true,
	.pin_config_get = ingenic_pinconf_get,
	.pin_config_set = ingenic_pinconf_set,
	.pin_config_group_get = ingenic_pinconf_group_get,
	.pin_config_group_set = ingenic_pinconf_group_set,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ingenic_pinctrl_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ingenic_gpio_of_match[] __initस्थिर = अणु
	अणु .compatible = "ingenic,jz4730-gpio", पूर्ण,
	अणु .compatible = "ingenic,jz4740-gpio", पूर्ण,
	अणु .compatible = "ingenic,jz4725b-gpio", पूर्ण,
	अणु .compatible = "ingenic,jz4750-gpio", पूर्ण,
	अणु .compatible = "ingenic,jz4755-gpio", पूर्ण,
	अणु .compatible = "ingenic,jz4760-gpio", पूर्ण,
	अणु .compatible = "ingenic,jz4770-gpio", पूर्ण,
	अणु .compatible = "ingenic,jz4775-gpio", पूर्ण,
	अणु .compatible = "ingenic,jz4780-gpio", पूर्ण,
	अणु .compatible = "ingenic,x1000-gpio", पूर्ण,
	अणु .compatible = "ingenic,x1830-gpio", पूर्ण,
	अणु .compatible = "ingenic,x2000-gpio", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init ingenic_gpio_probe(काष्ठा ingenic_pinctrl *jzpc,
				     काष्ठा device_node *node)
अणु
	काष्ठा ingenic_gpio_chip *jzgc;
	काष्ठा device *dev = jzpc->dev;
	काष्ठा gpio_irq_chip *girq;
	अचिन्हित पूर्णांक bank;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(node, "reg", &bank);
	अगर (err) अणु
		dev_err(dev, "Cannot read \"reg\" property: %i\n", err);
		वापस err;
	पूर्ण

	jzgc = devm_kzalloc(dev, माप(*jzgc), GFP_KERNEL);
	अगर (!jzgc)
		वापस -ENOMEM;

	jzgc->jzpc = jzpc;
	jzgc->reg_base = bank * jzpc->info->reg_offset;

	jzgc->gc.label = devm_kaप्र_लिखो(dev, GFP_KERNEL, "GPIO%c", 'A' + bank);
	अगर (!jzgc->gc.label)
		वापस -ENOMEM;

	/* DO NOT EXPAND THIS: FOR BACKWARD GPIO NUMBERSPACE COMPATIBIBILITY
	 * ONLY: WORK TO TRANSITION CONSUMERS TO USE THE GPIO DESCRIPTOR API IN
	 * <linux/gpio/consumer.h> INSTEAD.
	 */
	jzgc->gc.base = bank * 32;

	jzgc->gc.ngpio = 32;
	jzgc->gc.parent = dev;
	jzgc->gc.of_node = node;
	jzgc->gc.owner = THIS_MODULE;

	jzgc->gc.set = ingenic_gpio_set;
	jzgc->gc.get = ingenic_gpio_get;
	jzgc->gc.direction_input = ingenic_gpio_direction_input;
	jzgc->gc.direction_output = ingenic_gpio_direction_output;
	jzgc->gc.get_direction = ingenic_gpio_get_direction;
	jzgc->gc.request = gpiochip_generic_request;
	jzgc->gc.मुक्त = gpiochip_generic_मुक्त;

	jzgc->irq = irq_of_parse_and_map(node, 0);
	अगर (!jzgc->irq)
		वापस -EINVAL;

	jzgc->irq_chip.name = jzgc->gc.label;
	jzgc->irq_chip.irq_enable = ingenic_gpio_irq_enable;
	jzgc->irq_chip.irq_disable = ingenic_gpio_irq_disable;
	jzgc->irq_chip.irq_unmask = ingenic_gpio_irq_unmask;
	jzgc->irq_chip.irq_mask = ingenic_gpio_irq_mask;
	jzgc->irq_chip.irq_ack = ingenic_gpio_irq_ack;
	jzgc->irq_chip.irq_set_type = ingenic_gpio_irq_set_type;
	jzgc->irq_chip.irq_set_wake = ingenic_gpio_irq_set_wake;
	jzgc->irq_chip.irq_request_resources = ingenic_gpio_irq_request;
	jzgc->irq_chip.irq_release_resources = ingenic_gpio_irq_release;
	jzgc->irq_chip.flags = IRQCHIP_MASK_ON_SUSPEND;

	girq = &jzgc->gc.irq;
	girq->chip = &jzgc->irq_chip;
	girq->parent_handler = ingenic_gpio_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(dev, 1, माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;

	girq->parents[0] = jzgc->irq;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;

	err = devm_gpiochip_add_data(dev, &jzgc->gc, jzgc);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक __init ingenic_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ingenic_pinctrl *jzpc;
	काष्ठा pinctrl_desc *pctl_desc;
	व्योम __iomem *base;
	स्थिर काष्ठा ingenic_chip_info *chip_info;
	काष्ठा device_node *node;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	chip_info = of_device_get_match_data(dev);
	अगर (!chip_info) अणु
		dev_err(dev, "Unsupported SoC\n");
		वापस -EINVAL;
	पूर्ण

	jzpc = devm_kzalloc(dev, माप(*jzpc), GFP_KERNEL);
	अगर (!jzpc)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	jzpc->map = devm_regmap_init_mmio(dev, base,
			&ingenic_pinctrl_regmap_config);
	अगर (IS_ERR(jzpc->map)) अणु
		dev_err(dev, "Failed to create regmap\n");
		वापस PTR_ERR(jzpc->map);
	पूर्ण

	jzpc->dev = dev;
	jzpc->info = chip_info;

	pctl_desc = devm_kzalloc(&pdev->dev, माप(*pctl_desc), GFP_KERNEL);
	अगर (!pctl_desc)
		वापस -ENOMEM;

	/* fill in pinctrl_desc काष्ठाure */
	pctl_desc->name = dev_name(dev);
	pctl_desc->owner = THIS_MODULE;
	pctl_desc->pctlops = &ingenic_pctlops;
	pctl_desc->pmxops = &ingenic_pmxops;
	pctl_desc->confops = &ingenic_confops;
	pctl_desc->npins = chip_info->num_chips * PINS_PER_GPIO_CHIP;
	pctl_desc->pins = jzpc->pdesc = devm_kसुस्मृति(&pdev->dev,
			pctl_desc->npins, माप(*jzpc->pdesc), GFP_KERNEL);
	अगर (!jzpc->pdesc)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctl_desc->npins; i++) अणु
		jzpc->pdesc[i].number = i;
		jzpc->pdesc[i].name = kaप्र_लिखो(GFP_KERNEL, "P%c%d",
						'A' + (i / PINS_PER_GPIO_CHIP),
						i % PINS_PER_GPIO_CHIP);
	पूर्ण

	jzpc->pctl = devm_pinctrl_रेजिस्टर(dev, pctl_desc, jzpc);
	अगर (IS_ERR(jzpc->pctl)) अणु
		dev_err(dev, "Failed to register pinctrl\n");
		वापस PTR_ERR(jzpc->pctl);
	पूर्ण

	क्रम (i = 0; i < chip_info->num_groups; i++) अणु
		स्थिर काष्ठा group_desc *group = &chip_info->groups[i];

		err = pinctrl_generic_add_group(jzpc->pctl, group->name,
				group->pins, group->num_pins, group->data);
		अगर (err < 0) अणु
			dev_err(dev, "Failed to register group %s\n",
					group->name);
			वापस err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < chip_info->num_functions; i++) अणु
		स्थिर काष्ठा function_desc *func = &chip_info->functions[i];

		err = pinmux_generic_add_function(jzpc->pctl, func->name,
				func->group_names, func->num_group_names,
				func->data);
		अगर (err < 0) अणु
			dev_err(dev, "Failed to register function %s\n",
					func->name);
			वापस err;
		पूर्ण
	पूर्ण

	dev_set_drvdata(dev, jzpc->map);

	क्रम_each_child_of_node(dev->of_node, node) अणु
		अगर (of_match_node(ingenic_gpio_of_match, node)) अणु
			err = ingenic_gpio_probe(jzpc, node);
			अगर (err) अणु
				of_node_put(node);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा IF_ENABLED(cfg, ptr)	PTR_IF(IS_ENABLED(cfg), (ptr))

अटल स्थिर काष्ठा of_device_id ingenic_pinctrl_of_match[] = अणु
	अणु
		.compatible = "ingenic,jz4730-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4730, &jz4730_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,jz4740-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4740, &jz4740_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,jz4725b-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4725B, &jz4725b_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,jz4750-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4750, &jz4750_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,jz4755-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4755, &jz4755_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,jz4760-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4760, &jz4760_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,jz4760b-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4760, &jz4760_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,jz4770-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4770, &jz4770_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,jz4775-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4775, &jz4775_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,jz4780-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_JZ4780, &jz4780_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,x1000-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_X1000, &x1000_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,x1000e-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_X1000, &x1000_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,x1500-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_X1500, &x1500_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,x1830-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_X1830, &x1830_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,x2000-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_X2000, &x2000_chip_info)
	पूर्ण,
	अणु
		.compatible = "ingenic,x2000e-pinctrl",
		.data = IF_ENABLED(CONFIG_MACH_X2000, &x2000_chip_info)
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ingenic_pinctrl_driver = अणु
	.driver = अणु
		.name = "pinctrl-ingenic",
		.of_match_table = ingenic_pinctrl_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ingenic_pinctrl_drv_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_probe(&ingenic_pinctrl_driver,
				     ingenic_pinctrl_probe);
पूर्ण
subsys_initcall(ingenic_pinctrl_drv_रेजिस्टर);
