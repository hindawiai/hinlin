<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Analog Devices AD7292 SPI ADC driver
 *
 * Copyright 2019 Analog Devices Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/iपन.स>

#घोषणा ADI_VENDOR_ID 0x0018

/* AD7292 रेजिस्टरs definition */
#घोषणा AD7292_REG_VENDOR_ID		0x00
#घोषणा AD7292_REG_CONF_BANK		0x05
#घोषणा AD7292_REG_CONV_COMM		0x0E
#घोषणा AD7292_REG_ADC_CH(x)		(0x10 + (x))

/* AD7292 configuration bank subरेजिस्टरs definition */
#घोषणा AD7292_BANK_REG_VIN_RNG0	0x10
#घोषणा AD7292_BANK_REG_VIN_RNG1	0x11
#घोषणा AD7292_BANK_REG_SAMP_MODE	0x12

#घोषणा AD7292_RD_FLAG_MSK(x)		(BIT(7) | ((x) & 0x3F))

/* AD7292_REG_ADC_CONVERSION */
#घोषणा AD7292_ADC_DATA_MASK		GENMASK(15, 6)
#घोषणा AD7292_ADC_DATA(x)		FIELD_GET(AD7292_ADC_DATA_MASK, x)

/* AD7292_CHANNEL_SAMPLING_MODE */
#घोषणा AD7292_CH_SAMP_MODE(reg, ch)	(((reg) >> 8) & BIT(ch))

/* AD7292_CHANNEL_VIN_RANGE */
#घोषणा AD7292_CH_VIN_RANGE(reg, ch)	((reg) & BIT(ch))

#घोषणा AD7292_VOLTAGE_CHAN(_chan)					\
अणु									\
	.type = IIO_VOLTAGE,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |			\
			      BIT(IIO_CHAN_INFO_SCALE),			\
	.indexed = 1,							\
	.channel = _chan,						\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad7292_channels[] = अणु
	AD7292_VOLTAGE_CHAN(0),
	AD7292_VOLTAGE_CHAN(1),
	AD7292_VOLTAGE_CHAN(2),
	AD7292_VOLTAGE_CHAN(3),
	AD7292_VOLTAGE_CHAN(4),
	AD7292_VOLTAGE_CHAN(5),
	AD7292_VOLTAGE_CHAN(6),
	AD7292_VOLTAGE_CHAN(7)
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7292_channels_dअगरf[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.indexed = 1,
		.dअगरferential = 1,
		.channel = 0,
		.channel2 = 1,
	पूर्ण,
	AD7292_VOLTAGE_CHAN(2),
	AD7292_VOLTAGE_CHAN(3),
	AD7292_VOLTAGE_CHAN(4),
	AD7292_VOLTAGE_CHAN(5),
	AD7292_VOLTAGE_CHAN(6),
	AD7292_VOLTAGE_CHAN(7)
पूर्ण;

काष्ठा ad7292_state अणु
	काष्ठा spi_device *spi;
	काष्ठा regulator *reg;
	अचिन्हित लघु vref_mv;

	__be16 d16 ____cacheline_aligned;
	u8 d8[2];
पूर्ण;

अटल पूर्णांक ad7292_spi_reg_पढ़ो(काष्ठा ad7292_state *st, अचिन्हित पूर्णांक addr)
अणु
	पूर्णांक ret;

	st->d8[0] = AD7292_RD_FLAG_MSK(addr);

	ret = spi_ग_लिखो_then_पढ़ो(st->spi, st->d8, 1, &st->d16, 2);
	अगर (ret < 0)
		वापस ret;

	वापस be16_to_cpu(st->d16);
पूर्ण

अटल पूर्णांक ad7292_spi_subreg_पढ़ो(काष्ठा ad7292_state *st, अचिन्हित पूर्णांक addr,
				  अचिन्हित पूर्णांक sub_addr, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक shअगरt = 16 - (8 * len);
	पूर्णांक ret;

	st->d8[0] = AD7292_RD_FLAG_MSK(addr);
	st->d8[1] = sub_addr;

	ret = spi_ग_लिखो_then_पढ़ो(st->spi, st->d8, 2, &st->d16, len);
	अगर (ret < 0)
		वापस ret;

	वापस (be16_to_cpu(st->d16) >> shअगरt);
पूर्ण

अटल पूर्णांक ad7292_single_conversion(काष्ठा ad7292_state *st,
				    अचिन्हित पूर्णांक chan_addr)
अणु
	पूर्णांक ret;

	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->d8,
			.len = 4,
			.delay = अणु
				.value = 6,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,
		पूर्ण, अणु
			.rx_buf = &st->d16,
			.len = 2,
		पूर्ण,
	पूर्ण;

	st->d8[0] = chan_addr;
	st->d8[1] = AD7292_RD_FLAG_MSK(AD7292_REG_CONV_COMM);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));

	अगर (ret < 0)
		वापस ret;

	वापस be16_to_cpu(st->d16);
पूर्ण

