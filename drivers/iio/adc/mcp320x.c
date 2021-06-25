<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Oskar Andero <oskar.andero@gmail.com>
 * Copyright (C) 2014 Rose Technology
 * 	   Allan Benकरोrff Jensen <abj@rosetechnology.dk>
 *	   Soren Andersen <san@rosetechnology.dk>
 *
 * Driver क्रम following ADC chips from Microchip Technology's:
 * 10 Bit converter
 * MCP3001
 * MCP3002
 * MCP3004
 * MCP3008
 * ------------
 * 12 bit converter
 * MCP3201
 * MCP3202
 * MCP3204
 * MCP3208
 * ------------
 * 13 bit converter
 * MCP3301
 * ------------
 * 22 bit converter
 * MCP3550
 * MCP3551
 * MCP3553
 *
 * Datasheet can be found here:
 * https://ww1.microchip.com/करोwnloads/en/DeviceDoc/21293C.pdf  mcp3001
 * https://ww1.microchip.com/करोwnloads/en/DeviceDoc/21294E.pdf  mcp3002
 * https://ww1.microchip.com/करोwnloads/en/DeviceDoc/21295d.pdf  mcp3004/08
 * http://ww1.microchip.com/करोwnloads/en/DeviceDoc/21290D.pdf  mcp3201
 * http://ww1.microchip.com/करोwnloads/en/DeviceDoc/21034D.pdf  mcp3202
 * http://ww1.microchip.com/करोwnloads/en/DeviceDoc/21298c.pdf  mcp3204/08
 * https://ww1.microchip.com/करोwnloads/en/DeviceDoc/21700E.pdf  mcp3301
 * http://ww1.microchip.com/करोwnloads/en/DeviceDoc/21950D.pdf  mcp3550/1/3
 */

#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/regulator/consumer.h>

क्रमागत अणु
	mcp3001,
	mcp3002,
	mcp3004,
	mcp3008,
	mcp3201,
	mcp3202,
	mcp3204,
	mcp3208,
	mcp3301,
	mcp3550_50,
	mcp3550_60,
	mcp3551,
	mcp3553,
पूर्ण;

काष्ठा mcp320x_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	अचिन्हित पूर्णांक resolution;
	अचिन्हित पूर्णांक conv_समय; /* usec */
पूर्ण;

/**
 * काष्ठा mcp320x - Microchip SPI ADC instance
 * @spi: SPI slave (parent of the IIO device)
 * @msg: SPI message to select a channel and receive a value from the ADC
 * @transfer: SPI transfers used by @msg
 * @start_conv_msg: SPI message to start a conversion by briefly निश्चितing CS
 * @start_conv_transfer: SPI transfer used by @start_conv_msg
 * @reg: regulator generating Vref
 * @lock: protects पढ़ो sequences
 * @chip_info: ADC properties
 * @tx_buf: buffer क्रम @transfer[0] (not used on single-channel converters)
 * @rx_buf: buffer क्रम @transfer[1]
 */
काष्ठा mcp320x अणु
	काष्ठा spi_device *spi;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer transfer[2];
	काष्ठा spi_message start_conv_msg;
	काष्ठा spi_transfer start_conv_transfer;

	काष्ठा regulator *reg;
	काष्ठा mutex lock;
	स्थिर काष्ठा mcp320x_chip_info *chip_info;

	u8 tx_buf ____cacheline_aligned;
	u8 rx_buf[4];
पूर्ण;

अटल पूर्णांक mcp320x_channel_to_tx_data(पूर्णांक device_index,
			स्थिर अचिन्हित पूर्णांक channel, bool dअगरferential)
अणु
	पूर्णांक start_bit = 1;

	चयन (device_index) अणु
	हाल mcp3002:
	हाल mcp3202:
		वापस ((start_bit << 4) | (!dअगरferential << 3) |
							(channel << 2));
	हाल mcp3004:
	हाल mcp3204:
	हाल mcp3008:
	हाल mcp3208:
		वापस ((start_bit << 6) | (!dअगरferential << 5) |
							(channel << 2));
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mcp320x_adc_conversion(काष्ठा mcp320x *adc, u8 channel,
				  bool dअगरferential, पूर्णांक device_index, पूर्णांक *val)
