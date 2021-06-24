<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Base driver क्रम Marvell 88PM8607
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *
 * Author: Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/घातer/अक्षरger-manager.h>

#घोषणा INT_STATUS_NUM			3

अटल स्थिर काष्ठा resource bk0_resources[] = अणु
	अणु2, 2, "duty cycle", IORESOURCE_REG, पूर्ण,
	अणु3, 3, "always on",  IORESOURCE_REG, पूर्ण,
	अणु3, 3, "current",    IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource bk1_resources[] = अणु
	अणु4, 4, "duty cycle", IORESOURCE_REG, पूर्ण,
	अणु5, 5, "always on",  IORESOURCE_REG, पूर्ण,
	अणु5, 5, "current",    IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource bk2_resources[] = अणु
	अणु6, 6, "duty cycle", IORESOURCE_REG, पूर्ण,
	अणु7, 7, "always on",  IORESOURCE_REG, पूर्ण,
	अणु5, 5, "current",    IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource led0_resources[] = अणु
	/* RGB1 Red LED */
	अणु0xd, 0xd, "control", IORESOURCE_REG, पूर्ण,
	अणु0xc, 0xc, "blink",   IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource led1_resources[] = अणु
	/* RGB1 Green LED */
	अणु0xe, 0xe, "control", IORESOURCE_REG, पूर्ण,
	अणु0xc, 0xc, "blink",   IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource led2_resources[] = अणु
	/* RGB1 Blue LED */
	अणु0xf, 0xf, "control", IORESOURCE_REG, पूर्ण,
	अणु0xc, 0xc, "blink",   IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource led3_resources[] = अणु
	/* RGB2 Red LED */
	अणु0x9, 0x9, "control", IORESOURCE_REG, पूर्ण,
	अणु0x8, 0x8, "blink",   IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource led4_resources[] = अणु
	/* RGB2 Green LED */
	अणु0xa, 0xa, "control", IORESOURCE_REG, पूर्ण,
	अणु0x8, 0x8, "blink",   IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource led5_resources[] = अणु
	/* RGB2 Blue LED */
	अणु0xb, 0xb, "control", IORESOURCE_REG, पूर्ण,
	अणु0x8, 0x8, "blink",   IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource buck1_resources[] = अणु
	अणु0x24, 0x24, "buck set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource buck2_resources[] = अणु
	अणु0x25, 0x25, "buck set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource buck3_resources[] = अणु
	अणु0x26, 0x26, "buck set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो1_resources[] = अणु
	अणु0x10, 0x10, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो2_resources[] = अणु
	अणु0x11, 0x11, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो3_resources[] = अणु
	अणु0x12, 0x12, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो4_resources[] = अणु
	अणु0x13, 0x13, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो5_resources[] = अणु
	अणु0x14, 0x14, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो6_resources[] = अणु
	अणु0x15, 0x15, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो7_resources[] = अणु
	अणु0x16, 0x16, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो8_resources[] = अणु
	अणु0x17, 0x17, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो9_resources[] = अणु
	अणु0x18, 0x18, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो10_resources[] = अणु
	अणु0x19, 0x19, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो12_resources[] = अणु
	अणु0x1a, 0x1a, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो_vibrator_resources[] = अणु
	अणु0x28, 0x28, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा resource lकरो14_resources[] = अणु
	अणु0x1b, 0x1b, "ldo set", IORESOURCE_REG, पूर्ण,
पूर्ण;

अटल काष्ठा resource touch_resources[] = अणु
	अणुPM8607_IRQ_PEN, PM8607_IRQ_PEN, "touch", IORESOURCE_IRQ,पूर्ण,
पूर्ण;

अटल काष्ठा resource onkey_resources[] = अणु
	अणुPM8607_IRQ_ONKEY, PM8607_IRQ_ONKEY, "onkey", IORESOURCE_IRQ,पूर्ण,
पूर्ण;

अटल काष्ठा resource codec_resources[] = अणु
	/* Headset microphone insertion or removal */
	अणुPM8607_IRQ_MICIN,   PM8607_IRQ_MICIN,   "micin",   IORESOURCE_IRQ,पूर्ण,
	/* Hook-चयन press or release */
	अणुPM8607_IRQ_HOOK,    PM8607_IRQ_HOOK,    "hook",    IORESOURCE_IRQ,पूर्ण,
	/* Headset insertion or removal */
	अणुPM8607_IRQ_HEADSET, PM8607_IRQ_HEADSET, "headset", IORESOURCE_IRQ,पूर्ण,
	/* Audio लघु */
	अणुPM8607_IRQ_AUDIO_SHORT, PM8607_IRQ_AUDIO_SHORT, "audio-short",
	 IORESOURCE_IRQ,पूर्ण,
पूर्ण;

अटल काष्ठा resource battery_resources[] = अणु
	अणुPM8607_IRQ_CC,  PM8607_IRQ_CC,  "columb counter", IORESOURCE_IRQ,पूर्ण,
	अणुPM8607_IRQ_BAT, PM8607_IRQ_BAT, "battery",        IORESOURCE_IRQ,पूर्ण,
पूर्ण;

