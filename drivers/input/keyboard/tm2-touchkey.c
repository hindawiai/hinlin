<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TM2 touchkey device driver
 *
 * Copyright 2005 Phil Blundell
 * Copyright 2016 Samsung Electronics Co., Ltd.
 *
 * Author: Beomho Seo <beomho.seo@samsung.com>
 * Author: Jaechul Lee <jcsing.lee@samsung.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा TM2_TOUCHKEY_DEV_NAME		"tm2-touchkey"

#घोषणा ARIES_TOUCHKEY_CMD_LED_ON	0x1
#घोषणा ARIES_TOUCHKEY_CMD_LED_OFF	0x2
#घोषणा TM2_TOUCHKEY_CMD_LED_ON		0x10
#घोषणा TM2_TOUCHKEY_CMD_LED_OFF	0x20
#घोषणा TM2_TOUCHKEY_BIT_PRESS_EV	BIT(3)
#घोषणा TM2_TOUCHKEY_BIT_KEYCODE	GENMASK(2, 0)
#घोषणा TM2_TOUCHKEY_LED_VOLTAGE_MIN	2500000
#घोषणा TM2_TOUCHKEY_LED_VOLTAGE_MAX	3300000

काष्ठा touchkey_variant अणु
	u8 keycode_reg;
	u8 base_reg;
	u8 cmd_led_on;
	u8 cmd_led_off;
	bool no_reg;
	bool fixed_regulator;
पूर्ण;

काष्ठा पंचांग2_touchkey_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	काष्ठा led_classdev led_dev;
	काष्ठा regulator *vdd;
	काष्ठा regulator_bulk_data regulators[3];
	स्थिर काष्ठा touchkey_variant *variant;
	u32 keycodes[4];
	पूर्णांक num_keycodes;
पूर्ण;

अटल स्थिर काष्ठा touchkey_variant पंचांग2_touchkey_variant = अणु
	.keycode_reg = 0x03,
	.base_reg = 0x00,
	.cmd_led_on = TM2_TOUCHKEY_CMD_LED_ON,
	.cmd_led_off = TM2_TOUCHKEY_CMD_LED_OFF,
पूर्ण;

अटल स्थिर काष्ठा touchkey_variant midas_touchkey_variant = अणु
	.keycode_reg = 0x00,
	.base_reg = 0x00,
	.cmd_led_on = TM2_TOUCHKEY_CMD_LED_ON,
	.cmd_led_off = TM2_TOUCHKEY_CMD_LED_OFF,
पूर्ण;

अटल काष्ठा touchkey_variant aries_touchkey_variant = अणु
	.no_reg = true,
	.fixed_regulator = true,
	.cmd_led_on = ARIES_TOUCHKEY_CMD_LED_ON,
	.cmd_led_off = ARIES_TOUCHKEY_CMD_LED_OFF,
पूर्ण;

अटल स्थिर काष्ठा touchkey_variant tc360_touchkey_variant = अणु
	.keycode_reg = 0x00,
	.base_reg = 0x00,
	.fixed_regulator = true,
	.cmd_led_on = TM2_TOUCHKEY_CMD_LED_ON,
	.cmd_led_off = TM2_TOUCHKEY_CMD_LED_OFF,
पूर्ण;

अटल पूर्णांक पंचांग2_touchkey_led_brightness_set(काष्ठा led_classdev *led_dev,
					    क्रमागत led_brightness brightness)
अणु
	काष्ठा पंचांग2_touchkey_data *touchkey =
		container_of(led_dev, काष्ठा पंचांग2_touchkey_data, led_dev);
	u32 volt;
	u8 data;

	अगर (brightness == LED_OFF) अणु
		volt = TM2_TOUCHKEY_LED_VOLTAGE_MIN;
		data = touchkey->variant->cmd_led_off;
	पूर्ण अन्यथा अणु
		volt = TM2_TOUCHKEY_LED_VOLTAGE_MAX;
		data = touchkey->variant->cmd_led_on;
	पूर्ण

	अगर (!touchkey->variant->fixed_regulator)
		regulator_set_voltage(touchkey->vdd, volt, volt);

	वापस touchkey->variant->no_reg ?
		i2c_smbus_ग_लिखो_byte(touchkey->client, data) :
		i2c_smbus_ग_लिखो_byte_data(touchkey->client,
					  touchkey->variant->base_reg, data);
