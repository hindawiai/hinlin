<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD7766/AD7767 SPI ADC driver
 *
 * Copyright 2016 Analog Devices Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

काष्ठा ad7766_chip_info अणु
	अचिन्हित पूर्णांक decimation_factor;
पूर्ण;

क्रमागत अणु
	AD7766_SUPPLY_AVDD = 0,
	AD7766_SUPPLY_DVDD = 1,
	AD7766_SUPPLY_VREF = 2,
	AD7766_NUM_SUPPLIES = 3
पूर्ण;

काष्ठा ad7766 अणु
	स्थिर काष्ठा ad7766_chip_info *chip_info;
	काष्ठा spi_device *spi;
	काष्ठा clk *mclk;
	काष्ठा gpio_desc *pd_gpio;
	काष्ठा regulator_bulk_data reg[AD7766_NUM_SUPPLIES];

	काष्ठा iio_trigger *trig;

	काष्ठा spi_transfer xfer;
	काष्ठा spi_message msg;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 * Make the buffer large enough क्रम one 24 bit sample and one 64 bit
	 * aligned 64 bit बारtamp.
	 */
	अचिन्हित अक्षर data[ALIGN(3, माप(s64)) + माप(s64)]
			____cacheline_aligned;
पूर्ण;

/*
 * AD7766 and AD7767 variations are पूर्णांकerface compatible, the मुख्य dअगरference is
 * analog perक्रमmance. Both parts will use the same ID.
 */
क्रमागत ad7766_device_ids अणु
	ID_AD7766,
	ID_AD7766_1,
	ID_AD7766_2,
पूर्ण;

अटल irqवापस_t ad7766_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad7766 *ad7766 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = spi_sync(ad7766->spi, &ad7766->msg);
	अगर (ret < 0)
		जाओ करोne;

	iio_push_to_buffers_with_बारtamp(indio_dev, ad7766->data,
		pf->बारtamp);
करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ad7766_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7766 *ad7766 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ad7766->reg), ad7766->reg);
	अगर (ret < 0) अणु
		dev_err(&ad7766->spi->dev, "Failed to enable supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(ad7766->mclk);
	अगर (ret < 0) अणु
		dev_err(&ad7766->spi->dev, "Failed to enable MCLK: %d\n", ret);
		regulator_bulk_disable(ARRAY_SIZE(ad7766->reg), ad7766->reg);
		वापस ret;
	पूर्ण

	gpiod_set_value(ad7766->pd_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7766_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7766 *ad7766 = iio_priv(indio_dev);

	gpiod_set_value(ad7766->pd_gpio, 1);

	/*
	 * The PD pin is synchronous to the घड़ी, so give it some समय to
	 * notice the change beक्रमe we disable the घड़ी.
	 */
	msleep(20);

	clk_disable_unprepare(ad7766->mclk);
	regulator_bulk_disable(ARRAY_SIZE(ad7766->reg), ad7766->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7766_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad7766 *ad7766 = iio_priv(indio_dev);
	काष्ठा regulator *vref = ad7766->reg[AD7766_SUPPLY_VREF].consumer;
	पूर्णांक scale_uv;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_SCALE:
		scale_uv = regulator_get_voltage(vref);
		अगर (scale_uv < 0)
			वापस scale_uv;
		*val = scale_uv / 1000;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = clk_get_rate(ad7766->mclk) /
			ad7766->chip_info->decimation_factor;
		वापस IIO_VAL_INT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad7766_channels[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.scan_type = अणु
			.sign = 's',
			.realbits = 24,
			.storagebits = 32,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल स्थिर काष्ठा ad7766_chip_info ad7766_chip_info[] = अणु
	[ID_AD7766] = अणु
		.decimation_factor = 8,
	पूर्ण,
	[ID_AD7766_1] = अणु
		.decimation_factor = 16,
	पूर्ण,
	[ID_AD7766_2] = अणु
		.decimation_factor = 32,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_buffer_setup_ops ad7766_buffer_setup_ops = अणु
	.preenable = &ad7766_preenable,
	.postdisable = &ad7766_postdisable,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7766_info = अणु
	.पढ़ो_raw = &ad7766_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t ad7766_irq(पूर्णांक irq, व्योम *निजी)
अणु
	iio_trigger_poll(निजी);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ad7766_set_trigger_state(काष्ठा iio_trigger *trig, bool enable)
अणु
	काष्ठा ad7766 *ad7766 = iio_trigger_get_drvdata(trig);

	अगर (enable)
		enable_irq(ad7766->spi->irq);
	अन्यथा
		disable_irq(ad7766->spi->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops ad7766_trigger_ops = अणु
	.set_trigger_state = ad7766_set_trigger_state,
	.validate_device = iio_trigger_validate_own_device,
पूर्ण;

अटल पूर्णांक ad7766_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad7766 *ad7766;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*ad7766));
	अगर (!indio_dev)
		वापस -ENOMEM;

	ad7766 = iio_priv(indio_dev);
	ad7766->chip_info = &ad7766_chip_info[id->driver_data];

	ad7766->mclk = devm_clk_get(&spi->dev, "mclk");
	अगर (IS_ERR(ad7766->mclk))
		वापस PTR_ERR(ad7766->mclk);

	ad7766->reg[AD7766_SUPPLY_AVDD].supply = "avdd";
	ad7766->reg[AD7766_SUPPLY_DVDD].supply = "dvdd";
	ad7766->reg[AD7766_SUPPLY_VREF].supply = "vref";

	ret = devm_regulator_bulk_get(&spi->dev, ARRAY_SIZE(ad7766->reg),
		ad7766->reg);
	अगर (ret)
		वापस ret;

	ad7766->pd_gpio = devm_gpiod_get_optional(&spi->dev, "powerdown",
		GPIOD_OUT_HIGH);
	अगर (IS_ERR(ad7766->pd_gpio))
		वापस PTR_ERR(ad7766->pd_gpio);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad7766_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7766_channels);
	indio_dev->info = &ad7766_info;

	अगर (spi->irq > 0) अणु
		ad7766->trig = devm_iio_trigger_alloc(&spi->dev, "%s-dev%d",
			indio_dev->name, indio_dev->id);
		अगर (!ad7766->trig)
			वापस -ENOMEM;

		ad7766->trig->ops = &ad7766_trigger_ops;
		iio_trigger_set_drvdata(ad7766->trig, ad7766);

		/*
		 * The device generates पूर्णांकerrupts as दीर्घ as it is घातered up.
		 * Some platक्रमms might not allow the option to घातer it करोwn so
		 * करोn't enable the पूर्णांकerrupt to aव्योम extra load on the प्रणाली
		 */
		ret = devm_request_irq(&spi->dev, spi->irq, ad7766_irq,
				       IRQF_TRIGGER_FALLING | IRQF_NO_AUTOEN,
				       dev_name(&spi->dev),
				       ad7766->trig);
		अगर (ret < 0)
			वापस ret;

		ret = devm_iio_trigger_रेजिस्टर(&spi->dev, ad7766->trig);
		अगर (ret)
			वापस ret;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);

	ad7766->spi = spi;

	/* First byte always 0 */
	ad7766->xfer.rx_buf = &ad7766->data[1];
	ad7766->xfer.len = 3;

	spi_message_init(&ad7766->msg);
	spi_message_add_tail(&ad7766->xfer, &ad7766->msg);

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev,
		&iio_pollfunc_store_समय, &ad7766_trigger_handler,
		&ad7766_buffer_setup_ops);
	अगर (ret)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7766_id[] = अणु
	अणु"ad7766", ID_AD7766पूर्ण,
	अणु"ad7766-1", ID_AD7766_1पूर्ण,
	अणु"ad7766-2", ID_AD7766_2पूर्ण,
	अणु"ad7767", ID_AD7766पूर्ण,
	अणु"ad7767-1", ID_AD7766_1पूर्ण,
	अणु"ad7767-2", ID_AD7766_2पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7766_id);

अटल काष्ठा spi_driver ad7766_driver = अणु
	.driver = अणु
		.name	= "ad7766",
	पूर्ण,
	.probe		= ad7766_probe,
	.id_table	= ad7766_id,
पूर्ण;
module_spi_driver(ad7766_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD7766 and AD7767 ADCs driver support");
MODULE_LICENSE("GPL v2");
