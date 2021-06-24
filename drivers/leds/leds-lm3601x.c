<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Flash and torch driver क्रम Texas Instruments LM3601X LED
// Flash driver chip family
// Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/led-class-flash.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा LM3601X_LED_IR		0x0
#घोषणा LM3601X_LED_TORCH	0x1

/* Registers */
#घोषणा LM3601X_ENABLE_REG	0x01
#घोषणा LM3601X_CFG_REG		0x02
#घोषणा LM3601X_LED_FLASH_REG	0x03
#घोषणा LM3601X_LED_TORCH_REG	0x04
#घोषणा LM3601X_FLAGS_REG	0x05
#घोषणा LM3601X_DEV_ID_REG	0x06

#घोषणा LM3601X_SW_RESET	BIT(7)

/* Enable Mode bits */
#घोषणा LM3601X_MODE_STANDBY	0x00
#घोषणा LM3601X_MODE_IR_DRV	BIT(0)
#घोषणा LM3601X_MODE_TORCH	BIT(1)
#घोषणा LM3601X_MODE_STROBE	(BIT(0) | BIT(1))
#घोषणा LM3601X_STRB_EN		BIT(2)
#घोषणा LM3601X_STRB_EDGE_TRIG	BIT(3)
#घोषणा LM3601X_IVFM_EN		BIT(4)

#घोषणा LM36010_BOOST_LIMIT_28	BIT(5)
#घोषणा LM36010_BOOST_FREQ_4MHZ	BIT(6)
#घोषणा LM36010_BOOST_MODE_PASS	BIT(7)

/* Flag Mask */
#घोषणा LM3601X_FLASH_TIME_OUT	BIT(0)
#घोषणा LM3601X_UVLO_FAULT	BIT(1)
#घोषणा LM3601X_THERM_SHUTDOWN	BIT(2)
#घोषणा LM3601X_THERM_CURR	BIT(3)
#घोषणा LM36010_CURR_LIMIT	BIT(4)
#घोषणा LM3601X_SHORT_FAULT	BIT(5)
#घोषणा LM3601X_IVFM_TRIP	BIT(6)
#घोषणा LM36010_OVP_FAULT	BIT(7)

#घोषणा LM3601X_MAX_TORCH_I_UA	376000
#घोषणा LM3601X_MIN_TORCH_I_UA	2400
#घोषणा LM3601X_TORCH_REG_DIV	2965

#घोषणा LM3601X_MAX_STROBE_I_UA	1500000
#घोषणा LM3601X_MIN_STROBE_I_UA	11000
#घोषणा LM3601X_STROBE_REG_DIV	11800

#घोषणा LM3601X_TIMEOUT_MASK	0x1e
#घोषणा LM3601X_ENABLE_MASK	(LM3601X_MODE_IR_DRV | LM3601X_MODE_TORCH)

#घोषणा LM3601X_LOWER_STEP_US	40000
#घोषणा LM3601X_UPPER_STEP_US	200000
#घोषणा LM3601X_MIN_TIMEOUT_US	40000
#घोषणा LM3601X_MAX_TIMEOUT_US	1600000
#घोषणा LM3601X_TIMEOUT_XOVER_US 400000

क्रमागत lm3601x_type अणु
	CHIP_LM36010 = 0,
	CHIP_LM36011,
पूर्ण;

/**
 * काष्ठा lm3601x_led -
 * @fled_cdev: flash LED class device poपूर्णांकer
 * @client: Poपूर्णांकer to the I2C client
 * @regmap: Devices रेजिस्टर map
 * @lock: Lock क्रम पढ़ोing/writing the device
 * @led_name: LED label क्रम the Torch or IR LED
 * @flash_समयout: the समयout क्रम the flash
 * @last_flag: last known flags रेजिस्टर value
 * @torch_current_max: maximum current क्रम the torch
 * @flash_current_max: maximum current क्रम the flash
 * @max_flash_समयout: maximum समयout क्रम the flash
 * @led_mode: The mode to enable either IR or Torch
 */