पूर्ण

अटल पूर्णांक पंचांग2_touchkey_घातer_enable(काष्ठा पंचांग2_touchkey_data *touchkey)
अणु
	पूर्णांक error;

	error = regulator_bulk_enable(ARRAY_SIZE(touchkey->regulators),
				      touchkey->regulators);
	अगर (error)
		वापस error;

	/* रुकोing क्रम device initialization, at least 150ms */
	msleep(150);

	वापस 0;
पूर्ण

अटल व्योम पंचांग2_touchkey_घातer_disable(व्योम *data)
अणु
	काष्ठा पंचांग2_touchkey_data *touchkey = data;

	regulator_bulk_disable(ARRAY_SIZE(touchkey->regulators),
			       touchkey->regulators);
पूर्ण

अटल irqवापस_t पंचांग2_touchkey_irq_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा पंचांग2_touchkey_data *touchkey = devid;
	पूर्णांक data;
	पूर्णांक index;
	पूर्णांक i;

	अगर (touchkey->variant->no_reg)
		data = i2c_smbus_पढ़ो_byte(touchkey->client);
	अन्यथा
		data = i2c_smbus_पढ़ो_byte_data(touchkey->client,
						touchkey->variant->keycode_reg);
	अगर (data < 0) अणु
		dev_err(&touchkey->client->dev,
			"failed to read i2c data: %d\n", data);
		जाओ out;
	पूर्ण

	index = (data & TM2_TOUCHKEY_BIT_KEYCODE) - 1;
	अगर (index < 0 || index >= touchkey->num_keycodes) अणु
		dev_warn(&touchkey->client->dev,
			 "invalid keycode index %d\n", index);
		जाओ out;
	पूर्ण

	अगर (data & TM2_TOUCHKEY_BIT_PRESS_EV) अणु
		क्रम (i = 0; i < touchkey->num_keycodes; i++)
			input_report_key(touchkey->input_dev,
					 touchkey->keycodes[i], 0);
	पूर्ण अन्यथा अणु
		input_report_key(touchkey->input_dev,
				 touchkey->keycodes[index], 1);
	पूर्ण

	input_sync(touchkey->input_dev);