अणु
	पूर्णांक ret;

	अगर (adc->chip_info->conv_समय) अणु
		ret = spi_sync(adc->spi, &adc->start_conv_msg);
		अगर (ret < 0)
			वापस ret;

		usleep_range(adc->chip_info->conv_समय,
			     adc->chip_info->conv_समय + 100);
	पूर्ण

	स_रखो(&adc->rx_buf, 0, माप(adc->rx_buf));
	अगर (adc->chip_info->num_channels > 1)
		adc->tx_buf = mcp320x_channel_to_tx_data(device_index, channel,
							 dअगरferential);

	ret = spi_sync(adc->spi, &adc->msg);
	अगर (ret < 0)
		वापस ret;

	चयन (device_index) अणु
	हाल mcp3001:
		*val = (adc->rx_buf[0] << 5 | adc->rx_buf[1] >> 3);
		वापस 0;
	हाल mcp3002:
	हाल mcp3004:
	हाल mcp3008:
		*val = (adc->rx_buf[0] << 2 | adc->rx_buf[1] >> 6);
		वापस 0;
	हाल mcp3201:
		*val = (adc->rx_buf[0] << 7 | adc->rx_buf[1] >> 1);
		वापस 0;
	हाल mcp3202:
	हाल mcp3204:
	हाल mcp3208:
		*val = (adc->rx_buf[0] << 4 | adc->rx_buf[1] >> 4);
		वापस 0;
	हाल mcp3301:
		*val = sign_extend32((adc->rx_buf[0] & 0x1f) << 8
				    | adc->rx_buf[1], 12);
		वापस 0;
	हाल mcp3550_50:
	हाल mcp3550_60:
	हाल mcp3551:
	हाल mcp3553: अणु
		u32 raw = be32_to_cpup((__be32 *)adc->rx_buf);

		अगर (!(adc->spi->mode & SPI_CPOL))
			raw <<= 1; /* strip Data Ready bit in SPI mode 0,0 */

		/*
		 * If the input is within -vref and vref, bit 21 is the sign.
		 * Up to 12% overrange or underrange are allowed, in which हाल
		 * bit 23 is the sign and bit 0 to 21 is the value.
		 */
		raw >>= 8;
		अगर (raw & BIT(22) && raw & BIT(23))
			वापस -EIO; /* cannot have overrange AND underrange */
		अन्यथा अगर (raw & BIT(22))
			raw &= ~BIT(22); /* overrange */
		अन्यथा अगर (raw & BIT(23) || raw & BIT(21))
			raw |= GENMASK(31, 22); /* underrange or negative */

		*val = (s32)raw;
		वापस 0;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mcp320x_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mcp320x *adc = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;
	पूर्णांक device_index = 0;

	mutex_lock(&adc->lock);

	device_index = spi_get_device_id(adc->spi)->driver_data;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = mcp320x_adc_conversion(adc, channel->address,
			channel->dअगरferential, device_index, val);
		अगर (ret < 0)
			जाओ out;

		ret = IIO_VAL_INT;
		अवरोध;

	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(adc->reg);
		अगर (ret < 0)
			जाओ out;

		/* convert regulator output voltage to mV */
		*val = ret / 1000;
		*val2 = adc->chip_info->resolution;
		ret = IIO_VAL_FRACTIONAL_LOG2;
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&adc->lock);

	वापस ret;
पूर्ण

#घोषणा MCP320X_VOLTAGE_CHANNEL(num)				\
	अणु							\
		.type = IIO_VOLTAGE,				\
		.indexed = 1,					\
		.channel = (num),				\
		.address = (num),				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) \
	पूर्ण

