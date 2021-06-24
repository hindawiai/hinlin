<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Input driver क्रम Microchip CAP11xx based capacitive touch sensors
 *
 * (c) 2014 Daniel Mack <linux@zonque.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/leds.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>

#घोषणा CAP11XX_REG_MAIN_CONTROL	0x00
#घोषणा CAP11XX_REG_MAIN_CONTROL_GAIN_SHIFT	(6)
#घोषणा CAP11XX_REG_MAIN_CONTROL_GAIN_MASK	(0xc0)
#घोषणा CAP11XX_REG_MAIN_CONTROL_DLSEEP		BIT(4)
#घोषणा CAP11XX_REG_GENERAL_STATUS	0x02
#घोषणा CAP11XX_REG_SENSOR_INPUT	0x03
#घोषणा CAP11XX_REG_NOISE_FLAG_STATUS	0x0a
#घोषणा CAP11XX_REG_SENOR_DELTA(X)	(0x10 + (X))
#घोषणा CAP11XX_REG_SENSITIVITY_CONTROL	0x1f
#घोषणा CAP11XX_REG_CONFIG		0x20
#घोषणा CAP11XX_REG_SENSOR_ENABLE	0x21
#घोषणा CAP11XX_REG_SENSOR_CONFIG	0x22
#घोषणा CAP11XX_REG_SENSOR_CONFIG2	0x23
#घोषणा CAP11XX_REG_SAMPLING_CONFIG	0x24
#घोषणा CAP11XX_REG_CALIBRATION		0x26
#घोषणा CAP11XX_REG_INT_ENABLE		0x27
#घोषणा CAP11XX_REG_REPEAT_RATE		0x28
#घोषणा CAP11XX_REG_MT_CONFIG		0x2a
#घोषणा CAP11XX_REG_MT_PATTERN_CONFIG	0x2b
#घोषणा CAP11XX_REG_MT_PATTERN		0x2d
#घोषणा CAP11XX_REG_RECALIB_CONFIG	0x2f
#घोषणा CAP11XX_REG_SENSOR_THRESH(X)	(0x30 + (X))
#घोषणा CAP11XX_REG_SENSOR_NOISE_THRESH	0x38
#घोषणा CAP11XX_REG_STANDBY_CHANNEL	0x40
#घोषणा CAP11XX_REG_STANDBY_CONFIG	0x41
#घोषणा CAP11XX_REG_STANDBY_SENSITIVITY	0x42
#घोषणा CAP11XX_REG_STANDBY_THRESH	0x43
#घोषणा CAP11XX_REG_CONFIG2		0x44
#घोषणा CAP11XX_REG_CONFIG2_ALT_POL	BIT(6)
#घोषणा CAP11XX_REG_SENSOR_BASE_CNT(X)	(0x50 + (X))
#घोषणा CAP11XX_REG_LED_POLARITY	0x73
#घोषणा CAP11XX_REG_LED_OUTPUT_CONTROL	0x74

#घोषणा CAP11XX_REG_LED_DUTY_CYCLE_1	0x90
#घोषणा CAP11XX_REG_LED_DUTY_CYCLE_2	0x91
#घोषणा CAP11XX_REG_LED_DUTY_CYCLE_3	0x92
#घोषणा CAP11XX_REG_LED_DUTY_CYCLE_4	0x93

#घोषणा CAP11XX_REG_LED_DUTY_MIN_MASK	(0x0f)
#घोषणा CAP11XX_REG_LED_DUTY_MIN_MASK_SHIFT	(0)
#घोषणा CAP11XX_REG_LED_DUTY_MAX_MASK	(0xf0)
#घोषणा CAP11XX_REG_LED_DUTY_MAX_MASK_SHIFT	(4)
#घोषणा CAP11XX_REG_LED_DUTY_MAX_VALUE	(15)

#घोषणा CAP11XX_REG_SENSOR_CALIB	(0xb1 + (X))
#घोषणा CAP11XX_REG_SENSOR_CALIB_LSB1	0xb9
#घोषणा CAP11XX_REG_SENSOR_CALIB_LSB2	0xba
#घोषणा CAP11XX_REG_PRODUCT_ID		0xfd
#घोषणा CAP11XX_REG_MANUFACTURER_ID	0xfe
#घोषणा CAP11XX_REG_REVISION		0xff