काष्ठा lm3601x_led अणु
	काष्ठा led_classdev_flash fled_cdev;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा mutex lock;

	अचिन्हित पूर्णांक flash_समयout;
	अचिन्हित पूर्णांक last_flag;

	u32 torch_current_max;
	u32 flash_current_max;
	u32 max_flash_समयout;

	u32 led_mode;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष lm3601x_regmap_defs[] = अणु
	अणु LM3601X_ENABLE_REG, 0x20 पूर्ण,
	अणु LM3601X_CFG_REG, 0x15 पूर्ण,
	अणु LM3601X_LED_FLASH_REG, 0x00 पूर्ण,
	अणु LM3601X_LED_TORCH_REG, 0x00 पूर्ण,
पूर्ण;

अटल bool lm3601x_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LM3601X_FLAGS_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config lm3601x_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LM3601X_DEV_ID_REG,
	.reg_शेषs = lm3601x_regmap_defs,
	.num_reg_शेषs = ARRAY_SIZE(lm3601x_regmap_defs),
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = lm3601x_अस्थिर_reg,
पूर्ण;

अटल काष्ठा lm3601x_led *fled_cdev_to_led(काष्ठा led_classdev_flash *fled_cdev)
अणु
	वापस container_of(fled_cdev, काष्ठा lm3601x_led, fled_cdev);
पूर्ण

अटल पूर्णांक lm3601x_पढ़ो_faults(काष्ठा lm3601x_led *led)
अणु
	पूर्णांक flags_val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(led->regmap, LM3601X_FLAGS_REG, &flags_val);
	अगर (ret < 0)
		वापस -EIO;

	led->last_flag = 0;

	अगर (flags_val & LM36010_OVP_FAULT)
		led->last_flag |= LED_FAULT_OVER_VOLTAGE;

	अगर (flags_val & (LM3601X_THERM_SHUTDOWN | LM3601X_THERM_CURR))
		led->last_flag |= LED_FAULT_OVER_TEMPERATURE;

	अगर (flags_val & LM3601X_SHORT_FAULT)
		led->last_flag |= LED_FAULT_SHORT_CIRCUIT;

	अगर (flags_val & LM36010_CURR_LIMIT)
		led->last_flag |= LED_FAULT_OVER_CURRENT;

	अगर (flags_val & LM3601X_UVLO_FAULT)
		led->last_flag |= LED_FAULT_UNDER_VOLTAGE;

	अगर (flags_val & LM3601X_IVFM_TRIP)
		led->last_flag |= LED_FAULT_INPUT_VOLTAGE;

	अगर (flags_val & LM3601X_THERM_SHUTDOWN)
		led->last_flag |= LED_FAULT_LED_OVER_TEMPERATURE;

	वापस led->last_flag;
पूर्ण

