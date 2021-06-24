<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max5487.c - Support क्रम MAX5487, MAX5488, MAX5489 digital potentiometers
 *
 * Copyright (C) 2016 Cristina-Gabriela Moraru <cristina.moraru09@gmail.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/acpi.h>

#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/iपन.स>

#घोषणा MAX5487_WRITE_WIPER_A	(0x01 << 8)
#घोषणा MAX5487_WRITE_WIPER_B	(0x02 << 8)

/* copy both wiper regs to NV regs */
#घोषणा MAX5487_COPY_AB_TO_NV	(0x23 << 8)
/* copy both NV regs to wiper regs */
#घोषणा MAX5487_COPY_NV_TO_AB	(0x33 << 8)

#घोषणा MAX5487_MAX_POS		255

काष्ठा max5487_data अणु
	काष्ठा spi_device *spi;
	पूर्णांक kohms;
पूर्ण;

#घोषणा MAX5487_CHANNEL(ch, addr) अणु				\
	.type = IIO_RESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = ch,						\
	.address = addr,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec max5487_channels[] = अणु
	MAX5487_CHANNEL(0, MAX5487_WRITE_WIPER_A),
	MAX5487_CHANNEL(1, MAX5487_WRITE_WIPER_B),
पूर्ण;

अटल पूर्णांक max5487_ग_लिखो_cmd(काष्ठा spi_device *spi, u16 cmd)
अणु
	वापस spi_ग_लिखो(spi, (स्थिर व्योम *) &cmd, माप(u16));
पूर्ण

अटल पूर्णांक max5487_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max5487_data *data = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_SCALE)
		वापस -EINVAL;

	*val = 1000 * data->kohms;
	*val2 = MAX5487_MAX_POS;

	वापस IIO_VAL_FRACTIONAL;
पूर्ण

अटल पूर्णांक max5487_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा max5487_data *data = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	अगर (val < 0 || val > MAX5487_MAX_POS)
		वापस -EINVAL;

	वापस max5487_ग_लिखो_cmd(data->spi, chan->address | val);
पूर्ण

अटल स्थिर काष्ठा iio_info max5487_info = अणु
	.पढ़ो_raw = max5487_पढ़ो_raw,
	.ग_लिखो_raw = max5487_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक max5487_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा max5487_data *data;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	spi_set_drvdata(spi, indio_dev);
	data = iio_priv(indio_dev);

	data->spi = spi;
	data->kohms = id->driver_data;

	indio_dev->info = &max5487_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = max5487_channels;
	indio_dev->num_channels = ARRAY_SIZE(max5487_channels);

	/* restore both wiper regs from NV regs */
	ret = max5487_ग_लिखो_cmd(data->spi, MAX5487_COPY_NV_TO_AB);
	अगर (ret < 0)
		वापस ret;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक max5487_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);

	iio_device_unरेजिस्टर(indio_dev);

	/* save both wiper regs to NV regs */
	वापस max5487_ग_लिखो_cmd(spi, MAX5487_COPY_AB_TO_NV);
पूर्ण

अटल स्थिर काष्ठा spi_device_id max5487_id[] = अणु
	अणु "MAX5487", 10 पूर्ण,
	अणु "MAX5488", 50 पूर्ण,
	अणु "MAX5489", 100 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, max5487_id);

अटल स्थिर काष्ठा acpi_device_id max5487_acpi_match[] = अणु
	अणु "MAX5487", 10 पूर्ण,
	अणु "MAX5488", 50 पूर्ण,
	अणु "MAX5489", 100 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, max5487_acpi_match);

अटल काष्ठा spi_driver max5487_driver = अणु
	.driver = अणु
		.name = "max5487",
		.acpi_match_table = ACPI_PTR(max5487_acpi_match),
	पूर्ण,
	.id_table = max5487_id,
	.probe = max5487_spi_probe,
	.हटाओ = max5487_spi_हटाओ
पूर्ण;
module_spi_driver(max5487_driver);

MODULE_AUTHOR("Cristina-Gabriela Moraru <cristina.moraru09@gmail.com>");
MODULE_DESCRIPTION("max5487 SPI driver");
MODULE_LICENSE("GPL v2");