out:
	अगर (touchkey->variant->fixed_regulator &&
				data & TM2_TOUCHKEY_BIT_PRESS_EV) अणु
		/* touch turns backlight on, so make sure we're in sync */
		अगर (touchkey->led_dev.brightness == LED_OFF)
			पंचांग2_touchkey_led_brightness_set(&touchkey->led_dev,
							LED_OFF);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक पंचांग2_touchkey_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा पंचांग2_touchkey_data *touchkey;
	पूर्णांक error;
	पूर्णांक i;

	अगर (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "incompatible I2C adapter\n");
		वापस -EIO;
	पूर्ण

	touchkey = devm_kzalloc(&client->dev, माप(*touchkey), GFP_KERNEL);
	अगर (!touchkey)
		वापस -ENOMEM;

	touchkey->client = client;
	i2c_set_clientdata(client, touchkey);

	touchkey->variant = of_device_get_match_data(&client->dev);

	touchkey->regulators[0].supply = "vcc";
	touchkey->regulators[1].supply = "vdd";
	touchkey->regulators[2].supply = "vddio";
	error = devm_regulator_bulk_get(&client->dev,
					ARRAY_SIZE(touchkey->regulators),
					touchkey->regulators);
	अगर (error) अणु
		dev_err(&client->dev, "failed to get regulators: %d\n", error);
		वापस error;
	पूर्ण

	/* Save VDD क्रम easy access */
	touchkey->vdd = touchkey->regulators[1].consumer;

	touchkey->num_keycodes = of_property_पढ़ो_variable_u32_array(np,
					"linux,keycodes", touchkey->keycodes, 0,
					ARRAY_SIZE(touchkey->keycodes));
	अगर (touchkey->num_keycodes <= 0) अणु
		/* शेष keycodes */
		touchkey->keycodes[0] = KEY_PHONE;
		touchkey->keycodes[1] = KEY_BACK;
		touchkey->num_keycodes = 2;
	पूर्ण

	error = पंचांग2_touchkey_घातer_enable(touchkey);
	अगर (error) अणु
		dev_err(&client->dev, "failed to power up device: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&client->dev,
					 पंचांग2_touchkey_घातer_disable, touchkey);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to install poweroff handler: %d\n", error);
		वापस error;
	पूर्ण

	/* input device */
	touchkey->input_dev = devm_input_allocate_device(&client->dev);
	अगर (!touchkey->input_dev) अणु
		dev_err(&client->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	touchkey->input_dev->name = TM2_TOUCHKEY_DEV_NAME;
	touchkey->input_dev->id.bustype = BUS_I2C;

	क्रम (i = 0; i < touchkey->num_keycodes; i++)
		input_set_capability(touchkey->input_dev, EV_KEY,
				     touchkey->keycodes[i]);

	error = input_रेजिस्टर_device(touchkey->input_dev);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, पंचांग2_touchkey_irq_handler,
					  IRQF_ONESHOT,
					  TM2_TOUCHKEY_DEV_NAME, touchkey);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to request threaded irq: %d\n", error);
		वापस error;
	पूर्ण

	/* led device */
	touchkey->led_dev.name = TM2_TOUCHKEY_DEV_NAME;
	touchkey->led_dev.brightness = LED_ON;
	touchkey->led_dev.max_brightness = LED_ON;
	touchkey->led_dev.brightness_set_blocking =
					पंचांग2_touchkey_led_brightness_set;

	error = devm_led_classdev_रेजिस्टर(&client->dev, &touchkey->led_dev);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to register touchkey led: %d\n", error);
		वापस error;
	पूर्ण

	अगर (touchkey->variant->fixed_regulator)
		पंचांग2_touchkey_led_brightness_set(&touchkey->led_dev, LED_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused पंचांग2_touchkey_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा पंचांग2_touchkey_data *touchkey = i2c_get_clientdata(client);

	disable_irq(client->irq);
	पंचांग2_touchkey_घातer_disable(touchkey);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused पंचांग2_touchkey_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा पंचांग2_touchkey_data *touchkey = i2c_get_clientdata(client);
	पूर्णांक ret;

	enable_irq(client->irq);

	ret = पंचांग2_touchkey_घातer_enable(touchkey);
	अगर (ret)
		dev_err(dev, "failed to enable power: %d\n", ret);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(पंचांग2_touchkey_pm_ops,
			 पंचांग2_touchkey_suspend, पंचांग2_touchkey_resume);

अटल स्थिर काष्ठा i2c_device_id पंचांग2_touchkey_id_table[] = अणु
	अणु TM2_TOUCHKEY_DEV_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पंचांग2_touchkey_id_table);

अटल स्थिर काष्ठा of_device_id पंचांग2_touchkey_of_match[] = अणु
	अणु
		.compatible = "cypress,tm2-touchkey",
		.data = &पंचांग2_touchkey_variant,
	पूर्ण, अणु
		.compatible = "cypress,midas-touchkey",
		.data = &midas_touchkey_variant,
	पूर्ण, अणु
		.compatible = "cypress,aries-touchkey",
		.data = &aries_touchkey_variant,
	पूर्ण, अणु
		.compatible = "coreriver,tc360-touchkey",
		.data = &tc360_touchkey_variant,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, पंचांग2_touchkey_of_match);

अटल काष्ठा i2c_driver पंचांग2_touchkey_driver = अणु
	.driver = अणु
		.name = TM2_TOUCHKEY_DEV_NAME,
		.pm = &पंचांग2_touchkey_pm_ops,
		.of_match_table = of_match_ptr(पंचांग2_touchkey_of_match),
	पूर्ण,
	.probe = पंचांग2_touchkey_probe,
	.id_table = पंचांग2_touchkey_id_table,
पूर्ण;
module_i2c_driver(पंचांग2_touchkey_driver);

MODULE_AUTHOR("Beomho Seo <beomho.seo@samsung.com>");
MODULE_AUTHOR("Jaechul Lee <jcsing.lee@samsung.com>");
MODULE_DESCRIPTION("Samsung touchkey driver");
MODULE_LICENSE("GPL v2");
