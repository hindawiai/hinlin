<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max31722 - hwmon driver क्रम Maxim Integrated MAX31722/MAX31723 SPI
 * digital thermometer and thermostats.
 *
 * Copyright (c) 2016, Intel Corporation.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#घोषणा MAX31722_REG_CFG				0x00
#घोषणा MAX31722_REG_TEMP_LSB				0x01

#घोषणा MAX31722_MODE_CONTINUOUS			0x00
#घोषणा MAX31722_MODE_STANDBY				0x01
#घोषणा MAX31722_MODE_MASK				0xFE
#घोषणा MAX31722_RESOLUTION_12BIT			0x06
#घोषणा MAX31722_WRITE_MASK				0x80

काष्ठा max31722_data अणु
	काष्ठा device *hwmon_dev;
	काष्ठा spi_device *spi_device;
	u8 mode;
पूर्ण;

अटल पूर्णांक max31722_set_mode(काष्ठा max31722_data *data, u8 mode)
अणु
	पूर्णांक ret;
	काष्ठा spi_device *spi = data->spi_device;
	u8 buf[2] = अणु
		MAX31722_REG_CFG | MAX31722_WRITE_MASK,
		(data->mode & MAX31722_MODE_MASK) | mode
	पूर्ण;

	ret = spi_ग_लिखो(spi, &buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "failed to set sensor mode.\n");
		वापस ret;
	पूर्ण
	data->mode = (data->mode & MAX31722_MODE_MASK) | mode;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार max31722_temp_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार ret;
	काष्ठा max31722_data *data = dev_get_drvdata(dev);

	ret = spi_w8r16(data->spi_device, MAX31722_REG_TEMP_LSB);
	अगर (ret < 0)
		वापस ret;
	/* Keep 12 bits and multiply by the scale of 62.5 millidegrees/bit. */
	वापस प्र_लिखो(buf, "%d\n", (s16)le16_to_cpu(ret) * 125 / 32);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, max31722_temp, 0);

अटल काष्ठा attribute *max31722_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(max31722);

अटल पूर्णांक max31722_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा max31722_data *data;

	data = devm_kzalloc(&spi->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spi_set_drvdata(spi, data);
	data->spi_device = spi;
	/*
	 * Set SD bit to 0 so we can have continuous measurements.
	 * Set resolution to 12 bits क्रम maximum precision.
	 */
	data->mode = MAX31722_MODE_CONTINUOUS | MAX31722_RESOLUTION_12BIT;
	ret = max31722_set_mode(data, MAX31722_MODE_CONTINUOUS);
	अगर (ret < 0)
		वापस ret;

	data->hwmon_dev = hwmon_device_रेजिस्टर_with_groups(&spi->dev,
							    spi->modalias,
							    data,
							    max31722_groups);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		max31722_set_mode(data, MAX31722_MODE_STANDBY);
		वापस PTR_ERR(data->hwmon_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max31722_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा max31722_data *data = spi_get_drvdata(spi);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);

	वापस max31722_set_mode(data, MAX31722_MODE_STANDBY);
पूर्ण

अटल पूर्णांक __maybe_unused max31722_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi_device = to_spi_device(dev);
	काष्ठा max31722_data *data = spi_get_drvdata(spi_device);

	वापस max31722_set_mode(data, MAX31722_MODE_STANDBY);
पूर्ण

अटल पूर्णांक __maybe_unused max31722_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi_device = to_spi_device(dev);
	काष्ठा max31722_data *data = spi_get_drvdata(spi_device);

	वापस max31722_set_mode(data, MAX31722_MODE_CONTINUOUS);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max31722_pm_ops, max31722_suspend, max31722_resume);

अटल स्थिर काष्ठा spi_device_id max31722_spi_id[] = अणु
	अणु"max31722", 0पूर्ण,
	अणु"max31723", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id __maybe_unused max31722_acpi_id[] = अणु
	अणु"MAX31722", 0पूर्ण,
	अणु"MAX31723", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, max31722_spi_id);

अटल काष्ठा spi_driver max31722_driver = अणु
	.driver = अणु
		.name = "max31722",
		.pm = &max31722_pm_ops,
		.acpi_match_table = ACPI_PTR(max31722_acpi_id),
	पूर्ण,
	.probe =            max31722_probe,
	.हटाओ =           max31722_हटाओ,
	.id_table =         max31722_spi_id,
पूर्ण;

module_spi_driver(max31722_driver);

MODULE_AUTHOR("Tiberiu Breana <tiberiu.a.breana@intel.com>");
MODULE_DESCRIPTION("max31722 sensor driver");
MODULE_LICENSE("GPL v2");