#घोषणा CAP11XX_MANUFACTURER_ID	0x5d

#अगर_घोषित CONFIG_LEDS_CLASS
काष्ठा cap11xx_led अणु
	काष्ठा cap11xx_priv *priv;
	काष्ठा led_classdev cdev;
	u32 reg;
पूर्ण;
#पूर्ण_अगर

काष्ठा cap11xx_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा input_dev *idev;

	काष्ठा cap11xx_led *leds;
	पूर्णांक num_leds;

	/* config */
	u32 keycodes[];
पूर्ण;

काष्ठा cap11xx_hw_model अणु
	u8 product_id;
	अचिन्हित पूर्णांक num_channels;
	अचिन्हित पूर्णांक num_leds;
पूर्ण;

क्रमागत अणु
	CAP1106,
	CAP1126,
	CAP1188,
पूर्ण;

अटल स्थिर काष्ठा cap11xx_hw_model cap11xx_devices[] = अणु
	[CAP1106] = अणु .product_id = 0x55, .num_channels = 6, .num_leds = 0 पूर्ण,
	[CAP1126] = अणु .product_id = 0x53, .num_channels = 6, .num_leds = 2 पूर्ण,
	[CAP1188] = अणु .product_id = 0x50, .num_channels = 8, .num_leds = 8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cap11xx_reg_शेषs[] = अणु
	अणु CAP11XX_REG_MAIN_CONTROL,		0x00 पूर्ण,
	अणु CAP11XX_REG_GENERAL_STATUS,		0x00 पूर्ण,
	अणु CAP11XX_REG_SENSOR_INPUT,		0x00 पूर्ण,
	अणु CAP11XX_REG_NOISE_FLAG_STATUS,	0x00 पूर्ण,
	अणु CAP11XX_REG_SENSITIVITY_CONTROL,	0x2f पूर्ण,
	अणु CAP11XX_REG_CONFIG,			0x20 पूर्ण,
	अणु CAP11XX_REG_SENSOR_ENABLE,		0x3f पूर्ण,
	अणु CAP11XX_REG_SENSOR_CONFIG,		0xa4 पूर्ण,
	अणु CAP11XX_REG_SENSOR_CONFIG2,		0x07 पूर्ण,
	अणु CAP11XX_REG_SAMPLING_CONFIG,		0x39 पूर्ण,
	अणु CAP11XX_REG_CALIBRATION,		0x00 पूर्ण,
	अणु CAP11XX_REG_INT_ENABLE,		0x3f पूर्ण,
	अणु CAP11XX_REG_REPEAT_RATE,		0x3f पूर्ण,
	अणु CAP11XX_REG_MT_CONFIG,		0x80 पूर्ण,
	अणु CAP11XX_REG_MT_PATTERN_CONFIG,	0x00 पूर्ण,
	अणु CAP11XX_REG_MT_PATTERN,		0x3f पूर्ण,
	अणु CAP11XX_REG_RECALIB_CONFIG,		0x8a पूर्ण,
	अणु CAP11XX_REG_SENSOR_THRESH(0),		0x40 पूर्ण,
	अणु CAP11XX_REG_SENSOR_THRESH(1),		0x40 पूर्ण,
	अणु CAP11XX_REG_SENSOR_THRESH(2),		0x40 पूर्ण,
	अणु CAP11XX_REG_SENSOR_THRESH(3),		0x40 पूर्ण,
	अणु CAP11XX_REG_SENSOR_THRESH(4),		0x40 पूर्ण,
	अणु CAP11XX_REG_SENSOR_THRESH(5),		0x40 पूर्ण,
	अणु CAP11XX_REG_SENSOR_NOISE_THRESH,	0x01 पूर्ण,
	अणु CAP11XX_REG_STANDBY_CHANNEL,		0x00 पूर्ण,
	अणु CAP11XX_REG_STANDBY_CONFIG,		0x39 पूर्ण,
	अणु CAP11XX_REG_STANDBY_SENSITIVITY,	0x02 पूर्ण,
	अणु CAP11XX_REG_STANDBY_THRESH,		0x40 पूर्ण,
	अणु CAP11XX_REG_CONFIG2,			0x40 पूर्ण,
	अणु CAP11XX_REG_LED_POLARITY,		0x00 पूर्ण,
	अणु CAP11XX_REG_SENSOR_CALIB_LSB1,	0x00 पूर्ण,
	अणु CAP11XX_REG_SENSOR_CALIB_LSB2,	0x00 पूर्ण,