अटल काष्ठा resource अक्षरger_resources[] = अणु
	अणुPM8607_IRQ_CHG,  PM8607_IRQ_CHG,  "charger detect",  IORESOURCE_IRQ,पूर्ण,
	अणुPM8607_IRQ_CHG_DONE,  PM8607_IRQ_CHG_DONE,  "charging done",
	 IORESOURCE_IRQ,पूर्ण,
	अणुPM8607_IRQ_CHG_FAIL,  PM8607_IRQ_CHG_FAIL,  "charging timeout",
	 IORESOURCE_IRQ,पूर्ण,
	अणुPM8607_IRQ_CHG_FAULT, PM8607_IRQ_CHG_FAULT, "charging fault",
	 IORESOURCE_IRQ,पूर्ण,
	अणुPM8607_IRQ_GPADC1,    PM8607_IRQ_GPADC1,    "battery temperature",
	 IORESOURCE_IRQ,पूर्ण,
	अणुPM8607_IRQ_VBAT, PM8607_IRQ_VBAT, "battery voltage", IORESOURCE_IRQ,पूर्ण,
	अणुPM8607_IRQ_VCHG, PM8607_IRQ_VCHG, "vchg voltage",    IORESOURCE_IRQ,पूर्ण,
पूर्ण;

अटल काष्ठा resource rtc_resources[] = अणु
	अणुPM8607_IRQ_RTC, PM8607_IRQ_RTC, "rtc", IORESOURCE_IRQ,पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell bk_devs[] = अणु
	अणु
		.name = "88pm860x-backlight",
		.id = 0,
		.num_resources = ARRAY_SIZE(bk0_resources),
		.resources = bk0_resources,
	पूर्ण, अणु
		.name = "88pm860x-backlight",
		.id = 1,
		.num_resources = ARRAY_SIZE(bk1_resources),
		.resources = bk1_resources,
	पूर्ण, अणु
		.name = "88pm860x-backlight",
		.id = 2,
		.num_resources = ARRAY_SIZE(bk2_resources),
		.resources = bk2_resources,
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell led_devs[] = अणु
	अणु
		.name = "88pm860x-led",
		.id = 0,
		.num_resources = ARRAY_SIZE(led0_resources),
		.resources = led0_resources,
	पूर्ण, अणु
		.name = "88pm860x-led",
		.id = 1,
		.num_resources = ARRAY_SIZE(led1_resources),
		.resources = led1_resources,
	पूर्ण, अणु
		.name = "88pm860x-led",
		.id = 2,
		.num_resources = ARRAY_SIZE(led2_resources),
		.resources = led2_resources,
	पूर्ण, अणु
		.name = "88pm860x-led",
		.id = 3,
		.num_resources = ARRAY_SIZE(led3_resources),
		.resources = led3_resources,
	पूर्ण, अणु
		.name = "88pm860x-led",
		.id = 4,
		.num_resources = ARRAY_SIZE(led4_resources),
		.resources = led4_resources,
	पूर्ण, अणु
		.name = "88pm860x-led",
		.id = 5,
		.num_resources = ARRAY_SIZE(led5_resources),
		.resources = led5_resources,
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell reg_devs[] = अणु
	अणु
		.name = "88pm860x-regulator",
		.id = 0,
		.num_resources = ARRAY_SIZE(buck1_resources),
		.resources = buck1_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 1,
		.num_resources = ARRAY_SIZE(buck2_resources),
		.resources = buck2_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 2,
		.num_resources = ARRAY_SIZE(buck3_resources),
		.resources = buck3_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 3,
		.num_resources = ARRAY_SIZE(lकरो1_resources),
		.resources = lकरो1_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 4,
		.num_resources = ARRAY_SIZE(lकरो2_resources),
		.resources = lकरो2_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 5,
		.num_resources = ARRAY_SIZE(lकरो3_resources),
		.resources = lकरो3_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 6,
		.num_resources = ARRAY_SIZE(lकरो4_resources),
		.resources = lकरो4_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 7,
		.num_resources = ARRAY_SIZE(lकरो5_resources),
		.resources = lकरो5_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 8,
		.num_resources = ARRAY_SIZE(lकरो6_resources),
		.resources = lकरो6_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 9,
		.num_resources = ARRAY_SIZE(lकरो7_resources),
		.resources = lकरो7_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 10,
		.num_resources = ARRAY_SIZE(lकरो8_resources),
		.resources = lकरो8_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 11,
		.num_resources = ARRAY_SIZE(lकरो9_resources),
		.resources = lकरो9_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 12,
		.num_resources = ARRAY_SIZE(lकरो10_resources),
		.resources = lकरो10_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 13,
		.num_resources = ARRAY_SIZE(lकरो12_resources),
		.resources = lकरो12_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 14,
		.num_resources = ARRAY_SIZE(lकरो_vibrator_resources),
		.resources = lकरो_vibrator_resources,
	पूर्ण, अणु
		.name = "88pm860x-regulator",
		.id = 15,
		.num_resources = ARRAY_SIZE(lकरो14_resources),
		.resources = lकरो14_resources,
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell touch_devs[] = अणु
	अणु"88pm860x-touch", -1,पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell onkey_devs[] = अणु
	अणु"88pm860x-onkey", -1,पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell codec_devs[] = अणु
	अणु"88pm860x-codec", -1,पूर्ण,
पूर्ण;

अटल काष्ठा regulator_consumer_supply preg_supply[] = अणु
	REGULATOR_SUPPLY("preg", "charger-manager"),
पूर्ण;

अटल काष्ठा regulator_init_data preg_init_data = अणु
	.num_consumer_supplies	= ARRAY_SIZE(preg_supply),
	.consumer_supplies	= &preg_supply[0],
पूर्ण;

अटल काष्ठा अक्षरger_regulator chg_desc_regulator_data[] = अणु
	अणु .regulator_name = "preg", पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell घातer_devs[] = अणु
	अणु"88pm860x-battery", -1,पूर्ण,
	अणु"88pm860x-charger", -1,पूर्ण,
	अणु"88pm860x-preg",    -1,पूर्ण,
	अणु"charger-manager", -1,पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell rtc_devs[] = अणु
	अणु"88pm860x-rtc", -1,पूर्ण,
