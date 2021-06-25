<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
 /*
  * iio/adc/max1027.c
  * Copyright (C) 2014 Philippe Reynes
  *
  * based on linux/drivers/iio/ad7923.c
  * Copyright 2011 Analog Devices Inc (from AD7923 Driver)
  * Copyright 2012 CS Systemes d'Inक्रमmation
  *
  * max1027.c
  *
  * Partial support क्रम max1027 and similar chips.
  */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा MAX1027_CONV_REG  BIT(7)
#घोषणा MAX1027_SETUP_REG BIT(6)
#घोषणा MAX1027_AVG_REG   BIT(5)
#घोषणा MAX1027_RST_REG   BIT(4)

/* conversion रेजिस्टर */
#घोषणा MAX1027_TEMP      BIT(0)
#घोषणा MAX1027_SCAN_0_N  (0x00 << 1)
#घोषणा MAX1027_SCAN_N_M  (0x01 << 1)
#घोषणा MAX1027_SCAN_N    (0x02 << 1)
#घोषणा MAX1027_NOSCAN    (0x03 << 1)
#घोषणा MAX1027_CHAN(n)   ((n) << 3)

/* setup रेजिस्टर */
#घोषणा MAX1027_UNIPOLAR  0x02
#घोषणा MAX1027_BIPOLAR   0x03
#घोषणा MAX1027_REF_MODE0 (0x00 << 2)
#घोषणा MAX1027_REF_MODE1 (0x01 << 2)
#घोषणा MAX1027_REF_MODE2 (0x02 << 2)
#घोषणा MAX1027_REF_MODE3 (0x03 << 2)
#घोषणा MAX1027_CKS_MODE0 (0x00 << 4)
#घोषणा MAX1027_CKS_MODE1 (0x01 << 4)
#घोषणा MAX1027_CKS_MODE2 (0x02 << 4)
#घोषणा MAX1027_CKS_MODE3 (0x03 << 4)

/* averaging रेजिस्टर */
#घोषणा MAX1027_NSCAN_4   0x00
#घोषणा MAX1027_NSCAN_8   0x01
#घोषणा MAX1027_NSCAN_12  0x02
#घोषणा MAX1027_NSCAN_16  0x03
#घोषणा MAX1027_NAVG_4    (0x00 << 2)
#घोषणा MAX1027_NAVG_8    (0x01 << 2)
#घोषणा MAX1027_NAVG_16   (0x02 << 2)
#घोषणा MAX1027_NAVG_32   (0x03 << 2)
#घोषणा MAX1027_AVG_EN    BIT(4)

क्रमागत max1027_id अणु
	max1027,
	max1029,
	max1031,
	max1227,
	max1229,
	max1231,
पूर्ण;

अटल स्थिर काष्ठा spi_device_id max1027_id[] = अणु
	अणु"max1027", max1027पूर्ण,
	अणु"max1029", max1029पूर्ण,
	अणु"max1031", max1031पूर्ण,
	अणु"max1227", max1227पूर्ण,
	अणु"max1229", max1229पूर्ण,
	अणु"max1231", max1231पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, max1027_id);

अटल स्थिर काष्ठा of_device_id max1027_adc_dt_ids[] = अणु
	अणु .compatible = "maxim,max1027" पूर्ण,
	अणु .compatible = "maxim,max1029" पूर्ण,
	अणु .compatible = "maxim,max1031" पूर्ण,
	अणु .compatible = "maxim,max1227" पूर्ण,
	अणु .compatible = "maxim,max1229" पूर्ण,
	अणु .compatible = "maxim,max1231" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max1027_adc_dt_ids);

#घोषणा MAX1027_V_CHAN(index, depth)					\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = index,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.scan_index = index + 1,				\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = depth,				\
			.storagebits = 16,				\
			.shअगरt = 2,					\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

#घोषणा MAX1027_T_CHAN							\
	अणु								\
		.type = IIO_TEMP,					\
		.channel = 0,						\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.scan_index = 0,					\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = 12,					\
			.storagebits = 16,				\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

