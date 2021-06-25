<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5721, AD5721R, AD5761, AD5761R, Voltage Output Digital to Analog Converter
 *
 * Copyright 2016 Qtechnology A/S
 * 2016 Ricarकरो Ribalda <ribalda@kernel.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/platक्रमm_data/ad5761.h>

#घोषणा AD5761_ADDR(addr)		((addr & 0xf) << 16)
#घोषणा AD5761_ADDR_NOOP		0x0
#घोषणा AD5761_ADDR_DAC_WRITE		0x3
#घोषणा AD5761_ADDR_CTRL_WRITE_REG	0x4
#घोषणा AD5761_ADDR_SW_DATA_RESET	0x7
#घोषणा AD5761_ADDR_DAC_READ		0xb
#घोषणा AD5761_ADDR_CTRL_READ_REG	0xc
#घोषणा AD5761_ADDR_SW_FULL_RESET	0xf

#घोषणा AD5761_CTRL_USE_INTVREF		BIT(5)
#घोषणा AD5761_CTRL_ETS			BIT(6)

/**
 * काष्ठा ad5761_chip_info - chip specअगरic inक्रमmation
 * @पूर्णांक_vref:	Value of the पूर्णांकernal reference voltage in mV - 0 अगर बाह्यal
 *		reference voltage is used
 * @channel:	channel specअगरication
*/

काष्ठा ad5761_chip_info अणु
	अचिन्हित दीर्घ पूर्णांक_vref;
	स्थिर काष्ठा iio_chan_spec channel;
पूर्ण;

काष्ठा ad5761_range_params अणु
	पूर्णांक m;
	पूर्णांक c;
पूर्ण;

क्रमागत ad5761_supported_device_ids अणु
	ID_AD5721,
	ID_AD5721R,
	ID_AD5761,
	ID_AD5761R,
पूर्ण;

/**
 * काष्ठा ad5761_state - driver instance specअगरic data
 * @spi:		spi_device
 * @vref_reg:		reference voltage regulator
 * @use_पूर्णांकref:		true when the पूर्णांकernal voltage reference is used
 * @vref:		actual voltage reference in mVolts
 * @range:		output range mode used
 * @lock:		lock to protect the data buffer during SPI ops
 * @data:		cache aligned spi buffer
 */
काष्ठा ad5761_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*vref_reg;
	काष्ठा mutex			lock;

	bool use_पूर्णांकref;
	पूर्णांक vref;
	क्रमागत ad5761_voltage_range range;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	जोड़ अणु
		__be32 d32;
		u8 d8[4];
	पूर्ण data[3] ____cacheline_aligned;
पूर्ण;

अटल स्थिर काष्ठा ad5761_range_params ad5761_range_params[] = अणु
	[AD5761_VOLTAGE_RANGE_M10V_10V] = अणु
		.m = 80,
		.c = 40,
	पूर्ण,
	[AD5761_VOLTAGE_RANGE_0V_10V] = अणु
		.m = 40,
		.c = 0,
	पूर्ण,
	[AD5761_VOLTAGE_RANGE_M5V_5V] = अणु
		.m = 40,
		.c = 20,
	पूर्ण,
	[AD5761_VOLTAGE_RANGE_0V_5V] = अणु
		.m = 20,
		.c = 0,
	पूर्ण,
	[AD5761_VOLTAGE_RANGE_M2V5_7V5] = अणु
		.m = 40,
		.c = 10,
	पूर्ण,
	[AD5761_VOLTAGE_RANGE_M3V_3V] = अणु
		.m = 24,
		.c = 12,
	पूर्ण,
	[AD5761_VOLTAGE_RANGE_0V_16V] = अणु
		.m = 64,
		.c = 0,
	पूर्ण,
	[AD5761_VOLTAGE_RANGE_0V_20V] = अणु
		.m = 80,
		.c = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक _ad5761_spi_ग_लिखो(काष्ठा ad5761_state *st, u8 addr, u16 val)
अणु
	st->data[0].d32 = cpu_to_be32(AD5761_ADDR(addr) | val);

	वापस spi_ग_लिखो(st->spi, &st->data[0].d8[1], 3);
पूर्ण

अटल पूर्णांक ad5761_spi_ग_लिखो(काष्ठा iio_dev *indio_dev, u8 addr, u16 val)
अणु
	काष्ठा ad5761_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = _ad5761_spi_ग_लिखो(st, addr, val);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक _ad5761_spi_पढ़ो(काष्ठा ad5761_state *st, u8 addr, u16 *val)
