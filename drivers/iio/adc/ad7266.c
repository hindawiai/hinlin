<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD7266/65 SPI ADC driver
 *
 * Copyright 2012 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश <linux/platक्रमm_data/ad7266.h>

काष्ठा ad7266_state अणु
	काष्ठा spi_device	*spi;
	काष्ठा regulator	*reg;
	अचिन्हित दीर्घ		vref_mv;

	काष्ठा spi_transfer	single_xfer[3];
	काष्ठा spi_message	single_msg;

	क्रमागत ad7266_range	range;
	क्रमागत ad7266_mode	mode;
	bool			fixed_addr;
	काष्ठा gpio_desc	*gpios[3];

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 * The buffer needs to be large enough to hold two samples (4 bytes) and
	 * the naturally aligned बारtamp (8 bytes).
	 */
	काष्ठा अणु
		__be16 sample[2];
		s64 बारtamp;
	पूर्ण data ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ad7266_wakeup(काष्ठा ad7266_state *st)
अणु
	/* Any पढ़ो with >= 2 bytes will wake the device */
	वापस spi_पढ़ो(st->spi, &st->data.sample[0], 2);
पूर्ण

अटल पूर्णांक ad7266_घातerकरोwn(काष्ठा ad7266_state *st)
अणु
	/* Any पढ़ो with < 2 bytes will घातerकरोwn the device */
	वापस spi_पढ़ो(st->spi, &st->data.sample[0], 1);
पूर्ण

अटल पूर्णांक ad7266_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7266_state *st = iio_priv(indio_dev);
	वापस ad7266_wakeup(st);
पूर्ण

अटल पूर्णांक ad7266_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7266_state *st = iio_priv(indio_dev);
	वापस ad7266_घातerकरोwn(st);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops iio_triggered_buffer_setup_ops = अणु
	.preenable = &ad7266_preenable,
	.postdisable = &ad7266_postdisable,
पूर्ण;

अटल irqवापस_t ad7266_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad7266_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = spi_पढ़ो(st->spi, st->data.sample, 4);
	अगर (ret == 0) अणु
		iio_push_to_buffers_with_बारtamp(indio_dev, &st->data,
			    pf->बारtamp);
	पूर्ण

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ad7266_select_input(काष्ठा ad7266_state *st, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक i;

	अगर (st->fixed_addr)
		वापस;

	चयन (st->mode) अणु
	हाल AD7266_MODE_SINGLE_ENDED:
		nr >>= 1;
		अवरोध;
	हाल AD7266_MODE_PSEUDO_DIFF:
		nr |= 1;
		अवरोध;
	हाल AD7266_MODE_DIFF:
		nr &= ~1;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < 3; ++i)
		gpiod_set_value(st->gpios[i], (bool)(nr & BIT(i)));
पूर्ण

अटल पूर्णांक ad7266_update_scan_mode(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा ad7266_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक nr = find_first_bit(scan_mask, indio_dev->masklength);

	ad7266_select_input(st, nr);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7266_पढ़ो_single(काष्ठा ad7266_state *st, पूर्णांक *val,
	अचिन्हित पूर्णांक address)
अणु
	पूर्णांक ret;

	ad7266_select_input(st, address);

	ret = spi_sync(st->spi, &st->single_msg);
	*val = be16_to_cpu(st->data.sample[address % 2]);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7266_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा ad7266_state *st = iio_priv(indio_dev);
	अचिन्हित दीर्घ scale_mv;
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = ad7266_पढ़ो_single(st, val, chan->address);
		iio_device_release_direct_mode(indio_dev);

		*val = (*val >> 2) & 0xfff;
		अगर (chan->scan_type.sign == 's')
			*val = sign_extend32(*val, 11);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		scale_mv = st->vref_mv;
		अगर (st->mode == AD7266_MODE_DIFF)
			scale_mv *= 2;
		अगर (st->range == AD7266_RANGE_2VREF)
			scale_mv *= 2;

		*val = scale_mv;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		अगर (st->range == AD7266_RANGE_2VREF &&
			st->mode != AD7266_MODE_DIFF)
			*val = 2048;
		अन्यथा
			*val = 0;
		वापस IIO_VAL_INT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा AD7266_CHAN(_chan, _sign) अणु			\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.channel = (_chan),				\
	.address = (_chan),				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) \
		| BIT(IIO_CHAN_INFO_OFFSET),			\
	.scan_index = (_chan),				\
	.scan_type = अणु					\
		.sign = (_sign),			\
		.realbits = 12,				\
		.storagebits = 16,			\
		.shअगरt = 2,				\
		.endianness = IIO_BE,			\
	पूर्ण,						\