#घोषणा MAX1X27_CHANNELS(depth)			\
	MAX1027_T_CHAN,				\
	MAX1027_V_CHAN(0, depth),		\
	MAX1027_V_CHAN(1, depth),		\
	MAX1027_V_CHAN(2, depth),		\
	MAX1027_V_CHAN(3, depth),		\
	MAX1027_V_CHAN(4, depth),		\
	MAX1027_V_CHAN(5, depth),		\
	MAX1027_V_CHAN(6, depth),		\
	MAX1027_V_CHAN(7, depth)

#घोषणा MAX1X29_CHANNELS(depth)			\
	MAX1X27_CHANNELS(depth),		\
	MAX1027_V_CHAN(8, depth),		\
	MAX1027_V_CHAN(9, depth),		\
	MAX1027_V_CHAN(10, depth),		\
	MAX1027_V_CHAN(11, depth)

#घोषणा MAX1X31_CHANNELS(depth)			\
	MAX1X27_CHANNELS(depth),		\
	MAX1X29_CHANNELS(depth),		\
	MAX1027_V_CHAN(12, depth),		\
	MAX1027_V_CHAN(13, depth),		\
	MAX1027_V_CHAN(14, depth),		\
	MAX1027_V_CHAN(15, depth)

अटल स्थिर काष्ठा iio_chan_spec max1027_channels[] = अणु
	MAX1X27_CHANNELS(10),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max1029_channels[] = अणु
	MAX1X29_CHANNELS(10),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max1031_channels[] = अणु
	MAX1X31_CHANNELS(10),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max1227_channels[] = अणु
	MAX1X27_CHANNELS(12),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max1229_channels[] = अणु
	MAX1X29_CHANNELS(12),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max1231_channels[] = अणु
	MAX1X31_CHANNELS(12),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ max1027_available_scan_masks[] = अणु
	0x000001ff,
	0x00000000,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ max1029_available_scan_masks[] = अणु
	0x00001fff,
	0x00000000,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ max1031_available_scan_masks[] = अणु
	0x0001ffff,
	0x00000000,
पूर्ण;

काष्ठा max1027_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	स्थिर अचिन्हित दीर्घ *available_scan_masks;
पूर्ण;

अटल स्थिर काष्ठा max1027_chip_info max1027_chip_info_tbl[] = अणु
	[max1027] = अणु
		.channels = max1027_channels,
		.num_channels = ARRAY_SIZE(max1027_channels),
		.available_scan_masks = max1027_available_scan_masks,
	पूर्ण,
	[max1029] = अणु
		.channels = max1029_channels,
		.num_channels = ARRAY_SIZE(max1029_channels),
		.available_scan_masks = max1029_available_scan_masks,
	पूर्ण,
	[max1031] = अणु
		.channels = max1031_channels,
		.num_channels = ARRAY_SIZE(max1031_channels),
		.available_scan_masks = max1031_available_scan_masks,
	पूर्ण,
	[max1227] = अणु
		.channels = max1227_channels,
		.num_channels = ARRAY_SIZE(max1227_channels),
		.available_scan_masks = max1027_available_scan_masks,
	पूर्ण,
	[max1229] = अणु
		.channels = max1229_channels,
		.num_channels = ARRAY_SIZE(max1229_channels),
		.available_scan_masks = max1029_available_scan_masks,
	पूर्ण,
	[max1231] = अणु
		.channels = max1231_channels,
		.num_channels = ARRAY_SIZE(max1231_channels),
		.available_scan_masks = max1031_available_scan_masks,
	पूर्ण,
पूर्ण;

काष्ठा max1027_state अणु
	स्थिर काष्ठा max1027_chip_info	*info;
	काष्ठा spi_device		*spi;
	काष्ठा iio_trigger		*trig;
	__be16				*buffer;
	काष्ठा mutex			lock;

	u8				reg ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक max1027_पढ़ो_single_value(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *chan,
				     पूर्णांक *val)
