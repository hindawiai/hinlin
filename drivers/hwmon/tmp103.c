<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Texas Instruments TMP103 SMBus temperature sensor driver
 * Copyright (C) 2014 Heiko Schocher <hs@denx.de>
 *
 * Based on:
 * Texas Instruments TMP102 SMBus temperature sensor driver
 *
 * Copyright (C) 2010 Steven King <sfking@fdwdc.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/regmap.h>

#घोषणा TMP103_TEMP_REG		0x00
#घोषणा TMP103_CONF_REG		0x01
#घोषणा TMP103_TLOW_REG		0x02
#घोषणा TMP103_THIGH_REG	0x03

#घोषणा TMP103_CONF_M0		0x01
#घोषणा TMP103_CONF_M1		0x02
#घोषणा TMP103_CONF_LC		0x04
#घोषणा TMP103_CONF_FL		0x08
#घोषणा TMP103_CONF_FH		0x10
#घोषणा TMP103_CONF_CR0		0x20
#घोषणा TMP103_CONF_CR1		0x40
#घोषणा TMP103_CONF_ID		0x80
#घोषणा TMP103_CONF_SD		(TMP103_CONF_M1)
#घोषणा TMP103_CONF_SD_MASK	(TMP103_CONF_M0 | TMP103_CONF_M1)

#घोषणा TMP103_CONFIG		(TMP103_CONF_CR1 | TMP103_CONF_M1)
#घोषणा TMP103_CONFIG_MASK	(TMP103_CONF_CR0 | TMP103_CONF_CR1 | \
				 TMP103_CONF_M0 | TMP103_CONF_M1)

अटल अंतरभूत पूर्णांक पंचांगp103_reg_to_mc(s8 val)
अणु
	वापस val * 1000;
पूर्ण

अटल अंतरभूत u8 पंचांगp103_mc_to_reg(पूर्णांक val)
अणु
	वापस DIV_ROUND_CLOSEST(val, 1000);
पूर्ण

अटल sमाप_प्रकार पंचांगp103_temp_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, sda->index, &regval);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", पंचांगp103_reg_to_mc(regval));
पूर्ण

अटल sमाप_प्रकार पंचांगp103_temp_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	काष्ठा regmap *regmap = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	val = clamp_val(val, -55000, 127000);
	ret = regmap_ग_लिखो(regmap, sda->index, पंचांगp103_mc_to_reg(val));
	वापस ret ? ret : count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, पंचांगp103_temp, TMP103_TEMP_REG);

अटल SENSOR_DEVICE_ATTR_RW(temp1_min, पंचांगp103_temp, TMP103_TLOW_REG);

अटल SENSOR_DEVICE_ATTR_RW(temp1_max, पंचांगp103_temp, TMP103_THIGH_REG);

अटल काष्ठा attribute *पंचांगp103_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(पंचांगp103);

अटल bool पंचांगp103_regmap_is_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == TMP103_TEMP_REG;
पूर्ण

अटल स्थिर काष्ठा regmap_config पंचांगp103_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = TMP103_THIGH_REG,
	.अस्थिर_reg = पंचांगp103_regmap_is_अस्थिर,
पूर्ण;

अटल पूर्णांक पंचांगp103_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = devm_regmap_init_i2c(client, &पंचांगp103_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	ret = regmap_update_bits(regmap, TMP103_CONF_REG, TMP103_CONFIG_MASK,
				 TMP103_CONFIG);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "error writing config register\n");
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, regmap);
	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
						      regmap, पंचांगp103_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल पूर्णांक __maybe_unused पंचांगp103_suspend(काष्ठा device *dev)
अणु
	काष्ठा regmap *regmap = dev_get_drvdata(dev);

	वापस regmap_update_bits(regmap, TMP103_CONF_REG,
				  TMP103_CONF_SD_MASK, 0);
पूर्ण

अटल पूर्णांक __maybe_unused पंचांगp103_resume(काष्ठा device *dev)
अणु
	काष्ठा regmap *regmap = dev_get_drvdata(dev);

	वापस regmap_update_bits(regmap, TMP103_CONF_REG,
				  TMP103_CONF_SD_MASK, TMP103_CONF_SD);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(पंचांगp103_dev_pm_ops, पंचांगp103_suspend, पंचांगp103_resume);

अटल स्थिर काष्ठा i2c_device_id पंचांगp103_id[] = अणु
	अणु "tmp103", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पंचांगp103_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused पंचांगp103_of_match[] = अणु
	अणु .compatible = "ti,tmp103" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, पंचांगp103_of_match);

अटल काष्ठा i2c_driver पंचांगp103_driver = अणु
	.driver = अणु
		.name	= "tmp103",
		.of_match_table = of_match_ptr(पंचांगp103_of_match),
		.pm	= &पंचांगp103_dev_pm_ops,
	पूर्ण,
	.probe_new	= पंचांगp103_probe,
	.id_table	= पंचांगp103_id,
पूर्ण;

module_i2c_driver(पंचांगp103_driver);

MODULE_AUTHOR("Heiko Schocher <hs@denx.de>");
MODULE_DESCRIPTION("Texas Instruments TMP103 temperature sensor driver");
MODULE_LICENSE("GPL");