पूर्ण

#घोषणा AD7266_DECLARE_SINGLE_ENDED_CHANNELS(_name, _sign) \
स्थिर काष्ठा iio_chan_spec ad7266_channels_##_name[] = अणु \
	AD7266_CHAN(0, (_sign)), \
	AD7266_CHAN(1, (_sign)), \
	AD7266_CHAN(2, (_sign)), \
	AD7266_CHAN(3, (_sign)), \
	AD7266_CHAN(4, (_sign)), \
	AD7266_CHAN(5, (_sign)), \
	AD7266_CHAN(6, (_sign)), \
	AD7266_CHAN(7, (_sign)), \
	AD7266_CHAN(8, (_sign)), \
	AD7266_CHAN(9, (_sign)), \
	AD7266_CHAN(10, (_sign)), \
	AD7266_CHAN(11, (_sign)), \
	IIO_CHAN_SOFT_TIMESTAMP(13), \
पूर्ण

#घोषणा AD7266_DECLARE_SINGLE_ENDED_CHANNELS_FIXED(_name, _sign) \
स्थिर काष्ठा iio_chan_spec ad7266_channels_##_name##_fixed[] = अणु \
	AD7266_CHAN(0, (_sign)), \
	AD7266_CHAN(1, (_sign)), \
	IIO_CHAN_SOFT_TIMESTAMP(2), \
पूर्ण

अटल AD7266_DECLARE_SINGLE_ENDED_CHANNELS(u, 'u');
अटल AD7266_DECLARE_SINGLE_ENDED_CHANNELS(s, 's');
अटल AD7266_DECLARE_SINGLE_ENDED_CHANNELS_FIXED(u, 'u');
अटल AD7266_DECLARE_SINGLE_ENDED_CHANNELS_FIXED(s, 's');

#घोषणा AD7266_CHAN_DIFF(_chan, _sign) अणु			\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.channel = (_chan) * 2,				\
	.channel2 = (_chan) * 2 + 1,			\
	.address = (_chan),				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE)	\
		| BIT(IIO_CHAN_INFO_OFFSET),			\
	.scan_index = (_chan),				\
	.scan_type = अणु					\
		.sign = _sign,			\
		.realbits = 12,				\
		.storagebits = 16,			\
		.shअगरt = 2,				\
		.endianness = IIO_BE,			\
	पूर्ण,						\
	.dअगरferential = 1,				\
पूर्ण

#घोषणा AD7266_DECLARE_DIFF_CHANNELS(_name, _sign) \
स्थिर काष्ठा iio_chan_spec ad7266_channels_dअगरf_##_name[] = अणु \
	AD7266_CHAN_DIFF(0, (_sign)), \
	AD7266_CHAN_DIFF(1, (_sign)), \
	AD7266_CHAN_DIFF(2, (_sign)), \
	AD7266_CHAN_DIFF(3, (_sign)), \
	AD7266_CHAN_DIFF(4, (_sign)), \
	AD7266_CHAN_DIFF(5, (_sign)), \
	IIO_CHAN_SOFT_TIMESTAMP(6), \
पूर्ण

अटल AD7266_DECLARE_DIFF_CHANNELS(s, 's');
अटल AD7266_DECLARE_DIFF_CHANNELS(u, 'u');

