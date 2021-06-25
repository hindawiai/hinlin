<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * AD7816 digital temperature sensor driver supporting AD7816/7/8
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/list.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

/*
 * AD7816 config masks
 */
#घोषणा AD7816_FULL			0x1
#घोषणा AD7816_PD			0x2
#घोषणा AD7816_CS_MASK			0x7
#घोषणा AD7816_CS_MAX			0x4

/*
 * AD7816 temperature masks
 */
#घोषणा AD7816_VALUE_OFFSET		6
#घोषणा AD7816_BOUND_VALUE_BASE		0x8
#घोषणा AD7816_BOUND_VALUE_MIN		-95
#घोषणा AD7816_BOUND_VALUE_MAX		152
#घोषणा AD7816_TEMP_FLOAT_OFFSET	2
#घोषणा AD7816_TEMP_FLOAT_MASK		0x3

/*
 * काष्ठा ad7816_chip_info - chip specअगरic inक्रमmation
 */

काष्ठा ad7816_chip_info अणु
	kernel_uदीर्घ_t id;
	काष्ठा spi_device *spi_dev;
	काष्ठा gpio_desc *rdwr_pin;
	काष्ठा gpio_desc *convert_pin;
	काष्ठा gpio_desc *busy_pin;
	u8  oti_data[AD7816_CS_MAX + 1];
	u8  channel_id;	/* 0 always be temperature */
	u8  mode;
पूर्ण;

क्रमागत ad7816_type अणु
	ID_AD7816,
	ID_AD7817,
	ID_AD7818,
पूर्ण;

/*
 * ad7816 data access by SPI
 */
