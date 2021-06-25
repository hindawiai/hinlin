<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// TI LM36274 LED chip family driver
// Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com/

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/leds.h>
#समावेश <linux/leds-ti-lmu-common.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/ti-lmu.h>
#समावेश <linux/mfd/ti-lmu-रेजिस्टर.h>

#समावेश <uapi/linux/uleds.h>

#घोषणा LM36274_MAX_STRINGS	4
#घोषणा LM36274_BL_EN		BIT(4)

/**
 * काष्ठा lm36274
 * @pdev: platक्रमm device
 * @led_dev: led class device
 * @lmu_data: Register and setting values क्रम common code
 * @regmap: Devices रेजिस्टर map
 * @dev: Poपूर्णांकer to the devices device काष्ठा
 * @led_sources: The LED strings supported in this array
 * @num_leds: Number of LED strings are supported in this array
 */
काष्ठा lm36274 अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा led_classdev led_dev;
	काष्ठा ti_lmu_bank lmu_data;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;

	u32 led_sources[LM36274_MAX_STRINGS];
	पूर्णांक num_leds;
पूर्ण;

अटल पूर्णांक lm36274_brightness_set(काष्ठा led_classdev *led_cdev,
				  क्रमागत led_brightness brt_val)
अणु
	काष्ठा lm36274 *chip = container_of(led_cdev, काष्ठा lm36274, led_dev);

	वापस ti_lmu_common_set_brightness(&chip->lmu_data, brt_val);
पूर्ण

अटल पूर्णांक lm36274_init(काष्ठा lm36274 *chip)
अणु
	पूर्णांक enable_val = 0;
	पूर्णांक i;

	क्रम (i = 0; i < chip->num_leds; i++)
		enable_val |= (1 << chip->led_sources[i]);

	अगर (!enable_val) अणु
		dev_err(chip->dev, "No LEDs were enabled\n");
		वापस -EINVAL;
	पूर्ण

	enable_val |= LM36274_BL_EN;

	वापस regmap_ग_लिखो(chip->regmap, LM36274_REG_BL_EN, enable_val);
पूर्ण

अटल पूर्णांक lm36274_parse_dt(काष्ठा lm36274 *chip,
			    काष्ठा led_init_data *init_data)
अणु
	काष्ठा device *dev = chip->dev;
	काष्ठा fwnode_handle *child;
	पूर्णांक ret;

	/* There should only be 1 node */
	अगर (device_get_child_node_count(dev) != 1)
		वापस -EINVAL;

	child = device_get_next_child_node(dev, शून्य);

	init_data->fwnode = child;
	init_data->devicename = chip->pdev->name;
	/* क्रम backwards compatibility when `label` property is not present */
	init_data->शेष_label = ":";

	chip->num_leds = fwnode_property_count_u32(child, "led-sources");
	अगर (chip->num_leds <= 0) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32_array(child, "led-sources",
					     chip->led_sources, chip->num_leds);
	अगर (ret) अणु
		dev_err(dev, "led-sources property missing\n");
		जाओ err;
	पूर्ण

	वापस 0;
err:
	fwnode_handle_put(child);
	वापस ret;
पूर्ण

अटल पूर्णांक lm36274_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_lmu *lmu = dev_get_drvdata(pdev->dev.parent);
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा lm36274 *chip;
	पूर्णांक ret;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->pdev = pdev;
	chip->dev = &pdev->dev;
	chip->regmap = lmu->regmap;
	platक्रमm_set_drvdata(pdev, chip);

	ret = lm36274_parse_dt(chip, &init_data);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to parse DT node\n");
		वापस ret;
	पूर्ण

	ret = lm36274_init(chip);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to init the device\n");
		वापस ret;
	पूर्ण

	chip->lmu_data.regmap = chip->regmap;
	chip->lmu_data.max_brightness = MAX_BRIGHTNESS_11BIT;
	chip->lmu_data.msb_brightness_reg = LM36274_REG_BRT_MSB;
	chip->lmu_data.lsb_brightness_reg = LM36274_REG_BRT_LSB;

	chip->led_dev.max_brightness = MAX_BRIGHTNESS_11BIT;
	chip->led_dev.brightness_set_blocking = lm36274_brightness_set;

	ret = devm_led_classdev_रेजिस्टर_ext(chip->dev, &chip->led_dev,
					     &init_data);
	अगर (ret)
		dev_err(chip->dev, "Failed to register LED for node %pfw\n",
			init_data.fwnode);

	fwnode_handle_put(init_data.fwnode);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_lm36274_leds_match[] = अणु
	अणु .compatible = "ti,lm36274-backlight", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lm36274_leds_match);

अटल काष्ठा platक्रमm_driver lm36274_driver = अणु
	.probe  = lm36274_probe,
	.driver = अणु
		.name = "lm36274-leds",
		.of_match_table = of_lm36274_leds_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lm36274_driver)

MODULE_DESCRIPTION("Texas Instruments LM36274 LED driver");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
