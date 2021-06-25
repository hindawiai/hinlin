<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// TI LM3697 LED chip family driver
// Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/leds-ti-lmu-common.h>

#घोषणा LM3697_REV			0x0
#घोषणा LM3697_RESET			0x1
#घोषणा LM3697_OUTPUT_CONFIG		0x10
#घोषणा LM3697_CTRL_A_RAMP		0x11
#घोषणा LM3697_CTRL_B_RAMP		0x12
#घोषणा LM3697_CTRL_A_B_RT_RAMP		0x13
#घोषणा LM3697_CTRL_A_B_RAMP_CFG	0x14
#घोषणा LM3697_CTRL_A_B_BRT_CFG		0x16
#घोषणा LM3697_CTRL_A_FS_CURR_CFG	0x17
#घोषणा LM3697_CTRL_B_FS_CURR_CFG	0x18
#घोषणा LM3697_PWM_CFG			0x1c
#घोषणा LM3697_CTRL_A_BRT_LSB		0x20
#घोषणा LM3697_CTRL_A_BRT_MSB		0x21
#घोषणा LM3697_CTRL_B_BRT_LSB		0x22
#घोषणा LM3697_CTRL_B_BRT_MSB		0x23
#घोषणा LM3697_CTRL_ENABLE		0x24

#घोषणा LM3697_SW_RESET		BIT(0)

#घोषणा LM3697_CTRL_A_EN	BIT(0)
#घोषणा LM3697_CTRL_B_EN	BIT(1)
#घोषणा LM3697_CTRL_A_B_EN	(LM3697_CTRL_A_EN | LM3697_CTRL_B_EN)

#घोषणा LM3697_MAX_LED_STRINGS	3

#घोषणा LM3697_CONTROL_A	0
#घोषणा LM3697_CONTROL_B	1
#घोषणा LM3697_MAX_CONTROL_BANKS 2

/**
 * काष्ठा lm3697_led -
 * @hvled_strings: Array of LED strings associated with a control bank
 * @label: LED label
 * @led_dev: LED class device
 * @priv: Poपूर्णांकer to the device काष्ठा
 * @lmu_data: Register and setting values क्रम common code
 * @control_bank: Control bank the LED is associated to. 0 is control bank A
 *		   1 is control bank B
 */
काष्ठा lm3697_led अणु
	u32 hvled_strings[LM3697_MAX_LED_STRINGS];
	अक्षर label[LED_MAX_NAME_SIZE];
	काष्ठा led_classdev led_dev;
	काष्ठा lm3697 *priv;
	काष्ठा ti_lmu_bank lmu_data;
	पूर्णांक control_bank;
	पूर्णांक enabled;
	पूर्णांक num_leds;
पूर्ण;

/**
 * काष्ठा lm3697 -
 * @enable_gpio: Hardware enable gpio
 * @regulator: LED supply regulator poपूर्णांकer
 * @client: Poपूर्णांकer to the I2C client
 * @regmap: Devices रेजिस्टर map
 * @dev: Poपूर्णांकer to the devices device काष्ठा
 * @lock: Lock क्रम पढ़ोing/writing the device
 * @leds: Array of LED strings
 */
काष्ठा lm3697 अणु
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regulator *regulator;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा mutex lock;

	पूर्णांक bank_cfg;
	पूर्णांक num_banks;

	काष्ठा lm3697_led leds[];
पूर्ण;

अटल स्थिर काष्ठा reg_शेष lm3697_reg_defs[] = अणु
	अणुLM3697_OUTPUT_CONFIG, 0x6पूर्ण,
	अणुLM3697_CTRL_A_RAMP, 0x0पूर्ण,
	अणुLM3697_CTRL_B_RAMP, 0x0पूर्ण,
	अणुLM3697_CTRL_A_B_RT_RAMP, 0x0पूर्ण,
	अणुLM3697_CTRL_A_B_RAMP_CFG, 0x0पूर्ण,
	अणुLM3697_CTRL_A_B_BRT_CFG, 0x0पूर्ण,
	अणुLM3697_CTRL_A_FS_CURR_CFG, 0x13पूर्ण,
	अणुLM3697_CTRL_B_FS_CURR_CFG, 0x13पूर्ण,
	अणुLM3697_PWM_CFG, 0xcपूर्ण,
	अणुLM3697_CTRL_A_BRT_LSB, 0x0पूर्ण,
	अणुLM3697_CTRL_A_BRT_MSB, 0x0पूर्ण,
	अणुLM3697_CTRL_B_BRT_LSB, 0x0पूर्ण,
	अणुLM3697_CTRL_B_BRT_MSB, 0x0पूर्ण,
	अणुLM3697_CTRL_ENABLE, 0x0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lm3697_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = LM3697_CTRL_ENABLE,
	.reg_शेषs = lm3697_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(lm3697_reg_defs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक lm3697_brightness_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness brt_val)
