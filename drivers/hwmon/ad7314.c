<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD7314 digital temperature sensor driver क्रम AD7314, ADT7301 and ADT7302
 *
 * Copyright 2010 Analog Devices Inc.
 *
 * Conversion to hwmon from IIO करोne by Jonathan Cameron <jic23@cam.ac.uk>
 */
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/bitops.h>

/*
 * AD7314 temperature masks
 */
#घोषणा AD7314_TEMP_MASK		0x7FE0
#घोषणा AD7314_TEMP_SHIFT		5

/*
 * ADT7301 and ADT7302 temperature masks
 */
#घोषणा ADT7301_TEMP_MASK		0x3FFF

क्रमागत ad7314_variant अणु
	adt7301,
	adt7302,
	ad7314,
पूर्ण;

काष्ठा ad7314_data अणु
	काष्ठा spi_device	*spi_dev;
	u16 rx ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ad7314_spi_पढ़ो(काष्ठा ad7314_data *chip)
अणु
	पूर्णांक ret;

	ret = spi_पढ़ो(chip->spi_dev, (u8 *)&chip->rx, माप(chip->rx));
	अगर (ret < 0) अणु
		dev_err(&chip->spi_dev->dev, "SPI read error\n");
		वापस ret;
	पूर्ण

	वापस be16_to_cpu(chip->rx);
पूर्ण

अटल sमाप_प्रकार ad7314_temperature_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा ad7314_data *chip = dev_get_drvdata(dev);
	s16 data;
	पूर्णांक ret;

	ret = ad7314_spi_पढ़ो(chip);
	अगर (ret < 0)
		वापस ret;
	चयन (spi_get_device_id(chip->spi_dev)->driver_data) अणु
	हाल ad7314:
		data = (ret & AD7314_TEMP_MASK) >> AD7314_TEMP_SHIFT;
		data = sign_extend32(data, 9);

		वापस प्र_लिखो(buf, "%d\n", 250 * data);
	हाल adt7301:
	हाल adt7302:
		/*
		 * Documented as a 13 bit twos complement रेजिस्टर
		 * with a sign bit - which is a 14 bit 2's complement
		 * रेजिस्टर.  1lsb - 31.25 milli degrees centigrade
		 */
		data = ret & ADT7301_TEMP_MASK;
		data = sign_extend32(data, 13);

		वापस प्र_लिखो(buf, "%d\n",
			       DIV_ROUND_CLOSEST(data * 3125, 100));
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, ad7314_temperature, 0);

अटल काष्ठा attribute *ad7314_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(ad7314);

अटल पूर्णांक ad7314_probe(काष्ठा spi_device *spi_dev)
अणु
	काष्ठा ad7314_data *chip;
	काष्ठा device *hwmon_dev;

	chip = devm_kzalloc(&spi_dev->dev, माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	chip->spi_dev = spi_dev;
	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&spi_dev->dev,
							   spi_dev->modalias,
							   chip, ad7314_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7314_id[] = अणु
	अणु "adt7301", adt7301 पूर्ण,
	अणु "adt7302", adt7302 पूर्ण,
	अणु "ad7314", ad7314 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7314_id);

अटल काष्ठा spi_driver ad7314_driver = अणु
	.driver = अणु
		.name = "ad7314",
	पूर्ण,
	.probe = ad7314_probe,
	.id_table = ad7314_id,
पूर्ण;

module_spi_driver(ad7314_driver);

MODULE_AUTHOR("Sonic Zhang <sonic.zhang@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7314, ADT7301 and ADT7302 digital temperature sensor driver");
MODULE_LICENSE("GPL v2");