#घोषणा AD7266_DECLARE_DIFF_CHANNELS_FIXED(_name, _sign) \
स्थिर काष्ठा iio_chan_spec ad7266_channels_dअगरf_fixed_##_name[] = अणु \
	AD7266_CHAN_DIFF(0, (_sign)), \
	AD7266_CHAN_DIFF(1, (_sign)), \
	IIO_CHAN_SOFT_TIMESTAMP(2), \
पूर्ण

अटल AD7266_DECLARE_DIFF_CHANNELS_FIXED(s, 's');
अटल AD7266_DECLARE_DIFF_CHANNELS_FIXED(u, 'u');

अटल स्थिर काष्ठा iio_info ad7266_info = अणु
	.पढ़ो_raw = &ad7266_पढ़ो_raw,
	.update_scan_mode = &ad7266_update_scan_mode,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ad7266_available_scan_masks[] = अणु
	0x003,
	0x00c,
	0x030,
	0x0c0,
	0x300,
	0xc00,
	0x000,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ad7266_available_scan_masks_dअगरf[] = अणु
	0x003,
	0x00c,
	0x030,
	0x000,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ad7266_available_scan_masks_fixed[] = अणु
	0x003,
	0x000,
पूर्ण;

काष्ठा ad7266_chan_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	स्थिर अचिन्हित दीर्घ *scan_masks;
पूर्ण;

#घोषणा AD7266_CHAN_INFO_INDEX(_dअगरferential, _चिन्हित, _fixed) \
	(((_dअगरferential) << 2) | ((_चिन्हित) << 1) | ((_fixed) << 0))

अटल स्थिर काष्ठा ad7266_chan_info ad7266_chan_infos[] = अणु
	[AD7266_CHAN_INFO_INDEX(0, 0, 0)] = अणु
		.channels = ad7266_channels_u,
		.num_channels = ARRAY_SIZE(ad7266_channels_u),
		.scan_masks = ad7266_available_scan_masks,
	पूर्ण,
	[AD7266_CHAN_INFO_INDEX(0, 0, 1)] = अणु
		.channels = ad7266_channels_u_fixed,
		.num_channels = ARRAY_SIZE(ad7266_channels_u_fixed),
		.scan_masks = ad7266_available_scan_masks_fixed,
	पूर्ण,
	[AD7266_CHAN_INFO_INDEX(0, 1, 0)] = अणु
		.channels = ad7266_channels_s,
		.num_channels = ARRAY_SIZE(ad7266_channels_s),
		.scan_masks = ad7266_available_scan_masks,
	पूर्ण,
	[AD7266_CHAN_INFO_INDEX(0, 1, 1)] = अणु
		.channels = ad7266_channels_s_fixed,
		.num_channels = ARRAY_SIZE(ad7266_channels_s_fixed),
		.scan_masks = ad7266_available_scan_masks_fixed,
	पूर्ण,
	[AD7266_CHAN_INFO_INDEX(1, 0, 0)] = अणु
		.channels = ad7266_channels_dअगरf_u,
		.num_channels = ARRAY_SIZE(ad7266_channels_dअगरf_u),
		.scan_masks = ad7266_available_scan_masks_dअगरf,
	पूर्ण,
	[AD7266_CHAN_INFO_INDEX(1, 0, 1)] = अणु
		.channels = ad7266_channels_dअगरf_fixed_u,
		.num_channels = ARRAY_SIZE(ad7266_channels_dअगरf_fixed_u),
		.scan_masks = ad7266_available_scan_masks_fixed,
	पूर्ण,
	[AD7266_CHAN_INFO_INDEX(1, 1, 0)] = अणु
		.channels = ad7266_channels_dअगरf_s,
		.num_channels = ARRAY_SIZE(ad7266_channels_dअगरf_s),
		.scan_masks = ad7266_available_scan_masks_dअगरf,
	पूर्ण,
	[AD7266_CHAN_INFO_INDEX(1, 1, 1)] = अणु
		.channels = ad7266_channels_dअगरf_fixed_s,
		.num_channels = ARRAY_SIZE(ad7266_channels_dअगरf_fixed_s),
		.scan_masks = ad7266_available_scan_masks_fixed,
	पूर्ण,
पूर्ण;

