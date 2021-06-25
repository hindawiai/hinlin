<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// TI LP50XX LED chip family driver
// Copyright (C) 2018-20 Texas Instruments Incorporated - https://www.ti.com/

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <uapi/linux/uleds.h>

#समावेश <linux/led-class-multicolor.h>

#समावेश "leds.h"

#घोषणा LP50XX_DEV_CFG0		0x00
#घोषणा LP50XX_DEV_CFG1		0x01
#घोषणा LP50XX_LED_CFG0		0x02

/* LP5009 and LP5012 रेजिस्टरs */
#घोषणा LP5012_BNK_BRT		0x03
#घोषणा LP5012_BNKA_CLR		0x04
#घोषणा LP5012_BNKB_CLR		0x05
#घोषणा LP5012_BNKC_CLR		0x06
#घोषणा LP5012_LED0_BRT		0x07
#घोषणा LP5012_OUT0_CLR		0x0b
#घोषणा LP5012_RESET		0x17

/* LP5018 and LP5024 रेजिस्टरs */
#घोषणा LP5024_BNK_BRT		0x03
#घोषणा LP5024_BNKA_CLR		0x04
#घोषणा LP5024_BNKB_CLR		0x05
#घोषणा LP5024_BNKC_CLR		0x06
#घोषणा LP5024_LED0_BRT		0x07
#घोषणा LP5024_OUT0_CLR		0x0f
#घोषणा LP5024_RESET		0x27

/* LP5030 and LP5036 रेजिस्टरs */
#घोषणा LP5036_LED_CFG1		0x03
#घोषणा LP5036_BNK_BRT		0x04
#घोषणा LP5036_BNKA_CLR		0x05
#घोषणा LP5036_BNKB_CLR		0x06
#घोषणा LP5036_BNKC_CLR		0x07
#घोषणा LP5036_LED0_BRT		0x08
#घोषणा LP5036_OUT0_CLR		0x14
#घोषणा LP5036_RESET		0x38

#घोषणा LP50XX_SW_RESET		0xff
#घोषणा LP50XX_CHIP_EN		BIT(6)

/* There are 3 LED outमाला_दो per bank */
#घोषणा LP50XX_LEDS_PER_MODULE	3

#घोषणा LP5009_MAX_LED_MODULES	2
#घोषणा LP5012_MAX_LED_MODULES	4
#घोषणा LP5018_MAX_LED_MODULES	6
#घोषणा LP5024_MAX_LED_MODULES	8
#घोषणा LP5030_MAX_LED_MODULES	10
#घोषणा LP5036_MAX_LED_MODULES	12