#घोषणा MCP320X_VOLTAGE_CHANNEL_DIFF(chan1, chan2)		\
	अणु							\
		.type = IIO_VOLTAGE,				\
		.indexed = 1,					\
		.channel = (chan1),				\
		.channel2 = (chan2),				\
		.address = (chan1),				\
		.dअगरferential = 1,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) \
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mcp3201_channels[] = अणु
	MCP320X_VOLTAGE_CHANNEL_DIFF(0, 1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mcp3202_channels[] = अणु
	MCP320X_VOLTAGE_CHANNEL(0),
	MCP320X_VOLTAGE_CHANNEL(1),
	MCP320X_VOLTAGE_CHANNEL_DIFF(0, 1),
	MCP320X_VOLTAGE_CHANNEL_DIFF(1, 0),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mcp3204_channels[] = अणु
	MCP320X_VOLTAGE_CHANNEL(0),
	MCP320X_VOLTAGE_CHANNEL(1),
	MCP320X_VOLTAGE_CHANNEL(2),
	MCP320X_VOLTAGE_CHANNEL(3),
	MCP320X_VOLTAGE_CHANNEL_DIFF(0, 1),
	MCP320X_VOLTAGE_CHANNEL_DIFF(1, 0),
	MCP320X_VOLTAGE_CHANNEL_DIFF(2, 3),
	MCP320X_VOLTAGE_CHANNEL_DIFF(3, 2),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mcp3208_channels[] = अणु
	MCP320X_VOLTAGE_CHANNEL(0),
	MCP320X_VOLTAGE_CHANNEL(1),
	MCP320X_VOLTAGE_CHANNEL(2),
	MCP320X_VOLTAGE_CHANNEL(3),
	MCP320X_VOLTAGE_CHANNEL(4),
	MCP320X_VOLTAGE_CHANNEL(5),
	MCP320X_VOLTAGE_CHANNEL(6),
	MCP320X_VOLTAGE_CHANNEL(7),
	MCP320X_VOLTAGE_CHANNEL_DIFF(0, 1),
	MCP320X_VOLTAGE_CHANNEL_DIFF(1, 0),
	MCP320X_VOLTAGE_CHANNEL_DIFF(2, 3),
	MCP320X_VOLTAGE_CHANNEL_DIFF(3, 2),
	MCP320X_VOLTAGE_CHANNEL_DIFF(4, 5),
	MCP320X_VOLTAGE_CHANNEL_DIFF(5, 4),
	MCP320X_VOLTAGE_CHANNEL_DIFF(6, 7),
	MCP320X_VOLTAGE_CHANNEL_DIFF(7, 6),
पूर्ण;

अटल स्थिर काष्ठा iio_info mcp320x_info = अणु
	.पढ़ो_raw = mcp320x_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा mcp320x_chip_info mcp320x_chip_infos[] = अणु
	[mcp3001] = अणु
		.channels = mcp3201_channels,
		.num_channels = ARRAY_SIZE(mcp3201_channels),
		.resolution = 10
	पूर्ण,
	[mcp3002] = अणु
		.channels = mcp3202_channels,
		.num_channels = ARRAY_SIZE(mcp3202_channels),
		.resolution = 10
	पूर्ण,
	[mcp3004] = अणु
		.channels = mcp3204_channels,
		.num_channels = ARRAY_SIZE(mcp3204_channels),
		.resolution = 10
	पूर्ण,
	[mcp3008] = अणु
		.channels = mcp3208_channels,
		.num_channels = ARRAY_SIZE(mcp3208_channels),
		.resolution = 10
	पूर्ण,
	[mcp3201] = अणु
		.channels = mcp3201_channels,
		.num_channels = ARRAY_SIZE(mcp3201_channels),
		.resolution = 12
	पूर्ण,
	[mcp3202] = अणु
		.channels = mcp3202_channels,
		.num_channels = ARRAY_SIZE(mcp3202_channels),
		.resolution = 12
	पूर्ण,
	[mcp3204] = अणु
		.channels = mcp3204_channels,
		.num_channels = ARRAY_SIZE(mcp3204_channels),
		.resolution = 12
	पूर्ण,
	[mcp3208] = अणु
		.channels = mcp3208_channels,
		.num_channels = ARRAY_SIZE(mcp3208_channels),
		.resolution = 12
	पूर्ण,
	[mcp3301] = अणु
		.channels = mcp3201_channels,
		.num_channels = ARRAY_SIZE(mcp3201_channels),
		.resolution = 13
	पूर्ण,
	[mcp3550_50] = अणु
		.channels = mcp3201_channels,
		.num_channels = ARRAY_SIZE(mcp3201_channels),
		.resolution = 21,
		/* 2% max deviation + 144 घड़ी periods to निकास shutकरोwn */
		.conv_समय = 80000 * 1.02 + 144000 / 102.4,
	पूर्ण,
	[mcp3550_60] = अणु
		.channels = mcp3201_channels,
		.num_channels = ARRAY_SIZE(mcp3201_channels),
		.resolution = 21,
		.conv_समय = 66670 * 1.02 + 144000 / 122.88,
	पूर्ण,
	[mcp3551] = अणु
		.channels = mcp3201_channels,
		.num_channels = ARRAY_SIZE(mcp3201_channels),
		.resolution = 21,
		.conv_समय = 73100 * 1.02 + 144000 / 112.64,
	पूर्ण,
	[mcp3553] = अणु
		.channels = mcp3201_channels,
		.num_channels = ARRAY_SIZE(mcp3201_channels),
		.resolution = 21,
		.conv_समय = 16670 * 1.02 + 144000 / 122.88,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mcp320x_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा mcp320x *adc;
	स्थिर काष्ठा mcp320x_chip_info *chip_info;
	पूर्णांक ret, device_index;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mcp320x_info;
	spi_set_drvdata(spi, indio_dev);

	device_index = spi_get_device_id(spi)->driver_data;
	chip_info = &mcp320x_chip_infos[device_index];
	indio_dev->channels = chip_info->channels;
	indio_dev->num_channels = chip_info->num_channels;

	adc->chip_info = chip_info;

	adc->transfer[0].tx_buf = &adc->tx_buf;
	adc->transfer[0].len = माप(adc->tx_buf);
	adc->transfer[1].rx_buf = adc->rx_buf;
	adc->transfer[1].len = DIV_ROUND_UP(chip_info->resolution, 8);

	अगर (chip_info->num_channels == 1)
		/* single-channel converters are rx only (no MOSI pin) */
		spi_message_init_with_transfers(&adc->msg,
						&adc->transfer[1], 1);
	अन्यथा
		spi_message_init_with_transfers(&adc->msg, adc->transfer,
						ARRAY_SIZE(adc->transfer));

	चयन (device_index) अणु
	हाल mcp3550_50:
	हाल mcp3550_60:
	हाल mcp3551:
	हाल mcp3553:
		/* rx len increases from 24 to 25 bit in SPI mode 0,0 */
		अगर (!(spi->mode & SPI_CPOL))
			adc->transfer[1].len++;

		/* conversions are started by निश्चितing CS pin क्रम 8 usec */
		adc->start_conv_transfer.delay.value = 8;
		adc->start_conv_transfer.delay.unit = SPI_DELAY_UNIT_USECS;
		spi_message_init_with_transfers(&adc->start_conv_msg,
						&adc->start_conv_transfer, 1);

		/*
		 * If CS was previously kept low (continuous conversion mode)
		 * and then changed to high, the chip is in shutकरोwn.
		 * Someबार it fails to wake from shutकरोwn and घड़ीs out
		 * only 0xffffff.  The magic sequence of perक्रमming two
		 * conversions without delay between them resets the chip
		 * and ensures all subsequent conversions succeed.
		 */
		mcp320x_adc_conversion(adc, 0, 1, device_index, &ret);
		mcp320x_adc_conversion(adc, 0, 1, device_index, &ret);
	पूर्ण

	adc->reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(adc->reg))
		वापस PTR_ERR(adc->reg);

	ret = regulator_enable(adc->reg);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&adc->lock);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ reg_disable;

	वापस 0;