अटल व्योम ad7266_init_channels(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7266_state *st = iio_priv(indio_dev);
	bool is_dअगरferential, is_चिन्हित;
	स्थिर काष्ठा ad7266_chan_info *chan_info;
	पूर्णांक i;

	is_dअगरferential = st->mode != AD7266_MODE_SINGLE_ENDED;
	is_चिन्हित = (st->range == AD7266_RANGE_2VREF) |
		    (st->mode == AD7266_MODE_DIFF);

	i = AD7266_CHAN_INFO_INDEX(is_dअगरferential, is_चिन्हित, st->fixed_addr);
	chan_info = &ad7266_chan_infos[i];

	indio_dev->channels = chan_info->channels;
	indio_dev->num_channels = chan_info->num_channels;
	indio_dev->available_scan_masks = chan_info->scan_masks;
	indio_dev->masklength = chan_info->num_channels - 1;
पूर्ण

अटल स्थिर अक्षर * स्थिर ad7266_gpio_labels[] = अणु
	"ad0", "ad1", "ad2",
पूर्ण;

अटल पूर्णांक ad7266_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7266_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad7266_state *st;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get_optional(&spi->dev, "vref");
	अगर (!IS_ERR(st->reg)) अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;

		ret = regulator_get_voltage(st->reg);
		अगर (ret < 0)
			जाओ error_disable_reg;

		st->vref_mv = ret / 1000;
	पूर्ण अन्यथा अणु
		/* Any other error indicates that the regulator करोes exist */
		अगर (PTR_ERR(st->reg) != -ENODEV)
			वापस PTR_ERR(st->reg);
		/* Use पूर्णांकernal reference */
		st->vref_mv = 2500;
	पूर्ण

	अगर (pdata) अणु
		st->fixed_addr = pdata->fixed_addr;
		st->mode = pdata->mode;
		st->range = pdata->range;

		अगर (!st->fixed_addr) अणु
			क्रम (i = 0; i < ARRAY_SIZE(st->gpios); ++i) अणु
				st->gpios[i] = devm_gpiod_get(&spi->dev,
						      ad7266_gpio_labels[i],
						      GPIOD_OUT_LOW);
				अगर (IS_ERR(st->gpios[i])) अणु
					ret = PTR_ERR(st->gpios[i]);
					जाओ error_disable_reg;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		st->fixed_addr = true;
		st->range = AD7266_RANGE_VREF;
		st->mode = AD7266_MODE_DIFF;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &ad7266_info;

	ad7266_init_channels(indio_dev);

	/* wakeup */
	st->single_xfer[0].rx_buf = &st->data.sample[0];
	st->single_xfer[0].len = 2;
	st->single_xfer[0].cs_change = 1;
	/* conversion */
	st->single_xfer[1].rx_buf = st->data.sample;
	st->single_xfer[1].len = 4;
	st->single_xfer[1].cs_change = 1;
	/* घातerकरोwn */
	st->single_xfer[2].tx_buf = &st->data.sample[0];
	st->single_xfer[2].len = 1;

	spi_message_init(&st->single_msg);
	spi_message_add_tail(&st->single_xfer[0], &st->single_msg);
	spi_message_add_tail(&st->single_xfer[1], &st->single_msg);
	spi_message_add_tail(&st->single_xfer[2], &st->single_msg);

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_समय,
		&ad7266_trigger_handler, &iio_triggered_buffer_setup_ops);
	अगर (ret)
		जाओ error_disable_reg;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_buffer_cleanup;

	वापस 0;

error_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
error_disable_reg:
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7266_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad7266_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7266_id[] = अणु
	अणु"ad7265", 0पूर्ण,
	अणु"ad7266", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7266_id);

अटल काष्ठा spi_driver ad7266_driver = अणु
	.driver = अणु
		.name	= "ad7266",
	पूर्ण,
	.probe		= ad7266_probe,
	.हटाओ		= ad7266_हटाओ,
	.id_table	= ad7266_id,
पूर्ण;
module_spi_driver(ad7266_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD7266/65 ADC");
MODULE_LICENSE("GPL v2");