अटल पूर्णांक ad7816_spi_पढ़ो(काष्ठा ad7816_chip_info *chip, u16 *data)
अणु
	काष्ठा spi_device *spi_dev = chip->spi_dev;
	पूर्णांक ret;
	__be16 buf;

	gpiod_set_value(chip->rdwr_pin, 1);
	gpiod_set_value(chip->rdwr_pin, 0);
	ret = spi_ग_लिखो(spi_dev, &chip->channel_id, माप(chip->channel_id));
	अगर (ret < 0) अणु
		dev_err(&spi_dev->dev, "SPI channel setting error\n");
		वापस ret;
	पूर्ण
	gpiod_set_value(chip->rdwr_pin, 1);

	अगर (chip->mode == AD7816_PD) अणु /* operating mode 2 */
		gpiod_set_value(chip->convert_pin, 1);
		gpiod_set_value(chip->convert_pin, 0);
	पूर्ण अन्यथा अणु /* operating mode 1 */
		gpiod_set_value(chip->convert_pin, 0);
		gpiod_set_value(chip->convert_pin, 1);
	पूर्ण

	अगर (chip->id == ID_AD7816 || chip->id == ID_AD7817) अणु
		जबतक (gpiod_get_value(chip->busy_pin))
			cpu_relax();
	पूर्ण

	gpiod_set_value(chip->rdwr_pin, 0);
	gpiod_set_value(chip->rdwr_pin, 1);
	ret = spi_पढ़ो(spi_dev, &buf, माप(*data));
	अगर (ret < 0) अणु
		dev_err(&spi_dev->dev, "SPI data read error\n");
		वापस ret;
	पूर्ण

	*data = be16_to_cpu(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7816_spi_ग_लिखो(काष्ठा ad7816_chip_info *chip, u8 data)
अणु
	काष्ठा spi_device *spi_dev = chip->spi_dev;
	पूर्णांक ret;

	gpiod_set_value(chip->rdwr_pin, 1);
	gpiod_set_value(chip->rdwr_pin, 0);
	ret = spi_ग_लिखो(spi_dev, &data, माप(data));
	अगर (ret < 0)
		dev_err(&spi_dev->dev, "SPI oti data write error\n");

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ad7816_show_mode(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7816_chip_info *chip = iio_priv(indio_dev);

	अगर (chip->mode)
		वापस प्र_लिखो(buf, "power-save\n");
	वापस प्र_लिखो(buf, "full\n");
पूर्ण

अटल sमाप_प्रकार ad7816_store_mode(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf,
				 माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7816_chip_info *chip = iio_priv(indio_dev);

	अगर (म_भेद(buf, "full")) अणु
		gpiod_set_value(chip->rdwr_pin, 1);
		chip->mode = AD7816_FULL;
	पूर्ण अन्यथा अणु
		gpiod_set_value(chip->rdwr_pin, 0);
		chip->mode = AD7816_PD;
	पूर्ण

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(mode, 0644,
		ad7816_show_mode,
		ad7816_store_mode,
		0);

अटल sमाप_प्रकार ad7816_show_available_modes(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "full\npower-save\n");
पूर्ण

अटल IIO_DEVICE_ATTR(available_modes, 0444, ad7816_show_available_modes,
			शून्य, 0);

अटल sमाप_प्रकार ad7816_show_channel(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7816_chip_info *chip = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%d\n", chip->channel_id);
पूर्ण

अटल sमाप_प्रकार ad7816_store_channel(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf,
				    माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7816_chip_info *chip = iio_priv(indio_dev);
	अचिन्हित दीर्घ data;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &data);
	अगर (ret)
		वापस ret;

	अगर (data > AD7816_CS_MAX && data != AD7816_CS_MASK) अणु
		dev_err(&chip->spi_dev->dev, "Invalid channel id %lu for %s.\n",
			data, indio_dev->name);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (म_भेद(indio_dev->name, "ad7818") == 0 && data > 1) अणु
		dev_err(&chip->spi_dev->dev,
			"Invalid channel id %lu for ad7818.\n", data);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (म_भेद(indio_dev->name, "ad7816") == 0 && data > 0) अणु
		dev_err(&chip->spi_dev->dev,
			"Invalid channel id %lu for ad7816.\n", data);
		वापस -EINVAL;
	पूर्ण

	chip->channel_id = data;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(channel, 0644,
		ad7816_show_channel,
		ad7816_store_channel,
		0);

अटल sमाप_प्रकार ad7816_show_value(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7816_chip_info *chip = iio_priv(indio_dev);
	u16 data;
	s8 value;
	पूर्णांक ret;

	ret = ad7816_spi_पढ़ो(chip, &data);
	अगर (ret)
		वापस -EIO;

	data >>= AD7816_VALUE_OFFSET;

	अगर (chip->channel_id == 0) अणु
		value = (s8)((data >> AD7816_TEMP_FLOAT_OFFSET) - 103);
		data &= AD7816_TEMP_FLOAT_MASK;
		अगर (value < 0)
			data = BIT(AD7816_TEMP_FLOAT_OFFSET) - data;
		वापस प्र_लिखो(buf, "%d.%.2d\n", value, data * 25);
	पूर्ण
	वापस प्र_लिखो(buf, "%u\n", data);
पूर्ण

अटल IIO_DEVICE_ATTR(value, 0444, ad7816_show_value, शून्य, 0);

अटल काष्ठा attribute *ad7816_attributes[] = अणु
	&iio_dev_attr_available_modes.dev_attr.attr,
	&iio_dev_attr_mode.dev_attr.attr,
	&iio_dev_attr_channel.dev_attr.attr,
	&iio_dev_attr_value.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7816_attribute_group = अणु
	.attrs = ad7816_attributes,
पूर्ण;

/*
 * temperature bound events
 */

#घोषणा IIO_EVENT_CODE_AD7816_OTI IIO_UNMOD_EVENT_CODE(IIO_TEMP,	\
						       0,		\
						       IIO_EV_TYPE_THRESH, \
						       IIO_EV_सूची_FALLING)

अटल irqवापस_t ad7816_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	iio_push_event(निजी, IIO_EVENT_CODE_AD7816_OTI,
		       iio_get_समय_ns(निजी));
	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार ad7816_show_oti(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7816_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक value;

	अगर (chip->channel_id > AD7816_CS_MAX) अणु
		dev_err(dev, "Invalid oti channel id %d.\n", chip->channel_id);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (chip->channel_id == 0) अणु
		value = AD7816_BOUND_VALUE_MIN +
			(chip->oti_data[chip->channel_id] -
			AD7816_BOUND_VALUE_BASE);
		वापस प्र_लिखो(buf, "%d\n", value);
	पूर्ण
	वापस प्र_लिखो(buf, "%u\n", chip->oti_data[chip->channel_id]);
पूर्ण

अटल अंतरभूत sमाप_प्रकार ad7816_set_oti(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf,
				     माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7816_chip_info *chip = iio_priv(indio_dev);
	दीर्घ value;
	u8 data;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &value);
	अगर (ret)
		वापस ret;

	अगर (chip->channel_id > AD7816_CS_MAX) अणु
		dev_err(dev, "Invalid oti channel id %d.\n", chip->channel_id);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (chip->channel_id == 0) अणु
		अगर (value < AD7816_BOUND_VALUE_MIN ||
		    value > AD7816_BOUND_VALUE_MAX)
			वापस -EINVAL;

		data = (u8)(value - AD7816_BOUND_VALUE_MIN +
			AD7816_BOUND_VALUE_BASE);
	पूर्ण अन्यथा अणु
		अगर (value < AD7816_BOUND_VALUE_BASE || value > 255)
			वापस -EINVAL;

		data = (u8)value;
	पूर्ण

	ret = ad7816_spi_ग_लिखो(chip, data);
	अगर (ret)
		वापस -EIO;

	chip->oti_data[chip->channel_id] = data;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(oti, 0644,
		       ad7816_show_oti, ad7816_set_oti, 0);

अटल काष्ठा attribute *ad7816_event_attributes[] = अणु
	&iio_dev_attr_oti.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7816_event_attribute_group = अणु
	.attrs = ad7816_event_attributes,
	.name = "events",
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7816_info = अणु
	.attrs = &ad7816_attribute_group,
	.event_attrs = &ad7816_event_attribute_group,
पूर्ण;

/*
 * device probe and हटाओ
 */

अटल पूर्णांक ad7816_probe(काष्ठा spi_device *spi_dev)
अणु
	काष्ठा ad7816_chip_info *chip;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक i, ret;

	indio_dev = devm_iio_device_alloc(&spi_dev->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;
	chip = iio_priv(indio_dev);
	/* this is only used क्रम device removal purposes */
	dev_set_drvdata(&spi_dev->dev, indio_dev);

	chip->spi_dev = spi_dev;
	क्रम (i = 0; i <= AD7816_CS_MAX; i++)
		chip->oti_data[i] = 203;

	chip->id = spi_get_device_id(spi_dev)->driver_data;
	chip->rdwr_pin = devm_gpiod_get(&spi_dev->dev, "rdwr", GPIOD_OUT_HIGH);
	अगर (IS_ERR(chip->rdwr_pin)) अणु
		ret = PTR_ERR(chip->rdwr_pin);
		dev_err(&spi_dev->dev, "Failed to request rdwr GPIO: %d\n",
			ret);
		वापस ret;
	पूर्ण
	chip->convert_pin = devm_gpiod_get(&spi_dev->dev, "convert",
					   GPIOD_OUT_HIGH);
	अगर (IS_ERR(chip->convert_pin)) अणु
		ret = PTR_ERR(chip->convert_pin);
		dev_err(&spi_dev->dev, "Failed to request convert GPIO: %d\n",
			ret);
		वापस ret;
	पूर्ण
	अगर (chip->id == ID_AD7816 || chip->id == ID_AD7817) अणु
		chip->busy_pin = devm_gpiod_get(&spi_dev->dev, "busy",
						GPIOD_IN);
		अगर (IS_ERR(chip->busy_pin)) अणु
			ret = PTR_ERR(chip->busy_pin);
			dev_err(&spi_dev->dev, "Failed to request busy GPIO: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	indio_dev->name = spi_get_device_id(spi_dev)->name;
	indio_dev->info = &ad7816_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (spi_dev->irq) अणु
		/* Only low trigger is supported in ad7816/7/8 */
		ret = devm_request_thपढ़ोed_irq(&spi_dev->dev, spi_dev->irq,
						शून्य,
						&ad7816_event_handler,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						indio_dev->name,
						indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = devm_iio_device_रेजिस्टर(&spi_dev->dev, indio_dev);
	अगर (ret)
		वापस ret;

	dev_info(&spi_dev->dev, "%s temperature sensor and ADC registered.\n",
		 indio_dev->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ad7816_of_match[] = अणु
	अणु .compatible = "adi,ad7816", पूर्ण,
	अणु .compatible = "adi,ad7817", पूर्ण,
	अणु .compatible = "adi,ad7818", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7816_of_match);

अटल स्थिर काष्ठा spi_device_id ad7816_id[] = अणु
	अणु "ad7816", ID_AD7816 पूर्ण,
	अणु "ad7817", ID_AD7817 पूर्ण,
	अणु "ad7818", ID_AD7818 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, ad7816_id);

अटल काष्ठा spi_driver ad7816_driver = अणु
	.driver = अणु
		.name = "ad7816",
		.of_match_table = ad7816_of_match,
	पूर्ण,
	.probe = ad7816_probe,
	.id_table = ad7816_id,
पूर्ण;
module_spi_driver(ad7816_driver);

MODULE_AUTHOR("Sonic Zhang <sonic.zhang@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7816/7/8 digital temperature sensor driver");
MODULE_LICENSE("GPL v2");