अणु
	पूर्णांक ret;
	काष्ठा max1027_state *st = iio_priv(indio_dev);

	अगर (iio_buffer_enabled(indio_dev)) अणु
		dev_warn(&indio_dev->dev, "trigger mode already enabled");
		वापस -EBUSY;
	पूर्ण

	/* Start acquisition on conversion रेजिस्टर ग_लिखो */
	st->reg = MAX1027_SETUP_REG | MAX1027_REF_MODE2 | MAX1027_CKS_MODE2;
	ret = spi_ग_लिखो(st->spi, &st->reg, 1);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev,
			"Failed to configure setup register\n");
		वापस ret;
	पूर्ण

	/* Configure conversion रेजिस्टर with the requested chan */
	st->reg = MAX1027_CONV_REG | MAX1027_CHAN(chan->channel) |
		  MAX1027_NOSCAN;
	अगर (chan->type == IIO_TEMP)
		st->reg |= MAX1027_TEMP;
	ret = spi_ग_लिखो(st->spi, &st->reg, 1);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev,
			"Failed to configure conversion register\n");
		वापस ret;
	पूर्ण

	/*
	 * For an unknown reason, when we use the mode "10" (ग_लिखो
	 * conversion रेजिस्टर), the पूर्णांकerrupt करोesn't occur every समय.
	 * So we just रुको 1 ms.
	 */
	mdelay(1);

	/* Read result */
	ret = spi_पढ़ो(st->spi, st->buffer, (chan->type == IIO_TEMP) ? 4 : 2);
	अगर (ret < 0)
		वापस ret;

	*val = be16_to_cpu(st->buffer[0]);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक max1027_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret = 0;
	काष्ठा max1027_state *st = iio_priv(indio_dev);

	mutex_lock(&st->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = max1027_पढ़ो_single_value(indio_dev, chan, val);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = 1;
			*val2 = 8;
			ret = IIO_VAL_FRACTIONAL;
			अवरोध;
		हाल IIO_VOLTAGE:
			*val = 2500;
			*val2 = chan->scan_type.realbits;
			ret = IIO_VAL_FRACTIONAL_LOG2;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक max1027_debugfs_reg_access(काष्ठा iio_dev *indio_dev,
				      अचिन्हित reg, अचिन्हित ग_लिखोval,
				      अचिन्हित *पढ़ोval)
अणु
	काष्ठा max1027_state *st = iio_priv(indio_dev);
	u8 *val = (u8 *)st->buffer;

	अगर (पढ़ोval) अणु
		पूर्णांक ret = spi_पढ़ो(st->spi, val, 2);
		*पढ़ोval = be16_to_cpu(st->buffer[0]);
		वापस ret;
	पूर्ण

	*val = (u8)ग_लिखोval;
	वापस spi_ग_लिखो(st->spi, val, 1);
पूर्ण

अटल पूर्णांक max1027_validate_trigger(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_trigger *trig)
अणु
	काष्ठा max1027_state *st = iio_priv(indio_dev);

	अगर (st->trig != trig)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक max1027_set_trigger_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा max1027_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (state) अणु
		/* Start acquisition on cnvst */
		st->reg = MAX1027_SETUP_REG | MAX1027_CKS_MODE0 |
			  MAX1027_REF_MODE2;
		ret = spi_ग_लिखो(st->spi, &st->reg, 1);
		अगर (ret < 0)
			वापस ret;

		/* Scan from 0 to max */
		st->reg = MAX1027_CONV_REG | MAX1027_CHAN(0) |
			  MAX1027_SCAN_N_M | MAX1027_TEMP;
		ret = spi_ग_लिखो(st->spi, &st->reg, 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Start acquisition on conversion रेजिस्टर ग_लिखो */
		st->reg = MAX1027_SETUP_REG | MAX1027_CKS_MODE2	|
			  MAX1027_REF_MODE2;
		ret = spi_ग_लिखो(st->spi, &st->reg, 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t max1027_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा max1027_state *st = iio_priv(indio_dev);

	pr_debug("%s(irq=%d, private=0x%p)\n", __func__, irq, निजी);

	/* fill buffer with all channel */
	spi_पढ़ो(st->spi, st->buffer, indio_dev->masklength * 2);

	iio_push_to_buffers(indio_dev, st->buffer);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops max1027_trigger_ops = अणु
	.validate_device = &iio_trigger_validate_own_device,
	.set_trigger_state = &max1027_set_trigger_state,
पूर्ण;

अटल स्थिर काष्ठा iio_info max1027_info = अणु
	.पढ़ो_raw = &max1027_पढ़ो_raw,
	.validate_trigger = &max1027_validate_trigger,
	.debugfs_reg_access = &max1027_debugfs_reg_access,
पूर्ण;

अटल पूर्णांक max1027_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा max1027_state *st;

	pr_debug("%s: probe(spi = 0x%p)\n", __func__, spi);

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य) अणु
		pr_err("Can't allocate iio device\n");
		वापस -ENOMEM;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);

	st = iio_priv(indio_dev);
	st->spi = spi;
	st->info = &max1027_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	mutex_init(&st->lock);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &max1027_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->info->channels;
	indio_dev->num_channels = st->info->num_channels;
	indio_dev->available_scan_masks = st->info->available_scan_masks;

	st->buffer = devm_kदो_स्मृति_array(&indio_dev->dev,
				  indio_dev->num_channels, 2,
				  GFP_KERNEL);
	अगर (st->buffer == शून्य) अणु
		dev_err(&indio_dev->dev, "Can't allocate buffer\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (spi->irq) अणु
		ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev,
						      &iio_pollfunc_store_समय,
						      &max1027_trigger_handler,
						      शून्य);
		अगर (ret < 0) अणु
			dev_err(&indio_dev->dev, "Failed to setup buffer\n");
			वापस ret;
		पूर्ण

		st->trig = devm_iio_trigger_alloc(&spi->dev, "%s-trigger",
						  indio_dev->name);
		अगर (st->trig == शून्य) अणु
			ret = -ENOMEM;
			dev_err(&indio_dev->dev,
				"Failed to allocate iio trigger\n");
			वापस ret;
		पूर्ण

		st->trig->ops = &max1027_trigger_ops;
		iio_trigger_set_drvdata(st->trig, indio_dev);
		ret = devm_iio_trigger_रेजिस्टर(&indio_dev->dev,
						st->trig);
		अगर (ret < 0) अणु
			dev_err(&indio_dev->dev,
				"Failed to register iio trigger\n");
			वापस ret;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq,
						iio_trigger_generic_data_rdy_poll,
						शून्य,
						IRQF_TRIGGER_FALLING,
						spi->dev.driver->name,
						st->trig);
		अगर (ret < 0) अणु
			dev_err(&indio_dev->dev, "Failed to allocate IRQ.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Internal reset */
	st->reg = MAX1027_RST_REG;
	ret = spi_ग_लिखो(st->spi, &st->reg, 1);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev, "Failed to reset the ADC\n");
		वापस ret;
	पूर्ण

	/* Disable averaging */
	st->reg = MAX1027_AVG_REG;
	ret = spi_ग_लिखो(st->spi, &st->reg, 1);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev, "Failed to configure averaging register\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल काष्ठा spi_driver max1027_driver = अणु
	.driver = अणु
		.name	= "max1027",
		.of_match_table = max1027_adc_dt_ids,
	पूर्ण,
	.probe		= max1027_probe,
	.id_table	= max1027_id,
पूर्ण;
module_spi_driver(max1027_driver);

MODULE_AUTHOR("Philippe Reynes <tremyfr@yahoo.fr>");
MODULE_DESCRIPTION("MAX1X27/MAX1X29/MAX1X31 ADC");
MODULE_LICENSE("GPL v2");
