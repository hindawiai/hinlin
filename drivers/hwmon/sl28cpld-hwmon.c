<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sl28cpld hardware monitoring driver
 *
 * Copyright 2020 Kontron Europe GmbH
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>

#घोषणा FAN_INPUT		0x00
#घोषणा   FAN_SCALE_X8		BIT(7)
#घोषणा   FAN_VALUE_MASK	GENMASK(6, 0)

काष्ठा sl28cpld_hwmon अणु
	काष्ठा regmap *regmap;
	u32 offset;
पूर्ण;

अटल umode_t sl28cpld_hwmon_is_visible(स्थिर व्योम *data,
					 क्रमागत hwmon_sensor_types type,
					 u32 attr, पूर्णांक channel)
अणु
	वापस 0444;
पूर्ण

अटल पूर्णांक sl28cpld_hwmon_पढ़ो(काष्ठा device *dev,
			       क्रमागत hwmon_sensor_types type, u32 attr,
			       पूर्णांक channel, दीर्घ *input)
अणु
	काष्ठा sl28cpld_hwmon *hwmon = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	चयन (attr) अणु
	हाल hwmon_fan_input:
		ret = regmap_पढ़ो(hwmon->regmap, hwmon->offset + FAN_INPUT,
				  &value);
		अगर (ret)
			वापस ret;
		/*
		 * The रेजिस्टर has a 7 bit value and 1 bit which indicates the
		 * scale. If the MSB is set, then the lower 7 bit has to be
		 * multiplied by 8, to get the correct पढ़ोing.
		 */
		अगर (value & FAN_SCALE_X8)
			value = FIELD_GET(FAN_VALUE_MASK, value) << 3;

		/*
		 * The counter period is 1000ms and the sysfs specअगरication
		 * says we should asssume 2 pulses per revolution.
		 */
		value *= 60 / 2;

		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	*input = value;
	वापस 0;
पूर्ण

अटल स्थिर u32 sl28cpld_hwmon_fan_config[] = अणु
	HWMON_F_INPUT,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info sl28cpld_hwmon_fan = अणु
	.type = hwmon_fan,
	.config = sl28cpld_hwmon_fan_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *sl28cpld_hwmon_info[] = अणु
	&sl28cpld_hwmon_fan,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops sl28cpld_hwmon_ops = अणु
	.is_visible = sl28cpld_hwmon_is_visible,
	.पढ़ो = sl28cpld_hwmon_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info sl28cpld_hwmon_chip_info = अणु
	.ops = &sl28cpld_hwmon_ops,
	.info = sl28cpld_hwmon_info,
पूर्ण;

अटल पूर्णांक sl28cpld_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sl28cpld_hwmon *hwmon;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret;

	अगर (!pdev->dev.parent)
		वापस -ENODEV;

	hwmon = devm_kzalloc(&pdev->dev, माप(*hwmon), GFP_KERNEL);
	अगर (!hwmon)
		वापस -ENOMEM;

	hwmon->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!hwmon->regmap)
		वापस -ENODEV;

	ret = device_property_पढ़ो_u32(&pdev->dev, "reg", &hwmon->offset);
	अगर (ret)
		वापस -EINVAL;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(&pdev->dev,
				"sl28cpld_hwmon", hwmon,
				&sl28cpld_hwmon_chip_info, शून्य);
	अगर (IS_ERR(hwmon_dev))
		dev_err(&pdev->dev, "failed to register as hwmon device");

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id sl28cpld_hwmon_of_match[] = अणु
	अणु .compatible = "kontron,sl28cpld-fan" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sl28cpld_hwmon_of_match);

अटल काष्ठा platक्रमm_driver sl28cpld_hwmon_driver = अणु
	.probe = sl28cpld_hwmon_probe,
	.driver = अणु
		.name = "sl28cpld-fan",
		.of_match_table = sl28cpld_hwmon_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sl28cpld_hwmon_driver);

MODULE_DESCRIPTION("sl28cpld Hardware Monitoring Driver");
MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_LICENSE("GPL");
