<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8860 4-Channel LED Driver
 *
 * Copyright (C) 2014 Texas Instruments
 *
 * Author: Dan Murphy <dmurphy@ti.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>

#घोषणा LP8860_DISP_CL1_BRT_MSB		0x00
#घोषणा LP8860_DISP_CL1_BRT_LSB		0x01
#घोषणा LP8860_DISP_CL1_CURR_MSB	0x02
#घोषणा LP8860_DISP_CL1_CURR_LSB	0x03
#घोषणा LP8860_CL2_BRT_MSB		0x04
#घोषणा LP8860_CL2_BRT_LSB		0x05
#घोषणा LP8860_CL2_CURRENT		0x06
#घोषणा LP8860_CL3_BRT_MSB		0x07
#घोषणा LP8860_CL3_BRT_LSB		0x08
#घोषणा LP8860_CL3_CURRENT		0x09
#घोषणा LP8860_CL4_BRT_MSB		0x0a
#घोषणा LP8860_CL4_BRT_LSB		0x0b
#घोषणा LP8860_CL4_CURRENT		0x0c
#घोषणा LP8860_CONFIG			0x0d
#घोषणा LP8860_STATUS			0x0e
#घोषणा LP8860_FAULT			0x0f
#घोषणा LP8860_LED_FAULT		0x10
#घोषणा LP8860_FAULT_CLEAR		0x11
#घोषणा LP8860_ID			0x12
#घोषणा LP8860_TEMP_MSB			0x13
#घोषणा LP8860_TEMP_LSB			0x14
#घोषणा LP8860_DISP_LED_CURR_MSB	0x15
#घोषणा LP8860_DISP_LED_CURR_LSB	0x16
#घोषणा LP8860_DISP_LED_PWM_MSB		0x17
#घोषणा LP8860_DISP_LED_PWM_LSB		0x18
#घोषणा LP8860_EEPROM_CNTRL		0x19
#घोषणा LP8860_EEPROM_UNLOCK		0x1a

#घोषणा LP8860_EEPROM_REG_0		0x60
#घोषणा LP8860_EEPROM_REG_1		0x61
#घोषणा LP8860_EEPROM_REG_2		0x62
#घोषणा LP8860_EEPROM_REG_3		0x63
#घोषणा LP8860_EEPROM_REG_4		0x64
#घोषणा LP8860_EEPROM_REG_5		0x65
#घोषणा LP8860_EEPROM_REG_6		0x66
#घोषणा LP8860_EEPROM_REG_7		0x67
#घोषणा LP8860_EEPROM_REG_8		0x68
#घोषणा LP8860_EEPROM_REG_9		0x69
#घोषणा LP8860_EEPROM_REG_10		0x6a
#घोषणा LP8860_EEPROM_REG_11		0x6b
#घोषणा LP8860_EEPROM_REG_12		0x6c
#घोषणा LP8860_EEPROM_REG_13		0x6d
#घोषणा LP8860_EEPROM_REG_14		0x6e
#घोषणा LP8860_EEPROM_REG_15		0x6f
#घोषणा LP8860_EEPROM_REG_16		0x70
#घोषणा LP8860_EEPROM_REG_17		0x71
#घोषणा LP8860_EEPROM_REG_18		0x72
#घोषणा LP8860_EEPROM_REG_19		0x73
#घोषणा LP8860_EEPROM_REG_20		0x74
#घोषणा LP8860_EEPROM_REG_21		0x75
#घोषणा LP8860_EEPROM_REG_22		0x76
#घोषणा LP8860_EEPROM_REG_23		0x77
#घोषणा LP8860_EEPROM_REG_24		0x78

#घोषणा LP8860_LOCK_EEPROM		0x00
#घोषणा LP8860_UNLOCK_EEPROM		0x01
#घोषणा LP8860_PROGRAM_EEPROM		0x02
#घोषणा LP8860_EEPROM_CODE_1		0x08
#घोषणा LP8860_EEPROM_CODE_2		0xba
#घोषणा LP8860_EEPROM_CODE_3		0xef

#घोषणा LP8860_CLEAR_FAULTS		0x01

#घोषणा LP8860_NAME			"lp8860"

