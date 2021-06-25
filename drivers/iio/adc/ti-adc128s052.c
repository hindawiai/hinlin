<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Angelo Compagnucci <angelo.compagnucci@gmail.com>
 *
 * Driver क्रम Texas Instruments' ADC128S052, ADC122S021 and ADC124S021 ADC chip.
 * Datasheets can be found here:
 * https://www.ti.com/lit/ds/symlink/adc128s052.pdf
 * https://www.ti.com/lit/ds/symlink/adc122s021.pdf
 * https://www.ti.com/lit/ds/symlink/adc124s021.pdf
 */

#समावेश <linux/acpi.h>
#समावेश <linux/err.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>

काष्ठा adc128_configuration अणु
	स्थिर काष्ठा iio_chan_spec	*channels;
	u8				num_channels;
पूर्ण;

काष्ठा adc128 अणु
	काष्ठा spi_device *spi;

	काष्ठा regulator *reg;
	काष्ठा mutex lock;

	u8 buffer[2] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक adc128_adc_conversion(काष्ठा adc128 *adc, u8 channel)
अणु
	पूर्णांक ret;

	mutex_lock(&adc->lock);

	adc->buffer[0] = channel << 3;
	adc->buffer[1] = 0;

	ret = spi_ग_लिखो(adc->spi, &adc->buffer, 2);
	अगर (ret < 0) अणु
		mutex_unlock(&adc->lock);
		वापस ret;
	पूर्ण

	ret = spi_पढ़ो(adc->spi, &adc->buffer, 2);

	mutex_unlock(&adc->lock);

	अगर (ret < 0)
		वापस ret;

	वापस ((adc->buffer[0] << 8 | adc->buffer[1]) & 0xFFF);
पूर्ण

अटल पूर्णांक adc128_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा adc128 *adc = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:

		ret = adc128_adc_conversion(adc, channel->channel);
		अगर (ret < 0)
			वापस ret;

		*val = ret;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:

		ret = regulator_get_voltage(adc->reg);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000;
		*val2 = 12;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	शेष:
		वापस -EINVAL;
	पूर्ण

पूर्ण

#घोषणा ADC128_VOLTAGE_CHANNEL(num)	\
	अणु \
		.type = IIO_VOLTAGE, \
		.indexed = 1, \
		.channel = (num), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) \
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adc128s052_channels[] = अणु
	ADC128_VOLTAGE_CHANNEL(0),
	ADC128_VOLTAGE_CHANNEL(1),
	ADC128_VOLTAGE_CHANNEL(2),
	ADC128_VOLTAGE_CHANNEL(3),
	ADC128_VOLTAGE_CHANNEL(4),
	ADC128_VOLTAGE_CHANNEL(5),
	ADC128_VOLTAGE_CHANNEL(6),
	ADC128_VOLTAGE_CHANNEL(7),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adc122s021_channels[] = अणु
	ADC128_VOLTAGE_CHANNEL(0),
	ADC128_VOLTAGE_CHANNEL(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adc124s021_channels[] = अणु
	ADC128_VOLTAGE_CHANNEL(0),
	ADC128_VOLTAGE_CHANNEL(1),
	ADC128_VOLTAGE_CHANNEL(2),
	ADC128_VOLTAGE_CHANNEL(3),
पूर्ण;

अटल स्थिर काष्ठा adc128_configuration adc128_config[] = अणु
	अणु adc128s052_channels, ARRAY_SIZE(adc128s052_channels) पूर्ण,
	अणु adc122s021_channels, ARRAY_SIZE(adc122s021_channels) पूर्ण,
	अणु adc124s021_channels, ARRAY_SIZE(adc124s021_channels) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info adc128_info = अणु
	.पढ़ो_raw = adc128_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक adc128_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	अचिन्हित पूर्णांक config;
	काष्ठा adc128 *adc;
	पूर्णांक ret;

	अगर (dev_fwnode(&spi->dev))
		config = (अचिन्हित दीर्घ) device_get_match_data(&spi->dev);
	अन्यथा
		config = spi_get_device_id(spi)->driver_data;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;

	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &adc128_info;

	indio_dev->channels = adc128_config[config].channels;
	indio_dev->num_channels = adc128_config[config].num_channels;

	adc->reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(adc->reg))
		वापस PTR_ERR(adc->reg);

	ret = regulator_enable(adc->reg);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&adc->lock);

	ret = iio_device_रेजिस्टर(indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक adc128_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा adc128 *adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(adc->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adc128_of_match[] = अणु
	अणु .compatible = "ti,adc128s052", पूर्ण,
	अणु .compatible = "ti,adc122s021", पूर्ण,
	अणु .compatible = "ti,adc122s051", पूर्ण,
	अणु .compatible = "ti,adc122s101", पूर्ण,
	अणु .compatible = "ti,adc124s021", पूर्ण,
	अणु .compatible = "ti,adc124s051", पूर्ण,
	अणु .compatible = "ti,adc124s101", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adc128_of_match);

अटल स्थिर काष्ठा spi_device_id adc128_id[] = अणु
	अणु "adc128s052", 0 पूर्ण,	/* index पूर्णांकo adc128_config */
	अणु "adc122s021",	1 पूर्ण,
	अणु "adc122s051",	1 पूर्ण,
	अणु "adc122s101",	1 पूर्ण,
	अणु "adc124s021", 2 पूर्ण,
	अणु "adc124s051", 2 पूर्ण,
	अणु "adc124s101", 2 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adc128_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id adc128_acpi_match[] = अणु
	अणु "AANT1280", 2 पूर्ण, /* ADC124S021 compatible ACPI ID */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, adc128_acpi_match);
#पूर्ण_अगर

अटल काष्ठा spi_driver adc128_driver = अणु
	.driver = अणु
		.name = "adc128s052",
		.of_match_table = adc128_of_match,
		.acpi_match_table = ACPI_PTR(adc128_acpi_match),
	पूर्ण,
	.probe = adc128_probe,
	.हटाओ = adc128_हटाओ,
	.id_table = adc128_id,
पूर्ण;
module_spi_driver(adc128_driver);

MODULE_AUTHOR("Angelo Compagnucci <angelo.compagnucci@gmail.com>");
MODULE_DESCRIPTION("Texas Instruments ADC128S052");
MODULE_LICENSE("GPL v2");