अणु
	पूर्णांक ret;
	काष्ठा spi_transfer xfers[] = अणु
		अणु
			.tx_buf = &st->data[0].d8[1],
			.bits_per_word = 8,
			.len = 3,
			.cs_change = true,
		पूर्ण, अणु
			.tx_buf = &st->data[1].d8[1],
			.rx_buf = &st->data[2].d8[1],
			.bits_per_word = 8,
			.len = 3,
		पूर्ण,
	पूर्ण;

	st->data[0].d32 = cpu_to_be32(AD5761_ADDR(addr));
	st->data[1].d32 = cpu_to_be32(AD5761_ADDR(AD5761_ADDR_NOOP));

	ret = spi_sync_transfer(st->spi, xfers, ARRAY_SIZE(xfers));

	*val = be32_to_cpu(st->data[2].d32);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5761_spi_पढ़ो(काष्ठा iio_dev *indio_dev, u8 addr, u16 *val)
अणु
	काष्ठा ad5761_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = _ad5761_spi_पढ़ो(st, addr, val);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5761_spi_set_range(काष्ठा ad5761_state *st,
				क्रमागत ad5761_voltage_range range)
अणु
	u16 aux;
	पूर्णांक ret;

	aux = (range & 0x7) | AD5761_CTRL_ETS;

	अगर (st->use_पूर्णांकref)
		aux |= AD5761_CTRL_USE_INTVREF;

	ret = _ad5761_spi_ग_लिखो(st, AD5761_ADDR_SW_FULL_RESET, 0);
	अगर (ret)
		वापस ret;

	ret = _ad5761_spi_ग_लिखो(st, AD5761_ADDR_CTRL_WRITE_REG, aux);
	अगर (ret)
		वापस ret;

	st->range = range;

	वापस 0;
पूर्ण

अटल पूर्णांक ad5761_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ mask)
अणु
	काष्ठा ad5761_state *st;
	पूर्णांक ret;
	u16 aux;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ad5761_spi_पढ़ो(indio_dev, AD5761_ADDR_DAC_READ, &aux);
		अगर (ret)
			वापस ret;
		*val = aux >> chan->scan_type.shअगरt;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		st = iio_priv(indio_dev);
		*val = st->vref * ad5761_range_params[st->range].m;
		*val /= 10;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		st = iio_priv(indio_dev);
		*val = -(1 << chan->scan_type.realbits);
		*val *=	ad5761_range_params[st->range].c;
		*val /=	ad5761_range_params[st->range].m;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5761_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ mask)
अणु
	u16 aux;

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	अगर (val2 || (val << chan->scan_type.shअगरt) > 0xffff || val < 0)
		वापस -EINVAL;

	aux = val << chan->scan_type.shअगरt;

	वापस ad5761_spi_ग_लिखो(indio_dev, AD5761_ADDR_DAC_WRITE, aux);
पूर्ण

अटल स्थिर काष्ठा iio_info ad5761_info = अणु
	.पढ़ो_raw = &ad5761_पढ़ो_raw,
	.ग_लिखो_raw = &ad5761_ग_लिखो_raw,
पूर्ण;

#घोषणा AD5761_CHAN(_bits) अणु				\
	.type = IIO_VOLTAGE,				\
	.output = 1,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
		BIT(IIO_CHAN_INFO_OFFSET),		\
	.scan_type = अणु					\
		.sign = 'u',				\
		.realbits = (_bits),			\
		.storagebits = 16,			\
		.shअगरt = 16 - (_bits),			\
	पूर्ण,						\
पूर्ण

अटल स्थिर काष्ठा ad5761_chip_info ad5761_chip_infos[] = अणु
	[ID_AD5721] = अणु
		.पूर्णांक_vref = 0,
		.channel = AD5761_CHAN(12),
	पूर्ण,
	[ID_AD5721R] = अणु
		.पूर्णांक_vref = 2500,
		.channel = AD5761_CHAN(12),
	पूर्ण,
	[ID_AD5761] = अणु
		.पूर्णांक_vref = 0,
		.channel = AD5761_CHAN(16),
	पूर्ण,
	[ID_AD5761R] = अणु
		.पूर्णांक_vref = 2500,
		.channel = AD5761_CHAN(16),
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad5761_get_vref(काष्ठा ad5761_state *st,
			   स्थिर काष्ठा ad5761_chip_info *chip_info)
