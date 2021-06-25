<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DAC7612 Dual, 12-Bit Serial input Digital-to-Analog Converter
 *
 * Copyright 2019 Qtechnology A/S
 * 2019 Ricarकरो Ribalda <ribalda@kernel.org>
 *
 * Licensed under the GPL-2.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/iपन.स>

#घोषणा DAC7612_RESOLUTION 12
#घोषणा DAC7612_ADDRESS 4
#घोषणा DAC7612_START 5

काष्ठा dac7612 अणु
	काष्ठा spi_device *spi;
	काष्ठा gpio_desc *loaddacs;
	uपूर्णांक16_t cache[2];

	/*
	 * Lock to protect the state of the device from potential concurrent
	 * ग_लिखो accesses from userspace. The ग_लिखो operation requires an
	 * SPI ग_लिखो, then toggling of a GPIO, so the lock aims to protect
	 * the sanity of the entire sequence of operation.
	 */
	काष्ठा mutex lock;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	uपूर्णांक8_t data[2] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक dac7612_cmd_single(काष्ठा dac7612 *priv, पूर्णांक channel, u16 val)
अणु
	पूर्णांक ret;

	priv->data[0] = BIT(DAC7612_START) | (channel << DAC7612_ADDRESS);
	priv->data[0] |= val >> 8;
	priv->data[1] = val & 0xff;

	priv->cache[channel] = val;

	ret = spi_ग_लिखो(priv->spi, priv->data, माप(priv->data));
	अगर (ret)
		वापस ret;

	gpiod_set_value(priv->loaddacs, 1);
	gpiod_set_value(priv->loaddacs, 0);

	वापस 0;
पूर्ण

#घोषणा dac7612_CHANNEL(chan, name) अणु				\
	.type = IIO_VOLTAGE,					\
	.channel = (chan),					\
	.indexed = 1,						\
	.output = 1,						\
	.datasheet_name = name,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec dac7612_channels[] = अणु
	dac7612_CHANNEL(0, "OUTA"),
	dac7612_CHANNEL(1, "OUTB"),
पूर्ण;

अटल पूर्णांक dac7612_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा dac7612 *priv;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		priv = iio_priv(iio_dev);
		*val = priv->cache[chan->channel];
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = 1;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dac7612_ग_लिखो_raw(काष्ठा iio_dev *iio_dev,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा dac7612 *priv = iio_priv(iio_dev);
	पूर्णांक ret;

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	अगर ((val >= BIT(DAC7612_RESOLUTION)) || val < 0 || val2)
		वापस -EINVAL;

	अगर (val == priv->cache[chan->channel])
		वापस 0;

	mutex_lock(&priv->lock);
	ret = dac7612_cmd_single(priv, chan->channel, val);
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info dac7612_info = अणु
	.पढ़ो_raw = dac7612_पढ़ो_raw,
	.ग_लिखो_raw = dac7612_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक dac7612_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *iio_dev;
	काष्ठा dac7612 *priv;
	पूर्णांक i;
	पूर्णांक ret;

	iio_dev = devm_iio_device_alloc(&spi->dev, माप(*priv));
	अगर (!iio_dev)
		वापस -ENOMEM;

	priv = iio_priv(iio_dev);
	/*
	 * LOADDACS pin can be controlled by the driver or बाह्यally.
	 * When controlled by the driver, the DAC value is updated after
	 * every ग_लिखो.
	 * When the driver करोes not control the PIN, the user or an बाह्यal
	 * event can change the value of all DACs by pulsing करोwn the LOADDACs
	 * pin.
	 */
	priv->loaddacs = devm_gpiod_get_optional(&spi->dev, "ti,loaddacs",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->loaddacs))
		वापस PTR_ERR(priv->loaddacs);
	priv->spi = spi;
	spi_set_drvdata(spi, iio_dev);
	iio_dev->info = &dac7612_info;
	iio_dev->modes = INDIO_सूचीECT_MODE;
	iio_dev->channels = dac7612_channels;
	iio_dev->num_channels = ARRAY_SIZE(priv->cache);
	iio_dev->name = spi_get_device_id(spi)->name;

	mutex_init(&priv->lock);

	क्रम (i = 0; i < ARRAY_SIZE(priv->cache); i++) अणु
		ret = dac7612_cmd_single(priv, i, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&spi->dev, iio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id dac7612_id[] = अणु
	अणु"ti-dac7612"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, dac7612_id);

अटल स्थिर काष्ठा of_device_id dac7612_of_match[] = अणु
	अणु .compatible = "ti,dac7612" पूर्ण,
	अणु .compatible = "ti,dac7612u" पूर्ण,
	अणु .compatible = "ti,dac7612ub" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dac7612_of_match);

अटल काष्ठा spi_driver dac7612_driver = अणु
	.driver = अणु
		   .name = "ti-dac7612",
		   .of_match_table = dac7612_of_match,
		   पूर्ण,
	.probe = dac7612_probe,
	.id_table = dac7612_id,
पूर्ण;
module_spi_driver(dac7612_driver);

MODULE_AUTHOR("Ricardo Ribalda <ribalda@kernel.org>");
MODULE_DESCRIPTION("Texas Instruments DAC7612 DAC driver");
MODULE_LICENSE("GPL v2");