पूर्ण;

अटल bool cap11xx_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CAP11XX_REG_MAIN_CONTROL:
	हाल CAP11XX_REG_SENSOR_INPUT:
	हाल CAP11XX_REG_SENOR_DELTA(0):
	हाल CAP11XX_REG_SENOR_DELTA(1):
	हाल CAP11XX_REG_SENOR_DELTA(2):
	हाल CAP11XX_REG_SENOR_DELTA(3):
	हाल CAP11XX_REG_SENOR_DELTA(4):
	हाल CAP11XX_REG_SENOR_DELTA(5):
	हाल CAP11XX_REG_PRODUCT_ID:
	हाल CAP11XX_REG_MANUFACTURER_ID:
	हाल CAP11XX_REG_REVISION:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config cap11xx_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CAP11XX_REG_REVISION,
	.reg_शेषs = cap11xx_reg_शेषs,

	.num_reg_शेषs = ARRAY_SIZE(cap11xx_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = cap11xx_अस्थिर_reg,
पूर्ण;

अटल irqवापस_t cap11xx_thपढ़ो_func(पूर्णांक irq_num, व्योम *data)
अणु
	काष्ठा cap11xx_priv *priv = data;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret, i;

	/*
	 * Deनिश्चित पूर्णांकerrupt. This needs to be करोne beक्रमe पढ़ोing the status
	 * रेजिस्टरs, which will not carry valid values otherwise.
	 */
	ret = regmap_update_bits(priv->regmap, CAP11XX_REG_MAIN_CONTROL, 1, 0);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_पढ़ो(priv->regmap, CAP11XX_REG_SENSOR_INPUT, &status);
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < priv->idev->keycodemax; i++)
		input_report_key(priv->idev, priv->keycodes[i],
				 status & (1 << i));

	input_sync(priv->idev);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cap11xx_set_sleep(काष्ठा cap11xx_priv *priv, bool sleep)
अणु
	/*
	 * DLSEEP mode will turn off all LEDS, prevent this
	 */
	अगर (IS_ENABLED(CONFIG_LEDS_CLASS) && priv->num_leds)
		वापस 0;

	वापस regmap_update_bits(priv->regmap, CAP11XX_REG_MAIN_CONTROL,
				  CAP11XX_REG_MAIN_CONTROL_DLSEEP,
				  sleep ? CAP11XX_REG_MAIN_CONTROL_DLSEEP : 0);
पूर्ण

अटल पूर्णांक cap11xx_input_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा cap11xx_priv *priv = input_get_drvdata(idev);

	वापस cap11xx_set_sleep(priv, false);
पूर्ण

अटल व्योम cap11xx_input_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा cap11xx_priv *priv = input_get_drvdata(idev);

	cap11xx_set_sleep(priv, true);
पूर्ण

#अगर_घोषित CONFIG_LEDS_CLASS
अटल पूर्णांक cap11xx_led_set(काष्ठा led_classdev *cdev,
			    क्रमागत led_brightness value)
अणु
	काष्ठा cap11xx_led *led = container_of(cdev, काष्ठा cap11xx_led, cdev);
	काष्ठा cap11xx_priv *priv = led->priv;

	/*
	 * All LEDs share the same duty cycle as this is a HW
	 * limitation. Brightness levels per LED are either
	 * 0 (OFF) and 1 (ON).
	 */
	वापस regmap_update_bits(priv->regmap,
				  CAP11XX_REG_LED_OUTPUT_CONTROL,
				  BIT(led->reg),
				  value ? BIT(led->reg) : 0);
पूर्ण

अटल पूर्णांक cap11xx_init_leds(काष्ठा device *dev,
			     काष्ठा cap11xx_priv *priv, पूर्णांक num_leds)
