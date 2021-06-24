<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ad7949.c - Analog Devices ADC driver 14/16 bits 4/8 channels
 *
 * Copyright (C) 2018 CMC NV
 *
 * https://www.analog.com/media/en/technical-करोcumentation/data-sheets/AD7949.pdf
 */

#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#घोषणा AD7949_MASK_CHANNEL_SEL		GENMASK(9, 7)
#घोषणा AD7949_MASK_TOTAL		GENMASK(13, 0)
#घोषणा AD7949_OFFSET_CHANNEL_SEL	7
#घोषणा AD7949_CFG_READ_BACK		0x1
#घोषणा AD7949_CFG_REG_SIZE_BITS	14

क्रमागत अणु
	ID_AD7949 = 0,
	ID_AD7682,
	ID_AD7689,
पूर्ण;

काष्ठा ad7949_adc_spec अणु
	u8 num_channels;
	u8 resolution;
पूर्ण;

अटल स्थिर काष्ठा ad7949_adc_spec ad7949_adc_spec[] = अणु
	[ID_AD7949] = अणु .num_channels = 8, .resolution = 14 पूर्ण,
	[ID_AD7682] = अणु .num_channels = 4, .resolution = 16 पूर्ण,
	[ID_AD7689] = अणु .num_channels = 8, .resolution = 16 पूर्ण,
पूर्ण;

/**
 * काष्ठा ad7949_adc_chip - AD ADC chip
 * @lock: protects ग_लिखो sequences
 * @vref: regulator generating Vref
 * @indio_dev: reference to iio काष्ठाure
 * @spi: reference to spi काष्ठाure
 * @resolution: resolution of the chip
 * @cfg: copy of the configuration रेजिस्टर
 * @current_channel: current channel in use
 * @buffer: buffer to send / receive data to / from device
 */
काष्ठा ad7949_adc_chip अणु
	काष्ठा mutex lock;
	काष्ठा regulator *vref;
	काष्ठा iio_dev *indio_dev;
	काष्ठा spi_device *spi;
	u8 resolution;
	u16 cfg;
	अचिन्हित पूर्णांक current_channel;
	u16 buffer ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ad7949_spi_ग_लिखो_cfg(काष्ठा ad7949_adc_chip *ad7949_adc, u16 val,
				u16 mask)
अणु
	पूर्णांक ret;
	पूर्णांक bits_per_word = ad7949_adc->resolution;
	पूर्णांक shअगरt = bits_per_word - AD7949_CFG_REG_SIZE_BITS;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx[] = अणु
		अणु
			.tx_buf = &ad7949_adc->buffer,
			.len = 2,
			.bits_per_word = bits_per_word,
		पूर्ण,
	पूर्ण;

	ad7949_adc->cfg = (val & mask) | (ad7949_adc->cfg & ~mask);
	ad7949_adc->buffer = ad7949_adc->cfg << shअगरt;
	spi_message_init_with_transfers(&msg, tx, 1);
	ret = spi_sync(ad7949_adc->spi, &msg);

	/*
	 * This delay is to aव्योम a new request beक्रमe the required समय to
	 * send a new command to the device
	 */
	udelay(2);
	वापस ret;
पूर्ण

अटल पूर्णांक ad7949_spi_पढ़ो_channel(काष्ठा ad7949_adc_chip *ad7949_adc, पूर्णांक *val,
				   अचिन्हित पूर्णांक channel)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक bits_per_word = ad7949_adc->resolution;
	पूर्णांक mask = GENMASK(ad7949_adc->resolution - 1, 0);
	काष्ठा spi_message msg;
	काष्ठा spi_transfer tx[] = अणु
		अणु
			.rx_buf = &ad7949_adc->buffer,
			.len = 2,
			.bits_per_word = bits_per_word,
		पूर्ण,
	पूर्ण;

	/*
	 * 1: ग_लिखो CFG क्रम sample N and पढ़ो old data (sample N-2)
	 * 2: अगर CFG was not changed since sample N-1 then we'll get good data
	 *    at the next xfer, so we bail out now, otherwise we ग_लिखो something
	 *    and we पढ़ो garbage (sample N-1 configuration).
	 */
	क्रम (i = 0; i < 2; i++) अणु
		ret = ad7949_spi_ग_लिखो_cfg(ad7949_adc,
					   channel << AD7949_OFFSET_CHANNEL_SEL,
					   AD7949_MASK_CHANNEL_SEL);
		अगर (ret)
			वापस ret;
		अगर (channel == ad7949_adc->current_channel)
			अवरोध;
	पूर्ण

	/* 3: ग_लिखो something and पढ़ो actual data */
	ad7949_adc->buffer = 0;
	spi_message_init_with_transfers(&msg, tx, 1);
	ret = spi_sync(ad7949_adc->spi, &msg);
	अगर (ret)
		वापस ret;

	/*
	 * This delay is to aव्योम a new request beक्रमe the required समय to
	 * send a new command to the device
	 */
	udelay(2);

	ad7949_adc->current_channel = channel;

	*val = ad7949_adc->buffer & mask;

	वापस 0;
पूर्ण