अटल पूर्णांक lm3601x_brightness_set(काष्ठा led_classdev *cdev,
					क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_flash *fled_cdev = lcdev_to_flcdev(cdev);
	काष्ठा lm3601x_led *led = fled_cdev_to_led(fled_cdev);
	पूर्णांक ret, led_mode_val;

	mutex_lock(&led->lock);

	ret = lm3601x_पढ़ो_faults(led);
	अगर (ret < 0)
		जाओ out;

	अगर (led->led_mode == LM3601X_LED_TORCH)
		led_mode_val = LM3601X_MODE_TORCH;
	अन्यथा
		led_mode_val = LM3601X_MODE_IR_DRV;

	अगर (brightness == LED_OFF) अणु
		ret = regmap_update_bits(led->regmap, LM3601X_ENABLE_REG,
					led_mode_val, LED_OFF);
		जाओ out;
	पूर्ण

	ret = regmap_ग_लिखो(led->regmap, LM3601X_LED_TORCH_REG, brightness);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_update_bits(led->regmap, LM3601X_ENABLE_REG,
				LM3601X_MODE_TORCH | LM3601X_MODE_IR_DRV,
				led_mode_val);
out:
	mutex_unlock(&led->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lm3601x_strobe_set(काष्ठा led_classdev_flash *fled_cdev,
				bool state)
अणु
	काष्ठा lm3601x_led *led = fled_cdev_to_led(fled_cdev);
	पूर्णांक समयout_reg_val;
	पूर्णांक current_समयout;
	पूर्णांक ret;

	mutex_lock(&led->lock);

	ret = regmap_पढ़ो(led->regmap, LM3601X_CFG_REG, &current_समयout);
	अगर (ret < 0)
		जाओ out;

	अगर (led->flash_समयout >= LM3601X_TIMEOUT_XOVER_US)
		समयout_reg_val = led->flash_समयout / LM3601X_UPPER_STEP_US + 0x07;
	अन्यथा
		समयout_reg_val = led->flash_समयout / LM3601X_LOWER_STEP_US - 0x01;

	अगर (led->flash_समयout != current_समयout)
		ret = regmap_update_bits(led->regmap, LM3601X_CFG_REG,
					LM3601X_TIMEOUT_MASK, समयout_reg_val);

	अगर (state)
		ret = regmap_update_bits(led->regmap, LM3601X_ENABLE_REG,
					LM3601X_MODE_TORCH | LM3601X_MODE_IR_DRV,
					LM3601X_MODE_STROBE);
	अन्यथा
		ret = regmap_update_bits(led->regmap, LM3601X_ENABLE_REG,
					LM3601X_MODE_STROBE, LED_OFF);

	ret = lm3601x_पढ़ो_faults(led);
out:
	mutex_unlock(&led->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lm3601x_flash_brightness_set(काष्ठा led_classdev_flash *fled_cdev,
					u32 brightness)
अणु
	काष्ठा lm3601x_led *led = fled_cdev_to_led(fled_cdev);
	u8 brightness_val;
	पूर्णांक ret;

	mutex_lock(&led->lock);
	ret = lm3601x_पढ़ो_faults(led);
	अगर (ret < 0)
		जाओ out;

	अगर (brightness == LED_OFF) अणु
		ret = regmap_update_bits(led->regmap, LM3601X_ENABLE_REG,
					LM3601X_MODE_STROBE, LED_OFF);
		जाओ out;
	पूर्ण

	brightness_val = brightness / LM3601X_STROBE_REG_DIV;

	ret = regmap_ग_लिखो(led->regmap, LM3601X_LED_FLASH_REG, brightness_val);
out:
	mutex_unlock(&led->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lm3601x_flash_समयout_set(काष्ठा led_classdev_flash *fled_cdev,
				u32 समयout)
अणु
	काष्ठा lm3601x_led *led = fled_cdev_to_led(fled_cdev);

	mutex_lock(&led->lock);

	led->flash_समयout = समयout;

	mutex_unlock(&led->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lm3601x_strobe_get(काष्ठा led_classdev_flash *fled_cdev, bool *state)
अणु
	काष्ठा lm3601x_led *led = fled_cdev_to_led(fled_cdev);
	पूर्णांक strobe_state;
	पूर्णांक ret;

	mutex_lock(&led->lock);

	ret = regmap_पढ़ो(led->regmap, LM3601X_ENABLE_REG, &strobe_state);
	अगर (ret < 0)
		जाओ out;

	*state = strobe_state & LM3601X_MODE_STROBE;

out:
	mutex_unlock(&led->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lm3601x_flash_fault_get(काष्ठा led_classdev_flash *fled_cdev,
				u32 *fault)
अणु
	काष्ठा lm3601x_led *led = fled_cdev_to_led(fled_cdev);

	lm3601x_पढ़ो_faults(led);

	*fault = led->last_flag;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा led_flash_ops flash_ops = अणु
	.flash_brightness_set	= lm3601x_flash_brightness_set,
	.strobe_set		= lm3601x_strobe_set,
	.strobe_get		= lm3601x_strobe_get,
	.समयout_set		= lm3601x_flash_समयout_set,
	.fault_get		= lm3601x_flash_fault_get,
पूर्ण;

अटल पूर्णांक lm3601x_रेजिस्टर_leds(काष्ठा lm3601x_led *led,
				 काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा led_classdev *led_cdev;
	काष्ठा led_flash_setting *setting;
	काष्ठा led_init_data init_data = अणुपूर्ण;

	led->fled_cdev.ops = &flash_ops;

	setting = &led->fled_cdev.समयout;
	setting->min = LM3601X_MIN_TIMEOUT_US;
	setting->max = led->max_flash_समयout;
	setting->step = LM3601X_LOWER_STEP_US;
	setting->val = led->max_flash_समयout;

	setting = &led->fled_cdev.brightness;
	setting->min = LM3601X_MIN_STROBE_I_UA;
	setting->max = led->flash_current_max;
	setting->step = LM3601X_TORCH_REG_DIV;
	setting->val = led->flash_current_max;

	led_cdev = &led->fled_cdev.led_cdev;
	led_cdev->brightness_set_blocking = lm3601x_brightness_set;
	led_cdev->max_brightness = DIV_ROUND_UP(led->torch_current_max,
						LM3601X_TORCH_REG_DIV);
	led_cdev->flags |= LED_DEV_CAP_FLASH;

	init_data.fwnode = fwnode;
	init_data.devicename = led->client->name;
	init_data.शेष_label = (led->led_mode == LM3601X_LED_TORCH) ?
					"torch" : "infrared";
	वापस devm_led_classdev_flash_रेजिस्टर_ext(&led->client->dev,
						&led->fled_cdev, &init_data);
पूर्ण

अटल पूर्णांक lm3601x_parse_node(काष्ठा lm3601x_led *led,
			      काष्ठा fwnode_handle **fwnode)
अणु
	काष्ठा fwnode_handle *child = शून्य;
	पूर्णांक ret = -ENODEV;

	child = device_get_next_child_node(&led->client->dev, child);
	अगर (!child) अणु
		dev_err(&led->client->dev, "No LED Child node\n");
		वापस ret;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(child, "reg", &led->led_mode);
	अगर (ret) अणु
		dev_err(&led->client->dev, "reg DT property missing\n");
		जाओ out_err;
	पूर्ण

	अगर (led->led_mode > LM3601X_LED_TORCH ||
	    led->led_mode < LM3601X_LED_IR) अणु
		dev_warn(&led->client->dev, "Invalid led mode requested\n");
		ret = -EINVAL;
		जाओ out_err;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(child, "led-max-microamp",
					&led->torch_current_max);
	अगर (ret) अणु
		dev_warn(&led->client->dev,
			"led-max-microamp DT property missing\n");
		जाओ out_err;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(child, "flash-max-microamp",
				&led->flash_current_max);
	अगर (ret) अणु
		dev_warn(&led->client->dev,
			 "flash-max-microamp DT property missing\n");
		जाओ out_err;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(child, "flash-max-timeout-us",
				&led->max_flash_समयout);
	अगर (ret) अणु
		dev_warn(&led->client->dev,
			 "flash-max-timeout-us DT property missing\n");
		जाओ out_err;
	पूर्ण

	*fwnode = child;

out_err:
	fwnode_handle_put(child);
	वापस ret;
पूर्ण

अटल पूर्णांक lm3601x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3601x_led *led;
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक ret;

	led = devm_kzalloc(&client->dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	led->client = client;
	i2c_set_clientdata(client, led);

	ret = lm3601x_parse_node(led, &fwnode);
	अगर (ret)
		वापस -ENODEV;

	led->regmap = devm_regmap_init_i2c(client, &lm3601x_regmap);
	अगर (IS_ERR(led->regmap)) अणु
		ret = PTR_ERR(led->regmap);
		dev_err(&client->dev,
			"Failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	mutex_init(&led->lock);

	वापस lm3601x_रेजिस्टर_leds(led, fwnode);
पूर्ण

अटल पूर्णांक lm3601x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3601x_led *led = i2c_get_clientdata(client);

	mutex_destroy(&led->lock);

	वापस regmap_update_bits(led->regmap, LM3601X_ENABLE_REG,
			   LM3601X_ENABLE_MASK,
			   LM3601X_MODE_STANDBY);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3601x_id[] = अणु
	अणु "LM36010", CHIP_LM36010 पूर्ण,
	अणु "LM36011", CHIP_LM36011 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm3601x_id);

अटल स्थिर काष्ठा of_device_id of_lm3601x_leds_match[] = अणु
	अणु .compatible = "ti,lm36010", पूर्ण,
	अणु .compatible = "ti,lm36011", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lm3601x_leds_match);

अटल काष्ठा i2c_driver lm3601x_i2c_driver = अणु
	.driver = अणु
		.name = "lm3601x",
		.of_match_table = of_lm3601x_leds_match,
	पूर्ण,
	.probe_new = lm3601x_probe,
	.हटाओ = lm3601x_हटाओ,
	.id_table = lm3601x_id,
पूर्ण;
module_i2c_driver(lm3601x_i2c_driver);

MODULE_DESCRIPTION("Texas Instruments Flash Lighting driver for LM3601X");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
