<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI ADC108S102 SPI ADC driver
 *
 * Copyright (c) 2013-2015 Intel Corporation.
 * Copyright (c) 2017 Siemens AG
 *
 * This IIO device driver is deचिन्हित to work with the following
 * analog to digital converters from Texas Instruments:
 *  ADC108S102
 *  ADC128S102
 * The communication with ADC chip is via the SPI bus (mode 3).
 */

#समावेश <linux/acpi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/types.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

/*
 * In हाल of ACPI, we use the hard-wired 5000 mV of the Galileo and IOT2000
 * boards as शेष क्रम the reference pin VA. Device tree users encode that
 * via the vref-supply regulator.
 */
#घोषणा ADC108S102_VA_MV_ACPI_DEFAULT	5000

/*
 * Defining the ADC resolution being 12 bits, we can use the same driver क्रम
 * both ADC108S102 (10 bits resolution) and ADC128S102 (12 bits resolution)
 * chips. The ADC108S102 effectively वापसs a 12-bit result with the 2
 * least-signअगरicant bits unset.
 */
#घोषणा ADC108S102_BITS		12
#घोषणा ADC108S102_MAX_CHANNELS	8

/*
 * 16-bit SPI command क्रमmat:
 *   [15:14] Ignored
 *   [13:11] 3-bit channel address
 *   [10:0]  Ignored
 */
#घोषणा ADC108S102_CMD(ch)		((u16)(ch) << 11)

/*
 * 16-bit SPI response क्रमmat:
 *   [15:12] Zeros
 *   [11:0]  12-bit ADC sample (क्रम ADC108S102, [1:0] will always be 0).
 */
#घोषणा ADC108S102_RES_DATA(res)	((u16)res & GENMASK(11, 0))

काष्ठा adc108s102_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*reg;
	u32				va_millivolt;
	/* SPI transfer used by triggered buffer handler*/
	काष्ठा spi_transfer		ring_xfer;
	/* SPI transfer used by direct scan */
	काष्ठा spi_transfer		scan_single_xfer;
	/* SPI message used by ring_xfer SPI transfer */
	काष्ठा spi_message		ring_msg;
	/* SPI message used by scan_single_xfer SPI transfer */
	काष्ठा spi_message		scan_single_msg;

	/*
	 * SPI message buffers:
	 *  tx_buf: |C0|C1|C2|C3|C4|C5|C6|C7|XX|
	 *  rx_buf: |XX|R0|R1|R2|R3|R4|R5|R6|R7|tt|tt|tt|tt|
	 *
	 *  tx_buf: 8 channel पढ़ो commands, plus 1 dummy command
	 *  rx_buf: 1 dummy response, 8 channel responses, plus 64-bit बारtamp
	 */
	__be16				rx_buf[13] ____cacheline_aligned;
	__be16				tx_buf[9] ____cacheline_aligned;
पूर्ण;

#घोषणा ADC108S102_V_CHAN(index)					\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = index,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
			BIT(IIO_CHAN_INFO_SCALE),			\
		.address = index,					\
		.scan_index = index,					\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = ADC108S102_BITS,			\
			.storagebits = 16,				\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adc108s102_channels[] = अणु
	ADC108S102_V_CHAN(0),
	ADC108S102_V_CHAN(1),
	ADC108S102_V_CHAN(2),
	ADC108S102_V_CHAN(3),
	ADC108S102_V_CHAN(4),
	ADC108S102_V_CHAN(5),
	ADC108S102_V_CHAN(6),
	ADC108S102_V_CHAN(7),
	IIO_CHAN_SOFT_TIMESTAMP(8),
पूर्ण;

अटल पूर्णांक adc108s102_update_scan_mode(काष्ठा iio_dev *indio_dev,
		अचिन्हित दीर्घ स्थिर *active_scan_mask)
अणु
	काष्ठा adc108s102_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक bit, cmds;

	/*
	 * Fill in the first x लघुs of tx_buf with the number of channels
	 * enabled क्रम sampling by the triggered buffer.
	 */
	cmds = 0;
	क्रम_each_set_bit(bit, active_scan_mask, ADC108S102_MAX_CHANNELS)
		st->tx_buf[cmds++] = cpu_to_be16(ADC108S102_CMD(bit));

	/* One dummy command added, to घड़ी in the last response */
	st->tx_buf[cmds++] = 0x00;

	/* build SPI ring message */
	st->ring_xfer.tx_buf = &st->tx_buf[0];
	st->ring_xfer.rx_buf = &st->rx_buf[0];
	st->ring_xfer.len = cmds * माप(st->tx_buf[0]);

	spi_message_init_with_transfers(&st->ring_msg, &st->ring_xfer, 1);

	वापस 0;
