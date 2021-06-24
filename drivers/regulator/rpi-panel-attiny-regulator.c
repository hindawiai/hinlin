<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Marek Vasut <marex@denx.de>
 *
 * Based on rpi_touchscreen.c by Eric Anholt <eric@anholt.net>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

/* I2C रेजिस्टरs of the Aपंचांगel microcontroller. */
#घोषणा REG_ID		0x80
#घोषणा REG_PORTA	0x81
#घोषणा REG_PORTA_HF	BIT(2)
#घोषणा REG_PORTA_VF	BIT(3)
#घोषणा REG_PORTB	0x82
#घोषणा REG_POWERON	0x85
#घोषणा REG_PWM		0x86

अटल स्थिर काष्ठा regmap_config attiny_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = REG_PWM,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक attiny_lcd_घातer_enable(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक data;

	regmap_ग_लिखो(rdev->regmap, REG_POWERON, 1);
	/* Wait क्रम nPWRDWN to go low to indicate घातeron is करोne. */
	regmap_पढ़ो_poll_समयout(rdev->regmap, REG_PORTB, data,
					data & BIT(0), 10, 1000000);

	/* Default to the same orientation as the बंदd source
	 * firmware used क्रम the panel.  Runसमय rotation
	 * configuration will be supported using VC4's plane
	 * orientation bits.
	 */
	regmap_ग_लिखो(rdev->regmap, REG_PORTA, BIT(2));

	वापस 0;
पूर्ण

अटल पूर्णांक attiny_lcd_घातer_disable(काष्ठा regulator_dev *rdev)
अणु
	regmap_ग_लिखो(rdev->regmap, REG_PWM, 0);
	regmap_ग_लिखो(rdev->regmap, REG_POWERON, 0);
	udelay(1);
	वापस 0;
पूर्ण

अटल पूर्णांक attiny_lcd_घातer_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, REG_POWERON, &data);
	अगर (ret < 0)
		वापस ret;

	अगर (!(data & BIT(0)))
		वापस 0;

	ret = regmap_पढ़ो(rdev->regmap, REG_PORTB, &data);
	अगर (ret < 0)
		वापस ret;

	वापस data & BIT(0);
पूर्ण

अटल स्थिर काष्ठा regulator_init_data attiny_regulator_शेष = अणु
	.स्थिरraपूर्णांकs = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops attiny_regulator_ops = अणु
	.enable = attiny_lcd_घातer_enable,
	.disable = attiny_lcd_घातer_disable,
	.is_enabled = attiny_lcd_घातer_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc attiny_regulator = अणु
	.name	= "tc358762-power",
	.ops	= &attiny_regulator_ops,
	.type	= REGULATOR_VOLTAGE,
	.owner	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक attiny_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा regmap *regmap = bl_get_data(bl);
	पूर्णांक brightness = bl->props.brightness;

	अगर (bl->props.घातer != FB_BLANK_UNBLANK ||
	    bl->props.fb_blank != FB_BLANK_UNBLANK)
		brightness = 0;

	वापस regmap_ग_लिखो(regmap, REG_PWM, brightness);
पूर्ण

अटल पूर्णांक attiny_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा regmap *regmap = bl_get_data(bl);
	पूर्णांक ret, brightness;

	ret = regmap_पढ़ो(regmap, REG_PWM, &brightness);
	अगर (ret)
		वापस ret;

	वापस brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops attiny_bl = अणु
	.update_status	= attiny_update_status,
	.get_brightness	= attiny_get_brightness,
पूर्ण;

/*
 * I2C driver पूर्णांकerface functions
 */
अटल पूर्णांक attiny_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा backlight_properties props = अणु पूर्ण;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा backlight_device *bl;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	regmap = devm_regmap_init_i2c(i2c, &attiny_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(regmap, REG_ID, &data);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read REG_ID reg: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (data) अणु
	हाल 0xde: /* ver 1 */
	हाल 0xc3: /* ver 2 */
		अवरोध;
	शेष:
		dev_err(&i2c->dev, "Unknown Atmel firmware revision: 0x%02x\n", data);
		वापस -ENODEV;
	पूर्ण

	regmap_ग_लिखो(regmap, REG_POWERON, 0);
	mdelay(1);

	config.dev = &i2c->dev;
	config.regmap = regmap;
	config.of_node = i2c->dev.of_node;
	config.init_data = &attiny_regulator_शेष;

	rdev = devm_regulator_रेजिस्टर(&i2c->dev, &attiny_regulator, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&i2c->dev, "Failed to register ATTINY regulator\n");
		वापस PTR_ERR(rdev);
	पूर्ण

	props.type = BACKLIGHT_RAW;
	props.max_brightness = 0xff;
	bl = devm_backlight_device_रेजिस्टर(&i2c->dev,
					    "7inch-touchscreen-panel-bl",
					    &i2c->dev, regmap, &attiny_bl,
					    &props);
	अगर (IS_ERR(bl))
		वापस PTR_ERR(bl);

	bl->props.brightness = 0xff;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id attiny_dt_ids[] = अणु
	अणु .compatible = "raspberrypi,7inch-touchscreen-panel-regulator" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, attiny_dt_ids);

अटल काष्ठा i2c_driver attiny_regulator_driver = अणु
	.driver = अणु
		.name = "rpi_touchscreen_attiny",
		.of_match_table = of_match_ptr(attiny_dt_ids),
	पूर्ण,
	.probe = attiny_i2c_probe,
पूर्ण;

module_i2c_driver(attiny_regulator_driver);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("Regulator device driver for Raspberry Pi 7-inch touchscreen");
MODULE_LICENSE("GPL v2");
