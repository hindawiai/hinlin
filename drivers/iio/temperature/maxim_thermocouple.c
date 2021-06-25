<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * maxim_thermocouple.c  - Support क्रम Maxim thermocouple chips
 *
 * Copyright (C) 2016-2018 Matt Ranostay
 * Author: <matt.ranostay@konsulko.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा MAXIM_THERMOCOUPLE_DRV_NAME	"maxim_thermocouple"

क्रमागत अणु
	MAX6675,
	MAX31855,
	MAX31855K,
	MAX31855J,
	MAX31855N,
	MAX31855S,
	MAX31855T,
	MAX31855E,
	MAX31855R,
पूर्ण;

अटल स्थिर अक्षर maxim_tc_types[] = अणु
	'K', '?', 'K', 'J', 'N', 'S', 'T', 'E', 'R'
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max6675_channels[] = अणु
	अणु	/* thermocouple temperature */
		.type = IIO_TEMP,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_THERMOCOUPLE_TYPE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 13,
			.storagebits = 16,
			.shअगरt = 3,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max31855_channels[] = अणु
	अणु	/* thermocouple temperature */
		.type = IIO_TEMP,
		.address = 2,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_THERMOCOUPLE_TYPE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 14,
			.storagebits = 16,
			.shअगरt = 2,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	अणु	/* cold junction temperature */
		.type = IIO_TEMP,
		.address = 0,
		.channel2 = IIO_MOD_TEMP_AMBIENT,
		.modअगरied = 1,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 1,
		.scan_type = अणु
			.sign = 's',
			.realbits = 12,
			.storagebits = 16,
			.shअगरt = 4,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ max31855_scan_masks[] = अणु0x3, 0पूर्ण;

काष्ठा maxim_thermocouple_chip अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	स्थिर अचिन्हित दीर्घ *scan_masks;
	u8 num_channels;
	u8 पढ़ो_size;

	/* bit-check क्रम valid input */
	u32 status_bit;
पूर्ण;

अटल स्थिर काष्ठा maxim_thermocouple_chip maxim_thermocouple_chips[] = अणु
	[MAX6675] = अणु
			.channels = max6675_channels,
			.num_channels = ARRAY_SIZE(max6675_channels),
			.पढ़ो_size = 2,
			.status_bit = BIT(2),
		पूर्ण,
	[MAX31855] = अणु
			.channels = max31855_channels,
			.num_channels = ARRAY_SIZE(max31855_channels),
			.पढ़ो_size = 4,
			.scan_masks = max31855_scan_masks,
			.status_bit = BIT(16),
		पूर्ण,
पूर्ण;

काष्ठा maxim_thermocouple_data अणु
	काष्ठा spi_device *spi;
	स्थिर काष्ठा maxim_thermocouple_chip *chip;

	u8 buffer[16] ____cacheline_aligned;
	अक्षर tc_type;
पूर्ण;

