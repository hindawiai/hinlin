<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADS8344 16-bit 8-Channel ADC driver
 *
 * Author: Gregory CLEMENT <gregory.clement@bootlin.com>
 *
 * Datasheet: https://www.ti.com/lit/ds/symlink/ads8344.pdf
 */

#समावेश <linux/delay.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#घोषणा ADS8344_START BIT(7)
#घोषणा ADS8344_SINGLE_END BIT(2)
#घोषणा ADS8344_CHANNEL(channel) ((channel) << 4)
#घोषणा ADS8344_CLOCK_INTERNAL 0x2 /* PD1 = 1 and PD0 = 0 */

काष्ठा ads8344 अणु
	काष्ठा spi_device *spi;
	काष्ठा regulator *reg;
	/*
	 * Lock protecting access to adc->tx_buff and rx_buff,
	 * especially from concurrent पढ़ो on sysfs file.
	 */
	काष्ठा mutex lock;

	u8 tx_buf ____cacheline_aligned;
	u8 rx_buf[3];
पूर्ण;

#घोषणा ADS8344_VOLTAGE_CHANNEL(chan, addr)				\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = chan,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.address = addr,					\
	पूर्ण

#घोषणा ADS8344_VOLTAGE_CHANNEL_DIFF(chan1, chan2, addr)		\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = (chan1),					\
		.channel2 = (chan2),					\
		.dअगरferential = 1,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.address = addr,					\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ads8344_channels[] = अणु
	ADS8344_VOLTAGE_CHANNEL(0, 0),
	ADS8344_VOLTAGE_CHANNEL(1, 4),
	ADS8344_VOLTAGE_CHANNEL(2, 1),
	ADS8344_VOLTAGE_CHANNEL(3, 5),
	ADS8344_VOLTAGE_CHANNEL(4, 2),
	ADS8344_VOLTAGE_CHANNEL(5, 6),
	ADS8344_VOLTAGE_CHANNEL(6, 3),
	ADS8344_VOLTAGE_CHANNEL(7, 7),
	ADS8344_VOLTAGE_CHANNEL_DIFF(0, 1, 8),
	ADS8344_VOLTAGE_CHANNEL_DIFF(2, 3, 9),
	ADS8344_VOLTAGE_CHANNEL_DIFF(4, 5, 10),
	ADS8344_VOLTAGE_CHANNEL_DIFF(6, 7, 11),
	ADS8344_VOLTAGE_CHANNEL_DIFF(1, 0, 12),
	ADS8344_VOLTAGE_CHANNEL_DIFF(3, 2, 13),
	ADS8344_VOLTAGE_CHANNEL_DIFF(5, 4, 14),
	ADS8344_VOLTAGE_CHANNEL_DIFF(7, 6, 15),
पूर्ण;

अटल पूर्णांक ads8344_adc_conversion(काष्ठा ads8344 *adc, पूर्णांक channel,
				  bool dअगरferential)
अणु
	काष्ठा spi_device *spi = adc->spi;
	पूर्णांक ret;

	adc->tx_buf = ADS8344_START;
	अगर (!dअगरferential)
		adc->tx_buf |= ADS8344_SINGLE_END;
	adc->tx_buf |= ADS8344_CHANNEL(channel);
	adc->tx_buf |= ADS8344_CLOCK_INTERNAL;

	ret = spi_ग_लिखो(spi, &adc->tx_buf, 1);
	अगर (ret)
		वापस ret;

	udelay(9);

	ret = spi_पढ़ो(spi, adc->rx_buf, माप(adc->rx_buf));
	अगर (ret)
		वापस ret;

	वापस adc->rx_buf[0] << 9 | adc->rx_buf[1] << 1 | adc->rx_buf[2] >> 7;
पूर्ण

अटल पूर्णांक ads8344_पढ़ो_raw(काष्ठा iio_dev *iio,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *value,
			    पूर्णांक *shअगरt, दीर्घ mask)
अणु
	काष्ठा ads8344 *adc = iio_priv(iio);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);
		*value = ads8344_adc_conversion(adc, channel->address,
						channel->dअगरferential);
		mutex_unlock(&adc->lock);
		अगर (*value < 0)
			वापस *value;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*value = regulator_get_voltage(adc->reg);
		अगर (*value < 0)
			वापस *value;

		/* convert regulator output voltage to mV */
		*value /= 1000;
		*shअगरt = 16;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info ads8344_info = अणु
	.पढ़ो_raw = ads8344_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक ads8344_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ads8344 *adc;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;
	mutex_init(&adc->lock);

	indio_dev->name = dev_name(&spi->dev);
	indio_dev->info = &ads8344_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ads8344_channels;
	indio_dev->num_channels = ARRAY_SIZE(ads8344_channels);

	adc->reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(adc->reg))
		वापस PTR_ERR(adc->reg);

	ret = regulator_enable(adc->reg);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, indio_dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		regulator_disable(adc->reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ads8344_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ads8344 *adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(adc->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ads8344_of_match[] = अणु
	अणु .compatible = "ti,ads8344", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ads8344_of_match);

अटल काष्ठा spi_driver ads8344_driver = अणु
	.driver = अणु
		.name = "ads8344",
		.of_match_table = ads8344_of_match,
	पूर्ण,
	.probe = ads8344_probe,
	.हटाओ = ads8344_हटाओ,
पूर्ण;
module_spi_driver(ads8344_driver);

MODULE_AUTHOR("Gregory CLEMENT <gregory.clement@bootlin.com>");
MODULE_DESCRIPTION("ADS8344 driver");
MODULE_LICENSE("GPL");