#घोषणा AD7949_ADC_CHANNEL(chan) अणु				\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = (chan),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad7949_adc_channels[] = अणु
	AD7949_ADC_CHANNEL(0),
	AD7949_ADC_CHANNEL(1),
	AD7949_ADC_CHANNEL(2),
	AD7949_ADC_CHANNEL(3),
	AD7949_ADC_CHANNEL(4),
	AD7949_ADC_CHANNEL(5),
	AD7949_ADC_CHANNEL(6),
	AD7949_ADC_CHANNEL(7),
पूर्ण;

अटल पूर्णांक ad7949_spi_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ad7949_adc_chip *ad7949_adc = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&ad7949_adc->lock);
		ret = ad7949_spi_पढ़ो_channel(ad7949_adc, val, chan->channel);
		mutex_unlock(&ad7949_adc->lock);

		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(ad7949_adc->vref);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 5000;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad7949_spi_reg_access(काष्ठा iio_dev *indio_dev,
			अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक ग_लिखोval,
			अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ad7949_adc_chip *ad7949_adc = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	अगर (पढ़ोval)
		*पढ़ोval = ad7949_adc->cfg;
	अन्यथा
		ret = ad7949_spi_ग_लिखो_cfg(ad7949_adc,
			ग_लिखोval & AD7949_MASK_TOTAL, AD7949_MASK_TOTAL);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7949_spi_info = अणु
	.पढ़ो_raw = ad7949_spi_पढ़ो_raw,
	.debugfs_reg_access = ad7949_spi_reg_access,
पूर्ण;

अटल पूर्णांक ad7949_spi_init(काष्ठा ad7949_adc_chip *ad7949_adc)
अणु
	पूर्णांक ret;
	पूर्णांक val;

	/* Sequencer disabled, CFG पढ़ोback disabled, IN0 as शेष channel */
	ad7949_adc->current_channel = 0;
	ret = ad7949_spi_ग_लिखो_cfg(ad7949_adc, 0x3C79, AD7949_MASK_TOTAL);

	/*
	 * Do two dummy conversions to apply the first configuration setting.
	 * Required only after the start up of the device.
	 */
	ad7949_spi_पढ़ो_channel(ad7949_adc, &val, ad7949_adc->current_channel);
	ad7949_spi_पढ़ो_channel(ad7949_adc, &val, ad7949_adc->current_channel);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7949_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	स्थिर काष्ठा ad7949_adc_spec *spec;
	काष्ठा ad7949_adc_chip *ad7949_adc;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*ad7949_adc));
	अगर (!indio_dev) अणु
		dev_err(dev, "can not allocate iio device\n");
		वापस -ENOMEM;
	पूर्ण

	indio_dev->info = &ad7949_spi_info;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad7949_adc_channels;
	spi_set_drvdata(spi, indio_dev);

	ad7949_adc = iio_priv(indio_dev);
	ad7949_adc->indio_dev = indio_dev;
	ad7949_adc->spi = spi;

	spec = &ad7949_adc_spec[spi_get_device_id(spi)->driver_data];
	indio_dev->num_channels = spec->num_channels;
	ad7949_adc->resolution = spec->resolution;

	ad7949_adc->vref = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(ad7949_adc->vref)) अणु
		dev_err(dev, "fail to request regulator\n");
		वापस PTR_ERR(ad7949_adc->vref);
	पूर्ण

	ret = regulator_enable(ad7949_adc->vref);
	अगर (ret < 0) अणु
		dev_err(dev, "fail to enable regulator\n");
		वापस ret;
	पूर्ण

	mutex_init(&ad7949_adc->lock);

	ret = ad7949_spi_init(ad7949_adc);
	अगर (ret) अणु
		dev_err(dev, "enable to init this device: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "fail to register iio device: %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	mutex_destroy(&ad7949_adc->lock);
	regulator_disable(ad7949_adc->vref);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7949_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad7949_adc_chip *ad7949_adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	mutex_destroy(&ad7949_adc->lock);
	regulator_disable(ad7949_adc->vref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ad7949_spi_of_id[] = अणु
	अणु .compatible = "adi,ad7949" पूर्ण,
	अणु .compatible = "adi,ad7682" पूर्ण,
	अणु .compatible = "adi,ad7689" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7949_spi_of_id);

अटल स्थिर काष्ठा spi_device_id ad7949_spi_id[] = अणु
	अणु "ad7949", ID_AD7949  पूर्ण,
	अणु "ad7682", ID_AD7682 पूर्ण,
	अणु "ad7689", ID_AD7689 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7949_spi_id);

अटल काष्ठा spi_driver ad7949_spi_driver = अणु
	.driver = अणु
		.name		= "ad7949",
		.of_match_table	= ad7949_spi_of_id,
	पूर्ण,
	.probe	  = ad7949_spi_probe,
	.हटाओ   = ad7949_spi_हटाओ,
	.id_table = ad7949_spi_id,
पूर्ण;
module_spi_driver(ad7949_spi_driver);

MODULE_AUTHOR("Charles-Antoine Couret <charles-antoine.couret@essensium.com>");
MODULE_DESCRIPTION("Analog Devices 14/16-bit 8-channel ADC driver");
MODULE_LICENSE("GPL v2");