अटल पूर्णांक maxim_thermocouple_पढ़ो(काष्ठा maxim_thermocouple_data *data,
				   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक storage_bytes = data->chip->पढ़ो_size;
	अचिन्हित पूर्णांक shअगरt = chan->scan_type.shअगरt + (chan->address * 8);
	__be16 buf16;
	__be32 buf32;
	पूर्णांक ret;

	चयन (storage_bytes) अणु
	हाल 2:
		ret = spi_पढ़ो(data->spi, (व्योम *)&buf16, storage_bytes);
		*val = be16_to_cpu(buf16);
		अवरोध;
	हाल 4:
		ret = spi_पढ़ो(data->spi, (व्योम *)&buf32, storage_bytes);
		*val = be32_to_cpu(buf32);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	/* check to be sure this is a valid पढ़ोing */
	अगर (*val & data->chip->status_bit)
		वापस -EINVAL;

	*val = sign_extend32(*val >> shअगरt, chan->scan_type.realbits - 1);

	वापस 0;
पूर्ण

अटल irqवापस_t maxim_thermocouple_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा maxim_thermocouple_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = spi_पढ़ो(data->spi, data->buffer, data->chip->पढ़ो_size);
	अगर (!ret) अणु
		iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
						   iio_get_समय_ns(indio_dev));
	पूर्ण

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक maxim_thermocouple_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				       काष्ठा iio_chan_spec स्थिर *chan,
				       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा maxim_thermocouple_data *data = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = maxim_thermocouple_पढ़ो(data, chan, val);
		iio_device_release_direct_mode(indio_dev);

		अगर (!ret)
			वापस IIO_VAL_INT;

		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->channel2) अणु
		हाल IIO_MOD_TEMP_AMBIENT:
			*val = 62;
			*val2 = 500000; /* 1000 * 0.0625 */
			ret = IIO_VAL_INT_PLUS_MICRO;
			अवरोध;
		शेष:
			*val = 250; /* 1000 * 0.25 */
			ret = IIO_VAL_INT;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_THERMOCOUPLE_TYPE:
		*val = data->tc_type;
		ret = IIO_VAL_CHAR;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info maxim_thermocouple_info = अणु
	.पढ़ो_raw = maxim_thermocouple_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक maxim_thermocouple_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा iio_dev *indio_dev;
	काष्ठा maxim_thermocouple_data *data;
	स्थिर पूर्णांक chip_type = (id->driver_data == MAX6675) ? MAX6675 : MAX31855;
	स्थिर काष्ठा maxim_thermocouple_chip *chip =
		&maxim_thermocouple_chips[chip_type];
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->info = &maxim_thermocouple_info;
	indio_dev->name = MAXIM_THERMOCOUPLE_DRV_NAME;
	indio_dev->channels = chip->channels;
	indio_dev->available_scan_masks = chip->scan_masks;
	indio_dev->num_channels = chip->num_channels;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	data = iio_priv(indio_dev);
	data->spi = spi;
	data->chip = chip;
	data->tc_type = maxim_tc_types[id->driver_data];

	ret = devm_iio_triggered_buffer_setup(&spi->dev,
				indio_dev, शून्य,
				maxim_thermocouple_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	अगर (id->driver_data == MAX31855)
		dev_warn(&spi->dev, "generic max31855 ID is deprecated\nplease use more specific part type");

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id maxim_thermocouple_id[] = अणु
	अणु"max6675", MAX6675पूर्ण,
	अणु"max31855", MAX31855पूर्ण,
	अणु"max31855k", MAX31855Kपूर्ण,
	अणु"max31855j", MAX31855Jपूर्ण,
	अणु"max31855n", MAX31855Nपूर्ण,
	अणु"max31855s", MAX31855Sपूर्ण,
	अणु"max31855t", MAX31855Tपूर्ण,
	अणु"max31855e", MAX31855Eपूर्ण,
	अणु"max31855r", MAX31855Rपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, maxim_thermocouple_id);

अटल स्थिर काष्ठा of_device_id maxim_thermocouple_of_match[] = अणु
        अणु .compatible = "maxim,max6675" पूर्ण,
        अणु .compatible = "maxim,max31855" पूर्ण,
	अणु .compatible = "maxim,max31855k" पूर्ण,
	अणु .compatible = "maxim,max31855j" पूर्ण,
	अणु .compatible = "maxim,max31855n" पूर्ण,
	अणु .compatible = "maxim,max31855s" पूर्ण,
	अणु .compatible = "maxim,max31855t" पूर्ण,
	अणु .compatible = "maxim,max31855e" पूर्ण,
	अणु .compatible = "maxim,max31855r" पूर्ण,
        अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, maxim_thermocouple_of_match);

अटल काष्ठा spi_driver maxim_thermocouple_driver = अणु
	.driver = अणु
		.name	= MAXIM_THERMOCOUPLE_DRV_NAME,
		.of_match_table = maxim_thermocouple_of_match,
	पूर्ण,
	.probe		= maxim_thermocouple_probe,
	.id_table	= maxim_thermocouple_id,
पूर्ण;
module_spi_driver(maxim_thermocouple_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("Maxim thermocouple sensors");
MODULE_LICENSE("GPL");