पूर्ण;


काष्ठा pm860x_irq_data अणु
	पूर्णांक	reg;
	पूर्णांक	mask_reg;
	पूर्णांक	enable;		/* enable or not */
	पूर्णांक	offs;		/* bit offset in mask रेजिस्टर */
पूर्ण;

अटल काष्ठा pm860x_irq_data pm860x_irqs[] = अणु
	[PM8607_IRQ_ONKEY] = अणु
		.reg		= PM8607_INT_STATUS1,
		.mask_reg	= PM8607_INT_MASK_1,
		.offs		= 1 << 0,
	पूर्ण,
	[PM8607_IRQ_EXTON] = अणु
		.reg		= PM8607_INT_STATUS1,
		.mask_reg	= PM8607_INT_MASK_1,
		.offs		= 1 << 1,
	पूर्ण,
	[PM8607_IRQ_CHG] = अणु
		.reg		= PM8607_INT_STATUS1,
		.mask_reg	= PM8607_INT_MASK_1,
		.offs		= 1 << 2,
	पूर्ण,
	[PM8607_IRQ_BAT] = अणु
		.reg		= PM8607_INT_STATUS1,
		.mask_reg	= PM8607_INT_MASK_1,
		.offs		= 1 << 3,
	पूर्ण,
	[PM8607_IRQ_RTC] = अणु
		.reg		= PM8607_INT_STATUS1,
		.mask_reg	= PM8607_INT_MASK_1,
		.offs		= 1 << 4,
	पूर्ण,
	[PM8607_IRQ_CC] = अणु
		.reg		= PM8607_INT_STATUS1,
		.mask_reg	= PM8607_INT_MASK_1,
		.offs		= 1 << 5,
	पूर्ण,
	[PM8607_IRQ_VBAT] = अणु
		.reg		= PM8607_INT_STATUS2,
		.mask_reg	= PM8607_INT_MASK_2,
		.offs		= 1 << 0,
	पूर्ण,
	[PM8607_IRQ_VCHG] = अणु
		.reg		= PM8607_INT_STATUS2,
		.mask_reg	= PM8607_INT_MASK_2,
		.offs		= 1 << 1,
	पूर्ण,
	[PM8607_IRQ_VSYS] = अणु
		.reg		= PM8607_INT_STATUS2,
		.mask_reg	= PM8607_INT_MASK_2,
		.offs		= 1 << 2,
	पूर्ण,
	[PM8607_IRQ_TINT] = अणु
		.reg		= PM8607_INT_STATUS2,
		.mask_reg	= PM8607_INT_MASK_2,
		.offs		= 1 << 3,
	पूर्ण,
	[PM8607_IRQ_GPADC0] = अणु
		.reg		= PM8607_INT_STATUS2,
		.mask_reg	= PM8607_INT_MASK_2,
		.offs		= 1 << 4,
	पूर्ण,
	[PM8607_IRQ_GPADC1] = अणु
		.reg		= PM8607_INT_STATUS2,
		.mask_reg	= PM8607_INT_MASK_2,
		.offs		= 1 << 5,
	पूर्ण,
	[PM8607_IRQ_GPADC2] = अणु
		.reg		= PM8607_INT_STATUS2,
		.mask_reg	= PM8607_INT_MASK_2,
		.offs		= 1 << 6,
	पूर्ण,
	[PM8607_IRQ_GPADC3] = अणु
		.reg		= PM8607_INT_STATUS2,
		.mask_reg	= PM8607_INT_MASK_2,
		.offs		= 1 << 7,
	पूर्ण,
	[PM8607_IRQ_AUDIO_SHORT] = अणु
		.reg		= PM8607_INT_STATUS3,
		.mask_reg	= PM8607_INT_MASK_3,
		.offs		= 1 << 0,
	पूर्ण,
	[PM8607_IRQ_PEN] = अणु
		.reg		= PM8607_INT_STATUS3,
		.mask_reg	= PM8607_INT_MASK_3,
		.offs		= 1 << 1,
	पूर्ण,
	[PM8607_IRQ_HEADSET] = अणु
		.reg		= PM8607_INT_STATUS3,
		.mask_reg	= PM8607_INT_MASK_3,
		.offs		= 1 << 2,
	पूर्ण,
	[PM8607_IRQ_HOOK] = अणु
		.reg		= PM8607_INT_STATUS3,
		.mask_reg	= PM8607_INT_MASK_3,
		.offs		= 1 << 3,
	पूर्ण,
	[PM8607_IRQ_MICIN] = अणु
		.reg		= PM8607_INT_STATUS3,
		.mask_reg	= PM8607_INT_MASK_3,
		.offs		= 1 << 4,
	पूर्ण,
	[PM8607_IRQ_CHG_FAIL] = अणु
		.reg		= PM8607_INT_STATUS3,
		.mask_reg	= PM8607_INT_MASK_3,
		.offs		= 1 << 5,
	पूर्ण,
	[PM8607_IRQ_CHG_DONE] = अणु
		.reg		= PM8607_INT_STATUS3,
		.mask_reg	= PM8607_INT_MASK_3,
		.offs		= 1 << 6,
	पूर्ण,
	[PM8607_IRQ_CHG_FAULT] = अणु
		.reg		= PM8607_INT_STATUS3,
		.mask_reg	= PM8607_INT_MASK_3,
		.offs		= 1 << 7,
	पूर्ण,
पूर्ण;