reg_disable:
	regulator_disable(adc->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक mcp320x_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा mcp320x *adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(adc->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mcp320x_dt_ids[] = अणु
	/* NOTE: The use of compatibles with no venकरोr prefix is deprecated. */
	अणु .compatible = "mcp3001" पूर्ण,
	अणु .compatible = "mcp3002" पूर्ण,
	अणु .compatible = "mcp3004" पूर्ण,
	अणु .compatible = "mcp3008" पूर्ण,
	अणु .compatible = "mcp3201" पूर्ण,
	अणु .compatible = "mcp3202" पूर्ण,
	अणु .compatible = "mcp3204" पूर्ण,
	अणु .compatible = "mcp3208" पूर्ण,
	अणु .compatible = "mcp3301" पूर्ण,
	अणु .compatible = "microchip,mcp3001" पूर्ण,
	अणु .compatible = "microchip,mcp3002" पूर्ण,
	अणु .compatible = "microchip,mcp3004" पूर्ण,
	अणु .compatible = "microchip,mcp3008" पूर्ण,
	अणु .compatible = "microchip,mcp3201" पूर्ण,
	अणु .compatible = "microchip,mcp3202" पूर्ण,
	अणु .compatible = "microchip,mcp3204" पूर्ण,
	अणु .compatible = "microchip,mcp3208" पूर्ण,
	अणु .compatible = "microchip,mcp3301" पूर्ण,
	अणु .compatible = "microchip,mcp3550-50" पूर्ण,
	अणु .compatible = "microchip,mcp3550-60" पूर्ण,
	अणु .compatible = "microchip,mcp3551" पूर्ण,
	अणु .compatible = "microchip,mcp3553" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp320x_dt_ids);

अटल स्थिर काष्ठा spi_device_id mcp320x_id[] = अणु
	अणु "mcp3001", mcp3001 पूर्ण,
	अणु "mcp3002", mcp3002 पूर्ण,
	अणु "mcp3004", mcp3004 पूर्ण,
	अणु "mcp3008", mcp3008 पूर्ण,
	अणु "mcp3201", mcp3201 पूर्ण,
	अणु "mcp3202", mcp3202 पूर्ण,
	अणु "mcp3204", mcp3204 पूर्ण,
	अणु "mcp3208", mcp3208 पूर्ण,
	अणु "mcp3301", mcp3301 पूर्ण,
	अणु "mcp3550-50", mcp3550_50 पूर्ण,
	अणु "mcp3550-60", mcp3550_60 पूर्ण,
	अणु "mcp3551", mcp3551 पूर्ण,
	अणु "mcp3553", mcp3553 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mcp320x_id);

अटल काष्ठा spi_driver mcp320x_driver = अणु
	.driver = अणु
		.name = "mcp320x",
		.of_match_table = mcp320x_dt_ids,
	पूर्ण,
	.probe = mcp320x_probe,
	.हटाओ = mcp320x_हटाओ,
	.id_table = mcp320x_id,
पूर्ण;
module_spi_driver(mcp320x_driver);

MODULE_AUTHOR("Oskar Andero <oskar.andero@gmail.com>");
MODULE_DESCRIPTION("Microchip Technology MCP3x01/02/04/08 and MCP3550/1/3");
MODULE_LICENSE("GPL v2");
