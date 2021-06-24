<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NXP PCF50633 GPIO Driver
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Author: Balaji Rao <balajirrao@खोलोmoko.org>
 * All rights reserved.
 *
 * Broken करोwn from monstrous PCF50633 driver मुख्यly by
 * Harald Welte, Andy Green and Werner Almesberger
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/mfd/pcf50633/core.h>
#समावेश <linux/mfd/pcf50633/gpपन.स>
#समावेश <linux/mfd/pcf50633/pmic.h>

अटल स्थिर u8 pcf50633_regulator_रेजिस्टरs[PCF50633_NUM_REGULATORS] = अणु
	[PCF50633_REGULATOR_AUTO]	= PCF50633_REG_AUTOOUT,
	[PCF50633_REGULATOR_DOWN1]	= PCF50633_REG_DOWN1OUT,
	[PCF50633_REGULATOR_DOWN2]	= PCF50633_REG_DOWN2OUT,
	[PCF50633_REGULATOR_MEMLDO]	= PCF50633_REG_MEMLDOOUT,
	[PCF50633_REGULATOR_LDO1]	= PCF50633_REG_LDO1OUT,
	[PCF50633_REGULATOR_LDO2]	= PCF50633_REG_LDO2OUT,
	[PCF50633_REGULATOR_LDO3]	= PCF50633_REG_LDO3OUT,
	[PCF50633_REGULATOR_LDO4]	= PCF50633_REG_LDO4OUT,
	[PCF50633_REGULATOR_LDO5]	= PCF50633_REG_LDO5OUT,
	[PCF50633_REGULATOR_LDO6]	= PCF50633_REG_LDO6OUT,
	[PCF50633_REGULATOR_HCLDO]	= PCF50633_REG_HCLDOOUT,
पूर्ण;

पूर्णांक pcf50633_gpio_set(काष्ठा pcf50633 *pcf, पूर्णांक gpio, u8 val)
अणु
	u8 reg;

	reg = gpio - PCF50633_GPIO1 + PCF50633_REG_GPIO1CFG;

	वापस pcf50633_reg_set_bit_mask(pcf, reg, 0x07, val);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_gpio_set);

u8 pcf50633_gpio_get(काष्ठा pcf50633 *pcf, पूर्णांक gpio)
अणु
	u8 reg, val;

	reg = gpio - PCF50633_GPIO1 + PCF50633_REG_GPIO1CFG;
	val = pcf50633_reg_पढ़ो(pcf, reg) & 0x07;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_gpio_get);

पूर्णांक pcf50633_gpio_invert_set(काष्ठा pcf50633 *pcf, पूर्णांक gpio, पूर्णांक invert)
अणु
	u8 val, reg;

	reg = gpio - PCF50633_GPIO1 + PCF50633_REG_GPIO1CFG;
	val = !!invert << 3;

	वापस pcf50633_reg_set_bit_mask(pcf, reg, 1 << 3, val);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_gpio_invert_set);

पूर्णांक pcf50633_gpio_invert_get(काष्ठा pcf50633 *pcf, पूर्णांक gpio)
अणु
	u8 reg, val;

	reg = gpio - PCF50633_GPIO1 + PCF50633_REG_GPIO1CFG;
	val = pcf50633_reg_पढ़ो(pcf, reg);

	वापस val & (1 << 3);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_gpio_invert_get);

पूर्णांक pcf50633_gpio_घातer_supply_set(काष्ठा pcf50633 *pcf,
					पूर्णांक gpio, पूर्णांक regulator, पूर्णांक on)
अणु
	u8 reg, val, mask;

	/* the *ENA रेजिस्टर is always one after the *OUT रेजिस्टर */
	reg = pcf50633_regulator_रेजिस्टरs[regulator] + 1;

	val = !!on << (gpio - PCF50633_GPIO1);
	mask = 1 << (gpio - PCF50633_GPIO1);

	वापस pcf50633_reg_set_bit_mask(pcf, reg, mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_gpio_घातer_supply_set);

MODULE_LICENSE("GPL");