अणु
	काष्ठा lm3697_led *led = container_of(led_cdev, काष्ठा lm3697_led,
					      led_dev);
	पूर्णांक ctrl_en_val = (1 << led->control_bank);
	काष्ठा device *dev = led->priv->dev;
	पूर्णांक ret;

	mutex_lock(&led->priv->lock);

	अगर (brt_val == LED_OFF) अणु
		ret = regmap_update_bits(led->priv->regmap, LM3697_CTRL_ENABLE,
					 ctrl_en_val, ~ctrl_en_val);
		अगर (ret) अणु
			dev_err(dev, "Cannot write ctrl register\n");
			जाओ brightness_out;
		पूर्ण

		led->enabled = LED_OFF;
	पूर्ण अन्यथा अणु
		ret = ti_lmu_common_set_brightness(&led->lmu_data, brt_val);
		अगर (ret) अणु
			dev_err(dev, "Cannot write brightness\n");
			जाओ brightness_out;
		पूर्ण

		अगर (!led->enabled) अणु
			ret = regmap_update_bits(led->priv->regmap,
						 LM3697_CTRL_ENABLE,
						 ctrl_en_val, ctrl_en_val);
			अगर (ret) अणु
				dev_err(dev, "Cannot enable the device\n");
				जाओ brightness_out;
			पूर्ण

			led->enabled = brt_val;
		पूर्ण
	पूर्ण