पूर्ण

अटल irqवापस_t adc108s102_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adc108s102_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = spi_sync(st->spi, &st->ring_msg);
	अगर (ret < 0)
		जाओ out_notअगरy;

	/* Skip the dummy response in the first slot */
	iio_push_to_buffers_with_बारtamp(indio_dev,
					   (u8 *)&st->rx_buf[1],
					   iio_get_समय_ns(indio_dev));

out_notअगरy:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adc108s102_scan_direct(काष्ठा adc108s102_state *st, अचिन्हित पूर्णांक ch)
अणु
	पूर्णांक ret;

	st->tx_buf[0] = cpu_to_be16(ADC108S102_CMD(ch));
	ret = spi_sync(st->spi, &st->scan_single_msg);
	अगर (ret)
		वापस ret;

	/* Skip the dummy response in the first slot */
	वापस be16_to_cpu(st->rx_buf[1]);
पूर्ण

अटल पूर्णांक adc108s102_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा adc108s102_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = adc108s102_scan_direct(st, chan->address);

		iio_device_release_direct_mode(indio_dev);

		अगर (ret < 0)
			वापस ret;

		*val = ADC108S102_RES_DATA(ret);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type != IIO_VOLTAGE)
			अवरोध;

		*val = st->va_millivolt;
		*val2 = chan->scan_type.realbits;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info adc108s102_info = अणु
	.पढ़ो_raw		= &adc108s102_पढ़ो_raw,
	.update_scan_mode	= &adc108s102_update_scan_mode,
पूर्ण;

अटल पूर्णांक adc108s102_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा adc108s102_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	अगर (ACPI_COMPANION(&spi->dev)) अणु
		st->va_millivolt = ADC108S102_VA_MV_ACPI_DEFAULT;
	पूर्ण अन्यथा अणु
		st->reg = devm_regulator_get(&spi->dev, "vref");
		अगर (IS_ERR(st->reg))
			वापस PTR_ERR(st->reg);

		ret = regulator_enable(st->reg);
		अगर (ret < 0) अणु
			dev_err(&spi->dev, "Cannot enable vref regulator\n");
			वापस ret;
		पूर्ण

		ret = regulator_get_voltage(st->reg);
		अगर (ret < 0) अणु
			dev_err(&spi->dev, "vref get voltage failed\n");
			वापस ret;
		पूर्ण

		st->va_millivolt = ret / 1000;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;

	indio_dev->name = spi->modalias;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = adc108s102_channels;
	indio_dev->num_channels = ARRAY_SIZE(adc108s102_channels);
	indio_dev->info = &adc108s102_info;

	/* Setup शेष message */
	st->scan_single_xfer.tx_buf = st->tx_buf;
	st->scan_single_xfer.rx_buf = st->rx_buf;
	st->scan_single_xfer.len = 2 * माप(st->tx_buf[0]);

	spi_message_init_with_transfers(&st->scan_single_msg,
					&st->scan_single_xfer, 1);

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 &adc108s102_trigger_handler, शून्य);
	अगर (ret)
		जाओ error_disable_reg;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to register IIO device\n");
		जाओ error_cleanup_triggered_buffer;
	पूर्ण
	वापस 0;

error_cleanup_triggered_buffer:
	iio_triggered_buffer_cleanup(indio_dev);

error_disable_reg:
	regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक adc108s102_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा adc108s102_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adc108s102_of_match[] = अणु
	अणु .compatible = "ti,adc108s102" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adc108s102_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id adc108s102_acpi_ids[] = अणु
	अणु "INT3495", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, adc108s102_acpi_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा spi_device_id adc108s102_id[] = अणु
	अणु "adc108s102", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adc108s102_id);

अटल काष्ठा spi_driver adc108s102_driver = अणु
	.driver = अणु
		.name   = "adc108s102",
		.of_match_table = adc108s102_of_match,
		.acpi_match_table = ACPI_PTR(adc108s102_acpi_ids),
	पूर्ण,
	.probe		= adc108s102_probe,
	.हटाओ		= adc108s102_हटाओ,
	.id_table	= adc108s102_id,
पूर्ण;
module_spi_driver(adc108s102_driver);

MODULE_AUTHOR("Bogdan Pricop <bogdan.pricop@emutex.com>");
MODULE_DESCRIPTION("Texas Instruments ADC108S102 and ADC128S102 driver");
MODULE_LICENSE("GPL v2");