/**
 * काष्ठा lp8860_led -
 * @lock - Lock क्रम पढ़ोing/writing the device
 * @client - Poपूर्णांकer to the I2C client
 * @led_dev - led class device poपूर्णांकer
 * @regmap - Devices रेजिस्टर map
 * @eeprom_regmap - EEPROM रेजिस्टर map
 * @enable_gpio - VDDIO/EN gpio to enable communication पूर्णांकerface
 * @regulator - LED supply regulator poपूर्णांकer
 */
काष्ठा lp8860_led अणु
	काष्ठा mutex lock;
	काष्ठा i2c_client *client;
	काष्ठा led_classdev led_dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap *eeprom_regmap;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regulator *regulator;
पूर्ण;

काष्ठा lp8860_eeprom_reg अणु
	uपूर्णांक8_t reg;
	uपूर्णांक8_t value;
पूर्ण;

अटल काष्ठा lp8860_eeprom_reg lp8860_eeprom_disp_regs[] = अणु
	अणु LP8860_EEPROM_REG_0, 0xed पूर्ण,
	अणु LP8860_EEPROM_REG_1, 0xdf पूर्ण,
	अणु LP8860_EEPROM_REG_2, 0xdc पूर्ण,
	अणु LP8860_EEPROM_REG_3, 0xf0 पूर्ण,
	अणु LP8860_EEPROM_REG_4, 0xdf पूर्ण,
	अणु LP8860_EEPROM_REG_5, 0xe5 पूर्ण,
	अणु LP8860_EEPROM_REG_6, 0xf2 पूर्ण,
	अणु LP8860_EEPROM_REG_7, 0x77 पूर्ण,
	अणु LP8860_EEPROM_REG_8, 0x77 पूर्ण,
	अणु LP8860_EEPROM_REG_9, 0x71 पूर्ण,
	अणु LP8860_EEPROM_REG_10, 0x3f पूर्ण,
	अणु LP8860_EEPROM_REG_11, 0xb7 पूर्ण,
	अणु LP8860_EEPROM_REG_12, 0x17 पूर्ण,
	अणु LP8860_EEPROM_REG_13, 0xef पूर्ण,
	अणु LP8860_EEPROM_REG_14, 0xb0 पूर्ण,
	अणु LP8860_EEPROM_REG_15, 0x87 पूर्ण,
	अणु LP8860_EEPROM_REG_16, 0xce पूर्ण,
	अणु LP8860_EEPROM_REG_17, 0x72 पूर्ण,
	अणु LP8860_EEPROM_REG_18, 0xe5 पूर्ण,
	अणु LP8860_EEPROM_REG_19, 0xdf पूर्ण,
	अणु LP8860_EEPROM_REG_20, 0x35 पूर्ण,
	अणु LP8860_EEPROM_REG_21, 0x06 पूर्ण,
	अणु LP8860_EEPROM_REG_22, 0xdc पूर्ण,
	अणु LP8860_EEPROM_REG_23, 0x88 पूर्ण,
	अणु LP8860_EEPROM_REG_24, 0x3E पूर्ण,
पूर्ण;

अटल पूर्णांक lp8860_unlock_eeprom(काष्ठा lp8860_led *led, पूर्णांक lock)
अणु
	पूर्णांक ret;

	mutex_lock(&led->lock);

	अगर (lock == LP8860_UNLOCK_EEPROM) अणु
		ret = regmap_ग_लिखो(led->regmap,
			LP8860_EEPROM_UNLOCK,
			LP8860_EEPROM_CODE_1);
		अगर (ret) अणु
			dev_err(&led->client->dev, "EEPROM Unlock failed\n");
			जाओ out;
		पूर्ण

		ret = regmap_ग_लिखो(led->regmap,
			LP8860_EEPROM_UNLOCK,
			LP8860_EEPROM_CODE_2);
		अगर (ret) अणु
			dev_err(&led->client->dev, "EEPROM Unlock failed\n");
			जाओ out;
		पूर्ण
		ret = regmap_ग_लिखो(led->regmap,
			LP8860_EEPROM_UNLOCK,
			LP8860_EEPROM_CODE_3);
		अगर (ret) अणु
			dev_err(&led->client->dev, "EEPROM Unlock failed\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(led->regmap,
			LP8860_EEPROM_UNLOCK,
			LP8860_LOCK_EEPROM);
	पूर्ण