अणु
	काष्ठा device_node *node = dev->of_node, *child;
	काष्ठा cap11xx_led *led;
	पूर्णांक cnt = of_get_child_count(node);
	पूर्णांक error;

	अगर (!num_leds || !cnt)
		वापस 0;

	अगर (cnt > num_leds)
		वापस -EINVAL;

	led = devm_kसुस्मृति(dev, cnt, माप(काष्ठा cap11xx_led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	priv->leds = led;

	error = regmap_update_bits(priv->regmap,
				CAP11XX_REG_LED_OUTPUT_CONTROL, 0xff, 0);
	अगर (error)
		वापस error;

	error = regmap_update_bits(priv->regmap, CAP11XX_REG_LED_DUTY_CYCLE_4,
				CAP11XX_REG_LED_DUTY_MAX_MASK,
				CAP11XX_REG_LED_DUTY_MAX_VALUE <<
				CAP11XX_REG_LED_DUTY_MAX_MASK_SHIFT);
	अगर (error)
		वापस error;

	क्रम_each_child_of_node(node, child) अणु
		u32 reg;

		led->cdev.name =
			of_get_property(child, "label", शून्य) ? : child->name;
		led->cdev.शेष_trigger =
			of_get_property(child, "linux,default-trigger", शून्य);
		led->cdev.flags = 0;
		led->cdev.brightness_set_blocking = cap11xx_led_set;
		led->cdev.max_brightness = 1;
		led->cdev.brightness = LED_OFF;

		error = of_property_पढ़ो_u32(child, "reg", &reg);
		अगर (error != 0 || reg >= num_leds) अणु
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण

		led->reg = reg;
		led->priv = priv;

		error = devm_led_classdev_रेजिस्टर(dev, &led->cdev);
		अगर (error) अणु
			of_node_put(child);
			वापस error;
		पूर्ण

		priv->num_leds++;
		led++;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक cap11xx_init_leds(काष्ठा device *dev,
			     काष्ठा cap11xx_priv *priv, पूर्णांक num_leds)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cap11xx_i2c_probe(काष्ठा i2c_client *i2c_client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c_client->dev;
	काष्ठा cap11xx_priv *priv;
	काष्ठा device_node *node;
	स्थिर काष्ठा cap11xx_hw_model *cap;
	पूर्णांक i, error, irq, gain = 0;
	अचिन्हित पूर्णांक val, rev;
	u32 gain32;

	अगर (id->driver_data >= ARRAY_SIZE(cap11xx_devices)) अणु
		dev_err(dev, "Invalid device ID %lu\n", id->driver_data);
		वापस -EINVAL;
	पूर्ण

	cap = &cap11xx_devices[id->driver_data];
	अगर (!cap || !cap->num_channels) अणु
		dev_err(dev, "Invalid device configuration\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(dev,
			    काष्ठा_size(priv, keycodes, cap->num_channels),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = devm_regmap_init_i2c(i2c_client, &cap11xx_regmap_config);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	error = regmap_पढ़ो(priv->regmap, CAP11XX_REG_PRODUCT_ID, &val);
	अगर (error)
		वापस error;

	अगर (val != cap->product_id) अणु
		dev_err(dev, "Product ID: Got 0x%02x, expected 0x%02x\n",
			val, cap->product_id);
		वापस -ENXIO;
	पूर्ण

	error = regmap_पढ़ो(priv->regmap, CAP11XX_REG_MANUFACTURER_ID, &val);
	अगर (error)
		वापस error;

	अगर (val != CAP11XX_MANUFACTURER_ID) अणु
		dev_err(dev, "Manufacturer ID: Got 0x%02x, expected 0x%02x\n",
			val, CAP11XX_MANUFACTURER_ID);
		वापस -ENXIO;
	पूर्ण

	error = regmap_पढ़ो(priv->regmap, CAP11XX_REG_REVISION, &rev);
	अगर (error < 0)
		वापस error;

	dev_info(dev, "CAP11XX detected, revision 0x%02x\n", rev);
	node = dev->of_node;

	अगर (!of_property_पढ़ो_u32(node, "microchip,sensor-gain", &gain32)) अणु
		अगर (is_घातer_of_2(gain32) && gain32 <= 8)
			gain = ilog2(gain32);
		अन्यथा
			dev_err(dev, "Invalid sensor-gain value %d\n", gain32);
	पूर्ण

	अगर (of_property_पढ़ो_bool(node, "microchip,irq-active-high")) अणु
		error = regmap_update_bits(priv->regmap, CAP11XX_REG_CONFIG2,
					   CAP11XX_REG_CONFIG2_ALT_POL, 0);
		अगर (error)
			वापस error;
	पूर्ण

	/* Provide some useful शेषs */
	क्रम (i = 0; i < cap->num_channels; i++)
		priv->keycodes[i] = KEY_A + i;

	of_property_पढ़ो_u32_array(node, "linux,keycodes",
				   priv->keycodes, cap->num_channels);

	error = regmap_update_bits(priv->regmap, CAP11XX_REG_MAIN_CONTROL,
				   CAP11XX_REG_MAIN_CONTROL_GAIN_MASK,
				   gain << CAP11XX_REG_MAIN_CONTROL_GAIN_SHIFT);
	अगर (error)
		वापस error;

	/* Disable स्वतःrepeat. The Linux input प्रणाली has its own handling. */
	error = regmap_ग_लिखो(priv->regmap, CAP11XX_REG_REPEAT_RATE, 0);
	अगर (error)
		वापस error;

	priv->idev = devm_input_allocate_device(dev);
	अगर (!priv->idev)
		वापस -ENOMEM;

	priv->idev->name = "CAP11XX capacitive touch sensor";
	priv->idev->id.bustype = BUS_I2C;
	priv->idev->evbit[0] = BIT_MASK(EV_KEY);

	अगर (of_property_पढ़ो_bool(node, "autorepeat"))
		__set_bit(EV_REP, priv->idev->evbit);

	क्रम (i = 0; i < cap->num_channels; i++)
		__set_bit(priv->keycodes[i], priv->idev->keybit);

	__clear_bit(KEY_RESERVED, priv->idev->keybit);

	priv->idev->keycode = priv->keycodes;
	priv->idev->keycodesize = माप(priv->keycodes[0]);
	priv->idev->keycodemax = cap->num_channels;

	priv->idev->id.venकरोr = CAP11XX_MANUFACTURER_ID;
	priv->idev->id.product = cap->product_id;
	priv->idev->id.version = rev;

	priv->idev->खोलो = cap11xx_input_खोलो;
	priv->idev->बंद = cap11xx_input_बंद;

	error = cap11xx_init_leds(dev, priv, cap->num_leds);
	अगर (error)
		वापस error;

	input_set_drvdata(priv->idev, priv);

	/*
	 * Put the device in deep sleep mode क्रम now.
	 * ->खोलो() will bring it back once the it is actually needed.
	 */
	cap11xx_set_sleep(priv, true);

	error = input_रेजिस्टर_device(priv->idev);
	अगर (error)
		वापस error;

	irq = irq_of_parse_and_map(node, 0);
	अगर (!irq) अणु
		dev_err(dev, "Unable to parse or map IRQ\n");
		वापस -ENXIO;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, irq, शून्य, cap11xx_thपढ़ो_func,
					  IRQF_ONESHOT, dev_name(dev), priv);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cap11xx_dt_ids[] = अणु
	अणु .compatible = "microchip,cap1106", पूर्ण,
	अणु .compatible = "microchip,cap1126", पूर्ण,
	अणु .compatible = "microchip,cap1188", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cap11xx_dt_ids);

अटल स्थिर काष्ठा i2c_device_id cap11xx_i2c_ids[] = अणु
	अणु "cap1106", CAP1106 पूर्ण,
	अणु "cap1126", CAP1126 पूर्ण,
	अणु "cap1188", CAP1188 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cap11xx_i2c_ids);

अटल काष्ठा i2c_driver cap11xx_i2c_driver = अणु
	.driver = अणु
		.name	= "cap11xx",
		.of_match_table = cap11xx_dt_ids,
	पूर्ण,
	.id_table	= cap11xx_i2c_ids,
	.probe		= cap11xx_i2c_probe,
पूर्ण;

module_i2c_driver(cap11xx_i2c_driver);

MODULE_DESCRIPTION("Microchip CAP11XX driver");
MODULE_AUTHOR("Daniel Mack <linux@zonque.org>");
MODULE_LICENSE("GPL v2");