brightness_out:
	mutex_unlock(&led->priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lm3697_init(काष्ठा lm3697 *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा lm3697_led *led;
	पूर्णांक i, ret;

	अगर (priv->enable_gpio) अणु
		gpiod_direction_output(priv->enable_gpio, 1);
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(priv->regmap, LM3697_RESET, LM3697_SW_RESET);
		अगर (ret) अणु
			dev_err(dev, "Cannot reset the device\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = regmap_ग_लिखो(priv->regmap, LM3697_CTRL_ENABLE, 0x0);
	अगर (ret) अणु
		dev_err(dev, "Cannot write ctrl enable\n");
		जाओ out;
	पूर्ण

	ret = regmap_ग_लिखो(priv->regmap, LM3697_OUTPUT_CONFIG, priv->bank_cfg);
	अगर (ret)
		dev_err(dev, "Cannot write OUTPUT config\n");

	क्रम (i = 0; i < priv->num_banks; i++) अणु
		led = &priv->leds[i];
		ret = ti_lmu_common_set_ramp(&led->lmu_data);
		अगर (ret)
			dev_err(dev, "Setting the ramp rate failed\n");
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक lm3697_probe_dt(काष्ठा lm3697 *priv)
अणु
	काष्ठा fwnode_handle *child = शून्य;
	काष्ठा device *dev = priv->dev;
	काष्ठा lm3697_led *led;
	पूर्णांक ret = -EINVAL;
	पूर्णांक control_bank;
	माप_प्रकार i = 0;
	पूर्णांक j;

	priv->enable_gpio = devm_gpiod_get_optional(dev, "enable",
						    GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->enable_gpio)) अणु
		ret = PTR_ERR(priv->enable_gpio);
		dev_err(dev, "Failed to get enable gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->regulator = devm_regulator_get(dev, "vled");
	अगर (IS_ERR(priv->regulator))
		priv->regulator = शून्य;

	device_क्रम_each_child_node(dev, child) अणु
		काष्ठा led_init_data init_data = अणुपूर्ण;

		ret = fwnode_property_पढ़ो_u32(child, "reg", &control_bank);
		अगर (ret) अणु
			dev_err(dev, "reg property missing\n");
			fwnode_handle_put(child);
			जाओ child_out;
		पूर्ण

		अगर (control_bank > LM3697_CONTROL_B) अणु
			dev_err(dev, "reg property is invalid\n");
			ret = -EINVAL;
			fwnode_handle_put(child);
			जाओ child_out;
		पूर्ण

		led = &priv->leds[i];

		ret = ti_lmu_common_get_brt_res(dev, child, &led->lmu_data);
		अगर (ret)
			dev_warn(dev,
				 "brightness resolution property missing\n");

		led->control_bank = control_bank;
		led->lmu_data.regmap = priv->regmap;
		led->lmu_data.runसमय_ramp_reg = LM3697_CTRL_A_RAMP +
						 control_bank;
		led->lmu_data.msb_brightness_reg = LM3697_CTRL_A_BRT_MSB +
						   led->control_bank * 2;
		led->lmu_data.lsb_brightness_reg = LM3697_CTRL_A_BRT_LSB +
						   led->control_bank * 2;

		led->num_leds = fwnode_property_count_u32(child, "led-sources");
		अगर (led->num_leds > LM3697_MAX_LED_STRINGS) अणु
			dev_err(dev, "Too many LED strings defined\n");
			जारी;
		पूर्ण

		ret = fwnode_property_पढ़ो_u32_array(child, "led-sources",
						    led->hvled_strings,
						    led->num_leds);
		अगर (ret) अणु
			dev_err(dev, "led-sources property missing\n");
			fwnode_handle_put(child);
			जाओ child_out;
		पूर्ण

		क्रम (j = 0; j < led->num_leds; j++)
			priv->bank_cfg |=
				(led->control_bank << led->hvled_strings[j]);

		ret = ti_lmu_common_get_ramp_params(dev, child, &led->lmu_data);
		अगर (ret)
			dev_warn(dev, "runtime-ramp properties missing\n");

		init_data.fwnode = child;
		init_data.devicename = priv->client->name;
		/* क्रम backwards compatibility अगर `label` is not present */
		init_data.शेष_label = ":";

		led->priv = priv;
		led->led_dev.max_brightness = led->lmu_data.max_brightness;
		led->led_dev.brightness_set_blocking = lm3697_brightness_set;

		ret = devm_led_classdev_रेजिस्टर_ext(dev, &led->led_dev,
						     &init_data);
		अगर (ret) अणु
			dev_err(dev, "led register err: %d\n", ret);
			fwnode_handle_put(child);
			जाओ child_out;
		पूर्ण

		i++;
	पूर्ण

child_out:
	वापस ret;
पूर्ण

अटल पूर्णांक lm3697_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा lm3697 *led;
	पूर्णांक count;
	पूर्णांक ret;

	count = device_get_child_node_count(dev);
	अगर (!count || count > LM3697_MAX_CONTROL_BANKS) अणु
		dev_err(dev, "Strange device tree!");
		वापस -ENODEV;
	पूर्ण

	led = devm_kzalloc(dev, काष्ठा_size(led, leds, count), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	mutex_init(&led->lock);
	i2c_set_clientdata(client, led);

	led->client = client;
	led->dev = dev;
	led->num_banks = count;
	led->regmap = devm_regmap_init_i2c(client, &lm3697_regmap_config);
	अगर (IS_ERR(led->regmap)) अणु
		ret = PTR_ERR(led->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = lm3697_probe_dt(led);
	अगर (ret)
		वापस ret;

	वापस lm3697_init(led);
पूर्ण

अटल पूर्णांक lm3697_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3697 *led = i2c_get_clientdata(client);
	काष्ठा device *dev = &led->client->dev;
	पूर्णांक ret;

	ret = regmap_update_bits(led->regmap, LM3697_CTRL_ENABLE,
				 LM3697_CTRL_A_B_EN, 0);
	अगर (ret) अणु
		dev_err(dev, "Failed to disable the device\n");
		वापस ret;
	पूर्ण

	अगर (led->enable_gpio)
		gpiod_direction_output(led->enable_gpio, 0);

	अगर (led->regulator) अणु
		ret = regulator_disable(led->regulator);
		अगर (ret)
			dev_err(dev, "Failed to disable regulator\n");
	पूर्ण

	mutex_destroy(&led->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3697_id[] = अणु
	अणु "lm3697", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm3697_id);

अटल स्थिर काष्ठा of_device_id of_lm3697_leds_match[] = अणु
	अणु .compatible = "ti,lm3697", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lm3697_leds_match);

अटल काष्ठा i2c_driver lm3697_driver = अणु
	.driver = अणु
		.name	= "lm3697",
		.of_match_table = of_lm3697_leds_match,
	पूर्ण,
	.probe		= lm3697_probe,
	.हटाओ		= lm3697_हटाओ,
	.id_table	= lm3697_id,
पूर्ण;
module_i2c_driver(lm3697_driver);

MODULE_DESCRIPTION("Texas Instruments LM3697 LED driver");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