out:
	mutex_unlock(&led->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lp8860_fault_check(काष्ठा lp8860_led *led)
अणु
	पूर्णांक ret, fault;
	अचिन्हित पूर्णांक पढ़ो_buf;

	ret = regmap_पढ़ो(led->regmap, LP8860_LED_FAULT, &पढ़ो_buf);
	अगर (ret)
		जाओ out;

	fault = पढ़ो_buf;

	ret = regmap_पढ़ो(led->regmap, LP8860_FAULT, &पढ़ो_buf);
	अगर (ret)
		जाओ out;

	fault |= पढ़ो_buf;

	/* Attempt to clear any faults */
	अगर (fault)
		ret = regmap_ग_लिखो(led->regmap, LP8860_FAULT_CLEAR,
			LP8860_CLEAR_FAULTS);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक lp8860_brightness_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness brt_val)
अणु
	काष्ठा lp8860_led *led =
			container_of(led_cdev, काष्ठा lp8860_led, led_dev);
	पूर्णांक disp_brightness = brt_val * 255;
	पूर्णांक ret;

	mutex_lock(&led->lock);

	ret = lp8860_fault_check(led);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Cannot read/clear faults\n");
		जाओ out;
	पूर्ण

	ret = regmap_ग_लिखो(led->regmap, LP8860_DISP_CL1_BRT_MSB,
			(disp_brightness & 0xff00) >> 8);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Cannot write CL1 MSB\n");
		जाओ out;
	पूर्ण

	ret = regmap_ग_लिखो(led->regmap, LP8860_DISP_CL1_BRT_LSB,
			disp_brightness & 0xff);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Cannot write CL1 LSB\n");
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&led->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lp8860_init(काष्ठा lp8860_led *led)
अणु
	अचिन्हित पूर्णांक पढ़ो_buf;
	पूर्णांक ret, i, reg_count;

	अगर (led->regulator) अणु
		ret = regulator_enable(led->regulator);
		अगर (ret) अणु
			dev_err(&led->client->dev,
				"Failed to enable regulator\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (led->enable_gpio)
		gpiod_direction_output(led->enable_gpio, 1);

	ret = lp8860_fault_check(led);
	अगर (ret)
		जाओ out;

	ret = regmap_पढ़ो(led->regmap, LP8860_STATUS, &पढ़ो_buf);
	अगर (ret)
		जाओ out;

	ret = lp8860_unlock_eeprom(led, LP8860_UNLOCK_EEPROM);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Failed unlocking EEPROM\n");
		जाओ out;
	पूर्ण

	reg_count = ARRAY_SIZE(lp8860_eeprom_disp_regs) / माप(lp8860_eeprom_disp_regs[0]);
	क्रम (i = 0; i < reg_count; i++) अणु
		ret = regmap_ग_लिखो(led->eeprom_regmap,
				lp8860_eeprom_disp_regs[i].reg,
				lp8860_eeprom_disp_regs[i].value);
		अगर (ret) अणु
			dev_err(&led->client->dev, "Failed writing EEPROM\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = lp8860_unlock_eeprom(led, LP8860_LOCK_EEPROM);
	अगर (ret)
		जाओ out;

	ret = regmap_ग_लिखो(led->regmap,
			LP8860_EEPROM_CNTRL,
			LP8860_PROGRAM_EEPROM);
	अगर (ret) अणु
		dev_err(&led->client->dev, "Failed programming EEPROM\n");
		जाओ out;
	पूर्ण

	वापस ret;

out:
	अगर (ret)
		अगर (led->enable_gpio)
			gpiod_direction_output(led->enable_gpio, 0);

	अगर (led->regulator) अणु
		ret = regulator_disable(led->regulator);
		अगर (ret)
			dev_err(&led->client->dev,
				"Failed to disable regulator\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा reg_शेष lp8860_reg_defs[] = अणु
	अणु LP8860_DISP_CL1_BRT_MSB, 0x00पूर्ण,
	अणु LP8860_DISP_CL1_BRT_LSB, 0x00पूर्ण,
	अणु LP8860_DISP_CL1_CURR_MSB, 0x00पूर्ण,
	अणु LP8860_DISP_CL1_CURR_LSB, 0x00पूर्ण,
	अणु LP8860_CL2_BRT_MSB, 0x00पूर्ण,
	अणु LP8860_CL2_BRT_LSB, 0x00पूर्ण,
	अणु LP8860_CL2_CURRENT, 0x00पूर्ण,
	अणु LP8860_CL3_BRT_MSB, 0x00पूर्ण,
	अणु LP8860_CL3_BRT_LSB, 0x00पूर्ण,
	अणु LP8860_CL3_CURRENT, 0x00पूर्ण,
	अणु LP8860_CL4_BRT_MSB, 0x00पूर्ण,
	अणु LP8860_CL4_BRT_LSB, 0x00पूर्ण,
	अणु LP8860_CL4_CURRENT, 0x00पूर्ण,
	अणु LP8860_CONFIG, 0x00पूर्ण,
	अणु LP8860_FAULT_CLEAR, 0x00पूर्ण,
	अणु LP8860_EEPROM_CNTRL, 0x80पूर्ण,
	अणु LP8860_EEPROM_UNLOCK, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lp8860_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LP8860_EEPROM_UNLOCK,
	.reg_शेषs = lp8860_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(lp8860_reg_defs),
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष lp8860_eeprom_defs[] = अणु
	अणु LP8860_EEPROM_REG_0, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_1, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_2, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_3, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_4, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_5, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_6, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_7, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_8, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_9, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_10, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_11, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_12, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_13, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_14, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_15, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_16, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_17, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_18, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_19, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_20, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_21, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_22, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_23, 0x00 पूर्ण,
	अणु LP8860_EEPROM_REG_24, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lp8860_eeprom_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LP8860_EEPROM_REG_24,
	.reg_शेषs = lp8860_eeprom_defs,
	.num_reg_शेषs = ARRAY_SIZE(lp8860_eeprom_defs),
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक lp8860_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा lp8860_led *led;
	काष्ठा device_node *np = dev_of_node(&client->dev);
	काष्ठा device_node *child_node;
	काष्ठा led_init_data init_data = अणुपूर्ण;

	led = devm_kzalloc(&client->dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	child_node = of_get_next_available_child(np, शून्य);
	अगर (!child_node)
		वापस -EINVAL;

	led->enable_gpio = devm_gpiod_get_optional(&client->dev,
						   "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(led->enable_gpio)) अणु
		ret = PTR_ERR(led->enable_gpio);
		dev_err(&client->dev, "Failed to get enable gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	led->regulator = devm_regulator_get(&client->dev, "vled");
	अगर (IS_ERR(led->regulator))
		led->regulator = शून्य;

	led->client = client;
	led->led_dev.brightness_set_blocking = lp8860_brightness_set;

	mutex_init(&led->lock);

	i2c_set_clientdata(client, led);

	led->regmap = devm_regmap_init_i2c(client, &lp8860_regmap_config);
	अगर (IS_ERR(led->regmap)) अणु
		ret = PTR_ERR(led->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	led->eeprom_regmap = devm_regmap_init_i2c(client, &lp8860_eeprom_regmap_config);
	अगर (IS_ERR(led->eeprom_regmap)) अणु
		ret = PTR_ERR(led->eeprom_regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = lp8860_init(led);
	अगर (ret)
		वापस ret;

	init_data.fwnode = of_fwnode_handle(child_node);
	init_data.devicename = LP8860_NAME;
	init_data.शेष_label = ":display_cluster";

	ret = devm_led_classdev_रेजिस्टर_ext(&client->dev, &led->led_dev,
					     &init_data);
	अगर (ret) अणु
		dev_err(&client->dev, "led register err: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp8860_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lp8860_led *led = i2c_get_clientdata(client);
	पूर्णांक ret;

	अगर (led->enable_gpio)
		gpiod_direction_output(led->enable_gpio, 0);

	अगर (led->regulator) अणु
		ret = regulator_disable(led->regulator);
		अगर (ret)
			dev_err(&led->client->dev,
				"Failed to disable regulator\n");
	पूर्ण

	mutex_destroy(&led->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp8860_id[] = अणु
	अणु "lp8860", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp8860_id);

अटल स्थिर काष्ठा of_device_id of_lp8860_leds_match[] = अणु
	अणु .compatible = "ti,lp8860", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lp8860_leds_match);

अटल काष्ठा i2c_driver lp8860_driver = अणु
	.driver = अणु
		.name	= "lp8860",
		.of_match_table = of_lp8860_leds_match,
	पूर्ण,
	.probe		= lp8860_probe,
	.हटाओ		= lp8860_हटाओ,
	.id_table	= lp8860_id,
पूर्ण;
module_i2c_driver(lp8860_driver);

MODULE_DESCRIPTION("Texas Instruments LP8860 LED driver");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