अटल पूर्णांक ad7292_vin_range_multiplier(काष्ठा ad7292_state *st, पूर्णांक channel)
अणु
	पूर्णांक samp_mode, range0, range1, factor = 1;

	/*
	 * Every AD7292 ADC channel may have its input range adjusted according
	 * to the settings at the ADC sampling mode and VIN range subरेजिस्टरs.
	 * For a given channel, the minimum input range is equal to Vref, and it
	 * may be increased by a multiplier factor of 2 or 4 according to the
	 * following rule:
	 * If channel is being sampled with respect to AGND:
	 *	factor = 4 अगर VIN range0 and VIN range1 equal 0
	 *	factor = 2 अगर only one of VIN ranges equal 1
	 *	factor = 1 अगर both VIN range0 and VIN range1 equal 1
	 * If channel is being sampled with respect to AVDD:
	 *	factor = 4 अगर VIN range0 and VIN range1 equal 0
	 *	Behavior is undefined अगर any of VIN range करोesn't equal 0
	 */

	samp_mode = ad7292_spi_subreg_पढ़ो(st, AD7292_REG_CONF_BANK,
					   AD7292_BANK_REG_SAMP_MODE, 2);

	अगर (samp_mode < 0)
		वापस samp_mode;

	range0 = ad7292_spi_subreg_पढ़ो(st, AD7292_REG_CONF_BANK,
					AD7292_BANK_REG_VIN_RNG0, 2);

	अगर (range0 < 0)
		वापस range0;

	range1 = ad7292_spi_subreg_पढ़ो(st, AD7292_REG_CONF_BANK,
					AD7292_BANK_REG_VIN_RNG1, 2);

	अगर (range1 < 0)
		वापस range1;

	अगर (AD7292_CH_SAMP_MODE(samp_mode, channel)) अणु
		/* Sampling with respect to AGND */
		अगर (!AD7292_CH_VIN_RANGE(range0, channel))
			factor *= 2;

		अगर (!AD7292_CH_VIN_RANGE(range1, channel))
			factor *= 2;

	पूर्ण अन्यथा अणु
		/* Sampling with respect to AVDD */
		अगर (AD7292_CH_VIN_RANGE(range0, channel) ||
		    AD7292_CH_VIN_RANGE(range1, channel))
			वापस -EPERM;

		factor = 4;
	पूर्ण

	वापस factor;
पूर्ण

अटल पूर्णांक ad7292_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   स्थिर काष्ठा iio_chan_spec *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad7292_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक ch_addr;
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		ch_addr = AD7292_REG_ADC_CH(chan->channel);
		ret = ad7292_single_conversion(st, ch_addr);
		अगर (ret < 0)
			वापस ret;

		*val = AD7292_ADC_DATA(ret);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/*
		 * To convert a raw value to standard units, the IIO defines
		 * this क्रमmula: Scaled value = (raw + offset) * scale.
		 * For the scale to be a correct multiplier क्रम (raw + offset),
		 * it must be calculated as the input range भागided by the
		 * number of possible distinct input values. Given the ADC data
		 * is 10 bit दीर्घ, it may assume 2^10 distinct values.
		 * Hence, scale = range / 2^10. The IIO_VAL_FRACTIONAL_LOG2
		 * वापस type indicates to the IIO API to भागide *val by 2 to
		 * the घातer of *val2 when वापसing from पढ़ो_raw.
		 */

		ret = ad7292_vin_range_multiplier(st, chan->channel);
		अगर (ret < 0)
			वापस ret;

		*val = st->vref_mv * ret;
		*val2 = 10;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7292_info = अणु
	.पढ़ो_raw = ad7292_पढ़ो_raw,
पूर्ण;

अटल व्योम ad7292_regulator_disable(व्योम *data)
अणु
	काष्ठा ad7292_state *st = data;

	regulator_disable(st->reg);
पूर्ण

अटल पूर्णांक ad7292_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7292_state *st;
	काष्ठा iio_dev *indio_dev;
	काष्ठा device_node *child;
	bool dअगरf_channels = false;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	st->spi = spi;

	ret = ad7292_spi_reg_पढ़ो(st, AD7292_REG_VENDOR_ID);
	अगर (ret != ADI_VENDOR_ID) अणु
		dev_err(&spi->dev, "Wrong vendor id 0x%x\n", ret);
		वापस -EINVAL;
	पूर्ण

	st->reg = devm_regulator_get_optional(&spi->dev, "vref");
	अगर (!IS_ERR(st->reg)) अणु
		ret = regulator_enable(st->reg);
		अगर (ret) अणु
			dev_err(&spi->dev,
				"Failed to enable external vref supply\n");
			वापस ret;
		पूर्ण

		ret = devm_add_action_or_reset(&spi->dev,
					       ad7292_regulator_disable, st);
		अगर (ret) अणु
			regulator_disable(st->reg);
			वापस ret;
		पूर्ण

		ret = regulator_get_voltage(st->reg);
		अगर (ret < 0)
			वापस ret;

		st->vref_mv = ret / 1000;
	पूर्ण अन्यथा अणु
		/* Use the पूर्णांकernal voltage reference. */
		st->vref_mv = 1250;
	पूर्ण

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &ad7292_info;

	क्रम_each_available_child_of_node(spi->dev.of_node, child) अणु
		dअगरf_channels = of_property_पढ़ो_bool(child, "diff-channels");
		अगर (dअगरf_channels) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (dअगरf_channels) अणु
		indio_dev->num_channels = ARRAY_SIZE(ad7292_channels_dअगरf);
		indio_dev->channels = ad7292_channels_dअगरf;
	पूर्ण अन्यथा अणु
		indio_dev->num_channels = ARRAY_SIZE(ad7292_channels);
		indio_dev->channels = ad7292_channels;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7292_id_table[] = अणु
	अणु "ad7292", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7292_id_table);

अटल स्थिर काष्ठा of_device_id ad7292_of_match[] = अणु
	अणु .compatible = "adi,ad7292" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7292_of_match);

अटल काष्ठा spi_driver ad7292_driver = अणु
	.driver = अणु
		.name = "ad7292",
		.of_match_table = ad7292_of_match,
	पूर्ण,
	.probe = ad7292_probe,
	.id_table = ad7292_id_table,
पूर्ण;
module_spi_driver(ad7292_driver);

MODULE_AUTHOR("Marcelo Schmitt <marcelo.schmitt1@gmail.com>");
MODULE_DESCRIPTION("Analog Devices AD7292 ADC driver");
MODULE_LICENSE("GPL v2");
