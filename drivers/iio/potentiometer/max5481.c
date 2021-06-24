<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Maxim Integrated MAX5481-MAX5484 digital potentiometer driver
 * Copyright 2016 Rockwell Collins
 *
 * Datasheet:
 * https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX5481-MAX5484.pdf
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>

/* ग_लिखो wiper reg */
#घोषणा MAX5481_WRITE_WIPER (0 << 4)
/* copy wiper reg to NV reg */
#घोषणा MAX5481_COPY_AB_TO_NV (2 << 4)
/* copy NV reg to wiper reg */
#घोषणा MAX5481_COPY_NV_TO_AB (3 << 4)

#घोषणा MAX5481_MAX_POS    1023

क्रमागत max5481_variant अणु
	max5481,
	max5482,
	max5483,
	max5484,
पूर्ण;

काष्ठा max5481_cfg अणु
	पूर्णांक kohms;
पूर्ण;

अटल स्थिर काष्ठा max5481_cfg max5481_cfg[] = अणु
	[max5481] = अणु .kohms =  10, पूर्ण,
	[max5482] = अणु .kohms =  50, पूर्ण,
	[max5483] = अणु .kohms =  10, पूर्ण,
	[max5484] = अणु .kohms =  50, पूर्ण,
पूर्ण;

काष्ठा max5481_data अणु
	काष्ठा spi_device *spi;
	स्थिर काष्ठा max5481_cfg *cfg;
	u8 msg[3] ____cacheline_aligned;
पूर्ण;

#घोषणा MAX5481_CHANNEL अणु					\
	.type = IIO_RESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = 0,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec max5481_channels[] = अणु
	MAX5481_CHANNEL,
पूर्ण;

अटल पूर्णांक max5481_ग_लिखो_cmd(काष्ठा max5481_data *data, u8 cmd, u16 val)
अणु
	काष्ठा spi_device *spi = data->spi;

	data->msg[0] = cmd;

	चयन (cmd) अणु
	हाल MAX5481_WRITE_WIPER:
		data->msg[1] = val >> 2;
		data->msg[2] = (val & 0x3) << 6;
		वापस spi_ग_लिखो(spi, data->msg, 3);

	हाल MAX5481_COPY_AB_TO_NV:
	हाल MAX5481_COPY_NV_TO_AB:
		वापस spi_ग_लिखो(spi, data->msg, 1);

	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक max5481_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan,
		पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max5481_data *data = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_SCALE)
		वापस -EINVAL;

	*val = 1000 * data->cfg->kohms;
	*val2 = MAX5481_MAX_POS;

	वापस IIO_VAL_FRACTIONAL;
पूर्ण

अटल पूर्णांक max5481_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan,
		पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा max5481_data *data = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	अगर (val < 0 || val > MAX5481_MAX_POS)
		वापस -EINVAL;

	वापस max5481_ग_लिखो_cmd(data, MAX5481_WRITE_WIPER, val);
पूर्ण

अटल स्थिर काष्ठा iio_info max5481_info = अणु
	.पढ़ो_raw = max5481_पढ़ो_raw,
	.ग_लिखो_raw = max5481_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा of_device_id max5481_match[] = अणु
	अणु .compatible = "maxim,max5481", .data = &max5481_cfg[max5481] पूर्ण,
	अणु .compatible = "maxim,max5482", .data = &max5481_cfg[max5482] पूर्ण,
	अणु .compatible = "maxim,max5483", .data = &max5481_cfg[max5483] पूर्ण,
	अणु .compatible = "maxim,max5484", .data = &max5481_cfg[max5484] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max5481_match);

अटल पूर्णांक max5481_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा max5481_data *data;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	spi_set_drvdata(spi, indio_dev);
	data = iio_priv(indio_dev);

	data->spi = spi;

	data->cfg = device_get_match_data(&spi->dev);
	अगर (!data->cfg)
		data->cfg = &max5481_cfg[id->driver_data];

	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	/* variant specअगरic configuration */
	indio_dev->info = &max5481_info;
	indio_dev->channels = max5481_channels;
	indio_dev->num_channels = ARRAY_SIZE(max5481_channels);

	/* restore wiper from NV */
	ret = max5481_ग_लिखो_cmd(data, MAX5481_COPY_NV_TO_AB, 0);
	अगर (ret < 0)
		वापस ret;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक max5481_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा max5481_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	/* save wiper reg to NV reg */
	वापस max5481_ग_लिखो_cmd(data, MAX5481_COPY_AB_TO_NV, 0);
पूर्ण

अटल स्थिर काष्ठा spi_device_id max5481_id_table[] = अणु
	अणु "max5481", max5481 पूर्ण,
	अणु "max5482", max5482 पूर्ण,
	अणु "max5483", max5483 पूर्ण,
	अणु "max5484", max5484 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, max5481_id_table);

अटल काष्ठा spi_driver max5481_driver = अणु
	.driver = अणु
		.name  = "max5481",
		.of_match_table = max5481_match,
	पूर्ण,
	.probe = max5481_probe,
	.हटाओ = max5481_हटाओ,
	.id_table = max5481_id_table,
पूर्ण;

module_spi_driver(max5481_driver);

MODULE_AUTHOR("Maury Anderson <maury.anderson@rockwellcollins.com>");
MODULE_DESCRIPTION("max5481 SPI driver");
MODULE_LICENSE("GPL v2");