अटल irqवापस_t pm860x_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_chip *chip = data;
	काष्ठा pm860x_irq_data *irq_data;
	काष्ठा i2c_client *i2c;
	पूर्णांक पढ़ो_reg = -1, value = 0;
	पूर्णांक i;

	i2c = (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	क्रम (i = 0; i < ARRAY_SIZE(pm860x_irqs); i++) अणु
		irq_data = &pm860x_irqs[i];
		अगर (पढ़ो_reg != irq_data->reg) अणु
			पढ़ो_reg = irq_data->reg;
			value = pm860x_reg_पढ़ो(i2c, irq_data->reg);
		पूर्ण
		अगर (value & irq_data->enable)
			handle_nested_irq(chip->irq_base + i);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pm860x_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा pm860x_chip *chip = irq_data_get_irq_chip_data(data);

	mutex_lock(&chip->irq_lock);
पूर्ण

अटल व्योम pm860x_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा pm860x_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा pm860x_irq_data *irq_data;
	काष्ठा i2c_client *i2c;
	अटल अचिन्हित अक्षर cached[3] = अणु0x0, 0x0, 0x0पूर्ण;
	अचिन्हित अक्षर mask[3];
	पूर्णांक i;

	i2c = (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	/* Load cached value. In initial, all IRQs are masked */
	क्रम (i = 0; i < 3; i++)
		mask[i] = cached[i];
	क्रम (i = 0; i < ARRAY_SIZE(pm860x_irqs); i++) अणु
		irq_data = &pm860x_irqs[i];
		चयन (irq_data->mask_reg) अणु
		हाल PM8607_INT_MASK_1:
			mask[0] &= ~irq_data->offs;
			mask[0] |= irq_data->enable;
			अवरोध;
		हाल PM8607_INT_MASK_2:
			mask[1] &= ~irq_data->offs;
			mask[1] |= irq_data->enable;
			अवरोध;
		हाल PM8607_INT_MASK_3:
			mask[2] &= ~irq_data->offs;
			mask[2] |= irq_data->enable;
			अवरोध;
		शेष:
			dev_err(chip->dev, "wrong IRQ\n");
			अवरोध;
		पूर्ण
	पूर्ण
	/* update mask पूर्णांकo रेजिस्टरs */
	क्रम (i = 0; i < 3; i++) अणु
		अगर (mask[i] != cached[i]) अणु
			cached[i] = mask[i];
			pm860x_reg_ग_लिखो(i2c, PM8607_INT_MASK_1 + i, mask[i]);
		पूर्ण
	पूर्ण

	mutex_unlock(&chip->irq_lock);
पूर्ण

अटल व्योम pm860x_irq_enable(काष्ठा irq_data *data)
अणु
	pm860x_irqs[data->hwirq].enable = pm860x_irqs[data->hwirq].offs;
पूर्ण

अटल व्योम pm860x_irq_disable(काष्ठा irq_data *data)
अणु
	pm860x_irqs[data->hwirq].enable = 0;
पूर्ण

अटल काष्ठा irq_chip pm860x_irq_chip = अणु
	.name		= "88pm860x",
	.irq_bus_lock	= pm860x_irq_lock,
	.irq_bus_sync_unlock = pm860x_irq_sync_unlock,
	.irq_enable	= pm860x_irq_enable,
	.irq_disable	= pm860x_irq_disable,
पूर्ण;

अटल पूर्णांक pm860x_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				 irq_hw_number_t hw)
अणु
	irq_set_chip_data(virq, d->host_data);
	irq_set_chip_and_handler(virq, &pm860x_irq_chip, handle_edge_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pm860x_irq_करोमुख्य_ops = अणु
	.map	= pm860x_irq_करोमुख्य_map,
	.xlate	= irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

अटल पूर्णांक device_irq_init(काष्ठा pm860x_chip *chip,
				     काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	काष्ठा i2c_client *i2c = (chip->id == CHIP_PM8607) ?
		chip->client : chip->companion;
	अचिन्हित अक्षर status_buf[INT_STATUS_NUM];
	अचिन्हित दीर्घ flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT;
	पूर्णांक data, mask, ret = -EINVAL;
	पूर्णांक nr_irqs, irq_base = -1;
	काष्ठा device_node *node = i2c->dev.of_node;

	mask = PM8607_B0_MISC1_INV_INT | PM8607_B0_MISC1_INT_CLEAR
		| PM8607_B0_MISC1_INT_MASK;
	data = 0;
	chip->irq_mode = 0;
	अगर (pdata && pdata->irq_mode) अणु
		/*
		 * irq_mode defines the way of clearing पूर्णांकerrupt. If it's 1,
		 * clear IRQ by ग_लिखो. Otherwise, clear it by पढ़ो.
		 * This control bit is valid from 88PM8607 B0 steping.
		 */
		data |= PM8607_B0_MISC1_INT_CLEAR;
		chip->irq_mode = 1;
	पूर्ण
	ret = pm860x_set_bits(i2c, PM8607_B0_MISC1, mask, data);
	अगर (ret < 0)
		जाओ out;

	/* mask all IRQs */
	स_रखो(status_buf, 0, INT_STATUS_NUM);
	ret = pm860x_bulk_ग_लिखो(i2c, PM8607_INT_MASK_1,
				INT_STATUS_NUM, status_buf);
	अगर (ret < 0)
		जाओ out;

	अगर (chip->irq_mode) अणु
		/* clear पूर्णांकerrupt status by ग_लिखो */
		स_रखो(status_buf, 0xFF, INT_STATUS_NUM);
		ret = pm860x_bulk_ग_लिखो(i2c, PM8607_INT_STATUS1,
					INT_STATUS_NUM, status_buf);
	पूर्ण अन्यथा अणु
		/* clear पूर्णांकerrupt status by पढ़ो */
		ret = pm860x_bulk_पढ़ो(i2c, PM8607_INT_STATUS1,
					INT_STATUS_NUM, status_buf);
	पूर्ण
	अगर (ret < 0)
		जाओ out;

	mutex_init(&chip->irq_lock);

	अगर (pdata && pdata->irq_base)
		irq_base = pdata->irq_base;
	nr_irqs = ARRAY_SIZE(pm860x_irqs);
	chip->irq_base = irq_alloc_descs(irq_base, 0, nr_irqs, 0);
	अगर (chip->irq_base < 0) अणु
		dev_err(&i2c->dev, "Failed to allocate interrupts, ret:%d\n",
			chip->irq_base);
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	irq_करोमुख्य_add_legacy(node, nr_irqs, chip->irq_base, 0,
			      &pm860x_irq_करोमुख्य_ops, chip);
	chip->core_irq = i2c->irq;
	अगर (!chip->core_irq)
		जाओ out;

	ret = request_thपढ़ोed_irq(chip->core_irq, शून्य, pm860x_irq,
				   flags | IRQF_ONESHOT, "88pm860x", chip);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to request IRQ: %d\n", ret);
		chip->core_irq = 0;
	पूर्ण

	वापस 0;
out:
	chip->core_irq = 0;
	वापस ret;
पूर्ण

अटल व्योम device_irq_निकास(काष्ठा pm860x_chip *chip)
अणु
	अगर (chip->core_irq)
		मुक्त_irq(chip->core_irq, chip);
पूर्ण

पूर्णांक pm8606_osc_enable(काष्ठा pm860x_chip *chip, अचिन्हित लघु client)
अणु
	पूर्णांक ret = -EIO;
	काष्ठा i2c_client *i2c = (chip->id == CHIP_PM8606) ?
		chip->client : chip->companion;

	dev_dbg(chip->dev, "%s(B): client=0x%x\n", __func__, client);
	dev_dbg(chip->dev, "%s(B): vote=0x%x status=%d\n",
			__func__, chip->osc_vote,
			chip->osc_status);

	mutex_lock(&chip->osc_lock);
	/* Update voting status */
	chip->osc_vote |= client;
	/* If reference group is off - turn on*/
	अगर (chip->osc_status != PM8606_REF_GP_OSC_ON) अणु
		chip->osc_status = PM8606_REF_GP_OSC_UNKNOWN;
		/* Enable Reference group Vsys */
		अगर (pm860x_set_bits(i2c, PM8606_VSYS,
				PM8606_VSYS_EN, PM8606_VSYS_EN))
			जाओ out;

		/*Enable Internal Oscillator */
		अगर (pm860x_set_bits(i2c, PM8606_MISC,
				PM8606_MISC_OSC_EN, PM8606_MISC_OSC_EN))
			जाओ out;
		/* Update status (only अगर ग_लिखोs succeed) */
		chip->osc_status = PM8606_REF_GP_OSC_ON;
	पूर्ण
	mutex_unlock(&chip->osc_lock);

	dev_dbg(chip->dev, "%s(A): vote=0x%x status=%d ret=%d\n",
			__func__, chip->osc_vote,
			chip->osc_status, ret);
	वापस 0;
out:
	mutex_unlock(&chip->osc_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pm8606_osc_enable);

पूर्णांक pm8606_osc_disable(काष्ठा pm860x_chip *chip, अचिन्हित लघु client)
अणु
	पूर्णांक ret = -EIO;
	काष्ठा i2c_client *i2c = (chip->id == CHIP_PM8606) ?
		chip->client : chip->companion;

	dev_dbg(chip->dev, "%s(B): client=0x%x\n", __func__, client);
	dev_dbg(chip->dev, "%s(B): vote=0x%x status=%d\n",
			__func__, chip->osc_vote,
			chip->osc_status);

	mutex_lock(&chip->osc_lock);
	/* Update voting status */
	chip->osc_vote &= ~(client);
	/*
	 * If reference group is off and this is the last client to release
	 * - turn off
	 */
	अगर ((chip->osc_status != PM8606_REF_GP_OSC_OFF) &&
			(chip->osc_vote == REF_GP_NO_CLIENTS)) अणु
		chip->osc_status = PM8606_REF_GP_OSC_UNKNOWN;
		/* Disable Reference group Vsys */
		अगर (pm860x_set_bits(i2c, PM8606_VSYS, PM8606_VSYS_EN, 0))
			जाओ out;
		/* Disable Internal Oscillator */
		अगर (pm860x_set_bits(i2c, PM8606_MISC, PM8606_MISC_OSC_EN, 0))
			जाओ out;
		chip->osc_status = PM8606_REF_GP_OSC_OFF;
	पूर्ण
	mutex_unlock(&chip->osc_lock);

	dev_dbg(chip->dev, "%s(A): vote=0x%x status=%d ret=%d\n",
			__func__, chip->osc_vote,
			chip->osc_status, ret);
	वापस 0;
out:
	mutex_unlock(&chip->osc_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pm8606_osc_disable);

अटल व्योम device_osc_init(काष्ठा i2c_client *i2c)
अणु
	काष्ठा pm860x_chip *chip = i2c_get_clientdata(i2c);

	mutex_init(&chip->osc_lock);
	/* init portofino reference group voting and status */
	/* Disable Reference group Vsys */
	pm860x_set_bits(i2c, PM8606_VSYS, PM8606_VSYS_EN, 0);
	/* Disable Internal Oscillator */
	pm860x_set_bits(i2c, PM8606_MISC, PM8606_MISC_OSC_EN, 0);

	chip->osc_vote = REF_GP_NO_CLIENTS;
	chip->osc_status = PM8606_REF_GP_OSC_OFF;
पूर्ण

अटल व्योम device_bk_init(काष्ठा pm860x_chip *chip,
				     काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret, i;

	अगर (pdata && pdata->backlight) अणु
		अगर (pdata->num_backlights > ARRAY_SIZE(bk_devs))
			pdata->num_backlights = ARRAY_SIZE(bk_devs);
		क्रम (i = 0; i < pdata->num_backlights; i++) अणु
			bk_devs[i].platक्रमm_data = &pdata->backlight[i];
			bk_devs[i].pdata_size =
				माप(काष्ठा pm860x_backlight_pdata);
		पूर्ण
	पूर्ण
	ret = mfd_add_devices(chip->dev, 0, bk_devs,
			      ARRAY_SIZE(bk_devs), शून्य, 0, शून्य);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to add backlight subdev\n");
पूर्ण

अटल व्योम device_led_init(काष्ठा pm860x_chip *chip,
				      काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret, i;

	अगर (pdata && pdata->led) अणु
		अगर (pdata->num_leds > ARRAY_SIZE(led_devs))
			pdata->num_leds = ARRAY_SIZE(led_devs);
		क्रम (i = 0; i < pdata->num_leds; i++) अणु
			led_devs[i].platक्रमm_data = &pdata->led[i];
			led_devs[i].pdata_size =
				माप(काष्ठा pm860x_led_pdata);
		पूर्ण
	पूर्ण
	ret = mfd_add_devices(chip->dev, 0, led_devs,
			      ARRAY_SIZE(led_devs), शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to add led subdev\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम device_regulator_init(काष्ठा pm860x_chip *chip,
					    काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	अगर (pdata == शून्य)
		वापस;
	अगर (pdata->buck1) अणु
		reg_devs[0].platक्रमm_data = pdata->buck1;
		reg_devs[0].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->buck2) अणु
		reg_devs[1].platक्रमm_data = pdata->buck2;
		reg_devs[1].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->buck3) अणु
		reg_devs[2].platक्रमm_data = pdata->buck3;
		reg_devs[2].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो1) अणु
		reg_devs[3].platक्रमm_data = pdata->lकरो1;
		reg_devs[3].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो2) अणु
		reg_devs[4].platक्रमm_data = pdata->lकरो2;
		reg_devs[4].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो3) अणु
		reg_devs[5].platक्रमm_data = pdata->lकरो3;
		reg_devs[5].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो4) अणु
		reg_devs[6].platक्रमm_data = pdata->lकरो4;
		reg_devs[6].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो5) अणु
		reg_devs[7].platक्रमm_data = pdata->lकरो5;
		reg_devs[7].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो6) अणु
		reg_devs[8].platक्रमm_data = pdata->lकरो6;
		reg_devs[8].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो7) अणु
		reg_devs[9].platक्रमm_data = pdata->lकरो7;
		reg_devs[9].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो8) अणु
		reg_devs[10].platक्रमm_data = pdata->lकरो8;
		reg_devs[10].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो9) अणु
		reg_devs[11].platक्रमm_data = pdata->lकरो9;
		reg_devs[11].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो10) अणु
		reg_devs[12].platक्रमm_data = pdata->lकरो10;
		reg_devs[12].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो12) अणु
		reg_devs[13].platक्रमm_data = pdata->lकरो12;
		reg_devs[13].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो_vibrator) अणु
		reg_devs[14].platक्रमm_data = pdata->lकरो_vibrator;
		reg_devs[14].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	अगर (pdata->lकरो14) अणु
		reg_devs[15].platक्रमm_data = pdata->lकरो14;
		reg_devs[15].pdata_size = माप(काष्ठा regulator_init_data);
	पूर्ण
	ret = mfd_add_devices(chip->dev, 0, reg_devs,
			      ARRAY_SIZE(reg_devs), शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to add regulator subdev\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम device_rtc_init(काष्ठा pm860x_chip *chip,
				      काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	अगर (!pdata)
		वापस;

	rtc_devs[0].platक्रमm_data = pdata->rtc;
	rtc_devs[0].pdata_size = माप(काष्ठा pm860x_rtc_pdata);
	rtc_devs[0].num_resources = ARRAY_SIZE(rtc_resources);
	rtc_devs[0].resources = &rtc_resources[0];
	ret = mfd_add_devices(chip->dev, 0, &rtc_devs[0],
			      ARRAY_SIZE(rtc_devs), &rtc_resources[0],
			      chip->irq_base, शून्य);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to add rtc subdev\n");
पूर्ण

अटल व्योम device_touch_init(काष्ठा pm860x_chip *chip,
					काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	अगर (pdata == शून्य)
		वापस;

	touch_devs[0].platक्रमm_data = pdata->touch;
	touch_devs[0].pdata_size = माप(काष्ठा pm860x_touch_pdata);
	touch_devs[0].num_resources = ARRAY_SIZE(touch_resources);
	touch_devs[0].resources = &touch_resources[0];
	ret = mfd_add_devices(chip->dev, 0, &touch_devs[0],
			      ARRAY_SIZE(touch_devs), &touch_resources[0],
			      chip->irq_base, शून्य);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to add touch subdev\n");
पूर्ण

अटल व्योम device_घातer_init(काष्ठा pm860x_chip *chip,
					काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	अगर (pdata == शून्य)
		वापस;

	घातer_devs[0].platक्रमm_data = pdata->घातer;
	घातer_devs[0].pdata_size = माप(काष्ठा pm860x_घातer_pdata);
	घातer_devs[0].num_resources = ARRAY_SIZE(battery_resources);
	घातer_devs[0].resources = &battery_resources[0],
	ret = mfd_add_devices(chip->dev, 0, &घातer_devs[0], 1,
			      &battery_resources[0], chip->irq_base, शून्य);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to add battery subdev\n");

	घातer_devs[1].platक्रमm_data = pdata->घातer;
	घातer_devs[1].pdata_size = माप(काष्ठा pm860x_घातer_pdata);
	घातer_devs[1].num_resources = ARRAY_SIZE(अक्षरger_resources);
	घातer_devs[1].resources = &अक्षरger_resources[0],
	ret = mfd_add_devices(chip->dev, 0, &घातer_devs[1], 1,
			      &अक्षरger_resources[0], chip->irq_base, शून्य);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to add charger subdev\n");

	घातer_devs[2].platक्रमm_data = &preg_init_data;
	घातer_devs[2].pdata_size = माप(काष्ठा regulator_init_data);
	ret = mfd_add_devices(chip->dev, 0, &घातer_devs[2], 1,
			      शून्य, chip->irq_base, शून्य);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to add preg subdev\n");

	अगर (pdata->chg_desc) अणु
		pdata->chg_desc->अक्षरger_regulators =
			&chg_desc_regulator_data[0];
		pdata->chg_desc->num_अक्षरger_regulators	=
			ARRAY_SIZE(chg_desc_regulator_data),
		घातer_devs[3].platक्रमm_data = pdata->chg_desc;
		घातer_devs[3].pdata_size = माप(*pdata->chg_desc);
		ret = mfd_add_devices(chip->dev, 0, &घातer_devs[3], 1,
				      शून्य, chip->irq_base, शून्य);
		अगर (ret < 0)
			dev_err(chip->dev, "Failed to add chg-manager subdev\n");
	पूर्ण
पूर्ण

अटल व्योम device_onkey_init(काष्ठा pm860x_chip *chip,
					काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	onkey_devs[0].num_resources = ARRAY_SIZE(onkey_resources);
	onkey_devs[0].resources = &onkey_resources[0],
	ret = mfd_add_devices(chip->dev, 0, &onkey_devs[0],
			      ARRAY_SIZE(onkey_devs), &onkey_resources[0],
			      chip->irq_base, शून्य);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to add onkey subdev\n");
पूर्ण

अटल व्योम device_codec_init(काष्ठा pm860x_chip *chip,
					काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	codec_devs[0].num_resources = ARRAY_SIZE(codec_resources);
	codec_devs[0].resources = &codec_resources[0],
	ret = mfd_add_devices(chip->dev, 0, &codec_devs[0],
			      ARRAY_SIZE(codec_devs), &codec_resources[0], 0,
			      शून्य);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to add codec subdev\n");
पूर्ण

अटल व्योम device_8607_init(काष्ठा pm860x_chip *chip,
				       काष्ठा i2c_client *i2c,
				       काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक data, ret;

	ret = pm860x_reg_पढ़ो(i2c, PM8607_CHIP_ID);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to read CHIP ID: %d\n", ret);
		जाओ out;
	पूर्ण
	चयन (ret & PM8607_VERSION_MASK) अणु
	हाल 0x40:
	हाल 0x50:
		dev_info(chip->dev, "Marvell 88PM8607 (ID: %02x) detected\n",
			 ret);
		अवरोध;
	शेष:
		dev_err(chip->dev,
			"Failed to detect Marvell 88PM8607. Chip ID: %02x\n",
			ret);
		जाओ out;
	पूर्ण

	ret = pm860x_reg_पढ़ो(i2c, PM8607_BUCK3);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to read BUCK3 register: %d\n", ret);
		जाओ out;
	पूर्ण
	अगर (ret & PM8607_BUCK3_DOUBLE)
		chip->buck3_द्विगुन = 1;

	ret = pm860x_reg_पढ़ो(i2c, PM8607_B0_MISC1);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to read MISC1 register: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (pdata && (pdata->i2c_port == PI2C_PORT))
		data = PM8607_B0_MISC1_PI2C;
	अन्यथा
		data = 0;
	ret = pm860x_set_bits(i2c, PM8607_B0_MISC1, PM8607_B0_MISC1_PI2C, data);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to access MISC1:%d\n", ret);
		जाओ out;
	पूर्ण

	ret = device_irq_init(chip, pdata);
	अगर (ret < 0)
		जाओ out;

	device_regulator_init(chip, pdata);
	device_rtc_init(chip, pdata);
	device_onkey_init(chip, pdata);
	device_touch_init(chip, pdata);
	device_घातer_init(chip, pdata);
	device_codec_init(chip, pdata);
out:
	वापस;
पूर्ण

अटल व्योम device_8606_init(काष्ठा pm860x_chip *chip,
				       काष्ठा i2c_client *i2c,
				       काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	device_osc_init(i2c);
	device_bk_init(chip, pdata);
	device_led_init(chip, pdata);
पूर्ण

अटल पूर्णांक pm860x_device_init(काष्ठा pm860x_chip *chip,
					काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	chip->core_irq = 0;

	चयन (chip->id) अणु
	हाल CHIP_PM8606:
		device_8606_init(chip, chip->client, pdata);
		अवरोध;
	हाल CHIP_PM8607:
		device_8607_init(chip, chip->client, pdata);
		अवरोध;
	पूर्ण

	अगर (chip->companion) अणु
		चयन (chip->id) अणु
		हाल CHIP_PM8607:
			device_8606_init(chip, chip->companion, pdata);
			अवरोध;
		हाल CHIP_PM8606:
			device_8607_init(chip, chip->companion, pdata);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pm860x_device_निकास(काष्ठा pm860x_chip *chip)
अणु
	device_irq_निकास(chip);
	mfd_हटाओ_devices(chip->dev);
पूर्ण

अटल पूर्णांक verअगरy_addr(काष्ठा i2c_client *i2c)
अणु
	अचिन्हित लघु addr_8607[] = अणु0x30, 0x34पूर्ण;
	अचिन्हित लघु addr_8606[] = अणु0x10, 0x11पूर्ण;
	पूर्णांक size, i;

	अगर (i2c == शून्य)
		वापस 0;
	size = ARRAY_SIZE(addr_8606);
	क्रम (i = 0; i < size; i++) अणु
		अगर (i2c->addr == *(addr_8606 + i))
			वापस CHIP_PM8606;
	पूर्ण
	size = ARRAY_SIZE(addr_8607);
	क्रम (i = 0; i < size; i++) अणु
		अगर (i2c->addr == *(addr_8607 + i))
			वापस CHIP_PM8607;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config pm860x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक pm860x_dt_init(काष्ठा device_node *np,
				    काष्ठा device *dev,
				    काष्ठा pm860x_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	अगर (of_get_property(np, "marvell,88pm860x-irq-read-clr", शून्य))
		pdata->irq_mode = 1;
	ret = of_property_पढ़ो_u32(np, "marvell,88pm860x-slave-addr",
				   &pdata->companion_addr);
	अगर (ret) अणु
		dev_err(dev,
			"Not found \"marvell,88pm860x-slave-addr\" property\n");
		pdata->companion_addr = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा pm860x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा device_node *node = client->dev.of_node;
	काष्ठा pm860x_chip *chip;
	पूर्णांक ret;

	अगर (node && !pdata) अणु
		/* parse DT to get platक्रमm data */
		pdata = devm_kzalloc(&client->dev,
				     माप(काष्ठा pm860x_platक्रमm_data),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;
		ret = pm860x_dt_init(node, &client->dev, pdata);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (!pdata) अणु
		pr_info("No platform data in %s!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	chip = devm_kzalloc(&client->dev,
			    माप(काष्ठा pm860x_chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	chip->id = verअगरy_addr(client);
	chip->regmap = devm_regmap_init_i2c(client, &pm860x_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		ret = PTR_ERR(chip->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
				ret);
		वापस ret;
	पूर्ण
	chip->client = client;
	i2c_set_clientdata(client, chip);
	chip->dev = &client->dev;
	dev_set_drvdata(chip->dev, chip);

	/*
	 * Both client and companion client shares same platक्रमm driver.
	 * Driver distinguishes them by pdata->companion_addr.
	 * pdata->companion_addr is only asचिन्हित अगर companion chip exists.
	 * At the same समय, the companion_addr shouldn't equal to client
	 * address.
	 */
	अगर (pdata->companion_addr && (pdata->companion_addr != client->addr)) अणु
		chip->companion_addr = pdata->companion_addr;
		chip->companion = i2c_new_dummy_device(chip->client->adapter,
						chip->companion_addr);
		अगर (IS_ERR(chip->companion)) अणु
			dev_err(&client->dev,
				"Failed to allocate I2C companion device\n");
			वापस PTR_ERR(chip->companion);
		पूर्ण
		chip->regmap_companion = regmap_init_i2c(chip->companion,
							&pm860x_regmap_config);
		अगर (IS_ERR(chip->regmap_companion)) अणु
			ret = PTR_ERR(chip->regmap_companion);
			dev_err(&chip->companion->dev,
				"Failed to allocate register map: %d\n", ret);
			i2c_unरेजिस्टर_device(chip->companion);
			वापस ret;
		पूर्ण
		i2c_set_clientdata(chip->companion, chip);
	पूर्ण

	pm860x_device_init(chip, pdata);
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pm860x_chip *chip = i2c_get_clientdata(client);

	pm860x_device_निकास(chip);
	अगर (chip->companion) अणु
		regmap_निकास(chip->regmap_companion);
		i2c_unरेजिस्टर_device(chip->companion);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pm860x_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pm860x_chip *chip = i2c_get_clientdata(client);

	अगर (device_may_wakeup(dev) && chip->wakeup_flag)
		enable_irq_wake(chip->core_irq);
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pm860x_chip *chip = i2c_get_clientdata(client);

	अगर (device_may_wakeup(dev) && chip->wakeup_flag)
		disable_irq_wake(chip->core_irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pm860x_pm_ops, pm860x_suspend, pm860x_resume);

अटल स्थिर काष्ठा i2c_device_id pm860x_id_table[] = अणु
	अणु "88PM860x", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pm860x_id_table);

अटल स्थिर काष्ठा of_device_id pm860x_dt_ids[] = अणु
	अणु .compatible = "marvell,88pm860x", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pm860x_dt_ids);

अटल काष्ठा i2c_driver pm860x_driver = अणु
	.driver	= अणु
		.name	= "88PM860x",
		.pm     = &pm860x_pm_ops,
		.of_match_table	= pm860x_dt_ids,
	पूर्ण,
	.probe_new	= pm860x_probe,
	.हटाओ		= pm860x_हटाओ,
	.id_table	= pm860x_id_table,
पूर्ण;

अटल पूर्णांक __init pm860x_i2c_init(व्योम)
अणु
	पूर्णांक ret;

	ret = i2c_add_driver(&pm860x_driver);
	अगर (ret != 0)
		pr_err("Failed to register 88PM860x I2C driver: %d\n", ret);
	वापस ret;
पूर्ण
subsys_initcall(pm860x_i2c_init);

अटल व्योम __निकास pm860x_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&pm860x_driver);
पूर्ण
module_निकास(pm860x_i2c_निकास);

MODULE_DESCRIPTION("PMIC Driver for Marvell 88PM860x");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