अटल स्थिर काष्ठा reg_शेष lp5012_reg_defs[] = अणु
	अणुLP50XX_DEV_CFG0, 0x0पूर्ण,
	अणुLP50XX_DEV_CFG1, 0x3cपूर्ण,
	अणुLP50XX_LED_CFG0, 0x0पूर्ण,
	अणुLP5012_BNK_BRT, 0xffपूर्ण,
	अणुLP5012_BNKA_CLR, 0x0fपूर्ण,
	अणुLP5012_BNKB_CLR, 0x0fपूर्ण,
	अणुLP5012_BNKC_CLR, 0x0fपूर्ण,
	अणुLP5012_LED0_BRT, 0x0fपूर्ण,
	/* LEDX_BRT रेजिस्टरs are all 0xff क्रम शेषs */
	अणु0x08, 0xffपूर्ण, अणु0x09, 0xffपूर्ण, अणु0x0a, 0xffपूर्ण,
	अणुLP5012_OUT0_CLR, 0x0fपूर्ण,
	/* OUTX_CLR रेजिस्टरs are all 0x0 क्रम शेषs */
	अणु0x0c, 0x00पूर्ण, अणु0x0d, 0x00पूर्ण, अणु0x0e, 0x00पूर्ण, अणु0x0f, 0x00पूर्ण, अणु0x10, 0x00पूर्ण,
	अणु0x11, 0x00पूर्ण, अणु0x12, 0x00पूर्ण, अणु0x13, 0x00पूर्ण, अणु0x14, 0x00पूर्ण,	अणु0x15, 0x00पूर्ण,
	अणु0x16, 0x00पूर्ण,
	अणुLP5012_RESET, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_शेष lp5024_reg_defs[] = अणु
	अणुLP50XX_DEV_CFG0, 0x0पूर्ण,
	अणुLP50XX_DEV_CFG1, 0x3cपूर्ण,
	अणुLP50XX_LED_CFG0, 0x0पूर्ण,
	अणुLP5024_BNK_BRT, 0xffपूर्ण,
	अणुLP5024_BNKA_CLR, 0x0fपूर्ण,
	अणुLP5024_BNKB_CLR, 0x0fपूर्ण,
	अणुLP5024_BNKC_CLR, 0x0fपूर्ण,
	अणुLP5024_LED0_BRT, 0x0fपूर्ण,
	/* LEDX_BRT रेजिस्टरs are all 0xff क्रम शेषs */
	अणु0x08, 0xffपूर्ण, अणु0x09, 0xffपूर्ण, अणु0x0a, 0xffपूर्ण, अणु0x0b, 0xffपूर्ण, अणु0x0c, 0xffपूर्ण,
	अणु0x0d, 0xffपूर्ण, अणु0x0e, 0xffपूर्ण,
	अणुLP5024_OUT0_CLR, 0x0fपूर्ण,
	/* OUTX_CLR रेजिस्टरs are all 0x0 क्रम शेषs */
	अणु0x10, 0x00पूर्ण, अणु0x11, 0x00पूर्ण, अणु0x12, 0x00पूर्ण, अणु0x13, 0x00पूर्ण, अणु0x14, 0x00पूर्ण,
	अणु0x15, 0x00पूर्ण, अणु0x16, 0x00पूर्ण, अणु0x17, 0x00पूर्ण, अणु0x18, 0x00पूर्ण, अणु0x19, 0x00पूर्ण,
	अणु0x1a, 0x00पूर्ण, अणु0x1b, 0x00पूर्ण, अणु0x1c, 0x00पूर्ण, अणु0x1d, 0x00पूर्ण, अणु0x1e, 0x00पूर्ण,
	अणु0x1f, 0x00पूर्ण, अणु0x20, 0x00पूर्ण, अणु0x21, 0x00पूर्ण, अणु0x22, 0x00पूर्ण, अणु0x23, 0x00पूर्ण,
	अणु0x24, 0x00पूर्ण, अणु0x25, 0x00पूर्ण, अणु0x26, 0x00पूर्ण,
	अणुLP5024_RESET, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_शेष lp5036_reg_defs[] = अणु
	अणुLP50XX_DEV_CFG0, 0x0पूर्ण,
	अणुLP50XX_DEV_CFG1, 0x3cपूर्ण,
	अणुLP50XX_LED_CFG0, 0x0पूर्ण,
	अणुLP5036_LED_CFG1, 0x0पूर्ण,
	अणुLP5036_BNK_BRT, 0xffपूर्ण,
	अणुLP5036_BNKA_CLR, 0x0fपूर्ण,
	अणुLP5036_BNKB_CLR, 0x0fपूर्ण,
	अणुLP5036_BNKC_CLR, 0x0fपूर्ण,
	अणुLP5036_LED0_BRT, 0x0fपूर्ण,
	/* LEDX_BRT रेजिस्टरs are all 0xff क्रम शेषs */
	अणु0x08, 0xffपूर्ण, अणु0x09, 0xffपूर्ण, अणु0x0a, 0xffपूर्ण, अणु0x0b, 0xffपूर्ण, अणु0x0c, 0xffपूर्ण,
	अणु0x0d, 0xffपूर्ण, अणु0x0e, 0xffपूर्ण, अणु0x0f, 0xffपूर्ण, अणु0x10, 0xffपूर्ण, अणु0x11, 0xffपूर्ण,
	अणु0x12, 0xffपूर्ण, अणु0x13, 0xffपूर्ण,
	अणुLP5036_OUT0_CLR, 0x0fपूर्ण,
	/* OUTX_CLR रेजिस्टरs are all 0x0 क्रम शेषs */
	अणु0x15, 0x00पूर्ण, अणु0x16, 0x00पूर्ण, अणु0x17, 0x00पूर्ण, अणु0x18, 0x00पूर्ण, अणु0x19, 0x00पूर्ण,
	अणु0x1a, 0x00पूर्ण, अणु0x1b, 0x00पूर्ण, अणु0x1c, 0x00पूर्ण, अणु0x1d, 0x00पूर्ण, अणु0x1e, 0x00पूर्ण,
	अणु0x1f, 0x00पूर्ण, अणु0x20, 0x00पूर्ण, अणु0x21, 0x00पूर्ण, अणु0x22, 0x00पूर्ण, अणु0x23, 0x00पूर्ण,
	अणु0x24, 0x00पूर्ण, अणु0x25, 0x00पूर्ण, अणु0x26, 0x00पूर्ण, अणु0x27, 0x00पूर्ण, अणु0x28, 0x00पूर्ण,
	अणु0x29, 0x00पूर्ण, अणु0x2a, 0x00पूर्ण, अणु0x2b, 0x00पूर्ण, अणु0x2c, 0x00पूर्ण, अणु0x2d, 0x00पूर्ण,
	अणु0x2e, 0x00पूर्ण, अणु0x2f, 0x00पूर्ण, अणु0x30, 0x00पूर्ण, अणु0x31, 0x00पूर्ण, अणु0x32, 0x00पूर्ण,
	अणु0x33, 0x00पूर्ण, अणु0x34, 0x00पूर्ण, अणु0x35, 0x00पूर्ण, अणु0x36, 0x00पूर्ण, अणु0x37, 0x00पूर्ण,
	अणुLP5036_RESET, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_config lp5012_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LP5012_RESET,
	.reg_शेषs = lp5012_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(lp5012_reg_defs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lp5024_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LP5024_RESET,
	.reg_शेषs = lp5024_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(lp5024_reg_defs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lp5036_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LP5036_RESET,
	.reg_शेषs = lp5036_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(lp5036_reg_defs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

क्रमागत lp50xx_model अणु
	LP5009,
	LP5012,
	LP5018,
	LP5024,
	LP5030,
	LP5036,
पूर्ण;

/**
 * काष्ठा lp50xx_chip_info -
 * @lp50xx_regmap_config: regmap रेजिस्टर configuration
 * @model_id: LED device model
 * @max_modules: total number of supported LED modules
 * @num_leds: number of LED outमाला_दो available on the device
 * @led_brightness0_reg: first brightness रेजिस्टर of the device
 * @mix_out0_reg: first color mix रेजिस्टर of the device
 * @bank_brt_reg: bank brightness रेजिस्टर
 * @bank_mix_reg: color mix रेजिस्टर
 * @reset_reg: device reset रेजिस्टर
 */
काष्ठा lp50xx_chip_info अणु
	स्थिर काष्ठा regmap_config *lp50xx_regmap_config;
	पूर्णांक model_id;
	u8 max_modules;
	u8 num_leds;
	u8 led_brightness0_reg;
	u8 mix_out0_reg;
	u8 bank_brt_reg;
	u8 bank_mix_reg;
	u8 reset_reg;
पूर्ण;

अटल स्थिर काष्ठा lp50xx_chip_info lp50xx_chip_info_tbl[] = अणु
	[LP5009] = अणु
		.model_id = LP5009,
		.max_modules = LP5009_MAX_LED_MODULES,
		.num_leds = LP5009_MAX_LED_MODULES * LP50XX_LEDS_PER_MODULE,
		.led_brightness0_reg = LP5012_LED0_BRT,
		.mix_out0_reg = LP5012_OUT0_CLR,
		.bank_brt_reg = LP5012_BNK_BRT,
		.bank_mix_reg = LP5012_BNKA_CLR,
		.reset_reg = LP5012_RESET,
		.lp50xx_regmap_config = &lp5012_regmap_config,
	पूर्ण,
	[LP5012] = अणु
		.model_id = LP5012,
		.max_modules = LP5012_MAX_LED_MODULES,
		.num_leds = LP5012_MAX_LED_MODULES * LP50XX_LEDS_PER_MODULE,
		.led_brightness0_reg = LP5012_LED0_BRT,
		.mix_out0_reg = LP5012_OUT0_CLR,
		.bank_brt_reg = LP5012_BNK_BRT,
		.bank_mix_reg = LP5012_BNKA_CLR,
		.reset_reg = LP5012_RESET,
		.lp50xx_regmap_config = &lp5012_regmap_config,
	पूर्ण,
	[LP5018] = अणु
		.model_id = LP5018,
		.max_modules = LP5018_MAX_LED_MODULES,
		.num_leds = LP5018_MAX_LED_MODULES * LP50XX_LEDS_PER_MODULE,
		.led_brightness0_reg = LP5024_LED0_BRT,
		.mix_out0_reg = LP5024_OUT0_CLR,
		.bank_brt_reg = LP5024_BNK_BRT,
		.bank_mix_reg = LP5024_BNKA_CLR,
		.reset_reg = LP5024_RESET,
		.lp50xx_regmap_config = &lp5024_regmap_config,
	पूर्ण,
	[LP5024] = अणु
		.model_id = LP5024,
		.max_modules = LP5024_MAX_LED_MODULES,
		.num_leds = LP5024_MAX_LED_MODULES * LP50XX_LEDS_PER_MODULE,
		.led_brightness0_reg = LP5024_LED0_BRT,
		.mix_out0_reg = LP5024_OUT0_CLR,
		.bank_brt_reg = LP5024_BNK_BRT,
		.bank_mix_reg = LP5024_BNKA_CLR,
		.reset_reg = LP5024_RESET,
		.lp50xx_regmap_config = &lp5024_regmap_config,
	पूर्ण,
	[LP5030] = अणु
		.model_id = LP5030,
		.max_modules = LP5030_MAX_LED_MODULES,
		.num_leds = LP5030_MAX_LED_MODULES * LP50XX_LEDS_PER_MODULE,
		.led_brightness0_reg = LP5036_LED0_BRT,
		.mix_out0_reg = LP5036_OUT0_CLR,
		.bank_brt_reg = LP5036_BNK_BRT,
		.bank_mix_reg = LP5036_BNKA_CLR,
		.reset_reg = LP5036_RESET,
		.lp50xx_regmap_config = &lp5036_regmap_config,
	पूर्ण,
	[LP5036] = अणु
		.model_id = LP5036,
		.max_modules = LP5036_MAX_LED_MODULES,
		.num_leds = LP5036_MAX_LED_MODULES * LP50XX_LEDS_PER_MODULE,
		.led_brightness0_reg = LP5036_LED0_BRT,
		.mix_out0_reg = LP5036_OUT0_CLR,
		.bank_brt_reg = LP5036_BNK_BRT,
		.bank_mix_reg = LP5036_BNKA_CLR,
		.reset_reg = LP5036_RESET,
		.lp50xx_regmap_config = &lp5036_regmap_config,
	पूर्ण,
पूर्ण;

काष्ठा lp50xx_led अणु
	काष्ठा led_classdev_mc mc_cdev;
	काष्ठा lp50xx *priv;
	अचिन्हित दीर्घ bank_modules;
	पूर्णांक led_पूर्णांकensity[LP50XX_LEDS_PER_MODULE];
	u8 ctrl_bank_enabled;
	पूर्णांक led_number;
पूर्ण;

/**
 * काष्ठा lp50xx -
 * @enable_gpio: hardware enable gpio
 * @regulator: LED supply regulator poपूर्णांकer
 * @client: poपूर्णांकer to the I2C client
 * @regmap: device रेजिस्टर map
 * @dev: poपूर्णांकer to the devices device काष्ठा
 * @lock: lock क्रम पढ़ोing/writing the device
 * @chip_info: chip specअगरic inक्रमmation (ie num_leds)
 * @num_of_banked_leds: holds the number of banked LEDs
 * @leds: array of LED strings
 */
काष्ठा lp50xx अणु
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regulator *regulator;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा mutex lock;
	स्थिर काष्ठा lp50xx_chip_info *chip_info;
	पूर्णांक num_of_banked_leds;

	/* This needs to be at the end of the काष्ठा */
	काष्ठा lp50xx_led leds[];
पूर्ण;

अटल काष्ठा lp50xx_led *mcled_cdev_to_led(काष्ठा led_classdev_mc *mc_cdev)
अणु
	वापस container_of(mc_cdev, काष्ठा lp50xx_led, mc_cdev);
पूर्ण

अटल पूर्णांक lp50xx_brightness_set(काष्ठा led_classdev *cdev,
			     क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_mc *mc_dev = lcdev_to_mccdev(cdev);
	काष्ठा lp50xx_led *led = mcled_cdev_to_led(mc_dev);
	स्थिर काष्ठा lp50xx_chip_info *led_chip = led->priv->chip_info;
	u8 led_offset, reg_val;
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&led->priv->lock);
	अगर (led->ctrl_bank_enabled)
		reg_val = led_chip->bank_brt_reg;
	अन्यथा
		reg_val = led_chip->led_brightness0_reg +
			  led->led_number;

	ret = regmap_ग_लिखो(led->priv->regmap, reg_val, brightness);
	अगर (ret) अणु
		dev_err(led->priv->dev,
			"Cannot write brightness value %d\n", ret);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < led->mc_cdev.num_colors; i++) अणु
		अगर (led->ctrl_bank_enabled) अणु
			reg_val = led_chip->bank_mix_reg + i;
		पूर्ण अन्यथा अणु
			led_offset = (led->led_number * 3) + i;
			reg_val = led_chip->mix_out0_reg + led_offset;
		पूर्ण

		ret = regmap_ग_लिखो(led->priv->regmap, reg_val,
				   mc_dev->subled_info[i].पूर्णांकensity);
		अगर (ret) अणु
			dev_err(led->priv->dev,
				"Cannot write intensity value %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&led->priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lp50xx_set_banks(काष्ठा lp50xx *priv, u32 led_banks[])
अणु
	u8 led_config_lo, led_config_hi;
	u32 bank_enable_mask = 0;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < priv->chip_info->max_modules; i++) अणु
		अगर (led_banks[i])
			bank_enable_mask |= (1 << led_banks[i]);
	पूर्ण

	led_config_lo = bank_enable_mask;
	led_config_hi = bank_enable_mask >> 8;

	ret = regmap_ग_लिखो(priv->regmap, LP50XX_LED_CFG0, led_config_lo);
	अगर (ret)
		वापस ret;

	अगर (priv->chip_info->model_id >= LP5030)
		ret = regmap_ग_लिखो(priv->regmap, LP5036_LED_CFG1, led_config_hi);

	वापस ret;
पूर्ण

अटल पूर्णांक lp50xx_reset(काष्ठा lp50xx *priv)
अणु
	वापस regmap_ग_लिखो(priv->regmap, priv->chip_info->reset_reg, LP50XX_SW_RESET);
पूर्ण

अटल पूर्णांक lp50xx_enable_disable(काष्ठा lp50xx *priv, पूर्णांक enable_disable)
अणु
	पूर्णांक ret;

	ret = gpiod_direction_output(priv->enable_gpio, enable_disable);
	अगर (ret)
		वापस ret;

	अगर (enable_disable)
		वापस regmap_ग_लिखो(priv->regmap, LP50XX_DEV_CFG0, LP50XX_CHIP_EN);
	अन्यथा
		वापस regmap_ग_लिखो(priv->regmap, LP50XX_DEV_CFG0, 0);

पूर्ण

अटल पूर्णांक lp50xx_probe_leds(काष्ठा fwnode_handle *child, काष्ठा lp50xx *priv,
			     काष्ठा lp50xx_led *led, पूर्णांक num_leds)
अणु
	u32 led_banks[LP5036_MAX_LED_MODULES] = अणु0पूर्ण;
	पूर्णांक led_number;
	पूर्णांक ret;

	अगर (num_leds > 1) अणु
		अगर (num_leds > priv->chip_info->max_modules) अणु
			dev_err(priv->dev, "reg property is invalid\n");
			वापस -EINVAL;
		पूर्ण

		priv->num_of_banked_leds = num_leds;

		ret = fwnode_property_पढ़ो_u32_array(child, "reg", led_banks, num_leds);
		अगर (ret) अणु
			dev_err(priv->dev, "reg property is missing\n");
			वापस ret;
		पूर्ण

		ret = lp50xx_set_banks(priv, led_banks);
		अगर (ret) अणु
			dev_err(priv->dev, "Cannot setup banked LEDs\n");
			वापस ret;
		पूर्ण

		led->ctrl_bank_enabled = 1;
	पूर्ण अन्यथा अणु
		ret = fwnode_property_पढ़ो_u32(child, "reg", &led_number);
		अगर (ret) अणु
			dev_err(priv->dev, "led reg property missing\n");
			वापस ret;
		पूर्ण

		अगर (led_number > priv->chip_info->num_leds) अणु
			dev_err(priv->dev, "led-sources property is invalid\n");
			वापस -EINVAL;
		पूर्ण

		led->led_number = led_number;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp50xx_probe_dt(काष्ठा lp50xx *priv)
अणु
	काष्ठा fwnode_handle *child = शून्य;
	काष्ठा fwnode_handle *led_node = शून्य;
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा led_classdev *led_cdev;
	काष्ठा mc_subled *mc_led_info;
	काष्ठा lp50xx_led *led;
	पूर्णांक ret = -EINVAL;
	पूर्णांक num_colors;
	u32 color_id;
	पूर्णांक i = 0;

	priv->enable_gpio = devm_gpiod_get_optional(priv->dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->enable_gpio))
		वापस dev_err_probe(priv->dev, PTR_ERR(priv->enable_gpio),
				     "Failed to get enable GPIO\n");

	priv->regulator = devm_regulator_get(priv->dev, "vled");
	अगर (IS_ERR(priv->regulator))
		priv->regulator = शून्य;

	device_क्रम_each_child_node(priv->dev, child) अणु
		led = &priv->leds[i];
		ret = fwnode_property_count_u32(child, "reg");
		अगर (ret < 0) अणु
			dev_err(priv->dev, "reg property is invalid\n");
			जाओ child_out;
		पूर्ण

		ret = lp50xx_probe_leds(child, priv, led, ret);
		अगर (ret)
			जाओ child_out;

		init_data.fwnode = child;
		num_colors = 0;

		/*
		 * There are only 3 LEDs per module otherwise they should be
		 * banked which also is presented as 3 LEDs.
		 */
		mc_led_info = devm_kसुस्मृति(priv->dev, LP50XX_LEDS_PER_MODULE,
					   माप(*mc_led_info), GFP_KERNEL);
		अगर (!mc_led_info) अणु
			ret = -ENOMEM;
			जाओ child_out;
		पूर्ण

		fwnode_क्रम_each_child_node(child, led_node) अणु
			ret = fwnode_property_पढ़ो_u32(led_node, "color",
						       &color_id);
			अगर (ret) अणु
				dev_err(priv->dev, "Cannot read color\n");
				जाओ child_out;
			पूर्ण

			mc_led_info[num_colors].color_index = color_id;
			num_colors++;
		पूर्ण

		led->priv = priv;
		led->mc_cdev.num_colors = num_colors;
		led->mc_cdev.subled_info = mc_led_info;
		led_cdev = &led->mc_cdev.led_cdev;
		led_cdev->brightness_set_blocking = lp50xx_brightness_set;

		ret = devm_led_classdev_multicolor_रेजिस्टर_ext(priv->dev,
						       &led->mc_cdev,
						       &init_data);
		अगर (ret) अणु
			dev_err(priv->dev, "led register err: %d\n", ret);
			जाओ child_out;
		पूर्ण
		i++;
		fwnode_handle_put(child);
	पूर्ण

	वापस 0;

child_out:
	fwnode_handle_put(child);
	वापस ret;
पूर्ण

अटल पूर्णांक lp50xx_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा lp50xx *led;
	पूर्णांक count;
	पूर्णांक ret;

	count = device_get_child_node_count(&client->dev);
	अगर (!count) अणु
		dev_err(&client->dev, "LEDs are not defined in device tree!");
		वापस -ENODEV;
	पूर्ण

	led = devm_kzalloc(&client->dev, काष्ठा_size(led, leds, count),
			   GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	mutex_init(&led->lock);
	led->client = client;
	led->dev = &client->dev;
	led->chip_info = device_get_match_data(&client->dev);
	i2c_set_clientdata(client, led);
	led->regmap = devm_regmap_init_i2c(client,
					led->chip_info->lp50xx_regmap_config);
	अगर (IS_ERR(led->regmap)) अणु
		ret = PTR_ERR(led->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = lp50xx_reset(led);
	अगर (ret)
		वापस ret;

	ret = lp50xx_enable_disable(led, 1);
	अगर (ret)
		वापस ret;

	वापस lp50xx_probe_dt(led);
पूर्ण

अटल पूर्णांक lp50xx_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lp50xx *led = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = lp50xx_enable_disable(led, 0);
	अगर (ret) अणु
		dev_err(led->dev, "Failed to disable chip\n");
		वापस ret;
	पूर्ण

	अगर (led->regulator) अणु
		ret = regulator_disable(led->regulator);
		अगर (ret)
			dev_err(led->dev, "Failed to disable regulator\n");
	पूर्ण

	mutex_destroy(&led->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp50xx_id[] = अणु
	अणु "lp5009", (kernel_uदीर्घ_t)&lp50xx_chip_info_tbl[LP5009] पूर्ण,
	अणु "lp5012", (kernel_uदीर्घ_t)&lp50xx_chip_info_tbl[LP5012] पूर्ण,
	अणु "lp5018", (kernel_uदीर्घ_t)&lp50xx_chip_info_tbl[LP5018] पूर्ण,
	अणु "lp5024", (kernel_uदीर्घ_t)&lp50xx_chip_info_tbl[LP5024] पूर्ण,
	अणु "lp5030", (kernel_uदीर्घ_t)&lp50xx_chip_info_tbl[LP5030] पूर्ण,
	अणु "lp5036", (kernel_uदीर्घ_t)&lp50xx_chip_info_tbl[LP5036] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp50xx_id);

अटल स्थिर काष्ठा of_device_id of_lp50xx_leds_match[] = अणु
	अणु .compatible = "ti,lp5009", .data = &lp50xx_chip_info_tbl[LP5009] पूर्ण,
	अणु .compatible = "ti,lp5012", .data = &lp50xx_chip_info_tbl[LP5012] पूर्ण,
	अणु .compatible = "ti,lp5018", .data = &lp50xx_chip_info_tbl[LP5018] पूर्ण,
	अणु .compatible = "ti,lp5024", .data = &lp50xx_chip_info_tbl[LP5024] पूर्ण,
	अणु .compatible = "ti,lp5030", .data = &lp50xx_chip_info_tbl[LP5030] पूर्ण,
	अणु .compatible = "ti,lp5036", .data = &lp50xx_chip_info_tbl[LP5036] पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lp50xx_leds_match);

अटल काष्ठा i2c_driver lp50xx_driver = अणु
	.driver = अणु
		.name	= "lp50xx",
		.of_match_table = of_lp50xx_leds_match,
	पूर्ण,
	.probe_new	= lp50xx_probe,
	.हटाओ		= lp50xx_हटाओ,
	.id_table	= lp50xx_id,
पूर्ण;
module_i2c_driver(lp50xx_driver);

MODULE_DESCRIPTION("Texas Instruments LP50XX LED driver");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