अणु
	पूर्णांक ret;

	st->vref_reg = devm_regulator_get_optional(&st->spi->dev, "vref");
	अगर (PTR_ERR(st->vref_reg) == -ENODEV) अणु
		/* Use Internal regulator */
		अगर (!chip_info->पूर्णांक_vref) अणु
			dev_err(&st->spi->dev,
				"Voltage reference not found\n");
			वापस -EIO;
		पूर्ण

		st->use_पूर्णांकref = true;
		st->vref = chip_info->पूर्णांक_vref;
		वापस 0;
	पूर्ण

	अगर (IS_ERR(st->vref_reg)) अणु
		dev_err(&st->spi->dev,
			"Error getting voltage reference regulator\n");
		वापस PTR_ERR(st->vref_reg);
	पूर्ण

	ret = regulator_enable(st->vref_reg);
	अगर (ret) अणु
		dev_err(&st->spi->dev,
			 "Failed to enable voltage reference\n");
		वापस ret;
	पूर्ण

	ret = regulator_get_voltage(st->vref_reg);
	अगर (ret < 0) अणु
		dev_err(&st->spi->dev,
			 "Failed to get voltage reference value\n");
		जाओ disable_regulator_vref;
	पूर्ण

	अगर (ret < 2000000 || ret > 3000000) अणु
		dev_warn(&st->spi->dev,
			 "Invalid external voltage ref. value %d uV\n", ret);
		ret = -EIO;
		जाओ disable_regulator_vref;
	पूर्ण

	st->vref = ret / 1000;
	st->use_पूर्णांकref = false;

	वापस 0;

disable_regulator_vref:
	regulator_disable(st->vref_reg);
	st->vref_reg = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक ad5761_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *iio_dev;
	काष्ठा ad5761_state *st;
	पूर्णांक ret;
	स्थिर काष्ठा ad5761_chip_info *chip_info =
		&ad5761_chip_infos[spi_get_device_id(spi)->driver_data];
	क्रमागत ad5761_voltage_range voltage_range = AD5761_VOLTAGE_RANGE_0V_5V;
	काष्ठा ad5761_platक्रमm_data *pdata = dev_get_platdata(&spi->dev);

	iio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!iio_dev)
		वापस -ENOMEM;

	st = iio_priv(iio_dev);

	st->spi = spi;
	spi_set_drvdata(spi, iio_dev);

	ret = ad5761_get_vref(st, chip_info);
	अगर (ret)
		वापस ret;

	अगर (pdata)
		voltage_range = pdata->voltage_range;

	mutex_init(&st->lock);

	ret = ad5761_spi_set_range(st, voltage_range);
	अगर (ret)
		जाओ disable_regulator_err;

	iio_dev->info = &ad5761_info;
	iio_dev->modes = INDIO_सूचीECT_MODE;
	iio_dev->channels = &chip_info->channel;
	iio_dev->num_channels = 1;
	iio_dev->name = spi_get_device_id(st->spi)->name;
	ret = iio_device_रेजिस्टर(iio_dev);
	अगर (ret)
		जाओ disable_regulator_err;

	वापस 0;

disable_regulator_err:
	अगर (!IS_ERR_OR_शून्य(st->vref_reg))
		regulator_disable(st->vref_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5761_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *iio_dev = spi_get_drvdata(spi);
	काष्ठा ad5761_state *st = iio_priv(iio_dev);

	iio_device_unरेजिस्टर(iio_dev);

	अगर (!IS_ERR_OR_शून्य(st->vref_reg))
		regulator_disable(st->vref_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5761_id[] = अणु
	अणु"ad5721", ID_AD5721पूर्ण,
	अणु"ad5721r", ID_AD5721Rपूर्ण,
	अणु"ad5761", ID_AD5761पूर्ण,
	अणु"ad5761r", ID_AD5761Rपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5761_id);

अटल काष्ठा spi_driver ad5761_driver = अणु
	.driver = अणु
		   .name = "ad5761",
		   पूर्ण,
	.probe = ad5761_probe,
	.हटाओ = ad5761_हटाओ,
	.id_table = ad5761_id,
पूर्ण;
module_spi_driver(ad5761_driver);

MODULE_AUTHOR("Ricardo Ribalda <ribalda@kernel.org>");
MODULE_DESCRIPTION("Analog Devices AD5721, AD5721R, AD5761, AD5761R driver");
MODULE_LICENSE("GPL v2");
